import bpy
import nif_armature

def NifArmatureTemplate(armature_obj, name_ignore_suffix = True):
	mesh_data_list = []
	nif_dict = nif_armature.CreateArmatureDict(armature_obj)
	return nif_dict

def RootNodeTemplate(parent_obj, mesh_data_list, name_ignore_suffix = True):
	nif_dict = {}
	if name_ignore_suffix:
		p = parent_obj.name.rfind(".")
		if p != -1:
			name = parent_obj.name[:p]
		else:
			name = parent_obj.name
	else:
		name = parent_obj.name
	
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
		nif_dict['children'].append(RootNodeTemplate(child_obj, mesh_data_list, name_ignore_suffix))

	return nif_dict

def SingleClothTemplate(mesh_obj, mesh_data_list):
	nif_dict = {}
	nif_dict['name'] = 'ExportScene'
	nif_dict['matrix'] = [[1 if i == j else 0 for i in range(4)] for j in range(4)]
	nif_dict['scale'] = 1

	nif_dict['sgo_keep'] = 1
	nif_dict['geometry_index'] = 4294967295
	
	nif_dict['children'] = []

	nif_dict['children'].append(RootNodeTemplate(mesh_obj, mesh_data_list))

	return nif_dict
