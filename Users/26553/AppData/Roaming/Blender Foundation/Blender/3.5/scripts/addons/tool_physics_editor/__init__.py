import bpy
import os
import sys

dir = os.path.dirname(os.path.realpath(__file__))
if dir not in sys.path:
	sys.path.append(dir)

import PhysicsEditor.AttrOperator as AttrOperator
import PhysicsEditor.PhysicsTree as PhysicsTree

bl_info = {
	"name": "Starfield Havok Physics Editor",
	"version": (0, 15, 0),
	"blender": (3, 5, 0),
	"location": "File > Import-Export",
	"description": "Export havok physics data for starfield. Requires \"Starfield Geometry Bridge\" of the same version installed.",
	"warning": "",
	"category": "Import-Export",
	}

def register():
    AttrOperator.register()
    PhysicsTree.register()

def unregister():
    AttrOperator.unregister()
    PhysicsTree.unregister()