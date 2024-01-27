import bpy
from bpy.types import Node, NodeSocket

import PhysicsEditor.Utilities.utils_node as utils_node

import PhysicsEditor.Nodes.NodeBase as NodeBase

import PhysicsEditor.Utilities.utils_geometry as utils_geometry

class SimpleTriangleBoneDriverNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Drive physics bones with the closest triangle from simulation mesh'''
    bl_idname = 'SimpleTriangleBoneDriver'
    bl_label = 'Simple Triangle Bone Driver'

    mode_enum_prop: bpy.props.EnumProperty(name='Mode', items=[('FACE', 'Face Center', 'Drive physics bones with the triangle of the closest face center from simulation mesh'), ('EDGE','Avg. Edge Distance','Drive physics bones with the triangle with the minimun average edge distance to the bone from simulation mesh')], default='EDGE')

    def init(self, context):
        super().init(context)
        self.inputs.new('hkaBoneType', 'Bones')
        self.inputs.new('NodeSocketGeometry', 'Simulation Mesh')
        self.outputs.new('SimulationBonesType', 'Physics Bones')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        if not self.inputs['Bones'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Bones linked")
        if not self.inputs['Simulation Mesh'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Simulation Mesh linked")
        parent = utils_node.get_linked_single(self.inputs['Bones'])
        parent1 = utils_node.get_linked_single(self.inputs['Simulation Mesh'])
        if not parent.check_valid():
            return utils_node.NodeValidityReturn(False, self, "Invalid Bones linked")
        if not parent1.check_valid():
            return utils_node.NodeValidityReturn(False, self, "Invalid Simulation Mesh linked")
        return utils_node.NodeValidityReturn(True, self)
    
    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Mode:")
        layout.prop(self, "mode_enum_prop", text="")

    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Physics Bones':
            bones = utils_node.get_socket_input_single(self,'Bones')
            mesh = utils_node.get_socket_input_single(self,'Simulation Mesh')
            return {'factory': 'SimpleTriangleBoneDriver', 
                    'driver': self.name,
                    'mesh': mesh.name, 
                    'transform_set': bones['Armature'].name, 
                    'mode': self.mode_enum_prop, 
                    'cloth_bones': bones['Bone Indices']
                    }
        return None
    
    def gen_driver_data(self, driver_dict: dict, mesh: bpy.types.Object, armature: bpy.types.Object):
        if driver_dict['factory'] != 'SimpleTriangleBoneDriver':
            return None
        bone_indices = driver_dict['cloth_bones']
        mode = driver_dict['mode']
        face_indices = []
        bone_centers = [armature.data.bones[i].head_local for i in bone_indices]
        if mode == 'FACE':
            rtn = utils_geometry.QueryCloserFacesMultiple(mesh, 1, bone_centers)
            face_indices = [i for i, _, _ in rtn]
        elif mode == 'EDGE':
            def query_func(face:bpy.types.MeshPolygon, center):
                pivot1_co, pivot2_co, pivot3_co = utils_geometry.GetTriVerts(mesh, face)

                dist1, dist2, dist3 = utils_geometry.TriangleEdgeDistances(pivot1_co, pivot2_co, pivot3_co, center)
                return max(dist1, dist2, dist3)
            
            rtn = utils_geometry.QueryCloserFacesMultiple(mesh, 3, bone_centers, query_func)
            rtn = [sorted(lst, key=lambda x: x[1] * x[2]) for lst in rtn]
            face_indices = [lst[0][0] for lst in rtn]
        else:
            return None

        return {'factory': 'SimpleTriangleBoneDriver', 
                'mesh': mesh.name, 
                'transform_set': armature.name, 
                'mode': mode, 
                'cloth_bones': bone_indices,
                'face_indices': face_indices,
                }