import bpy
import os
import MaterialConverter
import MaterialGenShaderNode

IMAGE_TYPE_NON_COLOR = set(["NORMAL", "OPACITY", "AO", "METAL", "ROUGH", "HEIGHT"])

def is_mat(mat:bpy.types.Material) -> bool:
    if mat.use_nodes:
        return is_mat_tree(mat.node_tree)
    return False

def is_mat_tree(tree: bpy.types.ShaderNodeTree) -> bool:
    output_node = tree.get_output_node('ALL')
    if output_node is None:
        return False
    
    if not output_node.inputs['Surface'].is_linked:
        return False

    for texture_index in MaterialConverter.TextureIndex.__members__.values():
        if texture_index.name not in tree.nodes:
            return False

    bsdf = output_node.inputs['Surface'].links[0].from_node

    return bsdf.bl_idname == 'ShaderNodeGroup' and bsdf.node_tree is not None and bsdf.node_tree.name == 'SF_ShaderNode'

def get_active_mat_tree(obj: bpy.types.Object) -> bpy.types.ShaderNodeTree:
    if obj is None:
        return None

    if obj.type != 'MESH':
        return None

    mat = obj.active_material
    if mat is None:
        return None
    
    if is_mat(mat):
        return mat.node_tree

    return None

def get_all_mat_trees_from_obj(obj: bpy.types.Object) -> list[bpy.types.ShaderNodeTree]:
    if obj is None:
        return []

    if obj.type != 'MESH':
        return []
    
    mat_list = []
    for mat in obj.data.materials:
        if is_mat(mat):
            mat_list.append(mat.node_tree)
    
    return mat_list

def new_mat(mat_name: str, obj: bpy.types.Object = None, ) -> bpy.types.Material:
    mat = MaterialGenShaderNode.new_mat(mat_name=mat_name)
    if obj is not None:
        obj.active_material = mat
    return mat

def get_node_tree_BSDF_s(mat:bpy.types.Material) -> bpy.types.ShaderNodeGroup:
    if not is_mat(mat):
        return None
    
    output_node = mat.node_tree.get_output_node('ALL')

    return output_node.inputs['Surface'].links[0].from_node

def get_node_tree_BSDF(mat:bpy.types.Material) -> bpy.types.ShaderNodeGroup:
    return mat.node_tree.get_output_node('ALL').inputs['Surface'].links[0].from_node

def get_node_tree_texture_node(mat:bpy.types.Material, texture_index:MaterialConverter.TextureIndex) -> bpy.types.ShaderNodeTexImage:
    return mat.node_tree.nodes[texture_index.name]

def enable_texture_node(mat:bpy.types.Material, texture_index:MaterialConverter.TextureIndex, enable:bool):
    if not is_mat(mat):
        return
    
    mat.node_tree.nodes[texture_index.name].mute = not enable

def set_single_sided(mat:bpy.types.Material, single_sided:bool = True):
    if not is_mat(mat):
        return
    
    mat.use_backface_culling = single_sided

def get_single_sided(mat:bpy.types.Material) -> bool:
    if not is_mat(mat):
        return False
    
    return mat.use_backface_culling

def set_alpha_thresh(mat:bpy.types.Material, alpha_thresh:float):
    if not is_mat(mat):
        return
    
    get_node_tree_BSDF(mat).inputs['A_TEST_THRESH'].default_value = alpha_thresh

def get_alpha_thresh(mat:bpy.types.Material) -> float:
    if not is_mat(mat):
        return 0.0
    
    return get_node_tree_BSDF(mat).inputs['A_TEST_THRESH'].default_value

def set_alpha_blend_channel(mat:bpy.types.Material, alpha_blend_channel:MaterialConverter.BlendVertexColorChannel):
    if not is_mat(mat):
        return
    
    match alpha_blend_channel:
        case MaterialConverter.BlendVertexColorChannel.NONE:
            get_node_tree_BSDF(mat).inputs['A_BLEND_CHANNEL'].default_value = 0
        case MaterialConverter.BlendVertexColorChannel.RED:
            get_node_tree_BSDF(mat).inputs['A_BLEND_CHANNEL'].default_value = 1
        case MaterialConverter.BlendVertexColorChannel.GREEN:
            get_node_tree_BSDF(mat).inputs['A_BLEND_CHANNEL'].default_value = 2
        case MaterialConverter.BlendVertexColorChannel.BLUE:
            get_node_tree_BSDF(mat).inputs['A_BLEND_CHANNEL'].default_value = 3
        case MaterialConverter.BlendVertexColorChannel.ALPHA:
            get_node_tree_BSDF(mat).inputs['A_BLEND_CHANNEL'].default_value = 4
        case _:
            raise ValueError("Invalid BlendVertexColorChannel")

def get_alpha_blend_channel(mat:bpy.types.Material) -> MaterialConverter.BlendVertexColorChannel:
    if not is_mat(mat):
        return MaterialConverter.BlendVertexColorChannel.NONE
    
    match int(get_node_tree_BSDF(mat).inputs['A_BLEND_CHANNEL'].default_value):
        case 0:
            return MaterialConverter.BlendVertexColorChannel.NONE
        case 1:
            return MaterialConverter.BlendVertexColorChannel.RED
        case 2:
            return MaterialConverter.BlendVertexColorChannel.GREEN
        case 3:
            return MaterialConverter.BlendVertexColorChannel.BLUE
        case 4:
            return MaterialConverter.BlendVertexColorChannel.ALPHA
        case _:
            return MaterialConverter.BlendVertexColorChannel.NONE

def set_texture_map(mat:bpy.types.Material, texture_index:MaterialConverter.TextureIndex, image:bpy.types.Image):
    if not is_mat(mat):
        return
    
    if image is None:
        enable_texture_node(mat, texture_index, False)
    else:
        enable_texture_node(mat, texture_index, True)
    
    get_node_tree_texture_node(mat, texture_index).image = image
    if texture_index.name in IMAGE_TYPE_NON_COLOR:
        image.colorspace_settings.is_data = True

def get_texture_map(mat:bpy.types.Material, texture_index:MaterialConverter.TextureIndex) -> bpy.types.Image:
    if not is_mat(mat):
        return None
    
    return get_node_tree_texture_node(mat, texture_index).image

def export_texture_map(image:bpy.types.Image, path:str):
    if image is None:
        return False, ""
    if not path.endswith('.png'):
        path = os.path.splitext(path)[0] + '.png'
    os.makedirs(os.path.dirname(path), exist_ok=True)

    if os.path.exists(path) and os.path.isfile(path):
        os.remove(path)
        
    original_path = image.filepath_raw
    image.filepath_raw = path
    original_format = image.file_format
    image.file_format = 'PNG'
    image.save()
    image.filepath_raw = original_path
    image.file_format = original_format
    return True, path

import subprocess
import time

_texture_format: dict[str, str] = {
    "COLOR": "BC7_UNORM",
    "NORMAL": "BC5_SNORM",
    "OPACITY": "BC4_UNORM",
    "AO": "BC4_UNORM",
    "METAL": "BC4_UNORM",
    "ROUGH": "BC4_UNORM",
    "HEIGHT": "BC4_UNORM",
}

_srgb: list = ["COLOR"]

def _get_texture_format(texture_index:MaterialConverter.TextureIndex) -> str:
    if texture_index.name not in _texture_format:
        return "BC1_UNORM"
    return _texture_format[texture_index.name]

def _is_srgb(texture_index:MaterialConverter.TextureIndex) -> bool:
    return texture_index.name in _srgb

def _is_normal_map(texture_index:MaterialConverter.TextureIndex) -> bool:
    return texture_index.name == "NORMAL"

def convert_image_to_dds(texconv_path:str, texture_index:MaterialConverter.TextureIndex, png_path:str):
    if not png_path.endswith('.png'):
        raise ValueError("Input image is not a PNG file")

    cmd = [texconv_path]
    
    if _is_srgb(texture_index):
        cmd += ["-srgbi"]

    if _is_normal_map(texture_index):
        cmd += ["-inverty"]

    cmd += [
        "-f", _get_texture_format(texture_index),
        "-o", os.path.dirname(png_path), 
        "-y",
        "-nologo",
        png_path
    ]

    try:
        subprocess.run(cmd, check=True, shell=True)
        return True
    except subprocess.CalledProcessError as e:
        print(f"Export dds error: {e.stderr}")
        return False
    
def export_texture_map_to_dds(image:bpy.types.Image, texture_index:MaterialConverter.TextureIndex, path:str, texconv_path:str, remove_png:bool = True):
    if image is None:
        return False
    if not path.endswith('.dds'):
        path = os.path.splitext(path)[0] + '.dds'
    
    time_start = time.time()
    success, png_path = export_texture_map(image, path)
    time_end = time.time()
    
    if not success:
        print(f"Export texture map {image.name} failed")
        return False
    else:
        print(f"Export texture map {image.name} to png success: {time_end - time_start:.2f}s")
    
    time_start = time.time()
    success = convert_image_to_dds(texconv_path, texture_index, png_path)
    time_end = time.time()

    if not success:
        print(f"Convert texture map {image.name} to dds failed")
        return False
    else:
        print(f"Convert texture map {image.name} to dds success: {time_end - time_start:.2f}s")

    if remove_png:
        os.remove(png_path)