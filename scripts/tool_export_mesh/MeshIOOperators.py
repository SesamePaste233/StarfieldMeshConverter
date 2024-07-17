import bpy
import os

import MeshIO
import MorphIO

import utils_blender
import utils_common as utils

# Export operator
class ExportCustomMesh(bpy.types.Operator):
	bl_idname = "export_scene.custom_mesh"
	bl_label = "Export Custom Mesh"
	
	filepath: bpy.props.StringProperty(options={'HIDDEN'})
	filename: bpy.props.StringProperty(default='untitled.mesh')
	filter_glob: bpy.props.StringProperty(default="*.mesh", options={'HIDDEN'})
	
	max_border: bpy.props.FloatProperty(
		name="Compression Border",
		description="2 for body parts, 0 otherwise.",
		default=0,
	)
	use_world_origin: bpy.props.BoolProperty(
		name="Use world origin",
		description="Use world instead of object origin as output geometry's origin.",
		default=True
	)
	WEIGHTS: bpy.props.BoolProperty(
		name="Weights",
		description="Export vertex weights, only work with valid armature modifiers attached to objects.",
		default=True
	)
	use_secondary_uv: bpy.props.BoolProperty(
		name="Use Secondary UV",
		description="Use the topmost non-active UV map (if possible) as secondary UV",
		default=False
	)

	export_morph: bpy.props.BoolProperty(
		name="Export morph data (if any)",
		description="Export shape keys as morph keys",
		default=False,
	)

	export_sf_mesh_open_folder: bpy.props.BoolProperty(
		name="Open folder after export",
		default=False,
	)
	export_sf_mesh_hash_result: bpy.props.BoolProperty(
		name="Generate hash names",
		description="Export into [hex1]\\[hex2].mesh instead of [name].mesh",
		default=False,
	)

	def execute(self,context):
		original_active = utils_blender.GetActiveObject()
		original_selected = utils_blender.GetSelectedObjs(True)
		mesh_success, _, _, _ = MeshIO.ExportMesh(self,context,self.filepath,self)

		if 'FINISHED' in mesh_success and self.export_morph:
			utils_blender.SetSelectObjects(original_selected)
			utils_blender.SetActiveObject(original_active)
			_file_name, _ =os.path.splitext(self.filepath)
			morph_success, _ = MorphIO.ExportMorph_alt(self,context, _file_name + ".dat", self)
			if 'FINISHED' in morph_success:
				self.report({'INFO'}, "Operation successful.")

			return morph_success
		
		return mesh_success

	def invoke(self, context, event):
		_obj = context.active_object
		if _obj:
			self.filename = utils.sanitize_filename(_obj.name) + '.mesh'
		else:
			self.filename = 'untitled.mesh'

		if os.path.isdir(os.path.dirname(self.filepath)):
			self.filepath = os.path.join(os.path.dirname(self.filepath),self.filename)

		self.max_border = context.scene.max_border
		self.use_world_origin = context.scene.use_world_origin
		self.WEIGHTS = context.scene.WEIGHTS
		self.export_sf_mesh_open_folder = context.scene.export_sf_mesh_open_folder
		self.export_sf_mesh_hash_result = context.scene.export_sf_mesh_hash_result
		self.export_morph = context.scene.export_morph
		self.use_secondary_uv = context.scene.use_secondary_uv

		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

# Import operator
class ImportCustomMesh(bpy.types.Operator):
	bl_idname = "import_scene.custom_mesh"
	bl_label = "Import Custom Mesh"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='untitled.mesh')
	
	filter_glob: bpy.props.StringProperty(default="*.mesh", options={'HIDDEN'})

	import_as_read_only: bpy.props.BoolProperty(
		name="As Read Only",
		description="The object will be marked as read only. You can import morph once, however, as long as there's morph data in this object, any attempt to import a new morph will be prohibited.",
		default=False
	)
	meshlets_debug: bpy.props.BoolProperty(
		name="Debug Meshlets",
		description="Debug option. DO NOT USE.",
		default=False
	)
	culldata_debug: bpy.props.BoolProperty(
		name="Debug CullData",
		description="Debug option. DO NOT USE.",
		default=False
	)
	tangents_debug: bpy.props.BoolProperty(
		name="Debug Tangent Vectors",
		description="Debug option. DO NOT USE.",
		default=False
	)

	def execute(self, context):
		return MeshIO.ImportMesh(self.filepath, self, context, self)

	def invoke(self, context, event):
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

__classes__ = [
	ExportCustomMesh,
    ImportCustomMesh,
]

# Add custom menu entries in the File menu
def menu_func_export(self, context):
	self.layout.operator(
		ExportCustomMesh.bl_idname,
		text="Starfield Geometry (.mesh)",
	)

def menu_func_import(self, context):
	self.layout.operator(
		ImportCustomMesh.bl_idname,
		text="Starfield Geometry (.mesh)",
	)

def register():
    for c in __classes__:
        bpy.utils.register_class(c)
        
    bpy.types.TOPBAR_MT_file_export.append(menu_func_export)
    bpy.types.TOPBAR_MT_file_import.append(menu_func_import)
		
def unregister():
    for c in __classes__:
        bpy.utils.unregister_class(c)
        
    bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)
    bpy.types.TOPBAR_MT_file_import.remove(menu_func_import)
