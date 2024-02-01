from typing import Any
import bpy

class NodeValidityReturn:
    def __init__(self, valid:bool, who:bpy.types.Node, message:str = ''):
        self.valid = valid
        if who is not None:
            self.msg = [(who, message)]

    def __bool__(self):
        return self.valid
    
    def __str__(self):
        return self.what()
    
    def __repr__(self):
        return self.what()
    
    def __eq__(self, other):
        if isinstance(other, bool):
            return self.valid == other
        elif isinstance(other, NodeValidityReturn):
            return self.valid == other.valid
        else:
            return False
        
    def __add__(self, other):
        if isinstance(other, NodeValidityReturn):
            new_rtn = NodeValidityReturn(self.valid and other.valid, None)
            new_rtn.msg = self.msg + other.msg
            return new_rtn
        else:
            raise TypeError(f"unsupported operand type(s) for +: 'NodeValidityReturn' and '{type(other).__name__}'")
        
    def what(self):
        if self.valid:
            return 'Valid'
        msg = ''
        has_mesh_input_node = False
        has_skeleton_input_node = False
        for who, what in self.msg:
            if len(what) > 0:
                if who.bl_idname == 'MeshInputNode':
                    if not has_mesh_input_node:
                        has_mesh_input_node = True
                        msg += 'Mesh Input: ' + what + '\n'
                elif who.bl_idname == 'SkeletonInputNode':
                    if not has_skeleton_input_node:
                        has_skeleton_input_node = True
                        msg += 'Skeleton Input: ' + what + '\n'
                else:
                    msg += f'{who.name}: {what}\n'
        return msg


def validate_link(link:bpy.types.NodeLink) -> bool:
    from_socket = link.from_socket
    to_socket = link.to_socket
    if not hasattr(to_socket, 'is_allowed'):
        if from_socket.bl_idname == to_socket.bl_idname:
            return True
        else:
            return False
    if to_socket.is_allowed(from_socket):
        return True
    else:
        return False
    
    return False

def is_reroute_node(node:bpy.types.Node) -> bool:
    return node.bl_idname == "NodeReroute"

def get_linked_links(socket:bpy.types.NodeSocket) -> list[bpy.types.NodeLink]:
    linked_links = []
    if not socket.is_linked:
        return linked_links

    for link in socket.links:
        if link.is_valid:
            node = link.from_node
            while is_reroute_node(node):
                node = link.from_node
                if node.inputs[0].is_linked:
                    link = node.inputs[0].links[0]
                    if not link.is_valid:
                        node = None
                    node = link.from_node
                else:
                    node = None
            if node is not None:
                linked_links.append(link)

    return linked_links

def get_linked(socket:bpy.types.NodeSocket, exclude_muted = False) -> list[bpy.types.Node]:
    linked_nodes = []
    if not socket.is_linked:
        return linked_nodes

    for link in socket.links:
        #if link.is_valid:
        node = link.from_node
        while is_reroute_node(node):
            if exclude_muted and node.mute:
                node = None
                break
            node = link.from_node
            if node.inputs[0].is_linked:
                link = node.inputs[0].links[0]
                if not link.is_valid:
                    node = None
                node = link.from_node
            else:
                node = None
        if node is not None:
            if exclude_muted and node.mute:
                continue
            linked_nodes.append(node)

    return linked_nodes

def get_linked_single(socket:bpy.types.NodeSocket) -> bpy.types.Node:
    linked_nodes = get_linked(socket)
    if len(linked_nodes) > 0:
        return linked_nodes[0]
    else:
        return None

def get_all_linked_nodes(node:bpy.types.Node) -> list[bpy.types.Node]:
    linked_nodes = []
    for socket in node.inputs:
        nodes = get_linked(socket)
        linked_nodes.extend(nodes)
    return linked_nodes

def get_socket_input(node:bpy.types.Node, socket_name:str, exclude_muted = False) -> list:
    values = []
    if socket_name not in node.inputs:
        return []
    
    socket = node.inputs[socket_name]
    if not socket.is_linked:
        return values

    for link in socket.links:
        if link.is_valid:
            node = link.from_node
            while is_reroute_node(node):
                if exclude_muted and node.mute:
                    node = None
                    break
                node = link.from_node
                if node.inputs[0].is_linked:
                    link = node.inputs[0].links[0]
                    if not link.is_valid:
                        node = None
                    node = link.from_node
                else:
                    node = None
            if node is not None:
                if exclude_muted and node.mute:
                    continue
                if hasattr(node, 'get_socket_output'):
                    values.append(node.get_socket_output(link.from_socket.name))

    return values

def get_socket_input_single(node:bpy.types.Node, socket_name:str):
    values = get_socket_input(node, socket_name)
    if len(values) > 0:
        return values[0]
    else:
        return None
    
def get_all_output_nodes(tree:bpy.types.NodeTree, valid_only = True, linked_only = True) -> list[bpy.types.Node]:
    output_nodes = []
    for node in tree.nodes:
        if node.bl_idname == 'OutputNode':
            if linked_only and not node.inputs[0].is_linked:
                continue
            if valid_only and hasattr(node, "check_valid") and not node.check_valid():
                continue
            output_nodes.append(node)
    return output_nodes

def get_all_physics_trees() -> list[bpy.types.NodeTree]:
    trees = []
    for tree in bpy.data.node_groups:
        if tree.bl_idname == 'hclPhysicsTreeType':
            trees.append(tree)
    return trees

def update_tree_from_node_safe(node, context):
    if node is not None and isinstance(node, bpy.types.Node) and isinstance(node.id_data, bpy.types.NodeTree) and hasattr(node.id_data, 'update_tree'):
        node.id_data.update_tree(context)

def update_tree_from_node(node, context):
    node.id_data.update_tree(context)

def remove_socket_output(from_node: bpy.types.Node, from_socket: bpy.types.NodeSocket):
    tree = from_node.id_data
    for link in tree.links:
        if link.from_node == from_node and link.from_socket == from_socket:
            tree.links.remove(link)