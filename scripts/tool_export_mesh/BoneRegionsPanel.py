import bpy
import BoneRegionsReader
import numpy as np
import mathutils
import math

from nif_armature import BoneAxisCorrection, BoneAxisCorrectionRevert, bone_axis_correction, bone_axis_correction_inv

import functools

def br_data():
    return BoneRegionsReader.__bone_regions_data__

@functools.lru_cache(maxsize=256)
def _is_facebone(pose_bone_name:str):
	return pose_bone_name.startswith("faceBone_") or pose_bone_name == "Eye.L" or pose_bone_name == "Eye.R"

def apply_transform(result, pose_bone:bpy.types.PoseBone):
	if not _is_facebone(pose_bone.name):
		return
	dx, dy, dz = result[:3]
	dRx, dRy, dRz = result[3:6]
	dSx, dSy, dSz = result[6:9]
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
    return np.array([delta_translation.x, delta_translation.y, delta_translation.z, -delta_rotation.x, -delta_rotation.y, -delta_rotation.z, delta_scale.x-1, delta_scale.y-1, delta_scale.z-1])

def forward(self, context):
    data = [entry.value for entry_group in bpy.context.scene.br_regions_forward_list for entry in entry_group.entries]

    control_matrix = np.array(data).reshape(BoneRegionsReader.__bone_regions_data__.get_input_shape()).T

    result = BoneRegionsReader.__bone_regions_data__._forward(control_matrix)

    # Change Bone Pose
    armature:bpy.types.Object = bpy.context.scene.br_driven_armature
    if armature is None:
         return
    
    for i, bone_name in enumerate(br_data().bone_names):
        bone:bpy.types.PoseBone = armature.pose.bones.get(bone_name)
        if bone is not None:
            apply_transform(result[i], bone)

def forward_sculpt(self, context):
	data = [entry.value if entry.is_zero_to_one else entry.value_non_z2o for entry_group in bpy.context.scene.br_sculpt_regions_forward_list for entry in entry_group.entries]

	slider_values = np.array(data)

	result = BoneRegionsReader.__bone_regions_data__._forward_sculpt(slider_values)

	# Change Bone Pose
	armature:bpy.types.Object = bpy.context.scene.br_driven_armature
	if armature is None:
		return
	
	for i, bone_name in enumerate(br_data().bone_names):
		bone:bpy.types.PoseBone = armature.pose.bones.get(bone_name)
		if bone is not None:
			apply_transform(result[i], bone)

class SGB_UL_RegionList(bpy.types.UIList):
	def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
		row = layout.row()
		row.prop(item, "name", text="", emboss=False)
		row.prop(item, 'enabled', text="")

class SGB_UL_RegionForwardList(bpy.types.UIList):
	def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
		row = layout.row()
		row.prop(item, "name", text="", emboss=False)
		row.prop(item, 'value', text="")

class SGB_UL_SculptRegionForwardList(bpy.types.UIList):
	def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
		row = layout.row()
		row.prop(item, "name", text="", emboss=False)
		if item.is_zero_to_one:
			row.prop(item, 'value', text="")
		else:
			row.prop(item, 'value_non_z2o', text="")

def reset_face_region_values(self, context):
	for face_region_collection in bpy.context.scene.br_regions_forward_list:
		for entry in face_region_collection.entries:
			entry.value = 0.0

def reset_sculpt_region_values(self, context):
	for sculpt_region_collection in bpy.context.scene.br_sculpt_regions_forward_list:
		for entry in sculpt_region_collection.entries:
			entry.value = 0.0
			entry.value_non_z2o = 0.0

def reload_face_region_forward_list(self, context):
	bpy.context.scene.br_regions_forward_list.clear()
	for region_name in BoneRegionsReader.__bone_regions_data__.face_region_names:
		entry_group = bpy.context.scene.br_regions_forward_list.add()
		entry_group.name = region_name
		for pheno_name in BoneRegionsReader.__bone_regions_data__.phenotypes:
			entry_group.entries.add().name = pheno_name

def reload_sculpt_region_forward_list(self, context):
	bpy.context.scene.br_sculpt_regions_forward_list.clear()
	for sculpt_region_name in BoneRegionsReader.__bone_regions_data__.sculpt_regions:
		entry_group = bpy.context.scene.br_sculpt_regions_forward_list.add()
		entry_group.name = sculpt_region_name
		for sculpt_region_slider in BoneRegionsReader.__bone_regions_data__.regions[sculpt_region_name].sliders.values():
			slider = entry_group.entries.add()
			slider.name = sculpt_region_slider.name
			slider.is_zero_to_one = sculpt_region_slider.is_zero_to_one

def reload_face_region_list(self, context):
	bpy.context.scene.br_regions_list.clear()
	for pheno in BoneRegionsReader.__bone_regions_data__.phenotypes:
		entry = bpy.context.scene.br_regions_list.add()
		entry.name = pheno
		entry.enabled = False 

class BoneRegionEntry(bpy.types.PropertyGroup):
	name: bpy.props.StringProperty(name="Name", default="")
	enabled: bpy.props.BoolProperty(
        default=True
    )

class BoneRegionForwardEntry(bpy.types.PropertyGroup):
	name: bpy.props.StringProperty(name="Name", default="")
	value: bpy.props.FloatProperty(
		name="Value", 
		default=0.0,
		min=0.0,
		max=1.0,
        update=forward
    )

class BoneRegionForwardEntryGroup(bpy.types.PropertyGroup):
    name: bpy.props.StringProperty(name="Name", default="")
    entries: bpy.props.CollectionProperty(type=BoneRegionForwardEntry)
    active_index: bpy.props.IntProperty(default=0)

class BoneSculptRegionForwardEntry(bpy.types.PropertyGroup):
	name: bpy.props.StringProperty(name="Name", default="")
	is_zero_to_one: bpy.props.BoolProperty(default=True)
	value: bpy.props.FloatProperty(
		name="Value", 
		default=0.0,
		min=0.0,
		max=1.0,
		update=forward_sculpt
    )
	value_non_z2o: bpy.props.FloatProperty(
        name="Value", 
		default=0.0,
		min=-1.0,
		max=1.0,
		update=forward_sculpt
	)

class BoneSculptRegionForwardEntryGroup(bpy.types.PropertyGroup):
    name: bpy.props.StringProperty(name="Name", default="")
    entries: bpy.props.CollectionProperty(type=BoneSculptRegionForwardEntry)
    active_index: bpy.props.IntProperty(default=0)


def br_edit_mode_update(self, context):
	if self.br_edit_mode == "PHENOTYPES":
		reload_face_region_list(self, context)
	elif self.br_edit_mode == "SCULPT":
		pass
	elif self.br_edit_mode == "VIEWING PHENOTYPES":
		reload_face_region_forward_list(self, context)
	elif self.br_edit_mode == "VIEWING SCULPT":
		reload_sculpt_region_forward_list(self, context)

def FAKE_BUTTON_load_bone_regions_update(self, context):
	if self.FAKE_BUTTON_load_bone_regions:
		try:
			BoneRegionsReader.__bone_regions_data__.import_from_file(bpy.path.abspath(self.bone_regions_file_path), bpy.path.abspath(self.bone_regions_mapping_file_path))
			reload_face_region_forward_list(self, context)
			reload_sculpt_region_forward_list(self, context)
		except Exception as e:
			print("ERROR", str(e))
			BoneRegionsReader.__bone_regions_data__.clear()        
		self.FAKE_BUTTON_load_bone_regions = False

def FAKE_BUTTON_clear_bone_regions_update(self, context):
	if self.FAKE_BUTTON_clear_bone_regions:
		reset_face_region_values(self, context)
		reset_sculpt_region_values(self, context)
		self.FAKE_BUTTON_clear_bone_regions = False

def FAKE_BUTTON_refresh_bone_regions_update(self, context):
	if self.FAKE_BUTTON_refresh_bone_regions:
		BoneRegionsReader.__bone_regions_data__.clear()
		try:
			BoneRegionsReader.__bone_regions_data__.import_from_file(bpy.path.abspath(self.bone_regions_file_path), bpy.path.abspath(self.bone_regions_mapping_file_path))
			reload_face_region_forward_list(self, context)
			reload_sculpt_region_forward_list(self, context)
		except Exception as e:
			print("ERROR", str(e))
		finally:
			BoneRegionsReader.__bone_regions_data__.clear()
			self.br_regions_forward_list.clear()
			self.br_sculpt_regions_forward_list.clear()
		
		self.FAKE_BUTTON_refresh_bone_regions = False

def FAKE_BUTTON_unload_bone_regions_update(self, context):
	if self.FAKE_BUTTON_unload_bone_regions:
		reset_face_region_values(self, context)
		reset_sculpt_region_values(self, context)                        
		BoneRegionsReader.__bone_regions_data__.clear()
		self.br_regions_forward_list.clear()
		self.br_sculpt_regions_forward_list.clear()
		self.FAKE_BUTTON_unload_bone_regions = False

class BoneRegionsPanel(bpy.types.Panel):
	bl_label = "Bone Regions"
	bl_idname = "OBJECT_PT_sf_bone_regions"
	bl_space_type = 'VIEW_3D'
	bl_region_type = 'UI'
	bl_category = 'Bone Regions'
	bl_context = 'objectmode'

	def draw(self, context):
		layout = self.layout
		
		layout.label(text="Bone Regions File:")
		layout.prop(context.scene, "bone_regions_file_path", text="")
		layout.label(text="Bone Regions Mapping File:")
		layout.prop(context.scene, "bone_regions_mapping_file_path", text="")

		if BoneRegionsReader.__bone_regions_data__.is_emtpy():
			col = layout.row(align=True)
			col.prop(context.scene, "FAKE_BUTTON_load_bone_regions", text="Load Files", toggle=True)
			return
		
		row = layout.row(align=True)
		row.prop(context.scene, "FAKE_BUTTON_refresh_bone_regions", text="Refresh Files", toggle=True)
		row.prop(context.scene, "FAKE_BUTTON_unload_bone_regions", text="Unload Files", toggle=True)

		layout.prop(context.scene, "br_edit_mode", text="Edit Mode")
		layout.prop(context.scene, "br_driven_armature", text="Driven Armature")

		if context.scene.br_edit_mode != "VIEWING PHENOTYPES" and context.scene.br_edit_mode != "VIEWING SCULPT":
			col = layout.column(align=True)
			if context.scene.br_edit_mode == "PHENOTYPES":
				col.label(text="Phenotypes")
				col.template_list(
					listtype_name="SGB_UL_RegionList",
					list_id="", 
					dataptr=context.scene, 
					propname="br_regions_list", 
					active_dataptr=context.scene, 
					active_propname="br_regions_list_index", 
					rows=5
				)
		else:
			layout.prop(context.scene, "FAKE_BUTTON_clear_bone_regions", text="Clear Bone Regions", toggle=True)
			if context.scene.br_edit_mode == "VIEWING PHENOTYPES":
				for face_region_collection in context.scene.br_regions_forward_list:
					col = layout.column(align=True)
					col.label(text=face_region_collection.name)
					col.template_list(
						listtype_name="SGB_UL_RegionForwardList",
						list_id="", 
						dataptr=face_region_collection, 
						propname="entries", 
						active_dataptr=face_region_collection, 
						active_propname="active_index", 
						rows=5
					)
			elif context.scene.br_edit_mode == "VIEWING SCULPT":
				for sculpt_region_collection in context.scene.br_sculpt_regions_forward_list:
					col = layout.column()
					col.label(text=sculpt_region_collection.name)
					col.template_list(
						listtype_name="SGB_UL_SculptRegionForwardList",
						list_id="",
						dataptr=sculpt_region_collection,
						propname="entries",
						active_dataptr=sculpt_region_collection,
						active_propname="active_index",
						rows=5
					)

from utils_common import __prop_wrapper

__classes__ = [
	BoneRegionEntry,
	BoneRegionForwardEntry,
	BoneRegionForwardEntryGroup,
	BoneSculptRegionForwardEntry,
	BoneSculptRegionForwardEntryGroup,
	SGB_UL_RegionList,
	SGB_UL_RegionForwardList,
	SGB_UL_SculptRegionForwardList,
	BoneRegionsPanel
]

__scene_global_attrs__ = {
	'br_edit_mode': __prop_wrapper(
        bpy.props.EnumProperty,
        items=[
            ("PHENOTYPES", "Phenotypes", ""),
            ("SCULPT", "Sculpt", ""),
            ("VIEWING PHENOTYPES", "Viewing Phenos", ""),
			("VIEWING SCULPT", "Viewing Sculpt", ""),
        ],
        default="VIEWING PHENOTYPES",
        update=br_edit_mode_update
	),
    'br_regions_list': __prop_wrapper(
        bpy.props.CollectionProperty,
        type=BoneRegionEntry
	),
	'br_regions_list_index': __prop_wrapper(
		bpy.props.IntProperty,
		default=0
	),
	'br_regions_forward_list': __prop_wrapper(
        bpy.props.CollectionProperty,
		type=BoneRegionForwardEntryGroup
	),
	'br_regions_forward_list_index': __prop_wrapper(
		bpy.props.IntProperty,
		default=0
	),
	'br_sculpt_regions_forward_list': __prop_wrapper(
        bpy.props.CollectionProperty,
		type=BoneSculptRegionForwardEntryGroup
	),
	'br_sculpt_regions_forward_list_index': __prop_wrapper(
		bpy.props.IntProperty,
		default=0
	),
	'bone_regions_file_path': __prop_wrapper(
		bpy.props.StringProperty,
		name="Bone Regions File Path",
		subtype='FILE_PATH',
		default=""
	),
	'bone_regions_mapping_file_path': __prop_wrapper(
		bpy.props.StringProperty,
		name="Bone Regions Mapping File Path",
		subtype='FILE_PATH',
		default=""
	),
	'br_driven_armature': __prop_wrapper(
		bpy.props.PointerProperty,
		type=bpy.types.Object,
		poll=lambda self, object: object.type == 'ARMATURE'
	),
    'FAKE_BUTTON_load_bone_regions': __prop_wrapper(
		bpy.props.BoolProperty,
		name="Load Bone Regions",
		default=False,
		update=FAKE_BUTTON_load_bone_regions_update
	),
    'FAKE_BUTTON_clear_bone_regions': __prop_wrapper(
		bpy.props.BoolProperty,
		name="Clear Bone Regions",
		default=False,
		update=FAKE_BUTTON_clear_bone_regions_update
	),
	'FAKE_BUTTON_refresh_bone_regions': __prop_wrapper(
		bpy.props.BoolProperty,
		name="Refresh Bone Regions Files",
		default=False,
		update=FAKE_BUTTON_refresh_bone_regions_update
	),
	'FAKE_BUTTON_unload_bone_regions': __prop_wrapper(
		bpy.props.BoolProperty,
		name="Unload Bone Regions",
		default=False,
		update=FAKE_BUTTON_unload_bone_regions_update
	)
}

def register():
	for c in __classes__:
		bpy.utils.register_class(c)
	
	for attr in __scene_global_attrs__:
		setattr(bpy.types.Scene, attr, __scene_global_attrs__[attr]())


def unregister():
	for c in __classes__:
		bpy.utils.unregister_class(c)
	
	for attr in __scene_global_attrs__:
		delattr(bpy.types.Scene, attr)
