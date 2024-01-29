from typing import Set
import bpy
from bpy.types import Context

import nif_armature

def get_skeleton_names(self, context):
    nif_armature.LoadAllSkeletonLookup()
    skel_names = nif_armature.GetAvailableSkeletonNames()
    if len(skel_names) == 0:
        return [("NONE", "None", "None")]
    return [(name, name.replace("_", " ").title(), name) for name in skel_names]

class OBJECT_OT_import_skeleton_from_assets(bpy.types.Operator):
    '''Import skeleton from assets'''
    bl_idname = "object.import_skeleton_from_assets"
    bl_label = "Import Skeleton From Assets"

    skeleton_name_enum: bpy.props.EnumProperty(
        name="Skeleton Name",
        description="Skeleton Name",
        items=get_skeleton_names,
        default=0,
    )

    def execute(self, context: Context) -> Set[int] | Set[str]:
        if self.skeleton_name_enum == 'NONE':
            return {'CANCELLED'}

        armature_obj = nif_armature.ImportArmatureFromJson(self.skeleton_name_enum, context.collection)
        armature_obj.name = self.skeleton_name_enum
        return {'FINISHED'}
    
    def invoke(self, context: Context, event: bpy.types.Event) -> Set[int] | Set[str]:
        return context.window_manager.invoke_props_dialog(self)

def menu_func_import(self, context: Context) -> None:
    self.layout.operator(OBJECT_OT_import_skeleton_from_assets.bl_idname, text="Skeleton From Assets")

def register():
    bpy.utils.register_class(OBJECT_OT_import_skeleton_from_assets)
    bpy.types.VIEW3D_MT_add.append(menu_func_import)

def unregister():
    bpy.types.VIEW3D_MT_add.remove(menu_func_import)
    bpy.utils.unregister_class(OBJECT_OT_import_skeleton_from_assets)
