import bpy
import numpy as np
import bmesh
import functools
import ctypes

import utils_math
from utils_common import timer

class AtomicException(Exception):
    pass

class MeshTypeException(Exception):
    pass

class MorphUncalculatedException(Exception):
    pass

class UVIndexException(Exception):
    pass

class UVNotFoundException(Exception):
    pass

class Primitive():
    class Options():
        def __init__(self):
            self.max_border = 0.0
            self.secondary_uv_layer_index = -1 # May cause different atomic vertices!
            self.gather_weights_data = False
            self.gather_morph_data = False
            self.use_global_positions = False

            # Less frequently changed options
            self.normal_tangent_round_precision = 3
            self.atomic_max_number = 65535
            self.weight_cutoff_threshold = 0.0001
            self.max_weights_per_vertex = 8
            self.prune_empty_vertex_groups = True

            self.vertex_group_merge_source:list[str] = []
            self.vertex_group_merge_target:str = ''

            self.vertex_group_ignore:list[str] = []

    def __init__(self, object:bpy.types.Object, options:Options = Options()):
        if object.type != "MESH":
            raise MeshTypeException("Primitive.__init__() expect input 'object' to be a 'MESH' type object. Got: " + object.type)
        self.blender_object:bpy.types.Object = object
        self.blender_mesh:bpy.types.Mesh = object.data
        # Attributes should be per-vertex, used to convert per-loop data to per-vertex data
        self._atomic_attributes = [
            ('vertex_index', np.uint32), 
            ('uv_x', np.float32),
            ('uv_y', np.float32),
            ('uv_x_2', np.float32),
            ('uv_y_2', np.float32),
            ('normal_x', np.float32),
            ('normal_y', np.float32),
            ('normal_z', np.float32),
            ('color_r', np.float32),
            ('color_g', np.float32),
            ('color_b', np.float32),
            ('color_a', np.float32)
        ]
        self.vertex_weights_data = {
            "vertex_weights": [],
            "vertex_group_names": []
        }
        self.vertex_morph_data = {
            "shapeKeys": [],
            "deltaPositions": None,
            "targetColors": None,
            "deltaNormals": None,
            "deltaTangents": None
        }
        self.triangles = None

        self.atomic_vertices = np.empty(len(self.blender_mesh.loops), dtype=self._atomic_attributes)
        self.atomic_to_loop_id = None # Mapping from atomic vertex id to loop id
        self.loop_id_to_atomic = None # Mapping from loop id to atomic vertex id

        self.gather_color_data = True
        self.color_data_source_index = -1
        self.color_domain = None

        self.options = options

        self.key_blocks:list[bpy.types.ShapeKey] = []

    @functools.cached_property
    def positions(self):
        return self.raw_positions[self.atomic_vertices['vertex_index']]

    @functools.cached_property
    def uv(self):
        _uv = np.empty((len(self.atomic_vertices), 2), dtype=np.float32) # To ensure row-major order in memory
        _uv[:, 0] = self.atomic_vertices['uv_x']
        _uv[:, 1] = self.atomic_vertices['uv_y']
        return _uv
    
    @functools.cached_property
    def uv_2(self):
        _uv = np.empty((len(self.atomic_vertices), 2), dtype=np.float32)
        _uv[:, 0] = self.atomic_vertices['uv_x_2']
        _uv[:, 1] = self.atomic_vertices['uv_y_2']
        return _uv
    
    @functools.cached_property
    def normals(self):
        _normal = np.empty((len(self.atomic_vertices), 3), dtype=np.float32)
        _normal[:, 0] = self.atomic_vertices['normal_x']
        _normal[:, 1] = self.atomic_vertices['normal_y']
        _normal[:, 2] = self.atomic_vertices['normal_z']
        return _normal

    @functools.cached_property
    def tangents(self):
        return self.raw_tangents[self.atomic_to_loop_id]
    
    @functools.cached_property
    def bitangent_sign(self):
        return self.raw_bitangent_signs[self.atomic_to_loop_id]
    
    @functools.cached_property
    def colors(self):
        _color = np.empty((len(self.atomic_vertices), 4), dtype=np.float32)
        _color[:, 0] = self.atomic_vertices['color_r']
        _color[:, 1] = self.atomic_vertices['color_g']
        _color[:, 2] = self.atomic_vertices['color_b']
        _color[:, 3] = self.atomic_vertices['color_a']
        return _color

    @functools.cached_property
    def morph_positions(self):
        return [raw_morph_positions[self.atomic_vertices['vertex_index']] for raw_morph_positions in self.raw_morph_positions]

    @functools.cached_property
    def morph_normals(self):
        return [raw_morph_normals[self.atomic_to_loop_id] for raw_morph_normals in self.raw_morph_normals]
    
    @functools.cached_property
    def morph_tangents(self):
        return [raw_morph_tangents[self.atomic_to_loop_id] for raw_morph_tangents in self.raw_morph_tangents]
    
    @functools.cached_property
    def morph_position_deltas(self):
        return [raw_morph_position_deltas[self.atomic_vertices['vertex_index']] for raw_morph_position_deltas in self.raw_morph_position_deltas]

    @functools.cached_property
    def morph_normal_deltas(self):
        return [raw_morph_normal_deltas[self.atomic_to_loop_id] for raw_morph_normal_deltas in self.raw_morph_normal_deltas]
    
    @functools.cached_property
    def morph_tangent_deltas(self):
        return [raw_morph_tangent_deltas[self.atomic_to_loop_id] for raw_morph_tangent_deltas in self.raw_morph_tangent_deltas]

    def gather(self):
        if not self.scan_object_for_data():
            print("Primitive.gather() failed to scan object for data")

        self.gather_atomics()

        self.deduplicate_atomics()

        self.gather_positions()

        # Execution order doesn't matter for the following three functions
        if self.options.gather_weights_data:
            self.gather_weights()

        if self.options.gather_morph_data:
            self.gather_morphs()

        self.gather_triangles()
    
    @timer
    def scan_object_for_data(self):
        # Check for UV data
        if not self.blender_mesh.uv_layers.active:
            raise UVNotFoundException("No active UV data found on mesh")
            return False
        
        self.uv_layer = self.blender_mesh.uv_layers.active

        self.second_uv_layer = None
        if self.options.secondary_uv_layer_index != -1:
            if self.options.secondary_uv_layer_index < len(self.blender_mesh.uv_layers):
                self.second_uv_layer = self.blender_mesh.uv_layers[self.options.secondary_uv_layer_index]
                if self.second_uv_layer == self.uv_layer:
                    print("Primitive.scan_object_for_data() Secondary UV layer is the same as primary UV layer!")
            else:
                raise UVIndexException("Primitive.scan_object_for_data() secondary_uv_layer_index out of range")
                self.secondary_uv_layer = None
                self.secondary_uv_layer_index = None

        if self.blender_mesh.color_attributes.render_color_index == -1:
            print("No color data found on mesh")
            self.gather_color_data = False
        else:
            self.color_data_source_index = self.blender_mesh.color_attributes.render_color_index
            self.color_domain = self.blender_mesh.color_attributes[self.color_data_source_index].domain

        self.armature:bpy.types.Object = None

        if self.options.gather_weights_data:
            if not self.blender_object.vertex_groups:
                print("No vertex groups found on object")
                self.options.gather_weights_data = False

            armatures = [m.object for m in self.blender_object.modifiers if m.type == 'ARMATURE' and m.object is not None]

            if not armatures:
                print("No armature modifier found on object")
                self.options.gather_weights_data = False
                self.armature = None
            elif len(armatures) > 1:
                print("Multiple armature modifiers found on object")
                self.options.gather_weights_data = False
                self.armature = armatures[0]
            else:
                self.armature = armatures[0]

        if self.options.gather_morph_data:
            if self.blender_mesh.shape_keys:
                for key_block in self.blender_mesh.shape_keys.key_blocks:
                    if key_block != key_block.relative_key and not key_block.mute:
                        self.key_blocks.append(key_block)
                if not self.key_blocks:
                    print("No exportable shape keys found on mesh")
                    self.options.gather_morph_data = False
            else:
                print("No shape keys found on mesh")
                self.options.gather_morph_data = False

        if self.options.vertex_group_merge_target != '' and self.options.vertex_group_merge_source:
            if not any([vg.name in self.blender_object.vertex_groups for vg in self.options.vertex_group_merge_source]):
                print("All source vertex groups not found on object")
                self.options.vertex_group_merge_source = []
                self.options.vertex_group_merge_target = ''
            elif self.options.vertex_group_merge_target not in self.blender_object.vertex_groups:
                print("Target vertex group not found on object")
                self.options.vertex_group_merge_source = []
                self.options.vertex_group_merge_target = ''
            else:
                source_indices = [self.blender_object.vertex_groups.find(vg_name) for vg_name in self.options.vertex_group_merge_source]
                source_indices = np.array([i for i in source_indices if i != -1])
                target_index = self.blender_object.vertex_groups.find(self.options.vertex_group_merge_target)
                self.vertex_group_indices_mapping = np.array(range(len(self.blender_object.vertex_groups)))
                self.vertex_group_indices_mapping[source_indices] = target_index                           

        self.vertex_group_ignore_indices = set()
        if self.options.vertex_group_ignore:
            ignore_indices = [self.blender_object.vertex_groups.find(vg_name) for vg_name in self.options.vertex_group_ignore]
            self.vertex_group_ignore_indices = set([i for i in ignore_indices if i != -1])

        return True
    
    @timer
    def gather_atomics(self):
        # Gather vertex index data
        self.blender_mesh.loops.foreach_get('vertex_index', self.atomic_vertices['vertex_index'])

        # Gather UV data
        _temp_arr = np.empty(len(self.blender_mesh.loops) * 2, dtype = np.float32)
        self.uv_layer.data.foreach_get('uv', _temp_arr)
        uvs = _temp_arr.reshape(-1, 2).T
        # u, v -> u, 1-v
        uvs[1] = 1 - uvs[1]
        self.atomic_vertices['uv_x'] = uvs[0]
        self.atomic_vertices['uv_y'] = uvs[1]

        # Gather secondary UV data if available
        if self.options.secondary_uv_layer_index != -1 and self.second_uv_layer:
            _temp_arr = np.empty(len(self.blender_mesh.loops) * 2, dtype = np.float32)
            self.second_uv_layer.data.foreach_get('uv', _temp_arr)
            uvs = _temp_arr.reshape(-1, 2).T
            # u, v -> u, 1-v
            uvs[1] = 1 - uvs[1]
            self.atomic_vertices['uv_x_2'] = uvs[0]
            self.atomic_vertices['uv_y_2'] = uvs[1]
        else:
            self.atomic_vertices['uv_x_2'] = np.zeros(len(self.blender_mesh.loops), dtype=np.float32)
            self.atomic_vertices['uv_y_2'] = np.zeros(len(self.blender_mesh.loops), dtype=np.float32)

        # Gather normal data
        self._calculate_normals()
        normals = self.raw_normals.reshape(-1, 3).T
        self.atomic_vertices['normal_x'] = normals[0]
        self.atomic_vertices['normal_y'] = normals[1]
        self.atomic_vertices['normal_z'] = normals[2]

        # Gather tangent data
        # Gather bitangent sign data
        self._calculate_tangents()


        # Gather color data
        if self.gather_color_data and self.color_data_source_index != -1 and self.color_domain:
            if self.color_domain == 'POINT':
                colors = np.empty(len(self.blender_mesh.vertices) * 4, dtype = np.float32)
            elif self.color_domain == 'CORNER':
                colors = np.empty(len(self.blender_mesh.loops) * 4, dtype = np.float32)

            self.blender_mesh.color_attributes[self.color_data_source_index].data.foreach_get('color', colors)
            
            if self.color_domain == 'POINT':
                colors = colors.reshape(-1, 4)
                colors = colors[self.atomic_vertices['vertex_index']].T
            elif self.color_domain == 'CORNER':
                colors = colors.reshape(-1, 4).T

            self.atomic_vertices['color_r'] = colors[0]
            self.atomic_vertices['color_g'] = colors[1]
            self.atomic_vertices['color_b'] = colors[2]
            self.atomic_vertices['color_a'] = colors[3]

    @timer
    def deduplicate_atomics(self, raise_exception = True):
        self.atomic_vertices, self.atomic_to_loop_id, self.loop_id_to_atomic = np.unique(self.atomic_vertices, return_index=True, return_inverse=True)

        print("Final vertices count: " + str(len(self.atomic_vertices)))

        if len(self.atomic_vertices) > self.options.atomic_max_number:
            if raise_exception:
                raise AtomicException("Primitive.deduplicate_atomics() deduplicated atomic vertices exceed atomic_max_number")
            else:
                return False
            
        return True

    @timer
    def gather_positions(self):
        self.raw_positions = np.empty(len(self.blender_mesh.vertices) * 3, dtype=np.float32)
        self.blender_mesh.vertices.foreach_get('co', self.raw_positions)
        self.raw_positions = self.raw_positions.reshape(-1, 3)
        self._post_vertex_transform(self.raw_positions)

        self.raw_morph_positions = []
        self.raw_morph_position_deltas = []
        for key_block in self.key_blocks:
            vs = np.empty(len(self.blender_mesh.vertices) * 3, dtype=np.float32)
            key_block.data.foreach_get('co', vs)
            vs = vs.reshape(len(self.blender_mesh.vertices), 3)

            self._post_vertex_transform(vs)

            self.raw_morph_positions.append(vs)
            self.raw_morph_position_deltas.append(vs - self.raw_positions)

    @timer
    def gather_weights(self):
        vertex_groups = self.blender_object.vertex_groups
        if self.options.prune_empty_vertex_groups:
            vgrp_markers = [[vg.name, -1] for vg in vertex_groups]
        else:
            vgrp_markers = [[vg.name, i] for vg, i in zip(vertex_groups, range(len(vertex_groups)))]
        new_id = 0

        bm = bmesh.new()
        bm.from_mesh(self.blender_mesh)
        bm.verts.layers.deform.verify()
        deform = bm.verts.layers.deform.active
        weight_data = []
        _min_weight = self.options.weight_cutoff_threshold

        if self.options.vertex_group_merge_source and self.options.vertex_group_merge_target != '':
            for v in bm.verts:
                g = v[deform]
                
                vertex_weight_data = []
                for bone_id, weight in g.items():
                    if bone_id in self.vertex_group_ignore_indices:
                        continue
                    bone_id = self.vertex_group_indices_mapping[bone_id]
                    if weight > _min_weight:
                        if vgrp_markers[bone_id][1] == -1:
                            vgrp_markers[bone_id][1] = new_id
                            new_id += 1
                        vertex_weight_data.append([vgrp_markers[bone_id][1], weight])

                # Deduplicate the list by the first element
                for i in range(len(vertex_weight_data)):
                    for j in range(i+1, len(vertex_weight_data)):
                        if vertex_weight_data[i][0] == vertex_weight_data[j][0]:
                            vertex_weight_data[i][1] += vertex_weight_data[j][1]
                            vertex_weight_data[j][1] = 0

                # Remove the elements with 0 weight
                vertex_weight_data = [x for x in vertex_weight_data if x[1] != 0]
                
                if len(vertex_weight_data) > self.options.max_weights_per_vertex:
                    vertex_weight_data = sorted(vertex_weight_data, key=lambda x: x[1], reverse=True)[:self.options.max_weights_per_vertex]
                elif len(vertex_weight_data) == 0:
                    vertex_weight_data.append([0, 0])

                weight_data.append(vertex_weight_data)

        else:
            for v in bm.verts:
                g = v[deform]
                
                vertex_weight_data = []
                for bone_id, weight in g.items():
                    if bone_id in self.vertex_group_ignore_indices:
                        continue
                    if weight > _min_weight:
                        if vgrp_markers[bone_id][1] == -1:
                            vgrp_markers[bone_id][1] = new_id
                            new_id += 1
                        vertex_weight_data.append([vgrp_markers[bone_id][1], weight])
                
                if len(vertex_weight_data) > self.options.max_weights_per_vertex:
                    vertex_weight_data = sorted(vertex_weight_data, key=lambda x: x[1], reverse=True)[:self.options.max_weights_per_vertex]
                elif len(vertex_weight_data) == 0:
                    vertex_weight_data.append([0, 0])

                weight_data.append(vertex_weight_data)

        self.vertex_weights_data["vertex_weights"] = [weight_data[i] for i in self.atomic_vertices['vertex_index']]
        vgrp_markers = sorted(vgrp_markers, key=lambda x: x[1])
        self.vertex_weights_data['vertex_group_names'] = [vg[0] for vg in vgrp_markers if vg[1] != -1]

        bm.free()

        print("Final vertex weights count: " + str(len(self.vertex_weights_data["vertex_weights"])))

    @timer
    def gather_morphs(self):
        self.vertex_morph_data["shapeKeys"] = [key_block.name for key_block in self.key_blocks]
        self.vertex_morph_data["deltaPositions"] = np.array(self.morph_position_deltas)
        self.vertex_morph_data['targetColors'] = np.ones((len(self.key_blocks), len(self.atomic_vertices), 3), dtype=np.float32) * 255
        self.vertex_morph_data["deltaNormals"] = np.array(self.morph_normal_deltas, dtype=np.float32)
        self.vertex_morph_data["deltaTangents"] = np.array(self.morph_tangent_deltas, dtype=np.float32)

    @timer
    def gather_triangles(self):
        self.blender_mesh.calc_loop_triangles()
        self.triangles = np.empty(len(self.blender_mesh.loop_triangles) * 3, dtype=np.uint32)
        self.blender_mesh.loop_triangles.foreach_get('loops', self.triangles)

        # For each loop id in triangles, replace it with the corresponding atomic vertex id
        self.triangles = self.loop_id_to_atomic[self.triangles]

        print("Final triangles count: " + str(len(self.triangles)))

    def _calculate_normals(self):
        '''
            Inspired from glTF 2.0 exporter for Blender
        '''
        key_blocks = self.key_blocks if self.options.gather_morph_data else []
        if key_blocks:
            self.raw_normals = key_blocks[0].relative_key.normals_split_get()
            self.raw_normals = np.array(self.raw_normals, dtype=np.float32)
        else:
            self.raw_normals = np.empty(len(self.blender_mesh.loops) * 3, dtype=np.float32)
            self.blender_mesh.calc_normals_split()
            self.blender_mesh.loops.foreach_get('normal', self.raw_normals)
        
        self.raw_normals = self.raw_normals.reshape(-1, 3)

        self.raw_normals = np.round(self.raw_normals, self.options.normal_tangent_round_precision)

        # Handle degenrated normals
        is_zero = ~self.raw_normals.any(axis=1)
        self.raw_normals[is_zero, 2] = 1

        self._post_normal_transform(self.raw_normals)

        self.raw_morph_normals = []
        self.raw_morph_normal_deltas = []
        if self.options.gather_morph_data:
            for key_block in key_blocks:
                # TODO: look for custom morph normal attributes first!

                raw_morph_normals = np.array(key_block.normals_split_get(), dtype=np.float32)
                raw_morph_normals = raw_morph_normals.reshape(len(self.blender_mesh.loops), 3)
                raw_morph_normals = np.round(raw_morph_normals, self.options.normal_tangent_round_precision)

                # Handle degenrated normals
                is_zero = ~raw_morph_normals.any(axis=1)
                raw_morph_normals[is_zero, 2] = 1

                self._post_normal_transform(raw_morph_normals)

                self.raw_morph_normals.append(raw_morph_normals)
                
                # For DirectX compression format
                raw_morph_normal_deltas = utils_math.bounded_vector_substraction(self.raw_normals, raw_morph_normals)

                self.raw_morph_normal_deltas.append(raw_morph_normal_deltas)

    def _calculate_tangents(self):
        self.blender_mesh.calc_tangents()
        self.raw_tangents = np.empty(len(self.blender_mesh.loops) * 3, dtype = np.float32)
        self.blender_mesh.loops.foreach_get('tangent', self.raw_tangents)
        self.raw_tangents = self.raw_tangents.reshape(len(self.blender_mesh.loops), 3)

        self.raw_tangents = np.round(self.raw_tangents, self.options.normal_tangent_round_precision)

        self._post_tangent_transform(self.raw_tangents)

        _temp_arr = np.empty(len(self.blender_mesh.loops), dtype = np.int32)
        self.blender_mesh.loops.foreach_get('bitangent_sign', _temp_arr)
        self.raw_bitangent_signs = _temp_arr
        self._post_bitangent_transform()

        # Should be the same as implementation in glTF 2.0 exporter for Blender, but a lot faster (30+ times faster)
        # Calculate morph tangents from morph normals, basis normals and basis tangents (64k verts 77 SK, 160 ms)
        self.raw_morph_tangents = []
        self.raw_morph_tangent_deltas = []
        if self.options.gather_morph_data:
            for raw_morph_normals in self.raw_morph_normals:
                batch_rot = utils_math.batch_rotation_matrices(self.raw_normals, raw_morph_normals)

                raw_morph_tangents = np.einsum('ijk,ik->ij', batch_rot, self.raw_tangents)

                self.raw_morph_tangents.append(raw_morph_tangents)

                # For DirectX compression format
                morph_tangent_deltas = self.raw_bitangent_signs[:, np.newaxis] * utils_math.bounded_vector_substraction(self.raw_tangents, raw_morph_tangents)

                self.raw_morph_tangent_deltas.append(morph_tangent_deltas)

    def _post_vertex_transform(self, vertices:np.ndarray) -> None:
        # Potentially rotations and flips
        if self.armature or self.options.use_global_positions:
            matrix = self.blender_object.matrix_world
            vertices = utils_math.apply_mat_to_all(matrix, vertices)

    def _post_normal_transform(self, vectors:np.ndarray):
        # Potentially rotations and flips
        if self.armature:
            apply_matrix = self.armature.matrix_world.inverted_safe() @ self.blender_object.matrix_world
            apply_matrix = apply_matrix.to_3x3().inverted_safe().transposed()
            normal_transform = self.armature.matrix_world.to_3x3() @ apply_matrix
            vectors = utils_math.apply_mat_to_all(normal_transform, vectors)
        elif self.options.use_global_positions:
            apply_matrix = self.blender_object.matrix_world
            normal_transform = apply_matrix.to_3x3().inverted_safe().transposed()
            vectors = utils_math.apply_mat_to_all(normal_transform, vectors)
        utils_math.NormalizeRows(vectors)

    def _post_tangent_transform(self, vectors:np.ndarray):
        # Potentially rotations and flips
        if self.armature:
            apply_matrix = self.armature.matrix_world.inverted_safe() @ self.blender_object.matrix_world
            tangent_transform = apply_matrix.to_quaternion().to_matrix()
            vectors = utils_math.apply_mat_to_all(tangent_transform, vectors)
        elif self.options.use_global_positions:
            apply_matrix = self.blender_object.matrix_world
            tangent_transform = apply_matrix.to_quaternion().to_matrix()
            vectors = utils_math.apply_mat_to_all(tangent_transform, vectors)
        utils_math.NormalizeRows(vectors)

    def _post_bitangent_transform(self):
        if self.armature:
            apply_matrix = self.armature.matrix_world.inverted_safe() @ self.blender_object.matrix_world
            tangent_transform = apply_matrix.to_quaternion().to_matrix()
            flipped = tangent_transform.determinant() < 0
            if flipped:
                self.raw_bitangent_signs *= -1
        elif self.options.use_global_positions:
            apply_matrix = self.blender_object.matrix_world
            tangent_transform = apply_matrix.to_quaternion().to_matrix()
            flipped = tangent_transform.determinant() < 0
            if flipped:
                self.raw_bitangent_signs *= -1

    @timer
    def to_mesh_json_dict(self):
        data = {
            "max_border": self.options.max_border,
            "num_verts": len(self.atomic_vertices),
            "positions_raw": self.positions.flatten().tolist(),
            "num_indices": len(self.triangles),
            "vertex_indices_raw": self.triangles.tolist(),
            "normals": self.normals.tolist(),
            "uv_coords": self.uv.tolist(),
            "vertex_color": self.colors.tolist() if self.gather_color_data else [],
            "vertex_group_names": self.vertex_weights_data["vertex_group_names"],
            "vertex_weights": self.vertex_weights_data["vertex_weights"],
            "smooth_group": [],
            "tangents": [list(t) + [3 if f < 0 else 0] for t, f in zip(self.tangents.tolist(), self.bitangent_sign.tolist())],
        }
        if self.options.secondary_uv_layer_index:
            data["uv_coords_2"] = self.uv_2.tolist()

        return data

    @timer
    def to_mesh_numpy_dict(self):
        data_matrices = {
            "positions_raw": self.positions,# np.float32
            "vertex_indices_raw": self.triangles, # np.int64
            "normals": self.normals, # np.float32
            "uv_coords": self.uv, # np.float32
            "vertex_color": self.colors if self.gather_color_data else None, # np.float32
            "tangents": self.tangents, # np.float32
            "bitangent_signs": self.bitangent_sign, # np.int32
            "uv_coords_2": self.uv_2 if self.options.secondary_uv_layer_index != -1 else None # np.float32
        }
        data = {
            "max_border": self.options.max_border,
            "num_verts": len(self.atomic_vertices),
            "num_indices": len(self.triangles),
            "vertex_group_names": self.vertex_weights_data["vertex_group_names"],
            "vertex_weights": self.vertex_weights_data["vertex_weights"],
            "ptr_positions": ctypes.addressof(self.positions.ctypes.data_as(ctypes.POINTER(ctypes.c_float)).contents), # np.float32
            "ptr_indices": ctypes.addressof(self.triangles.ctypes.data_as(ctypes.POINTER(ctypes.c_int64)).contents), # np.int64
            "ptr_normals": ctypes.addressof(self.normals.ctypes.data_as(ctypes.POINTER(ctypes.c_float)).contents), # np.float32
            "ptr_uv1": ctypes.addressof(self.uv.ctypes.data_as(ctypes.POINTER(ctypes.c_float)).contents), # np.float32
            "ptr_uv2": ctypes.addressof(self.uv_2.ctypes.data_as(ctypes.POINTER(ctypes.c_float)).contents) if self.options.secondary_uv_layer_index != -1 else 0, # np.float32
            "ptr_color": ctypes.addressof(self.colors.ctypes.data_as(ctypes.POINTER(ctypes.c_float)).contents) if self.gather_color_data else 0, # np.float32
            "ptr_tangents": ctypes.addressof(self.tangents.ctypes.data_as(ctypes.POINTER(ctypes.c_float)).contents), # np.float32
            "ptr_bitangent_signs": ctypes.addressof(self.bitangent_sign.ctypes.data_as(ctypes.POINTER(ctypes.c_int32)).contents), # np.int32
        }

        print("ptr_positions", data["ptr_positions"])

        return data_matrices, data
    
    @timer
    def to_morph_json_dict(self):
        if not self.options.gather_morph_data:
            raise MorphUncalculatedException("Primitive.to_morph_json_dict() called without gather_morph_data option set to True")
            return None
        data = {
            "numVertices": len(self.atomic_vertices),
            "shapeKeys": self.vertex_morph_data["shapeKeys"],
            "deltaPositions": self.vertex_morph_data["deltaPositions"].tolist(),
            "targetColors": self.vertex_morph_data["targetColors"].tolist(),
            "deltaNormals": self.vertex_morph_data["deltaNormals"].tolist(),
            "deltaTangents": self.vertex_morph_data["deltaTangents"].tolist()
        }
        return data
    
    @timer
    def to_morph_numpy_dict(self):
        if not self.options.gather_morph_data:
            raise MorphUncalculatedException("Primitive.to_morph_numpy_dict() called without gather_morph_data option set to True")
            return None
        data = {
            "numVertices": len(self.atomic_vertices),
            **self.vertex_morph_data
        }
        return data

if __name__ == "__main__":
    import time
    
    start = time.time()
    obj = bpy.context.active_object
    primitive = Primitive(obj)
    primitive.gather()
    print("Time total: ", time.time() - start)