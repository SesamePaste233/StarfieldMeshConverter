import bpy
import PhysicsEditor.utils_node as utils_node

import utils_blender

global_vis_meshes = {}

def insert_vis_meshes(who: bpy.types.Node, vis_mesh: bpy.types.Object):
    global global_vis_meshes
    if who in global_vis_meshes.keys():
        mesh_data = global_vis_meshes[who]
        if isinstance(mesh_data, list):
            for mesh in mesh_data:
                try:
                    bpy.data.meshes.remove(mesh.data)
                except:
                    pass
        elif isinstance(mesh_data, bpy.types.Object):
            try:
                bpy.data.meshes.remove(mesh_data.data)
            except:
                pass
    global_vis_meshes[who] = vis_mesh
    return vis_mesh

def remove_vis_meshes(who: bpy.types.Node):
    global global_vis_meshes
    if who in global_vis_meshes.keys():
        mesh_data = global_vis_meshes[who]
        if isinstance(mesh_data, list):
            for mesh in mesh_data:
                try:
                    bpy.data.meshes.remove(mesh.data)
                except:
                    pass
        elif isinstance(mesh_data, bpy.types.Object):
            try:
                bpy.data.meshes.remove(mesh_data.data)
            except:
                pass
    global_vis_meshes.pop(who, None)

def clear_vis_meshes():
    global global_vis_meshes
    for node, mesh in global_vis_meshes.items():
        if isinstance(mesh, list):
            for m in mesh:
                try:
                    bpy.data.meshes.remove(m.data)
                except:
                    pass
        elif isinstance(mesh, bpy.types.Object):
            try:
                bpy.data.meshes.remove(mesh.data)
            except:
                pass
    global_vis_meshes.clear()

def find_vis_meshes(who: bpy.types.Node):
    global global_vis_meshes
    if who in global_vis_meshes.keys():
        return global_vis_meshes[who]
    else:
        return None

class hclPhysicsNodeBase:
    @classmethod
    def poll(cls, ntree):
        return ntree.bl_idname == 'hclPhysicsTreeType'
    
    def backward_vis_mesh(self, draw_only_valid = True) -> tuple[list[bpy.types.Object], utils_node.NodeValidityReturn]: 
        print(f"called {self.bl_idname}")

        if draw_only_valid:
            if not self.check_valid():
                self.show_as_invalid()
                print(f"invalid {self.name}")
                rtn = self.backward_check_valid()
                return [], rtn
            else:
                print(f"valid {self.name}")
                self.show_as_valid()

        children = utils_node.get_all_linked_nodes(self)
        meshes = []
        for c in children:
            meshes += c.backward_vis_mesh()[0]

        vis_mesh = self.draw_vis_mesh()        
        if vis_mesh is not None:
            insert_vis_meshes(self, vis_mesh)
            meshes.append(vis_mesh)
        return meshes, utils_node.NodeValidityReturn(True, self)
    
    def backward_check_valid(self) -> utils_node.NodeValidityReturn:
        children = utils_node.get_all_linked_nodes(self)
        children_valid = utils_node.NodeValidityReturn(True, self)
        for c in children:
            child_valid = c.backward_check_valid()
            if not child_valid:
                c.show_as_invalid()
                children_valid = children_valid + child_valid
            else:
                c.show_as_valid()
        
        if not children_valid:
            return children_valid
        
        valid = self.check_valid()
        if not valid:
            self.show_as_invalid()
            return valid
        else:
            self.show_as_valid()
            return utils_node.NodeValidityReturn(True, self)
    
    def show_as_invalid(self):
        self.mute = True
    
    def show_as_valid(self):
        self.mute = False

    # Override this function to draw a mesh for visualization
    def draw_vis_mesh(self):
        return None
    
    # Override this function to check if the node is valid
    def check_valid(self) -> utils_node.NodeValidityReturn:
        return utils_node.NodeValidityReturn(True, self)
    
    # Override this function to get the output of a socket
    def get_socket_output(self, socket_name:str):
        return None

    def update(self):
        pass

    def insert_link(self, link:bpy.types.NodeLink):
        self._before_link_validation(link)
        link.is_valid = utils_node.validate_link(link)
        self._after_link_validation(link)

    def _before_link_validation(self, link: bpy.types.NodeLink):
        '''Override this function to do something before link validation'''
        pass

    def _after_link_validation(self, link: bpy.types.NodeLink):
        '''Override this function to do something after link validation'''
        pass
    
    def draw_buttons(self, context, layout):
        layout.label(text="Name: " + self.name)

class hclSingletonNodeBase:
    @classmethod
    def poll(cls, ntree):
        if ntree.bl_idname != 'hclPhysicsTreeType':
            return False
        for node in ntree.nodes:
            if node.bl_idname == cls.bl_idname:
                cls.report({'ERROR'}, f"Only one {cls.bl_label} node is allowed in a tree")
                return False
        return True
        

class ViewerOutputNodeBase(hclPhysicsNodeBase, bpy.types.Node):
    '''View Physics Data, doesn't output anything'''

    bl_idname = 'ViewerOutputNode'
    bl_label = "Viewer Output"

    def init(self, context):
        viewer_skt = self.inputs.new('VersitileSocket', "Any")
        viewer_skt.link_limit = 8
        viewer_skt.display_shape = 'DIAMOND'

    def check_valid(self) -> utils_node.NodeValidityReturn:
        return utils_node.NodeValidityReturn(True, self)

    def free(self):
        clear_vis_meshes()
        super().free()

    def update(self):
        clear_vis_meshes()
        if self.id_data.vis_meshes_collection is not None:
            utils_blender.remove_collection(self.id_data.vis_meshes_collection)
        meshes, _ = self.backward_vis_mesh()
        if meshes is not None and len(meshes) != 0:
            coll = utils_blender.new_collection('VIS_MESHES')
            utils_blender.move_object_to_collection(meshes, coll)
            self.id_data.vis_meshes_collection = coll
        #print(meshes)


class OutputNodeBase(hclPhysicsNodeBase, bpy.types.Node):
    '''Output Physics Data'''

    bl_idname = 'OutputNode'
    bl_label = "Graph Output"
    bl_width_default = 400

    error_msg: bpy.props.StringProperty(name='Error Message', default='')
        
    def init(self, context):
        self.inputs.new('hclPhysicsDataType', "Physics Data")
    
    def check_valid(self) -> utils_node.NodeValidityReturn:
        if not self.inputs['Physics Data'].is_linked:
            return utils_node.NodeValidityReturn(False, self, "No Physics Data linked")
        
        parent = utils_node.get_linked_single(self.inputs['Physics Data'])
        if parent.check_valid():
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, "Invalid Physics Data linked")

    def free(self):
        clear_vis_meshes()
        super().free()

    def update(self):
        clear_vis_meshes()
        if self.id_data.vis_meshes_collection is not None:
            utils_blender.remove_collection(self.id_data.vis_meshes_collection)
        meshes, rtn = self.backward_vis_mesh()
        if meshes is not None and len(meshes) != 0:
            coll = utils_blender.new_collection('VIS_MESHES')
            utils_blender.move_object_to_collection(meshes, coll)
            self.id_data.vis_meshes_collection = coll
            self.error_msg = ""
        else:
            self.error_msg = rtn.what()
        #print(meshes)
            
    def get_socket_output(self, socket_name: str = ""):
        valid = self.check_valid()
        if not valid:
            return None
        
        build_target = 'UNKNOWN'
        physics_data = utils_node.get_socket_input_single(self,'Physics Data')
        if physics_data['factory'] in ['TwoStatesPhysicsData']:
            build_target = 'GenericClothSim'
        return {'target': build_target, **physics_data}
    
    def draw_buttons(self, context, layout):
        layout.label(text="Error Message:")

        # Create a box to draw the error message
        box = layout.box()

        # Devide error message by lines
        lines = self.error_msg.splitlines()

        # Draw each line
        for line in lines:
            box.label(text=line)

        layout.label(text="Export Folder:")
        layout.prop(context.scene, "physics_file_path", text="")
        layout.operator('object.physics_data_export', text='Export Physics Data', icon='EXPORT')

class SkeletonInputNodeBase(hclPhysicsNodeBase, hclSingletonNodeBase, bpy.types.Node):
    '''Input Skeleton for Particles and Colliders. A graph share the same skeleton.'''

    bl_idname = 'SkeletonInputNode'
    bl_label = "Skeleton Input"

    def init(self, context):
        self.outputs.new('hkaSkeletonType', "hkaSkeleton")
        
    def check_valid(self) -> utils_node.NodeValidityReturn:
        # find skeleton, if not found, return false
        if self.id_data.skeleton is None or self.id_data.skeleton.type != 'ARMATURE' or self.id_data.skeleton.data is None:
            return utils_node.NodeValidityReturn(False, self, "No Skeleton input")
        return utils_node.NodeValidityReturn(True, self)
    
    def get_socket_output(self, socket_name: str = "hkaSkeleton"):
        return self.id_data.skeleton
    
    def draw_buttons(self, context, layout):
        layout.label(text="Armature:")
        layout.prop(self.id_data, "skeleton", text="")

class MeshInputNodeBase(hclPhysicsNodeBase, hclSingletonNodeBase, bpy.types.Node):
    '''Input Mesh for Particles and Constraints. A graph share the same mesh.'''

    bl_idname = 'MeshInputNode'
    bl_label = "Simulation Mesh Input"

    def init(self, context):
        self.outputs.new('NodeSocketGeometry', "Simulation Mesh")
        
    def check_valid(self)-> utils_node.NodeValidityReturn:
        # find mesh, if not found, return false
        if self.id_data.mesh is None or self.id_data.mesh.type != 'MESH' or self.id_data.mesh.data is None:
            return utils_node.NodeValidityReturn(False, self, "No Mesh input")
        return utils_node.NodeValidityReturn(True, self)
    
    def get_socket_output(self, socket_name: str = "Simulation Mesh"):
        return self.id_data.mesh
    
    def draw_buttons(self, context, layout):
        layout.label(text="Simulation Mesh:")
        layout.prop(self.id_data, "mesh", text="")