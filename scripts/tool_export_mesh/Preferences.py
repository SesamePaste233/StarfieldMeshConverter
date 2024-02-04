import bpy
import os
import shutil
import utils_blender as utils_blender

class ChooseFileForPreferencesOperator(bpy.types.Operator):
    bl_idname = "object.choose_file_for_preferences"
    bl_label = "Choose File"

    filepath: bpy.props.StringProperty(subtype="FILE_PATH")
    filename: bpy.props.StringProperty()
    directory: bpy.props.StringProperty()

    #files: bpy.props.CollectionProperty(type=bpy.types.OperatorFileListElement)

    def execute(self, context):
        if self.filepath == "":
            self.report({'ERROR'}, "No file selected")
            return {'CANCELLED'}
        
        if os.path.exists(self.filepath) == False or os.path.isfile(self.filepath) == False:
            self.report({'ERROR'}, "Invalid file selected")
            return {'CANCELLED'}

        # Copy the file to the plugin directory
        plugin_dir = utils_blender.ThirdPartyFolderPath()
        texconv_path = os.path.join(plugin_dir, "texconv.exe")
        shutil.copy(self.filepath, texconv_path)

        preferences = utils_blender.get_preferences()
        preferences.texconv_path = texconv_path
        return {'FINISHED'}

    def invoke(self, context, event):
        context.window_manager.fileselect_add(self)
        return {'RUNNING_MODAL'}

    def draw(self, context):
        layout = self.layout
        layout.label(text="Choose File for Preferences")

class SGBPreferences(bpy.types.AddonPreferences):
    bl_idname = "tool_export_mesh"

    texconv_path: bpy.props.StringProperty(
        name="Texconv Path",
        subtype="FILE_PATH",
        default=os.path.join(utils_blender.ThirdPartyFolderPath(), "texconv.exe"),
        description="Path to texconv.exe"
    )

    def draw(self, context):
        layout = self.layout
        sublayout = layout.column(heading="Texconv Path")
        sublayout.enabled = False
        sublayout.prop(self, "texconv_path")
        layout.operator("object.choose_file_for_preferences")

def register():
    bpy.utils.register_class(SGBPreferences)
    bpy.utils.register_class(ChooseFileForPreferencesOperator)

def unregister():
    bpy.utils.unregister_class(SGBPreferences)
    bpy.utils.unregister_class(ChooseFileForPreferencesOperator)