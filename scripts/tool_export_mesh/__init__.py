import bpy
import os
import sys

dir = os.path.dirname(os.path.realpath(__file__))
if dir not in sys.path:
	sys.path.append(dir)

import utils_common as utils

# Modules
import PhysicsPanel
import MaterialPanel
import ImportSkeleOp
import Preferences
import BoneRegionsPanel
import MorphPanel
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

def path_update_func(self, context):
	utils.export_mesh_folder_path = context.scene.export_mesh_folder_path
	utils.assets_folder = context.scene.assets_folder
	utils.save("cached_paths", 'export_mesh_folder_path', 'assets_folder')

utils.load("cached_paths")

__scene_global_attrs__ = {
	"sgb_debug_mode": utils.__prop_wrapper(
		bpy.props.BoolProperty,
		name="Debug Mode",
		description="Debug option. DO NOT USE.",
		default=False
	),
	"geometry_bridge_version": utils.__prop_wrapper(
		bpy.props.StringProperty,
		name="__geometry_bridge_version__",
		default = f"{bl_info['version'][0]}.{bl_info['version'][1]}.{bl_info['version'][2]}",
	),
	"export_mesh_folder_path": utils.__prop_wrapper(
		bpy.props.StringProperty,
		name="Export Folder",
		subtype='DIR_PATH',
		default= utils.export_mesh_folder_path,
		update = path_update_func
	),
	"assets_folder": utils.__prop_wrapper(
		bpy.props.StringProperty,
		name="Assets Folder",
		subtype='DIR_PATH',
		default= utils.assets_folder,
		update = path_update_func
	),
}

__modules__ = [
	PhysicsPanel,
	MaterialPanel,
	ImportSkeleOp,
	Preferences,
	BoneRegionsPanel,
	MorphPanel,
	MeshIOOperators,
	MorphIOOperators,
	NifIOOperators,
]

# Register the operators and menu entries
def register():

	for attr in __scene_global_attrs__:
		setattr(bpy.types.Scene, attr, __scene_global_attrs__[attr]())
	
	for module in __modules__:
		module.register()

def unregister():

	for attr in __scene_global_attrs__:
		delattr(bpy.types.Scene, attr)

	for module in __modules__:
		module.unregister()

if __name__ == "__main__":
	register()