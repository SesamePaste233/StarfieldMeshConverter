import bpy
import BoneRegionsReader
import numpy as np
import mathutils
import functools
import math

from nif_armature import BoneAxisCorrection, BoneAxisCorrectionRevert, bone_axis_correction, bone_axis_correction_inv

def br_data():
    return BoneRegionsReader.__bone_regions_data__

@functools.lru_cache(maxsize=256)
def _is_facebone(pose_bone_name:str):
	return pose_bone_name.startswith("faceBone_") or pose_bone_name == "Eye.L" or pose_bone_name == "Eye.R"

def _has_transform(pose_bone:bpy.types.PoseBone):
	tf = collect_transform(pose_bone)
	return not np.isclose(tf, np.zeros(9)).all()

def apply_transform(data, pose_bone:bpy.types.PoseBone):
	if not _is_facebone(pose_bone.name):
		return
	dx, dy, dz = data[:3]
	dRx, dRy, dRz = data[3:6]
	dSx, dSy, dSz = data[6:9]
	pose_bone.location = bone_axis_correction_inv @ mathutils.Vector((dx, dy, dz)) * 0.01
	rot_mat = mathutils.Euler((-dRx, -dRy, -dRz), 'XYZ').to_matrix().to_4x4()
	rot_eul = (bone_axis_correction_inv @ rot_mat @ bone_axis_correction).to_euler('XYZ')
	pose_bone.rotation_mode = 'XYZ'
	pose_bone.rotation_euler = rot_eul
	pose_bone.scale = mathutils.Vector((1, 1, 1)) + bone_axis_correction_inv @ mathutils.Vector((dSx, -dSy, dSz))

def collect_transform(pose_bone:bpy.types.PoseBone)->np.ndarray:
    mat = bone_axis_correction_inv @ pose_bone.matrix_basis @ bone_axis_correction
    delta_translation = mat.to_translation() * 100
    delta_rotation = mat.to_euler('XYZ')
    delta_scale = mat.to_scale()
    return np.array([-delta_translation.x, -delta_translation.y, delta_translation.z, delta_rotation.x, delta_rotation.y, -delta_rotation.z, delta_scale.x-1, delta_scale.y-1, delta_scale.z-1]).round(4)

def facebones_with_pose(armature:bpy.types.Object)->list[str]:
	return [bone.name for bone in armature.pose.bones if _is_facebone(bone.name) and _has_transform(bone)]

def add_new_slider(region_name: str, slider_name: str, is_zero_to_one: bool):
	if region_name not in br_data().sculpt_regions:
		return None

	if slider_name in br_data().regions[region_name].sliders:
		return None

	slider = br_data().AddSculptRegion(region_name, slider_name, is_zero_to_one)
	return slider

def remove_slider(region_name: str, slider_name: str):
    if region_name not in br_data().sculpt_regions:
        return False

    if slider_name not in br_data().regions[region_name].sliders:
        return False

    return br_data().RemoveSculptRegion(region_name, slider_name)

def update_slider(region_name: str, slider_name: str, new_name = None, new_is_zero_to_one = None):
    if region_name not in br_data().sculpt_regions:
        return False

    if slider_name not in br_data().regions[region_name].sliders:
        return False

    region = br_data().regions[region_name]
    slider = region.sliders[slider_name]
	
    if new_is_zero_to_one is not None:
        slider.is_zero_to_one = new_is_zero_to_one

    if new_name is not None and new_name != "" and new_name != slider_name:
        slider.name = new_name
        region.sliders[new_name] = region.sliders.pop(slider_name)
		
    return True
		

def get_slider(region_name: str, slider_name: str):
    return br_data().get_slider(region_name, slider_name)

def collect_sculpt(region_name: str, slider_name: str, is_maxima: bool):
    armature:bpy.types.Object = bpy.context.scene.br_driven_armature
    if armature is None:
        return False

    br = br_data()

    if region_name not in br.sculpt_regions:
        return False

    if slider_name not in br.regions[region_name].sliders:
        return False

    active_bones = facebones_with_pose(armature)

    if not active_bones:
        return False

    bone_data = {}
    for bone_name in active_bones:
        data = collect_transform(armature.pose.bones[bone_name])
        if bone_name == 'Eye.L':
            bone_data['L_Eye'] = data
        elif bone_name == 'Eye.R':
            bone_data['R_Eye'] = data
        else:
            bone_data[bone_name] = data
        
        print(f"Collected data for {bone_name}:", data)

    return br.SetSculptRegionSlider(region_name, slider_name, bone_data, is_maxima)
	
def save_sculpt_regions(filepath: str):
    br = br_data()
    br.export_to_file(filepath)