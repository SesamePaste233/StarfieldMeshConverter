import bpy
import os
import json
import PhysicsEditor.utils_node as utils_node

import nif_armature
import utils_blender
import utils_common as utils

def get_physics_data(tree: bpy.types.NodeTree):
    if tree.bl_idname != 'hclPhysicsTreeType':
        return None
    
    out_nodes = utils_node.get_all_output_nodes(tree)

    if len(out_nodes) != 1:
        return None
    
    out_node = out_nodes[0]

    physics_data_dict = out_node.get_socket_output()

    if physics_data_dict is None:
        return None

    if physics_data_dict['target'] == 'GenericClothSim':
        particles_dict = physics_data_dict['cloth_data']['particles']
        particles_list = utils.FlattenDictToList(particles_dict, replace_none=True, replace_none_with={})
        physics_data_dict['cloth_data']['particles'] = particles_list

        for constraint in physics_data_dict['cloth_data']['constraints']:
            if 'links' in constraint:
                constraint['links'] = utils.FlattenDictToList(constraint['links'])

        colliders = physics_data_dict['cloth_data']['colliders']
        exclude_collision = physics_data_dict['cloth_data']['exclude_collision']
        for collider in colliders:
            exclude = []
            if collider['name'] in exclude_collision:
                exclude = exclude_collision[collider['name']]
            collider['collision_mask'] = [i for i in range(len(particles_list)) if i not in exclude]

        armature = tree.skeleton

        ref_mesh = tree.mesh

        bone_list = [utils_blender.RevertRenamingBone(bone.name) for bone in armature.data.bones]
        arma_dict = nif_armature.CreateArmatureDict(armature)

        normals,_,_ = utils_blender.GetNormalTangents(ref_mesh.data, with_tangent=False)

        # Copy ref_mesh and triangulate it
        tri_mesh = utils_blender.TriangulateMesh(ref_mesh)

        # Apply transform for tri_mesh
        utils_blender.ApplyTransform(tri_mesh)

        # Collect triangle indices
        tri_indices = []
        for poly in tri_mesh.data.polygons:
            tri_indices.append(poly.vertices[0])
            tri_indices.append(poly.vertices[1])
            tri_indices.append(poly.vertices[2])

        # Collect weights
        utils_blender.RemoveNonBoneVG(tri_mesh, armature)
        weights, vg_names = utils_blender.GatherWeights(tri_mesh, quantize_bytes=1, max_blend_entries=4)

        if len(vg_names) == 0:
            print('Ref mesh must be weighted to hkaSkeleton!')
            return None

        weights, used_indices = utils_blender.RemapBoneIdToSkeleton(weights, vg_names, armature)

        weights, used_indices = utils_blender.RemapBoneIdToSubset(weights, used_indices)

        weights = utils_blender.NormalizeAndQuantizeWeights(weights, quantize_bytes=1)

        driver_data = physics_data_dict['bone_driver_data']
        driver = driver_data['driver']
        driver_node = tree.nodes[driver]
        processed_driver_data = driver_node.gen_driver_data(driver_data, tri_mesh, armature)
        processed_driver_data['local_bone_transforms'] = utils_blender.GethclLocalBoneTransforms(tri_mesh, armature, processed_driver_data['face_indices'], processed_driver_data['cloth_bones'])
        if processed_driver_data is None:
            return None
        else:
            physics_data_dict['bone_driver_data'] = processed_driver_data

        # Delete the copy of the mesh
        utils_blender.RemoveMeshObj(tri_mesh)

        physics_data = {
            'data': physics_data_dict,
            'armature': arma_dict,
            'bone_list': bone_list,
            'mesh_indices': tri_indices,
            #'mesh_normals': normals.tolist(),
            'weights': weights,
            'used_indices': used_indices,
        }

        # Save the physics data to a json file
        physics_data_path = os.path.join(utils.export_mesh_folder_path, 'physics_data.json')
        with open(physics_data_path, 'w') as f:
            json.dump(physics_data, f)

        return physics_data
    
    return None