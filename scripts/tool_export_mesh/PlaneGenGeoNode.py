### CapsuleGenGeoNode.py ###
# Automatically generated by NodeToPython Addon: https://github.com/BrendanParmer/NodeToPython/releases/tag/v2.2.0
import bpy

#initialize plane_gen node group
def plane_gen_node_group():
	plane_gen= bpy.data.node_groups.new(type = 'GeometryNodeTree', name = "Plane_Gen")

	#initialize plane_gen nodes
	#node Points
	points = plane_gen.nodes.new("GeometryNodePoints")
	#Count
	points.inputs[0].default_value = 1
	#Radius
	points.inputs[2].default_value = 0.10000000149011612

	#node Mesh Circle
	mesh_circle = plane_gen.nodes.new("GeometryNodeMeshCircle")
	mesh_circle.fill_type = 'TRIANGLE_FAN'
	#Vertices
	mesh_circle.inputs[0].default_value = 32

	#node Align Euler to Vector
	align_euler_to_vector = plane_gen.nodes.new("FunctionNodeAlignEulerToVector")
	align_euler_to_vector.axis = 'Z'
	align_euler_to_vector.pivot_axis = 'AUTO'
	#Rotation
	align_euler_to_vector.inputs[0].default_value = (0.0, 0.0, 0.0)
	#Factor
	align_euler_to_vector.inputs[1].default_value = 1.0

	#node Instance on Points
	instance_on_points = plane_gen.nodes.new("GeometryNodeInstanceOnPoints")
	#Selection
	instance_on_points.inputs[1].default_value = True
	#Pick Instance
	instance_on_points.inputs[3].default_value = False
	#Instance Index
	instance_on_points.inputs[4].default_value = 0
	#Scale
	instance_on_points.inputs[6].default_value = (1.0, 1.0, 1.0)

	#plane_gen outputs
	#output Geometry
	plane_gen.outputs.new('NodeSocketGeometry', "Geometry")
	plane_gen.outputs[0].attribute_domain = 'POINT'


	#node Group Output
	group_output = plane_gen.nodes.new("NodeGroupOutput")

	#plane_gen inputs
	#input Geometry
	plane_gen.inputs.new('NodeSocketGeometry', "Geometry")
	plane_gen.inputs[0].attribute_domain = 'POINT'

	#input Origin
	plane_gen.inputs.new('NodeSocketVector', "Origin")
	plane_gen.inputs[1].default_value = (0.0, 0.0, 0.0)
	plane_gen.inputs[1].min_value = -3.4028234663852886e+38
	plane_gen.inputs[1].max_value = 3.4028234663852886e+38
	plane_gen.inputs[1].attribute_domain = 'POINT'

	#input Normal
	plane_gen.inputs.new('NodeSocketVector', "Normal")
	plane_gen.inputs[2].default_value = (0.0, 0.0, 1.0)
	plane_gen.inputs[2].min_value = -3.4028234663852886e+38
	plane_gen.inputs[2].max_value = 3.4028234663852886e+38
	plane_gen.inputs[2].attribute_domain = 'POINT'

	#input Size
	plane_gen.inputs.new('NodeSocketFloatDistance', "Size")
	plane_gen.inputs[3].default_value = 1.0
	plane_gen.inputs[3].min_value = 0.0
	plane_gen.inputs[3].max_value = 3.4028234663852886e+38
	plane_gen.inputs[3].attribute_domain = 'POINT'


	#node Group Input
	group_input = plane_gen.nodes.new("NodeGroupInput")


	#Set locations
	points.location = (-120.0, 0.0)
	mesh_circle.location = (-120.0, -120.0)
	align_euler_to_vector.location = (-120.0, -260.0)
	instance_on_points.location = (60.0, 0.0)
	group_output.location = (240.0, 0.0)
	group_input.location = (-320.0, 0.0)

	#Set dimensions
	points.width, points.height = 140.0, 100.0
	mesh_circle.width, mesh_circle.height = 140.0, 100.0
	align_euler_to_vector.width, align_euler_to_vector.height = 140.0, 100.0
	instance_on_points.width, instance_on_points.height = 140.0, 100.0
	group_output.width, group_output.height = 140.0, 100.0
	group_input.width, group_input.height = 140.0, 100.0

	#initialize plane_gen links
	#group_input.Origin -> points.Position
	plane_gen.links.new(group_input.outputs[1], points.inputs[1])
	#points.Geometry -> instance_on_points.Points
	plane_gen.links.new(points.outputs[0], instance_on_points.inputs[0])
	#instance_on_points.Instances -> group_output.Geometry
	plane_gen.links.new(instance_on_points.outputs[0], group_output.inputs[0])
	#align_euler_to_vector.Rotation -> instance_on_points.Rotation
	plane_gen.links.new(align_euler_to_vector.outputs[0], instance_on_points.inputs[5])
	#group_input.Normal -> align_euler_to_vector.Vector
	plane_gen.links.new(group_input.outputs[2], align_euler_to_vector.inputs[2])
	#group_input.Size -> mesh_circle.Radius
	plane_gen.links.new(group_input.outputs[3], mesh_circle.inputs[1])
	#mesh_circle.Mesh -> instance_on_points.Instance
	plane_gen.links.new(mesh_circle.outputs[0], instance_on_points.inputs[2])
	plane_gen.use_fake_user = True
	return plane_gen

def GetGeoNode():
	if "Plane_Gen" in bpy.data.node_groups:
		return bpy.data.node_groups["Plane_Gen"]
	else:
		return plane_gen_node_group()