import bpy
from bpy.types import Node, NodeSocket

import PhysicsEditor.Utilities.utils_node as utils_node

import PhysicsEditor.Nodes.NodeBase as NodeBase

class TwoStatePhysicsDataNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Generic Physics Data Factory'''

    bl_idname = 'TwoStatePhysicsData'
    bl_label = 'Two State Physics Data'

    def init(self, context):
        self.inputs.new('hclSimClothDataType', 'Cloth Data')
        self.inputs.new('NodeSocketGeometry', 'Simulation Mesh')
        self.inputs.new('SimulationBonesType', 'Physics Bones')
        self.outputs.new('hclPhysicsDataType', 'Physics Data')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        print(f'check_valid {self.name}')
        if not self.inputs['Cloth Data'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Cloth Data linked")
        if not self.inputs['Physics Bones'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Physics Bones linked")
        if not self.inputs['Simulation Mesh'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Simulation Mesh linked")
        parent = utils_node.get_linked_single(self.inputs['Cloth Data'])
        parent1 = utils_node.get_linked_single(self.inputs['Physics Bones'])
        parent2 = utils_node.get_linked_single(self.inputs['Simulation Mesh'])
        if parent.check_valid() and parent1.check_valid() and parent2.check_valid():
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, "Invalid Data linked")
    
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        cloth_data = utils_node.get_socket_input_single(self,'Cloth Data')
        bones = utils_node.get_socket_input_single(self,'Physics Bones')
        mesh = utils_node.get_socket_input_single(self,'Simulation Mesh')
        return {'factory': 'TwoStatesPhysicsData',
                'cloth_data': cloth_data, 
                'reference_mesh': mesh.name, 
                'transform_set': bones['transform_set'],
                'bone_driver_data': bones,
                }
    