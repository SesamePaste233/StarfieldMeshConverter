import bpy

import PhysicsEditor.PhysicsConverter as PhysicsConverter
import utils_common as utils

class ExportPhysicsDataOperator(bpy.types.Operator):
	bl_idname = "object.physics_data_export"
	bl_label = "Export Physics Data"

	def execute(self, context):
		physics_node_tree = context.scene.physics_node_tree_prop

		PhysicsConverter.get_physics_data(physics_node_tree)

		return {'FINISHED'}
	
class ExportPhysicsDataPanel(bpy.types.Panel):
	"""Panel for the Export Physics Data functionality"""
	bl_idname = "OBJECT_PT_export_physics_data"
	bl_label = "Export Physics Data"
	bl_space_type = 'VIEW_3D'
	bl_region_type = 'UI'
	bl_category = 'Tool'

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