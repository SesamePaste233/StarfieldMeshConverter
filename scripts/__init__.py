import bpy
import os
import sys

dir = os.path.dirname(os.path.realpath(__file__))
if dir not in sys.path:
	sys.path.append(dir)

from utils_blender import GetActiveObject, SetActiveObject, GetSelectedObjs, SetSelectObjects

import utils
from utils import sanitize_filename, load, save

from MeshIO import ImportMesh, ExportMesh

from MorphIO import ImportMorph, ExportMorph

from NifIO import ImportNif, ExportNif

bl_info = {
	"name": "Starfield Mesh Exporter",
	"version": (0, 11, 0),
	"blender": (3, 5, 0),
	"location": "File > Import-Export",
	"description": "Export .mesh geometry file for starfield.",
	"warning": "",
	"category": "Import-Export",
	}

# Define a list of items with labels
export_items = [
	("GEO", "Geometry", "Export geometry data (positions and indices)."),
	("NORM", "Normals", "Export normals data."),
	("UV", "UV", "Export texture coordinates data."),
	("VERTCOLOR", "Vertex Color", "Export vertex color data."),
	("WEIGHTS", "Weights", "Export vertex groups data."),
]

# Export operator
class ExportCustomMesh(bpy.types.Operator):
	bl_idname = "export_scene.custom_mesh"
	bl_label = "Export Custom Mesh"
	
	filepath: bpy.props.StringProperty(options={'HIDDEN'})
	filename: bpy.props.StringProperty(default='untitled.mesh')
	filter_glob: bpy.props.StringProperty(default="*.mesh", options={'HIDDEN'})

	mesh_scale: bpy.props.FloatProperty(
		name="Scale",
		default=1,
	)
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
	normalize_weights: bpy.props.BoolProperty(
		name="Normalize weights",
		description="",
		default=True,
	)
	GEO: bpy.props.BoolProperty(
		name="Geometry",
		description=export_items[0][2],
		default=True
	)
	NORM: bpy.props.BoolProperty(
		name="Normals",
		description=export_items[1][2],
		default=True
	)
	VERTCOLOR: bpy.props.BoolProperty(
		name="Vertex Color",
		description=export_items[3][2],
		default=True
	)
	WEIGHTS: bpy.props.BoolProperty(
		name="Weights",
		description=export_items[4][2],
		default=True
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
		original_active = GetActiveObject()
		original_selected = GetSelectedObjs(True)
		mesh_success, _, _, _ = ExportMesh(self,context,self.filepath,self)

		if 'FINISHED' in mesh_success and self.export_morph:
			SetSelectObjects(original_selected)
			SetActiveObject(original_active)
			_file_name, _ =os.path.splitext(self.filepath)
			morph_success = ExportMorph(self,context, _file_name + ".dat", self)
			if 'FINISHED' in morph_success:
				self.report({'INFO'}, "Operation successful.")

			return morph_success
		
		return mesh_success

	def invoke(self, context, event):
		_obj = context.active_object
		if _obj:
			self.filename = _obj.name + '.mesh'
		else:
			self.filename = 'untitled.mesh'

		self.mesh_scale = context.scene.mesh_scale
		self.max_border = context.scene.max_border
		self.use_world_origin = context.scene.use_world_origin
		self.normalize_weights = context.scene.normalize_weights
		self.GEO = context.scene.GEO
		self.NORM = context.scene.NORM
		self.VERTCOLOR = context.scene.VERTCOLOR
		self.WEIGHTS = context.scene.WEIGHTS
		self.export_sf_mesh_open_folder = context.scene.export_sf_mesh_open_folder
		self.export_sf_mesh_hash_result = context.scene.export_sf_mesh_hash_result
		self.export_morph = context.scene.export_morph

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
		return ImportMesh(self, context, self)

	def invoke(self, context, event):
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ImportCustomNif(bpy.types.Operator):
	bl_idname = "import_scene.custom_nif"
	bl_label = "Import Custom Nif"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='untitled.nif')
	
	filter_glob: bpy.props.StringProperty(default="*.nif", options={'HIDDEN'})

	assets_folder: bpy.props.StringProperty(subtype="FILE_PATH")
	import_as_read_only: bpy.props.BoolProperty(
		name="As Read Only",
		description="The object will be marked as read only. You can import morph once, however, as long as there's morph data in this object, any attempt to import a new morph will be prohibited.",
		default=False
	)
	correct_rotation: bpy.props.BoolProperty(
		name="Correct Rotation",
		description="Correct Beth's weird rotations and translations. Makes the model consistent with the skeleton.",
		default=True
	)
	max_lod: bpy.props.IntProperty(
		name="Max Lod",
		description="Maximum Loaded LoD, 0 for loading all LoDs.",
		default=1,
	)
	boneinfo_debug: bpy.props.BoolProperty(
		name="Debug BoneInfo",
		description="Debug option. DO NOT USE.",
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
		return ImportNif(self, context, self)

	def invoke(self, context, event):
		self.assets_folder = context.scene.assets_folder
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}
	
class ExportCustomNif(bpy.types.Operator):
	bl_idname = "export_scene.custom_nif"
	bl_label = "Export Custom Nif"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='untitled.nif')
	
	filter_glob: bpy.props.StringProperty(default="*.nif", options={'HIDDEN'})

	export_template: bpy.props.EnumProperty(
		name="Nif Template",
		description="",
		items=(('None', "As Is", "Export all items parented to the root node that are interpretable as Nif objects."),
			   ('Auto', "Based On Root Name", "Auto select template based on the name of the root."),),
		default='None',
	)

	mesh_scale: bpy.props.FloatProperty(
		name="Scale",
		default=1,
	)
	max_border: bpy.props.FloatProperty(
		name="Compression Border",
		description="2 for body parts, 0 otherwise.",
		default=0,
	)
	normalize_weights: bpy.props.BoolProperty(
		name="Normalize weights",
		description="",
		default=True,
	)
	GEO: bpy.props.BoolProperty(
		name="Geometry",
		description=export_items[0][2],
		default=True
	)
	NORM: bpy.props.BoolProperty(
		name="Normals",
		description=export_items[1][2],
		default=True
	)
	VERTCOLOR: bpy.props.BoolProperty(
		name="Vertex Color",
		description=export_items[3][2],
		default=True
	)
	WEIGHTS: bpy.props.BoolProperty(
		name="Weights",
		description=export_items[4][2],
		default=True
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
		default=True,
	)

	use_world_origin = False

	def execute(self, context):
		return ExportNif(self, context, self)

	def invoke(self, context, event):
		_obj = context.active_object
		if _obj:
			self.filename = _obj.name + '.nif'
		else:
			self.filename = 'untitled.nif'

		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ImportCustomMorph(bpy.types.Operator):
	bl_idname = "import_scene.custom_morph"
	bl_label = "Import Custom Morph"
	
	filepath: bpy.props.StringProperty(subtype="FILE_PATH")
	filename: bpy.props.StringProperty(default='morph.dat')
	filter_glob: bpy.props.StringProperty(default="*.dat", options={'HIDDEN'})
	debug_delta_normal: bpy.props.BoolProperty(
		name="Debug Delta Normals",
		description="Debug option. DO NOT USE.",
		default=False
	)
	def execute(self, context):
		return ImportMorph(self, context, self)

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
		return ExportMorph(self, context, self.filepath, self)

	def invoke(self, context, event):
		self.filename = "morph.dat"
		self.use_world_origin = context.scene.use_world_origin
		context.window_manager.fileselect_add(self)
		return {'RUNNING_MODAL'}

class ExportSFMeshOperator(bpy.types.Operator):
	"""Export the active object"""
	bl_idname = "export_scene.sfmesh"
	bl_label = "Export Active Mesh"
	
	folder_path: bpy.props.StringProperty(subtype="DIR_PATH", default="")

	def execute(self, context):
		_obj = bpy.context.active_object
		if _obj and _obj.type == 'MESH':
			original_active = GetActiveObject()
			original_selected = GetSelectedObjs(True)
			active_object_name = bpy.context.active_object.name
			success,_,_,_ = ExportMesh(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, sanitize_filename(active_object_name) + '.mesh'), self)

			if 'FINISHED' in success and context.scene.export_morph:
				SetSelectObjects(original_selected)
				SetActiveObject(original_active)
				morph_success = ExportMorph(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, sanitize_filename(active_object_name) + '.dat'), self)
				
				if 'FINISHED' in morph_success:
					self.report({'INFO'}, "Operation successful.")

				return morph_success
			
			return success
		
		self.report({'WARNING'}, "You didn't choose a object with geometry!")
		return {'CANCELLED'}

class ExportSFMeshPanel(bpy.types.Panel):
	"""Panel for the Export Starfield Mesh functionality"""
	bl_idname = "OBJECT_PT_export_sf_mesh"
	bl_label = "Export Starfield Mesh"
	bl_space_type = 'VIEW_3D'
	bl_region_type = 'UI'
	bl_category = 'Tool'

	def draw(self, context):
		layout = self.layout
		# Folder path input
		layout.label(text="Export Folder:")
		layout.prop(context.scene, "export_mesh_folder_path", text="")
		layout.label(text="Assets Folder:")
		layout.prop(context.scene, "assets_folder", text="")

		# Export settings
		layout.label(text="Export Settings:")
		layout.prop(context.scene, "mesh_scale", text="Scale")
		layout.prop(context.scene, "max_border", text="Compression Border")
		layout.prop(context.scene, "use_world_origin", text="Use world origin")
		layout.prop(context.scene, "normalize_weights", text="Normalize weights")
		
		
		layout.label(text="Export Datatypes:") 
		# Create a checkbox for each item
		for item in export_items:
			layout.prop(context.scene, item[0], text=item[1])
		
		layout.prop(context.scene, "export_morph", text="Morph Data")
		   
		layout.label(text="After Export:") 
		layout.prop(context.scene, "export_sf_mesh_open_folder", text="Open export folder")
		layout.prop(context.scene, "export_sf_mesh_hash_result", text="Hash file name")
		# Button to export the selected skeleton
		layout.operator("export_scene.sfmesh", text="Export .mesh")


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

def menu_func_import_nif(self, context):
	self.layout.operator(
		ImportCustomNif.bl_idname,
		text="Starfield Nif File (.nif)",
	)

def menu_func_export_nif(self, context):
	self.layout.operator(
		ExportCustomNif.bl_idname,
		text="Starfield Nif File (.nif)",
	)

def update_func(self, context):
	utils.export_mesh_folder_path = context.scene.export_mesh_folder_path
	utils.assets_folder = context.scene.assets_folder

	save("cached_paths", 'export_mesh_folder_path', 'assets_folder')
	print(globals())

# Register the operators and menu entries
def register():
	load("cached_paths")

	bpy.types.Scene.export_mesh_folder_path = bpy.props.StringProperty(
		name="Export Folder",
		subtype='DIR_PATH',
		default= utils.export_mesh_folder_path,
		update = update_func
	)
	bpy.types.Scene.assets_folder = bpy.props.StringProperty(
		name="Assets Folder",
		subtype='DIR_PATH',
		default= utils.assets_folder,
		update = update_func
	)
	bpy.types.Scene.mesh_scale = bpy.props.FloatProperty(
		name="Scale",
		default=1,
	)
	bpy.types.Scene.max_border = bpy.props.FloatProperty(
		name="Compression Border",
		description="2 for body parts, 0 (Auto) otherwise.",
		default=0,
	)
	bpy.types.Scene.use_world_origin = bpy.props.BoolProperty(
		name="Use world origin",
		description="Use world instead of object origin as output geometry's origin.",
		default=True
	)
	bpy.types.Scene.normalize_weights = bpy.props.BoolProperty(
		name="Normalize weights",
		description="",
		default=False
	)
	bpy.types.Scene.GEO = bpy.props.BoolProperty(
		name="Geometry",
		description=export_items[0][2],
		default=True
	)
	bpy.types.Scene.NORM = bpy.props.BoolProperty(
		name="Normals",
		description=export_items[1][2],
		default=True
	)
	bpy.types.Scene.VERTCOLOR = bpy.props.BoolProperty(
		name="Vertex Color",
		description=export_items[3][2],
		default=True
	)
	bpy.types.Scene.WEIGHTS = bpy.props.BoolProperty(
		name="Weights",
		description=export_items[4][2],
		default=True
	)
	bpy.types.Scene.export_morph = bpy.props.BoolProperty(
		name="Morph Data",
		description="Export shape keys as morph keys",
		default=True
	)

	bpy.types.Scene.export_sf_mesh_open_folder = bpy.props.BoolProperty(
		name="Open folder",
		default=False,
	)
	bpy.types.Scene.export_sf_mesh_hash_result = bpy.props.BoolProperty(
		name="Generate hash names",
		description="Export into [hex1]\\[hex2].mesh instead of [model_name].mesh",
		default=False,
	)

	bpy.utils.register_class(ExportCustomMesh)
	bpy.utils.register_class(ImportCustomMesh)
	bpy.utils.register_class(ImportCustomNif)
	bpy.utils.register_class(ImportCustomMorph)
	bpy.utils.register_class(ExportCustomMorph)
	bpy.utils.register_class(ExportSFMeshOperator)
	bpy.utils.register_class(ExportSFMeshPanel)
	bpy.utils.register_class(ExportCustomNif)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import_morph)
	bpy.types.TOPBAR_MT_file_import.append(menu_func_import_nif)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export_morph)
	bpy.types.TOPBAR_MT_file_export.append(menu_func_export_nif)

def unregister():
	bpy.utils.unregister_class(ExportSFMeshOperator)
	bpy.utils.unregister_class(ExportSFMeshPanel)
	bpy.utils.unregister_class(ExportCustomMesh)
	bpy.utils.unregister_class(ImportCustomMesh)
	bpy.utils.unregister_class(ImportCustomNif)
	bpy.utils.unregister_class(ImportCustomMorph)
	bpy.utils.unregister_class(ExportCustomMorph)
	bpy.utils.unregister_class(ExportCustomNif)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_nif)
	bpy.types.TOPBAR_MT_file_import.remove(menu_func_import_morph)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_morph)
	bpy.types.TOPBAR_MT_file_export.remove(menu_func_export_nif)
	del bpy.types.Scene.export_mesh_folder_path
	del bpy.types.Scene.assets_folder
	del bpy.types.Scene.mesh_scale
	del bpy.types.Scene.max_border
	del bpy.types.Scene.use_world_origin
	del bpy.types.Scene.normalize_weights
	del bpy.types.Scene.GEO
	del bpy.types.Scene.NORM
	del bpy.types.Scene.VERTCOLOR
	del bpy.types.Scene.WEIGHTS
	del bpy.types.Scene.export_sf_mesh_open_folder
	del bpy.types.Scene.export_sf_mesh_hash_result
	del bpy.types.Scene.export_morph

if __name__ == "__main__":
	register()