import bpy
import nif_armature
import utils_blender

def NifArmatureTemplate(armature_obj, bone_name_list:list, name_ignore_suffix = True):
	mesh_data_list = []
	nif_dict = nif_armature.CreateArmatureDict(armature_obj, bone_name_list)
	return nif_dict

def RootNodeTemplate(parent_obj, mesh_data_list, connect_pts, ignore_suffix = True):
	nif_dict = {}
	
	name = utils_blender.GetBSGeometryName(parent_obj)
	if ignore_suffix:
		p = name.rfind(".")
		if p != -1:
			name = name[:p]
		else:
			name = name

	nif_dict['name'] = name
	nif_dict['matrix'] = [[1 if i == j else 0 for i in range(4)] for j in range(4)]
	T = parent_obj.matrix_world
	for i in range(4):
		for j in range(4):
			nif_dict['matrix'][i][j] = T[i][j]
	nif_dict['scale'] = parent_obj.scale[0]
	
	if parent_obj.type == 'MESH':
		mesh_data_list.append(parent_obj)
		nif_dict['sgo_keep'] = 0
		nif_dict['geometry_index'] = len(mesh_data_list) - 1
	else:
		nif_dict['sgo_keep'] = 1
		nif_dict['geometry_index'] = 4294967295
	
	nif_dict['children'] = []
	for child_obj in parent_obj.children:
		if child_obj.name.startswith("CPA:"):
			cpa_dict = {}
			cpa_dict["child_name"] = child_obj.name[4:]
			cpa_dict["parent_name"] = name
			cpa_dict["translation"] = list(child_obj.location)
			cpa_dict["rot_quat"] = list(child_obj.rotation_quaternion)
			cpa_dict["scale"] = list(child_obj.scale)[0]
			connect_pts.append(cpa_dict)
		else:
			nif_dict['children'].append(RootNodeTemplate(child_obj, mesh_data_list, connect_pts, ignore_suffix))

	return nif_dict

def SingleClothTemplate(mesh_obj, mesh_data_list, connect_pts):
	nif_dict = {}
	nif_dict['name'] = 'ExportScene'
	nif_dict['matrix'] = [[1 if i == j else 0 for i in range(4)] for j in range(4)]
	nif_dict['scale'] = 1

	nif_dict['sgo_keep'] = 1
	nif_dict['geometry_index'] = 4294967295
	
	nif_dict['children'] = [RootNodeTemplate(mesh_obj, mesh_data_list, connect_pts)]

	return nif_dict
