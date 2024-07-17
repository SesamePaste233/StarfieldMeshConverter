import bpy, os, sys, NifIO, MorphIO, json

dir = os.path.dirname(os.path.realpath(__file__))
if dir not in sys.path:
	sys.path.append(dir)

import batch_operators as batch_op
import batch_ui as batch_ui
import batch_utils as batch_utils

#import imp
#imp.reload(batch_ui)
#imp.reload(batch_op)
#imp.reload(batch_utils)

bl_info = {
	"name": "Starfield Geometry Bridge - Batch Processing",
	"author": "SesamePaste & Deveris",
	"version": (0, 0, 1),
	"blender": (3, 5, 0),
	"location": "File > Import-Export",
	"description": "Batch processing of Starfield files.",
	"warning": "",
	"category": "Import-Export"
}

def register():
    batch_ui.register()
    batch_op.register()

def unregister():
    batch_ui.unregister()
    batch_op.unregister()
