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

    #node Group Input.001
    group_input_001 = sf_shadernode.nodes.new("NodeGroupInput")
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

    #input METALNESS
    sf_shadernode.inputs.new('NodeSocketFloatFactor', "METAL")
    sf_shadernode.inputs[3].default_value = 0.0
    sf_shadernode.inputs[3].min_value = 0.0
    sf_shadernode.inputs[3].max_value = 1.0
    sf_shadernode.inputs[3].attribute_domain = 'POINT'

    #input ROUGHNESS
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

    #node Math.003
    math_003 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_003.operation = 'COMPARE'
    #Value_001
    math_003.inputs[1].default_value = 4.0
    #Value_002
    math_003.inputs[2].default_value = 0.5

    #node Math.001
    math_001 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_001.operation = 'COMPARE'
    #Value_001
    math_001.inputs[1].default_value = 2.0
    #Value_002
    math_001.inputs[2].default_value = 0.5

    #node Math.002
    math_002 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_002.operation = 'COMPARE'
    #Value_001
    math_002.inputs[1].default_value = 3.0
    #Value_002
    math_002.inputs[2].default_value = 0.5

    #node Math.004
    math_004 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_004.operation = 'MULTIPLY'
    #Value_002
    math_004.inputs[2].default_value = 0.5

    #node Math.006
    math_006 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_006.operation = 'MULTIPLY'
    #Value_002
    math_006.inputs[2].default_value = 0.5

    #node Math.007
    math_007 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_007.operation = 'MULTIPLY'
    #Value_002
    math_007.inputs[2].default_value = 0.5

    #node Math.009
    math_009 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_009.operation = 'ADD'
    #Value_002
    math_009.inputs[2].default_value = 0.5

    #node Math.008
    math_008 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_008.operation = 'ADD'
    #Value_002
    math_008.inputs[2].default_value = 0.5

    #node Math.005
    math_005 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_005.operation = 'MULTIPLY'
    #Value_002
    math_005.inputs[2].default_value = 0.5

    #node Math
    math = sf_shadernode.nodes.new("ShaderNodeMath")
    math.operation = 'COMPARE'
    #Value_001
    math.inputs[1].default_value = 1.0
    #Value_002
    math.inputs[2].default_value = 0.5

    #node Color Attribute
    color_attribute = sf_shadernode.nodes.new("ShaderNodeVertexColor")
    color_attribute.layer_name = 'Color'

    #node Group Input
    group_input = sf_shadernode.nodes.new("NodeGroupInput")

    #node Separate Color
    separate_color = sf_shadernode.nodes.new("ShaderNodeSeparateColor")
    separate_color.mode = 'RGB'

    #node Group Input.002
    group_input_002 = sf_shadernode.nodes.new("NodeGroupInput")

    #node Math.010
    math_010 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_010.operation = 'ADD'
    math_010.use_clamp = True
    #Value_002
    math_010.inputs[2].default_value = 0.5

    #node Math.011
    math_011 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_011.operation = 'MULTIPLY'
    #Value_002
    math_011.inputs[2].default_value = 0.5

    #node Group Input.003
    group_input_003 = sf_shadernode.nodes.new("NodeGroupInput")

    #node Math.012
    math_012 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_012.operation = 'LESS_THAN'
    #Value_002
    math_012.inputs[2].default_value = 0.5

    #node Math.013
    math_013 = sf_shadernode.nodes.new("ShaderNodeMath")
    math_013.operation = 'SUBTRACT'
    #Value
    math_013.inputs[0].default_value = 1.0
    #Value_002
    math_013.inputs[2].default_value = 0.5


    #Set locations
    group_output.location = (290.0, 0.0)
    mix.location = (-300.0, 180.0)
    invert.location = (-620.0, 20.0)
    group_input_001.location = (-860.0, 180.0)
    principled_bsdf.location = (0.0, 0.0)
    math_003.location = (-1680.0, -1240.0)
    math_001.location = (-1680.0, -760.0)
    math_002.location = (-1680.0, -1000.0)
    math_004.location = (-1100.0, -620.0)
    math_006.location = (-1100.0, -940.0)
    math_007.location = (-1100.0, -1100.0)
    math_009.location = (-920.0, -940.0)
    math_008.location = (-920.0, -780.0)
    math_005.location = (-1100.0, -780.0)
    math.location = (-1680.0, -520.0)
    color_attribute.location = (-1480.0, -820.0)
    group_input.location = (-500.0, -80.0)
    separate_color.location = (-1320.0, -720.0)
    group_input_002.location = (-2000.0, -460.0)
    math_010.location = (-740.0, -860.0)
    math_011.location = (-500.0, -980.0)
    group_input_003.location = (-740.0, -1040.0)
    math_012.location = (-320.0, -1040.0)
    math_013.location = (-160.0, -1040.0)

    #Set dimensions
    group_output.width, group_output.height = 140.0, 100.0
    mix.width, mix.height = 140.0, 100.0
    invert.width, invert.height = 140.0, 100.0
    group_input_001.width, group_input_001.height = 140.0, 100.0
    principled_bsdf.width, principled_bsdf.height = 240.0, 100.0
    math_003.width, math_003.height = 140.0, 100.0
    math_001.width, math_001.height = 140.0, 100.0
    math_002.width, math_002.height = 140.0, 100.0
    math_004.width, math_004.height = 140.0, 100.0
    math_006.width, math_006.height = 140.0, 100.0
    math_007.width, math_007.height = 140.0, 100.0
    math_009.width, math_009.height = 140.0, 100.0
    math_008.width, math_008.height = 140.0, 100.0
    math_005.width, math_005.height = 140.0, 100.0
    math.width, math.height = 140.0, 100.0
    color_attribute.width, color_attribute.height = 140.0, 100.0
    group_input.width, group_input.height = 140.0, 100.0
    separate_color.width, separate_color.height = 140.0, 100.0
    group_input_002.width, group_input_002.height = 140.0, 100.0
    math_010.width, math_010.height = 140.0, 100.0
    math_011.width, math_011.height = 140.0, 100.0
    group_input_003.width, group_input_003.height = 140.0, 100.0
    math_012.width, math_012.height = 140.0, 100.0
    math_013.width, math_013.height = 140.0, 100.0

    #initialize sf_shadernode links
    #principled_bsdf.BSDF -> group_output.BSDF
    sf_shadernode.links.new(principled_bsdf.outputs[0], group_output.inputs[0])
    #group_input.METALNESS -> principled_bsdf.Metallic
    sf_shadernode.links.new(group_input.outputs[3], principled_bsdf.inputs[6])
    #group_input.ROUGHNESS -> principled_bsdf.Roughness
    sf_shadernode.links.new(group_input.outputs[4], principled_bsdf.inputs[9])
    #group_input.NORMAL -> principled_bsdf.Normal
    sf_shadernode.links.new(group_input.outputs[1], principled_bsdf.inputs[22])
    #group_input.HEIGHT -> group_output.Displacement
    sf_shadernode.links.new(group_input.outputs[6], group_output.inputs[1])
    #group_input_001.COLOR -> mix.A
    sf_shadernode.links.new(group_input_001.outputs[0], mix.inputs[6])
    #group_input_001.AO -> invert.Color
    sf_shadernode.links.new(group_input_001.outputs[5], invert.inputs[1])
    #invert.Color -> mix.B
    sf_shadernode.links.new(invert.outputs[0], mix.inputs[7])
    #group_input_002.A_BLEND_CHANNEL -> math.Value
    sf_shadernode.links.new(group_input_002.outputs[8], math.inputs[0])
    #group_input_002.A_BLEND_CHANNEL -> math_001.Value
    sf_shadernode.links.new(group_input_002.outputs[8], math_001.inputs[0])
    #group_input_002.A_BLEND_CHANNEL -> math_002.Value
    sf_shadernode.links.new(group_input_002.outputs[8], math_002.inputs[0])
    #group_input_002.A_BLEND_CHANNEL -> math_003.Value
    sf_shadernode.links.new(group_input_002.outputs[8], math_003.inputs[0])
    #color_attribute.Color -> separate_color.Color
    sf_shadernode.links.new(color_attribute.outputs[0], separate_color.inputs[0])
    #separate_color.Red -> math_004.Value
    sf_shadernode.links.new(separate_color.outputs[0], math_004.inputs[1])
    #math.Value -> math_004.Value
    sf_shadernode.links.new(math.outputs[0], math_004.inputs[0])
    #math_003.Value -> math_007.Value
    sf_shadernode.links.new(math_003.outputs[0], math_007.inputs[0])
    #math_002.Value -> math_006.Value
    sf_shadernode.links.new(math_002.outputs[0], math_006.inputs[0])
    #math_001.Value -> math_005.Value
    sf_shadernode.links.new(math_001.outputs[0], math_005.inputs[0])
    #separate_color.Green -> math_005.Value
    sf_shadernode.links.new(separate_color.outputs[1], math_005.inputs[1])
    #separate_color.Blue -> math_006.Value
    sf_shadernode.links.new(separate_color.outputs[2], math_006.inputs[1])
    #color_attribute.Alpha -> math_007.Value
    sf_shadernode.links.new(color_attribute.outputs[1], math_007.inputs[1])
    #math_004.Value -> math_008.Value
    sf_shadernode.links.new(math_004.outputs[0], math_008.inputs[0])
    #math_005.Value -> math_008.Value
    sf_shadernode.links.new(math_005.outputs[0], math_008.inputs[1])
    #math_006.Value -> math_009.Value
    sf_shadernode.links.new(math_006.outputs[0], math_009.inputs[0])
    #math_007.Value -> math_009.Value
    sf_shadernode.links.new(math_007.outputs[0], math_009.inputs[1])
    #math_009.Value -> math_010.Value
    sf_shadernode.links.new(math_009.outputs[0], math_010.inputs[1])
    #math_008.Value -> math_010.Value
    sf_shadernode.links.new(math_008.outputs[0], math_010.inputs[0])
    #group_input_003.OPACITY -> math_011.Value
    sf_shadernode.links.new(group_input_003.outputs[2], math_011.inputs[1])
    #group_input.COLOR -> principled_bsdf.Base Color
    sf_shadernode.links.new(group_input.outputs[0], principled_bsdf.inputs[0])
    #math_010.Value -> math_011.Value
    sf_shadernode.links.new(math_010.outputs[0], math_011.inputs[0])
    #math_011.Value -> math_012.Value
    sf_shadernode.links.new(math_011.outputs[0], math_012.inputs[0])
    #group_input_003.A_TEST_THRESH -> math_012.Value
    sf_shadernode.links.new(group_input_003.outputs[7], math_012.inputs[1])
    #math_012.Value -> math_013.Value
    sf_shadernode.links.new(math_012.outputs[0], math_013.inputs[1])
    #math_013.Value -> principled_bsdf.Alpha
    sf_shadernode.links.new(math_013.outputs[0], principled_bsdf.inputs[21])
	
    return sf_shadernode

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