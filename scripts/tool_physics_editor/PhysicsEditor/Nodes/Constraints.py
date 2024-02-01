import bpy
from bpy.types import Node, NodeSocket

import PhysicsEditor.Nodes.NodeBase as NodeBase

from PhysicsEditor.Nodes.NodeBase import find_vis_meshes

import PhysicsEditor.Utilities.utils_node as utils_node

import PhysicsEditor.Prefabs.PlaneGenGeoNode as PlaneGenGeoNode

import PhysicsEditor.Prefabs.AttributeVisGeoNode as AttributeVisGeoNode

import PhysicsEditor.Utilities.utils_prefabs as utils_prefabs

import PhysicsEditor.Utilities.utils_geometry as utils_geometry

def update_visibility(self, context):
    objects = find_vis_meshes(self)
    if objects is None:
        utils_node.update_tree_from_node(self, context)
        return
    if isinstance(objects, bpy.types.Object):
        objects.hide_viewport = not self.show_constraint
    else:
        for obj in objects:
            obj.hide_viewport = not self.show_constraint

def update_vis_scale(self, context):
    objects = find_vis_meshes(self)
    if objects is None:
        return
    if isinstance(objects, bpy.types.Object):
        utils_prefabs.SetVisEdgesParameters(objects, vis_scale=self.vis_scale)
    else:
        for obj in objects:
            utils_prefabs.SetVisEdgesParameters(obj, vis_scale=self.vis_scale)

def update_vis_scale_verts(self, context):
    objects = find_vis_meshes(self)
    if objects is None:
        return
    if isinstance(objects, bpy.types.Object):
        utils_prefabs.SetVisVertsParameters(objects, vis_scale=self.vis_scale)
    else:
        for obj in objects:
            utils_prefabs.SetVisVertsParameters(obj, vis_scale=self.vis_scale)

class StandardLinkConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Default cloth simulation links between particles. Constraint on the length of the link'''

    bl_idname = 'StandardLinkConstraint'
    bl_label = 'Standard Link'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=False, update=update_visibility)
    vis_scale: bpy.props.FloatProperty(name='Vis Scale', default=0.02, min=0.001, update=update_vis_scale)

    def init(self, context):
        super().init(context)
        AttributeVisGeoNode.GetGeoNode()
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        links_skt = self.inputs.new('hclClothLinksType', 'Links')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        #print(f'check_valid {self.name}')
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
            box.prop(self, "vis_scale", text="Vis Scale")
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
    
    def draw_vis_mesh(self):
        if not self.show_constraint:
            return None
        links = utils_node.get_socket_input_single(self,'Links')['links']
        e_ids = links.keys()
        e_values = [l['stiffness'] for l in links.values()]

        return utils_prefabs.VisEdgesFromMesh(self.id_data.mesh, e_ids, e_values, self.vis_scale)

class StretchLinkConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Constraint the stretch of links between particles. Useful for cloth with elastic properties'''

    bl_idname = 'StretchLinkConstraint'
    bl_label = 'Stretch Link'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=False, update=update_visibility)
    vis_scale: bpy.props.FloatProperty(name='Vis Scale', default=0.02, min=0.001, update=update_vis_scale)

    def init(self, context):
        super().init(context)
        AttributeVisGeoNode.GetGeoNode()
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        links_skt = self.inputs.new('hclClothLinksType', 'Links')
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')

    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        #print(f'check_valid {self.name}')
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
            box.prop(self, "vis_scale", text="Vis Scale")
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

    def draw_vis_mesh(self):
        if not self.show_constraint:
            return None
        links = utils_node.get_socket_input_single(self,'Links')['links']
        e_ids = links.keys()
        e_values = [l['stiffness'] for l in links.values()]

        return utils_prefabs.VisEdgesFromMesh(self.id_data.mesh, e_ids, e_values, self.vis_scale)
    
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
        #print(f'check_valid {self.name}')
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
    stiffness: bpy.props.FloatProperty(name='Stiffness', min=0, max=1, default=1)
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
        #print(f'check_valid {self.name}')
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
        #print(f'draw_vis_mesh {self.name}')
        if not self.show_constraint:
            return None
        particles = utils_node.get_socket_input_single(self,'Particles')
        p_ids = utils_node.get_socket_input_single(self,'Particle Indices')[0]
        #print(p_ids)
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
    
class LocalRangeConstraintNode(NodeBase.hclPhysicsNodeBase, Node):
    '''Constraint Particles within a range of their initial positions'''

    bl_idname = 'LocalRangeConstraint'
    bl_label = 'Local Range Constraint'

    show_constraint: bpy.props.BoolProperty(name='Show Constraint', default=False, update=update_visibility)
    stiffness: bpy.props.FloatProperty(name='Global Stiffness', min=0, max=1, description="1 means particles will only move within the range, 0 means no constraint at all, 0.3 will allow some flexibility", default=1)
    base_stiffness: bpy.props.FloatProperty(name='Base Stiffness', min=0, max=1, description="1 means particles will only move within the range, 0 means no constraint at all, 0.3 will allow some flexibility", default=0.1)
    effect_range: bpy.props.FloatProperty(name='Minimun Range', min = 0.001, description="Particles within this range will NOT be constrained", default=0.01)
    mode: bpy.props.EnumProperty(name='Mode', items=[('FIXED', 'Fixed', 'Constraint strength for particles is a fixed value'), ('CASCADE', 'Cascade', 'Particles around cloth bones that are closer to non-cloth bones have higher stiffness')], default='CASCADE')
    cascade_falloff_factor: bpy.props.FloatProperty(name='Cascade Falloff Factor', min=0, max=1, description="The falloff factor for cloth bones in cascade mode", default=0.8)
    constraint_normals: bpy.props.BoolProperty(name='Constraint Normal Directions', default=False)
    upper_normal_threshold: bpy.props.FloatProperty(name='Upper Normal Threshold', default=0.5)
    lower_normal_threshold: bpy.props.FloatProperty(name='Lower Normal Threshold', default=-0.5)

    def init(self, context):
        super().init(context)
        AttributeVisGeoNode.GetGeoNode()
        particles_skt = self.inputs.new('hclClothParticlesType', 'Particles')
        input_skt1 = self.inputs.new('IndicesOnDomainType', 'Particle Indices (Default: All)')
        input_skt1.display_shape = 'CIRCLE_DOT'
        particles_out_skt = self.outputs.new('hclClothParticlesType', 'Particles')
        
    def check_valid(self) -> utils_node.NodeValidityReturn:
        valid = super().check_valid()
        if not valid:
            return valid
        #print(f'check_valid {self.name}')
        if self.inputs['Particles'].is_linked:
            parent = utils_node.get_linked_single(self.inputs['Particles'])
            if not parent.check_valid():
                return utils_node.NodeValidityReturn(False, self, "Invalid Particles linked")
            
            parent2 = utils_node.get_linked_single(self.inputs['Particle Indices (Default: All)'])
            if parent2 is not None:
                if not parent2.check_valid():
                    return utils_node.NodeValidityReturn(False, self, "Invalid Particle Indices linked")
                
                domain = utils_node.get_socket_input_single(self,'Particle Indices (Default: All)')[1]
                if domain != 'POINT':
                    return utils_node.NodeValidityReturn(False, self, "Particle Indices must be on POINT domain")
            return utils_node.NodeValidityReturn(True, self)
        return utils_node.NodeValidityReturn(False, self, 'No Particles or Bone linked')

    def draw_buttons(self, context, layout):
        super().draw_buttons(context, layout)
        if self.show_constraint:
            box = layout.box()
            box.scale_y = 0.9
            box.prop(self, "show_constraint", text="Show Constraint")
        else:
            layout.prop(self, "show_constraint", text="Show Constraint")

        if self.mode == "FIXED":
            layout.prop(self, "stiffness", text="Particles Stiffness")
        else:
            layout.prop(self, "base_stiffness", text="Base Stiffness (better around 0.3)")

        layout.prop(self, "effect_range", text="Minimum Range")
        if self.mode == "FIXED":
            layout.prop(self, "mode", text="Mode")
        elif self.mode == "CASCADE":
            box0 = layout.box()
            box0.prop(self, "mode", text="Mode")
            box0.prop(self, "cascade_falloff_factor", text="Cascade Falloff Factor")
        if self.constraint_normals:
            box1 = layout.box()
            box1.scale_y = 0.9
            box1.prop(self, "constraint_normals", text="Constraint Normals")
            box1.prop(self, "upper_normal_threshold", text="Upper Normal Threshold")
            box1.prop(self, "lower_normal_threshold", text="Lower Normal Threshold")
        else:
            layout.prop(self, "constraint_normals", text="Constraint Normals")

    def get_socket_output(self, socket_name: str):
        valid = self.check_valid()
        if not valid:
            return None
        
        if socket_name == 'Particles':
            particles = utils_node.get_socket_input_single(self,'Particles').copy()

            if self.inputs['Particle Indices (Default: All)'].is_linked:
                particle_indices = utils_node.get_socket_input_single(self,'Particle Indices (Default: All)')
            else:
                particle_indices = [list(particles['particles'].keys()), 'POINT']

            particles_list = particle_indices[0]
            if self.mode == 'FIXED':
                stiffness_list = [float(self.stiffness) for _ in particle_indices[0]]
            else:
                stiffness_list = [float(self.base_stiffness) for _ in particle_indices[0]]
            max_distances = [float(self.effect_range) for _ in particle_indices[0]]
            if self.constraint_normals:
                upper_normal_threshold_list = [float(self.upper_normal_threshold) for _ in particle_indices[0]]
                lower_normal_threshold_list = [float(self.lower_normal_threshold) for _ in particle_indices[0]]
            else:
                upper_normal_threshold_list = [340282001837565597733306976381245063168 for _ in particle_indices[0]]
                lower_normal_threshold_list = [-340282001837565597733306976381245063168 for _ in particle_indices[0]]

            if 'constraints' in particles:
                # if there exists a constraint of the same type, pick it
                for constraint in particles['constraints']:
                    if constraint['constraint'] == 'LocalRange':
                        constraint['particles'].extend(particles_list)
                        constraint['max_distances'].extend(max_distances)
                        constraint['upper_normal_thresholds'].extend(upper_normal_threshold_list)
                        constraint['lower_normal_thresholds'].extend(lower_normal_threshold_list)
                        constraint['stiffnesses'].extend(stiffness_list)
                        constraint['modes'].extend([self.mode for _ in particle_indices[0]])
                        constraint['apply_normal_component'] = constraint['apply_normal_component'] or self.constraint_normals
                        return particles

            constraint = {
                'constraint': 'LocalRange',
                'name': self.name,
                'particles': particles_list,
                'max_distances': max_distances,
                'upper_normal_thresholds': upper_normal_threshold_list,
                'lower_normal_thresholds': lower_normal_threshold_list,
                'stiffnesses': stiffness_list,
                'modes': [self.mode for _ in particle_indices[0]],
                'apply_normal_component': self.constraint_normals,
            }
            particles['constraints'].append(constraint)
            return particles
        
    def get_constraint_data(self, _constraint_dict, armature: bpy.types.Object, mesh: bpy.types.Object, cloth_bone_ids: list[int]):
        constraint_dict = _constraint_dict.copy()
        bone_names = [armature.data.bones[i].name for i in cloth_bone_ids]
        bone_centers = {armature.data.bones[i].name: armature.data.bones[i].head_local for i in cloth_bone_ids}
        cascade_trees, bone_factors, bone_tree_ids = utils_geometry.GetClothBoneSubTrees(armature, bone_names, self.cascade_falloff_factor)
        bone_centers = {armature.data.bones[i].name: armature.data.bones[i].head_local for i in bone_tree_ids.keys()}
        query_particle_centers = []
        query_particles_list_idx = []
        for i, modes in enumerate(constraint_dict['modes']):
            if modes == 'CASCADE':
                query_particles_list_idx.append(i)
                query_particle_centers.append(mesh.data.vertices[i].co)

        particle_tree_ids, particle_tree_dists = utils_geometry.AssignPointsToSubTrees(bone_centers, bone_tree_ids, query_particle_centers)

        for p_t_id in range(len(cascade_trees)):
            particle_ids = [i for i in range(len(query_particle_centers)) if particle_tree_ids[i] == p_t_id]
            particle_centers = [query_particle_centers[i] for i in range(len(query_particle_centers)) if particle_tree_ids[i] == p_t_id]
            particle_dists = [particle_tree_dists[i] for i in range(len(query_particle_centers)) if particle_tree_ids[i] == p_t_id]
            subtree_bones = [k for k in bone_tree_ids.keys() if bone_tree_ids[k] == p_t_id]
            subtree_centers = [bone_centers[k] for k in subtree_bones]
            subtree_factors = [bone_factors[k] for k in subtree_bones]
            avg_dist = sum(particle_dists) / len(particle_dists)
            p_factors = utils_geometry.GaussianDistanceWeightingScheme(subtree_centers, subtree_factors, particle_centers, avg_dist * 0.5)

            for p_id, p_factor in zip(particle_ids, p_factors):
                constraint_dict['stiffnesses'][query_particles_list_idx[p_id]] *= p_factor

        return constraint_dict

    def draw_vis_mesh(self):
        if not self.show_constraint:
            return None
        
        particles = utils_node.get_socket_input_single(self,'Particles')
        particle_indices = []
        if self.inputs['Particle Indices (Default: All)'].is_linked:
            particle_indices = utils_node.get_socket_input_single(self,'Particle Indices (Default: All)')[0]
        else:
            particle_indices = particles['particles'].keys()

        stiffness = [float(self.stiffness * 0.02) for _ in particle_indices]

        return utils_prefabs.VisVertsFromMesh(self.id_data.mesh, particle_indices, stiffness)
