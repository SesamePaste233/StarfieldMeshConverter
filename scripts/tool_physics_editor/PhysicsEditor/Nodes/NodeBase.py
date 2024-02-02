import bpy
from version import __plugin_version__, make_version, Version
from PhysicsEditor.NodeVersions import get_node_script_version

import PhysicsEditor.Utilities.utils_node as utils_node

global_vis_meshes = {}

global_initialized = set()

def move_object_to_collection(objs, coll):
	for obj in objs:
		if obj != None:
			if isinstance(obj, bpy.types.Object):
				old_colls = [c for c in obj.users_collection]
				for c in old_colls:
					if c != None:
						c.objects.unlink(obj)
				coll.objects.link(obj)
			elif isinstance(obj, list):
				for o in obj:
					old_colls = [c for c in o.users_collection]
					for c in old_colls:
						if c != None:
							c.objects.unlink(o)
					coll.objects.link(o)

def new_collection(name, do_link = True):
	coll = bpy.data.collections.new(name)
	if do_link:
		bpy.context.scene.collection.children.link(coll)
	return coll

def remove_collection(coll, hierarchy = True):
	if hierarchy:
		for obj in coll.objects:
			bpy.data.objects.remove(obj, do_unlink=True)

	bpy.data.collections.remove(coll)

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
    try: 
        for node, mesh in global_vis_meshes.items():
            if mesh == None:
                continue
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
    instance_version: bpy.props.StringProperty(name='Version', default=Version((1,0,0)).as_str(), options={'HIDDEN'})

    @classmethod
    def poll(cls, ntree):
        return ntree.bl_idname == 'hclPhysicsTreeType'
    
    # Called on init for every node
    def update_version(self):
        self.instance_version = get_node_script_version(self.bl_idname).as_str()

    def init(self, context):
        self.update_version()

    def backward_vis_mesh(self, draw_only_valid = True) -> tuple[list[bpy.types.Object], utils_node.NodeValidityReturn]: 
        #print(f"called {self.bl_idname}")

        if draw_only_valid:
            if not self.check_valid():
                self.show_as_invalid()
                #print(f"invalid {self.name}")
                rtn = self.backward_check_valid()
                return [], rtn
            else:
                #print(f"valid {self.name}")
                self.show_as_valid()

        if self.id_data not in global_initialized:
            global_initialized.add(self.id_data)
            return [], utils_node.NodeValidityReturn(True, self)

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
        if make_version(self.instance_version) != get_node_script_version(self.bl_idname):
            return utils_node.NodeValidityReturn(False, self, "Version mismatch! Delete and recreate this node.")
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
        super().init(context)
        viewer_skt = self.inputs.new('VersitileSocket', "Any")
        viewer_skt.link_limit = 8
        viewer_skt.display_shape = 'DIAMOND'

    def check_valid(self) -> utils_node.NodeValidityReturn:
        return super().check_valid()

    def free(self):
        clear_vis_meshes()
        super().free()

    def update(self):
        clear_vis_meshes()
        if self.id_data.vis_meshes_collection is not None:
            remove_collection(self.id_data.vis_meshes_collection)
        meshes, _ = self.backward_vis_mesh()
        if meshes is not None and len(meshes) != 0:
            coll = new_collection('VIS_MESHES')
            move_object_to_collection(meshes, coll)
            self.id_data.vis_meshes_collection = coll
        #print(meshes)


class OutputNodeBase(hclPhysicsNodeBase, bpy.types.Node):
    '''Output Physics Data'''

    bl_idname = 'OutputNode'
    bl_label = "Graph Output"
    bl_width_default = 400

    error_msg: bpy.props.StringProperty(name='Error Message', default='')
        
    def init(self, context):
        super().init(context)
        self.inputs.new('hclPhysicsDataType', "Physics Data")
    
    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid

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
            remove_collection(self.id_data.vis_meshes_collection)
        meshes, rtn = self.backward_vis_mesh()
        if meshes is not None and len(meshes) != 0:
            coll = new_collection('VIS_MESHES')
            move_object_to_collection(meshes, coll)
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

        #layout.label(text="Export Folder:")
        #layout.prop(context.scene, "physics_file_path", text="")
        #layout.operator('object.physics_data_export', text='To Portable File', icon='EXPORT')

class SkeletonInputNodeBase(hclPhysicsNodeBase, hclSingletonNodeBase, bpy.types.Node):
    '''Input Skeleton for Particles and Colliders. A graph share the same skeleton.'''

    bl_idname = 'SkeletonInputNode'
    bl_label = "Skeleton Input"

    def init(self, context):
        super().init(context)
        self.outputs.new('hkaSkeletonType', "hkaSkeleton")
        
    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
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
        super().init(context)
        self.outputs.new('NodeSocketGeometry', "Simulation Mesh")
        
    def check_valid(self)-> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        # find mesh, if not found, return false
        if self.id_data.mesh is None or self.id_data.mesh.type != 'MESH' or self.id_data.mesh.data is None:
            return utils_node.NodeValidityReturn(False, self, "No Mesh input")
        elif len(self.id_data.mesh.data.polygons) == 0:
            return utils_node.NodeValidityReturn(False, self, f"Mesh \"{self.id_data.mesh.name}\" has no faces")
        return utils_node.NodeValidityReturn(True, self)
    
    def get_socket_output(self, socket_name: str = "Simulation Mesh"):
        return self.id_data.mesh
    
    def draw_buttons(self, context, layout):
        layout.label(text="Simulation Mesh:")
        layout.prop(self.id_data, "mesh", text="")