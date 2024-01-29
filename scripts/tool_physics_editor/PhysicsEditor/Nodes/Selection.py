import bpy
import bmesh
from bpy.types import Node, NodeLink, NodeSocket

import PhysicsEditor.Nodes.NodeBase as NodeBase

import PhysicsEditor.Utilities.utils_node as utils_node

def get_attr_enum_items(self, context):
    if self.inputs['Mesh'].is_linked:
        parent = utils_node.get_linked_single(self.inputs['Mesh'])
        if parent.check_valid():
            items = []
            mesh = utils_node.get_socket_input_single(self,'Mesh')
            for attr in mesh.data.attributes:
                if attr.domain == self.domain_enum_prop and attr.data_type == self.type_enum_prop:
                    items.append((attr.name, attr.name, attr.name))

            if self.type_enum_prop == 'FLOAT' and self.domain_enum_prop == 'POINT':
                for vg in mesh.vertex_groups:
                    items.append((vg.name, vg.name, vg.name))
            return items
    return []

valid_operators = {
    'FLOAT': ('Higher or equal to','Lower or equal to','Higher than','Lower than','Equal to','Not equal to',),
    'INT': ('Higher or equal to','Lower or equal to','Higher than','Lower than','Equal to','Not equal to',),
    'BOOLEAN': ('Is','Not')
}

def get_operator_enum_items(self, context):
    if self.type_enum_prop in valid_operators.keys():
        return zip(valid_operators[self.type_enum_prop], valid_operators[self.type_enum_prop], valid_operators[self.type_enum_prop])
    return []

def update_type_enum(self, context):
    if self.type_enum_prop == 'BOOLEAN':
        self.operator_enum_prop = 'Is'

def update_domain_enum(self, context):
    utils_node.remove_socket_output(self, self.outputs['Indices On Domain'])

class MeshAttrSelectionNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Select Mesh elements by Attributes'''

    bl_idname = 'MeshAttrSelection'
    bl_label = 'Mesh Attribute Selection'

    domain_enum_prop: bpy.props.EnumProperty(name='Domain', items=[('POINT', 'Point', 'Point'), ('EDGE', 'Edge', 'Edge'), ('FACE', 'Face', 'Face')], update = update_domain_enum)
    type_enum_prop: bpy.props.EnumProperty(name='Type', items=[('FLOAT', 'Float', 'Float')], update=update_type_enum)
    attr_enum_prop: bpy.props.EnumProperty(name='Attribute', items=get_attr_enum_items)
    operator_enum_prop: bpy.props.EnumProperty(name='Operator', items=get_operator_enum_items)
    float_operand_prop: bpy.props.FloatProperty(name='Operand', default=0)
    int_operand_prop: bpy.props.IntProperty(name='Operand', default=0)
    bool_operand_prop: bpy.props.BoolProperty(name='Operand', default=True)

    def init(self, context):
        super().init(context)
        mesh_skt = self.inputs.new('NodeSocketGeometry', 'Mesh')
        mesh_skt.show_expanded = True
        mesh_skt.hide_value = True
        elem_indices_skt = self.outputs.new('IndicesOnDomainType', 'Indices On Domain')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        if self.inputs['Mesh'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Mesh'])
            if parent.check_valid():
                mesh = utils_node.get_socket_input_single(self,'Mesh')
                if self.attr_enum_prop in mesh.data.attributes or self.attr_enum_prop in mesh.vertex_groups:
                    return utils_node.NodeValidityReturn(True, self)
                return utils_node.NodeValidityReturn(False, self, f"Cannot find attribute \'{self.attr_enum_prop}\' in mesh \'{mesh.name}\'")
            else:
                return utils_node.NodeValidityReturn(False, self, "Invalid Mesh linked")
        return utils_node.NodeValidityReturn(False, self, "No Mesh linked")

    def get_socket_output(self, socket_name: str = "Indices On Domain"):
        valid = self.check_valid()
        if not valid:
            return [], self.domain_enum_prop
        
        if socket_name == 'Indices On Domain':
            mesh = utils_node.get_socket_input_single(self,'Mesh')
            if self.attr_enum_prop not in mesh.data.attributes and self.type_enum_prop == 'FLOAT' and self.domain_enum_prop == 'POINT':
                vg = mesh.vertex_groups[self.attr_enum_prop]
                if self.operator_enum_prop == 'Higher than':
                    return [i for i in range(len(mesh.data.vertices)) if vg.weight(i) > self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Lower than':
                    return [i for i in range(len(mesh.data.vertices)) if vg.weight(i) < self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Equal to':
                    return [i for i in range(len(mesh.data.vertices)) if vg.weight(i) == self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Not equal to':
                    return [i for i in range(len(mesh.data.vertices)) if vg.weight(i) != self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Higher or equal to':
                    return [i for i in range(len(mesh.data.vertices)) if vg.weight(i) >= self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Lower or equal to':
                    return [i for i in range(len(mesh.data.vertices)) if vg.weight(i) <= self.float_operand_prop], self.domain_enum_prop
                
            attr = mesh.data.attributes[self.attr_enum_prop]
            bm = bmesh.new()
            bm.from_mesh(mesh.data)
            if self.type_enum_prop == 'FLOAT':
                if self.domain_enum_prop == 'POINT':
                    layer = bm.verts.layers.float.get(attr.name)
                elif self.domain_enum_prop == 'EDGE':
                    layer = bm.edges.layers.float.get(attr.name)
                elif self.domain_enum_prop == 'FACE':
                    layer = bm.faces.layers.float.get(attr.name)

                print(bm.verts.layers.float)
                if self.operator_enum_prop == 'Higher than':
                    if self.domain_enum_prop == 'POINT':
                        return [v.index for v in bm.verts if v[layer] > self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'EDGE':
                        return [e.index for e in bm.edges if e[layer] > self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'FACE':
                        return [f.index for f in bm.faces if f[layer] > self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Lower than':
                    if self.domain_enum_prop == 'POINT':
                        return [v.index for v in bm.verts if v[layer] < self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'EDGE':
                        return [e.index for e in bm.edges if e[layer] < self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'FACE':
                        return [f.index for f in bm.faces if f[layer] < self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Equal to':
                    if self.domain_enum_prop == 'POINT':
                        return [v.index for v in bm.verts if v[layer] == self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'EDGE':
                        return [e.index for e in bm.edges if e[layer] == self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'FACE':
                        return [f.index for f in bm.faces if f[layer] == self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Not equal to':
                    if self.domain_enum_prop == 'POINT':
                        return [v.index for v in bm.verts if v[layer] != self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'EDGE':
                        return [e.index for e in bm.edges if e[layer] != self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'FACE':
                        return [f.index for f in bm.faces if f[layer] != self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Higher or equal to':
                    if self.domain_enum_prop == 'POINT':
                        return [v.index for v in bm.verts if v[layer] >= self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'EDGE':
                        return [e.index for e in bm.edges if e[layer] >= self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'FACE':
                        return [f.index for f in bm.faces if f[layer] >= self.float_operand_prop], self.domain_enum_prop
                elif self.operator_enum_prop == 'Lower or equal to':
                    if self.domain_enum_prop == 'POINT':
                        return [v.index for v in bm.verts if v[layer] <= self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'EDGE':
                        return [e.index for e in bm.edges if e[layer] <= self.float_operand_prop], self.domain_enum_prop
                    elif self.domain_enum_prop == 'FACE':
                        return [f.index for f in bm.faces if f[layer] <= self.float_operand_prop], self.domain_enum_prop
                    
        
        return [], self.domain_enum_prop
    
    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        layout.label(text="Domain:")
        layout.prop(self, "domain_enum_prop", text="")
        layout.label(text="Type:")
        layout.prop(self, "type_enum_prop", text="")
        layout.label(text="Attribute:")
        layout.prop(self, "attr_enum_prop", text="")
        layout.label(text="Operator:")
        layout.prop(self, "operator_enum_prop", text="")
        layout.label(text="Operand:")
        if self.type_enum_prop == 'FLOAT':
            layout.prop(self, "float_operand_prop", text="")
        elif self.type_enum_prop == 'INT':
            layout.prop(self, "int_operand_prop", text="")
        elif self.type_enum_prop == 'BOOLEAN':
            layout.prop(self, "bool_operand_prop", text="")

class ConcatenateIndicesNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Concatenate Indices'''

    bl_idname = 'ConcatenateIndices'
    bl_label = 'Concatenate Indices'

    def init(self, context):
        super().init(context)
        self.inputs.new('IndicesOnDomainType', 'Indices 1')
        self.inputs.new('IndicesOnDomainType', 'Indices 2')
        self.outputs.new('IndicesOnDomainType', 'Indices On Domain')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        print(f'check_valid {self.name}')
        if self.inputs['Indices 1'].is_linked and self.inputs['Indices 2'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Indices 1'])
            parent1 = utils_node.get_linked_single(self.inputs['Indices 2'])
            if parent.check_valid() and parent1.check_valid():
                domain = utils_node.get_socket_input_single(self,'Indices 1')[1]
                domain1 = utils_node.get_socket_input_single(self,'Indices 2')[1]
                if domain == domain1:
                    return utils_node.NodeValidityReturn(True, self)
                return utils_node.NodeValidityReturn(False, self, "Indices domains are not the same")
            else:
                return utils_node.NodeValidityReturn(False, self, "Invalid Indices linked")
        return utils_node.NodeValidityReturn(False, self, "No Indices linked")

    def get_socket_output(self, socket_name: str = "Indices On Domain"):
        valid = self.check_valid()
        if not valid:
            return [], None
        
        if socket_name == 'Indices On Domain':
            indices1 = utils_node.get_socket_input_single(self,'Indices 1')[0]
            indices2 = utils_node.get_socket_input_single(self,'Indices 2')[0]
            return indices1 + indices2, utils_node.get_socket_input_single(self,'Indices 1')[1]
        return [], 'POINT'