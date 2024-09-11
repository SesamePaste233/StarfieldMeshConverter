from typing import Set
import os
import bpy
from bpy.types import Context, Event
import MaterialConverter as MaterialConverter
import utils_common as utils
import utils_blender as utils_blender
import utils_material as utils_material

def get_mat_items():
    items = [("None", "None", "")]
    try:
        mat_ngs = utils_material.get_all_mat_trees_from_obj(utils_blender.GetActiveObject())
        return items + [(mat_ng.name, mat_ng.name, "") for mat_ng in mat_ngs]
    except:
        return items
    
class NewMaterialOperator(bpy.types.Operator):
    """New Material Operator"""
    bl_idname = "object.sf_new_material"
    bl_label = "New Material"

    sf_new_mat_name: bpy.props.StringProperty(
        name="Material Name",
        default="Starfield Mat"
    )

    apply_to_active: bpy.props.BoolProperty(
        name="Apply To Active Object",
        default=False
    )

    def execute(self, context):
        active_obj = utils_blender.GetActiveObject()
        mat = utils_material.new_mat(self.sf_new_mat_name)
        self.sf_new_mat_name = mat.name + "_new"
        context.scene.sf_export_material_name = mat
        if self.apply_to_active:
            bpy.ops.object.sf_apply_material()
        return {'FINISHED'}
    
    def invoke(self, context: Context, event: Event) -> Set[int] | Set[str]:
        active_obj = utils_blender.GetActiveObject()
        if active_obj is not None:
            self.sf_new_mat_name = utils.sanitize_filename(active_obj.name) + "_mat"
        return context.window_manager.invoke_props_dialog(self)
    
class ApplyMaterialOnObjectOperator(bpy.types.Operator):
    """Apply Material On Object Operator"""
    bl_idname = "object.sf_apply_material"
    bl_label = "Apply Material To Active Object"

    def execute(self, context):
        active_obj = utils_blender.GetActiveObject()
        if active_obj is not None and active_obj.type != 'MESH':
            self.report({'ERROR'}, "Active object is not a mesh")
            return {'CANCELLED'}
        mat = context.scene.sf_export_material_name
        active_obj.active_material = mat

        color_attrs = active_obj.data.color_attributes
        if "Color" not in color_attrs:
            color_attrs.new("Color", "FLOAT_COLOR", "POINT")
        color_attrs.active_color = color_attrs['Color']
        return {'FINISHED'}

class ExportMaterialOperator(bpy.types.Operator):
    """Export Material Operator"""
    bl_idname = "object.material_data_export"
    bl_label = "Export Material Data"

    def execute(self, context):
        texconv_path = utils_blender.get_texconv_path()
        if texconv_path is None:
            self.report({'ERROR'}, "texconv.exe not found. Reset its path in addon preferences.")
            return {'CANCELLED'}
        
        mat_name = utils.sanitize_filename(context.scene.sf_export_material_name.name)
        mat_folder = context.scene.sf_export_material_folder
        texture_folder = os.path.join("Textures", mat_name)
        
        return MaterialConverter.ExportMat(mat_name, context.scene, context, self, mat_folder, mat_folder, texture_folder, texconv_path)


class ExportMaterialPanel(bpy.types.Panel):
    """Panel for the Export Material functionality"""
    bl_idname = "OBJECT_PT_export_material"
    bl_label = "Export Material"
    bl_space_type = 'VIEW_3D'
    bl_region_type = 'UI'
    bl_category = 'Tool'

    def draw(self, context):
        layout = self.layout
        texconv_path = utils_blender.get_texconv_path()

        if texconv_path is None:
            layout.operator("object.choose_file_for_preferences", text="Set texconv.exe Path")
            return

        if bpy.context.object is not None and bpy.context.object.mode != 'OBJECT':
            layout.enabled = False

        layout.label(text="Material Name")
        layout.prop(context.scene, "sf_export_material_name", text="")
        layout.operator("object.sf_new_material", text="New Material", icon="ADD")
        sub_layout0 = layout.column(align=True)

        sub_layout = layout.column(align=True)

        if context.scene.sf_export_material_name is None:
            sub_layout.enabled = False
            sub_layout0.enabled = False
        else:
            if context.active_object is not None and context.active_object.type == 'MESH':
                sub_layout.enabled = True
            sub_layout0.enabled = True

        sub_layout0.operator("object.sf_apply_material", text="Apply Mat To Active Object")
        sub_layout.label(text="Shader Model")
        sub_layout.prop(context.scene, "sf_export_material_ShaderModel", text="")

        sub_layout.label(text="Texture Maps")
        for texture_item in MaterialConverter.TextureIndex.__members__.values():
            sub_layout.prop(context.scene, f"sf_export_material_{texture_item.name}")
            
            sub_layout.prop(context.scene, f"sf_export_material_{texture_item.name}_size")
            if texture_item == MaterialConverter.TextureIndex.NORMAL:
                row = sub_layout.row(align=True)
                row.prop(context.scene, "sf_export_material_normal_map_flip_y", text="Flip Y", toggle=True)

        sub_layout.label(text="Alpha Settings")
        box = sub_layout.box()
        if context.scene.sf_export_material_OPACITY is not None:
            box.label(text="Alpha Threshold")
            box.prop(context.scene, "sf_export_material_alpha_thresh", text="")

            # Sadly vertex color blending doesn't really work
            #box.label(text="Blend Vertex Color Channel")
            #box.prop(context.scene, "sf_export_material_alpha_blend_channel", text="")
        else:
            box.label(text="No Opacity Map Found")

        sub_layout.label(text="Export Folder")
        sub_layout.prop(context.scene, "sf_export_material_folder", text="")

        sub_layout.operator("object.material_data_export", text="Export Material")

def update_selected_mat(self, context):
    mat = context.scene.sf_export_material_name
    if mat is None:
        return
    single_sided = utils_material.get_single_sided(mat)
    alpha_thresh = utils_material.get_alpha_thresh(mat)
    alpha_blend_channel = utils_material.get_alpha_blend_channel(mat)
    context.scene.sf_export_material_ShaderModel = "1LayerStandard" if single_sided else "TwoSided1Layer"
    context.scene.sf_export_material_alpha_thresh = alpha_thresh
    context.scene.sf_export_material_alpha_blend_channel = alpha_blend_channel.value

    for texture_item in MaterialConverter.TextureIndex.__members__.values():
        texture_node = utils_material.get_node_tree_texture_node(mat, texture_item)
        if texture_node is not None:
            context.scene[f"sf_export_material_{texture_item.name}"] = texture_node.image

def update_shader_model(self, context):
    mat = context.scene.sf_export_material_name
    single_sided = context.scene.sf_export_material_ShaderModel == "1LayerStandard"
    utils_material.set_single_sided(mat, single_sided)

def update_alpha_thresh(self, context):
    mat = context.scene.sf_export_material_name
    utils_material.set_alpha_thresh(mat, context.scene.sf_export_material_alpha_thresh)

def update_alpha_blend_channel(self, context):
    mat = context.scene.sf_export_material_name
    utils_material.set_alpha_blend_channel(mat, MaterialConverter.BlendVertexColorChannel(self.sf_export_material_alpha_blend_channel))

def update_texture_at_index(key:MaterialConverter.TextureIndex):
    def update_texture(self, context):
        mat = context.scene.sf_export_material_name
        utils_material.set_texture_map(mat, key, context.scene[f"sf_export_material_{key.name}"])
    return update_texture

def register():
    bpy.types.Scene.sf_export_material_name = bpy.props.PointerProperty(
        name = "Material",
        type = bpy.types.Material,
        poll = lambda self, obj: utils_material.is_mat(obj),
        update=update_selected_mat
    )
    bpy.types.Scene.sf_export_material_ShaderModel = bpy.props.EnumProperty(
        name="Shader Model",
        items=[
            ("1LayerStandard", "Single Sided", "Single Sided"),
            ("TwoSided1Layer", "Double Sided", "Double Sided")
        ],
        default="1LayerStandard",
        update=update_shader_model
    )
    for texture_item in MaterialConverter.TextureIndex.__members__.values():
        name = str(texture_item.name)
        if name != "AO":
            name = name.title()
        setattr(bpy.types.Scene, f"sf_export_material_{texture_item.name}",
        bpy.props.PointerProperty(
            name=name,
            type=bpy.types.Image,
            update=update_texture_at_index(texture_item),
            poll = lambda self, obj: obj.size[0] * obj.size[1],
        ))
        setattr(bpy.types.Scene, f"sf_export_material_{texture_item.name}_size",
        bpy.props.EnumProperty(
            name="Size",
            items=[
                ("None", "Default", ""),
                ("512", "512", ""),
                ("1024", "1024", ""),
                ("2048", "2048", ""),
                ("3072", "3072", ""),
                ("4096", "4096", ""),
            ],
            default="None",
        ))
    bpy.types.Scene.sf_export_material_normal_map_flip_y = bpy.props.BoolProperty(
        name="Flip Y",
        default=False
    )
    
    bpy.types.Scene.sf_export_material_alpha_thresh = bpy.props.FloatProperty(
        name="Alpha Threshold",
        default=0.0,
        min=0,
        max=1,
        update=update_alpha_thresh
    )
    bpy.types.Scene.sf_export_material_alpha_blend_channel = bpy.props.EnumProperty(
        name="Alpha Blend Vertex Color Channel",
        items=[
            ("None", "No Blending", "No Vertex Color Blending"),
            ("Alpha", "Alpha", "Alpha"),
            ("Red", "Red", "Red"),
            ("Green", "Green", "Green"),
            ("Blue", "Blue", "Blue"),
        ],
        default="Alpha",
        update=update_alpha_blend_channel
    )
    bpy.types.Scene.sf_export_material_folder = bpy.props.StringProperty(
		name="Export Folder",
		subtype='DIR_PATH',
        default=utils.export_mesh_folder_path
    )
    
    bpy.utils.register_class(ApplyMaterialOnObjectOperator)
    bpy.utils.register_class(NewMaterialOperator)
    bpy.utils.register_class(ExportMaterialOperator)
    bpy.utils.register_class(ExportMaterialPanel)

def unregister():
    bpy.utils.unregister_class(ApplyMaterialOnObjectOperator)
    bpy.utils.unregister_class(NewMaterialOperator)
    bpy.utils.unregister_class(ExportMaterialOperator)
    bpy.utils.unregister_class(ExportMaterialPanel)
    del bpy.types.Scene.sf_export_material_name
    del bpy.types.Scene.sf_export_material_ShaderModel
    for texture_item in MaterialConverter.TextureIndex.__members__.values():
        delattr(bpy.types.Scene, f"sf_export_material_{texture_item.name}")
        delattr(bpy.types.Scene, f"sf_export_material_{texture_item.name}_size")
    del bpy.types.Scene.sf_export_material_normal_map_flip_y
    del bpy.types.Scene.sf_export_material_alpha_thresh
    del bpy.types.Scene.sf_export_material_alpha_blend_channel
    del bpy.types.Scene.sf_export_material_folder
