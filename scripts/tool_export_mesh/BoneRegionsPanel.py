import bpy
import BoneRegionsReader
import numpy as np
import math
import os

from utils_bone_regions import br_data, apply_transform

import utils_bone_regions as ubr

def forward_update(self, context):
	data = [entry.value for entry_group in bpy.context.scene.br_regions_forward_list for entry in entry_group.entries if entry.name != "NONE"]

	control_matrix = np.array(data).reshape(BoneRegionsReader.__bone_regions_data__.get_input_shape()).T

	result = BoneRegionsReader.__bone_regions_data__._forward(control_matrix)

	# Change Bone Pose
	armature:bpy.types.Object = bpy.context.scene.br_driven_armature
	if armature is None:
			return

	for i, bone_name in enumerate(br_data().bone_names):
		if bone_name == 'L_Eye':
			bone:bpy.types.PoseBone = armature.pose.bones.get('Eye.L')
		elif bone_name == 'R_Eye':
			bone:bpy.types.PoseBone = armature.pose.bones.get('Eye.R')
		else:
			bone:bpy.types.PoseBone = armature.pose.bones.get(bone_name)
		if bone is not None:
			apply_transform(result[i], bone)

def forward_sculpt_update(self, context):
	data = [entry.value if entry.is_zero_to_one else entry.value_non_z2o for entry_group in bpy.context.scene.br_sculpt_regions_forward_list for entry in entry_group.entries if entry.name != "NONE"]

	slider_values = np.array(data)

	result = BoneRegionsReader.__bone_regions_data__._forward_sculpt(slider_values)

	# Change Bone Pose
	armature:bpy.types.Object = bpy.context.scene.br_driven_armature
	if armature is None:
		return
	
	for i, bone_name in enumerate(br_data().bone_names):
		if bone_name == 'L_Eye':
			bone:bpy.types.PoseBone = armature.pose.bones.get('Eye.L')
		elif bone_name == 'R_Eye':
			bone:bpy.types.PoseBone = armature.pose.bones.get('Eye.R')
		else:
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
	def draw_item(self, context, layout:bpy.types.UILayout, data, item, icon, active_data, active_propname, index):
		if item.name != "NONE":
			col = layout.column()
			col.label(text=str(item.slider_id))
			col.scale_x = 0.2
			row = layout.row()
			row.prop(item, "name", text="", emboss=False)
			row.prop(item, 'is_zero_to_one', icon="ARROW_LEFTRIGHT", icon_only=True, invert_checkbox=True)
			if item.is_zero_to_one:
				row.prop(item, 'value', text="")
			else:
				row.prop(item, 'value_non_z2o', text="")

			row.prop(item, 'FAKE_BUTTON_delete', icon='X', icon_only=True, emboss=False)
		else:
			row = layout.row()
			row.prop(item, 'FAKE_BUTTON_add', text="Add New Slider", icon='ADD', icon_only=True, emboss=False)

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
	for region_name in BoneRegionsReader.__bone_regions_data__.pheno_face_region_names:
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
			slider.sculpt_region_name = sculpt_region_name
			slider.is_zero_to_one = sculpt_region_slider.is_zero_to_one
			slider.slider_id = sculpt_region_slider.id

		none_slider = entry_group.entries.add()
		none_slider.name = "NONE"
		none_slider.sculpt_region_name = sculpt_region_name

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
        update=forward_update
    )

class BoneRegionForwardEntryGroup(bpy.types.PropertyGroup):
    name: bpy.props.StringProperty(name="Name", default="")
    entries: bpy.props.CollectionProperty(type=BoneRegionForwardEntry)
    active_index: bpy.props.IntProperty(default=0, name="Slider")

def BoneSculptRegionForwardEntry_name_update(self, context):
	if self.name == "":
		self.name = self.old_slider_name
		return

	old_slider_name = self.old_slider_name
	new_slider_name = self.name
	region_name = self.sculpt_region_name

	if self.old_slider_name == "":
		pass
	else:
		ubr.update_slider(region_name, old_slider_name, new_slider_name)

	self.old_slider_name = new_slider_name
	return
	
def BoneSculptRegionForwardEntry_is_zero_to_one_update(self, context):
	rtn = ubr.update_slider(self.sculpt_region_name, self.name, new_is_zero_to_one=self.is_zero_to_one)
	if not rtn:
		raise Exception(f"Failed to update slider: region: {self.sculpt_region_name}, slider: {self.name}")


def BoneSculptRegionForwardEntry_FAKE_BUTTON_delete_update(self, context):
	ubr.remove_slider(self.sculpt_region_name, self.name)
	for sculpt_region_collection in bpy.context.scene.br_sculpt_regions_forward_list:
		if sculpt_region_collection.name == self.sculpt_region_name:
			sculpt_region_collection.entries.remove(sculpt_region_collection.entries.find(self.name))
			break

def BoneSculptRegionForwardEntry_FAKE_BUTTON_add_update(self, context):
	default_name = "New Slider"
	i = 1
	while ubr.get_slider(self.sculpt_region_name, default_name) is not None:
		default_name = f"New Slider.{i:03}"
		i += 1
	
	region_name = self.sculpt_region_name

	new_slider = ubr.add_new_slider(self.sculpt_region_name, default_name, True)

	if new_slider is None:
		raise Exception("Failed to add new slider")

	for sculpt_region_collection in bpy.context.scene.br_sculpt_regions_forward_list:
		if sculpt_region_collection.name == region_name:
			sculpt_region_collection.entries.remove(sculpt_region_collection.entries.find("NONE"))

			slider = sculpt_region_collection.entries.add()
			slider.name = new_slider.name
			slider.sculpt_region_name = region_name
			slider.is_zero_to_one = new_slider.is_zero_to_one
			slider.slider_id = new_slider.id

			none_slider = sculpt_region_collection.entries.add()
			none_slider.name = "NONE"
			none_slider.sculpt_region_name = region_name
			return

	raise Exception("This should not happen")

class BoneSculptRegionForwardEntry(bpy.types.PropertyGroup):
	sculpt_region_name: bpy.props.StringProperty(
		name="Region Name",
		default="",
	)
	slider_id: bpy.props.IntProperty(
		name="Slider ID",
		default=0,
	)
	old_slider_name: bpy.props.StringProperty(
		name="Old Name",
		default="",
	)
	name: bpy.props.StringProperty(
		name="Name", 
		default="",
		update=BoneSculptRegionForwardEntry_name_update
	)
	is_zero_to_one: bpy.props.BoolProperty(
		name="Bi-directional Slider",
		default=True,
		update=BoneSculptRegionForwardEntry_is_zero_to_one_update
	)
	value: bpy.props.FloatProperty(
		name="Value", 
		default=0.0,
		min=0.0,
		max=1.0,
		update=forward_sculpt_update
    )
	value_non_z2o: bpy.props.FloatProperty(
        name="Value", 
		default=0.0,
		min=-1.0,
		max=1.0,
		update=forward_sculpt_update
	)

	FAKE_BUTTON_delete: bpy.props.BoolProperty(
		name="Delete",
		default=False,
		update=BoneSculptRegionForwardEntry_FAKE_BUTTON_delete_update
	)

	FAKE_BUTTON_add: bpy.props.BoolProperty(
		name="Add",
		default=False,
		update=BoneSculptRegionForwardEntry_FAKE_BUTTON_add_update
	)

class BoneSculptRegionForwardEntryGroup(bpy.types.PropertyGroup):
    name: bpy.props.StringProperty(name="Name", default="")
    entries: bpy.props.CollectionProperty(type=BoneSculptRegionForwardEntry)
    active_index: bpy.props.IntProperty(default=0, name="Slider")


def br_edit_mode_update(self, context):
	if self.br_edit_mode == "PHENOTYPES":
		reload_face_region_list(self, context)
	elif self.br_edit_mode == "SCULPT":
		pass
	elif self.br_edit_mode == "VIEWING PHENOTYPES":
		reload_face_region_forward_list(self, context)
	elif self.br_edit_mode == "VIEWING SCULPT":
		reload_sculpt_region_forward_list(self, context)

def bone_regions_file_path_update(self, context):
	BoneRegionsReader.__bone_regions_data__.clear()
	if not os.path.exists(bpy.path.abspath(self.bone_regions_file_path)) or not os.path.exists(bpy.path.abspath(self.bone_regions_mapping_file_path)):
		self.FAKE_BUTTON_refresh_bone_regions = False
		return

	try:
		BoneRegionsReader.__bone_regions_data__.import_from_file(bpy.path.abspath(self.bone_regions_file_path), bpy.path.abspath(self.bone_regions_mapping_file_path))
		reload_face_region_forward_list(self, context)
		reload_sculpt_region_forward_list(self, context)
	except Exception as e:
		BoneRegionsReader.__bone_regions_data__.clear()
		self.br_regions_forward_list.clear()
		self.br_sculpt_regions_forward_list.clear()
		print("ERROR", str(e))
	
	self.FAKE_BUTTON_refresh_bone_regions = False


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
		if not os.path.exists(bpy.path.abspath(self.bone_regions_file_path)) or not os.path.exists(bpy.path.abspath(self.bone_regions_mapping_file_path)):
			self.FAKE_BUTTON_refresh_bone_regions = False
			return

		try:
			BoneRegionsReader.__bone_regions_data__.import_from_file(bpy.path.abspath(self.bone_regions_file_path), bpy.path.abspath(self.bone_regions_mapping_file_path))
			reload_face_region_forward_list(self, context)
			reload_sculpt_region_forward_list(self, context)
		except Exception as e:
			BoneRegionsReader.__bone_regions_data__.clear()
			self.br_regions_forward_list.clear()
			self.br_sculpt_regions_forward_list.clear()
			print("ERROR", str(e))
		
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

		layout.operator("object.sculpt_regions_file_save", text="Save Sculpt Data")

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
			layout.prop(context.scene, "FAKE_BUTTON_clear_bone_regions", text="Clear Bone Transforms", toggle=True)
			if context.scene.br_edit_mode == "VIEWING PHENOTYPES":
				for face_region_collection in context.scene.br_regions_forward_list:
					col = layout.column(align=True)
					col.label(text=face_region_collection.name)
					col.template_list(
						listtype_name="SGB_UL_RegionForwardList",
						list_id=face_region_collection.name + "_sliders", 
						dataptr=face_region_collection, 
						propname="entries", 
						active_dataptr=face_region_collection, 
						active_propname="active_index", 
						rows=5
					)
			elif context.scene.br_edit_mode == "VIEWING SCULPT":
				#row = layout.row(align=True)
				#row.operator("object.sculpt_regions_add", text="New Slider")
				#layout.operator("object.sculpt_regions_remove", text="Remove Sculpt Region")
				#layout.operator("object.sculpt_regions_update", text="Update Sculpt Region")
				row = layout.row(align=True)
				if context.scene.br_driven_armature is None:
					row.enabled = False
				row.operator("object.sculpt_regions_collect", text="Collect Sculpt Data")
				for sculpt_region_collection in context.scene.br_sculpt_regions_forward_list:
					col = layout.column()
					col.label(text=sculpt_region_collection.name)
					col.template_list(
						listtype_name="SGB_UL_SculptRegionForwardList",
						list_id=sculpt_region_collection.name + "_sliders",
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
            ("VIEWING PHENOTYPES", "Viewing Phenos", ""),
			("VIEWING SCULPT", "Sculpt", ""),
        ],
        default="VIEWING SCULPT",
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
		default="",
		update=bone_regions_file_path_update
	),
	'bone_regions_mapping_file_path': __prop_wrapper(
		bpy.props.StringProperty,
		name="Bone Regions Mapping File Path",
		subtype='FILE_PATH',
		default="",
		update=bone_regions_file_path_update
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
