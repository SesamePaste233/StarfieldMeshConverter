import bpy
import os
import bmesh
import json

from utils_blender import GetActiveObject, SetActiveObject, GetSelectedObjs, SetSelectObjects

from utils_blender import read_only_marker

from utils_blender import PreprocessAndProxy, SmoothPerimeterNormal, GetNormalTangents, VisualizeVectors

from MeshConverter import _dll_export_morph, _dll_import_morph

def ImportMorph(options, context, operator):
	import_path = options.filepath
	
	rtn = _dll_import_morph(import_path.encode('utf-8')).decode('utf-8')

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
		normals, tangents, signs = GetNormalTangents(target_obj.data, True)
		
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
			VisualizeVectors(target_obj.data, offsets, [[n[0] + s * dn[0], n[1] + s * dn[1], n[2] + s * dn[2]] for n, dn, s in zip(tangents, delta_tangents, signs)], key_name)

	operator.report({'INFO'}, f"Import Morph Successful.")
	return {'FINISHED'}
	
def ExportMorph(options, context, export_file_path, operator):
	export_path = export_file_path

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
		return {"CANCELLED"}

	if target_obj.data.shape_keys == None or target_obj.data.shape_keys.key_blocks == None:
		operator.report({'WARNING'}, f"Object has no shape keys.")
		return {"CANCELLED"}

	num_shape_keys = len(target_obj.data.shape_keys.key_blocks)
	print(list(target_obj.data.shape_keys.key_blocks))
	key_blocks = target_obj.data.shape_keys.key_blocks
	if num_shape_keys < 2:
		operator.report({'WARNING'}, f"No enough shape keys to export.")
		return {"CANCELLED"}
	
	if key_blocks[0].name != 'Basis':
		operator.report({'WARNING'}, f"The first shape key should always be the basis and named \'Basis\'.")
		return {"CANCELLED"}
	
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
			for _key in key_blocks:
				_key_index = key_blocks.keys().index(_key.name)
				ref_key_index = ref_key_blocks.keys().index(_key.name)
				if ref_key_index == -1:
					operator.report({'WARNING'}, f"Reference objects don't have some keys: {_key.name}")
					return {"CANCELLED"}
				key_mapping[_key_index] = ref_key_index

			for ref_key in ref_key_blocks:
				ref_key.value = 0

	target_obj, proxy_obj = PreprocessAndProxy(target_obj, options.use_world_origin, False)

	verts_count = len(proxy_obj.data.vertices)
	key_blocks = proxy_obj.data.shape_keys.key_blocks

	SmoothPerimeterNormal(proxy_obj, s_objs, True)

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
			jsondata["morphData"][i].append([0,0,0,[],[]])
	
	Basis = key_blocks[0]
	
	for key in original_shape_keys:
		key.value = 0

	for n, sk in enumerate(shape_keys):
		for i in range(verts_count):
			jsondata["morphData"][n][i][0] = sk.data[i].co.x - Basis.data[i].co.x
			jsondata["morphData"][n][i][1] = sk.data[i].co.y - Basis.data[i].co.y
			jsondata["morphData"][n][i][2] = sk.data[i].co.z - Basis.data[i].co.z

	basis_normals, basis_tangents, basis_tangentsigns = GetNormalTangents(proxy_obj.data, True)

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

		normals, tangents, _ = GetNormalTangents(me, True)

		for i in range(verts_count):
			jsondata["morphData"][n][i][3] = list(normals[i] - basis_normals[i])
			jsondata["morphData"][n][i][4] = list(basis_tangentsigns[i] * (tangents[i] - basis_tangents[i]))

		bpy.data.meshes.remove(me)
		
		SetActiveObject(proxy_obj)
	
	if ref_obj:
		mesh = ref_obj.data
		bpy.data.objects.remove(ref_obj)
		bpy.data.meshes.remove(mesh)

	for key in original_shape_keys:
		key.value = 0

	target_obj.active_shape_key_index = 0

	json_data = json.dumps(jsondata)

	returncode = _dll_export_morph(json_data.encode(), export_path.encode())

	if returncode != 0:
		bpy.data.meshes.remove(proxy_obj.data)
		
		SetActiveObject(target_obj)

		operator.report({'INFO'}, f"Execution failed with return code {returncode}. Contact the author for assistance.")
		return {"CANCELLED"}

	bpy.data.meshes.remove(proxy_obj.data)
	
	SetActiveObject(target_obj)

	operator.report({'INFO'}, f"Export morph successful.")
	return {"FINISHED"}
