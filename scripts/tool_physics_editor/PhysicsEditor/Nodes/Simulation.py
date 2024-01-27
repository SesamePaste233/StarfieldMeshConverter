import bpy
from bpy.types import Node, NodeSocket

import PhysicsEditor.Utilities.utils_node as utils_node

import PhysicsEditor.Nodes.NodeBase as NodeBase

class SimClothDataNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Combine particles and colliders to create a cloth data, allow multiple collider inputs'''

    bl_idname = 'SimClothData'
    bl_label = 'Sim Cloth Data'

    gravity_vector: bpy.props.FloatVectorProperty(name='Gravity Vector', default=(0,0,-9.81), size=3)
    global_damping_per_second: bpy.props.FloatProperty(name='Global Damping Per Second', default=0.2)

    def init(self, context):
        super().init(context)
        particles = self.inputs.new('hclClothParticlesType', 'Particles')
        particles.hide_value = True
        colliders = self.inputs.new('hclMultiColliderType', 'Colliders')
        colliders.link_limit = 32
        colliders.display_shape = 'DIAMOND'
        colliders.hide_value = True
        my_output = self.outputs.new('hclSimClothDataType', 'Simulation Data')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        if not self.inputs['Particles'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Particles linked")
        
        parent = utils_node.get_linked_single(self.inputs['Particles'])
        if not parent.check_valid():
            return utils_node.NodeValidityReturn(False, self, "Invalid Particles linked")
        
        if self.inputs['Colliders'].is_linked:
            parents = utils_node.get_linked(self.inputs['Colliders'])
            if len(parents) > 32:
                return utils_node.NodeValidityReturn(False, self, "Too many Colliders linked; Maximum is 32")
            for parent in parents:
                if not parent.check_valid():
                    return utils_node.NodeValidityReturn(False, self, "Invalid Colliders linked")
                
        return utils_node.NodeValidityReturn(True, self)
        
    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Cloth Data':
            particles = utils_node.get_socket_input_single(self,'Particles')
            colliders = utils_node.get_socket_input(self,'Colliders')
            return {**particles, 
                    'gravity_vector': (self.gravity_vector[0], self.gravity_vector[1], self.gravity_vector[2]),
                    'global_damping_per_second': float(self.global_damping_per_second),
                    'colliders':colliders, 
                    'exclude_collision':{}
                    }
        return None

    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Gravity Vector:")
        layout.prop(self, "gravity_vector", text="")
        layout.label(text="Global Damping Per Second:")
        layout.prop(self, "global_damping_per_second", text="")

class hclParticlesFromMeshNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Generate particles from mesh vertices'''

    bl_idname = 'hclParticlesFromMesh'
    bl_label = 'Particles From Mesh'

    mass_prop: bpy.props.FloatProperty(name='Mass', default=1.0)
    radius_prop: bpy.props.FloatProperty(name='Radius', default=0.02)
    friction_prop: bpy.props.FloatProperty(name='Friction', default=0.5)

    def init(self, context):
        super().init(context)
        output_skt = self.outputs.new('hclClothParticlesType', 'Particles')
        output_skt.hide_value = True
        input_skt = self.inputs.new('NodeSocketGeometry', 'Mesh')
        input_skt.hide_value = True
        bone_skt = self.inputs.new('hkaBoneType', 'Bind To Bone')
        bone_skt.hide_value = True
        input_skt1 = self.inputs.new('IndicesOnDomainType', 'Fixed Particle Indices')
        input_skt1.hide_value = True

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        if not self.inputs['Mesh'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Mesh linked")
        
        if not self.inputs['Bind To Bone'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Bone linked")
        
        if not self.inputs['Fixed Particle Indices'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Fixed Particle Indices linked")
        
        parent = utils_node.get_linked_single(self.inputs['Mesh'])
        if not parent.check_valid():
            return utils_node.NodeValidityReturn(False, self, "Invalid Mesh linked")

        parent0 = utils_node.get_linked_single(self.inputs['Bind To Bone'])
        if not parent0.check_valid():
            return utils_node.NodeValidityReturn(False, self, "Invalid Bone linked")
        else:
            bone = utils_node.get_socket_input_single(self,'Bind To Bone')
            if bone['Bone Index'] is None:
                return utils_node.NodeValidityReturn(False, self, "Requires single bone input but given many")
        
        parent1 = utils_node.get_linked_single(self.inputs['Fixed Particle Indices'])
        if parent1.check_valid():
            vertex_indices_input = utils_node.get_socket_input_single(self,'Fixed Particle Indices')
            try:
                domain = vertex_indices_input[1]
                if domain != 'POINT':
                    return utils_node.NodeValidityReturn(False, self, "Fixed Particle Indices must be on POINT domain")
            except:
                return utils_node.NodeValidityReturn(False, self, "Fixed Particle Indices must be on POINT domain")
        
            return utils_node.NodeValidityReturn(True, self)
        
        return utils_node.NodeValidityReturn(False, self, "Invalid Fixed Particle Indices linked")

    def get_socket_output(self, socket_name: str = 'Particles'):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Particles':
            mesh = utils_node.get_socket_input_single(self,'Mesh')
            v_ids = [v.index for v in mesh.data.vertices]

            if self.inputs['Fixed Particle Indices'].is_linked:
                fixed_particle_indices_input = utils_node.get_socket_input_single(self,'Fixed Particle Indices')
                f_ids = fixed_particle_indices_input[0]
            else:
                f_ids = []

            output = {i: {
                'position': tuple(mesh.data.vertices[i].co),
                'normal': tuple(mesh.data.vertices[i].normal),
                'mass': self.mass_prop,
                'radius': self.radius_prop,
                'friction': self.friction_prop,
                'is_fixed': i in f_ids,
            } for i in v_ids}
            print(output)
            return {'particles':output, 'pivot':utils_node.get_socket_input_single(self,'Bind To Bone')['Bone Index'], 'constraints': []}
        return None
        
    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Particle Mass:")
        layout.prop(self, "mass_prop", text="")
        layout.label(text="Particle Radius:")
        layout.prop(self, "radius_prop", text="")
        layout.label(text="Particle Friction:")
        layout.prop(self, "friction_prop", text="")

class hclLinksFromMeshNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Generate constraint links from mesh edges'''

    bl_idname = 'hclLinksFromMesh'
    bl_label = 'Links From Mesh'

    stiffness_prop: bpy.props.FloatProperty(name='Stiffness', default=1.0)

    def init(self, context):
        super().init(context)
        input_skt = self.inputs.new('NodeSocketGeometry', 'Mesh')
        input_skt.hide_value = True
        input_skt1 = self.inputs.new('IndicesOnDomainType', 'Edge Indices')
        input_skt1.display_shape = 'CIRCLE_DOT'
        input_skt1.hide_value = True
        output_skt = self.outputs.new('hclClothLinksType', 'Links')
        output_skt.hide_value = True

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        if not self.inputs['Mesh'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Mesh linked")
        
        if self.inputs['Edge Indices'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Mesh'])
            parent1 = utils_node.get_linked_single(self.inputs['Edge Indices'])
            if parent.check_valid() and parent1.check_valid():
                vertex_indices_input = utils_node.get_socket_input_single(self,'Edge Indices')
                try:
                    domain = vertex_indices_input[1]
                    if domain != 'EDGE':
                        return utils_node.NodeValidityReturn(False, self, "Edge Indices must be on EDGE domain")
                except:
                    return utils_node.NodeValidityReturn(False, self, "Edge Indices must be on EDGE domain")

        return utils_node.NodeValidityReturn(True, self)

    def get_socket_output(self, socket_name: str = 'Links'):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Links':
            mesh = utils_node.get_socket_input_single(self,'Mesh')
            if self.inputs['Edge Indices'].is_linked:
                edge_indices_input = utils_node.get_socket_input_single(self,'Edge Indices')
                e_ids = edge_indices_input[0]
            else:
                e_ids = [i for i in range(len(mesh.data.edges))]
            output = {i: {
                'stiffness': self.stiffness_prop,
                'particleA': mesh.data.edges[i].vertices[0],
                'particleB': mesh.data.edges[i].vertices[1],
            } for i in e_ids}
            return {'links':output}
        return None

    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Link Stiffness:")
        layout.prop(self, "stiffness_prop", text="")

def get_collider_enum_items(self, context):
    cloth_data = utils_node.get_socket_input_single(self,'Cloth Data')
    if cloth_data is None:
        return []
    return [(c['name'], c['name'], c['name']) for c in cloth_data['colliders']]

class DisableCollisionNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Disable particle-collider collision in given cloth data'''

    bl_idname = 'DisableCollision'
    bl_label = 'Disable Collision'

    collider_enum_prop: bpy.props.EnumProperty(name='Collider', items=get_collider_enum_items)

    def init(self, context):
        super().init(context)
        input_skt = self.inputs.new('hclSimClothDataType', 'Cloth Data')
        input_skt.hide_value = True
        particle_ids_skt = self.inputs.new('IndicesOnDomainType', 'Particle Indices')
        output_skt = self.outputs.new('hclSimClothDataType', 'Cloth Data')
        output_skt.hide_value = True

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        if not self.inputs['Cloth Data'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Cloth Data linked")
        
        if not self.inputs['Particle Indices'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Particle Indices linked")
        
        parent = utils_node.get_linked_single(self.inputs['Cloth Data'])
        if not parent.check_valid():
            return utils_node.NodeValidityReturn(False, self, "Invalid Cloth Data linked")
        
        parent1 = utils_node.get_linked_single(self.inputs['Particle Indices'])
        if not parent1.check_valid():
            return utils_node.NodeValidityReturn(False, self, "Invalid Particle Indices linked")
        
        domain = utils_node.get_socket_input_single(self,'Particle Indices')[1]
        if domain != 'POINT':
            return utils_node.NodeValidityReturn(False, self, "Particle Indices must be on POINT domain")
        
        return utils_node.NodeValidityReturn(True, self)

    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Cloth Data':
            cloth_data = utils_node.get_socket_input_single(self,'Cloth Data').copy()
            particle_indices = utils_node.get_socket_input_single(self,'Particle Indices')[0]
            cloth_data['exclude_collision'][self.collider_enum_prop] = particle_indices
            return cloth_data
        
        return None

    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Collider:")
        layout.prop(self, "collider_enum_prop", text="")