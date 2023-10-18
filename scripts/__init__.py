import bpy
import os
import subprocess
import shutil
import bmesh
import json
import hashlib
import datetime
from collections import defaultdict
import mathutils
import numpy as np
from mathutils import Color


bl_info = {
    "name": "Starfield Mesh Exporter",
    "version": (0, 5, 0),
    "blender": (3, 5, 0),
    "location": "File > Import-Export",
    "description": "Export .mesh geometry file for starfield.",
    "warning": "",
    "category": "Import-Export",
    }

read_only_marker = '[READONLY]'
mix_normal = False

invert_UV_tile_tangent = False

def sanitize_filename(filename):
    illegal_chars = ['<', '>', ':', '"', '/', '\\', '|', '?', '*']
    replacement_char = '_'  # You can replace illegal characters with another character or remove them

    # Replace illegal characters with the replacement character
    for char in illegal_chars:
        filename = filename.replace(char, replacement_char)

    return filename

def hash_string(input_string):
    # Create a SHA-1 hash object
    sha1 = hashlib.sha1()

    # Update the hash object with the input string encoded as bytes
    sha1.update(input_string.encode('utf-8'))

    # Get the hexadecimal representation of the hash
    hex_digest_input = sha1.hexdigest()

    # Take the first 20 characters of the input string's hexadecimal digest
    hex_result_input = hex_digest_input[:20]

    # Get the current date and time as a string
    current_datetime = datetime.datetime.now().strftime('%Y%m%d%H%M%S%f')

    # Create a SHA-1 hash object for the current date and time
    sha1 = hashlib.sha1()

    # Update the hash object with the current date and time encoded as bytes
    sha1.update(current_datetime.encode('utf-8'))

    # Get the hexadecimal representation of the hash
    hex_digest_datetime = sha1.hexdigest()

    # Take the first 20 characters of the datetime's hexadecimal digest
    hex_result_datetime = hex_digest_datetime[:20]

    # Combine the two hexadecimal results
    return hex_result_datetime, hex_result_input

def hash_string_2(input_string):
    # Create a SHA-1 hash object
    sha1 = hashlib.sha1()

    # Update the hash object with the input string encoded as bytes
    sha1.update(input_string.encode('utf-8'))

    # Get the hexadecimal representation of the hash
    hex_digest_input = sha1.hexdigest()

    # Take the first 20 characters of the input string's hexadecimal digest
    hex_result_input = hex_digest_input[:20]

    # Get the current timestamp as an integer
    current_timestamp = int(datetime.datetime.now().timestamp())

    # Convert the prefix and timestamp to integers
    prefix = int("fffff000000000000000", 16)
    timestamp = current_timestamp

    # Add the two integers together
    result = prefix + timestamp

    # Convert the result back to a 20-character hexadecimal string
    hex_result_datetime = format(result, '020x')

    # Combine the two hexadecimal results
    return hex_result_datetime, hex_result_input


def open_folder(initial_directory):

    # Set the window manager to the current context
    wm = bpy.context.window_manager

    # Call the file browser operator
    bpy.ops.wm.path_open(filepath=initial_directory)
                         
def copy_and_rename_file(source_file, destination_folder, new_file_name):
    # Extract the file name and extension
    file_name, file_extension = os.path.splitext(source_file)

    # Construct the destination path
    destination_path = os.path.join(destination_folder, new_file_name + '.mesh')
    
    shutil.copy2(source_file, destination_path)

def update_path(utils_p):
    utils_path = bpy.path.abspath(utils_p)
    temp_path = os.path.join(utils_path, 'Temp')
    
    return utils_path,temp_path

def delete_folder(path):
    try:
        shutil.rmtree(path)
        print(f"Folder '{path}' and its contents have been successfully deleted.")
    except FileNotFoundError:
        print(f"Folder '{path}' does not exist.")
    except Exception as e:
        print(f"An error occurred while deleting the folder '{path}': {e}")

def flatten(lst):
    result = []
    for item in lst:
        if isinstance(item, list):
            result.extend(flatten(item))
        else:
            result.append(item)
    return result
# Define a list of items with labels
export_items = [
    ("GEO", "Geometry", "Export geometry data (positions and indices)."),
    ("NORM", "Normals", "Export normals data."),
    ("UV", "UV", "Export texture coordinates data."),
    ("VERTCOLOR", "Vertex Color", "Export vertex color data."),
    ("WEIGHTS", "Weights", "Export vertex groups data."),
]
def GramSchmidtOrthogonalize(tangent, normal):
    # Project the tangent vector onto the normal vector
    projection = np.dot(tangent, normal) * normal

    # Subtract the projection from the original tangent to make it orthogonal to the normal
    orthogonal_tangent = tangent - projection

    # Normalize the resulting orthogonal tangent
    normalized_orthogonal_tangent = orthogonal_tangent / np.linalg.norm(orthogonal_tangent)

    return normalized_orthogonal_tangent

def Normalize(vec):
    n = np.linalg.norm(vec)
    if n == 0:
        return vec
    return vec / n

def SetSelectObjects(objs):
    original_selected = bpy.context.selected_objects
    bpy.ops.object.select_all(action='DESELECT')
    for obj in objs:
        obj.select_set(state=True)
    return original_selected

def GetActiveObject():
    return bpy.context.active_object

def SetActiveObject(obj):
    original_active = GetActiveObject()
    #bpy.ops.object.select_all(action='DESELECT')
    obj.select_set(True)
    bpy.context.view_layer.objects.active = obj
    return original_active

def GetSharpGroups(selected_obj):
    sharp_edge_vertices = []
    # Ensure we are in Edit Mode
    if selected_obj.mode != 'EDIT':
        bpy.ops.object.mode_set(mode='EDIT')

    # Deselect all
    bpy.ops.mesh.select_all(action='DESELECT')

    _obj = bpy.context.edit_object
    _me = _obj.data

    _bm = bmesh.from_edit_mesh(_me)
    for e in _bm.edges:
        if not e.smooth:
            e.select = True
    
    bmesh.update_edit_mesh(_me)

    # Switch to Vertex Select Mode
    bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='VERT')

    # Switch back to Object Mode
    bpy.ops.object.mode_set(mode='OBJECT')

    # Iterate through selected vertices and add their indices to the list
    for vertex in selected_obj.data.vertices:
        if vertex.select:
            sharp_edge_vertices.append(vertex.index)

    return sharp_edge_vertices

def PreprocessAndProxy(old_obj, use_world_origin, convert_to_mesh = True):
    if old_obj and old_obj.type == 'MESH':
        
        if old_obj.data.shape_keys != None:
            shape_key = old_obj.data.shape_keys.key_blocks["Basis"]
            if shape_key != None:
                keys = old_obj.data.shape_keys.key_blocks.keys()
                shape_key_index = keys.index(shape_key.name)
                old_obj.active_shape_key_index = shape_key_index
        
        new_obj = old_obj.copy()
        new_obj.data = old_obj.data.copy()
        new_obj.animation_data_clear()
        bpy.context.collection.objects.link(new_obj)
        bpy.context.view_layer.objects.active = new_obj

        bpy.ops.object.select_all(action='DESELECT')
        new_obj.select_set(True)
        if convert_to_mesh:
            bpy.ops.object.convert(target='MESH')

        # Mesh clean up
        if new_obj.mode != 'EDIT':
            bpy.ops.object.mode_set(mode='EDIT')

        # Select all
        bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='VERT')
        bpy.ops.mesh.select_all(action='SELECT')
        bpy.ops.mesh.delete_loose()
        bpy.ops.mesh.select_all(action='DESELECT')

        bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='EDGE')
        
        # Select all edges
        bpy.ops.mesh.select_all(action='SELECT')
        
        # Switch to Edge Select mode in UV Editor
        bpy.ops.uv.select_all(action='SELECT')
        
        bpy.ops.uv.seams_from_islands()
        
        bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='EDGE')
        bpy.ops.mesh.select_all(action='DESELECT')
        bpy.ops.mesh.select_non_manifold(extend=False, use_boundary=True, use_multi_face = False,use_non_contiguous = False, use_verts = False)

        __obj = bpy.context.edit_object
        __me = __obj.data

        __bm = bmesh.from_edit_mesh(__me)
        for __e in __bm.edges:
            if __e.select:
                __e.smooth = False

        bmesh.update_edit_mesh(__me)

        bpy.ops.mesh.edge_split(type='EDGE')
        
        bpy.ops.mesh.select_all(action='DESELECT')
        
        bpy.ops.object.mode_set(mode='OBJECT')
        
        if use_world_origin:
            bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)
        
        selected_obj = new_obj
        
        # Create a BMesh from the selected object
        bm = bmesh.new()
        bm.from_mesh(selected_obj.data)
        
        seams = [e for e in bm.edges if e.seam or not e.smooth]
        # split on seams
        bmesh.ops.split_edges(bm, edges=seams)
        
        # Triangulate the mesh
        bmesh.ops.triangulate(bm, faces=bm.faces)

        bm.to_mesh(selected_obj.data)
        bm.free()
        
        bpy.ops.object.select_all(action='DESELECT')
        selected_obj.select_set(True)

        bpy.ops.object.shade_smooth(use_auto_smooth=True)

        modifier = selected_obj.modifiers.new(name = selected_obj.name, type='DATA_TRANSFER')
        modifier.object = old_obj
        modifier.use_loop_data = True
        modifier.data_types_loops = {'CUSTOM_NORMAL'}
        modifier.use_max_distance = True
        modifier.max_distance = 0.01
        modifier.loop_mapping = "TOPOLOGY"

        bpy.ops.object.modifier_apply(modifier=modifier.name)

        return old_obj, selected_obj
    else:
        print("No valid object is selected.")
        return old_obj, None

def IsReadOnly(obj):
    return read_only_marker in obj.name

def IsMesh(obj):
    return obj.type == 'MESH'

def GetSelectedObjs(exclude_active):
    l = []
    for obj in bpy.context.selected_objects:
        if not exclude_active or obj != bpy.context.active_object:
            l.append(obj)
    return l

def SmoothPerimeterNormal(active_obj, selected_obj_list, apply_as_mesh = False, base_obj = None):
    if active_obj in selected_obj_list:
        selected_obj_list.remove(active_obj)
    
    if apply_as_mesh:
        original_active = SetActiveObject(active_obj)

    if base_obj:
        modifier = active_obj.modifiers.new(name = base_obj.name, type='DATA_TRANSFER')
        modifier.object = base_obj
        modifier.use_loop_data = True
        modifier.data_types_loops = {'CUSTOM_NORMAL'}
        modifier.use_max_distance = True
        modifier.max_distance = 0.01
        modifier.loop_mapping = "TOPOLOGY"
        if apply_as_mesh:
            bpy.ops.object.modifier_apply(modifier=modifier.name)

    for target_obj in selected_obj_list:
        if target_obj is not None:
            modifier = active_obj.modifiers.new(name = target_obj.name, type='DATA_TRANSFER')
            modifier.object = target_obj
            modifier.use_loop_data = True
            modifier.data_types_loops = {'CUSTOM_NORMAL'}
            modifier.use_max_distance = True
            modifier.max_distance = 0.01
            if mix_normal:
                modifier.mix_mode = 'ADD'
            if apply_as_mesh:
                bpy.ops.object.modifier_apply(modifier=modifier.name)

    if apply_as_mesh:
        SetActiveObject(original_active)

def GetNormalTangents(mesh, with_tangent = True):
    verts_count = len(mesh.vertices)
    Normals = [np.array([0,0,0]) for i in range(verts_count)]
    if with_tangent:
        Tangents = [np.array([0,0,0]) for i in range(verts_count)]

    mesh.calc_normals_split()
    mesh.calc_tangents()

    for face in mesh.polygons:
        for vert_idx, loop_idx in zip(face.vertices, face.loop_indices):
            Normals[vert_idx] = Normals[vert_idx] + np.array(mesh.loops[loop_idx].normal)
            if with_tangent:
                Tangents[vert_idx] = Tangents[vert_idx] + np.array(mesh.loops[loop_idx].tangent)

    _Normals = [Normalize(n) for n in Normals]

    if with_tangent:
        _Tangents = [GramSchmidtOrthogonalize(t, np.array(n)) for t,n in zip(Tangents, _Normals)]
    else:
        _Tangents = None

    return _Normals, _Tangents

def VisualizeVectors(obj_mesh, offsets, vectors, name = "Vectors"):
    bm = bmesh.new()
    bm.from_mesh(obj_mesh)
    num_tangents = len(vectors)
    if num_tangents != len(bm.verts) or len(offsets) != len(bm.verts):
        print("Cannot create vector vis due to vertex number mismatch.")
        pass
    else:
        mesh = bpy.data.meshes.new(name)  # add a new mesh
        obj = bpy.data.objects.new(name, mesh)  # add a new object using the mesh

        bpy.context.collection.objects.link(obj)
        scale = 0.02
        origins = [(offset[0] + v.co[0], offset[1] + v.co[1], offset[2] + v.co[2]) for v, offset in zip(bm.verts, offsets)]
        verts = origins + [(t[0] * scale + o[0], t[1] * scale + o[1], t[2] * scale + o[2]) for t, o in zip(vectors, origins)]
        edges = [[i,i + len(bm.verts)] for i in range(len(bm.verts))]
        mesh.from_pydata(verts, edges, [])

    bm.free()

def ExportMesh(options, context, filepath, operator):
    export_mesh_file_path = filepath
    export_mesh_folder_path = os.path.dirname(export_mesh_file_path)
    utils_path, temp_path = update_path(os.path.dirname(__file__))
    
    # Initialize dictionaries to store data
    data = {
        "max_border": options.max_border,
        "positions": [],
        "positions_raw": [],
        "vertex_indices": [],
        "vertex_indices_raw": [],
        "normals": [],
        "uv_coords": [],
        "vertex_color": [],
        "bone_list":[],
        "vertex_weights": [],
        "smooth_group": [],
        "tangents": [],
    }

    if not os.path.isdir(temp_path):
        os.makedirs(temp_path)

    old_obj = bpy.context.active_object
    if old_obj and old_obj.type == 'MESH':
        active_object_name = bpy.context.active_object.name
    else:
        operator.report({'WARNING'},"Selected object is not a mesh.")
        return {'CANCELLED'}
    
    s_objs = GetSelectedObjs(True)

    old_obj, selected_obj = PreprocessAndProxy(old_obj, options.use_world_origin)
    
    SmoothPerimeterNormal(selected_obj, s_objs)
    bpy.ops.object.convert(target='MESH')

    # Check if the selected object is a mesh
    if selected_obj and selected_obj.type == 'MESH':

        #if options.smooth_edge_normals:
        #    sharp_edge_vertices = GetSharpGroups(selected_obj)

        #    data["smooth_group"] = []

        #    for vertex in selected_obj.data.vertices:
        #        if vertex.index not in sharp_edge_vertices:
        #            data["smooth_group"].append(vertex.index)

        #    if "SMOOTH_GROUP" in selected_obj.vertex_groups:
        #        data["smooth_group"] = []
        #        smooth_group = selected_obj.vertex_groups["SMOOTH_GROUP"]
                
        #        for vertex in selected_obj.data.vertices:
                    # Check if the vertex is in the "SMOOTH_GROUP"
        #            for group_element in vertex.groups:
        #                if group_element.group == smooth_group.index:
        #                    data["smooth_group"].append(vertex.index)

                # Remove the vertex group
        #        selected_obj.vertex_groups.remove(smooth_group)

        #    if "SHARP_GROUP" in selected_obj.vertex_groups:
        #        data["smooth_group"] = []
        #        sharp_group = selected_obj.vertex_groups["SHARP_GROUP"]

        #        for vertex in selected_obj.data.vertices:
        #            is_sharp = False
        #            for group_element in vertex.groups:
        #                if group_element.group == sharp_group.index:
        #                    is_sharp = True
        #                    break
                    
        #            if not is_sharp and vertex.index not in sharp_edge_vertices:
        #                data["smooth_group"].append(vertex.index)

        #        selected_obj.vertex_groups.remove(sharp_group)
            
        bm = bmesh.new()
        bm.from_mesh(selected_obj.data)

        # Extract data from the mesh
        color_layer = bm.loops.layers.color.active
        uv_layer = bm.loops.layers.uv.active
        verts_count = 0
        hanging_verts = []

        if options.GEO:
            positions = [list(vert.co) for vert in selected_obj.data.vertices.values()] 
            data["positions_raw"] = flatten(positions)

        for v in bm.verts:
            verts_count += 1
            
            has_hanging_verts = False
            if len(v.link_loops) == 0:
                hanging_verts.append(v.index)
                has_hanging_verts = True
                
                    
            if has_hanging_verts:
                operator.report({'WARNING'}, "There are floating verts in your model. Some verts don't belong to any faces.")
                bpy.context.view_layer.objects.active = old_obj
                old_obj.select_set(True)
                bpy.data.meshes.remove(selected_obj.data)
                selected_obj = bpy.context.active_object

                # Ensure we are in Edit Mode
                if selected_obj.mode != 'EDIT':
                    bpy.ops.object.mode_set(mode='EDIT')

                # Deselect all
                bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='VERT')
                bpy.ops.mesh.select_all(action='DESELECT')

                t_obj = bpy.context.edit_object
                t_me = t_obj.data

                t_bm = bmesh.from_edit_mesh(t_me)
                for t_v in t_bm.verts:
                    if t_v.index in hanging_verts:
                        t_v.select = True
                
                bmesh.update_edit_mesh(t_me)

                bpy.ops.mesh.select_linked(delimit=set())

                return {'CANCELLED'}

            if options.VERTCOLOR and color_layer:
                loop = v.link_loops[0]
                data["vertex_color"].append([loop[color_layer][0],loop[color_layer][1],loop[color_layer][2],loop[color_layer][3]])

        
        try:
            data["uv_coords"] = [[] for i in range(verts_count)]
            Tangents = [np.array([0,0,0]) for i in range(verts_count)]
            Normals = [np.array([0,0,0]) for i in range(verts_count)]
            flipped_verts = [1 for i in range(verts_count)]
            selected_obj.data.calc_tangents()
            selected_obj.data.calc_normals_split()

            for face in selected_obj.data.polygons:
                for vert_idx, loop_idx in zip(face.vertices, face.loop_indices):
                    uv_coords = selected_obj.data.uv_layers.active.data[loop_idx].uv
                    data["uv_coords"][vert_idx] = [uv_coords[0],1-uv_coords[1]]
                    if uv_coords[1] > 1 and invert_UV_tile_tangent:
                        flipped_verts[vert_idx] = -1
                    Tangents[vert_idx] = Tangents[vert_idx] + np.array(selected_obj.data.loops[loop_idx].tangent)
                    Normals[vert_idx] = Normals[vert_idx] + np.array(selected_obj.data.loops[loop_idx].normal)

            data["normals"] = [list(Normalize(n)) for n in Normals]
            data["tangents"] = [list(f * GramSchmidtOrthogonalize(t, np.array(n))) for t, n, f in zip(Tangents, data["normals"], flipped_verts)]

            for _l in data["uv_coords"]:
                if len(_l) == 0:
                    operator.report({'WARNING'}, f"UV map is invalid.")
                    print(data["uv_coords"], verts_count)
                    return {'CANCELLED'}
                    
            
            if options.GEO:
                for f in bm.faces:
                    #data["vertex_indices"].append([v.index for v in f.verts])
                    data["vertex_indices_raw"].extend([v.index for v in f.verts])

            # Extract vertex weights and bones
            if options.WEIGHTS:
                vertex_groups = selected_obj.vertex_groups
                vgrp_names = [vg.name for vg in vertex_groups]
                data["bone_list"] = vgrp_names
                
                bm.verts.layers.deform.verify()

                deform = bm.verts.layers.deform.active
                
                for v in bm.verts:
                    g = v[deform]
                    
                    if len(g.items()) > 0 :
                        data["vertex_weights"].append(g.items())
                    elif len(data["bone_list"])>0:
                        data["vertex_weights"].append([[0, 0]])


        except IndexError:
            operator.report({'WARNING'}, "The mesh may have loose vertices, try to Clean Up the mesh or contact the author.")
            return {'CANCELLED'}

        # Save the data to a JSON file
        output_file = os.path.join(temp_path, "mesh_data.json")
        with open(output_file, 'w') as json_file:
            json.dump(data, json_file, indent=4)
        print(f"Data saved to {output_file}")

        # Cleanup
        bm.to_mesh(selected_obj.data)
        bm.free()
    else:
        operator.report({'WARNING'},"Selected object is not a mesh.")
        return {'CANCELLED'}

    if selected_obj:
        bpy.context.view_layer.objects.active = old_obj
        old_obj.select_set(True)
        bpy.data.meshes.remove(selected_obj.data)
        try:
            if options.export_sf_mesh_hash_result:
                hash_folder, hash_name = hash_string(active_object_name)
                object_folder_name = sanitize_filename(active_object_name)
                result_file_folder = os.path.join(os.path.dirname(export_mesh_file_path), object_folder_name, hash_folder)
                os.makedirs(result_file_folder)
                result_file_path = os.path.join(result_file_folder, hash_name + ".mesh")
            else:
                result_file_path = export_mesh_file_path
            
            log_file_path = os.path.join(utils_path, "console.log")
            with open(log_file_path, "w") as log_file:
                print("REPORT:",result_file_path)
                result = subprocess.run([os.path.join(utils_path, 'MeshConverter.exe'),
                                '-g',
                                os.path.join(temp_path, "mesh_data.json"),
                                result_file_path,
                                str(options.mesh_scale),
                                str(0),
                                str(int(options.normalize_weights)),
                                str(0),
                                ],stdout=log_file)


            if result.returncode == 0:
                operator.report({'INFO'}, "Starfield .mesh exported successfully")

                if options.export_sf_mesh_open_folder == True:
                    open_folder(bpy.path.abspath(export_mesh_folder_path))

                return {'FINISHED'}
                
            else:
                operator.report({'INFO'}, f"Execution failed with return code {result.returncode}. Contact the author for assistance.")
                return {'CANCELLED'}
            
        except subprocess.CalledProcessError as e:
            operator.report({'WARNING'}, f"Execution failed with return code {e.returncode}: {e.stderr}")
            return {'CANCELLED'}
        except FileNotFoundError:
            operator.report({'WARNING'}, "Executable not found.")
            return {'CANCELLED'}

    return {'CANCELLED'}

def ImportMesh(options, context, operator):
    import_path = options.filepath
    utils_path, temp_path = update_path(os.path.dirname(__file__))

    log_file_path = os.path.join(utils_path, "console_import.log")
    with open(log_file_path, "w") as log_file:
        result = subprocess.run([os.path.join(utils_path, 'MeshConverter.exe'),
                            '-b',
                            import_path,
                            os.path.join(temp_path, "mesh_data_import"),
                            ],stdout=log_file)


    if result.returncode == 0:
        operator.report({'INFO'}, "Starfield .mesh exported successfully")
        
        bpy.ops.wm.obj_import(
            filepath=os.path.join(temp_path, "mesh_data_import.obj"),
            forward_axis='Y',
            up_axis ='Z',  # Customize other import options here
        )

        obj = bpy.context.selected_objects[0]
        if obj:
            mesh = obj.data
            if not mesh.vertex_colors:
                mesh.vertex_colors.new()

            bm = bmesh.new()
            bm.from_mesh(mesh)

            col = obj.data.vertex_colors.active

            with open(os.path.join(temp_path, "mesh_data_import.json"), 'r') as json_file:
                data = json.load(json_file)

                if len(data["vertex_weights"]) > 0:
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

                    if len(bm.verts) != len(data["vertex_weights"]):
                        operator.report({'WARNING'}, f"Weight data mismatched. Contact the author for assistance.")
                        return {'CANCELLED'}
                    
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
                    if len(bm.verts) != len(data["vertex_weights"]):
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


                    for i in range(num_meshlets):
                        tri_counts = data['meshlets'][i][2]
                        tri_offset = data['meshlets'][i][3]
                        for j in range(tri_offset, tri_offset + tri_counts):
                            mesh.polygons[j].material_index = i

                    if options.culldata_debug:
                        
                        for i in range(num_meshlets):
                            center = data['culldata'][i][:3]
                            radius = data['culldata'][i][3]
                            normal = data['culldata'][i][4:7]
                            marker = data['culldata'][i][7]
                            apex = data['culldata'][i][8]

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

                if options.import_as_read_only:
                    obj.name = read_only_marker + obj.name

            bm.free()
            return {'FINISHED'}
        else:
            operator.report({'WARNING'}, f"Unknown error. Contact the author for assistance.")
            return {'CANCELLED'}

    else:
        operator.report({'INFO'}, f"Execution failed with return code {result.returncode}. Contact the author for assistance.")
        return {'CANCELLED'}

def ImportMorph(options, context, operator):
    #import_path = os.path.join(os.path.dirname(options.filepath),'morph.dat')
    import_path = options.filepath
    utils_path, temp_path = update_path(os.path.dirname(__file__))
    data_path = os.path.join(temp_path, "morph_data_import.json")

    log_file_path = os.path.join(utils_path, "console_import_morph.log")
    with open(log_file_path, "w") as log_file:
        result = subprocess.run([os.path.join(utils_path, 'MeshConverter.exe'),
                            '-bm',
                            import_path,
                            data_path,
                            ],stdout=log_file)
        
    if result.returncode != 0:
        operator.report({'INFO'}, f"Execution failed with return code {result.returncode}. Contact the author for assistance.")
        return {"CANCELLED"}
    

    with open(data_path, 'r') as json_file:
        if json_file == None:
            operator.report({'WARNING'}, f"Unable to open json file.")
            return {"CANCELLED"}
        
        jsondata = json.load(json_file)

        vert_count = jsondata["numVertices"]
        shape_keys = list(jsondata["shapeKeys"])
        morph_data = jsondata["morphData"]

        target_obj = bpy.context.active_object


        if target_obj == None or len(target_obj.data.vertices) != vert_count:
            target_obj = None
            for _obj in bpy.data.objects:
                if _obj.type == 'MESH' and read_only_marker not in _obj.name and len(_obj.data.vertices) == vert_count:
                    target_obj = _obj
                    break
        
        if target_obj == None:
            operator.report({'WARNING'}, f"No matching mesh found for the morph.")
            return {"CANCELLED"}
        else:
            if read_only_marker in target_obj.name and target_obj.data.shape_keys != None and len(target_obj.data.shape_keys.key_blocks) != 0:
                operator.report({'WARNING'}, f"Target mesh is Read Only! Remove {read_only_marker} in the name before continue.")
                return {"CANCELLED"}
        
        verts = target_obj.data.vertices

        target_obj.shape_key_clear()
        sk_basis = target_obj.shape_key_add(name = 'Basis', from_mix=False)
        sk_basis.interpolation = 'KEY_LINEAR'
        target_obj.data.shape_keys.use_relative = True

        if options.debug_delta_normal:
            normals, tangents = GetNormalTangents(target_obj.data, True)
            
        padding = 0

        for n, key_name in enumerate(shape_keys):
            if options.debug_delta_normal:
                delta_normals = [[] for i in range(len(verts))]
                delta_tangents = [[] for i in range(len(verts))]
                offsets = [[] for i in range(len(verts))]

            print(key_name)
            # Create new shape key
            sk = target_obj.shape_key_add(name = key_name, from_mix=False)
            sk.interpolation = 'KEY_LINEAR'
            sk.relative_key = sk_basis
            sk.slider_min = 0
            sk.slider_max = 1
            # position each vert
            for i in range(len(verts)):
                sk.data[i].co.x += morph_data[n][i][0]
                sk.data[i].co.y += morph_data[n][i][1]
                sk.data[i].co.z += morph_data[n][i][2]
                if options.debug_delta_normal:
                    offsets[i] = [morph_data[n][i][0],morph_data[n][i][1],morph_data[n][i][2]]
                    delta_normals[i] = [morph_data[n][i][4],morph_data[n][i][5],morph_data[n][i][6]]
                    delta_tangents[i] = [morph_data[n][i][7],morph_data[n][i][8],morph_data[n][i][9]]
            
            if options.debug_delta_normal:
                VisualizeVectors(target_obj.data, offsets, [[n[0] + dn[0], n[1] + dn[1], n[2] + dn[2]] for n, dn in zip(normals, delta_normals)], key_name)
                VisualizeVectors(target_obj.data, offsets, [[n[0] + dn[0], n[1] + dn[1], n[2] + dn[2]] for n, dn in zip(tangents, delta_tangents)], key_name)

        operator.report({'INFO'}, f"Import Morph Successful.")
        return {'FINISHED'}
    
def ExportMorph(options, context, export_file_path, operator):
    export_path = export_file_path
    utils_path, temp_path = update_path(os.path.dirname(__file__))
    data_path = os.path.join(temp_path, "morph_data_export.json")

    target_obj = GetActiveObject()
    s_objs = GetSelectedObjs(True)
    ref_obj = None
    if len(s_objs) > 0:
        n_objs = []
        for s_obj in s_objs:
            s_obj, n_obj = PreprocessAndProxy(s_obj, False, False)
            n_objs.append(n_obj)

        SetSelectObjects(n_objs)
        bpy.ops.object.join()
        ref_obj = GetActiveObject()
        bpy.ops.object.shade_smooth(use_auto_smooth=True)

    if target_obj == None:
        operator.report({'WARNING'}, f"Must select an object to export.")
        return {"FINISHED"}

    if target_obj.data.shape_keys == None or target_obj.data.shape_keys.key_blocks == None:
        operator.report({'WARNING'}, f"Object has no shape keys.")
        return {"FINISHED"}

    num_shape_keys = len(target_obj.data.shape_keys.key_blocks)
    print(list(target_obj.data.shape_keys.key_blocks))
    key_blocks = target_obj.data.shape_keys.key_blocks
    if num_shape_keys < 2:
        operator.report({'WARNING'}, f"No enough shape keys to export.")
        return {"FINISHED"}
    
    if key_blocks[0].name != 'Basis':
        operator.report({'WARNING'}, f"The first shape key should always be the basis and named \'Basis\'.")
        return {"FINISHED"}
    
    if ref_obj != None:
        if ref_obj.data.shape_keys == None or ref_obj.data.shape_keys.key_blocks == None:
            operator.report({'WARNING'}, f"Reference object has no shape keys.")
            return {"FINISHED"}

        ref_num_shape_keys = len(ref_obj.data.shape_keys.key_blocks)
        print(list(ref_obj.data.shape_keys.key_blocks))
        ref_key_blocks = ref_obj.data.shape_keys.key_blocks
        
        if ref_num_shape_keys < num_shape_keys:
            operator.report({'WARNING'}, f"Reference objects don't have enough keys.")
            return {"FINISHED"}
        else:
            key_mapping = [-1 for i in range(num_shape_keys)]
            for _key in key_blocks:
                _key_index = key_blocks.keys().index(_key.name)
                ref_key_index = ref_key_blocks.keys().index(_key.name)
                if ref_key_index == -1:
                    operator.report({'WARNING'}, f"Reference objects don't have some keys: {_key.name}")
                    return {"FINISHED"}
                key_mapping[_key_index] = ref_key_index

            for ref_key in ref_key_blocks:
                ref_key.value = 0

    target_obj, proxy_obj = PreprocessAndProxy(target_obj, False, False)
    verts_count = len(proxy_obj.data.vertices)
    bpy.ops.object.transform_apply(location=False, rotation=False, scale=True)
    key_blocks = proxy_obj.data.shape_keys.key_blocks

    SmoothPerimeterNormal(proxy_obj, s_objs, True)

    if num_shape_keys != len(key_blocks):
        raise("Unknown Error")
    
    jsondata = {
        "numVertices": 0,
        "shapeKeys": [],
        "morphData": [],
        "delta_normals":[]
    }

    jsondata["numVertices"] = verts_count
    jsondata["shapeKeys"] = [kb.name for kb in key_blocks[1:]]
    
    shape_keys = key_blocks[1:]
    original_shape_keys = target_obj.data.shape_keys.key_blocks[1:]

    for i in range(num_shape_keys - 1):
        jsondata["morphData"].append([])
        for j in range(jsondata["numVertices"]):
            jsondata["morphData"][i].append([0,0,0,[],[]])
    
    Basis = key_blocks[0]
    
    for key in original_shape_keys:
        key.value = 0

    for n, sk in enumerate(shape_keys):
        for i in range(verts_count):
            jsondata["morphData"][n][i][0] = sk.data[i].co.x - Basis.data[i].co.x
            jsondata["morphData"][n][i][1] = sk.data[i].co.y - Basis.data[i].co.y
            jsondata["morphData"][n][i][2] = sk.data[i].co.z - Basis.data[i].co.z

    basis_normals, basis_tangents = GetNormalTangents(proxy_obj.data, True)

    for n, cur_key in enumerate(original_shape_keys):
        shape_key_index = key_blocks.keys().index(cur_key.name)

        bpy.ops.object.mode_set(mode='EDIT')
        proxy_obj.active_shape_key_index = shape_key_index
        target_obj.active_shape_key_index = shape_key_index
        if ref_obj:
            ref_obj.active_shape_key_index = key_mapping[shape_key_index]
            for key in ref_key_blocks:
                key.value = 0
            ref_key_blocks[cur_key.name].value = 1

        for key in original_shape_keys:
            key.value = 0
        cur_key.value = 1

        bm = bmesh.from_edit_mesh(proxy_obj.data)
        me = bpy.data.meshes.new("mesh")
        me_obj = bpy.data.objects.new(cur_key.name, me)  # add a new object using the mesh
        bpy.context.collection.objects.link(me_obj)
        bm.to_mesh(me)
        bm.free()
        
        bpy.ops.object.mode_set(mode='OBJECT')
        SetActiveObject(me_obj)
        bpy.ops.object.shade_smooth(use_auto_smooth=True)

        SmoothPerimeterNormal(me_obj, [ref_obj], True, target_obj)

        normals, tangents = GetNormalTangents(me, True)

        for i in range(verts_count):
            jsondata["morphData"][n][i][3] = list(normals[i] - basis_normals[i])
            jsondata["morphData"][n][i][4] = list(tangents[i] - basis_tangents[i])

        bpy.data.meshes.remove(me)
        
        SetActiveObject(proxy_obj)
    
    if ref_obj:
        mesh = ref_obj.data
        bpy.data.objects.remove(ref_obj)
        bpy.data.meshes.remove(mesh)

    for key in original_shape_keys:
        key.value = 0

    target_obj.active_shape_key_index = 0

    with open(data_path, 'w') as json_file:
        json.dump(jsondata, json_file, indent=4)
    print(f"Data saved to {data_path}")

    log_file_path = os.path.join(utils_path, "console_export_morph.log")
    with open(log_file_path, "w") as log_file:
        result = subprocess.run([os.path.join(utils_path, 'MeshConverter.exe'),
                            '-gm',
                            data_path,
                            export_path,
                            ],stdout=log_file)
        
    if result.returncode != 0:
        bpy.data.meshes.remove(proxy_obj.data)
        
        SetActiveObject(target_obj)

        operator.report({'INFO'}, f"Execution failed with return code {result.returncode}. Contact the author for assistance.")
        return {"CANCELLED"}

    bpy.data.meshes.remove(proxy_obj.data)
    
    SetActiveObject(target_obj)

    operator.report({'INFO'}, f"Export morph successful.")
    return {"FINISHED"}

# Export operator
class ExportCustomMesh(bpy.types.Operator):
    bl_idname = "export.custom_mesh"
    bl_label = "Export Custom Mesh"
    
    filepath: bpy.props.StringProperty(options={'HIDDEN'})
    filename: bpy.props.StringProperty(default='untitled.mesh')
    filter_glob: bpy.props.StringProperty(default="*.mesh", options={'HIDDEN'})

    mesh_scale: bpy.props.FloatProperty(
        name="Scale",
        default=1,
    )
    max_border: bpy.props.FloatProperty(
        name="Compression Border",
        description="2 for body parts, 0 otherwise.",
        default=0,
    )
    use_world_origin: bpy.props.BoolProperty(
        name="Use world origin",
        description="Use world instead of object origin as output geometry's origin.",
        default=True
    )
    normalize_weights: bpy.props.BoolProperty(
        name="Normalize weights",
        description="",
        default=True,
    )
    GEO: bpy.props.BoolProperty(
        name="Geometry",
        description=export_items[0][2],
        default=True
    )
    NORM: bpy.props.BoolProperty(
        name="Normals",
        description=export_items[1][2],
        default=True
    )
    VERTCOLOR: bpy.props.BoolProperty(
        name="Vertex Color",
        description=export_items[3][2],
        default=True
    )
    WEIGHTS: bpy.props.BoolProperty(
        name="Weights",
        description=export_items[4][2],
        default=True
    )

    export_sf_mesh_open_folder: bpy.props.BoolProperty(
        name="Open folder after export",
        default=False,
    )
    export_sf_mesh_hash_result: bpy.props.BoolProperty(
        name="Generate hash names",
        description="Export into [hex1]\\[hex2].mesh instead of [name].mesh",
        default=False,
    )
    export_morph: bpy.props.BoolProperty(
        name="Export morph data (if any)",
        description="Export shape keys as morph keys",
        default=False,
    )

    def execute(self,context):
        original_active = GetActiveObject()
        original_selected = GetSelectedObjs(True)
        mesh_success = ExportMesh(self,context,self.filepath,self)

        if 'FINISHED' in mesh_success and self.export_morph:
            SetSelectObjects(original_selected)
            SetActiveObject(original_active)
            _file_name, _ =os.path.splitext(self.filepath)
            morph_success = ExportMorph(self,context, _file_name + ".dat", self)
            if 'FINISHED' in morph_success:
                self.report({'INFO'}, "Operation successful.")

            return morph_success
        
        return mesh_success

    def invoke(self, context, event):
        _obj = context.active_object
        if _obj:
            self.filename = _obj.name + '.mesh'
        else:
            self.filename = 'untitled.mesh'
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

# Import operator
class ImportCustomMesh(bpy.types.Operator):
    bl_idname = "import.custom_mesh"
    bl_label = "Import Custom Mesh"
    
    filepath: bpy.props.StringProperty(subtype="FILE_PATH")
    filename: bpy.props.StringProperty(default='untitled.mesh')
    
    import_as_read_only: bpy.props.BoolProperty(
        name="As Read Only",
        description="The object will be marked as read only. You can import morph once, however, as long as there's morph data in this object, any attempt to import a new morph will be prohibited.",
        default=False
    )
    meshlets_debug: bpy.props.BoolProperty(
        name="Debug Meshlets",
        description="Debug option. DO NOT USE.",
        default=False
    )
    culldata_debug: bpy.props.BoolProperty(
        name="Debug CullData",
        description="Debug option. DO NOT USE.",
        default=False
    )
    tangents_debug: bpy.props.BoolProperty(
        name="Debug Tangent Vectors",
        description="Debug option. DO NOT USE.",
        default=False
    )

    def execute(self, context):
        return ImportMesh(self, context, self)

    def invoke(self, context, event):
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

class ImportCustomMorph(bpy.types.Operator):
    bl_idname = "import.custom_morph"
    bl_label = "Import Custom Morph"
    
    filepath: bpy.props.StringProperty(subtype="FILE_PATH")
    filename: bpy.props.StringProperty(default='morph.dat')
    debug_delta_normal: bpy.props.BoolProperty(
        name="Debug Delta Normals",
        description="Debug option. DO NOT USE.",
        default=False
    )
    def execute(self, context):
        return ImportMorph(self, context, self)

    def invoke(self, context, event):
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

class ExportCustomMorph(bpy.types.Operator):
    bl_idname = "export.custom_morph"
    bl_label = "Export Custom Morph"
    
    filepath: bpy.props.StringProperty(subtype="FILE_PATH")
    filename: bpy.props.StringProperty(default='morph.dat')
    filter_glob: bpy.props.StringProperty(default="*.dat", options={'HIDDEN'})

    def execute(self, context):
        return ExportMorph(self, context, self.filepath, self)

    def invoke(self, context, event):
        self.filename = "morph.dat"
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

class ExportSFMeshOperator(bpy.types.Operator):
    """Export the active object"""
    bl_idname = "export.sfmesh"
    bl_label = "Export Active Mesh"
    
    folder_path: bpy.props.StringProperty(subtype="DIR_PATH", default="")

    def execute(self, context):
        _obj = bpy.context.active_object
        if _obj and _obj.type == 'MESH':
            original_active = GetActiveObject()
            original_selected = GetSelectedObjs(True)
            active_object_name = bpy.context.active_object.name
            success = ExportMesh(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, sanitize_filename(active_object_name) + '.mesh'), self)

            if 'FINISHED' in success and context.scene.export_morph:
                SetSelectObjects(original_selected)
                SetActiveObject(original_active)
                morph_success = ExportMorph(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, sanitize_filename(active_object_name) + '.dat'), self)
                
                if 'FINISHED' in morph_success:
                    self.report({'INFO'}, "Operation successful.")

                return morph_success
            
            return success
        
        self.report({'WARNING'}, "You didn't choose a object with geometry!")
        return {'CANCELLED'}

class ExportSFMeshPanel(bpy.types.Panel):
    """Panel for the Export Starfield Mesh functionality"""
    bl_idname = "OBJECT_PT_export_sf_mesh"
    bl_label = "Export Starfield Mesh"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = 'Tool'

    def draw(self, context):
        layout = self.layout
        # Folder path input
        layout.label(text="Export Folder:")
        layout.prop(context.scene, "export_mesh_folder_path", text="")

        # Export settings
        layout.label(text="Export Settings:")
        layout.prop(context.scene, "mesh_scale", text="Scale")
        layout.prop(context.scene, "max_border", text="Compression Border")
        layout.prop(context.scene, "use_world_origin", text="Use world origin")
        layout.prop(context.scene, "normalize_weights", text="Normalize weights")
        
        
        layout.label(text="Export Datatypes:") 
        # Create a checkbox for each item
        for item in export_items:
            layout.prop(context.scene, item[0], text=item[1])
        
        layout.prop(context.scene, "export_morph", text="Morph Data")
           
        layout.label(text="After Export:") 
        layout.prop(context.scene, "export_sf_mesh_open_folder", text="Open export folder")
        layout.prop(context.scene, "export_sf_mesh_hash_result", text="Hash file name")
        # Button to export the selected skeleton
        layout.operator("export.sfmesh", text="Export .mesh")


# Add custom menu entries in the File menu
def menu_func_export(self, context):
    self.layout.operator(
        ExportCustomMesh.bl_idname,
        text="Starfield Geometry (.mesh)",
    )

def menu_func_import(self, context):
    self.layout.operator(
        ImportCustomMesh.bl_idname,
        text="Starfield Geometry (.mesh)",
    )

def menu_func_import_morph(self, context):
    self.layout.operator(
        ImportCustomMorph.bl_idname,
        text="Starfield Morph File (.dat)",
    )

def menu_func_export_morph(self, context):
    self.layout.operator(
        ExportCustomMorph.bl_idname,
        text="Starfield Morph File (.dat)",
    )

# Register the operators and menu entries
def register():
    bpy.types.Scene.export_mesh_folder_path = bpy.props.StringProperty(
        name="Export Folder",
        subtype='DIR_PATH',
        default=os.path.join(os.path.dirname(__file__),'Result'),
    )
    bpy.types.Scene.mesh_scale = bpy.props.FloatProperty(
        name="Scale",
        default=1,
    )
    bpy.types.Scene.max_border = bpy.props.FloatProperty(
        name="Compression Border",
        description="2 for body parts, 0 (Auto) otherwise.",
        default=0,
    )
    bpy.types.Scene.use_world_origin = bpy.props.BoolProperty(
        name="Use world origin",
        description="Use world instead of object origin as output geometry's origin.",
        default=True
    )
    bpy.types.Scene.normalize_weights = bpy.props.BoolProperty(
        name="Normalize weights",
        description="",
        default=False
    )
    bpy.types.Scene.GEO = bpy.props.BoolProperty(
        name="Geometry",
        description=export_items[0][2],
        default=True
    )
    bpy.types.Scene.NORM = bpy.props.BoolProperty(
        name="Normals",
        description=export_items[1][2],
        default=True
    )
    bpy.types.Scene.VERTCOLOR = bpy.props.BoolProperty(
        name="Vertex Color",
        description=export_items[3][2],
        default=True
    )
    bpy.types.Scene.WEIGHTS = bpy.props.BoolProperty(
        name="Weights",
        description=export_items[4][2],
        default=True
    )
    bpy.types.Scene.export_morph = bpy.props.BoolProperty(
        name="Morph Data",
        description="Export shape keys as morph keys",
        default=True
    )

    bpy.types.Scene.export_sf_mesh_open_folder = bpy.props.BoolProperty(
        name="Open folder",
        default=False,
    )
    bpy.types.Scene.export_sf_mesh_hash_result = bpy.props.BoolProperty(
        name="Generate hash names",
        description="Export into [hex1]\\[hex2].mesh instead of [model_name].mesh",
        default=False,
    )

    bpy.utils.register_class(ExportCustomMesh)
    bpy.utils.register_class(ImportCustomMesh)
    bpy.utils.register_class(ImportCustomMorph)
    bpy.utils.register_class(ExportCustomMorph)
    bpy.utils.register_class(ExportSFMeshOperator)
    bpy.utils.register_class(ExportSFMeshPanel)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export)
    bpy.types.TOPBAR_MT_file_import.append(menu_func_import)
    bpy.types.TOPBAR_MT_file_import.append(menu_func_import_morph)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export_morph)

def unregister():
    bpy.utils.unregister_class(ExportSFMeshOperator)
    bpy.utils.unregister_class(ExportSFMeshPanel)
    bpy.utils.unregister_class(ExportCustomMesh)
    bpy.utils.unregister_class(ImportCustomMesh)
    bpy.utils.unregister_class(ImportCustomMorph)
    bpy.utils.unregister_class(ExportCustomMorph)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)
    bpy.types.TOPBAR_MT_file_import.remove(menu_func_import)
    bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_morph)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_morph)
    del bpy.types.Scene.export_mesh_folder_path
    del bpy.types.Scene.mesh_scale
    del bpy.types.Scene.max_border
    del bpy.types.Scene.use_world_origin
    del bpy.types.Scene.normalize_weights
    del bpy.types.Scene.GEO
    del bpy.types.Scene.NORM
    del bpy.types.Scene.VERTCOLOR
    del bpy.types.Scene.WEIGHTS
    del bpy.types.Scene.export_sf_mesh_open_folder
    del bpy.types.Scene.export_sf_mesh_hash_result
    del bpy.types.Scene.export_morph

if __name__ == "__main__":
    register()