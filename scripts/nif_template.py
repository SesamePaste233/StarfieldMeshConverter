import bpy

def RootNodeTemplate(parent_obj, mesh_data_list, name_ignore_suffix = True):
	nif_dict = {}
	if name_ignore_suffix:
		name = parent_obj.name[:parent_obj.name.rfind(".")]
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
