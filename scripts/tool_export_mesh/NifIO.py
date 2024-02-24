import os
import json
import bpy
import mathutils

import MeshIO
import MorphIO
import utils_blender
import utils_material
import nif_armature
import nif_template
import utils_common as utils
import MeshConverter
import PhysicsConverter
import MaterialConverter

skeleton_obj_dict = {}

def ResetSkeletonObjDict():
	skeleton_obj_dict.clear()

def GetSkeletonObjDict():
	return skeleton_obj_dict

def TraverseNodeRecursive(armature_dict:dict, parent_node, collection, root_dict, options, additional_assets_folder, context, operator, nif_name = '', connect_pts = {}):
	_objects = []
	is_node = False
	is_rigged = False
	connect_point_nodes = []
	if (armature_dict["geometry_index"] != 4294967295):
		data = root_dict["geometries"][armature_dict["geometry_index"]]
		geo_name = armature_dict['name']
		material = bpy.data.materials.new(name=data['mat_path'])
		loaded = False

		lod = 0
		for mesh_info in data['geo_mesh_lod']:
			if options.max_lod != 0 and lod == options.max_lod:
				break

			factory_path = mesh_info['factory_path']
			if factory_path.endswith(".mesh"):
				factory_path = factory_path[:-5]

			mesh_filepath = os.path.join(options.assets_folder, 'geometries', factory_path + '.mesh')
			if os.path.isfile(mesh_filepath) == False:
				for additional_folder in additional_assets_folder:
					mesh_filepath = os.path.join(additional_folder, 'geometries', factory_path + '.mesh')
					if os.path.isfile(mesh_filepath):
						break
			
			lod += 1
			if os.path.isfile(mesh_filepath):
				rtn = MeshIO.ImportMesh(mesh_filepath, options, context, operator, factory_path)
				
				if 'FINISHED' in rtn:
					imported_obj = utils_blender.GetActiveObject()
					_objects.append(imported_obj)
					_objects[-1].name = geo_name
					if options.max_lod > 1:
						_objects[-1].name += f'_lod{lod}'
					imported_obj.data.materials.append(material)
					loaded = True
				else:
					operator.report({'WARNING'}, f'{factory_path}.mesh cannot be loaded.')
			else:
				operator.report({'WARNING'}, f'{mesh_filepath} doesn\'t exist. Please make sure you have the geometry files as loose files.')
		
		if options.geo_bounding_debug:
			bound_sphere = data["geo_bounding_sphere"]
			bound_center = data["geo_bounding_center"]
			bound_expand = data["geo_bounding_expand"]
			bounding_name = geo_name+'_bounding'
			
			box_obj = utils_blender.BoxFromCenterExpand(bounding_name, bound_center, bound_expand)
			sphere_obj = utils_blender.SphereFromCenterRadius(bounding_name+'_sphere', bound_sphere[:3], bound_sphere[3])
			box_obj.display_type = 'BOUNDS'
			_objects.append(box_obj)
			_objects.append(sphere_obj)
		
		if loaded == False:
			operator.report({'WARNING'}, f'No mesh was loaded for {geo_name}.')

		if 'has_skin' in data.keys() and data['has_skin'] == True:
			is_rigged = True
			for obj in _objects:
				suc = utils_blender.SetWeightKeys(obj, utils_blender.RenamingBoneList(data['bone_names']))

				if suc == False:
					operator.report({'WARNING'}, f'Number of vertex groups in mesh doesn\'t match with bone list in nif.')

			if options.skeleton_name == ' ':
				skeleton, matched_bones = nif_armature.MatchSkeletonAdvanced(data['bone_names'], geo_name +' '+ nif_name)
			else:
				skeleton, matched_bones = nif_armature.MatchSkeletonAdvanced(data['bone_names'], options.skeleton_name, True)

			if skeleton == None:
				operator.report({'WARNING'},f'Unable to find a matched skeleton for {geo_name}. Skipping...')
			
			else:
				operator.report({'INFO'},f'{geo_name} matched with skeleton {skeleton}')
				if options.boneinfo_debug:
					debug_capsule = {}
					for bonename, boneinfo in zip(data['bone_names'], data['bone_infos']):
						debug_capsule[bonename] = boneinfo
					
					nif_armature.ImportArmatureFromJson(skeleton, collection, _objects, geo_name, debug_capsule)

					for bonename, boneinfo in debug_capsule.items():
						bpy.ops.mesh.primitive_uv_sphere_add(radius=boneinfo['radius'], location=boneinfo['world_center'])
						bpy.context.object.display_type = 'BOUNDS'
						bpy.context.object.display_bounds_type = 'SPHERE'
						bpy.context.object.show_bounds = True
						bpy.context.object.name = f"Capsule_{bonename}"

				else:
					if skeleton in skeleton_obj_dict.keys():
						skeleton_obj_dict[skeleton].extend(_objects)
					else:
						skeleton_obj_dict[skeleton] = _objects

	else:
		is_node = True
		node_name = armature_dict['name']
		Axis = bpy.data.objects.new(node_name, None, )
		Axis.empty_display_type = 'ARROWS'
		Axis.show_name = True
		Axis.empty_display_size = 0.015
		_objects.append(Axis)

	if armature_dict['name'] in connect_pts.keys():
		for cp in connect_pts[armature_dict['name']]:
			cp_obj = bpy.data.objects.new("CPA:" + cp['child_name'], None)
			cp_obj.empty_display_type = 'ARROWS'
			cp_obj.show_name = True
			cp_obj.empty_display_size = 0.015
			connect_point_nodes.append(cp_obj)
		utils_blender.move_object_to_collection(connect_point_nodes, collection.children['ConnectPoint:Parents'])

	utils_blender.move_object_to_collection(_objects, collection)
	for obj in _objects:
		if parent_node != None:
			obj.parent = parent_node
		T = mathutils.Matrix()
		for i in range(4):
			for j in range(4):
				T[i][j] = armature_dict['matrix'][i][j]
		
		obj.matrix_world = T
		scale = armature_dict['scale']
		obj.scale = tuple([scale,scale,scale])

		for cp_obj in connect_point_nodes:
			cp_obj.location = cp['translation']
			cp_obj.rotation_quaternion = cp['rot_quat']
			cp_scale = cp['scale']
			cp_obj.scale = tuple([cp_scale,cp_scale,cp_scale])
			cp_obj.parent = obj
	
	if options.correct_rotation and is_node == False and is_rigged and skeleton != None:
		skeleton_info = nif_armature.SkeletonLookup(skeleton)

		for mesh_obj in _objects:
			
			correction = None

			for _bonename, _boneinfo in zip(data['bone_names'], data['bone_infos']):
				if _bonename in matched_bones:
					B_inv = mathutils.Matrix()
					for i in range(4):
						for j in range(4):
							B_inv[i][j] = _boneinfo['matrix'][i][j]
					
					B = mathutils.Matrix()
					for i in range(4):
						for j in range(4):
							B[i][j] = skeleton_info[_bonename]['matrix'][i][j]

					correction = B @ B_inv
					break
			
			if correction == None:
				operator.report({'WARNING'}, f'Failed to correct mesh for {geo_name}')
			else:
				mesh_obj.matrix_world = correction
			#axis, angle = correction.to_quaternion().to_axis_angle()
			#angle_integer = angle * 2 / math.pi
			#corrected = mathutils.Quaternion([round(axis[0]), round(axis[1]), round(axis[2])], round(angle_integer) * math.pi * 0.5).to_matrix()
			
			#mesh_obj.matrix_world = mathutils.Matrix.Identity(4)
			#for j in range(3):
			#	for k in range(3):
			#		mesh_obj.matrix_world[j][k] = corrected[j][k]
			
			#for j in range(3):
			#	mesh_obj.matrix_world[j][3] = pivot['matrix'][j][3]

	for child_dict in armature_dict['children']:
		TraverseNodeRecursive(child_dict, Axis, collection, root_dict, options, additional_assets_folder, context, operator, nif_name, connect_pts)


def ImportNif(file_path, options, context, operator):
	nif_armature.LoadAllSkeletonLookup()
	ResetSkeletonObjDict()
	assets_folder = options.assets_folder
	nifname = os.path.basename(file_path)
	additional_assets_folders = utils.ParentDirIfExsit(file_path, 6)
	nif_folder_name = os.path.basename(os.path.dirname(file_path))

	if assets_folder == utils.default_assets_folder:
		operator.report({'WARNING'}, 'Setup your assets folder before importing!')
		return {'CANCELLED'}, None, None
	
	json_str = MeshConverter.ImportNifAsJson(file_path, utils_blender.is_plugin_debug_mode(), os.path.join(utils.export_mesh_folder_path, 'havok_debug.txt'))
	
	if len(json_str) == 0:
		operator.report({'WARNING'}, f'Nif failed to load.')
		return {'CANCELLED'}, None, None
	
	_data = json.loads(json_str)

	prev_coll = bpy.data.collections.new(nifname)
	bpy.context.scene.collection.children.link(prev_coll)

	connect_pts = {}
	if "connection_points_p" in _data.keys():
		for cp in _data["connection_points_p"]:
			parent_name = cp["parent_name"]
			if parent_name == "":
				parent_name = _data['name']
			if parent_name not in connect_pts.keys():
				connect_pts[parent_name] = [cp]
			else:
				connect_pts[parent_name].append(cp)
		cpa_coll = bpy.data.collections.new("ConnectPoint:Parents")
		prev_coll.children.link(cpa_coll)
	#print(connect_pts)
	# Save the JSON data to a file
	#with open(utils.export_mesh_folder_path + '/nifDebug.json', 'w') as json_file:
	#	json.dump(_data, json_file, indent = 4)

	# Save the JSON str to a file
	#with open(utils.export_mesh_folder_path + '/nifDebugStr.json', 'w') as json_file:
	#	json_file.write(json_str)

	if "geometries" not in _data.keys():
		
		if options.skeleton_register_name != "":
			nif_armature.RegisterSkeleton(options.skeleton_register_name, _data)

		nif_armature.CreateArmature(_data, None, prev_coll, "Armature")
		operator.report({'INFO'}, f'Nif has no geometry. Loaded as Armature.')
		return {'FINISHED'}, None, None
	else:
		TraverseNodeRecursive(_data, None, prev_coll, _data, options, additional_assets_folders, context, operator, nifname + ' ' + nif_folder_name, connect_pts)

	operator.report({'INFO'}, f'Meshes loaded for {nifname}.')
	
	# Majority vote
	best_skel = "skeleton_female"
	obj_list = []
	max_obj = 0
	for skel, objs in skeleton_obj_dict.items():
		obj_list.extend(objs)
		if len(objs) > max_obj:
			max_obj = len(objs)
			best_skel = skel
	print(best_skel, obj_list)

	# Havok skeleton
	if options.debug_havok_physics and'havok_skeleton' in _data.keys():
		havok_skel = _data['havok_skeleton']
		skel_coll = bpy.data.collections.new("HavokSkeleton")
		bpy.context.scene.collection.children.link(skel_coll)
		hkaSkele = nif_armature.CreateArmature(havok_skel, obj_list, skel_coll, "hkaSkeleton")
		best_skel = None
		obj_list = []
		
		# DEBUG: Save the JSON data to a file
		#with open(utils.export_mesh_folder_path + '/hkaSkeletonDebug.json', 'w') as json_file:
		#	json.dump(_data['havok_skeleton'], json_file, indent = 4)

		if options.debug_havok_physics and 'havok_meshes' in _data.keys():
			havok_meshes = _data['havok_meshes']
			havok_vis_objs = []
			for mesh in havok_meshes:
				havok_vis_objs.extend(utils_blender.BuildhkBufferedMesh(mesh, hkaSkele))
			havok_vis_objs = [obj for obj in havok_vis_objs if obj != None]
			sim_mesh_obj = None
			pn_operator = None
			for vis_obj in havok_vis_objs:
				if vis_obj.name.find('hclSimClothData') != -1:
					sim_mesh_obj = vis_obj
				elif vis_obj.name.find('SkinPNOperator') != -1:
					pn_operator = vis_obj
			
			utils_blender.TransferWeightByDistance(sim_mesh_obj, pn_operator)

			hk_coll = utils_blender.new_collection("HavokPhysics")
			utils_blender.move_object_to_collection(havok_vis_objs, hk_coll)


	return {'FINISHED'}, best_skel, obj_list

def ExportNif(options, context, operator):
	nif_armature.LoadAllSkeletonLookup()
	original_selected = utils_blender.GetSelectedObjs(True)
	nif_filepath = options.filepath
	export_folder = os.path.dirname(nif_filepath)
	nif_filename = os.path.basename(nif_filepath)
	nif_name = os.path.splitext(nif_filename)[0]
	hash_filepath = options.export_sf_mesh_hash_result
	options.export_sf_mesh_hash_result = False
	options.use_world_origin = False
	has_physics_graph = options.physics_tree != "None" and options.physics_tree in bpy.data.node_groups
	if has_physics_graph:
		physics_graph = bpy.data.node_groups[options.physics_tree]
	custom_armature_attached = False
	physics_armature_attached = False
	has_skinned_geometry = False

	export_material = options.export_material
	if export_material:
		mat_folder = os.path.join(export_folder, 'Materials')
		texconv_path = utils_blender.get_texconv_path()
		if texconv_path is None:
			operator.report({'WARNING'}, 'Texconv path is not set. Please set it in the preferences.')
			export_material = False

	root = utils_blender.GetActiveObject()
	if root.type not in ['EMPTY','MESH', 'ARMATURE']:
		operator.report({'WARNING'}, f'Must select an empty object as Root Node or a mesh object as BSGeometry or an armature object as Skeleton.')
		return {'CANCELLED'}

	geometries = []
	mode = "MULTI_MESH"
	connect_pts = []
	recur_bone_list = []
	if root.type == 'EMPTY':
		mode = "MULTI_MESH"
		_data = nif_template.RootNodeTemplate(root, geometries, connect_pts)
	elif root.type == 'MESH':
		mode = "SINGLE_MESH"
		_data = nif_template.SingleClothTemplate(root, geometries, connect_pts)
	elif root.type == 'ARMATURE':
		mode = "SINGLE_MESH"
		_data = nif_template.NifArmatureTemplate(root, recur_bone_list)
		if len(recur_bone_list) != len(root.data.bones):
			operator.report({'WARNING'}, f'You have bogus bones in the skeleton!')
			return {'CANCELLED'}
		_data['sub_template'] = 2

	_data['geometries'] = []

	for mesh_obj in geometries:
		if mesh_obj.data == None:
			operator.report({'WARNING'}, f'Object {mesh_obj.name} has no mesh. Skipping...')
			continue

		mesh_data = {}
		mesh_data['geo_mesh_lod'] = []

		if mesh_obj.data.materials and len(mesh_obj.data.materials) > 0 and mesh_obj.data.materials[0]:
			mat = mesh_obj.data.materials[0]
			mat_path = mat.name
			if export_material and utils_material.is_mat(mat):
				sub_folder_name = utils.sanitize_filename(mesh_obj.name)
				mesh_obj_mat_folder = os.path.join(mat_folder, nif_name, sub_folder_name)
				tex_relfolder = os.path.join('Textures', nif_name, sub_folder_name)
				rtn, mat_path = MaterialConverter.ExportMatFromMaterial(mat, operator, mesh_obj_mat_folder, export_folder, tex_relfolder, texconv_path)
				mat_path = os.path.relpath(mat_path, export_folder)
				if 'FINISHED' in rtn:
					operator.report({'INFO'}, f'Material export for {mesh_obj.name} successful.')
				else:
					operator.report({'WARNING'}, f'Material export for {mesh_obj.name} failed.')

			mesh_data['mat_path'] = mat_path
		else:
			mesh_data['mat_path'] = 'MATERIAL_PATH'

		bbox_center, bbox_expand = utils_blender.GetObjBBoxCenterExpand(mesh_obj)
		mesh_data["geo_bounding_center"] = bbox_center
		mesh_data["geo_bounding_expand"] = bbox_expand

		mesh_lod_info = {}
		utils_blender.SetActiveObject(mesh_obj)

		vertex_groups = mesh_obj.vertex_groups
		vgrp_names = [vg.name for vg in vertex_groups]

		skeleton_info = None
		bone_list_filter = None
		if len(vgrp_names) > 0 and options.WEIGHTS:
			armatures = [m.object for m in mesh_obj.modifiers if m.type == 'ARMATURE' and m.object is not None]

			if len(armatures) == 0:
				operator.report({'WARNING'}, f'Object {mesh_obj.name} has no valid armature modifier. Searching in database for skeleton...')
				armature_name, bone_list_filter = nif_armature.MatchSkeletonAdvanced(vgrp_names, mesh_obj.name + ' ' + mesh_obj.data.name)
				if armature_name != None:
					skeleton_info = nif_armature.SkeletonLookup(armature_name)
			else:
				skeleton_info = {}
				armature = armatures[0]
				utils_blender.SetSelectObjects([])
				utils_blender.SetActiveObject(armature)
				bpy.ops.object.mode_set(mode='EDIT', toggle=False)
				for bone in armature.data.edit_bones:
					info = {}
					info['matrix'] = nif_armature.BoneAxisCorrectionRevert(bone.matrix)
					info['scale'] = 1
					skeleton_info[bone.name] = info
				
				bone_list_filter = list(set(skeleton_info.keys()) & set(vgrp_names))
				bpy.ops.object.mode_set(mode='OBJECT', toggle=False)
				if has_physics_graph:
					custom_armature_attached = True
					if armature == physics_graph.skeleton:
						physics_armature_attached = True
			#bone_list_filter = list(set(bone_list_filter) | set(cloth_bones))

		if hash_filepath:
			mesh_folder, mesh_name = utils.hash_string(mesh_obj.name)
			factory_name = mesh_folder + '\\' + mesh_name
		else:
			mesh_folder = utils.sanitize_filename(mesh_obj.name)
			if mesh_obj.data.name.endswith('.mesh'):
				mesh_name = utils.sanitize_filename(mesh_obj.data.name[:-5])
			else:
				mesh_name = utils.sanitize_filename(mesh_obj.data.name)
			factory_name = mesh_folder + '\\' + mesh_name + ".mesh"

		result_file_folder = os.path.join(export_folder, 'geometries', mesh_folder)
		os.makedirs(result_file_folder, exist_ok = True)
		result_file_path = os.path.join(result_file_folder, mesh_name + ".mesh")

		if mode == "SINGLE_MESH":
			utils_blender.SetSelectObjects(original_selected)
			utils_blender.SetActiveObject(mesh_obj)
		else:
			utils_blender.SetSelectObjects([])
			utils_blender.SetActiveObject(mesh_obj)
		rtn, verts_count, indices_count, bone_list = MeshIO.ExportMesh(options, context, result_file_path, operator, bone_list_filter, True)
		
		if 'FINISHED' not in rtn:
			operator.report({'WARNING'}, f'Failed exporting {mesh_obj.name}. Skipping...')
			continue

		has_skinned_geometry = True
		
		if options.export_morph:
			if mode == "SINGLE_MESH":
				result_morph_folder = os.path.join(export_folder, 'meshes', 'morphs', mesh_folder, mesh_name)
				os.makedirs(result_morph_folder, exist_ok = True)
				result_morph_path = os.path.join(result_morph_folder, "morph.dat")

				utils_blender.SetSelectObjects(original_selected)
				utils_blender.SetActiveObject(mesh_obj)

				morph_success = MorphIO.ExportMorph(options, context, result_morph_path, operator)

				if 'FINISHED' in morph_success:
					operator.report({'INFO'}, f"Morph export for {mesh_obj.name} successful.")
				else:
					operator.report({'WARNING'}, f"Morph export for {mesh_obj.name} failed.")
			else:
				operator.report({'WARNING'}, f'Morph export for multiple geometries in one nif is not supported!')

		mesh_lod_info['factory_path'] = factory_name
		mesh_lod_info['num_indices'] = indices_count
		mesh_lod_info['num_vertices'] = verts_count

		mesh_data['geo_mesh_lod'].append(mesh_lod_info)

		if bone_list != None and len(bone_list) > 0 and skeleton_info != None:
			mesh_data['has_skin'] = 1
			mesh_data['bone_names'] = utils_blender.RevertRenamingBoneList(bone_list)
			mesh_data['bone_infos'] = []

			#pivot = mathutils.Matrix.Identity(4)
			#for j in range(3):
			#	pivot[j][3] = mesh_obj.matrix_local[j][3]

			for bone_name in bone_list:
				bone_info = {}
				B_inv = skeleton_info[bone_name]['matrix'].inverted()

				V = B_inv @ mesh_obj.matrix_local # Or 'matrix_world' idk

				bone_info['matrix'] = [[V[i][j] for j in range(4)]for i in range(4)]
				bone_info['scale'] = 1 / skeleton_info[bone_name]['scale']
				mesh_data['bone_infos'].append(bone_info)


		_data["geometries"].append(mesh_data)

	_data['skeleton_mode'] = False
	_data['auto_detect'] = True

	for cp in connect_pts:
		if cp['parent_name'] == _data['name']:
			cp['parent_name'] = ''

	_data['connection_points_p'] = connect_pts

	if has_physics_graph:
		if not has_skinned_geometry or not physics_armature_attached:
			operator.report({'WARNING'}, f'Nif export doesn\'t have a skinned mesh that is weighted to the very same skeleton in Physics Editor. Physics data will be ignored.')
		else:
			physics_data, error_msg = PhysicsConverter.get_physics_data(physics_graph)
			if physics_data != None:
				_data['physics_data'] = physics_data
				_data['transcript_path'] = MeshConverter.GetTranscriptPath()
			else:
				operator.report({'WARNING'}, error_msg)
	#print(_data)
	json_data = json.dumps(_data)

	# Write the JSON data to a file
	if utils_blender.is_plugin_debug_mode():
		with open(nif_filepath + '.json', 'w') as json_file:
			json_file.write(json_data)

	returncode = MeshConverter.CreateNifFromJson(json_data, nif_filepath, export_folder)

	if not returncode:
		operator.report({'INFO'}, f"Execution failed with error message: \"{returncode.what()}\". Contact the author for assistance.")
		return {'CANCELLED'}

	operator.report({'INFO'},f'Export Nif successful.')
	return {'FINISHED'}
