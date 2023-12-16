import mathutils
import math
import bpy
import json
import os
import glob

import utils_common as utils
import utils_blender

bone_axis_correction = mathutils.Matrix.Rotation(math.radians(-90.0), 4, 'Z')
bone_axis_correction_inv = mathutils.Matrix.Rotation(math.radians(90.0), 4, 'Z')

skeleton_names = ['skeleton']
skeleton_pivots = {'skeleton':'C_Head'}
skeleton_lookup = {}

_possible_pivots = ['C_Head', 'COM', 'Root']

def GetPivotInfo(skeleton_name):
	return skeleton_lookup[skeleton_name][skeleton_pivots[skeleton_name]]

def GetAvailableSkeletonNames():
	return skeleton_names

def BoneAxisCorrection(T):
	return T @ bone_axis_correction

def BoneAxisCorrectionRevert(T):
	return T @ bone_axis_correction_inv

def SkeletonLookup(skeleton_name:str):
	return skeleton_lookup[skeleton_name]

def SkeletonRegistered(skeleton_name:str):
	return skeleton_name in skeleton_lookup.keys()

def RegisterSkeleton(skeleton_name:str, skeleton_data:dict):
	global skeleton_lookup
	if SkeletonRegistered(skeleton_name):
		return False
	
	with open(os.path.join(utils_blender.PluginAssetsFolderPath(), skeleton_name + '.json'), 'w') as file:
		file.write(json.dumps(skeleton_data))

	skeleton_names.append(skeleton_name)
	skeleton_lookup[skeleton_name] = {}
	LoadLookupRecursive(skeleton_data, skeleton_lookup[skeleton_name])
	
	for possible_pivot in _possible_pivots:
		if possible_pivot in skeleton_lookup[skeleton_name].keys():
			skeleton_pivots[skeleton_name] = possible_pivot
			break
	
	skeleton_dict = {}
	skeleton_dict['skeleton_names'] = skeleton_names
	skeleton_dict['skeleton_pivot'] = skeleton_pivots

	skeleton_folder = utils_blender.PluginAssetsFolderPath()
	with open(os.path.join(skeleton_folder, "_skeleton_list_.meta"), 'w') as file:
		file.write(json.dumps(skeleton_dict, indent = 4))

	return True

def LoadLookupRecursive(armature_dict:dict, lookup:dict):
	T = mathutils.Matrix()
	for i in range(4):
		for j in range(4):
			T[i][j] = armature_dict['matrix'][i][j]

	info_dict = {}
	info_dict['matrix'] = T
	info_dict['scale'] = armature_dict['scale']

	lookup[armature_dict['name']] = info_dict
	
	for child_dict in armature_dict['children']:
		LoadLookupRecursive(child_dict, lookup)

def LoadSkeletonLookup(skeleton_name):
	global skeleton_lookup
	if skeleton_name in skeleton_lookup.keys():
		return
	
	skeleton_lookup[skeleton_name] = {}
	utils_path = utils_blender.UtilsFolderPath()
	skeleton_path = os.path.join(utils_path, "Assets", f"{skeleton_name}.json")

	with open(skeleton_path, 'r') as json_file:
		data = json.load(json_file)

	LoadLookupRecursive(data, skeleton_lookup[skeleton_name])

def LoadAllSkeletonLookup():
	global skeleton_names
	global skeleton_pivots

	skeleton_meta_data = os.path.join(utils_blender.PluginAssetsFolderPath(), "_skeleton_list_.meta")

	if os.path.isfile(skeleton_meta_data):
		with open(skeleton_meta_data, 'r') as file:
			skeleton_dict = json.load(file)

		_skeleton_names = skeleton_dict['skeleton_names']
		_skeleton_pivots = skeleton_dict['skeleton_pivot']

		skeleton_names = []
		skeleton_pivots = {}
		for i in range(len(_skeleton_names)):
			skeleton_path = os.path.join(utils_blender.PluginAssetsFolderPath(), f"{_skeleton_names[i]}.json")
			if os.path.isfile(skeleton_path):
				skeleton_names.append(_skeleton_names[i])
				skeleton_pivots[_skeleton_names[i]] = _skeleton_pivots[_skeleton_names[i]]

		for skel in skeleton_names:
			LoadSkeletonLookup(skel)
	else:
		print(f"Skeleton Metadata cannot be found. Using default settings.")
		json_files = glob.glob(os.path.join(utils_blender.PluginAssetsFolderPath(), '*.json'))

		skeleton_names.clear()

		for file_path in json_files:
			skeleton_name = os.path.splitext(os.path.basename(file_path))[0]
			skeleton_names.append(skeleton_name)
			LoadSkeletonLookup(skeleton_name)
			for possible_pivot in _possible_pivots:
				if possible_pivot in skeleton_lookup[skeleton_name].keys():
					skeleton_pivots[skeleton_name] = possible_pivot
					break

		skeleton_dict = {}
		skeleton_dict['skeleton_names'] = skeleton_names
		skeleton_dict['skeleton_pivot'] = skeleton_pivots

		skeleton_folder = utils_blender.PluginAssetsFolderPath()
		with open(os.path.join(skeleton_folder, "_skeleton_list_.meta"), 'w') as file:
			file.write(json.dumps(skeleton_dict, indent=4))


def MatchSkeleton(bone_list):
	global skeleton_lookup
	bone_set = set(utils_blender.RevertRenamingBoneList(bone_list))
	max_count = 1
	matched_name = None
	bones = None
	for name, skele in skeleton_lookup.items():
		skele_bone_set = set(skele.keys())
		common_elements = skele_bone_set & bone_set
		common_count = len(common_elements)
		if common_count > max_count:
			matched_name = name
			max_count = common_count
			bones = list(common_elements)

	return matched_name, bones

def MatchSkeletonAdvanced(bone_list:list, obj_name:str, name_first = False):
	global skeleton_lookup
	bone_set = set(utils_blender.RevertRenamingBoneList(bone_list))
	max_count = -1
	matched_names = []
	bone_lists = []

	if name_first:
		if obj_name in skeleton_lookup.keys():
			skele_name = obj_name
			skele = skeleton_lookup[skele_name]
			skele_bone_set = set(skele.keys())
			common_elements = skele_bone_set & bone_set
			return skele_name, list(common_elements)
		else:
			best_id = -1
			tags_a = utils._tag(obj_name)
			highest_score = 0
			for i in range(len(skeleton_names)):
				tags_b = utils._tag(skeleton_names[i])
				score = utils._match_tags(tags_a, tags_b)
				print(obj_name, skeleton_names[i], score)
				if score > highest_score:
					best_id = i
					highest_score = score
			if best_id != -1:
				skele_name = skeleton_names[best_id]
				skele = skeleton_lookup[skele_name]
				skele_bone_set = set(skele.keys())
				common_elements = skele_bone_set & bone_set
				return skele_name, list(common_elements)
			else:
				return None, None

	for name, skele in skeleton_lookup.items():
		skele_bone_set = set(skele.keys())
		common_elements = skele_bone_set & bone_set
		common_count = len(common_elements)
		if common_count > max_count:
			matched_names.append([name])
			max_count = common_count
			bone_lists.append([list(common_elements)])
		elif common_count == max_count:
			matched_names[-1].append(name)
			bone_lists[-1].append(list(common_elements))

	best_matches = matched_names[-1]
	
	if len(best_matches) == 1:
		return best_matches[0], bone_lists[0]
	elif len(best_matches) == 0:
		return None, None
	
	best_id = -1
	tags_a = utils._tag(obj_name)
	highest_score = 0
	for i in range(len(best_matches)):
		tags_b = utils._tag(best_matches[i])
		score = utils._match_tags(tags_a, tags_b)
		print(obj_name, best_matches[i], score)
		if score > highest_score:
			best_id = i
			highest_score = score

	if best_id != -1:
		print(f'Matched with skeleton {best_matches[best_id]}')
		return best_matches[best_id], bone_lists[-1][best_id]
	else:
		return None, None


def CreateArmatureRecursive(armature_dict:dict, parent_bone, edit_bones, debug_capsule = None):
	b = edit_bones.new(utils_blender.RenamingBone(armature_dict['name']))
	b.head = tuple(armature_dict['head'])
	b.tail = tuple(armature_dict['tail'])
	T = mathutils.Matrix()
	for i in range(4):
		for j in range(4):
			T[i][j] = armature_dict['matrix'][i][j]
	
	b.matrix = BoneAxisCorrection(T)
	#print(armature_dict['name'])
	if parent_bone != None:
		b.parent = parent_bone

	if debug_capsule != None and armature_dict['name'] in debug_capsule:
		center = debug_capsule[armature_dict['name']]['center']

		start_point_homogeneous = mathutils.Vector((center[0], center[1], center[2], 1))

		# Assuming 'Trans' is a 4x4 transformation matrix
		transformed_start_point = T @ start_point_homogeneous

		# Convert from homogeneous coordinates to 3D Cartesian coordinates
		transformed_start_3d = transformed_start_point.to_3d()

		debug_capsule[armature_dict['name']]['world_center'] = transformed_start_3d

	if 'children' in armature_dict.keys():
		for child_dict in armature_dict['children']:
			CreateArmatureRecursive(child_dict, b, edit_bones, debug_capsule)

def CreateArmature(armature_dict: dict, skin_objects, collection, armature_name = None, debug_capsule = None):
	old_active = utils_blender.GetActiveObject()
	old_selected = utils_blender.GetSelectedObjs(True)

	armature = bpy.data.armatures.new('skeleton')
	
	arm_obj = bpy.data.objects.new('skeleton', armature)
	collection.objects.link(arm_obj)
	utils_blender.SetActiveObject(arm_obj)
	bpy.ops.object.mode_set(mode='EDIT', toggle=False)
	edit_bones = arm_obj.data.edit_bones

	CreateArmatureRecursive(armature_dict, None, edit_bones, debug_capsule)

	bpy.ops.object.mode_set(mode='OBJECT')

	if skin_objects != None:
		for skin_object in skin_objects:
			if skin_object:
				modifier = skin_object.modifiers.new(name = "Armature", type='ARMATURE')
				modifier.object = arm_obj
				#skin_object.parent = arm_obj

				if armature_name == None:
					arm_obj.name = skin_object.name
				else:
					arm_obj.name = armature_name

	utils_blender.SetSelectObjects(old_selected)
	utils_blender.SetActiveObject(old_active)
	return arm_obj

def ImportArmatureFromJson(skeleton_name, collection, skin_objs, armature_name = None, debug_capsule = None):
	utils_path = utils_blender.UtilsFolderPath()
	skeleton_path = os.path.join(utils_path, "Assets", f"{skeleton_name}.json")
	
	with open(skeleton_path, 'r') as json_file:
		data = json.load(json_file)

		return CreateArmature(data, skin_objs, collection, armature_name, debug_capsule)

def CreateArmatureDictRecursive(cur_bone, edit_bones) -> dict:
	armature_dict = {}
	armature_dict['name'] = utils_blender.RevertRenamingBone(cur_bone.name)
	armature_dict['head'] = list(cur_bone.head)
	armature_dict['tail'] = list(cur_bone.tail)
	armature_dict['matrix'] = [[1 if i == j else 0 for i in range(4)] for j in range(4)]
	armature_dict['scale'] = 1
	armature_dict['sgo_keep'] = 1
	armature_dict['geometry_index'] = 4294967295
	T = cur_bone.matrix
	for i in range(4):
		for j in range(4):
			armature_dict['matrix'][i][j] = float(T[i][j])
	armature_dict['children'] = []
	for child in cur_bone.children:
		armature_dict['children'].append(CreateArmatureDictRecursive(child, edit_bones))

	return armature_dict

def CreateArmatureDict(armature_obj) -> dict:
	old_active = utils_blender.GetActiveObject()
	utils_blender.SetActiveObject(armature_obj)
	bpy.ops.object.mode_set(mode='EDIT', toggle=False)
	edit_bones = armature_obj.data.edit_bones

	armature_dict = CreateArmatureDictRecursive(edit_bones[0], edit_bones)

	bpy.ops.object.mode_set(mode='OBJECT')
	utils_blender.SetActiveObject(old_active)

	return armature_dict