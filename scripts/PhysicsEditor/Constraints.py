import bpy
from bpy.types import Node, NodeSocket

import PhysicsEditor.NodeBase as NodeBase
from PhysicsEditor.NodeBase import find_vis_meshes
import PhysicsEditor.utils_node as utils_node
import utils_blender
import PlaneGenGeoNode

class StandardLinkConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    ''''''

    bl_idname = 'StandardLinkConstraint'
    bl_label = 'Standard Link'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=True)

    def init(self, context):
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        links_skt = self.inputs.new('hclClothLinksType', 'Links')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        print(f'check_valid {self.name}')
        if self.inputs['Particles'].is_linked and self.inputs['Links'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Particles'])
            parent1 = utils_node.get_linked_single(self.inputs['Links'])
            if not parent.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Particles linked")
            if not parent1.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Links linked")
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, 'No Particles or Links linked')
    
    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.prop(self, "show_constraint", text="Show Constraint")
    
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Particles':
            particles = utils_node.get_socket_input_single(self,'Particles').copy()
            links = utils_node.get_socket_input_single(self,'Links')
            constraint = {
                'constraint': 'StandardLink',
                'name': self.name,
                **links,
            }
            particles['constraints'].append(constraint)
            return particles
        return None

class StretchLinkConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    ''''''

    bl_idname = 'StretchLinkConstraint'
    bl_label = 'Stretch Link'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=True)

    def init(self, context):
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        links_skt = self.inputs.new('hclClothLinksType', 'Links')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        print(f'check_valid {self.name}')
        if self.inputs['Particles'].is_linked and self.inputs['Links'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Particles'])
            parent1 = utils_node.get_linked_single(self.inputs['Links'])
            if not parent.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Particles linked")
            if not parent1.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Links linked")
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, 'No Particles or Links linked')
    
    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.prop(self, "show_constraint", text="Show Constraint")
    
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Particles':
            particles = utils_node.get_socket_input_single(self,'Particles').copy()
            links = utils_node.get_socket_input_single(self,'Links')
            constraint = {
                'constraint': 'StretchLink',
                'name': self.name,
                **links,
            }
            particles['constraints'].append(constraint)
            return particles
        return None

class BendLinkConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    ''''''

    bl_idname = 'BendLinkConstraint'
    bl_label = 'Bend Link'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=True)

    def init(self, context):
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        links_skt = self.inputs.new('hclClothLinksType', 'Links')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        print(f'check_valid {self.name}')
        if self.inputs['Particles'].is_linked and self.inputs['Links'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Particles'])
            parent1 = utils_node.get_linked_single(self.inputs['Links'])
            if not parent.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Particles linked")
            if not parent1.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Links linked")
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, 'No Particles or Links linked')
    
    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.prop(self, "show_constraint", text="Show Constraint")
    
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Particles':
            particles = utils_node.get_socket_input_single(self,'Particles').copy()
            links = utils_node.get_socket_input_single(self,'Links')
            constraint = {
                'constraint': 'BendLink',
                'name': self.name,
                **links,
            }
            particles['constraints'].append(constraint)
            return particles
        return None

def update_plane_normal_dir(self, context):
    planes = find_vis_meshes(self)
    if planes is None or len(planes) == 0:
        return
    for plane in planes[1:]:
        utils_blender.SetPlaneParameters(plane, normal_dir=self.plane_normal_dir)

class BonePlanesConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Constraint Particles to Bone Planes'''

    bl_idname = 'BonePlanesConstraint'
    bl_label = 'Global Bone Plane Constraint'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=True)
    stiffness: bpy.props.FloatProperty(name='Stiffness', default=1)
    plane_normal_dir: bpy.props.FloatVectorProperty(name='Plane Normal Direction', default=(0, 0, 1), update=update_plane_normal_dir)

    def init(self, context):
        PlaneGenGeoNode.GetGeoNode()
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        bone_skt = self.inputs.new('hkaBoneType', 'Bone')
        input_skt1 = self.inputs.new('IndicesOnDomainType', 'Particle Indices')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        print(f'check_valid {self.name}')
        if self.inputs['Particles'].is_linked and self.inputs['Bone'].is_linked and self.inputs['Particle Indices'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Particles'])
            parent1 = utils_node.get_linked_single(self.inputs['Bone'])
            parent2 = utils_node.get_linked_single(self.inputs['Particle Indices'])
            if not parent.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Particles linked")
            if not parent1.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Bone linked")
            if not parent2.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Particle Indices linked")
            
            domain = utils_node.get_socket_input_single(self,'Particle Indices')[1]
            if domain != 'POINT':
                return utils_node.NodeValidityReturn(False, self, "Particle Indices must be on POINT domain")
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, 'No Particles, Bone or Particle Indices linked')
    
    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.prop(self, "show_constraint", text="Show Constraint")
        layout.label(text="Plane Normal Direction:")
        layout.prop(self, "plane_normal_dir", text="")
        layout.label(text="Stiffness:")
        layout.prop(self, "stiffness", text="")

    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Particles':
            particles = utils_node.get_socket_input_single(self,'Particles').copy()
            bone = utils_node.get_socket_input_single(self,'Bone')
            particle_indices = utils_node.get_socket_input_single(self,'Particle Indices')
            constraint = {
                'constraint': 'BonePlanes',
                'name': self.name,
                'bone': bone,
                'particle_indices': particle_indices,
                'plane_normal_dir': self.plane_normal_dir,
            }
            particles['constraints'].append(constraint)
            return particles
        return None
    
    def draw_vis_mesh(self):
        print(f'draw_vis_mesh {self.name}')
        if not self.show_constraint:
            return None
        particles = utils_node.get_socket_input_single(self,'Particles')
        p_ids = utils_node.get_socket_input_single(self,'Particle Indices')[0]
        print(p_ids)
        positions = [particles['particles'][p_id]['position'] for p_id in p_ids if p_id in particles['particles'].keys()]
        planes = [utils_blender.PlaneFromOriginNormal(self.name, position, self.plane_normal_dir) for position in positions]
        hkaBone = utils_node.get_socket_input_single(self,'Bone')
        anchor = utils_blender.ConstraintObjsToBoneRotation(planes, hkaBone['Armature'], hkaBone['Bone Index'])
        if anchor is None:
            return None
        return [anchor] + planes