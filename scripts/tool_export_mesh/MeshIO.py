import bpy
import os
import bmesh
import json
from collections import defaultdict
import mathutils
import numpy as np
from mathutils import Color

import utils_blender
import utils_common as utils
import utils_math
import MeshConverter

import utils_primitive

import time

def MeshToJson(obj, options, bone_list_filter = None, prune_empty_vertex_groups = False, head_object_mode = 'None', ref_objects = []):
	start_time = time.time()
	
	if not (obj and obj.type == 'MESH'):
		return {'CANCELLED'}, "Selected object is not a mesh.", None, None
	
	p_options = utils_primitive.Primitive.Options()
	p_options.gather_morph_data = False
	p_options.gather_weights_data = options.WEIGHTS
	p_options.use_global_positions = options.use_world_origin
	p_options.max_border = options.max_border
	
	p_options.prune_empty_vertex_groups = prune_empty_vertex_groups

	# Duplicate the object and triangulate the mesh
	with utils_blender.get_obj_proxy(obj, bmesh_triangulation=True) as new_obj:
		
		if obj.data.has_custom_normals:
			obj.data.calc_normals_split()
			loop_vertices = np.zeros(len(obj.data.loops), dtype=np.int32)
			obj.data.loops.foreach_get('vertex_index', loop_vertices)
			corner_normals = np.zeros(len(obj.data.loops) * 3, dtype=np.float32)
			obj.data.corner_normals.foreach_get('vector', corner_normals)
			corner_normals = corner_normals.reshape(-1, 3)
			vertex_normals = np.zeros((len(obj.data.vertices), 3))
			np.add.at(vertex_normals, loop_vertices, corner_normals.reshape(-1, 3))
			new_obj.data.normals_split_custom_set_from_vertices(vertex_normals.tolist())

		rtn, reason = utils_primitive.CheckForPrimitive(new_obj, gather_tangents=False)
		if not rtn:
			return {'CANCELLED'},  f"Object {obj.name} is not a valid object. Reason: {reason}"
		
		if options.use_secondary_uv:
			uv_layer = obj.data.uv_layers.active
			for _uv_layer in obj.data.uv_layers:
				if _uv_layer != uv_layer:
					p_options.secondary_uv_layer_index = obj.data.uv_layers.find(_uv_layer.name)
					break

		if head_object_mode == 'Base':
			facebone_vg_names = [vg.name for vg in obj.vertex_groups if vg.name.startswith("faceBone_")]
			p_options.vertex_group_merge_source = facebone_vg_names
			p_options.vertex_group_merge_target = "C_Head"

		if bone_list_filter is not None:
			for vg in obj.vertex_groups:
				if vg.name not in bone_list_filter:
					p_options.vertex_group_ignore.append(vg.name)

		primitive = utils_primitive.Primitive(new_obj, p_options)

		if len(ref_objects) >= 1:
			print("Snapping on export mesh was enabled. Snapping the data...")
			ref_primitives = []

			for ref_obj in ref_objects:
				rtn, reason = utils_primitive.CheckForPrimitive(ref_obj, gather_tangents=False)
				
				if not rtn:
					continue

				sel_p_options = utils_primitive.Primitive.Options()
				sel_p_options.gather_morph_data = False
				sel_p_options.gather_tangents = False
				sel_p_options.use_global_positions = options.use_world_origin

				sel_primitive = utils_primitive.Primitive(ref_obj, sel_p_options)
				sel_primitive.gather()
				ref_primitives.append(sel_primitive)

		try:
			primitive.gather()
		except utils_primitive.UVNotFoundException as e:
			return {'CANCELLED'}, "Your mesh has no active UV map.", None, None
		except utils_primitive.AtomicException as e:
			return {'CANCELLED'}, "Your mesh has too many vertices or sharp edges or uv islands. Try to reduce them.", None, None
		except Exception as e:
			return {'CANCELLED'}, f"An error occurred: {e}", None, None

		if len(ref_objects) >= 1:
			for ref_primitive in ref_primitives:

				utils_primitive.CopyNormalsAtSeam(
					primitive,
					ref_primitive,
					copy_range=options.snapping_range,
					lerp_coeff=options.snap_lerp_coeff
				)
		
		try:
			matrices, data = primitive.to_mesh_numpy_dict()
		except Exception as e:
			return {'CANCELLED'}, f"An error occurred on at converting to numpy dict: {e}", None, None

		print(f"MeshToJson took {time.time() - start_time} seconds")
		return {'FINISHED'}, "", data, matrices

def ExportMesh(options, context, filepath: str, operator, bone_list_filter = None, prune_empty_vertex_groups = False, head_object_mode = 'None', ref_objects = []):
	export_mesh_file_path = filepath
	export_mesh_folder_path = os.path.dirname(export_mesh_file_path)
	
	active_object = utils_blender.GetActiveObject()
	active_object_name = active_object.name

	if options.export_sf_mesh_hash_result:
		hash_folder, hash_name = utils.hash_string(active_object_name)
		object_folder_name = utils.sanitize_filename(active_object_name)
		result_file_folder = os.path.join(os.path.dirname(export_mesh_file_path), object_folder_name, hash_folder)
		os.makedirs(result_file_folder, exist_ok = True)
		result_file_path = os.path.join(result_file_folder, hash_name + ".mesh")
	else:
		result_file_path = export_mesh_file_path
	
	time_start = time.time()

	rtn, message, data, matrices = MeshToJson(active_object, options, bone_list_filter, prune_empty_vertex_groups, head_object_mode, ref_objects=ref_objects)

	time_end = time.time()

	if rtn != {'FINISHED'}:
		operator.report({'ERROR'}, message)
		return rtn, 0, 0, None

	#json_data = json.dumps(data)
	
	returncode = MeshConverter.ExportMeshFromNumpy({**data, **matrices}, result_file_path)

	time_end1 = time.time()

	if returncode:
		operator.report({'INFO'}, f"Starfield .mesh exported successfully. Gather:{time_end - time_start} + Dll:{time_end1 - time_end}")

		if options.export_sf_mesh_open_folder == True:
			utils_blender.open_folder(bpy.path.abspath(export_mesh_folder_path))

		return {'FINISHED'}, data['num_verts'], data['num_indices'], data['vertex_group_names']
		
	else:
		operator.report({'INFO'}, f"Execution failed with error message: \"{returncode.what()}\". Contact the author for assistance.")
		return {'CANCELLED'}, 0,0, None

def ImportMesh(file_path, options, context, operator, mesh_name_override = None):
	import_path = file_path

	rtn = MeshConverter.ImportMeshAsJson(import_path)
	if rtn == "":
		returncode = -1 
		operator.report({'INFO'}, f"Execution failed with return code {returncode}. Contact the author for assistance.")
		return {'CANCELLED'}
	else:
		returncode = 0
		operator.report({'INFO'}, "Starfield .mesh imported successfully")

	data = json.loads(rtn)

	return MeshFromJson(data, options, context, operator, mesh_name_override)

@utils.timer
def ImportMesh_Alt(file_path, options, context, operator, mesh_name_override = None):
	import_path = file_path

	dict = MeshConverter.ImportMeshAsNumpy(import_path)

	name = "ImportedMesh" if mesh_name_override == None else mesh_name_override

	obj = bpy.data.objects.new(name, bpy.data.meshes.new(name))
	mesh:bpy.types.Mesh = obj.data
	bpy.context.collection.objects.link(obj)

	# Add the vertices
	mesh.from_pydata(dict['positions_raw'], [], dict['vertex_indices_raw'])

	vertex_indices = np.empty(len(mesh.loops), dtype=np.int32)
	mesh.loops.foreach_get('vertex_index', vertex_indices)

	# Set the normals
	vert_normals = dict['normals']
	# Normalize the normals
	vert_normals = vert_normals / np.linalg.norm(vert_normals, axis=1)[:, np.newaxis]
	mesh.normals_split_custom_set_from_vertices(vert_normals)

	# Set the UVs
	uv_layer = mesh.uv_layers.new(name="UVMap")
	uv_layer.data.foreach_set("uv", dict['uv_coords'][vertex_indices].ravel())

	if not np.isclose(dict['uv_coords_2'], 0).any():
		uv_layer2 = mesh.uv_layers.new(name="UVMap2")
		uv_layer2.data.foreach_set("uv", dict['uv_coords_2'][vertex_indices].ravel())

	# Set the vertex colors
	if not np.isclose(dict['vertex_color'], 0).any():
		vertex_colors = mesh.color_attributes.new(name="Col", type='BYTE_COLOR', domain='CORNER')
		vertex_colors.data.foreach_set("color", dict['vertex_color'].ravel())

	if not dict['num_weightsPerVertex'] == 0:
		weights = dict['weights']
		bone_indices = dict['bone_indices']

		num_vertices = dict['num_verts']
		num_bones = np.max(bone_indices) + 1


		result = np.zeros((num_vertices, num_bones))

		np.add.at(result, (np.arange(num_vertices)[:, None], bone_indices), weights)

		for i in range(num_bones):
			vg = obj.vertex_groups.new(name=f"bone{i}")
			v_ids = result[:, i].nonzero()[0]
			ws = result[:, i][v_ids]
			[vg.add([int(v_id)], float(w), 'ADD') for v_id, w in zip(v_ids, ws)]

	utils_blender.SetActiveObject(obj)

	return {'FINISHED'}

def MeshFromJson(json_data, options, context, operator, mesh_name_override = None):
	data = json_data

	temp_path = utils_blender.TempFolderPath()
	
	obj_content = data['obj_content']
	with open(os.path.join(temp_path, "mesh_data_import.obj"), 'w') as f:
		f.write(obj_content)

	bpy.ops.wm.obj_import(
		filepath=os.path.join(temp_path, "mesh_data_import.obj"),
		forward_axis='Y',
		up_axis ='Z',  # Customize other import options here
	)

	obj = bpy.context.selected_objects[0]

	utils_blender.AverageCustomNormals(obj)

	if not obj:
		operator.report({'WARNING'}, f"Unknown error. Contact the author for assistance.")
		return {'CANCELLED'}

	mesh:bpy.types.Mesh = obj.data
	if mesh_name_override != None:
		mesh.name = mesh_name_override
	if not mesh.vertex_colors:
		mesh.vertex_colors.new()

	bm = bmesh.new()
	bm.from_mesh(mesh)

	col = obj.data.vertex_colors.active

	if "uv_coords2" in data:
		if len(data["uv_coords2"]) != len(mesh.vertices):
			operator.report({'WARNING'}, f"UV2 data mismatched. Contact the author for assistance.")
			return {'CANCELLED'}
		uv_layer2 = obj.data.uv_layers.new(name="UV2")
		for f in bm.faces:
			for vert_idx, loop_idx in zip(f.verts, f.loops):
				uv_coords = data["uv_coords2"][vert_idx.index]
				uv_layer2.data[loop_idx.index].uv = (uv_coords[0],1 - uv_coords[1])

	if len(data["vertex_weights"]) > 0:
		if len(bm.verts) != len(data["vertex_weights"]):
			operator.report({'WARNING'}, f"Weight data mismatched. Contact the author for assistance.")
			return {'CANCELLED'}
		
		num_bones_per_vert = len(data["vertex_weights"][0])
		num_bones = -1
		for v in bm.verts:
			for i in range(num_bones_per_vert):
				if data["vertex_weights"][v.index][i][0] > num_bones:
					num_bones = data["vertex_weights"][v.index][i][0]
		
		num_bones += 1
		bones = []
		for i in range(num_bones):
			bones.append(obj.vertex_groups.new(name='bone' + str(i)))

		for v in bm.verts:
			for i in range(num_bones_per_vert):
				cur_boneweight = data["vertex_weights"][v.index][i]
				
				if cur_boneweight[1] != 0:
					bones[int(cur_boneweight[0])].add([v.index], cur_boneweight[1],'ADD')
			#print(v.index, v.co, data["vertex_weights"][v.index])

	vertex_map = defaultdict(list)
	for poly in obj.data.polygons:
		for v_ix, l_ix in zip(poly.vertices, poly.loop_indices):
			vertex_map[v_ix].append(l_ix)

	if len(data["vertex_color"]) > 0:
		if len(bm.verts) != len(data["vertex_color"]):
			operator.report({'WARNING'}, f"Vertex data mismatched. Contact the author for assistance.")
			return {'CANCELLED'}
		for v_ix, l_ixs in vertex_map.items():
			for l_ix in l_ixs:
				col.data[l_ix].color = (data["vertex_color"][v_ix][0],data["vertex_color"][v_ix][1],data["vertex_color"][v_ix][2],data["vertex_color"][v_ix][3])
	
		
	if options.meshlets_debug and len(data['meshlets']) > 0:
		num_meshlets = len(data['meshlets'])

		for i in range(num_meshlets):
			material_name = f"Meshlet_{i}"
			material = bpy.data.materials.new(name=material_name)
			_h = (0.1 + 0.3*i) % 1.0
			_s = 1.0
			_v = 0.8
			_c = Color()
			_c.hsv = _h, _s, _v
			material.diffuse_color = _c[:] + (1.0,)
			mesh.materials.append(material)

		curr_tri = 0
		for i in range(num_meshlets):
			tri_counts = data['meshlets'][i][2]
			#tri_offset = data['meshlets'][i][3]
			for j in range(curr_tri, curr_tri + tri_counts):
				mesh.polygons[j].material_index = i
			curr_tri += tri_counts

		if options.culldata_debug:
			
			CULLDATA_VERSION = 2

			for i in range(num_meshlets):
				if CULLDATA_VERSION == 1:
					center = data['culldata'][i][:3]
					radius = data['culldata'][i][3]
					normal_and_marker = data['culldata'][i][4]
					normal = [normal_and_marker & 0xff, (normal_and_marker >> 8) & 0xff, (normal_and_marker >> 16) & 0xff]
					marker = (normal_and_marker >> 24) & 0xff
					apex = data['culldata'][i][5]

					bpy.ops.mesh.primitive_uv_sphere_add(radius=radius, location=center)
					bpy.context.object.display_type = 'BOUNDS'
					bpy.context.object.display_bounds_type = 'SPHERE'
					bpy.context.object.show_bounds = True
					bpy.context.object.name = f"Meshlet_{i}"

				
					normal_float = [(_i/255.0)*2 - 1 for _i in normal]
					is_degenerate = (marker == 255)
					angle = np.arccos(-marker/255.0) - (3.1415926 / 2)
					depth = radius / np.tan(angle)
					cone_center = [_i + _j * depth * 0.5 for _i,_j in zip(center, normal_float)]

					if not is_degenerate:
						bpy.ops.mesh.primitive_cone_add(vertices=32, radius1 = radius, depth = depth, location=cone_center)
						# Calculate the rotation matrix to align the up direction with the normal vector
						up_vector = mathutils.Vector((0, 0, 1)) 
						rotation_matrix = up_vector.rotation_difference(mathutils.Vector(normal_float)).to_matrix()

						# Apply the rotation to the cone
						bpy.context.object.rotation_euler = rotation_matrix.to_euler()

						bpy.context.object.display_type = 'BOUNDS'
						bpy.context.object.display_bounds_type = 'CONE'
						bpy.context.object.show_bounds = True
						bpy.context.object.name = f"CullCone_{i}"
						pass
					else:
						pass
				elif CULLDATA_VERSION == 2:
					min_max_bounds = data['culldata'][i][:6]

					box = utils_blender.BoxFromCenterExpand(f"CullBBox_{i}", min_max_bounds[:3], min_max_bounds[3:])
					box.show_bounds = True
					box.display_type = 'BOUNDS'
					box.display_bounds_type = 'BOX'
					box.show_wire = True

	if options.tangents_debug and len(data['tangents']) > 0:
		num_tangents = len(data['tangents'])
		if num_tangents != len(bm.verts):
			operator.report({'WARNING'}, f"Tangent data mismatched.")
		else:
			mesh = bpy.data.meshes.new("Tangents")  # add a new mesh
			obj = bpy.data.objects.new("Tangents", mesh)  # add a new object using the mesh

			bpy.context.collection.objects.link(obj)
			scale = 0.02
			verts = [v.co for v in bm.verts] + [(t[0] * scale + v.co[0], t[1] * scale + v.co[1], t[2] * scale + v.co[2]) for t, v in zip(data['tangents'], bm.verts)]
			edges = [[i,i + len(bm.verts)] for i in range(len(bm.verts))]
			mesh.from_pydata(verts, edges, [])
			for v_ix, l_ixs in vertex_map.items():
				for l_ix in l_ixs:
					w = data['tangents'][v_ix][3] / 3.0
					col.data[l_ix].color = (w, w, w, w)
	
	bm.free()
	utils_blender.SetActiveObject(obj)
	return {'FINISHED'}
