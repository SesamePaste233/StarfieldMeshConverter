import bpy

import PhysicsEditor.Utilities.utils_node as utils_node

# Custom socket type
class hclNodeSocketBase():
    # Description string
    '''Custom node socket type'''
    # Label for nice name display
    bl_label = ""

    color = (0.4, 0.4, 0.4, 1)

    @classmethod
    def is_allowed(cls, socket):
        return cls.bl_idname == socket.bl_idname
    
    # Optional function for drawing the socket input value
    def draw(self, context, layout, node, text):
        layout.label(text=text)

    # Socket color
    def draw_color(self, context, node):
        return self.color

class hclConstraintSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value = None
    bl_idname = 'hclConstraintType'
    bl_label = 'Constraint'
    color = (0.6, 0.4, 0.2, 1)

class hclMultiConstraintSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value = None
    bl_idname = 'hclMultiConstraintType'
    bl_label = 'Multi Constraints'
    color = (0.6, 0.4, 0.2, 1)

    @classmethod
    def is_allowed(cls, socket):
        return socket.bl_idname == 'hclConstraintType'
    
    def draw(self, context, layout, node, text):
        layout.label(text=text)

class hclPhysicsDataSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value = None
    bl_idname = 'hclPhysicsDataType'
    bl_label = 'Physics Data'
    color = (0.2, 0.4, 0.6, 1)

class hclSimClothDataSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value = None
    bl_idname = 'hclSimClothDataType'
    bl_label = 'Sim Cloth Data'
    color = (0.3, 0.2, 0.7, 1)

class hclAnimClothDataSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value = None
    bl_idname = 'hclAnimClothDataType'
    bl_label = 'Anim Cloth Data'
    color = (0.3, 0.2, 0.7, 1)

class hkaSkeletonSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value: bpy.props.PointerProperty(type=bpy.types.Armature)
    bl_idname = 'hkaSkeletonType'
    bl_label = 'Skeleton'
    color = (0.2, 0.6, 0.4, 1)

class hclColliderSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value = None
    bl_idname = 'hclColliderType'
    bl_label = 'Collider'
    color = (0.6, 0.2, 0.4, 1)

class hclMultiColliderSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    bl_idname = 'hclMultiColliderType'
    bl_label = 'Multi Colliders'
    color = (0.6, 0.2, 0.4, 1)

    @classmethod
    def is_allowed(cls, socket):
        return socket.bl_idname == 'hclColliderType'
    
    def draw(self, context, layout, node, text):
        layout.label(text=text)

class IndicesOnDomainSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value: tuple = ([], 'DOMAIN')
    bl_idname = 'IndicesOnDomainType'
    bl_label = 'Indices On Domain'
    color = (0.5, 0.8, 0.5, 1)

class hclClothParticlesSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value: list[int] = []
    bl_idname = 'hclClothParticlesType'
    bl_label = 'Cloth Particles'
    color = (0.5, 0.5, 0.8, 1)

class hclConstraintLinksSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value: tuple[list[int], list[int]] = []
    bl_idname = 'hclClothLinksType'
    bl_label = 'Constraint Link'
    color = (0.5, 0.7, 0.8, 1)

class hkaBoneSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value = {
        'Armature': None,
        'Bone Index': None,
        'Bone Indices': [],
    }
    bl_idname = 'hkaBoneType'
    bl_label = 'Bone'
    color = (0.7, 0.5, 0.8, 1)

class VersitileSocket(bpy.types.NodeSocket):
    default_value = None
    bl_idname = 'VersitileSocket'
    bl_label = 'Versitile Socket'
    color = (0.6, 0.6, 0.6, 1)
    default_value = None

    @classmethod
    def is_allowed(cls, socket):
        return True

    def draw(self, context, layout, node, text):
        layout.label(text=text)

    def draw_color(self, context, node):
        return self.color
    
class SimulationBonesSocket(bpy.types.NodeSocket, hclNodeSocketBase):
    default_value: list[int] = []
    bl_idname = 'SimulationBonesType'
    bl_label = 'Simulation Bones'
    color = (0.8, 0.5, 0.6, 1)