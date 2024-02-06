import json
import enum

class ShaderModel(enum.Enum):
    ONE_LAYER_STANDARD = "1LayerStandard"
    ONE_LAYER_TWO_SIDED = "TwoSided1Layer"

class TextureIndex(enum.Enum):
    COLOR = 0
    NORMAL = 1
    OPACITY = 2
    ROUGH = 3
    METAL = 4
    AO = 5
    HEIGHT = 6
    #EMISSIVE = 7
    #TRANSMISSIVE = 8

class BlendVertexColorChannel(enum.Enum):
    ALPHA = "Alpha"
    RED = "Red"
    GREEN = "Green"
    BLUE = "Blue"
    NONE = "None"

class AlphaSettingsComponent:
    def __init__(self, hasOpacity:bool, alphaTestThreshold:float = 0, blendVertexColorChannel:BlendVertexColorChannel = BlendVertexColorChannel.NONE) -> None:
        self.alphaTestThreshold = alphaTestThreshold
        self.blendVertexColorChannel = blendVertexColorChannel
        self.hasOpacity = hasOpacity

    def __str__(self) -> str:
        rtn_dict = self.to_dict()
        return json.dumps(rtn_dict, indent=2)

    def to_dict(self) -> dict:
        rtn_dict = {
            "Data": {
                "AlphaTestThreshold": f"{self.alphaTestThreshold:.6f}",
            },
            "Index": 0,
            "Type": "BSMaterial::AlphaSettingsComponent"
        }
        if self.blendVertexColorChannel != BlendVertexColorChannel.NONE:
            rtn_dict["Data"]["Blender"] = {
                "Data": {
                    "VertexColorChannel": self.blendVertexColorChannel.value
                },
                "Type": "BSMaterial::AlphaBlenderSettings"
            }
        if self.hasOpacity:
            rtn_dict["Data"]["HasOpacity"] = "true"
        return rtn_dict


class MatFile:
    def __init__(self) -> None:
        self.json_data = None

        self.name = "test"
        self.base_id = "0005DD03:A7CE75E1"

        self.num_texture_sets = 0
        self.num_UV_streams = 0
        self.num_materials = 0
        self.num_layers = 0

        self.shader_model = ShaderModel.ONE_LAYER_STANDARD
        self.alpha_test_threshold = 0
        self.alpha_blend_vertex_color_channel = BlendVertexColorChannel.NONE

        self.disable_mip_bias_hint = False
        self.texture_replacements = []
        self.texture_slots = {
            TextureIndex.COLOR.value: None,
            TextureIndex.NORMAL.value: None,
            TextureIndex.OPACITY.value: None,
            TextureIndex.ROUGH.value: None,
            TextureIndex.METAL.value: None,
            TextureIndex.AO.value: None,
            TextureIndex.HEIGHT.value: None,
            #TextureIndex.EMISSIVE.value: None,
            #TextureIndex.TRANSMISSIVE.value: None,
            #TextureIndex.UNKNOWN.value: None
        }

    def ID(self, id:str):
        if id.startswith("res:"):
            return id
        return f"res:{id}:{self.base_id}"

    @staticmethod
    def _default_component(data: dict, type: str, index: int = 0):
        return {
            "Data": data,
            "Index": index,
            "Type": type
        }
    
    @staticmethod
    def _default_component_no_index(data: dict, type: str):
        return {
            "Data": data,
            "Type": type
        }
    
    @classmethod
    def CTName(cls, name:str):
        return cls._default_component({"Name": name}, "BSComponentDB::CTName")
    
    @classmethod
    def LayerID(cls, id:str):
        return cls._default_component({"ID": id}, "BSMaterial::LayerID")
    
    @classmethod
    def ShaderModelComponentStr(cls, shader_model_str:str):
        return cls._default_component({"FileName": shader_model_str}, "BSMaterial::ShaderModelComponent")
    
    @classmethod
    def ShaderModelComponent(cls, shader_model:ShaderModel = ShaderModel.ONE_LAYER_STANDARD):
        return cls._default_component({"FileName": shader_model.value}, "BSMaterial::ShaderModelComponent")
    
    @classmethod
    def Color(cls, color:tuple[float, float, float, float] = (1, 1, 1, 1)):
        return cls._default_component_no_index({
                "Value": {
                    "Data": {
                        "w": f"{color[3]:.6f}",
                        "x": f"{color[0]:.6f}",
                        "y": f"{color[1]:.6f}",
                        "z": f"{color[2]:.6f}"
                    },
                    "Type": "XMFLOAT4"
                }
            },
            type = "BSMaterial::Color"
        )

    @classmethod
    def MipBiasSetting(cls, DisableMipBiasHint:bool = True):
        return {
            "Data": {
                "DisableMipBiasHint": str(DisableMipBiasHint).lower()
            },
            "Index": 0,
            "Type": "BSMaterial::MipBiasSetting"
        }

    @classmethod
    def LayeredEmissivityComponent(cls):
        return cls._default_component({
                "AdaptiveEmittance": "false",
                "EmissiveClipThreshold": "0.000000",
                "EnableAdaptiveLimits": "false",
                "Enabled": "false",
                "ExposureOffset": "0.000000",
                "FirstBlenderIndex": "BLEND_LAYER_8",
                "FirstBlenderMode": "Lerp",
                "FirstLayerIndex": "MATERIAL_LAYER_9",
                "FirstLayerMaskIndex": "None",
                "FirstLayerTint": cls.Color(),
                "LuminousEmittance": "432.000000",
                "MaxOffsetEmittance": "1.000000",
                "MinOffsetEmittance": "0.000000",
                "SecondBlenderIndex": "BLEND_LAYER_7",
                "SecondBlenderMode": "Lerp",
                "SecondLayerActive": "false",
                "SecondLayerIndex": "MATERIAL_LAYER_8",
                "SecondLayerMaskIndex": "None",
                "SecondLayerTint": cls.Color(),
                "ThirdLayerActive": "false",
                "ThirdLayerIndex": "MATERIAL_LAYER_7",
                "ThirdLayerMaskIndex": "None",
                "ThirdLayerTint": cls.Color(),
            },
            type = "BSMaterial::LayeredEmissivityComponent"
        )

    @classmethod
    def MaterialID(cls, id:str):
        return cls._default_component({"ID": id}, "BSMaterial::MaterialID")

    @classmethod
    def UVStreamID(cls, id:str):
        return cls._default_component({"ID": id}, "BSMaterial::UVStreamID")

    @classmethod
    def TextureSetID(cls, id:str): 
        return cls._default_component({"ID": id}, "BSMaterial::TextureSetID")

    @classmethod
    def TextureReplacement(cls, index:int, enabled:bool = True):
        return cls._default_component({"Enabled": str(enabled).lower()}, type="BSMaterial::TextureReplacement",index=index)

    @classmethod
    def MRTextureFile(cls, index:int, filename:str):
        return cls._default_component({"FileName": filename}, type="BSMaterial::MRTextureFile", index=index)

    def TextureSets(self, ID:str, texture_slots, texture_replacements:list[int] = [], DisableMipBiasHint:bool = False):
        self.num_texture_sets += 1
        return {
            "Components": [
                self.CTName(self.name + f"_TextureSet{self.num_texture_sets}"),
                *[self.MipBiasSetting(DisableMipBiasHint) for _ in range(1) if DisableMipBiasHint],
                *[self.TextureReplacement(index) for index in texture_replacements],
                *[self.MRTextureFile(index, path) for index, path in texture_slots.items() if path is not None],
            ],
            "ID": self.ID(ID),
            "Parent": "materials\\layered\\root\\texturesets.mat"
        }
    
    def UVStreams(self, ID:str):
        self.num_UV_streams += 1
        return {
            "Components": [
                self.CTName(self.name + f"_UVStream{self.num_UV_streams}"),
            ],
            "ID": self.ID(ID),
            "Parent": "materials\\layered\\root\\uvstreams.mat"
        }
    
    def Materials(self, ID:str, texture_set_ID:str):
        self.num_materials += 1
        return {
            "Components": [
                self.CTName(self.name + f"_Material{self.num_materials}"),
                self.TextureSetID(self.ID(texture_set_ID)),
            ],
            "ID": self.ID(ID),
            "Parent": "materials\\layered\\root\\materials.mat"
        }

    def Layers(self, ID:str, material_ID:str, uv_stream_ID:str):
        self.num_layers += 1
        return {
            "Components": [
                self.CTName(self.name + f"_Layer{self.num_layers}"),
                self.MaterialID(self.ID(material_ID)),
                self.UVStreamID(self.ID(uv_stream_ID)),
            ],
            "ID": self.ID(ID),
            "Parent": "materials\\layered\\root\\layers.mat"
        }

    def setBaseID(self, id:str):
        self.base_id = id

    def setName(self, name:str):
        self.name = name

    def setTexturePath(self, index:TextureIndex, path:str|None):
        self.texture_slots[index.value] = path

    def setShaderModel(self, shader_model:ShaderModel):
        self.shader_model = ShaderModel(shader_model)
    
    def setShaderModelStr(self, shader_model_str:str):
        self.shader_model = ShaderModel(shader_model_str)

    def setAlphaTestThreshold(self, threshold:float):
        self.alpha_test_threshold = threshold

    def setAlphaBlendVertexColorChannel(self, channel:BlendVertexColorChannel):
        self.alpha_blend_vertex_color_channel = BlendVertexColorChannel(channel)

    def compose(self) -> str:
        name = self.name
        has_opacity = self.texture_slots[TextureIndex.OPACITY.value] is not None
        self.json_data = {
            "Objects": [
                {
                "Components": [
                    self.CTName(name),
                    self.LayerID(self.ID("0574E109")),
                    AlphaSettingsComponent(has_opacity, self.alpha_test_threshold, self.alpha_blend_vertex_color_channel).to_dict(),
                    self.ShaderModelComponent(self.shader_model),
                    self.LayeredEmissivityComponent(),
                ],
                "Parent": "materials\\layered\\root\\layeredmaterials.mat"
                },
                self.Layers(self.ID("0574E109"), "0574E12A", "0574E181"),
                self.UVStreams(self.ID("0574E181")),
                self.Materials(self.ID("0574E12A"), "0574E154"),
                self.TextureSets(self.ID("0574E154"), self.texture_slots, self.texture_replacements, self.disable_mip_bias_hint)
            ],
            "Version": 1
        }
        return json.dumps(self.json_data, indent=2)
    

import bpy
import os
import utils_common as utils
import utils_material
import utils_blender

def ExportMatFromMaterial(material:bpy.types.Material, operator, mat_folder, texture_rootfolder, texture_relfolder, texconv_path):
    os.makedirs(mat_folder, exist_ok=True)
    os.makedirs(texture_rootfolder, exist_ok=True)
    
    mat = material
    mat_name = utils.sanitize_filename(material.name)
    single_sided = utils_material.get_single_sided(mat)
    alpha_thresh = utils_material.get_alpha_thresh(mat)
    alpha_blend_channel = utils_material.get_alpha_blend_channel(mat)
    sf_export_material_ShaderModel = "1LayerStandard" if single_sided else "TwoSided1Layer"
    sf_export_material_alpha_thresh = alpha_thresh
    sf_export_material_alpha_blend_channel = alpha_blend_channel.value
    
    images = {}
    for texture_item in TextureIndex.__members__.values():
        texture_node = utils_material.get_node_tree_texture_node(mat, texture_item)
        if texture_node is not None:
            images[f"sf_export_material_{texture_item.name}"] = texture_node.image
    
    mat = MatFile()
    mat.setName(mat_name)
    mat.setShaderModelStr(sf_export_material_ShaderModel)

    for texture_item in TextureIndex.__members__.values():
        texture_map = images[f"sf_export_material_{texture_item.name}"]
        if texture_map is not None and isinstance(texture_map, bpy.types.Image):
            texture_path = os.path.join(texture_rootfolder, texture_relfolder, f"{mat_name}_{texture_item.name.lower()}.png")
            utils_material.export_texture_map_to_dds(texture_map, texture_item, texture_path, texconv_path, not utils_blender.is_plugin_debug_mode())
            
            mat.setTexturePath(texture_item, os.path.join("Data", texture_relfolder, f"{mat_name}_{texture_item.name.lower()}.dds"))

    if images["sf_export_material_OPACITY"] is not None:
        mat.setAlphaTestThreshold(sf_export_material_alpha_thresh)
        mat.setAlphaBlendVertexColorChannel(sf_export_material_alpha_blend_channel)

    rtn = mat.compose()

    mat_path = os.path.join(mat_folder, f"{mat_name}.mat")
    if rtn is not None:
        with open(mat_path, "w") as f:
            f.write(rtn)
        operator.report({'INFO'}, "Material exported successfully.")
        return {'FINISHED'}, mat_path
    else:
        operator.report({'ERROR'}, "Failed to export material.")
        return {'CANCELLED'}, None

def ExportMat(mat_name, options, context, operator, mat_folder, texture_rootfolder, texture_relfolder, texconv_path):
    mat = MatFile()
    mat.setName(mat_name)
    mat.setShaderModelStr(options.sf_export_material_ShaderModel)

    for texture_item in TextureIndex.__members__.values():
        texture_map = options[f"sf_export_material_{texture_item.name}"]
        if texture_map is not None and isinstance(texture_map, bpy.types.Image):
            texture_path = os.path.join(texture_rootfolder, texture_relfolder, f"{mat_name}_{texture_item.name.lower()}.png")
            utils_material.export_texture_map_to_dds(texture_map, texture_item, texture_path, texconv_path, not utils_blender.is_plugin_debug_mode())
            
            mat.setTexturePath(texture_item, os.path.join("Data", texture_relfolder, f"{mat_name}_{texture_item.name.lower()}.dds"))

    if options.sf_export_material_OPACITY is not None:
        mat.setAlphaTestThreshold(options.sf_export_material_alpha_thresh)
        mat.setAlphaBlendVertexColorChannel(options.sf_export_material_alpha_blend_channel)

    rtn = mat.compose()

    if rtn is not None:
        with open(os.path.join(mat_folder, f"{mat_name}.mat"), "w") as f:
            f.write(rtn)
        operator.report({'INFO'}, "Material exported successfully.")
        return {'FINISHED'}
    else:
        operator.report({'ERROR'}, "Failed to export material.")
        return {'CANCELLED'}