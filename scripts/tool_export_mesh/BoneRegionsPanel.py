import bpy
import BoneRegionsReader
import numpy as np
import mathutils
import math

from nif_armature import BoneAxisCorrection, BoneAxisCorrectionRevert, bone_axis_correction, bone_axis_correction_inv

def br_data():
    return BoneRegionsReader.__bone_regions_data__

def apply_transform(result, pose_bone:bpy.types.PoseBone):
    dx, dy, dz = result[:3]
    dRx, dRy, dRz = result[3:6]
    dSx, dSy, dSz = result[6:9]
    pose_bone.location = bone_axis_correction_inv @ mathutils.Vector((dx, dy, dz)) * 0.01
    rot_mat = mathutils.Euler((-dRx, -dRy, -dRz), 'XYZ').to_matrix().to_4x4()
    rot_eul = (bone_axis_correction_inv @ rot_mat @ bone_axis_correction).to_euler('XYZ')
    pose_bone.rotation_mode = 'XYZ'
    pose_bone.rotation_euler = rot_eul
    pose_bone.scale = mathutils.Vector((1, 1, 1)) + bone_axis_correction_inv @ mathutils.Vector((dSx, dSy, dSz))

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

def br_entry_update(self, context):
    for entry in self.br_regions_list:
        entry.enabled = False
    self.br_regions_list[self.br_regions_list_index].enabled = True  

class BoneRegionEntry(bpy.types.PropertyGroup):
	name: bpy.props.StringProperty(name="Name", default="")
	enabled: bpy.props.BoolProperty(
        default=True,
        update= br_entry_update
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

def br_edit_mode_update(self, context):
    if self.br_edit_mode == "PHENOTYPES":
        self.br_regions_list.clear()
        for pheno in BoneRegionsReader.__bone_regions_data__.phenotypes:
            entry = self.br_regions_list.add()
            entry.name = pheno
            entry.enabled = False
    elif self.br_edit_mode == "SCULPT":
        pass

def FAKE_BUTTON_load_bone_regions_update(self, context):
    if self.FAKE_BUTTON_load_bone_regions:
        try:
            BoneRegionsReader.__bone_regions_data__.import_from_file(bpy.path.abspath(self.bone_regions_file_path), bpy.path.abspath(self.bone_regions_mapping_file_path))
            self.br_regions_forward_list.clear()
            for region_name in BoneRegionsReader.__bone_regions_data__.face_region_names:
                entry_group = self.br_regions_forward_list.add()
                entry_group.name = region_name
                for pheno_name in BoneRegionsReader.__bone_regions_data__.phenotypes:
                    entry_group.entries.add().name = pheno_name
        
        except Exception as e:
            print("ERROR", str(e))
            BoneRegionsReader.__bone_regions_data__.clear()        
        self.FAKE_BUTTON_load_bone_regions = False


def FAKE_BUTTON_apply_bone_regions_update(self, context):
    if self.FAKE_BUTTON_apply_bone_regions:
        if self.br_driven_armature is None:
            print("ERROR", "Driven Armature not set.")
            self.FAKE_BUTTON_apply_bone_regions = False
            return

        #if len(self.br_driven_mesh_collection) == 0:
        #    wm = bpy.context.window_manager
        #    wm.popup_menu(name="WARNING", title="Warning", message="Driven Mesh Collection not set.")
        #    self.FAKE_BUTTON_apply_bone_regions = False
        
        forward(self, context)        
        
        self.FAKE_BUTTON_apply_bone_regions = False

def FAKE_BUTTON_clear_bone_regions_update(self, context):
    if self.FAKE_BUTTON_clear_bone_regions:
        for face_region_collection in context.scene.br_regions_forward_list:
            for entry in face_region_collection.entries:
                entry.value = 0.0

        self.FAKE_BUTTON_clear_bone_regions = False

def FAKE_BUTTON_refresh_bone_regions_update(self, context):
    if self.FAKE_BUTTON_refresh_bone_regions:
        for face_region_collection in context.scene.br_regions_forward_list:
            for entry in face_region_collection.entries:
                entry.value = 0.0
        BoneRegionsReader.__bone_regions_data__.import_from_file(bpy.path.abspath(self.bone_regions_file_path), bpy.path.abspath(self.bone_regions_mapping_file_path))
        try:
            BoneRegionsReader.__bone_regions_data__.import_from_file(bpy.path.abspath(self.bone_regions_file_path), bpy.path.abspath(self.bone_regions_mapping_file_path))
            self.br_regions_forward_list.clear()
            for region_name in BoneRegionsReader.__bone_regions_data__.face_region_names:
                entry_group = self.br_regions_forward_list.add()
                entry_group.name = region_name
                for pheno_name in BoneRegionsReader.__bone_regions_data__.phenotypes:
                    entry_group.entries.add().name = pheno_name
        
        except Exception as e:
            print("ERROR", str(e))
            BoneRegionsReader.__bone_regions_data__.clear()
        
        self.FAKE_BUTTON_refresh_bone_regions = False

def unload_bone_regions_update(self, context):
    for face_region_collection in context.scene.br_regions_forward_list:
            for entry in face_region_collection.entries:
                entry.value = 0.0
    BoneRegionsReader.__bone_regions_data__.clear()

def FAKE_BUTTON_unload_bone_regions_update(self, context):
    if self.FAKE_BUTTON_unload_bone_regions:
        for face_region_collection in context.scene.br_regions_forward_list:
            for entry in face_region_collection.entries:
                entry.value = 0.0
        BoneRegionsReader.__bone_regions_data__.clear()
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

        if context.scene.br_edit_mode != "VIEWING":
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
            #layout.prop(context.scene, "FAKE_BUTTON_apply_bone_regions", text="Apply Bone Regions", toggle=True)



def register():
    bpy.utils.register_class(BoneRegionEntry)
    bpy.utils.register_class(BoneRegionForwardEntry)
    bpy.utils.register_class(BoneRegionForwardEntryGroup)
    bpy.utils.register_class(SGB_UL_RegionList)
    bpy.utils.register_class(SGB_UL_RegionForwardList)
    bpy.utils.register_class(BoneRegionsPanel)

    bpy.types.Scene.br_edit_mode = bpy.props.EnumProperty(
        items=[
            ("PHENOTYPES", "Phenotypes", ""),
            ("SCULPT", "Sculpt", ""),
            ("VIEWING", "Viewing", "")
        ],
        default="VIEWING",
        update=br_edit_mode_update
    )

    bpy.types.Scene.br_regions_list = bpy.props.CollectionProperty(
        type=BoneRegionEntry
    )

    bpy.types.Scene.br_regions_list_index = bpy.props.IntProperty(
        default=0
    )
    
    bpy.types.Scene.br_regions_forward_list = bpy.props.CollectionProperty(
        type=BoneRegionForwardEntryGroup
    )

    bpy.types.Scene.br_regions_forward_list_index = bpy.props.IntProperty(
        default=0
    )
	
    bpy.types.Scene.bone_regions_file_path = bpy.props.StringProperty(
        name="Bone Regions File Path",
        subtype='FILE_PATH',
        default="",
        update=unload_bone_regions_update
    )

    bpy.types.Scene.bone_regions_mapping_file_path = bpy.props.StringProperty(
        name="Bone Regions Mapping File Path",
        subtype='FILE_PATH',
        default="",
        update=unload_bone_regions_update
    )

    bpy.types.Scene.FAKE_BUTTON_load_bone_regions = bpy.props.BoolProperty(
        name="Load Bone Regions",
        default=False,
        update = FAKE_BUTTON_load_bone_regions_update
    )

    bpy.types.Scene.FAKE_BUTTON_apply_bone_regions = bpy.props.BoolProperty(
        name="Apply Bone Regions",
        default=False,
        update = FAKE_BUTTON_apply_bone_regions_update
    )

    bpy.types.Scene.FAKE_BUTTON_clear_bone_regions = bpy.props.BoolProperty(
        name="Clear Bone Regions",
        default=False,
        update = FAKE_BUTTON_clear_bone_regions_update
    )

    bpy.types.Scene.FAKE_BUTTON_refresh_bone_regions = bpy.props.BoolProperty(
        name="Refresh Bone Regions Files",
        default=False,
        update = FAKE_BUTTON_refresh_bone_regions_update
    )

    bpy.types.Scene.FAKE_BUTTON_unload_bone_regions = bpy.props.BoolProperty(
        name="Unload Bone Regions",
        default=False,
        update = FAKE_BUTTON_unload_bone_regions_update
    )

    bpy.types.Scene.br_driven_armature = bpy.props.PointerProperty(
        type=bpy.types.Object,
        poll=lambda self, object: object.type == 'ARMATURE'
    )


def unregister():
    bpy.utils.unregister_class(BoneRegionsPanel)
    bpy.utils.unregister_class(SGB_UL_RegionForwardList)
    bpy.utils.unregister_class(SGB_UL_RegionList)
    bpy.utils.unregister_class(BoneRegionForwardEntryGroup)
    bpy.utils.unregister_class(BoneRegionForwardEntry)
    bpy.utils.unregister_class(BoneRegionEntry)

    del bpy.types.Scene.br_edit_mode
    del bpy.types.Scene.br_regions_list
    del bpy.types.Scene.br_regions_list_index
    del bpy.types.Scene.br_regions_forward_list
    del bpy.types.Scene.br_regions_forward_list_index
    del bpy.types.Scene.bone_regions_file_path
    del bpy.types.Scene.bone_regions_mapping_file_path
    del bpy.types.Scene.FAKE_BUTTON_load_bone_regions
    del bpy.types.Scene.FAKE_BUTTON_apply_bone_regions
    del bpy.types.Scene.FAKE_BUTTON_clear_bone_regions
    del bpy.types.Scene.FAKE_BUTTON_refresh_bone_regions
    del bpy.types.Scene.FAKE_BUTTON_unload_bone_regions
    del bpy.types.Scene.br_driven_armature
