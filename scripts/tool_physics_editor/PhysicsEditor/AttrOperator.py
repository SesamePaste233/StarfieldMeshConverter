from typing import Set
import bpy
import bmesh
from bpy.types import Context, Event

class OBJECT_OT_add_custom_attribute_dialog(bpy.types.Operator):
    bl_idname = "object.add_custom_attribute_dialog"
    bl_label = "Mark Selected Elements"
    bl_options = {'REGISTER', 'UNDO'}

    def execute(self, context):
        bpy.ops.object.add_custom_attribute('INVOKE_DEFAULT')
        return {'FINISHED'}

class OBJECT_OT_add_custom_attribute(bpy.types.Operator):
    bl_idname = "object.add_custom_attribute"
    bl_label = "Mark Selected Elements"
    bl_options = {'REGISTER', 'UNDO'}

    def draw(self, context: Context):
        layout = self.layout
        if context.active_operator == self:
            layout.prop(context.scene, "add_custom_attribute_float_value")
        else:
            layout.label(text="Attribute Name:")
            layout.prop(context.scene, "add_custom_attribute_name", text="")
            layout.prop(context.scene, "add_custom_attribute_float_value")

    def execute(self, context):
        obj = context.active_object
        attribute_name = context.scene.add_custom_attribute_name
        float_value = context.scene.add_custom_attribute_float_value
        
        if obj is None or obj.type != 'MESH' or obj.mode != 'EDIT':
            self.report({'WARNING'}, "This operator only works in Edit Mode with a selected mesh object.")
            return {'CANCELLED'}
        
        selection_mode = bpy.context.tool_settings.mesh_select_mode[:]
    
        # Check if any element is selected in the current selection mode
        if not any(selection_mode):
            self.report({'WARNING'}, "No elements selected in the current mode.")
            return {'CANCELLED'}
        
        domain = None
        if selection_mode[0] == True:
            if domain is None:
                domain = 'POINT'
            else:
                self.report({'WARNING'}, "Multiple types of elements are selected.")
                return {'CANCELLED'}
        if selection_mode[1] == True:
            if domain is None:
                domain = 'EDGE'
            else:
                self.report({'WARNING'}, "Multiple types of elements are selected.")
                return {'CANCELLED'}
        if selection_mode[2] == True:
            if domain is None:
                domain = 'FACE'
            else:
                self.report({'WARNING'}, "Multiple types of elements are selected.")
                return {'CANCELLED'}
        
        attr = obj.data.attributes.get(attribute_name)
        if attr is not None:
            if attr.data_type != 'FLOAT' or attr.domain != domain:
                self.report({'WARNING'}, "There's an existing attribute with the same name!")
                return {'CANCELLED'}
            
        if attr is None:
            attr = obj.data.attributes.new(attribute_name, 'FLOAT', domain)
        
        mesh = obj.data
        bm = bmesh.from_edit_mesh(mesh)

        if selection_mode[0]:  # Vertex selection mode
            layer = bm.verts.layers.float.get(attr.name)
            for v in bm.verts:
                if v.select:
                    v[layer] = float_value
        elif selection_mode[1]:  # Edge selection mode
            layer = bm.edges.layers.float.get(attr.name)
            for e in bm.edges:
                if e.select:
                    e[layer] = float_value
        elif selection_mode[2]:  # Face selection mode
            layer = bm.faces.layers.float.get(attr.name)
            for f in bm.faces:
                if f.select:
                    f[layer] = float_value
                        
        bmesh.update_edit_mesh(mesh)
        bpy.ops.object.mode_set(mode='OBJECT')
        bpy.ops.object.mode_set(mode='EDIT')
        context.scene.add_custom_attribute_name = context.scene.add_custom_attribute_name + '_new'
        return {'FINISHED'}
    
    def invoke(self, context, event):
        wm = context.window_manager
        return wm.invoke_props_dialog(self)

def menu_func(self, context):
    self.layout.operator(OBJECT_OT_add_custom_attribute.bl_idname)

def menu_func_dialog(self, context):
    self.layout.operator(OBJECT_OT_add_custom_attribute_dialog.bl_idname)

def register():
    bpy.types.Scene.add_custom_attribute_name = bpy.props.StringProperty(
        name="Attribute Name",
        default="custom_attr",
        description="Name of the custom attribute",
    )
    bpy.types.Scene.add_custom_attribute_float_value = bpy.props.FloatProperty(
        name="Float Value",
        default=1.0,
        description="Value for the selected elements",
    )
    bpy.utils.register_class(OBJECT_OT_add_custom_attribute)
    bpy.utils.register_class(OBJECT_OT_add_custom_attribute_dialog)
    bpy.types.VIEW3D_MT_edit_mesh.append(menu_func)
    bpy.types.VIEW3D_MT_edit_mesh_context_menu.append(menu_func_dialog)


def unregister():
    bpy.types.VIEW3D_MT_edit_mesh.remove(menu_func)
    bpy.types.VIEW3D_MT_edit_mesh_context_menu.remove(menu_func_dialog)
    bpy.utils.unregister_class(OBJECT_OT_add_custom_attribute)
    bpy.utils.unregister_class(OBJECT_OT_add_custom_attribute_dialog)
    del bpy.types.Scene.add_custom_attribute_name
    del bpy.types.Scene.add_custom_attribute_float_value