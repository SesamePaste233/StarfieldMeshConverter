import bpy
import os

import MeshIO
import MorphIO

import utils_blender
import utils_common as utils

class ExportSFMeshOperator(bpy.types.Operator):
	"""Export the active object"""
	bl_idname = "export_scene.sfmesh"
	bl_label = "Export Active Mesh"

	def execute(self, context):
		_obj = bpy.context.active_object
		if _obj and _obj.type == 'MESH':
			original_active = utils_blender.GetActiveObject()
			original_selected = utils_blender.GetSelectedObjs(True)
			active_object_name = bpy.context.active_object.name
			success,num_verts_in_mesh,_,_ = MeshIO.ExportMesh(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, utils.sanitize_filename(active_object_name) + '.mesh'), self)

			if 'FINISHED' in success and context.scene.export_morph:
				utils_blender.SetSelectObjects(original_selected)
				utils_blender.SetActiveObject(original_active)
				morph_success, num_verts_in_morph = MorphIO.ExportMorph_alt(context.scene, context, os.path.join(context.scene.export_mesh_folder_path, utils.sanitize_filename(active_object_name) + '.dat'), self)
				
				if 'FINISHED' in morph_success:
					if num_verts_in_mesh != num_verts_in_morph:
						self.report({'WARNING'}, "The number of vertices in the mesh and morph data do not match. This may cause issues in the game.")
					else:
						self.report({'INFO'}, "Operation successful.")

				return morph_success
			
			return success
		
		self.report({'WARNING'}, "You didn't choose a object with geometry!")
		return {'CANCELLED'}

class CreateAdvancedMorphEditOperator(bpy.types.Operator):
	bl_idname = "object.advanced_morph_edit_create"
	bl_label = "Advanced Morph Edit"

	def execute(self, context):
		active_obj = utils_blender.GetActiveObject()
		ref_objs = utils_blender.GetSelectedObjs(True)
		if active_obj == None or active_obj.type != 'MESH':
			return {'CANCELLED'}
		
		target_objs = []

		rtn = MorphIO.CreateMorphObjSet(context.scene, context, active_obj, ref_objs, target_objs, self)
		
		return rtn

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
		layout.prop(context.scene, "max_border", text="Compression Border")
		layout.prop(context.scene, "use_world_origin", text="Use world origin")
		
		layout.label(text="Export Datatypes:") 
		layout.prop(context.scene, "WEIGHTS", text="Weights")
		
		layout.prop(context.scene, "export_morph", text="Morph Data")
		   
		layout.label(text="After Export:") 
		layout.prop(context.scene, "export_sf_mesh_open_folder", text="Open export folder")
		layout.prop(context.scene, "export_sf_mesh_hash_result", text="Hash file name")
		# Button to export the selected skeleton
		layout.operator("object.advanced_morph_edit_create", text = "Advanced Morph Edit")
		layout.operator("export_scene.sfmesh", text = "Export .mesh")

		layout.prop(context.scene, "sgb_debug_mode", text="Debug")


__scene_global_attrs__ = {
	"max_border": utils.__prop_wrapper(
		bpy.props.FloatProperty,
		name="Compression Border",
		description="2 for body parts, 0 (Auto) otherwise.",
		default=0,
	),
	"use_world_origin": utils.__prop_wrapper(
		bpy.props.BoolProperty,
		name="Use world origin",
		description="Use world instead of object origin as output geometry's origin.",
		default=True
	),
	"WEIGHTS": utils.__prop_wrapper(
		bpy.props.BoolProperty,
		name="Weights",
		description="Export vertex weights, only work with valid armature modifiers attached to objects.",
		default=True
	),
	"export_morph": utils.__prop_wrapper(
		bpy.props.BoolProperty,
		name="Morph Data",
		description="Export shape keys as morph keys",
		default=True
	),
	"export_sf_mesh_open_folder": utils.__prop_wrapper(
		bpy.props.BoolProperty,
		name="Open folder",
		default=False,
	),
	"export_sf_mesh_hash_result": utils.__prop_wrapper(
		bpy.props.BoolProperty,
		name="Generate hash names",
		description="Export into [hex1]\\[hex2].mesh instead of [model_name].mesh",
		default=False,
	),
	"use_secondary_uv": utils.__prop_wrapper(
		bpy.props.BoolProperty,
		name="Use Secondary UV",
		description="Use the topmost non-active UV map (if possible) as secondary UV",
		default=False
	),
}

__classes__ = [
	ExportSFMeshOperator,
	CreateAdvancedMorphEditOperator,
	ExportSFMeshPanel,
]

def register():
    for attr in __scene_global_attrs__:
        setattr(bpy.types.Scene, attr, __scene_global_attrs__[attr]())

    for cls in __classes__:
        bpy.utils.register_class(cls)
        
def unregister():
    for cls in __classes__:
        bpy.utils.unregister_class(cls)
		
    for attr in __scene_global_attrs__:
        delattr(bpy.types.Scene, attr)