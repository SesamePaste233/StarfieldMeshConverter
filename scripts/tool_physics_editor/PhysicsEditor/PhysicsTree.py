import bpy
from bpy.types import NodeTree, Node, NodeSocket

import nodeitems_utils
from nodeitems_utils import NodeCategory, NodeItem

import addon_utils

import PhysicsEditor.Nodes.NodeBase as NodeBase
import PhysicsEditor.Sockets.SocketTypes as SocketTypes
import PhysicsEditor.Nodes.Simulation as Simulation
import PhysicsEditor.Nodes.Constraints as Constraints
import PhysicsEditor.Nodes.Colliders as Colliders
import PhysicsEditor.Nodes.Skeleton as Skeleton
import PhysicsEditor.Nodes.Selection as Selection
import PhysicsEditor.Nodes.PhysicsData as PhysicsData
import PhysicsEditor.Nodes.Drivers as Drivers

import PhysicsEditor.Utilities.utils_node as utils_node

def update_tree(self, context):
    self.update_tree(context)

class PhysicsTree(NodeTree):
    '''Node tree representation of hclPhysics Data'''
    bl_idname = 'hclPhysicsTreeType'
    bl_label = "New Composition"
    bl_icon = 'NODETREE'

    mesh: bpy.props.PointerProperty(type=bpy.types.Object, poll=lambda self, object: object.type == 'MESH', update=update_tree)
    skeleton: bpy.props.PointerProperty(type=bpy.types.Object, poll=lambda self, object: object.type == 'ARMATURE', update=update_tree)

    vis_meshes_collection: bpy.props.PointerProperty(type=bpy.types.Collection)

    @classmethod
    def poll(cls, context):
        _, enabled = addon_utils.check("tool_export_mesh")
        return enabled and context.scene.sf_physics_editor_version == context.scene.geometry_bridge_version

    def update(self):
        for link in self.links:
            if not link.is_valid:
                link.is_valid = utils_node.validate_link(link)
                if not link.is_valid:
                    self.links.remove(link)

    def update_tree(self, context):
        nodes = utils_node.get_all_output_nodes(self, False, True)
        if len(nodes) > 0:
            links = utils_node.get_linked_links(nodes[0].inputs[0])
            if len(links) > 0:
                output_skt = links[0].from_socket
                input_skt = links[0].to_socket
                self.links.remove(links[0])
                self.links.new(input_skt, output_skt)

    def get_output_nodes(self):
        return utils_node.get_all_output_nodes(self)
                

class MyNodeCategory(NodeCategory):
    @classmethod
    def poll(cls, context):
        return context.space_data.tree_type == 'hclPhysicsTreeType'


node_categories = [
    MyNodeCategory('INPUTS', "Input", items=[
        NodeItem("SkeletonInputNode", label="Armature Input"),
        NodeItem("MeshInputNode", label="Mesh Input"),
    ]),
    MyNodeCategory('OUTPUTS', "Output", items=[
        NodeItem("OutputNode", label="Graph Output"),
        NodeItem("ViewerOutputNode", label="Viewer Output"),
    ]),
    MyNodeCategory('SELECTION', "Select", items=[
        NodeItem("MeshAttrSelection", label="Mesh Attribute Selection"),
        NodeItem("PickBoneFromSkeleton", label="Pick Bone From Skeleton"),
        NodeItem("MatchBoneName", label="Match Bone Name"),
    ]),
    MyNodeCategory('SIMDATA', "Simulation", items=[
        NodeItem("SimClothData", label="Sim Cloth Data"),
        NodeItem("hclParticlesFromMesh", label="Particles From Mesh"),
        NodeItem("hclLinksFromMesh", label="Links From Mesh"),
        NodeItem("DisableCollision", label="Disable Collision"),
    ]),
    MyNodeCategory('CONSTRAINTS', "Constraints", items=[
        NodeItem("StandardLinkConstraint", label="Standard Link"),
        NodeItem("StretchLinkConstraint", label="Stretch Link"),
        #NodeItem("BendStiffnessConstraint", label="Bend Stiffness"),
        NodeItem("BonePlanesConstraint", label="Global Bone Plane Constraint"),
    ]),
    MyNodeCategory('COLLIDERS', "Colliders", items=[
        NodeItem("CapsuleCollider", label="Capsule Collider"),
        NodeItem("TaperedCapsuleCollider", label="Tapered Capsule Collider"),
    ]),
    MyNodeCategory('PHYSICSDATA', "Physics Data", items=[
        NodeItem("TwoStatePhysicsData", label="Two State Physics Data"),
    ]),
    MyNodeCategory('DRIVERS', "Physics Bones", items=[
        NodeItem("SimpleTriangleBoneDriver", label="Simple Triangle Bone Driver"),
    ]),
]

classes = [
    PhysicsTree,
    # Sockets
    SocketTypes.hclConstraintSocket,
    SocketTypes.hclMultiConstraintSocket,
    SocketTypes.hclPhysicsDataSocket,
    SocketTypes.hclSimClothDataSocket,
    SocketTypes.hkaSkeletonSocket,
    SocketTypes.hclColliderSocket,
    SocketTypes.hclMultiColliderSocket,
    SocketTypes.VersitileSocket,
    SocketTypes.hclClothParticlesSocket,
    SocketTypes.hclConstraintLinksSocket,
    SocketTypes.IndicesOnDomainSocket,
    SocketTypes.hkaBoneSocket,
    SocketTypes.SimulationBonesSocket,
    # Nodes
    NodeBase.ViewerOutputNodeBase,
    NodeBase.OutputNodeBase,
    NodeBase.SkeletonInputNodeBase,
    NodeBase.MeshInputNodeBase,
    Simulation.SimClothDataNode,
    Constraints.StandardLinkConstraintNode,
    Constraints.StretchLinkConstraintNode,
    Constraints.BendStiffnessConstraintNode,
    Constraints.BonePlanesConstraintNode,
    Colliders.CapsuleColliderNode,
    Colliders.TaperedCapsuleColliderNode,
    Skeleton.PickBoneFromSkeletonNode,
    Selection.MeshAttrSelectionNode,
    Simulation.hclLinksFromMeshNode,
    Simulation.hclParticlesFromMeshNode,
    Simulation.DisableCollisionNode,
    PhysicsData.TwoStatePhysicsDataNode,
    Skeleton.MatchBoneNameNode,
    Drivers.SimpleTriangleBoneDriverNode,
]


def register():
    from bpy.utils import register_class
    for cls in classes:
        register_class(cls)

    nodeitems_utils.register_node_categories('HCL_NODES', node_categories)

def unregister():
    nodeitems_utils.unregister_node_categories('HCL_NODES')

    from bpy.utils import unregister_class
    for cls in reversed(classes):
        unregister_class(cls)
