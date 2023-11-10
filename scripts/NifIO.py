import os
import json
import bpy
import mathutils
import math

from MeshIO import ImportMesh, ExportMesh

from utils_blender import GetActiveObject, SetActiveObject, SetSelectObjects, SetWeightKeys, move_object_to_collection, PluginAssetsFolderPath

from nif_armature import MatchSkeletonAdvanced, ImportArmatureFromJson, LoadAllSkeletonLookup, CreateArmature, SkeletonLookup, BoneAxisCorrectionRevert, GetPivotInfo, RegisterSkeleton

from nif_template import RootNodeTemplate, SingleClothTemplate

from utils import hash_string, sanitize_filename, default_assets_folder

from MeshConverter import _dll_export_nif, _dll_import_nif

skeleton_obj_dict = {}

def ResetSkeletonObjDict():
	skeleton_obj_dict.clear()

def GetSkeletonObjDict():
	return skeleton_obj_dict

def TraverseNodeRecursive(armature_dict:dict, parent_node, collection, root_dict, options, additional_assets_folder, context, operator, nif_name = ''):
	_objects = []
	is_node = False
	is_rigged = False
	if (armature_dict["geometry_index"] != 4294967295):
		data = root_dict["geometries"][armature_dict["geometry_index"]]
		geo_name = armature_dict['name']
		loaded = False

		lod = 0
		for mesh_info in data['geo_mesh_lod']:
			if options.max_lod != 0 and lod == options.max_lod:
				break

			factory_path = mesh_info['factory_path']

			mesh_filepath = os.path.join(options.assets_folder, 'geometries', factory_path + '.mesh')
			if os.path.isfile(mesh_filepath) == False:
				for additional_folder in additional_assets_folder:
					mesh_filepath = os.path.join(additional_folder, 'geometries', factory_path + '.mesh')
					if os.path.isfile(mesh_filepath):
						break
			
			lod += 1
			if os.path.isfile(mesh_filepath):
				rtn = ImportMesh(mesh_filepath, options, context, operator, factory_path)
				
				if 'FINISHED' in rtn:
					_objects.append(GetActiveObject())
					_objects[-1].name = geo_name + f'_LOD:{lod}'
					loaded = True
				else:
					operator.report({'WARNING'}, f'{factory_path}.mesh cannot be loaded.')
			else:
				operator.report({'WARNING'}, f'{mesh_filepath}.mesh doesn\'t exist. Please make sure you have the geometry files as loose files.')

		if loaded == False:
			operator.report({'WARNING'}, f'No mesh was loaded for {geo_name}.')

		if 'has_skin' in data.keys() and data['has_skin'] == True:
			is_rigged = True
			for obj in _objects:
				SetWeightKeys(obj, data['bone_names'])

			skeleton, matched_bones = MatchSkeletonAdvanced(data['bone_names'], geo_name +' '+ nif_name)
			if skeleton == None:
				operator.report({'WARNING'},f'Unable to find a matched skeleton for {geo_name}. Skipping...')
			
			else:
				operator.report({'INFO'},f'{geo_name} matched with skeleton {skeleton}')
				if options.boneinfo_debug:
					debug_capsule = {}
					for bonename, boneinfo in zip(data['bone_names'], data['bone_infos']):
						debug_capsule[bonename] = boneinfo
					
					ImportArmatureFromJson(skeleton, collection, _objects, geo_name, debug_capsule)

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
		Axis = bpy.data.objects.new(armature_dict['name'], None, )
		Axis.empty_display_type = 'ARROWS'
		Axis.show_name = True
		Axis.empty_display_size = 0.015
		_objects.append(Axis)

	move_object_to_collection(_objects, collection)
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
	
	if options.correct_rotation and is_node == False and is_rigged and skeleton != None:
		skeleton_info = SkeletonLookup(skeleton)

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
		TraverseNodeRecursive(child_dict, Axis, collection, root_dict, options, additional_assets_folder, context, operator, nif_name)


def ImportNif(file_path, options, context, operator):
	LoadAllSkeletonLookup()
	ResetSkeletonObjDict()
	assets_folder = options.assets_folder
	nifname = os.path.basename(file_path)
	additional_assets_folder = os.path.dirname(file_path)
	
	if assets_folder == default_assets_folder:
		operator.report({'WARNING'}, 'Setup your assets folder before importing!')
		return {'CANCELLED'}, None, None
	
	json_str = _dll_import_nif(file_path.encode('utf-8')).decode('utf-8')
	
	if len(json_str) == 0:
		operator.report({'WARNING'}, f'Nif failed to load.')
		return {'CANCELLED'}, None, None
	
	_data = json.loads(json_str)

	prev_coll = bpy.data.collections.new(nifname)
	bpy.context.scene.collection.children.link(prev_coll)

	if "geometries" not in _data.keys():
		
		if options.skeleton_register_name != "":
			RegisterSkeleton(options.skeleton_register_name, _data)

		CreateArmature(_data, None, prev_coll, "Armature")
		operator.report({'INFO'}, f'Nif has no geometry. Loaded as Armature.')
		return {'FINISHED'}, None, None
	else:
		TraverseNodeRecursive(_data, None, prev_coll, _data, options, [additional_assets_folder], context, operator, nifname)

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

	return {'FINISHED'}, best_skel, obj_list

def ExportNif(options, context, operator):
	LoadAllSkeletonLookup()
	nif_filepath = options.filepath
	export_folder = os.path.dirname(nif_filepath)
	hash_filepath = options.export_sf_mesh_hash_result
	options.export_sf_mesh_hash_result = False
	options.use_world_origin = False

	if options.export_template == 'None':
		root = GetActiveObject()
		if root.type != 'EMPTY':
			if root.type != 'MESH':
				operator.report({'WARNING'}, f'Must select an empty object as Root Node or a mesh object as BSGeometry.')
				return {'CANCELLED'}

		geometries = []
		if root.type == 'EMPTY':
			_data = RootNodeTemplate(root, geometries)
		elif root.type == 'MESH':
			_data = SingleClothTemplate(root, geometries)
		
		print(_data, geometries)

		_data['geometries'] = []

		for mesh_obj in geometries:
			if mesh_obj.data == None:
				operator.report({'WARNING'}, f'Object {mesh_obj.name} has no mesh. Skipping...')
				continue

			mesh_data = {}
			mesh_data['geo_mesh_lod'] = []
			mesh_lod_info = {}
			SetActiveObject(mesh_obj)

			vertex_groups = mesh_obj.vertex_groups
			vgrp_names = [vg.name for vg in vertex_groups]

			skeleton_info = None
			bone_list_filter = None
			if len(vgrp_names) > 0 and options.WEIGHTS:
				armatures = [m.object for m in mesh_obj.modifiers if m.type == 'ARMATURE']

				if len(armatures) == 0:
					armature_name, bone_list_filter = MatchSkeletonAdvanced(vgrp_names, mesh_obj.name + ' ' + mesh_obj.data.name)
					if armature_name != None:
						skeleton_info = SkeletonLookup(armature_name)
				else:
					skeleton_info = {}
					armature = armatures[0]
					SetSelectObjects([])
					SetActiveObject(armature)
					bpy.ops.object.mode_set(mode='EDIT', toggle=False)
					for bone in armature.data.edit_bones:
						info = {}
						info['matrix'] = BoneAxisCorrectionRevert(bone.matrix)
						info['scale'] = 1
						skeleton_info[bone.name] = info
					
					bone_list_filter = list(set(skeleton_info.keys()) & set(vgrp_names))
					bpy.ops.object.mode_set(mode='OBJECT', toggle=False)

			SetSelectObjects([])
			SetActiveObject(mesh_obj)

			if hash_filepath:
				mesh_folder, mesh_name = hash_string(mesh_obj.name)
				result_file_folder = os.path.join(export_folder, 'geometries', mesh_folder)
				os.makedirs(result_file_folder, exist_ok = True)
				result_file_path = os.path.join(result_file_folder, mesh_name + ".mesh")
				factory_name = mesh_folder + '\\' + mesh_name
			else:
				mesh_folder = sanitize_filename(mesh_obj.name)
				mesh_name = sanitize_filename(mesh_obj.data.name)
				result_file_folder = os.path.join(export_folder, 'geometries', mesh_folder)
				os.makedirs(result_file_folder, exist_ok = True)
				result_file_path = os.path.join(result_file_folder, mesh_name + ".mesh")
				factory_name = mesh_folder + '\\' + mesh_name

			rtn, verts_count, indices_count, bone_list = ExportMesh(options,context,result_file_path,operator,bone_list_filter)

			if 'FINISHED' not in rtn:
				operator.report({'WARNING'}, f'Failed exporting {mesh_obj.name}. Skipping...')
				continue

			mesh_lod_info['factory_path'] = factory_name
			mesh_lod_info['num_indices'] = indices_count
			mesh_lod_info['num_vertices'] = verts_count

			mesh_data['geo_mesh_lod'].append(mesh_lod_info)

			mesh_data['mat_path'] = "MATERIAL_PATH"

			if bone_list != None and len(bone_list) > 0 and skeleton_info != None:
				mesh_data['has_skin'] = 1
				mesh_data['bone_names'] = bone_list
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
		#print(_data)
		json_data = json.dumps(_data)

		# Write the JSON data to a file
		#with open(nif_filepath + '.json', 'w') as json_file:
		#	json_file.write(json_data)

		returncode = _dll_export_nif(json_data.encode('utf-8'), nif_filepath.encode('utf-8'), export_folder.encode('utf-8'))

		if returncode != 0:
			operator.report({'INFO'}, f"Execution failed with return code {returncode}. Contact the author for assistance.")
			return {'CANCELLED'}

		operator.report({'INFO'},f'Export Nif successful.')
		return {'FINISHED'}
	
	operator.report({'WARNING'}, f'Unimplemented Template.')
	return {'CANCELLED'}
