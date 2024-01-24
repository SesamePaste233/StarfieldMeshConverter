import bpy
import os
import json

import PhysicsConverter as PhysicsConverter

import utils_common as utils

import addon_utils

import MeshConverter

class ExportPhysicsDataOperator(bpy.types.Operator):
	bl_idname = "object.physics_data_export"
	bl_label = "Export Physics Data"

	def execute(self, context):
		if context.scene.sf_physics_editor_version != context.scene.geometry_bridge_version:
			self.report({'ERROR'}, "Physics editor version does not match geometry bridge version.")
			return {'CANCELLED'}
		
		physics_node_tree = context.scene.physics_node_tree_prop

		if physics_node_tree is None:
			self.report({'ERROR'}, "No physics node tree selected.")
			return {'CANCELLED'}

		output_file = os.path.join(context.scene.physics_file_path, f"{utils.sanitize_filename(physics_node_tree.name)}.bin")

		data_dict = PhysicsConverter.get_physics_data(physics_node_tree.get_output_nodes(), physics_node_tree)

		if data_dict is None:
			self.report({'ERROR'}, "Failed to compose physics data from node graph.")
			return {'CANCELLED'}

		json_data = json.dumps(data_dict)

		rtn = MeshConverter.ComposePhysicsDataFromJson(json_data, MeshConverter.Platform.HCL_PLATFORM_X64, output_file, True)

		if not rtn:
			self.report({'ERROR'}, f"Failed to compose physics data. Error message: \"{rtn.what()}\".")
			return {'CANCELLED'}
		
		self.report({'INFO'}, "Physics data exported successfully.")

		return {'FINISHED'}
	
class ExportPhysicsDataPanel(bpy.types.Panel):
	"""Panel for the Export Physics Data functionality"""
	bl_idname = "OBJECT_PT_export_physics_data"
	bl_label = "Export Physics Data"
	bl_space_type = 'VIEW_3D'
	bl_region_type = 'UI'
	bl_category = 'Tool'

	@classmethod
	def poll(cls, context):
		_, enabled = addon_utils.check("tool_physics_editor")
		return enabled

	def draw(self, context):
		layout = self.layout
		# Folder path input
		layout.label(text="Export Folder:")
		layout.prop(context.scene, "physics_file_path", text="")

		layout.prop(context.scene, "physics_node_tree_prop", text="Physics Node Tree")
		# Export button
		layout.operator("object.physics_data_export", text="Export Physics Data")
		
def register():
	bpy.types.Scene.physics_node_tree_prop = bpy.props.PointerProperty(type=bpy.types.NodeTree, poll = lambda self, object: object.bl_idname == 'hclPhysicsTreeType')

	bpy.types.Scene.physics_file_path = bpy.props.StringProperty(
		name="Physics File Path",
		subtype='FILE_PATH',
		default= utils.export_mesh_folder_path,
	)

	bpy.utils.register_class(ExportPhysicsDataOperator)
	bpy.utils.register_class(ExportPhysicsDataPanel)
	
def unregister():
	bpy.utils.unregister_class(ExportPhysicsDataPanel)
	bpy.utils.unregister_class(ExportPhysicsDataOperator)

	del bpy.types.Scene.physics_node_tree_prop
	del bpy.types.Scene.physics_file_path