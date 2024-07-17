import bpy

import MorphIO

import os

class ImportCustomMorph(bpy.types.Operator):
	bl_idname = "import_scene.custom_morph"
	bl_label = "Import Custom Morph"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='morph.dat')
	filter_glob: bpy.props.StringProperty(default="*.dat", options={'HIDDEN'})
	as_multiple: bpy.props.BoolProperty(
		name="As Multiple Objs",
		description="Import Morph as multiple objects, allows greater freedom in morph editing.",
		default=False
	)
	use_attributes: bpy.props.BoolProperty(
		name="Import attributes",
		description="Import normals, tangents and colors as attributes.",
		default=False
	)
	debug_delta_normal: bpy.props.BoolProperty(
		name="Debug Delta Normals",
		description="Debug option. DO NOT USE.",
		default=False
	)
	debug_delta_tangent: bpy.props.BoolProperty(
		name="Debug Delta Tangents",
		description="Debug option. DO NOT USE.",
		default=False
	)
	debug_padding: bpy.props.BoolProperty(
		name="Debug Padding",
		description="Debug option. DO NOT USE.",
		default=False
	)
	def execute(self, context):
		return MorphIO.ImportMorph(self, context, self)

	def invoke(self, context, event):
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ExportCustomMorph(bpy.types.Operator):
	bl_idname = "export_scene.custom_morph"
	bl_label = "Export Custom Morph"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='morph.dat')
	filter_glob: bpy.props.StringProperty(default="*.dat", options={'HIDDEN'})

	use_world_origin: bpy.props.BoolProperty(
		name="Use world origin",
		description="Use world instead of object origin as output geometry's origin.",
		default=True
	)

	def execute(self, context):
		rtn, _ = MorphIO.ExportMorph_alt(self, context, self.filepath, self)
		return rtn

	def invoke(self, context, event):
		self.filename = "morph.dat"

		if os.path.isdir(os.path.dirname(self.filepath)):
			self.filepath = os.path.join(os.path.dirname(self.filepath),self.filename)

		self.use_world_origin = context.scene.use_world_origin
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}
	
__classes__ = [
	ImportCustomMorph,
    ExportCustomMorph,
]

def menu_func_import_morph(self, context):
	self.layout.operator(
		ImportCustomMorph.bl_idname,
		text="Starfield Morph File (.dat)",
	)

def menu_func_export_morph(self, context):
	self.layout.operator(
		ExportCustomMorph.bl_idname,
		text="Starfield Morph File (.dat)",
	)

def register():
    for cls in __classes__:
        bpy.utils.register_class(cls)
		
    bpy.types.TOPBAR_MT_file_import.append(menu_func_import_morph)
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export_morph)
		
def unregister():
    for cls in __classes__:
        bpy.utils.unregister_class(cls)

    bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_morph)
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_morph)