import bpy

#initialize sf_shadernode node group
def sf_shadernode_node_group():
    sf_shadernode= bpy.data.node_groups.new(type = 'ShaderNodeTree', name = "SF_ShaderNode")

    #initialize sf_shadernode nodes
    #node Group Output
    group_output = sf_shadernode.nodes.new("NodeGroupOutput")
    #sf_shadernode outputs
    #output BSDF
    sf_shadernode.outputs.new('NodeSocketShader', "BSDF")
    sf_shadernode.outputs[0].attribute_domain = 'POINT'

    #output Displacement
    sf_shadernode.outputs.new('NodeSocketVector', "Displacement")
    sf_shadernode.outputs[1].default_value = (0.0, 0.0, 0.0)
    sf_shadernode.outputs[1].min_value = -3.4028234663852886e+38
    sf_shadernode.outputs[1].max_value = 3.4028234663852886e+38
    sf_shadernode.outputs[1].attribute_domain = 'POINT'



    #node Mix
    mix = sf_shadernode.nodes.new("ShaderNodeMix")
    mix.data_type = 'RGBA'
    mix.clamp_factor = True
    mix.factor_mode = 'UNIFORM'
    mix.blend_type = 'MIX'
    #Factor_Float
    mix.inputs[0].default_value = 0.20000000298023224
    #Factor_Vector
    mix.inputs[1].default_value = (0.5, 0.5, 0.5)
    #A_Float
    mix.inputs[2].default_value = 0.0
    #B_Float
    mix.inputs[3].default_value = 0.0
    #A_Vector
    mix.inputs[4].default_value = (0.0, 0.0, 0.0)
    #B_Vector
    mix.inputs[5].default_value = (0.0, 0.0, 0.0)

    #node Invert
    invert = sf_shadernode.nodes.new("ShaderNodeInvert")
    #Fac
    invert.inputs[0].default_value = 1.0

    #node Group Input
    group_input = sf_shadernode.nodes.new("NodeGroupInput")
    #sf_shadernode inputs
    #input COLOR
    sf_shadernode.inputs.new('NodeSocketColor', "COLOR")
    sf_shadernode.inputs[0].default_value = (0.800000011920929, 0.800000011920929, 0.800000011920929, 1.0)
    sf_shadernode.inputs[0].attribute_domain = 'POINT'

    #input NORMAL
    sf_shadernode.inputs.new('NodeSocketVector', "NORMAL")
    sf_shadernode.inputs[1].default_value = (0.0, 0.0, 0.0)
    sf_shadernode.inputs[1].min_value = -3.4028234663852886e+38
    sf_shadernode.inputs[1].max_value = 3.4028234663852886e+38
    sf_shadernode.inputs[1].attribute_domain = 'POINT'
    sf_shadernode.inputs[1].hide_value = True

    #input OPACITY
    sf_shadernode.inputs.new('NodeSocketFloatFactor', "OPACITY")
    sf_shadernode.inputs[2].default_value = 1.0
    sf_shadernode.inputs[2].min_value = 0.0
    sf_shadernode.inputs[2].max_value = 1.0
    sf_shadernode.inputs[2].attribute_domain = 'POINT'

    #input METAL
    sf_shadernode.inputs.new('NodeSocketFloatFactor', "METAL")
    sf_shadernode.inputs[3].default_value = 0.0
    sf_shadernode.inputs[3].min_value = 0.0
    sf_shadernode.inputs[3].max_value = 1.0
    sf_shadernode.inputs[3].attribute_domain = 'POINT'

    #input ROUGH
    sf_shadernode.inputs.new('NodeSocketFloatFactor', "ROUGH")
    sf_shadernode.inputs[4].default_value = 0.5
    sf_shadernode.inputs[4].min_value = 0.0
    sf_shadernode.inputs[4].max_value = 1.0
    sf_shadernode.inputs[4].attribute_domain = 'POINT'

    #input AO
    sf_shadernode.inputs.new('NodeSocketFloatFactor', "AO")
    sf_shadernode.inputs[5].default_value = 0.0
    sf_shadernode.inputs[5].min_value = 0.0
    sf_shadernode.inputs[5].max_value = 1.0
    sf_shadernode.inputs[5].attribute_domain = 'POINT'

    #input HEIGHT
    sf_shadernode.inputs.new('NodeSocketVector', "HEIGHT")
    sf_shadernode.inputs[6].default_value = (0.0, 0.0, 0.0)
    sf_shadernode.inputs[6].min_value = -3.4028234663852886e+38
    sf_shadernode.inputs[6].max_value = 3.4028234663852886e+38
    sf_shadernode.inputs[6].attribute_domain = 'POINT'

    #input A_TEST_THRESH
    sf_shadernode.inputs.new('NodeSocketFloat', "A_TEST_THRESH")
    sf_shadernode.inputs[7].default_value = 0.0
    sf_shadernode.inputs[7].min_value = 0.0
    sf_shadernode.inputs[7].max_value = 1.0
    sf_shadernode.inputs[7].attribute_domain = 'POINT'

    #input A_BLEND_CHANNEL
    sf_shadernode.inputs.new('NodeSocketFloat', "A_BLEND_CHANNEL")
    sf_shadernode.inputs[8].default_value = 0.0
    sf_shadernode.inputs[8].min_value = 0.0
    sf_shadernode.inputs[8].max_value = 4.0
    sf_shadernode.inputs[8].attribute_domain = 'POINT'



    #node Principled BSDF
    principled_bsdf = sf_shadernode.nodes.new("ShaderNodeBsdfPrincipled")
    principled_bsdf.distribution = 'GGX'
    principled_bsdf.subsurface_method = 'RANDOM_WALK'
    #Subsurface
    principled_bsdf.inputs[1].default_value = 0.0
    #Subsurface Radius
    principled_bsdf.inputs[2].default_value = (1.0, 0.20000000298023224, 0.10000000149011612)
    #Subsurface Color
    principled_bsdf.inputs[3].default_value = (0.800000011920929, 0.800000011920929, 0.800000011920929, 1.0)
    #Subsurface IOR
    principled_bsdf.inputs[4].default_value = 1.399999976158142
    #Subsurface Anisotropy
    principled_bsdf.inputs[5].default_value = 0.0
    #Specular
    principled_bsdf.inputs[7].default_value = 0.0
    #Specular Tint
    principled_bsdf.inputs[8].default_value = 0.0
    #Anisotropic
    principled_bsdf.inputs[10].default_value = 0.0
    #Anisotropic Rotation
    principled_bsdf.inputs[11].default_value = 0.0
    #Sheen
    principled_bsdf.inputs[12].default_value = 0.0
    #Sheen Tint
    principled_bsdf.inputs[13].default_value = 0.5
    #Clearcoat
    principled_bsdf.inputs[14].default_value = 0.0
    #Clearcoat Roughness
    principled_bsdf.inputs[15].default_value = 0.029999999329447746
    #IOR
    principled_bsdf.inputs[16].default_value = 1.4500000476837158
    #Transmission
    principled_bsdf.inputs[17].default_value = 0.0
    #Transmission Roughness
    principled_bsdf.inputs[18].default_value = 0.0
    #Emission
    principled_bsdf.inputs[19].default_value = (0.0, 0.0, 0.0, 1.0)
    #Emission Strength
    principled_bsdf.inputs[20].default_value = 1.0
    #Clearcoat Normal
    principled_bsdf.inputs[23].default_value = (0.0, 0.0, 0.0)
    #Tangent
    principled_bsdf.inputs[24].default_value = (0.0, 0.0, 0.0)
    #Weight
    principled_bsdf.inputs[25].default_value = 0.0

    #node Group Input.001
    group_input_001 = sf_shadernode.nodes.new("NodeGroupInput")

    #node Math
    math = sf_shadernode.nodes.new("ShaderNodeMath")
    math.operation = 'LESS_THAN'
    math.use_clamp = True
    #Value_002
    math.inputs[2].default_value = 0.5

    #node Math.001
    math_001 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_001.operation = 'SUBTRACT'
    #Value
    math_001.inputs[0].default_value = 1.0
    #Value_002
    math_001.inputs[2].default_value = 0.5

    #node Math.002
    math_002 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_002.operation = 'MULTIPLY'
    #Value_002
    math_002.inputs[2].default_value = 0.5

    #node Group Input.002
    group_input_002 = sf_shadernode.nodes.new("NodeGroupInput")


    #Set locations
    group_output.location = (290.0, 0.0)
    mix.location = (-300.0, 180.0)
    invert.location = (-620.0, 20.0)
    group_input.location = (-860.0, 180.0)
    principled_bsdf.location = (0.0, 0.0)
    group_input_001.location = (-500.0, -80.0)
    math.location = (-780.0, -520.0)
    math_001.location = (-600.0, -520.0)
    math_002.location = (-300.0, -520.0)
    group_input_002.location = (-1220.0, -460.0)

    #Set dimensions
    group_output.width, group_output.height = 140.0, 100.0
    mix.width, mix.height = 140.0, 100.0
    invert.width, invert.height = 140.0, 100.0
    group_input.width, group_input.height = 140.0, 100.0
    principled_bsdf.width, principled_bsdf.height = 240.0, 100.0
    group_input_001.width, group_input_001.height = 140.0, 100.0
    math.width, math.height = 140.0, 100.0
    math_001.width, math_001.height = 140.0, 100.0
    math_002.width, math_002.height = 140.0, 100.0
    group_input_002.width, group_input_002.height = 140.0, 100.0

    #initialize sf_shadernode links
    #principled_bsdf.BSDF -> group_output.BSDF
    sf_shadernode.links.new(principled_bsdf.outputs[0], group_output.inputs[0])
    #group_input_001.METAL -> principled_bsdf.Metallic
    sf_shadernode.links.new(group_input_001.outputs[3], principled_bsdf.inputs[6])
    #group_input_001.ROUGH -> principled_bsdf.Roughness
    sf_shadernode.links.new(group_input_001.outputs[4], principled_bsdf.inputs[9])
    #group_input_001.NORMAL -> principled_bsdf.Normal
    sf_shadernode.links.new(group_input_001.outputs[1], principled_bsdf.inputs[22])
    #group_input_001.HEIGHT -> group_output.Displacement
    sf_shadernode.links.new(group_input_001.outputs[6], group_output.inputs[1])
    #group_input.COLOR -> mix.A
    sf_shadernode.links.new(group_input.outputs[0], mix.inputs[6])
    #group_input.AO -> invert.Color
    sf_shadernode.links.new(group_input.outputs[5], invert.inputs[1])
    #invert.Color -> mix.B
    sf_shadernode.links.new(invert.outputs[0], mix.inputs[7])
    #group_input_001.COLOR -> principled_bsdf.Base Color
    sf_shadernode.links.new(group_input_001.outputs[0], principled_bsdf.inputs[0])
    #group_input_002.OPACITY -> math.Value
    sf_shadernode.links.new(group_input_002.outputs[2], math.inputs[0])
    #group_input_002.A_TEST_THRESH -> math.Value
    sf_shadernode.links.new(group_input_002.outputs[7], math.inputs[1])
    #math.Value -> math_001.Value
    sf_shadernode.links.new(math.outputs[0], math_001.inputs[1])
    #math_001.Value -> math_002.Value
    sf_shadernode.links.new(math_001.outputs[0], math_002.inputs[0])
    #group_input_002.OPACITY -> math_002.Value
    sf_shadernode.links.new(group_input_002.outputs[2], math_002.inputs[1])
    #math_002.Value -> principled_bsdf.Alpha
    sf_shadernode.links.new(math_002.outputs[0], principled_bsdf.inputs[21])

def GetMatNode():
	if "SF_ShaderNode" in bpy.data.node_groups:
		return bpy.data.node_groups["SF_ShaderNode"]
	else:
		return sf_shadernode_node_group()

#initialize material node group
def new_mat(mat_name:str):
    mat = bpy.data.materials.new(name = mat_name)
    mat.use_nodes = True
    material = mat.node_tree
    #start with a clean node tree
    for node in material.nodes:
        material.nodes.remove(node)
    #initialize material nodes
    #node Material Output
    material_output = material.nodes.new("ShaderNodeOutputMaterial")
    material_output.target = 'ALL'
    #Thickness
    material_output.inputs[3].default_value = 0.0

    GetMatNode()

    #node Group
    group = material.nodes.new("ShaderNodeGroup")
    group.node_tree = bpy.data.node_groups["SF_ShaderNode"]
    #Input_8
    group.inputs[6].default_value = (0.0, 0.0, 0.0)
    #Input_9
    group.inputs[7].default_value = 0.0
    #Input_10
    group.inputs[8].default_value = 0.0

    #node COLOR
    color = material.nodes.new("ShaderNodeTexImage")
    color.name = "COLOR"
    color.interpolation = 'Linear'
    color.projection = 'FLAT'
    color.extension = 'REPEAT'
    color.mute = True
    #Vector
    color.inputs[0].default_value = (0.0, 0.0, 0.0)

    #node Normal Map
    normal_map = material.nodes.new("ShaderNodeNormalMap")
    normal_map.space = 'TANGENT'
    #Strength
    normal_map.inputs[0].default_value = 1.0

    #node OPACITY
    opacity = material.nodes.new("ShaderNodeTexImage")
    opacity.name = "OPACITY"
    opacity.interpolation = 'Linear'
    opacity.projection = 'FLAT'
    opacity.extension = 'REPEAT'
    opacity.mute = True
    #Vector
    opacity.inputs[0].default_value = (0.0, 0.0, 0.0)

    #node NORMAL
    normal = material.nodes.new("ShaderNodeTexImage")
    normal.name = "NORMAL"
    normal.interpolation = 'Linear'
    normal.projection = 'FLAT'
    normal.extension = 'REPEAT'
    normal.mute = True
    #Vector
    normal.inputs[0].default_value = (0.0, 0.0, 0.0)

    #node ROUGHNESS
    roughness = material.nodes.new("ShaderNodeTexImage")
    roughness.name = "ROUGH"
    roughness.interpolation = 'Linear'
    roughness.projection = 'FLAT'
    roughness.extension = 'REPEAT'
    roughness.mute = True
    #Vector
    roughness.inputs[0].default_value = (0.0, 0.0, 0.0)

    #node HEIGHT
    height = material.nodes.new("ShaderNodeTexImage")
    height.name = "HEIGHT"
    height.interpolation = 'Linear'
    height.projection = 'FLAT'
    height.extension = 'REPEAT'
    height.mute = True
    #Vector
    height.inputs[0].default_value = (0.0, 0.0, 0.0)

    #node AO
    ao = material.nodes.new("ShaderNodeTexImage")
    ao.name = "AO"
    ao.interpolation = 'Linear'
    ao.projection = 'FLAT'
    ao.extension = 'REPEAT'
    ao.mute = True
    #Vector
    ao.inputs[0].default_value = (0.0, 0.0, 0.0)

    #node METALNESS
    metalness = material.nodes.new("ShaderNodeTexImage")
    metalness.name = "METAL"
    metalness.interpolation = 'Linear'
    metalness.projection = 'FLAT'
    metalness.extension = 'REPEAT'
    metalness.mute = True
    #Vector
    metalness.inputs[0].default_value = (0.0, 0.0, 0.0)


    #Set locations
    material_output.location = (300.0, 300.0)
    group.location = (-20.0, 300.0)
    color.location = (-820.0, 300.0)
    normal_map.location = (-340.0, 160.0)
    opacity.location = (-820.0, -100.0)
    normal.location = (-820.0, 100.0)
    roughness.location = (-820.0, -500.0)
    height.location = (-820.0, -900.0)
    ao.location = (-820.0, -700.0)
    metalness.location = (-820.0, -300.0)

    #Set dimensions
    material_output.width, material_output.height = 140.0, 100.0
    group.width, group.height = 237.6750030517578, 100.0
    color.width, color.height = 240.0, 100.0
    normal_map.width, normal_map.height = 150.0, 100.0
    opacity.width, opacity.height = 240.0, 100.0
    normal.width, normal.height = 240.0, 100.0
    roughness.width, roughness.height = 240.0, 100.0
    height.width, height.height = 240.0, 100.0
    ao.width, ao.height = 240.0, 100.0
    metalness.width, metalness.height = 240.0, 100.0

    #initialize material links
    #group.BSDF -> material_output.Surface
    material.links.new(group.outputs[0], material_output.inputs[0])
    #group.Displacement -> material_output.Displacement
    material.links.new(group.outputs[1], material_output.inputs[2])
    #color.Color -> group.COLOR
    material.links.new(color.outputs[0], group.inputs[0])
    #normal.Color -> normal_map.Color
    material.links.new(normal.outputs[0], normal_map.inputs[1])
    #normal_map.Normal -> group.NORMAL
    material.links.new(normal_map.outputs[0], group.inputs[1])
    #opacity.Color -> group.OPACITY
    material.links.new(opacity.outputs[0], group.inputs[2])
    #ao.Color -> group.AO
    material.links.new(ao.outputs[0], group.inputs[5])
    #roughness.Color -> group.ROUGHNESS
    material.links.new(roughness.outputs[0], group.inputs[4])
    #metalness.Color -> group.METALNESS
    material.links.new(metalness.outputs[0], group.inputs[3])

    mat.blend_method = 'HASHED'
    mat.use_backface_culling = True
    mat.shadow_method = 'HASHED'

    return mat