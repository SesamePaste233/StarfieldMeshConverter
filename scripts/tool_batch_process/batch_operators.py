import bpy, os, sys

from bpy.props import CollectionProperty, StringProperty, IntProperty, BoolProperty, EnumProperty, FloatProperty

dir = os.path.dirname(os.path.realpath(__file__))
if dir not in sys.path:
	sys.path.append(dir)

import batch_utils
import batch_ui

"""

Generate outfit JSON files.
"""

class GenOutfitJson(bpy.types.Operator):
    bl_idname = "scene.gen_outfit_json"
    bl_label = "Generate outfit json"
    bl_description = "Generates outfit json files from .esm"
    filename: bpy.props.StringProperty(default='')
    directory: bpy.props.StringProperty(subtype="DIR_PATH")
    filter_glob: bpy.props.StringProperty(default="*.esm;*.esp", options={'HIDDEN'})

    def execute(self, event):
        addon_folder = os.path.dirname(os.path.abspath(__file__))
        batch_folder = os.path.join(addon_folder, "batch_files")
        esm = os.path.join(self.directory, self.filename)

        if not esm.endswith((".esm", ".esp")):
            self.report({'ERROR'}, "Please select esm or esp")
            return {'CANCELLED'}
        
        ret = batch_utils.generateOutfitJson(esm)

        if ret == False:
            self.report({'ERROR'}, "Something went wrong. Please contact author for assistance")
        
        batch_ui.refreshBatchList(batch_folder=batch_folder)
        
        return {'FINISHED'}
    
    def invoke(self, context, event):
        if not os.path.isfile(
                    os.path.join(os.path.dirname(os.path.abspath(__file__)), "gen_outfit", "genoutfit.exe")):
            
            self.report({'ERROR'}, "GenOutfit.exe not found.")
            return {'CANCELLED'}
        
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}


"""

Refresh Batch List.
"""

class RefreshBatchList(bpy.types.Operator):
    bl_idname = "scene.refresh_batch_list"
    bl_label = "Refresh list"
    bl_description = "Refresh batch list from assets folders"
    filename: bpy.props.StringProperty(default='')
    directory: bpy.props.StringProperty(subtype="DIR_PATH")

    def execute(self, event):
        addon_folder = os.path.dirname(os.path.abspath(__file__))
        batch_folder = os.path.join(addon_folder, "batch_files")
        
        if not os.path.isdir(batch_folder):
            os.makedirs(batch_folder)
        
        ret = batch_ui.refreshBatchList(batch_folder=batch_folder)

        if ret == False:
            self.report({'ERROR'}, "Something went wrong. Please contact author for assistance")
        
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return self.execute(event)

"""

Import from batch list.
"""

class ImportFromBatchList(bpy.types.Operator):
    bl_idname = "scene.import_from_batch_list"
    bl_label = "Import"
    bl_description = "Imports batch list selected entry"

    def execute(self, event):
        self.body_type = "any"
        self.morph_type = "Chargen"

        context = bpy.context

        plugin = context.scene.plugin_list[bpy.context.scene.plugin_list_index]

        self.assets_folder = context.scene.assets_folder_override[context.scene.assets_folder_override.find(plugin.name)].assets_folder
        self.correct_rotation = True
        self.max_lod = 1
        self.meshlets_debug = False
        self.tangents_debug = False
        self.import_as_read_only = False
        self.geo_bounding_debug = False
        self.boneinfo_debug = False
        self.load_havok_skeleten = False

        self.debug_delta_normal = False
        self.debug_padding = False
        self.debug_delta_tangent = False
        self.as_multiple = False
        self.use_attributes = False

        plugin_item = plugin.plugin_items[bpy.context.scene.batch_list_index]

        batch_utils.importFromBatchList(self, event, plugin_item)
        
        return {'FINISHED'}
    
    def invoke(self, context, event):
        return self.execute(event)

classes = [
    RefreshBatchList,
    ImportFromBatchList,
    GenOutfitJson
]

def register():
    for c in classes:
        bpy.utils.register_class(c)

def unregister():
    for c in classes:
        bpy.utils.unregister_class(c)
