import bpy
import os
import sys

dir = os.path.dirname(os.path.realpath(__file__))
if dir not in sys.path:
	sys.path.append(dir)

from version import __plugin_version__, Version

import PhysicsEditor.Utilities.utils_node as utils_node

import PhysicsEditor.AttrOperator as AttrOperator
import PhysicsEditor.PhysicsTree as PhysicsTree

import PhysicsEditor.ActivateVisOperator as ActivateVisOperator

bl_info = {
	"name": "Starfield Havok Physics Editor",
	"author": "SesamePaste",
	"version": (0, 15, 7),
	"blender": (3, 5, 0),
	"location": "File > Import-Export",
	"description": "Export havok physics data for starfield. Requires \"Starfield Geometry Bridge\" of the same version installed.",
	"warning": "",
	"category": "Import-Export",
	}

__plugin_version__ = Version(bl_info['version'])

def register():
	bpy.types.Scene.sf_physics_editor_version = bpy.props.StringProperty(
		name="__sf_physics_editor_version__",
		default = f"{bl_info['version'][0]}.{bl_info['version'][1]}.{bl_info['version'][2]}",
	)
	AttrOperator.register()
	PhysicsTree.register()
	ActivateVisOperator.register()

def unregister():
	ActivateVisOperator.unregister()
	AttrOperator.unregister()
	PhysicsTree.unregister()
	del bpy.types.Scene.sf_physics_editor_version