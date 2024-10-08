import bpy
import utils_bone_regions as ubr
import BoneRegionsReader
import os

def sculpt_regions_enum_items(self, context):
	items = [(region_name, region_name, "") for region_name in ubr.br_data().sculpt_regions]
	if len(items) == 0:
		items.append(("NONE", "NONE", "There's no sculpt regions. Create one first."))

	return items

def sculpt_region_sliders_enum_items(self, context):
	region_name = self.region_name
	region = ubr.br_data().regions.get(region_name, None)
	if region is None:
		return [("NONE", "NONE", "There's no sculpt regions. Create one first.")]
	
	items = [(slider_name, slider_name, "") for slider_name in region.sliders]
	if len(items) == 0:
		items.append(("NONE", "NONE", "There's no sliders in this sculpt region. Create one first."))

	return items

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
               
class SculptRegionsAddOperator(bpy.types.Operator):
    """Add new slider to a sculpt region"""
    bl_idname = "object.sculpt_regions_add"
    bl_label = "Add New Slider"
    bl_options = {'REGISTER', 'UNDO'}

    region_name: bpy.props.EnumProperty(name="Region Name", items=[(region, region, region) for region in BoneRegionsReader.__all_sculpt_regions__])
    slider_name: bpy.props.StringProperty(name="Slider Name", default="")
    is_zero_to_one: bpy.props.BoolProperty(name="Is Zero To One", default=True)

    def execute(self, context):
        if self.slider_name == "":
            self.report({'ERROR'}, "Slider name cannot be empty")
            return {'CANCELLED'}

        rtn = ubr.add_new_slider(self.region_name, self.slider_name, self.is_zero_to_one)
        reload_sculpt_region_forward_list(self, context)
        if not rtn:
            self.report({'ERROR'}, f"Failed to add slider {self.slider_name} to region {self.region_name}")
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)
    
    def draw(self, context):
        layout = self.layout
        layout.prop(self, "region_name")
        layout.prop(self, "slider_name")
        layout.prop(self, "is_zero_to_one")

class SculptRegionsRemoveOperator(bpy.types.Operator):
    """Remove slider from a sculpt region"""
    bl_idname = "object.sculpt_regions_remove"
    bl_label = "Remove Slider"
    bl_options = {'REGISTER', 'UNDO'}

    region_name: bpy.props.EnumProperty(name="Region Name", items=sculpt_regions_enum_items)
    slider_name: bpy.props.EnumProperty(name="Slider Name", items=sculpt_region_sliders_enum_items)

    def execute(self, context):
        rtn = ubr.remove_slider(self.region_name, self.slider_name)
        reload_sculpt_region_forward_list(self, context)
        if not rtn:
            self.report({'ERROR'}, f"Failed to remove slider {self.slider_name} from region {self.region_name}")
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)
    
    def draw(self, context):
        layout = self.layout
        layout.prop(self, "region_name")
        layout.prop(self, "slider_name")

class SculptRegionsUpdateOperator(bpy.types.Operator):
    """Update slider from a sculpt region"""
    bl_idname = "object.sculpt_regions_update"
    bl_label = "Update Slider"
    bl_options = {'REGISTER', 'UNDO'}

    region_name: bpy.props.EnumProperty(name="Region Name", items=sculpt_regions_enum_items)
    slider_name: bpy.props.EnumProperty(name="Slider Name", items=sculpt_region_sliders_enum_items)
    new_name: bpy.props.StringProperty(name="New Name", default="")
    new_is_zero_to_one: bpy.props.BoolProperty(name="Is Zero To One", default=True)

    def execute(self, context):
        rtn = ubr.update_slider(self.region_name, self.slider_name, self.new_name, self.new_is_zero_to_one)
        reload_sculpt_region_forward_list(self, context)
        if not rtn:
            self.report({'ERROR'}, f"Failed to update slider {self.slider_name} from region {self.region_name}")
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)
    
    def draw(self, context):
        layout = self.layout
        layout.prop(self, "region_name")
        layout.prop(self, "slider_name")
        layout.prop(self, "new_name")
        layout.prop(self, "new_is_zero_to_one")

def is_maxima_update(self, context):
    if self.is_maxima and self.is_minima:
        self.is_minima = False
    
    if not self.is_maxima and not self.is_minima:
        self.is_minima = True

def is_minima_update(self, context):
    if self.is_maxima and self.is_minima:
        self.is_maxima = False
    
    if not self.is_maxima and not self.is_minima:
        self.is_maxima = True

class SculptRegionsCollectOperator(bpy.types.Operator):
    """Collect sculpt data from active armature"""
    bl_idname = "object.sculpt_regions_collect"
    bl_label = "Collect Sculpt Data"
    bl_options = {'REGISTER', 'UNDO'}

    region_name: bpy.props.EnumProperty(name="Region Name", items=sculpt_regions_enum_items)
    slider_name: bpy.props.EnumProperty(name="Slider Name", items=sculpt_region_sliders_enum_items)
    is_maxima: bpy.props.BoolProperty(name="Maxima", default=True, update=is_maxima_update)
    is_minima: bpy.props.BoolProperty(name="Minima", default=False, update=is_minima_update)

    def execute(self, context):
        armature = bpy.context.scene.br_driven_armature
        if armature is None:
            self.report({'ERROR'}, "No armature selected")
            return {'CANCELLED'}
        else:
            bones = ubr.facebones_with_pose(armature)
            if len(bones) == 0:
                self.report({'ERROR'}, "No facebones with transform found in armature")
                return {'CANCELLED'}

        slider = ubr.get_slider(self.region_name, self.slider_name)
        if slider is not None and slider.is_zero_to_one:
             self.is_maxima = True
        rtn = ubr.collect_sculpt(self.region_name, self.slider_name, self.is_maxima)
        if not rtn:
            self.report({'ERROR'}, f"Failed to collect sculpt data from armature")
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)
    
    def draw(self, context):
        layout = self.layout
        layout.prop(self, "region_name")
        layout.prop(self, "slider_name")

        col = layout.column()

        slider = ubr.get_slider(self.region_name, self.slider_name)
        if slider is not None and slider.is_zero_to_one:
            self.is_maxima = True
            col.enabled = False

        row = col.row()
        row.prop(self, "is_maxima", toggle=True)
        row.prop(self, "is_minima", toggle=True)
    
        layout.label(text="Bones With Transform:")
        armature = bpy.context.scene.br_driven_armature
        box = layout.box()
        if armature is None:
            box.label(text="No armature selected")
        else:
            for bone_name in ubr.facebones_with_pose(armature):
                box.label(text=bone_name)

class SculptRegionsFileSaveOperator(bpy.types.Operator):
    """Save sculpt regions data to file"""
    bl_idname = "object.sculpt_regions_file_save"
    bl_label = "Save Sculpt Regions Data"
    bl_options = {'REGISTER', 'UNDO'}

    filepath: bpy.props.StringProperty(subtype="FILE_PATH")
    filename: bpy.props.StringProperty(default='[RACENAME]FacialBoneRegions[SEX].txt')

    filter_glob: bpy.props.StringProperty(default="*.txt", options={'HIDDEN'})

    def execute(self, context):
        ubr.save_sculpt_regions(self.filepath)
        return {'FINISHED'}

    def invoke(self, context, event):
        
        original_filepath = context.scene.bone_regions_file_path

        if original_filepath != "":
            self.filename = os.path.basename(original_filepath)
            self.filepath = original_filepath
        
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

__classes__ = [
    SculptRegionsAddOperator,
    SculptRegionsRemoveOperator,
    SculptRegionsUpdateOperator,
    SculptRegionsCollectOperator,
    SculptRegionsFileSaveOperator,
]

def register():
    for cls in __classes__:
        bpy.utils.register_class(cls)

def unregister():
    for cls in __classes__:
        bpy.utils.unregister_class(cls)