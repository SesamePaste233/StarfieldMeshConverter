import bpy
import os
import bmesh
import json
import math
import numpy as np
import time

import utils_blender
import utils_math
import utils_primitive
import MeshConverter

def IsMorphExportNode(obj):
	return obj.name.startswith('[MorphExport]')

def GetMorphObjMorphName(obj):
	name = obj.name
	return name[name.find('[') + 1 : name.find(']')]

def IsMorphObject(obj):
	if obj == None:
		return False
	name = obj.name
	i = name.find('[')
	j = name.find(']')
	return j > i

def DEPRECATED_ImportMorph(options, context, operator, result_objs = []):
	import_path = options.filepath
	
	rtn = MeshConverter.ImportMorphAsJson(import_path)

	if rtn == "":
		returncode = -1 
	else:
		returncode = 0

	if returncode != 0:
		operator.report({'INFO'}, f"Execution failed with return code {returncode}. Contact the author for assistance.")
		return {"CANCELLED"}
	
	jsondata = json.loads(rtn)

	vert_count = jsondata["numVertices"]
	shape_keys = list(jsondata["shapeKeys"])
	morph_data = jsondata["morphData"]

	target_obj = bpy.context.active_object

	if target_obj == None or len(target_obj.data.vertices) != vert_count:
		target_obj = None
		for _obj in bpy.data.objects:
			if _obj.type == 'MESH' and utils_blender.read_only_marker not in _obj.name and len(_obj.data.vertices) == vert_count:
				target_obj = _obj
				break
	
	if target_obj == None:
		operator.report({'WARNING'}, f"No matching mesh found for the morph.")
		return {"CANCELLED"}
	else:
		if utils_blender.read_only_marker in target_obj.name and target_obj.data.shape_keys != None and len(target_obj.data.shape_keys.key_blocks) != 0:
			operator.report({'WARNING'}, f"Target mesh is Read Only! Remove {utils_blender.read_only_marker} in the name before continue.")
			return {"CANCELLED"}
	

	verts = target_obj.data.vertices

	target_obj.shape_key_clear()
	sk_basis = target_obj.shape_key_add(name = 'Basis', from_mix=False)
	sk_basis.interpolation = 'KEY_LINEAR'
	target_obj.data.shape_keys.use_relative = True

	debug_mode = options.debug_delta_normal or options.debug_padding or options.debug_delta_tangent

	if debug_mode or options.as_multiple:
		normals, tangents, signs = utils_blender.GetNormalTangents(target_obj.data, True)
		
	if options.as_multiple:
		prev_coll = bpy.data.collections.new('morphs_' + target_obj.name)
		bpy.context.scene.collection.children.link(prev_coll)
		
		morph_node = bpy.data.objects.new('[MorphExport]' + target_obj.name, None, )
		morph_node.empty_display_size = 0.015

		utils_blender.move_object_to_collection([morph_node], prev_coll)
		utils_blender.move_object_to_parent([morph_node], target_obj)

		result_objs.clear()

	if options.as_multiple:
		key_blocks = target_obj.data.shape_keys.key_blocks
		for sk in key_blocks:
			shape_key_index = key_blocks.keys().index(sk.name)

			utils_blender.SetActiveObject(target_obj)
			bpy.ops.object.mode_set(mode='EDIT')
			target_obj.active_shape_key_index = shape_key_index
			for key in key_blocks:
				key.value = 0
			sk.value = 1

			bm = bmesh.from_edit_mesh(target_obj.data)
			me = bpy.data.meshes.new("mesh")
			me_obj = bpy.data.objects.new(f"[{sk.name}]"+target_obj.name, me)  # add a new object using the mesh
			bpy.context.collection.objects.link(me_obj)
			bm.to_mesh(me)
			bm.free()

			bpy.ops.object.mode_set(mode='OBJECT')
			me.use_auto_smooth = True
			me.normals_split_custom_set_from_vertices(normals)
			utils_blender.move_object_to_collection([me_obj], prev_coll)
			utils_blender.move_object_to_parent([me_obj], morph_node)

			result_objs.append(me_obj)

	for n, key_name in enumerate(shape_keys):
		
		if debug_mode or options.as_multiple or options.use_attributes:
			delta_normals = [[] for i in range(len(verts))]
			delta_tangents = [[] for i in range(len(verts))]
			offsets = [[] for i in range(len(verts))]
			target_vert_colors = [() for i in range(len(verts))]

		# Create new shape key
		sk = target_obj.shape_key_add(name = key_name, from_mix=False)
		sk.interpolation = 'KEY_LINEAR'
		sk.relative_key = sk_basis
		sk.slider_min = 0
		sk.slider_max = 1

		if options.use_attributes:
			utils_blender.addShapeKeyAttributes(target_obj, sk.name)

			target_obj.data.vertex_colors.active = target_obj.data.vertex_colors[f"COL_{sk.name}"]
			
		# position each vert
		for i in range(len(verts)):
			sk.data[i].co.x += morph_data[n][i][0]
			sk.data[i].co.y += morph_data[n][i][1]
			sk.data[i].co.z += morph_data[n][i][2]
			
			if debug_mode or options.as_multiple:
				offsets[i] = [morph_data[n][i][0],morph_data[n][i][1],morph_data[n][i][2]]
				target_vert_colors[i] = utils_blender.RGB888ToColor(morph_data[n][i][3])
				delta_normals[i] = [morph_data[n][i][4][0],morph_data[n][i][4][1],morph_data[n][i][4][2]]
				delta_tangents[i] = [morph_data[n][i][5][0],morph_data[n][i][5][1],morph_data[n][i][5][2]]
			
			if options.use_attributes:
				target_vert_colors[i] = utils_blender.RGB888ToColor(morph_data[n][i][3])

				target_obj.data.attributes.get(f"NRM_{sk.name}").data[i].vector = [morph_data[n][i][4][0],morph_data[n][i][4][1],morph_data[n][i][4][2]]
				target_obj.data.attributes.get(f"TAN_{sk.name}").data[i].vector = [morph_data[n][i][5][0],morph_data[n][i][5][1],morph_data[n][i][5][2]]

		if options.use_attributes:
			utils_blender.SetVertColorPerVert(target_obj, target_vert_colors)
			
		if options.as_multiple:
			key_blocks = target_obj.data.shape_keys.key_blocks
			shape_key_index = key_blocks.keys().index(sk.name)

			utils_blender.SetActiveObject(target_obj)
			bpy.ops.object.mode_set(mode='EDIT')
			target_obj.active_shape_key_index = shape_key_index
			for key in key_blocks:
				key.value = 0
			sk.value = 1

			bm = bmesh.from_edit_mesh(target_obj.data)
			me = bpy.data.meshes.new("mesh")
			me_obj = bpy.data.objects.new(f"[{sk.name}]"+target_obj.name, me)  # add a new object using the mesh
			bpy.context.collection.objects.link(me_obj)
			bm.to_mesh(me)
			bm.free()

			bpy.ops.object.mode_set(mode='OBJECT')
			me.use_auto_smooth = True
			me.vertex_colors.new(name='col')
			me.normals_split_custom_set_from_vertices([utils_math.NormalizeVec([n[0] + dn[0], n[1] + dn[1], n[2] + dn[2]]) for n, dn in zip(normals, delta_normals)])
			utils_blender.SetVertColorPerVert(me_obj, target_vert_colors)
			utils_blender.move_object_to_collection([me_obj], prev_coll)
			utils_blender.move_object_to_parent([me_obj], morph_node)

			result_objs.append(me_obj)

		if options.debug_delta_normal:
			utils_blender.VisualizeVectors(target_obj.data, offsets, [[n[0] + dn[0], n[1] + dn[1], n[2] + dn[2]] for n, dn in zip(normals, delta_normals)], key_name)
		if options.debug_padding:
			utils_blender.VisualizeVectors(target_obj.data, offsets, [[p * (n[0] + dn[0]), p * (n[1] + dn[1]), p * (n[2] + dn[2])] for n, dn, p in zip(normals, delta_normals, target_vert_colors)], key_name)
		if options.debug_delta_tangent:
			utils_blender.VisualizeVectors(target_obj.data, offsets, [[n[0] + s * dn[0], n[1] + s * dn[1], n[2] + s * dn[2]] for n, dn, s in zip(tangents, delta_tangents, signs)], key_name)
	
	
	
	operator.report({'INFO'}, f"Import Morph Successful.")
	return {'FINISHED'}

def ImportMorphFromNumpy(filepath, operator, debug_delta_normal = False, force_import_on_active = False):
	import_path = filepath
	
	data = MeshConverter.ImportMorphAsNumpy(import_path)

	vert_count = data["numVertices"]
	shape_keys = list(data["shapeKeys"])
	delta_pos = data["deltaPositions"]
	target_colors = data["targetColors"]
	delta_normals = data["deltaNormals"]
	delta_tangents = data["deltaTangents"]

	target_obj = bpy.context.active_object

	if force_import_on_active:
		target_vert_count = len(target_obj.data.vertices)
		operator.report({'WARNING'}, f"Forcing import on active object. Morph verts: {vert_count}, Target object verts: {target_vert_count}")
		if vert_count > target_vert_count:
			delta_pos = delta_pos[:, :target_vert_count, :]
			target_colors = target_colors[:, :target_vert_count, :]
			delta_normals = delta_normals[:, :target_vert_count, :]
			delta_tangents = delta_tangents[:, :target_vert_count, :]
		elif vert_count < target_vert_count:
			delta_pos = np.concatenate((delta_pos, np.zeros((len(shape_keys), target_vert_count - vert_count, 3))), axis=1)
			target_colors = np.concatenate((target_colors, np.zeros((len(shape_keys), target_vert_count - vert_count, 3))), axis=1)
			delta_normals = np.concatenate((delta_normals, np.zeros((len(shape_keys), target_vert_count - vert_count, 3))), axis=1)
			delta_tangents = np.concatenate((delta_tangents, np.zeros((len(shape_keys), target_vert_count - vert_count, 3))), axis=1)
		vert_count = target_vert_count

	if target_obj == None or len(target_obj.data.vertices) != vert_count:
		target_obj = None
		for _obj in bpy.data.objects:
			if _obj.type == 'MESH' and utils_blender.read_only_marker not in _obj.name and len(_obj.data.vertices) == vert_count:
				target_obj = _obj
				break
	
	if target_obj == None:
		operator.report({'WARNING'}, f"No matching mesh found for the morph. Expecting {vert_count} vertices in target object.")
		return {"CANCELLED"}
	else:
		if utils_blender.read_only_marker in target_obj.name and target_obj.data.shape_keys != None and len(target_obj.data.shape_keys.key_blocks) != 0:
			operator.report({'WARNING'}, f"Target mesh is Read Only! Remove {utils_blender.read_only_marker} in the name before continue.")
			return {"CANCELLED"}
	
	basis_positions = np.empty(len(target_obj.data.vertices) * 3, dtype=np.float32)
	target_obj.data.vertices.foreach_get('co', basis_positions)
	basis_positions = basis_positions.reshape(-1, 3)
	if debug_delta_normal:
		basis_normals = np.empty(len(target_obj.data.vertices) * 3, dtype=np.float32)
		target_obj.data.vertices.foreach_get('normal', basis_normals)
		basis_normals = basis_normals.reshape(-1, 3)

	target_obj.shape_key_clear()
	sk_basis = target_obj.shape_key_add(name = 'Basis', from_mix=False)
	sk_basis.interpolation = 'KEY_LINEAR'
	target_obj.data.shape_keys.use_relative = True

	for n, key_name in enumerate(shape_keys):
		sk = target_obj.shape_key_add(name = key_name, from_mix=False)
		sk.interpolation = 'KEY_LINEAR'
		sk.relative_key = sk_basis
		sk.slider_min = 0
		sk.slider_max = 1

		sk.data.foreach_set('co', (basis_positions + delta_pos[n]).flatten())

		if debug_delta_normal:
			utils_blender.VisualizeVectors(target_obj.data, delta_pos[n], basis_normals + delta_normals[n], key_name)

	operator.report({'INFO'}, f"Import Morph Successful.")
	return {'FINISHED'}

def ExportMorphFromSet(options, context, export_file_path, morph_node, operator):
	_morph_objs = [obj for obj in morph_node.children if IsMorphObject(obj)]
	morph_objs = []
	morph_names = []
	basis_obj = None
	has_basis = False

	if len(_morph_objs) < 2:
		operator.report({'WARNING'}, f'You don\'t have enough morph object to export. Expecting one Basis and at least one morph key.')
		return {'CANCELLED'}, None

	for morph_obj in _morph_objs:
		morph_name = GetMorphObjMorphName(morph_obj)
		if morph_name == 'Basis':
			if has_basis:
				operator.report({'WARNING'}, f'Two basis object present.')
				return {'CANCELLED'}, None
			basis_obj = morph_obj
			has_basis = True
		else:
			morph_objs.append(morph_obj)
			morph_names.append(morph_name)

	if has_basis == False:
		operator.report({'WARNING'}, f'You don\'t have any basis mesh.')
		return {'CANCELLED'}, None

	morph_name_non_overlapping = list(set(morph_names))
	if len(morph_name_non_overlapping) != len(morph_names):
		operator.report({'WARNING'}, f'Two identical morph key names present.')
		return {'CANCELLED'}, None

	assert(len(morph_objs) == len(morph_names))

	verts_count = len(basis_obj.data.vertices)
	invalid_morph_objs = []
	for morph_obj in morph_objs:
		if len(morph_obj.data.vertices) != verts_count:
			invalid_morph_objs.append(morph_obj)

	if len(invalid_morph_objs) != 0:
		utils_blender.SetSelectObjects(invalid_morph_objs)
		operator.report({'WARNING'}, f'Selected {len(invalid_morph_objs)} shapes have a different number of verts than basis shape.')
		return {'CANCELLED'}, None
	
	# Begin exporting

	jsondata = {
		"numVertices": 0,
		"shapeKeys": [],
		"morphData": [],
	}
	jsondata["numVertices"] = verts_count
	jsondata["shapeKeys"] = morph_names
	jsondata["morphData"] = []

	morphData = [[] for _ in range(len(morph_names))]

	basis_positions = np.array([list(vert.co) for vert in basis_obj.data.vertices.values()])

	vid_lid_list = utils_blender.CalcVIdLIdlist(basis_obj.data)
	basis_normals, basis_tangents, basis_tangentsigns = utils_blender.GetNormalTangents(basis_obj.data, True, True, vid_lid_list)

	no_color_objs_in_group = []
	for n, sk_obj in enumerate(morph_objs):

		sk_positions = np.array([list(vert.co) for vert in sk_obj.data.vertices.values()])
		nan_ps = np.isnan(sk_positions.flatten())
		if nan_ps.any():
			operator.report({'WARNING'}, f'Found NaN(s) in shape: {sk_obj.name} at vert id: {[i for i in range(verts_count) if nan_ps[i * 3]]}.')
			return {'CANCELLED'}, None

		sk_normals, sk_tangents, _ = utils_blender.GetNormalTangents(sk_obj.data, True, True, vid_lid_list)
		sk_v_colors, has_color = utils_blender.GetVertColorPerVert(sk_obj)
		if has_color == False:
			no_color_objs_in_group.append(sk_obj.name)

		d_P = (sk_positions - basis_positions).tolist()
		d_N = utils_math.bounded_vector_substraction(basis_normals, sk_normals).tolist()
		d_T = (basis_tangentsigns[:, np.newaxis] * utils_math.bounded_vector_substraction(basis_tangents, sk_tangents)).tolist()
		morphData[n] = [[d_p[0], d_p[1], d_p[2], utils_blender.ColorToRGB888(sk_v_colors[i]), d_n, d_t] for i, d_p, d_n, d_t in zip(range(verts_count), d_P, d_N, d_T)]

	if len(no_color_objs_in_group) != 0 and len(no_color_objs_in_group) != len(morph_objs):
		operator.report({'WARNING'}, f'No vertex color found in {len(no_color_objs_in_group)} morph objects: {", ".join(no_color_objs_in_group)}, target vertex colors of corresponding morph keys will be set to 1.')

	jsondata["morphData"] = morphData

	json_data = json.dumps(jsondata)

	if utils_blender.is_plugin_debug_mode():
		debug_json_data = json.dumps(jsondata, indent=2)
		with open(export_file_path + ".json", 'w') as f:
			f.write(debug_json_data)

	returncode = MeshConverter.ExportMorphFromJson(json_data, export_file_path)

	if not returncode:
		operator.report({'INFO'}, f"Execution failed with error message: \"{returncode.what()}\". Contact the author for assistance.")
		return {"CANCELLED"}, None

	operator.report({'INFO'}, f"Export morph successful.")
	return {"FINISHED"}, verts_count

def ExportMorph_alt(options, context, export_file_path, operator, snapping_range = 0.0, snap_delta_positions = False):
	export_path = export_file_path

	target_obj = utils_blender.GetActiveObject()
	selected_objs = utils_blender.GetSelectedObjs(True)
	
	if IsMorphExportNode(target_obj):
		return ExportMorphFromSet(options, context, export_file_path, target_obj, operator)

	p_options = utils_primitive.Primitive.Options()
	p_options.gather_morph_data = True
	p_options.use_global_positions = options.use_world_origin
	
	new_obj = target_obj.copy()
	new_obj.data = target_obj.data.copy()
	bm = bmesh.new()
	bm.from_mesh(new_obj.data)
	bmesh.ops.triangulate(bm, faces=bm.faces[:])
	bm.to_mesh(new_obj.data)
	bm.free()

	time_start = time.time()

	primitive = utils_primitive.Primitive(new_obj, p_options)

	sel_primitives = []
	if snapping_range > 0:
		for select_obj in selected_objs:
			rtn, reason = utils_primitive.CheckForPrimitive(select_obj, gather_tangents=False)
			if not rtn:
				operator.report({'WARNING'}, f"Object {select_obj.name} is not a valid primitive for snapping. Reason: {reason}")
				continue

			sel_p_options = utils_primitive.Primitive.Options()
			sel_p_options.gather_morph_data = True
			sel_p_options.gather_tangents = False
			sel_p_options.use_global_positions = options.use_world_origin

			sel_primitive = utils_primitive.Primitive(select_obj, sel_p_options)
			sel_primitive.gather()
			sel_primitives.append(sel_primitive)

	try:
		primitive.gather()

		for sel_prim in sel_primitives:
			utils_primitive.CopyMorphNormalsAtSeam(primitive, sel_prim, snapping_range, snap_delta_positions=snap_delta_positions)

		jsondata = primitive.to_morph_numpy_dict()
	except utils_primitive.UVNotFoundException as e:
		operator.report({'WARNING'}, f"UVNotFoundException caught: {e}.")
		return {'CANCELLED'},  None
	except utils_primitive.AtomicException as e:
		operator.report({'WARNING'}, f"AtomicException caught: {e}.")
		return {'CANCELLED'},  None
	except Exception as e:
		print(e)
		operator.report({'WARNING'}, f"An error occurred during gathering morph data. Message: {e}")
		return {'CANCELLED'},  None

	time_end = time.time()

	#json_data = json.dumps(jsondata)

	time_end1 = time.time()

	#if utils_blender.is_plugin_debug_mode():
	#	debug_json_data = json.dumps(jsondata, indent=2)
	#	with open(export_path + ".json", 'w') as f:
	#		f.write(debug_json_data)

	returncode = MeshConverter.ExportMorphFromNumpy(jsondata, export_path)

	time_end2 = time.time()

	if not returncode:
		bpy.data.meshes.remove(new_obj.data)
		
		utils_blender.SetActiveObject(target_obj)

		operator.report({'INFO'}, f"Execution failed with error message: \"{returncode.what()}\". Contact the author for assistance.")
		return {"CANCELLED"}, None

	bpy.data.meshes.remove(new_obj.data)

	utils_blender.SetActiveObject(target_obj)

	operator.report({'INFO'}, f"Export morph successful. Time taken: Gather: {time_end - time_start:.2f}  + Dll: {time_end2 - time_end1:.2} seconds.")
	return {"FINISHED"}, jsondata['numVertices']

def ExportMorph(options, context, export_file_path, operator):
	export_path = export_file_path

	target_obj = utils_blender.GetActiveObject()
	s_objs = utils_blender.GetSelectedObjs(True)
	ref_obj = None

	if IsMorphExportNode(target_obj):
		return ExportMorphFromSet(options, context, export_file_path, target_obj, operator)

	if target_obj == None or target_obj.type != 'MESH':
		operator.report({'WARNING'}, f"Must select a mesh object or [MorphExport] node to export.")
		return {"CANCELLED"}, None

	if target_obj.data.shape_keys == None or target_obj.data.shape_keys.key_blocks == None:
		operator.report({'INFO'}, f"No enough shape keys to export. Exporting empty morph file.")
		target_obj, proxy_obj = utils_blender.PreprocessAndProxy(target_obj, options.use_world_origin, False, auto_add_sharp=options.auto_add_sharp)
		if target_obj == None:
			return {"CANCELLED"}, None

		verts_count = len(proxy_obj.data.vertices)
		
		returncode = MeshConverter.ExportEmptyMorphFromJson(verts_count, export_path)

		if not returncode:
			bpy.data.meshes.remove(proxy_obj.data)
			
			utils_blender.SetActiveObject(target_obj)

			operator.report({'INFO'}, f"Execution failed with error message: \"{returncode.what()}\". Contact the author for assistance.")
			return {"CANCELLED"}, None

		num_verts = len(proxy_obj.data.vertices)
		bpy.data.meshes.remove(proxy_obj.data)
		
		utils_blender.SetActiveObject(target_obj)

		operator.report({'INFO'}, f"Export morph successful.")
		return {"FINISHED"}, num_verts
	
	num_shape_keys = len(target_obj.data.shape_keys.key_blocks)
	#print(list(target_obj.data.shape_keys.key_blocks))
	key_blocks = target_obj.data.shape_keys.key_blocks
	if num_shape_keys < 2:
		operator.report({'INFO'}, f"No enough shape keys to export. Exporting empty morph file.")
		target_obj, proxy_obj = utils_blender.PreprocessAndProxy(target_obj, options.use_world_origin, False, auto_add_sharp=options.auto_add_sharp)
		if target_obj == None:
			return {"CANCELLED"}, None
		
		verts_count = len(proxy_obj.data.vertices)

		returncode = MeshConverter.ExportEmptyMorphFromJson(verts_count, export_path)

		if not returncode:
			bpy.data.meshes.remove(proxy_obj.data)
			
			utils_blender.SetActiveObject(target_obj)

			operator.report({'INFO'}, f"Execution failed with error message: \"{returncode.what()}\". Contact the author for assistance.")
			return {"CANCELLED"}, None

		num_verts = len(proxy_obj.data.vertices)
		bpy.data.meshes.remove(proxy_obj.data)
		
		utils_blender.SetActiveObject(target_obj)

		operator.report({'INFO'}, f"Export morph successful.")
		return {"FINISHED"}, num_verts
	
	if key_blocks[0].name != 'Basis':
		operator.report({'WARNING'}, f"The first shape key should always be the basis and named \'Basis\'.")
		return {"CANCELLED"}, None
	
	if len(s_objs) > 0:
		n_objs = []
		for s_obj in s_objs:
			s_obj, n_obj = utils_blender.PreprocessAndProxy(s_obj, False, False, auto_add_sharp=options.auto_add_sharp)
			if s_obj == None:
				return {"CANCELLED"}, None
			n_objs.append(n_obj)

		utils_blender.SetSelectObjects(n_objs)
		bpy.ops.object.join()
		ref_obj = utils_blender.GetActiveObject()
		bpy.ops.object.shade_smooth(use_auto_smooth=True)
	
	if ref_obj != None:
		if ref_obj.data.shape_keys == None or ref_obj.data.shape_keys.key_blocks == None:
			operator.report({'WARNING'}, f"Reference object has no shape keys.")
			return {"CANCELLED"}, None

		ref_num_shape_keys = len(ref_obj.data.shape_keys.key_blocks)
		print(list(ref_obj.data.shape_keys.key_blocks))
		ref_key_blocks = ref_obj.data.shape_keys.key_blocks
		
		if ref_num_shape_keys < num_shape_keys:
			operator.report({'WARNING'}, f"Reference objects don't have enough keys.")
			return {"CANCELLED"}, None
		else:
			key_mapping = [-1 for i in range(num_shape_keys)]
			for _key in key_blocks:
				_key_index = key_blocks.keys().index(_key.name)
				if _key.name not in ref_key_blocks:
					operator.report({'WARNING'}, f"Reference objects don't have some keys: {_key.name}")
					#return {"CANCELLED"}, None
				else:
					ref_key_index = ref_key_blocks.keys().index(_key.name)
					key_mapping[_key_index] = ref_key_index

			for ref_key in ref_key_blocks:
				ref_key.value = 0

	target_obj, proxy_obj = utils_blender.PreprocessAndProxy(target_obj, options.use_world_origin, False, auto_add_sharp=options.auto_add_sharp)
	if target_obj == None:
		return {"CANCELLED"}, None

	verts_count = len(proxy_obj.data.vertices)
	key_blocks = proxy_obj.data.shape_keys.key_blocks

	utils_blender.SmoothPerimeterNormal(proxy_obj, s_objs, True)

	if num_shape_keys != len(key_blocks):
		raise("Unknown Error")
	
	jsondata = {
		"numVertices": 0,
		"shapeKeys": [],
		"morphData": [],
	}

	jsondata["numVertices"] = verts_count
	jsondata["shapeKeys"] = [kb.name for kb in key_blocks[1:]]
	
	shape_keys = key_blocks[1:]
	original_shape_keys = target_obj.data.shape_keys.key_blocks[1:]

	for i in range(num_shape_keys - 1):
		jsondata["morphData"].append([])
		for j in range(jsondata["numVertices"]):
			jsondata["morphData"][i].append([0,0,0,[255,255,255],[],[]])
	
	Basis = key_blocks[0]
	
	for key in original_shape_keys:
		key.value = 0

	time_start = time.time()

	for n, sk in enumerate(shape_keys):
		for i in range(verts_count):
			jsondata["morphData"][n][i][0] = sk.data[i].co.x - Basis.data[i].co.x
			jsondata["morphData"][n][i][1] = sk.data[i].co.y - Basis.data[i].co.y
			jsondata["morphData"][n][i][2] = sk.data[i].co.z - Basis.data[i].co.z

	vid_lid_list = utils_blender.CalcVIdLIdlist(proxy_obj.data)

	basis_normals, basis_tangents, basis_tangentsigns = utils_blender.GetNormalTangents(proxy_obj.data, True, True, vid_lid_list)

	for n, cur_key in enumerate(original_shape_keys):
		shape_key_index = key_blocks.keys().index(cur_key.name)

		bpy.ops.object.mode_set(mode='EDIT')
		proxy_obj.active_shape_key_index = shape_key_index
		target_obj.active_shape_key_index = shape_key_index
		
		do_smooth_perimeter = True
		if ref_obj:
			active_sk_index = key_mapping[shape_key_index]
			if active_sk_index == -1:
				do_smooth_perimeter = False	
			else:
				ref_obj.active_shape_key_index = active_sk_index
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
		utils_blender.SetActiveObject(me_obj)
		bpy.ops.object.shade_smooth(use_auto_smooth=True)

		if do_smooth_perimeter:
			utils_blender.SmoothPerimeterNormal(me_obj, [ref_obj], True, target_obj, loop_mapping_base="NEAREST_POLYNOR")
		
		normals, tangents, _ = utils_blender.GetNormalTangents(me, True, True, vid_lid_list)

		d_N = utils_math.bounded_vector_substraction(basis_normals, normals)
		d_T = basis_tangentsigns[:, np.newaxis] * utils_math.bounded_vector_substraction(basis_tangents, tangents)

		for i in range(verts_count):
			jsondata["morphData"][n][i][3] = [255,255,255] # Target vert color
			jsondata["morphData"][n][i][4] = list(d_N[i])
			jsondata["morphData"][n][i][5] = list(d_T[i])

		bpy.data.meshes.remove(me)
		
		utils_blender.SetActiveObject(proxy_obj)
	
	if ref_obj:
		mesh = ref_obj.data
		bpy.data.objects.remove(ref_obj)
		bpy.data.meshes.remove(mesh)

	for key in original_shape_keys:
		key.value = 0

	target_obj.active_shape_key_index = 0

	json_data = json.dumps(jsondata)

	time_end = time.time()

	if utils_blender.is_plugin_debug_mode():
		debug_json_data = json.dumps(jsondata, indent=2)
		with open(export_path + ".json", 'w') as f:
			f.write(debug_json_data)

	returncode = MeshConverter.ExportMorphFromJson(json_data, export_path)

	time_end2 = time.time()

	if not returncode:
		bpy.data.meshes.remove(proxy_obj.data)
		
		utils_blender.SetActiveObject(target_obj)

		operator.report({'INFO'}, f"Execution failed with error message: \"{returncode.what()}\". Contact the author for assistance.")
		return {"CANCELLED"}, None

	num_verts = len(proxy_obj.data.vertices)
	bpy.data.meshes.remove(proxy_obj.data)
	
	utils_blender.SetActiveObject(target_obj)

	operator.report({'INFO'}, f"Export morph successful. Time taken: {time_end - time_start:.2f}/{time_end2 - time_end:.2} seconds.")
	return {"FINISHED"}, num_verts

def CreateMorphObjSetDefault(options, context, basis_obj, target_objs: list, operator):
	basis_obj.shape_key_clear()

	sk_basis = basis_obj.shape_key_add(name = 'Basis', from_mix = False)
	sk_basis.interpolation = 'KEY_LINEAR'
	basis_obj.data.shape_keys.use_relative = True
	
	sk_names = ['Overweight', 'Thin', 'Strong']
	for sk_name in sk_names:
		sk = basis_obj.shape_key_add(name = sk_name, from_mix = False)
		sk.interpolation = 'KEY_LINEAR'
		sk.relative_key = sk_basis
		sk.slider_min = 0
		sk.slider_max = 1
	
def CreateMorphObjSet(options, context, basis_obj, ref_objs, target_objs: list, operator):
	ref_obj = None

	if basis_obj == None:
		operator.report({'WARNING'}, f"Must select an object to export.")
		return {"CANCELLED"}
	
	if basis_obj.data.shape_keys == None or basis_obj.data.shape_keys.key_blocks == None:
		operator.report({'WARNING'}, f"No enough shape keys. Using default preset.")
		CreateMorphObjSetDefault(options, context, basis_obj, target_objs, operator)

	num_shape_keys = len(basis_obj.data.shape_keys.key_blocks)
	original_shape_keys = basis_obj.data.shape_keys.key_blocks
	if num_shape_keys < 2:
		operator.report({'WARNING'}, f"No enough shape keys. Using default preset.")
		CreateMorphObjSetDefault(options, context, basis_obj, target_objs, operator)
	
	num_shape_keys = len(basis_obj.data.shape_keys.key_blocks)
	original_shape_keys = basis_obj.data.shape_keys.key_blocks

	if original_shape_keys[0].name != 'Basis':
		operator.report({'WARNING'}, f"The first shape key should always be the basis and named \'Basis\'.")
		return {"CANCELLED"}

	if len(ref_objs) > 0:
		n_objs = []
		for s_obj in ref_objs:
			s_obj, n_obj = utils_blender.PreprocessAndProxy(s_obj, False, False, auto_add_sharp=options.auto_add_sharp)
			if s_obj == None:
				return {"CANCELLED"}
			n_objs.append(n_obj)

		utils_blender.SetSelectObjects(n_objs)
		bpy.ops.object.join()
		ref_obj = utils_blender.GetActiveObject()
		bpy.ops.object.shade_smooth(use_auto_smooth=True)

	if ref_obj != None:
		if ref_obj.data.shape_keys == None or ref_obj.data.shape_keys.key_blocks == None:
			operator.report({'WARNING'}, f"Reference object has no shape keys.")
			return {"CANCELLED"}

		ref_num_shape_keys = len(ref_obj.data.shape_keys.key_blocks)
		print(list(ref_obj.data.shape_keys.key_blocks))
		ref_key_blocks = ref_obj.data.shape_keys.key_blocks
		
		if ref_num_shape_keys < num_shape_keys:
			operator.report({'WARNING'}, f"Reference objects don't have enough keys.")
			return {"CANCELLED"}
		else:
			key_mapping = [-1 for i in range(num_shape_keys)]
			for _key in original_shape_keys:
				_key_index = original_shape_keys.keys().index(_key.name)
				ref_key_index = original_shape_keys.keys().index(_key.name)
				if ref_key_index == -1:
					operator.report({'WARNING'}, f"Reference objects don't have some keys: {_key.name}")
					return {"CANCELLED"}
				key_mapping[_key_index] = ref_key_index

			for ref_key in ref_key_blocks:
				ref_key.value = 0

	prev_coll = bpy.data.collections.new('morphs_' + basis_obj.name)
	bpy.context.scene.collection.children.link(prev_coll)
	
	morph_node = bpy.data.objects.new('[MorphExport]' + basis_obj.name, None, )
	morph_node.empty_display_size = 0.015

	utils_blender.move_object_to_collection([morph_node], prev_coll)
	utils_blender.move_object_to_parent([morph_node], basis_obj)

	basis_obj, proxy_basis_obj = utils_blender.PreprocessAndProxy(basis_obj, False, False, False, auto_add_sharp=options.auto_add_sharp)
	
	if basis_obj == None:
		return {"CANCELLED"}
	
	proxy_basis_obj.name = "[Proxy]" + basis_obj.name

	verts_count = len(proxy_basis_obj.data.vertices)
	key_blocks = proxy_basis_obj.data.shape_keys.key_blocks

	if num_shape_keys != len(key_blocks):
		raise("Unknown Error")
	
	Basis = key_blocks[0]
	ShapeKeys = key_blocks[1:]
	
	target_objs.clear()
	for n, cur_key in enumerate(original_shape_keys):
		if cur_key.mute:
			continue
		
		shape_key_index = key_blocks.keys().index(cur_key.name)

		bpy.ops.object.mode_set(mode='EDIT')
		proxy_basis_obj.active_shape_key_index = shape_key_index
		basis_obj.active_shape_key_index = shape_key_index
		if ref_obj:
			ref_obj.active_shape_key_index = key_mapping[shape_key_index]
			for key in ref_key_blocks:
				key.value = 0
			ref_key_blocks[cur_key.name].value = 1

		for key in original_shape_keys:
			key.value = 0
		cur_key.value = 1

		bm = bmesh.from_edit_mesh(proxy_basis_obj.data)
		me = bpy.data.meshes.new("mesh")
		me_obj = bpy.data.objects.new(f"[{cur_key.name}]"+basis_obj.name, me)  # add a new object using the mesh
		bpy.context.collection.objects.link(me_obj)
		bm.to_mesh(me)
		bm.free()
		
		bpy.ops.object.mode_set(mode='OBJECT')
		utils_blender.SetActiveObject(me_obj)
		bpy.ops.object.shade_smooth(use_auto_smooth=True)
		utils_blender.move_object_to_collection([me_obj], prev_coll)
		utils_blender.move_object_to_parent([me_obj], morph_node)

		utils_blender.SmoothPerimeterNormal(me_obj, [ref_obj], True, basis_obj)
		
		utils_blender.SetActiveObject(proxy_basis_obj)
		target_objs.append(me_obj)

	# Clean up
	for key in original_shape_keys:
		key.value = 0
	bpy.data.meshes.remove(proxy_basis_obj.data)
	if ref_obj:
		mesh = ref_obj.data
		bpy.data.objects.remove(ref_obj)
		bpy.data.meshes.remove(mesh)

	operator.report({'INFO'}, f"Operation successful.")
	return {'FINISHED'}