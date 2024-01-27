import bpy
from bpy.types import Node, NodeSocket

import PhysicsEditor.Nodes.NodeBase as NodeBase

from PhysicsEditor.Nodes.NodeBase import find_vis_meshes

import PhysicsEditor.Utilities.utils_node as utils_node

import PhysicsEditor.Prefabs.PlaneGenGeoNode as PlaneGenGeoNode

import PhysicsEditor.Utilities.utils_prefabs as utils_prefabs

def update_visibility(self, context):
    objects = find_vis_meshes(self)
    if objects is None or len(objects) == 0:
        return
    for obj in objects:
        obj.hide_viewport = not self.show_constraint

class StandardLinkConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Default cloth simulation links between particles. Constraint on the length of the link'''

    bl_idname = 'StandardLinkConstraint'
    bl_label = 'Standard Link'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=False, update=update_visibility)

    def init(self, context):
        super().init(context)
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        links_skt = self.inputs.new('hclClothLinksType', 'Links')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
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
        if self.show_constraint:
            box = layout.box()
            box.scale_y = 0.9
            box.prop(self, "show_constraint", text="Show Constraint")
        else:
            layout.prop(self, "show_constraint", text="Show Constraint")
    
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Particles':
            particles = utils_node.get_socket_input_single(self,'Particles').copy()
            links: dict = utils_node.get_socket_input_single(self,'Links')['links']
            if 'constraints' in particles:
                # if there exists a constraint of the same type, pick it
                for constraint in particles['constraints']:
                    if constraint['constraint'] == 'StandardLink':
                        constraint['links'] = {**constraint['links'], **links}
                        return particles
            constraint = {
                'constraint': 'StandardLink',
                'name': self.name,
                'links': links,
            }
            particles['constraints'].append(constraint)
            return particles
        return None

class StretchLinkConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Constraint the stretch of links between particles. Useful for cloth with elastic properties'''

    bl_idname = 'StretchLinkConstraint'
    bl_label = 'Stretch Link'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=False, update=update_visibility)

    def init(self, context):
        super().init(context)
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        links_skt = self.inputs.new('hclClothLinksType', 'Links')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
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
        if self.show_constraint:
            box = layout.box()
            box.scale_y = 0.9
            box.prop(self, "show_constraint", text="Show Constraint")
        else:
            layout.prop(self, "show_constraint", text="Show Constraint")
    
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Particles':
            particles = utils_node.get_socket_input_single(self,'Particles').copy()
            links: dict = utils_node.get_socket_input_single(self,'Links')['links']
            if 'constraints' in particles:
                # if there exists a constraint of the same type, pick it
                for constraint in particles['constraints']:
                    if constraint['constraint'] == 'StretchLink':
                        constraint['links'] = {**constraint['links'], **links}
                        return particles
            constraint = {
                'constraint': 'StretchLink',
                'name': self.name,
                'links': links,
            }
            particles['constraints'].append(constraint)
            return particles
        return None

class BendStiffnessConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Constraint the bend stiffness of links between particles'''

    bl_idname = 'BendStiffnessConstraint'
    bl_label = 'Bend Stiffness'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=True)

    def init(self, context):
        super().init(context)
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        links_skt = self.inputs.new('hclClothLinksType', 'Links')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
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
                'constraint': 'BendStiffness',
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
        utils_prefabs.SetPlaneParameters(plane, normal_dir=self.plane_normal_dir)

def update_plane_size(self, context):
    planes = find_vis_meshes(self)
    if planes is None or len(planes) == 0:
        return
    for plane in planes[1:]:
        utils_prefabs.SetPlaneParameters(plane, size=self.vis_plane_size)

class BonePlanesConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Constraint Particles to a Plane that copies the rotation of a bone'''

    bl_idname = 'BonePlanesConstraint'
    bl_label = 'Global Bone Plane Constraint'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=False, update=update_visibility)
    vis_plane_size: bpy.props.FloatProperty(name='Plane Size', default=0.1, min=0.001, update=update_plane_size)
    stiffness: bpy.props.FloatProperty(name='Stiffness', default=1)
    plane_normal_dir: bpy.props.FloatVectorProperty(name='Plane Normal Direction', default=(1, 0, 0), update=update_plane_normal_dir)

    def init(self, context):
        super().init(context)
        PlaneGenGeoNode.GetGeoNode()
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        bone_skt = self.inputs.new('hkaBoneType', 'Bone')
        input_skt1 = self.inputs.new('IndicesOnDomainType', 'Particle Indices')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
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
        if self.show_constraint:
            box = layout.box()
            box.scale_y = 0.9
            box.prop(self, "show_constraint", text="Show Constraint")
            box.prop(self, "vis_plane_size", text="Vis Size")
        else:
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
            plane_normal = list(self.plane_normal_dir)
            if not any(plane_normal):
                plane_normal = [0, 0, 1]
            plane_normal.append(2)
            particles_list = particle_indices[0]
            bones_list = [bone['Bone Index'] for _ in particle_indices[0]]
            plane_normal_dir_list = [plane_normal for _ in particle_indices[0]]
            stiffness_list = [float(self.stiffness) for _ in particle_indices[0]]
            if 'constraints' in particles:
                # if there exists a constraint of the same type, pick it
                for constraint in particles['constraints']:
                    if constraint['constraint'] == 'BonePlanes':
                        constraint['particles'].extend(particles_list)
                        constraint['bone_ids'].extend(bones_list)
                        constraint['plane_normal_dirs'].extend(plane_normal_dir_list)
                        constraint['stiffnesses'].extend(stiffness_list)
                        return particles

            constraint = {
                'constraint': 'BonePlanes',
                'name': self.name,
                'particles': particles_list,
                'bone_ids': bones_list,
                'plane_normal_dirs': plane_normal_dir_list,
                'stiffnesses': stiffness_list,
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
        planes = [utils_prefabs.PlaneFromOriginNormal(self.name, position, self.plane_normal_dir, size = self.vis_plane_size) for position in positions]
        hkaBone = utils_node.get_socket_input_single(self,'Bone')
        anchor = utils_prefabs.ConstraintObjsToBoneRotation(planes, hkaBone['Armature'], hkaBone['Bone Index'])
        if anchor is None:
            return None
        vis_objs = [anchor] + planes
        for obj in vis_objs:
            obj.hide_viewport = not self.show_constraint
        return vis_objs