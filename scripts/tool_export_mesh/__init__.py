import bpy
import os
import sys
from numpy.linalg import LinAlgError

dir = os.path.dirname(os.path.realpath(__file__))
if dir not in sys.path:
	sys.path.append(dir)

import utils_blender

import utils_common as utils

import MeshIO

import MorphIO

import PhysicsPanel as PhysicsPanel

import MaterialPanel as MaterialPanel

import ImportSkeleOp as ImportSkeleOp

import Preferences as Preferences

import BoneRegionsPanel as BoneRegionsPanel

import NifIOOperators
import MorphIOOperators
import MeshIOOperators

bl_info = {
	"name": "Starfield Geometry Bridge",
	"author": "SesamePaste & Deveris",
	"version": (1, 2, 0),
	"blender": (3, 5, 0),
	"location": "File > Import-Export",
	"description": "Export .nif, .dat and .mesh files for Starfield.",
	"warning": "",
	"category": "Import-Export",
	}

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

class SGB_UL_ShapeKeyListItems(bpy.types.UIList):

	def draw_item(self, context, layout, data, item, icon, active_data, active_propname, index):
		layout.prop(item, "name", text="", emboss=False)
		layout.prop(item, 'enabled', text="")

class shapeKeyList(bpy.types.PropertyGroup):
	name: bpy.props.StringProperty(name="Shape-key name", default="")
	enabled: bpy.props.BoolProperty(default=True)

class TransferShapeKeys(bpy.types.Operator):
	bl_idname = "object.transfer_shape_keys"
	bl_label = "Transfer shape-keys"
	bl_description = "Transfer shape-keys from active object to selected"
	bl_options = {'UNDO'}

	falloff_sigma: bpy.props.FloatProperty(
		name="Falloff Sigma",
		max=1.0,
		min=0.01,
		default=0.15
	)

	copy_range: bpy.props.FloatProperty(
		name="Copy Range",
		max=0.1,
		min=0.001,
		default=0.005
	)

	shape_key_list: bpy.props.CollectionProperty(
        type=shapeKeyList
    )

	shape_key_list_index: bpy.props.IntProperty(
		default=0
	)

	def draw(self, context):
		layout = self.layout

		if context.object == None or len(utils_blender.GetSelectedObjs(True)) == 0:
			self.report({'ERROR'}, "No selected objects found")
			return
		
		layout.label(text=f"From: {context.object.name}")
		layout.label(text=f"To: {[o.name for o in utils_blender.GetSelectedObjs(True)]}")

		row = layout.row(align=True)

		row.prop(self, "falloff_sigma", slider=True)
		row.prop(self, "copy_range", slider=True)

		row = layout.row(align=True)

		layout.template_list(
            "SGB_UL_ShapeKeyListItems",
            "",
            self, "shape_key_list",
            self, "shape_key_list_index",
			type='GRID',
			rows=1,
			columns=4
		)

	def execute(self, context):
		import utils_transfer as transfer
		reference = context.object
		target_list = [o for o in utils_blender.GetSelectedObjs(True) if o.type == "MESH"]

		if reference.data.shape_keys == None:
			reference.shape_key_add('Basis')

		transfer_sk = [sk.name for sk in self.shape_key_list if sk.enabled == True]
		
		if len(transfer_sk) == 0:
			self.report({'ERROR'}, "No shape-keys were selected for transfer")
			return {'CANCELLED'}

		bpy.ops.ed.undo_push()

		for target in target_list:
			try:
				transfer.TransferShapekeys(
					reference,
					target,
					transfer_sk,
					falloff_sigma=self.falloff_sigma,
					copy_range=self.copy_range
				)

			except LinAlgError as e:
				self.report({'ERROR'}, "Reference mesh has duplicate vertices.")
				return {'CANCELLED'}
		
		self.report({'INFO'}, f"Transferred {len(transfer_sk)} shape-keys")
		
		return {'FINISHED'}

	def invoke(self, context, event):
		transfer_from = context.object
		target_list = utils_blender.GetSelectedObjs(True)
		self.shape_key_list.clear()

		self.falloff_sigma = 0.15
		self.copy_range = 0.005

		if transfer_from == None or transfer_from.type != "MESH":
			self.report({'ERROR'}, "No active object found")
			return {'CANCELLED'}
		
		elif transfer_from.data.shape_keys == None or len(transfer_from.data.shape_keys.key_blocks) <= 1:
			self.report({'ERROR'}, "No shape-keys found")
			return {'CANCELLED'}
		
		elif len(target_list) == 0:
			self.report({'ERROR'}, "No selected objects found")
			return {'CANCELLED'}

		for sk_name in [sk.name for idx, sk in enumerate(context.object.data.shape_keys.key_blocks) if idx != 0]:
			item = self.shape_key_list.add()
			item.name = sk_name
			item.do_transfer = True
		
		context.window_manager.invoke_props_dialog(self, width=500)
		
		return {'RUNNING_MODAL'}

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

class MorphListRecalculateNormals(bpy.types.Operator):
    bl_idname = "object.morph_list_recalculate_normals"
    bl_label = "Recalculate Normals"
    bl_description = "Recalculate normals and tangents deltas for this shape-key."
	
    @classmethod
    def poll(cls, context):
        return True
	
    def execute(self, context):
        obj = context.object

        bpy.ops.ed.undo_push()

        rtn = utils_blender.morphPanelRecalculateActiveNormals(obj)

        if rtn == False:
            self.report({'ERROR'}, "Shape-key for recalculating normals not found.")
            return {'CANCELLED'}

        self.report({'INFO'}, f"Recalculated normals for {obj.data.shape_keys.key_blocks[obj.active_shape_key_index].name}")
		
        return {'FINISHED'}

    def invoke(self, context, event):
        return context.window_manager.invoke_props_dialog(self)

def menu_func_morphs(self, context):
	layout = self.layout
	layout.separator()

	col = layout.column()

	obj = context.object

	if obj.data.shape_keys == None or len(obj.data.shape_keys.key_blocks) == 0:
		return
	
	if obj.active_shape_key_index == 0:
		return

	sk = obj.data.shape_keys.key_blocks[obj.active_shape_key_index]
	col.label(text="Attributes")

	row = layout.row(align=True)
	row.label(text=f"NRM: {'Found' if obj.data.attributes.get(f'NRM_{sk.name}') != None else 'Not found'}")
	row.label(text=f"TAN: {'Found' if obj.data.attributes.get(f'TAN_{sk.name}') != None else 'Not found'}")
	row.label(text=f"COL: {'Found' if obj.data.attributes.get(f'COL_{sk.name}') != None else 'Not found'}")
	
	row = layout.row(align=True)
	#row.operator("object.morph_list_recalculate_normals")
	row.operator(TransferShapeKeys.bl_idname)

def morphPanelRemoveActive(obj):
    if obj.morph_list_index == len(obj.morph_list):
        obj.morph_list_index = len(obj.morph_list) - 1

    index = obj.morph_list_index

    if index == -1:
        return

    active = obj.morph_list[index]
    morph_name = active.name
    mesh = obj.data

    if f"NRM_{morph_name}" in mesh.attributes:
        mesh.attributes.remove(mesh.attributes.get(f"NRM_{morph_name}"))

    if f"COL_{morph_name}" in mesh.attributes:
        mesh.attributes.remove(mesh.attributes.get(f"COL_{morph_name}"))

    obj.morph_list.remove(index)

    obj.morph_list_index = index - 1 if index - 1 > -1 else 0

def update_func(self, context):
	utils.export_mesh_folder_path = context.scene.export_mesh_folder_path
	utils.assets_folder = context.scene.assets_folder

	utils.save("cached_paths", 'export_mesh_folder_path', 'assets_folder')

# Register the operators and menu entries
def register():
	utils.load("cached_paths")
	bpy.types.Scene.sgb_debug_mode = bpy.props.BoolProperty(
		name="Debug Mode",
		description="Debug option. DO NOT USE.",
		default=False
	)

	bpy.types.Scene.geometry_bridge_version = bpy.props.StringProperty(
		name="__geometry_bridge_version__",
		default = f"{bl_info['version'][0]}.{bl_info['version'][1]}.{bl_info['version'][2]}",
	)

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

	bpy.types.Scene.WEIGHTS = bpy.props.BoolProperty(
		name="Weights",
		description="Export vertex weights, only work with valid armature modifiers attached to objects.",
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

	bpy.types.Scene.use_secondary_uv = bpy.props.BoolProperty(
		name="Use Secondary UV",
		description="Use the topmost non-active UV map (if possible) as secondary UV",
		default=False
	)

	MeshIOOperators.register()
	MorphIOOperators.register()
	NifIOOperators.register()

	bpy.utils.register_class(MorphListRecalculateNormals)
	bpy.utils.register_class(ExportSFMeshOperator)
	bpy.utils.register_class(CreateAdvancedMorphEditOperator)
	bpy.utils.register_class(SGB_UL_ShapeKeyListItems)
	bpy.utils.register_class(shapeKeyList)
	bpy.utils.register_class(TransferShapeKeys)
	bpy.utils.register_class(ExportSFMeshPanel)
	bpy.types.DATA_PT_shape_keys.append(menu_func_morphs)

	PhysicsPanel.register()
	MaterialPanel.register()
	ImportSkeleOp.register()
	Preferences.register()
	BoneRegionsPanel.register()

def unregister():
	bpy.utils.unregister_class(CreateAdvancedMorphEditOperator)
	bpy.utils.unregister_class(ExportSFMeshOperator)
	bpy.utils.unregister_class(ExportSFMeshPanel)
	bpy.utils.unregister_class(MorphListRecalculateNormals)
	bpy.utils.unregister_class(SGB_UL_ShapeKeyListItems)
	bpy.utils.unregister_class(shapeKeyList)
	bpy.utils.unregister_class(TransferShapeKeys)
	bpy.types.DATA_PT_shape_keys.remove(menu_func_morphs)
	del bpy.types.Scene.sgb_debug_mode
	del bpy.types.Scene.geometry_bridge_version
	del bpy.types.Scene.export_mesh_folder_path
	del bpy.types.Scene.assets_folder
	del bpy.types.Scene.max_border
	del bpy.types.Scene.use_world_origin
	del bpy.types.Scene.WEIGHTS
	del bpy.types.Scene.export_sf_mesh_open_folder
	del bpy.types.Scene.export_sf_mesh_hash_result
	del bpy.types.Scene.export_morph
	del bpy.types.Scene.use_secondary_uv

	PhysicsPanel.unregister()
	MaterialPanel.unregister()
	ImportSkeleOp.unregister()
	Preferences.unregister()
	BoneRegionsPanel.unregister()

	MeshIOOperators.unregister()
	MorphIOOperators.unregister()
	NifIOOperators.unregister()

if __name__ == "__main__":
	register()