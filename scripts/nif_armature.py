import mathutils
import math
import bpy
import json
import os

from utils_blender import GetActiveObject, SetActiveObject, GetSelectedObjs, SetSelectObjects, update_path

bone_axis_correction = mathutils.Matrix.Rotation(math.radians(-90.0), 4, 'Z')
bone_axis_correction_inv = mathutils.Matrix.Rotation(math.radians(90.0), 4, 'Z')

skeleton_names = ['skeleton']
#skeleton_pivots = {'skeleton':'C_Head'}
skeleton_lookup = {}

def CreateArmatureRecursive(armature_dict:dict, parent_bone, edit_bones, debug_capsule = None):
	b = edit_bones.new(armature_dict['name'])
	b.head = tuple(armature_dict['head'])
	b.tail = tuple(armature_dict['tail'])
	T = mathutils.Matrix()
	for i in range(4):
		for j in range(4):
			T[i][j] = armature_dict['matrix'][i][j]
	
	b.matrix = T @ bone_axis_correction
	print(armature_dict['name'])
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

	for child_dict in armature_dict['children']:
		CreateArmatureRecursive(child_dict, b, edit_bones, debug_capsule)

def CreateArmature(armature_dict: dict, skin_objects, collection, armature_name = None, debug_capsule = None):
	old_active = GetActiveObject()
	old_selected = GetSelectedObjs(True)

	armature = bpy.data.armatures.new('skeleton')
	
	arm_obj = bpy.data.objects.new('skeleton', armature)
	collection.objects.link(arm_obj)
	SetActiveObject(arm_obj)
	bpy.ops.object.mode_set(mode='EDIT', toggle=False)
	edit_bones = arm_obj.data.edit_bones

	CreateArmatureRecursive(armature_dict, None, edit_bones, debug_capsule)

	bpy.ops.object.mode_set(mode='OBJECT')

	if skin_objects != None:
		for skin_object in skin_objects:
			if skin_object:
				modifier = skin_object.modifiers.new(name = "Armature", type='ARMATURE')
				modifier.object = arm_obj
				skin_object.parent = arm_obj

				if armature_name == None:
					arm_obj.name = skin_object.name
				else:
					arm_obj.name = armature_name

	SetSelectObjects(old_selected)
	SetActiveObject(old_active)
	return arm_obj

def ImportArmatureFromJson(skeleton_name, collection, skin_objs, armature_name = None, debug_capsule = None):
	utils_path, temp_path = update_path(os.path.dirname(__file__))
	skeleton_path = os.path.join(utils_path, "Assets", f"{skeleton_name}.json")
	
	with open(skeleton_path, 'r') as json_file:
		data = json.load(json_file)

		return CreateArmature(data, skin_objs, collection, armature_name, debug_capsule)

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
	utils_path, temp_path = update_path(os.path.dirname(__file__))
	skeleton_path = os.path.join(utils_path, "Assets", f"{skeleton_name}.json")

	with open(skeleton_path, 'r') as json_file:
		data = json.load(json_file)

	LoadLookupRecursive(data, skeleton_lookup[skeleton_name])

def LoadAllSkeletonLookup():
	for skel in skeleton_names:
		LoadSkeletonLookup(skel)

def MatchSkeleton(bone_list):
	global skeleton_lookup
	bone_set = set(bone_list)
	max_count = 3
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
