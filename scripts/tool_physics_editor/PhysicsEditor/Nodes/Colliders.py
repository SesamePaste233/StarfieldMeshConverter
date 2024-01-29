import bpy
import math
import mathutils
from bpy.types import Context, Node, NodeSocket, UILayout

import PhysicsEditor.Nodes.NodeBase as NodeBase

from PhysicsEditor.Nodes.NodeBase import find_vis_meshes

import PhysicsEditor.Utilities.utils_node as utils_node

import PhysicsEditor.Prefabs.CapsuleGenGeoNode as CapsuleGenGeoNode

import PhysicsEditor.Utilities.utils_prefabs as utils_prefabs

def update_start_pos(self, context):
    utils_prefabs.SetCapsuleParameters(find_vis_meshes(self), bigEnd=self.start_pos_prop)

def update_end_pos(self, context):
    utils_prefabs.SetCapsuleParameters(find_vis_meshes(self), smallEnd=self.end_pos_prop)

def update_radius(self, context):
    utils_prefabs.SetCapsuleParameters(find_vis_meshes(self), smallRadius=self.radius_prop, bigRadius=self.radius_prop)

def update_start_radius(self, context):
    utils_prefabs.SetCapsuleParameters(find_vis_meshes(self), bigRadius=self.start_radius_prop)

def update_end_radius(self, context):
    utils_prefabs.SetCapsuleParameters(find_vis_meshes(self), smallRadius=self.end_radius_prop)

class CapsuleColliderNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Capsule collider'''

    bl_idname = 'CapsuleCollider'
    bl_label = 'Capsule Collider'

    capsule_name: bpy.props.StringProperty(name='Capsule Name', default='Invalid Collider')

    start_pos_prop: bpy.props.FloatVectorProperty(name='Start Position', default=(0, 0, 0), update=update_start_pos)
    end_pos_prop: bpy.props.FloatVectorProperty(name='End Position', default=(0, 0, 1), update=update_end_pos)
    radius_prop: bpy.props.FloatProperty(name='Radius', min=0.001, default=0.5, update=update_radius)    

    def init(self, context):
        super().init(context)
        CapsuleGenGeoNode.GetGeoNode()
        collider_skt = self.outputs.new('hclColliderType', 'Collider')
        bone_skt = self.inputs.new('hkaBoneType', 'Bind To Bone')
        bone_skt.hide_value = True

    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Capsule Name:")
        box = layout.box()
        box.scale_y = 0.7
        box.label(text=self.capsule_name)
        layout.label(text="Start Position:")
        layout.prop(self, "start_pos_prop", text="")
        layout.label(text="End Position:")
        layout.prop(self, "end_pos_prop", text="")
        layout.label(text="Radius:")
        layout.prop(self, "radius_prop", text="")

    def update(self):
        valid = self.check_valid()
        if not valid:
            self.capsule_name = 'Invalid Collider'
            return
        
        hkaBone = utils_node.get_socket_input_single(self,'Bind To Bone')
        armature = hkaBone['Armature']
        bone_index = hkaBone['Bone Index']
        bone_name = armature.data.bones[bone_index].name
        self.capsule_name = f'{bone_name}_Capsule'

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        parent = utils_node.get_linked_single(self.inputs['Bind To Bone'])
        if parent is None:
            return utils_node.NodeValidityReturn(False, self, "No Bone linked")
        if parent.check_valid():
            hkaBone = utils_node.get_socket_input_single(self,'Bind To Bone')
            if hkaBone['Bone Index'] is None:
                return utils_node.NodeValidityReturn(False, self, "Requires single bone input but given many")
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, "Invalid Bone linked")

    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Collider':
            hkaBone = utils_node.get_socket_input_single(self,'Bind To Bone')
            armature = hkaBone['Armature']
            bone_index = hkaBone['Bone Index']
            #bone_name = armature.data.bones[bone_index].name
            bone= armature.data.bones[bone_index]
            collider_world_transform: mathutils.Matrix = armature.matrix_world @ bone.matrix_local @ mathutils.Matrix.Rotation(math.radians(90.0), 4, 'Z')
            
            collider = {
                'collider': 'Capsule',
                'name': self.capsule_name,
                'type': 1,
                'localFrame': [[collider_world_transform[i][j] for i in range(4)] for j in range(4)],
                'capsuleStart': list(self.start_pos_prop),
                'capsuleEnd': list(self.end_pos_prop),
                'capsuleBigRadius': self.radius_prop,
                'capsuleSmallRadius': self.radius_prop,
                'bone': bone_index,
            }
            return collider
        return None

    def draw_vis_mesh(self):
        capsule = utils_prefabs.CapsuleFromParameters(self.capsule_name, self.start_pos_prop, self.end_pos_prop, self.radius_prop, self.radius_prop)
        hkaBone = utils_node.get_socket_input_single(self,'Bind To Bone')
        utils_prefabs.ConstraintObjToArmatureBone(capsule, hkaBone['Armature'], hkaBone['Bone Index'], True)
        return capsule

class TaperedCapsuleColliderNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Tapered Capsule collider'''

    bl_idname = 'TaperedCapsuleCollider'
    bl_label = 'Tapered Capsule Collider'

    capsule_name: bpy.props.StringProperty(name='Capsule Name', default='Invalid Collider')

    start_pos_prop: bpy.props.FloatVectorProperty(name='Start Position', default=(0, 0, 0), update=update_start_pos)
    end_pos_prop: bpy.props.FloatVectorProperty(name='End Position', default=(0, 0, 1), update=update_end_pos)
    start_radius_prop: bpy.props.FloatProperty(name='Start Radius', min=0.001, default=0.5, update=update_start_radius)
    end_radius_prop: bpy.props.FloatProperty(name='End Radius', min=0.001, default=0.5, update=update_end_radius)

    def init(self, context):
        super().init(context)
        CapsuleGenGeoNode.GetGeoNode()
        collider_skt = self.outputs.new('hclColliderType', 'Collider')
        bone_skt = self.inputs.new('hkaBoneType', 'Bind To Bone')
        bone_skt.hide_value = True

    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Capsule Name:")
        box = layout.box()
        box.scale_y = 0.7
        box.label(text=self.capsule_name)
        layout.label(text="Start Position:")
        layout.prop(self, "start_pos_prop", text="")
        layout.label(text="End Position:")
        layout.prop(self, "end_pos_prop", text="")
        layout.label(text="Start Radius:")
        layout.prop(self, "start_radius_prop", text="")
        layout.label(text="End Radius:")
        layout.prop(self, "end_radius_prop", text="")

    def update(self):
        valid = self.check_valid()
        if not valid:
            self.capsule_name = 'Invalid Collider'
            return
        
        hkaBone = utils_node.get_socket_input_single(self,'Bind To Bone')
        armature = hkaBone['Armature']
        bone_index = hkaBone['Bone Index']
        bone_name = armature.data.bones[bone_index].name
        self.capsule_name = f'{bone_name}_TaperedCapsule'
        
    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        parent = utils_node.get_linked_single(self.inputs['Bind To Bone'])
        if parent is None:
            return utils_node.NodeValidityReturn(False, self, "No Bone linked")
        if parent.check_valid():
            hkaBone = utils_node.get_socket_input_single(self,'Bind To Bone')
            if hkaBone['Bone Index'] is None:
                return utils_node.NodeValidityReturn(False, self, "Requires single bone input but given many")
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, "Invalid Bone linked")

    
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Collider':
            hkaBone = utils_node.get_socket_input_single(self,'Bind To Bone')
            armature = hkaBone['Armature']
            bone_index = hkaBone['Bone Index']
            #bone_name = armature.data.bones[bone_index].name
            bone= armature.data.bones[bone_index]
            collider_world_transform: mathutils.Matrix = armature.matrix_world @ bone.matrix_local @ mathutils.Matrix.Rotation(math.radians(90.0), 4, 'Z')
            
            if self.start_radius_prop < self.end_radius_prop:
                collider = {
                    'collider': 'Capsule',
                    'name': self.capsule_name,
                    'type': 1,
                    'localFrame': [[collider_world_transform[i][j] for i in range(4)] for j in range(4)],
                    'capsuleStart': list(self.end_pos_prop),
                    'capsuleEnd': list(self.start_pos_prop),
                    'capsuleBigRadius': self.end_radius_prop,
                    'capsuleSmallRadius': self.start_radius_prop,
                    'bone': bone_index,
                }
            else:
                collider = {
                    'collider': 'Capsule',
                    'name': self.capsule_name,
                    'type': 1,
                    'localFrame': [[collider_world_transform[i][j] for i in range(4)] for j in range(4)],
                    'capsuleStart': list(self.start_pos_prop),
                    'capsuleEnd': list(self.end_pos_prop),
                    'capsuleBigRadius': self.start_radius_prop,
                    'capsuleSmallRadius': self.end_radius_prop,
                    'bone': bone_index,
                }
            return collider
        return None
    
    def draw_vis_mesh(self):
        capsule = utils_prefabs.CapsuleFromParameters(self.capsule_name, self.start_pos_prop, self.end_pos_prop, self.start_radius_prop, self.end_radius_prop)
        hkaBone = utils_node.get_socket_input_single(self,'Bind To Bone')
        utils_prefabs.ConstraintObjToArmatureBone(capsule, hkaBone['Armature'], hkaBone['Bone Index'], True)
        return capsule
    