import bpy
import os
import json

import PhysicsConverter as PhysicsConverter

import utils_common as utils
import utils_blender as utils_blender

import addon_utils

import MeshConverter

import version

class ExportPhysicsDataOperator(bpy.types.Operator):
	bl_idname = "object.physics_data_export"
	bl_label = "Export As Portable"

	def execute(self, context):
		if version.compare_versions(context.scene.geometry_bridge_version, context.scene.sf_physics_editor_version, 'tool_physics_editor') is False:
			self.report({'ERROR'}, "Physics editor version does not match geometry bridge version.")
			return {'CANCELLED'}
		
		physics_node_tree = context.scene.physics_node_tree_prop

		if physics_node_tree is None:
			self.report({'ERROR'}, "No physics node tree selected.")
			return {'CANCELLED'}

		output_file = os.path.join(context.scene.physics_file_path, f"{utils.sanitize_filename(physics_node_tree.name)}.bin")

		data_dict, error_msg = PhysicsConverter.get_physics_data(physics_node_tree)

		if data_dict is None:
			self.report({'ERROR'}, error_msg)
			physics_node_tree.update_tree(context)
			return {'CANCELLED'}

		json_data = json.dumps(data_dict)

        # Save the physics data to a json file
		if utils_blender.is_plugin_debug_mode():
			physics_data_path = os.path.join(os.path.dirname(output_file), 'physics_data_debug.json')
			with open(physics_data_path, 'w') as f:
				json.dump(data_dict, f)

		rtn = MeshConverter.ComposePhysicsDataFromJson(json_data, MeshConverter.Platform.HCL_PLATFORM_X64, output_file, utils_blender.is_plugin_debug_mode())

		if not rtn:
			self.report({'ERROR'}, f"Dll failed to compose physics data. Error message: \"{rtn.what()}\".")
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
		layout.operator("object.geo_node_vis_reload")
		
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