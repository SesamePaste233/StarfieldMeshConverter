import bpy
import bmesh
from bpy.types import Context, Event

from PhysicsEditor.Prefabs.AttributeVisGeoNode import attr_vis_node_group
from PhysicsEditor.Prefabs.CapsuleGenGeoNode import capsule_gen_node_group
from PhysicsEditor.Prefabs.PlaneGenGeoNode import plane_gen_node_group

import PhysicsEditor.Utilities.utils_node as utils_node

class ReloadVisOperator(bpy.types.Operator):
	'''Reload if visualization is causing crashes, or after you updated the addon.'''
	bl_idname = "object.geo_node_vis_reload"
	bl_label = "Reload Vis Core"
	bl_options = {'REGISTER', 'UNDO'}

	def execute(self, context):
		if "Attr_Vis" in bpy.data.node_groups:
			bpy.data.node_groups.remove(bpy.data.node_groups["Attr_Vis"])
		attr_vis = attr_vis_node_group()
		
		if "Capsule_Gen" in bpy.data.node_groups:
			bpy.data.node_groups.remove(bpy.data.node_groups["Capsule_Gen"])
			if "Arc Instance" in bpy.data.node_groups:
				bpy.data.node_groups.remove(bpy.data.node_groups["Arc Instance"])
		capsule_gen = capsule_gen_node_group()

		if "Plane_Gen" in bpy.data.node_groups:
			bpy.data.node_groups.remove(bpy.data.node_groups["Plane_Gen"])
		plane_gen = plane_gen_node_group()

		trees = utils_node.get_all_physics_trees()
		for tree in trees:
			tree.update_tree(context)

		return {'FINISHED'}

def register():
	bpy.utils.register_class(ReloadVisOperator)

def unregister():
	bpy.utils.unregister_class(ReloadVisOperator)