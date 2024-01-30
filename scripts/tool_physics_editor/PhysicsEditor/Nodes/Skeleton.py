import bpy
from bpy.types import Node, NodeSocket

import PhysicsEditor.Nodes.NodeBase as NodeBase

import PhysicsEditor.Utilities.utils_node as utils_node

def get_bone_enum_items(self, context):
    if self.inputs['Skeleton'].is_linked:
        parent = utils_node.get_linked_single(self.inputs['Skeleton'])
        if parent.check_valid():
            items = []
            skeleton = utils_node.get_socket_input_single(self,'Skeleton')
            for bone in skeleton.data.bones:
                items.append((bone.name, bone.name, bone.name))
            return items
    return []

def update_bone_enum(self, context):
    utils_node.update_tree_from_node(self, context)

class PickBoneFromSkeletonNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Pick a Bone from Skeleton'''

    bl_idname = 'PickBoneFromSkeleton'
    bl_label = 'Pick Bone From Skeleton'

    bone_enum: bpy.props.EnumProperty(name='Bone', items=get_bone_enum_items, update=update_bone_enum)

    def init(self, context):
        super().init(context)
        skeleton_skt = self.inputs.new('hkaSkeletonType', 'Skeleton')
        skeleton_skt.show_expanded = True
        skeleton_skt.hide_value = True
        bone_index_skt = self.outputs.new('hkaBoneType', 'Bone')
        bone_index_skt.show_expanded = True
        bone_index_skt.hide_value = True

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        if self.inputs['Skeleton'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Skeleton'])
            if parent.check_valid():
                bone_name = self.bone_enum
                skeleton = utils_node.get_socket_input_single(self,'Skeleton')
                if bone_name in skeleton.data.bones:
                    return utils_node.NodeValidityReturn(True, self)
                else:
                    return utils_node.NodeValidityReturn(False, self, f"Bone \'{bone_name}\' not found in Skeleton")
        return utils_node.NodeValidityReturn(False, self, "No Skeleton linked")

    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Bone:")
        layout.prop(self, "bone_enum", text="")

    def get_socket_output(self, socket_name: str = "Bone"):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Bone':
            armature = utils_node.get_socket_input_single(self,'Skeleton')
            bone_index = armature.data.bones.find(self.bone_enum)
            return {'Armature':armature, 'Bone Index':bone_index, 'Bone Indices': [bone_index]}
        return None

def get_matched_bone_enum_items(self, context):
    matched_bones = self.get_matched_bones()
    return [(bone, bone, bone) for bone in matched_bones]

class MatchBoneNameNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Match Bone Name'''

    bl_idname = 'MatchBoneName'
    bl_label = 'Match Bone Name'

    match_mode_prop: bpy.props.EnumProperty(name='Match Mode', items=[('CONTAINS', 'Contains', 'Contains'), ('STARTS_WITH', 'Starts With', 'Starts With'), ('ENDS_WITH', 'Ends With', 'Ends With'), ('EXACT', 'Exact', 'Exact')])
    substring_prop: bpy.props.StringProperty(name='Substring', default='')
    matched_bone_enum: bpy.props.EnumProperty(name='Matched Bone', items=get_matched_bone_enum_items)

    def init(self, context):
        super().init(context)
        skeleton_skt = self.inputs.new('hkaSkeletonType', 'Skeleton')
        skeleton_skt.show_expanded = True
        skeleton_skt.hide_value = True
        bone_index_skt = self.outputs.new('hkaBoneType', 'Bones')
        bone_index_skt.show_expanded = True
        bone_index_skt.hide_value = True

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        if self.inputs['Skeleton'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Skeleton'])
            if parent.check_valid():
                if self.substring_prop != '':
                    return utils_node.NodeValidityReturn(True, self)
                else:
                    return utils_node.NodeValidityReturn(False, self, "Substring is empty")
        return utils_node.NodeValidityReturn(False, self, "No Skeleton linked")

    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Match Mode:")
        layout.prop(self, "match_mode_prop", text="")
        layout.label(text="Matching String:")
        layout.prop(self, "substring_prop", text="")
        layout.label(text="Matched Bone Dropdown:")
        layout.prop(self, "matched_bone_enum", text="")

    def get_matched_bones(self):
        if self.substring_prop == '':
            return []
        valid = self.check_valid()
        if not valid:
            return []
        
        skeleton = utils_node.get_socket_input_single(self,'Skeleton')
        bones = []
        if self.match_mode_prop == 'CONTAINS':
            bones = [bone.name for bone in skeleton.data.bones if self.substring_prop in bone.name]
        elif self.match_mode_prop == 'STARTS_WITH':
            bones = [bone.name for bone in skeleton.data.bones if bone.name.startswith(self.substring_prop)]
        elif self.match_mode_prop == 'ENDS_WITH':
            bones = [bone.name for bone in skeleton.data.bones if bone.name.endswith(self.substring_prop)]
        elif self.match_mode_prop == 'EXACT':
            bones = [bone.name for bone in skeleton.data.bones if bone.name == self.substring_prop]
        return bones


    def get_socket_output(self, socket_name: str = "Bones"):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Bones':
            armature = utils_node.get_socket_input_single(self,'Skeleton')
            bone_indices = []
            for i, bone in enumerate(armature.data.bones):
                if self.match_mode_prop == 'CONTAINS' and self.substring_prop in bone.name:
                    bone_indices.append(i)
                elif self.match_mode_prop == 'STARTS_WITH' and bone.name.startswith(self.substring_prop):
                    bone_indices.append(i)
                elif self.match_mode_prop == 'ENDS_WITH' and bone.name.endswith(self.substring_prop):
                    bone_indices.append(i)
                elif self.match_mode_prop == 'EXACT' and bone.name == self.substring_prop:
                    bone_indices.append(i)
            if len(bone_indices) == 1:
                return {'Armature':armature, 'Bone Index':bone_indices[0], 'Bone Indices': bone_indices}
            else:
                return {'Armature':armature, 'Bone Index':None, 'Bone Indices': bone_indices}
        return None

class CombineBoneSelectionNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Combine Bone/Bones inputs'''

    bl_idname = 'CombineBoneSelection'
    bl_label = 'Combine Bone Selection'

    def init(self, context):
        super().init(context)
        bone_index_skt_in1 = self.inputs.new('hkaBoneType', 'Bone(s) A')
        bone_index_skt_in2 = self.inputs.new('hkaBoneType', 'Bone(s) B')
        bone_index_skt = self.outputs.new('hkaBoneType', 'Bones')
 
    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        
        if self.inputs['Bone(s) A'].is_linked and self.inputs['Bone(s) B'].is_linked:
            parent1 = utils_node.get_linked_single(self.inputs['Bone(s) A'])
            parent2 = utils_node.get_linked_single(self.inputs['Bone(s) B'])
            if parent1.check_valid() and parent2.check_valid():
                return utils_node.NodeValidityReturn(True, self)
            else:
                return utils_node.NodeValidityReturn(False, self, "Bone(s) A or Bone(s) B not valid")
            
        elif self.inputs['Bone(s) A'].is_linked:
            parent1 = utils_node.get_linked_single(self.inputs['Bone(s) A'])
            if parent1.check_valid():
                return utils_node.NodeValidityReturn(True, self)
            else:
                return utils_node.NodeValidityReturn(False, self, "Bone(s) A not valid")
        
        elif self.inputs['Bone(s) B'].is_linked:
            parent2 = utils_node.get_linked_single(self.inputs['Bone(s) B'])
            if parent2.check_valid():
                return utils_node.NodeValidityReturn(True, self)
            else:
                return utils_node.NodeValidityReturn(False, self, "Bone(s) B not valid")
        
        return utils_node.NodeValidityReturn(False, self, "No Bone(s) A or Bone(s) B linked")
    
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Bones':
            bone_indices = []
            arma_obj = None
            if self.inputs['Bone(s) A'].is_linked:
                parent1 = utils_node.get_linked_single(self.inputs['Bone(s) A'])
                rtn1 = parent1.get_socket_output()
                arma_obj = rtn1['Armature']
                bone_indices += rtn1['Bone Indices']
            if self.inputs['Bone(s) B'].is_linked:
                parent2 = utils_node.get_linked_single(self.inputs['Bone(s) B'])
                rtn2 = parent2.get_socket_output()
                arma_obj = rtn2['Armature']
                bone_indices += rtn2['Bone Indices']
            if len(bone_indices) == 1:
                return {'Armature':arma_obj, 'Bone Index':bone_indices[0], 'Bone Indices': bone_indices}
            else:
                return {'Armature':arma_obj, 'Bone Index':None, 'Bone Indices': bone_indices}
        return None