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

def MeshToJson(obj, options, bone_list_filter = None, prune_empty_vertex_groups = False, replace_facebone_vg_with_head = False):
	# Initialize dictionaries to store data
	data = {
		"max_border": options.max_border,
		"num_verts": 0,
		"positions_raw": [],
		"num_indices": 0,
		"vertex_indices_raw": [],
		"normals": [],
		"uv_coords": [],
		"vertex_color": [],
		"vertex_group_names": [],
		"vertex_weights": [],
		"smooth_group": [],
		"tangents": [],
	}

	old_obj = obj
	if not (old_obj and old_obj.type == 'MESH'):
		return {'CANCELLED'}, "Selected object is not a mesh.", None

	old_obj, selected_obj = utils_blender.PreprocessAndProxy(old_obj, options.use_world_origin)

	if 'DOUBLE_FACES_VERTS' in selected_obj.vertex_groups:
		double_faces_vg = selected_obj.vertex_groups['DOUBLE_FACES_VERTS']
		selected_obj.vertex_groups.remove(double_faces_vg)
		double_faces_vg_old = old_obj.vertex_groups['DOUBLE_FACES_VERTS']
		old_obj.vertex_groups.remove(double_faces_vg_old)

	if "SMOOTH_GROUP" in selected_obj.vertex_groups:
		smooth_group = selected_obj.vertex_groups["SMOOTH_GROUP"]
		selected_obj.vertex_groups.remove(smooth_group)

	if "SHARP_GROUP" in selected_obj.vertex_groups:
		sharp_group = selected_obj.vertex_groups["SHARP_GROUP"]
		selected_obj.vertex_groups.remove(sharp_group)

	if bone_list_filter != None:
		for vert_gp in selected_obj.vertex_groups:
			if vert_gp.name not in bone_list_filter:
				selected_obj.vertex_groups.remove(vert_gp)

	if replace_facebone_vg_with_head:
		facebone_vg_names = [vg.name for vg in selected_obj.vertex_groups if vg.name.startswith("faceBone_")]
		utils_blender.CombineVertexGroups(selected_obj, facebone_vg_names, "C_Head", True)

	bm = bmesh.new()
	bm.from_mesh(selected_obj.data)

	# Extract data from the mesh
	color_layer = bm.loops.layers.color.active
	verts_count = 0
	hanging_verts = []

	if options.GEO:
		positions = [list(vert.co) for vert in selected_obj.data.vertices.values()] 
		data["positions_raw"] = utils.flatten(positions)

	for v in bm.verts:
		verts_count += 1
		
		has_hanging_verts = False
		if len(v.link_loops) == 0:
			hanging_verts.append(v.index)
			has_hanging_verts = True

		if options.VERTCOLOR and color_layer:
			loop = v.link_loops[0]
			data["vertex_color"].append([loop[color_layer][0],loop[color_layer][1],loop[color_layer][2],loop[color_layer][3]])

	data["num_verts"] = verts_count

	if verts_count >= 65535:
		return {'CANCELLED'}, f"Your model has to many vertices. Try to reduce your vertex count.", None

	if has_hanging_verts:
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

		return {'CANCELLED'}, "There are floating verts in your model. Some verts don't belong to any faces.", None
	
	try:
		first_uv_layer = selected_obj.data.uv_layers.active
		second_uv_layer = None
		if options.use_secondary_uv:
			# Select the other uv layer that is not the first one
			for uv_layer in selected_obj.data.uv_layers:
				if uv_layer != first_uv_layer:
					second_uv_layer = uv_layer
					break
			if second_uv_layer == None:
				options.use_secondary_uv = False
		data["uv_coords"] = [[] for _ in range(verts_count)]
		if options.use_secondary_uv:
			data["uv_coords2"] = [[] for _ in range(verts_count)]
		Tangents = [np.array([0,0,0]) for _ in range(verts_count)]
		Normals = [np.array([0,0,0]) for _ in range(verts_count)]
		Bitangent_sign = [1 for _ in range(verts_count)]
		selected_obj.data.calc_tangents()
		selected_obj.data.calc_normals_split()
		
		for face in selected_obj.data.polygons:
			for vert_idx, loop_idx in zip(face.vertices, face.loop_indices):
				uv_coords = first_uv_layer.data[loop_idx].uv
				data["uv_coords"][vert_idx] = [uv_coords[0],1 - uv_coords[1]]
				if options.use_secondary_uv:
					uv_coords2 = second_uv_layer.data[loop_idx].uv
					data["uv_coords2"][vert_idx] = [uv_coords2[0],1 - uv_coords2[1]]

				Bitangent_sign[vert_idx] = selected_obj.data.loops[loop_idx].bitangent_sign 
				Tangents[vert_idx] = np.array(selected_obj.data.loops[loop_idx].tangent) + Tangents[vert_idx]
				Normals[vert_idx] = np.array(selected_obj.data.loops[loop_idx].normal) + Normals[vert_idx]

		data["normals"] = [list(utils_math.Normalize(n)) for n in Normals]
		data["tangents"] = [list(utils_math.GramSchmidtOrthogonalize(t, np.array(n))) + [3 if f < 0 else 0] for t, n, f in zip(Tangents, data["normals"], Bitangent_sign)]

		for _l in data["uv_coords"]:
			if len(_l) == 0:
				print(data["uv_coords"], verts_count)
				return {'CANCELLED'}, "Some verts don't have UV coords.", None
				
		indices_count = 0
		if options.GEO:
			for f in bm.faces:
				data["vertex_indices_raw"].extend([v.index for v in f.verts])
				indices_count += 3

		data["num_indices"] = indices_count

		# Extract vertex weights and bones
		if len(selected_obj.vertex_groups) == 0:
			options.WEIGHTS = False

		if options.WEIGHTS:
			vertex_groups = selected_obj.vertex_groups
			if prune_empty_vertex_groups:
				vgrp_markers = [[vg.name, -1] for vg in vertex_groups]
			else:
				vgrp_markers = [[vg.name, i] for vg, i in zip(vertex_groups, range(len(vertex_groups)))]
			new_id = 0

			bm.verts.layers.deform.verify()

			deform = bm.verts.layers.deform.active
			
			data["vertex_weights"]=[]
			_min_weight = 1 / 65534
			for v in bm.verts:
				g = v[deform]
				
				data["vertex_weights"].append([])
				for bone_id, weight in g.items():
					if weight > _min_weight:
						if vgrp_markers[bone_id][1] == -1:
							vgrp_markers[bone_id][1] = new_id
							new_id += 1
						data["vertex_weights"][-1].append([vgrp_markers[bone_id][1], weight])
				
				if len(data["vertex_weights"][-1]) > 8:
					index_list = sorted(range(len(data["vertex_weights"][-1])), key=lambda k: data["vertex_weights"][-1][k], reverse=True)
					data["vertex_weights"][-1] = [data["vertex_weights"][-1][i] for i in index_list[:8]]
				
				if len(data["vertex_weights"][-1]) == 0:
					data["vertex_weights"][-1].append([0, 0])

			vgrp_markers = sorted(vgrp_markers, key=lambda x: x[1])
			data['vertex_group_names'] = [vg[0] for vg in vgrp_markers if vg[1] != -1]

	except IndexError:
		return {'CANCELLED'}, "The mesh may have loose vertices, try to Clean Up the mesh or contact the author.", None

	# Cleanup
	bm.to_mesh(selected_obj.data)
	bm.free()

	bpy.context.view_layer.objects.active = old_obj
	old_obj.select_set(True)
	
	bpy.data.meshes.remove(selected_obj.data)

	return {'FINISHED'}, "", data

def ExportMesh(options, context, filepath: str, operator, bone_list_filter = None, prune_empty_vertex_groups = False, replace_facebone_vg_with_head = False):
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
	
	rtn, message, data = MeshToJson(active_object, options, bone_list_filter, prune_empty_vertex_groups, replace_facebone_vg_with_head)

	if rtn != {'FINISHED'}:
		operator.report({'ERROR'}, message)
		return returncode, 0, 0, None

	json_data = json.dumps(data)

	#with open(result_file_path + '.json', 'w') as json_file:
	#	json_file.write(json_data)
	
	returncode = MeshConverter.ExportMeshFromJson(json_data, result_file_path, options.mesh_scale, False, options.normalize_weights, False)

	if returncode:
		operator.report({'INFO'}, "Starfield .mesh exported successfully")

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

					box = utils_blender.BoxFromCenterExpand(f"CullCone_{i}", min_max_bounds[:3], min_max_bounds[3:])
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
	
	if options.import_as_read_only:
		obj.name = utils_blender.read_only_marker + obj.name

	bm.free()
	utils_blender.SetActiveObject(obj)
	return {'FINISHED'}
