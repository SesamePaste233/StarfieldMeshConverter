import bpy
import os
import bmesh
import json
from collections import defaultdict
import mathutils
import numpy as np
from mathutils import Color

from utils_blender import SetActiveObject, GetSelectedObjs

from utils_blender import update_path, open_folder, read_only_marker

from utils_blender import PreprocessAndProxy, SmoothPerimeterNormal

from utils import hash_string, sanitize_filename, flatten

from utils_math import Normalize, GramSchmidtOrthogonalize

from MeshConverter import _dll_export_mesh, _dll_import_mesh

def ExportMesh(options, context, filepath, operator, bone_list_filter = None):
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
		return {'CANCELLED'}, 0,0, None
	
	s_objs = GetSelectedObjs(True)

	old_obj, selected_obj = PreprocessAndProxy(old_obj, options.use_world_origin)
	
	SmoothPerimeterNormal(selected_obj, s_objs)
	bpy.ops.object.convert(target='MESH')

	# Check if the selected object is a mesh
	if selected_obj and selected_obj.type == 'MESH':
		
		if "SMOOTH_GROUP" in selected_obj.vertex_groups:
			smooth_group = selected_obj.vertex_groups["SMOOTH_GROUP"]
			selected_obj.vertex_groups.remove(smooth_group)
			operator.report({"INFO"},f"SMOOTH_GROUP is no longer needed in this version.")

		if "SHARP_GROUP" in selected_obj.vertex_groups:
			sharp_group = selected_obj.vertex_groups["SHARP_GROUP"]
			selected_obj.vertex_groups.remove(sharp_group)
			operator.report({"INFO"},f"SHARP_GROUP is no longer needed in this version.")

		if bone_list_filter != None:
			for vert_gp in selected_obj.vertex_groups:
				if vert_gp.name not in bone_list_filter:
					selected_obj.vertex_groups.remove(vert_gp)

		bm = bmesh.new()
		bm.from_mesh(selected_obj.data)

		# Extract data from the mesh
		color_layer = bm.loops.layers.color.active
		uv_layer = bm.loops.layers.uv.active
		verts_count = 0
		hanging_verts = []
		vgrp_names = None

		if options.GEO:
			positions = [list(vert.co) for vert in selected_obj.data.vertices.values()] 
			data["positions_raw"] = flatten(positions)

		for v in bm.verts:
			verts_count += 1
			
			has_hanging_verts = False
			if len(v.link_loops) == 0:
				hanging_verts.append(v.index)
				has_hanging_verts = True

			if options.VERTCOLOR and color_layer:
				loop = v.link_loops[0]
				data["vertex_color"].append([loop[color_layer][0],loop[color_layer][1],loop[color_layer][2],loop[color_layer][3]])

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

			return {'CANCELLED'}, 0,0, None
		
		try:
			data["uv_coords"] = [[] for i in range(verts_count)]
			Tangents = [np.array([0,0,0]) for i in range(verts_count)]
			Normals = [np.array([0,0,0]) for i in range(verts_count)]
			Bitangent_sign = [1 for i in range(verts_count)]
			selected_obj.data.calc_tangents()
			selected_obj.data.calc_normals_split()

			for face in selected_obj.data.polygons:
				for vert_idx, loop_idx in zip(face.vertices, face.loop_indices):
					uv_coords = selected_obj.data.uv_layers.active.data[loop_idx].uv
					data["uv_coords"][vert_idx] = [uv_coords[0],1 - uv_coords[1]]

					Bitangent_sign[vert_idx] = selected_obj.data.loops[loop_idx].bitangent_sign 
					Tangents[vert_idx] = Tangents[vert_idx] + np.array(selected_obj.data.loops[loop_idx].tangent)
					Normals[vert_idx] = Normals[vert_idx] + np.array(selected_obj.data.loops[loop_idx].normal)

			data["normals"] = [list(Normalize(n)) for n in Normals]
			data["tangents"] = [list(GramSchmidtOrthogonalize(t, np.array(n))) + [3 if f < 0 else 0] for t, n, f in zip(Tangents, data["normals"], Bitangent_sign)]

			for _l in data["uv_coords"]:
				if len(_l) == 0:
					operator.report({'WARNING'}, f"Some verts don't have UV coords.")
					print(data["uv_coords"], verts_count)
					return {'CANCELLED'}, 0,0, None
					
			indices_count = 0
			if options.GEO:
				for f in bm.faces:
					data["vertex_indices_raw"].extend([v.index for v in f.verts])
					indices_count += 3

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
			return {'CANCELLED'}, 0,0, None

		# Cleanup
		bm.to_mesh(selected_obj.data)
		bm.free()
	else:
		operator.report({'WARNING'},"Selected object is not a mesh.")
		return {'CANCELLED'}, 0,0, None

	if selected_obj:
		bpy.context.view_layer.objects.active = old_obj
		old_obj.select_set(True)
		bpy.data.meshes.remove(selected_obj.data)

		if verts_count >= 65535:
			operator.report({'WARNING'}, f"You model has to many vertices. Try to reduce your vertex count.")
			return {'CANCELLED'}, 0,0, None

		if options.export_sf_mesh_hash_result:
			hash_folder, hash_name = hash_string(active_object_name)
			object_folder_name = sanitize_filename(active_object_name)
			result_file_folder = os.path.join(os.path.dirname(export_mesh_file_path), object_folder_name, hash_folder)
			os.makedirs(result_file_folder, exist_ok = True)
			result_file_path = os.path.join(result_file_folder, hash_name + ".mesh")
		else:
			result_file_path = export_mesh_file_path
		
		json_data = json.dumps(data)

		returncode = _dll_export_mesh(json_data.encode('utf-8'), result_file_path.encode('utf-8'), options.mesh_scale, False, options.normalize_weights, False)

		if returncode == 0:
			operator.report({'INFO'}, "Starfield .mesh exported successfully")

			if options.export_sf_mesh_open_folder == True:
				open_folder(bpy.path.abspath(export_mesh_folder_path))

			return {'FINISHED'}, verts_count, indices_count, vgrp_names
			
		else:
			operator.report({'INFO'}, f"Execution failed with return code {returncode}. Contact the author for assistance.")
			return {'CANCELLED'}, 0,0, None
		
	return {'CANCELLED'}, 0,0, None

def ImportMesh(options, context, operator, mesh_name_override = None):
	import_path = options.filepath
	utils_path, temp_path = update_path(os.path.dirname(__file__))

	rtn = _dll_import_mesh(import_path.encode('utf-8'), os.path.join(temp_path, "mesh_data_import").encode('utf-8')).decode('utf-8')

	if rtn == "":
		returncode = -1 
	else:
		returncode = 0

	if returncode == 0:
		operator.report({'INFO'}, "Starfield .mesh imported successfully")
		
		bpy.ops.wm.obj_import(
			filepath=os.path.join(temp_path, "mesh_data_import.obj"),
			forward_axis='Y',
			up_axis ='Z',  # Customize other import options here
		)

		obj = bpy.context.selected_objects[0]
		if obj:
			mesh = obj.data
			if mesh_name_override != None:
				mesh.name = mesh_name_override
			if not mesh.vertex_colors:
				mesh.vertex_colors.new()

			bm = bmesh.new()
			bm.from_mesh(mesh)

			col = obj.data.vertex_colors.active

			data = json.loads(rtn)

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
					for v_ix, l_ixs in vertex_map.items():
						for l_ix in l_ixs:
							w = data['tangents'][v_ix][3] / 3.0
							col.data[l_ix].color = (w, w, w, w)
			
			if options.import_as_read_only:
				obj.name = read_only_marker + obj.name

			bm.free()
			SetActiveObject(obj)
			return {'FINISHED'}
		else:
			operator.report({'WARNING'}, f"Unknown error. Contact the author for assistance.")
			return {'CANCELLED'}

	else:
		operator.report({'INFO'}, f"Execution failed with return code {returncode}. Contact the author for assistance.")
		return {'CANCELLED'}