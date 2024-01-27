import bpy
import math
import mathutils

import PhysicsEditor.Prefabs.CapsuleGenGeoNode as capsule_gen
import PhysicsEditor.Prefabs.PlaneGenGeoNode as plane_gen

def GetNodeGroupInputIdentifier(node_group, input_name):
	inputs = node_group.inputs
	id = inputs[input_name].identifier
	return id

def CapsuleFromParameters(name: str, smallEnd: list, bigEnd: list, smallRadius: float, bigRadius: float):
	mesh = bpy.data.meshes.new(name)
	obj = bpy.data.objects.new(name, mesh)

	bpy.context.collection.objects.link(obj)

	if smallRadius > bigRadius:
		smallRadius, bigRadius = bigRadius, smallRadius
		smallEnd, bigEnd = bigEnd, smallEnd

	gnmod = None
	for gnmod in obj.modifiers:
		if gnmod.type == "NODES":
			break

	if (gnmod is None) or (gnmod.type != "NODES"):
		gnmod = obj.modifiers.new("Capsule", "NODES")

	gnmod.node_group = capsule_gen.GetGeoNode()

	start_big_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Start/Big")
	end_small_id = GetNodeGroupInputIdentifier(gnmod.node_group, "End/Small")
	big_radius_id = GetNodeGroupInputIdentifier(gnmod.node_group, "bigRadius")
	small_radius_id = GetNodeGroupInputIdentifier(gnmod.node_group, "smallRadius")

	gnmod[start_big_id][0] = bigEnd[0]
	gnmod[start_big_id][1] = bigEnd[1]
	gnmod[start_big_id][2] = bigEnd[2]

	gnmod[end_small_id][0] = smallEnd[0]
	gnmod[end_small_id][1] = smallEnd[1]
	gnmod[end_small_id][2] = smallEnd[2]

	gnmod[big_radius_id] = bigRadius
	gnmod[small_radius_id] = smallRadius
	
	obj.display_type = 'WIRE'
	return obj

def SetCapsuleParameters(capsule_obj, smallEnd = None, bigEnd = None, smallRadius = None, bigRadius = None, create_if_not_exist = True):
	if capsule_obj == None:
		return
	gnmod = None
	for gnmod in capsule_obj.modifiers:
		if gnmod.type == "NODES" and gnmod.node_group.name == "Capsule_Gen":
			break

	if (gnmod is None) or (gnmod.type != "NODES") or (gnmod.node_group.name != "Capsule_Gen"):
		if not create_if_not_exist:
			return
		gnmod = capsule_obj.modifiers.new("Capsule", "NODES")

	if bigEnd is not None:
		start_big_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Start/Big")
		gnmod[start_big_id][0] = bigEnd[0]
		gnmod[start_big_id][1] = bigEnd[1]
		gnmod[start_big_id][2] = bigEnd[2]

	if smallEnd is not None:
		end_small_id = GetNodeGroupInputIdentifier(gnmod.node_group, "End/Small")
		gnmod[end_small_id][0] = smallEnd[0]
		gnmod[end_small_id][1] = smallEnd[1]
		gnmod[end_small_id][2] = smallEnd[2]

	if bigRadius is not None:
		big_radius_id = GetNodeGroupInputIdentifier(gnmod.node_group, "bigRadius")
		gnmod[big_radius_id] = bigRadius

	if smallRadius is not None:
		small_radius_id = GetNodeGroupInputIdentifier(gnmod.node_group, "smallRadius")
		gnmod[small_radius_id] = smallRadius

	gnmod.show_on_cage = True
	gnmod.show_on_cage = False

def ConstraintObjToArmatureBone(obj, armature_obj, bone_index, inherit_rotation = False):
	if armature_obj == None:
		return
	if obj == None:
		return
	if bone_index == None:
		return

	obj.constraints.clear()
	bone= armature_obj.data.bones[bone_index]
	if inherit_rotation:
		obj.matrix_world = armature_obj.matrix_world @ bone.matrix_local @ mathutils.Matrix.Rotation(math.radians(90.0), 4, 'Z')
		print(obj.matrix_world)
	arma_const = obj.constraints.new(type = 'ARMATURE')
	_target = arma_const.targets.new()
	_target.target = armature_obj
	_target.subtarget = bone.name

def PlaneFromOriginNormal(name: str, origin, normal_dir, size = 1.0):
	mesh = bpy.data.meshes.new(name)
	obj = bpy.data.objects.new(name, mesh)

	bpy.context.collection.objects.link(obj)

	gnmod = None
	for gnmod in obj.modifiers:
		if gnmod.type == "NODES":
			break

	if (gnmod is None) or (gnmod.type != "NODES"):
		gnmod = obj.modifiers.new("Plane", "NODES")

	gnmod.node_group = plane_gen.GetGeoNode()

	normal_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Normal")
	size_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Size")

	obj.location = origin

	gnmod[normal_id][0] = normal_dir[0]
	gnmod[normal_id][1] = normal_dir[1]
	gnmod[normal_id][2] = normal_dir[2]

	gnmod[size_id] = size
	
	return obj

def SetPlaneParameters(plane_obj, origin = None, normal_dir = None, size = None, create_if_not_exist = True):
	if plane_obj == None:
		return
	gnmod = None
	for gnmod in plane_obj.modifiers:
		if gnmod.type == "NODES" and gnmod.node_group.name == "Plane_Gen":
			break

	if (gnmod is None) or (gnmod.type != "NODES") or (gnmod.node_group.name != "Plane_Gen"):
		if not create_if_not_exist:
			return
		gnmod = plane_obj.modifiers.new("Plane", "NODES")

	if origin is not None:
		plane_obj.location = origin

	if normal_dir is not None:
		normal_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Normal")
		gnmod[normal_id][0] = normal_dir[0]
		gnmod[normal_id][1] = normal_dir[1]
		gnmod[normal_id][2] = normal_dir[2]

	if size is not None:
		size_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Size")
		gnmod[size_id] = size

	gnmod.show_on_cage = True
	gnmod.show_on_cage = False

def ConstraintObjsToBoneRotation(objs: list[bpy.types.Object], armature_obj, bone_index) -> bpy.types.Object:
	if armature_obj == None:
		return
	if objs == None or len(objs) == 0:
		return
	if bone_index == None:
		return

	mesh = bpy.data.meshes.new('ANCHOR_OBJ')
	anchor_obj = bpy.data.objects.new('ANCHOR_OBJ', mesh)

	bpy.context.collection.objects.link(anchor_obj)

	ConstraintObjToArmatureBone(anchor_obj, armature_obj, bone_index, False)

	for obj in objs:
		if obj == None:
			continue
		obj.constraints.clear()
		const = obj.constraints.new(type = 'COPY_ROTATION')
		const.target = anchor_obj

	return anchor_obj
