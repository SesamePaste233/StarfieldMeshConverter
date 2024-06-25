import bpy
import bmesh
import os
import numpy as np
import mathutils

import utils_math
import utils_common as utils
from nif_armature import BoneAxisCorrectionRevert
import CapsuleGenGeoNode as capsule_gen
import PlaneGenGeoNode as plane_gen

read_only_marker = '[READONLY]'
mix_normal = False

bone_rename_dict = {}

def UtilsFolderPath():
	utils_path = _update_path(os.path.dirname(__file__))
	return utils_path

def PluginAssetsFolderPath():
	utils_path = UtilsFolderPath()
	return os.path.join(utils_path, 'Assets')

def DefaultResultFolderPath():
	utils_path = UtilsFolderPath()
	result_path = os.path.join(utils_path, 'Results')
	
	if not os.path.isdir(result_path):
		os.makedirs(result_path)
    
	return result_path

def TempFolderPath():
	utils_path = UtilsFolderPath()
	temp_path = os.path.join(utils_path, 'Temp')
	
	if not os.path.isdir(temp_path):
		os.makedirs(temp_path)
		
	return temp_path

def ThirdPartyFolderPath():
	utils_path = UtilsFolderPath()
	third_party_path = os.path.join(utils_path, '3rdParty')
	
	if not os.path.isdir(third_party_path):
		os.makedirs(third_party_path)
		
	return third_party_path

def open_folder(initial_directory):

	# Set the window manager to the current context
	wm = bpy.context.window_manager

	# Call the file browser operator
	bpy.ops.wm.path_open(filepath=initial_directory)
						 
def _update_path(utils_p):
	utils_path = bpy.path.abspath(utils_p)
	return utils_path

def SetSelectObjects(objs):
	original_selected = bpy.context.selected_objects
	bpy.ops.object.select_all(action='DESELECT')
	for obj in objs:
		if obj != None:
			obj.select_set(state=True)
	return original_selected

def GetActiveObject():
	return bpy.context.active_object

def SetActiveObject(obj, deselect_all = False):
	original_active = GetActiveObject()
	if deselect_all:
		bpy.ops.object.select_all(action='DESELECT')
	if obj != None:
		obj.select_set(True)
	bpy.context.view_layer.objects.active = obj
	return original_active

def GetSharpGroups(selected_obj):
	sharp_edge_vertices = []
	# Ensure we are in Edit Mode
	if selected_obj.mode != 'EDIT':
		bpy.ops.object.mode_set(mode='EDIT')

	# Deselect all
	bpy.ops.mesh.select_all(action='DESELECT')

	_obj = bpy.context.edit_object
	_me = _obj.data

	_bm = bmesh.from_edit_mesh(_me)
	for e in _bm.edges:
		if not e.smooth:
			e.select = True
	
	bmesh.update_edit_mesh(_me)

	# Switch to Vertex Select Mode
	bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='VERT')

	# Switch back to Object Mode
	bpy.ops.object.mode_set(mode='OBJECT')

	# Iterate through selected vertices and add their indices to the list
	for vertex in selected_obj.data.vertices:
		if vertex.select:
			sharp_edge_vertices.append(vertex.index)

	return sharp_edge_vertices

def TriangulateMesh(mesh_obj:bpy.types.Object, make_copy = True) -> bpy.types.Object:
	if make_copy:
		mesh_obj = mesh_obj.copy()
		mesh_obj.data = mesh_obj.data.copy()
		bpy.context.collection.objects.link(mesh_obj)
		bpy.context.view_layer.objects.active = mesh_obj

	# Use bmesh to triangulate the mesh
	bm = bmesh.new()
	bm.from_mesh(mesh_obj.data)
	bmesh.ops.triangulate(bm, faces=bm.faces)
	bm.to_mesh(mesh_obj.data)
	bm.free()

	return mesh_obj

def ApplyTransform(mesh_obj:bpy.types.Object):
	prev_active = SetActiveObject(mesh_obj)
	bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)
	SetActiveObject(prev_active)

def PreprocessAndProxy(old_obj, use_world_origin, convert_to_mesh = True, do_triangulation = True):
	if old_obj and old_obj.type == 'MESH':
		
		if old_obj.data.uv_layers == None or len(old_obj.data.uv_layers) == 0 or old_obj.data.uv_layers.active == None:
			print(f"Your model has no active UV map! Please create one before exporting.")
			return None, None

		if old_obj.data.shape_keys != None and old_obj.data.shape_keys.key_blocks != None:
			key_blocks = old_obj.data.shape_keys.key_blocks
			if key_blocks[0].name == 'Basis':
				keys = old_obj.data.shape_keys.key_blocks.keys()
				shape_key_index = keys.index('Basis')
				old_obj.active_shape_key_index = shape_key_index

		new_obj = old_obj.copy()
		new_obj.data = old_obj.data.copy()
		new_obj.animation_data_clear()
		bpy.context.collection.objects.link(new_obj)
		bpy.context.view_layer.objects.active = new_obj

		SetActiveObject(new_obj, True)
		if convert_to_mesh:
			bpy.ops.object.convert(target='MESH')

		new_obj.data.validate()

		# Mesh clean up
		if new_obj.mode != 'EDIT':
			bpy.ops.object.mode_set(mode='EDIT')

		# Select all
		bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='VERT')
		bpy.ops.mesh.select_all(action='SELECT')
		bpy.ops.mesh.delete_loose()
		bpy.ops.mesh.select_all(action='DESELECT')

		bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='EDGE')
		
		# Select all edges
		bpy.ops.mesh.select_all(action='SELECT')
		
		# Switch to Edge Select mode in UV Editor
		bpy.ops.uv.select_all(action='SELECT')
		
		bpy.ops.uv.seams_from_islands()
		
		bpy.ops.object.mode_set(mode='OBJECT')

		base_obj = new_obj.copy()
		base_obj.data = new_obj.data.copy()
		base_obj.animation_data_clear()
		bpy.context.collection.objects.link(base_obj)
		bpy.context.view_layer.objects.active = base_obj

		SetActiveObject(base_obj, True)
		bpy.ops.object.mode_set(mode='EDIT')
		bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='EDGE')
		bpy.ops.mesh.select_all(action='DESELECT')
		bpy.ops.mesh.select_non_manifold(extend=False, use_boundary=True, use_multi_face = False,use_non_contiguous = False, use_verts = False)
		bpy.ops.mesh.remove_doubles()
		bpy.ops.object.mode_set(mode='OBJECT')

		SetActiveObject(new_obj, True)
		bpy.ops.object.mode_set(mode='EDIT')
		bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='EDGE')
		bpy.ops.mesh.select_all(action='DESELECT')
		bpy.ops.mesh.select_non_manifold(extend=False, use_boundary=True, use_multi_face = False,use_non_contiguous = False, use_verts = False)

		__obj = bpy.context.edit_object
		__me = __obj.data

		__bm = bmesh.from_edit_mesh(__me)
		for __e in __bm.edges:
			if __e.select:
				__e.smooth = False


		bmesh.update_edit_mesh(__me)
		
		__bm.free()

		bpy.ops.mesh.edge_split(type='EDGE')
		
		bpy.ops.mesh.select_all(action='DESELECT')
		
		bpy.ops.object.mode_set(mode='OBJECT')

		if use_world_origin:
			bpy.ops.object.transform_apply(location=True, rotation=True, scale=True)
		
		selected_obj = new_obj
		
		# Create a BMesh from the selected object
		bm = bmesh.new()
		bm.from_mesh(selected_obj.data)
		
		seams = [e for e in bm.edges if e.seam or not e.smooth]

		# split on seams
		bmesh.ops.split_edges(bm, edges=seams)

		if do_triangulation:
			bmesh.ops.triangulate(bm, faces=bm.faces)

		bm.to_mesh(selected_obj.data)
		bm.free()
		
		bpy.ops.object.select_all(action='DESELECT')
		selected_obj.select_set(True)

		bpy.ops.object.shade_smooth(use_auto_smooth=True)

		modifier2 = selected_obj.modifiers.new(name = selected_obj.name, type='DATA_TRANSFER')
		modifier2.object = base_obj
		#modifier2.vertex_group = double_faces_vg.name
		#modifier2.invert_vertex_group = True
		modifier2.use_loop_data = True
		modifier2.data_types_loops = {'CUSTOM_NORMAL'}
		modifier2.use_max_distance = True
		modifier2.max_distance = 0.001
		modifier2.loop_mapping = "NEAREST_POLYNOR"

		#modifier3 = selected_obj.modifiers.new(name = selected_obj.name, type='DATA_TRANSFER')

		bpy.ops.object.modifier_apply(modifier=modifier2.name)
		#bpy.ops.object.modifier_apply(modifier=modifier3.name)
		
		bpy.data.meshes.remove(base_obj.data)
		
		return old_obj, selected_obj
	else:
		print("No valid object is selected.")
		return None, None
	
def IsReadOnly(obj):
	return read_only_marker in obj.name

def IsMesh(obj):
	return obj.type == 'MESH'

def GetSelectedObjs(exclude_active = True):
	l = []
	for obj in bpy.context.selected_objects:
		if not exclude_active or obj != bpy.context.active_object:
			l.append(obj)
	return l

def move_object_to_collection(objs: list[bpy.types.Object], coll: bpy.types.Collection):
	for obj in objs:
		if obj != None:
			old_colls = [c for c in obj.users_collection]
			for c in old_colls:
				if c != None:
					c.objects.unlink(obj)
			coll.objects.link(obj)

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

def move_object_to_parent(objs, parent):
	for obj in objs:
		if obj != None and parent != None:
			obj.parent = parent


def SmoothPerimeterNormal(active_obj, selected_obj_list, apply_as_mesh = False, base_obj = None, loop_mapping_base = "TOPOLOGY"):
	if active_obj in selected_obj_list:
		selected_obj_list.remove(active_obj)
	
	if apply_as_mesh:
		original_active = SetActiveObject(active_obj)

	if base_obj:
		modifier = active_obj.modifiers.new(name = base_obj.name, type='DATA_TRANSFER')
		modifier.object = base_obj
		if 'DOUBLE_FACES_VERTS' in active_obj.vertex_groups:
			modifier.vertex_group = 'DOUBLE_FACES_VERTS'
			modifier.invert_vertex_group = True
		modifier.use_loop_data = True
		modifier.data_types_loops = {'CUSTOM_NORMAL'}
		modifier.use_max_distance = True
		modifier.max_distance = 0.001
		modifier.loop_mapping = loop_mapping_base
		if apply_as_mesh:
			bpy.ops.object.modifier_apply(modifier=modifier.name)

	for target_obj in selected_obj_list:
		if target_obj is not None:
			modifier = active_obj.modifiers.new(name = target_obj.name, type='DATA_TRANSFER')
			modifier.object = target_obj
			if 'DOUBLE_FACES_VERTS' in active_obj.vertex_groups:
				modifier.vertex_group = 'DOUBLE_FACES_VERTS'
				modifier.invert_vertex_group = True
			modifier.use_loop_data = True
			modifier.data_types_loops = {'CUSTOM_NORMAL'}
			modifier.use_max_distance = True
			modifier.max_distance = 0.001
			if mix_normal:
				modifier.mix_mode = 'ADD'
			if apply_as_mesh:
				bpy.ops.object.modifier_apply(modifier=modifier.name)

	if apply_as_mesh:
		SetActiveObject(original_active)

def CalcVIdLIdlist(mesh):
	vid_lid_list = [0 for _ in range(len(mesh.vertices))]
	for face in mesh.polygons:
		for l_id in face.loop_indices:
			vid_lid_list[mesh.loops[l_id].vertex_index] = l_id
	return vid_lid_list

def GetNormalTangents(mesh, with_tangent = True, fast_mode = False, fast_mode_list = None):
	if fast_mode and fast_mode_list != None:
		mesh.calc_normals_split()
		if with_tangent:
			mesh.calc_tangents()		
			Normals = [np.array(mesh.loops[loop_idx].normal) for loop_idx in fast_mode_list]
			
			if with_tangent:
				Bitangent_sign = [mesh.loops[loop_idx].bitangent_sign for loop_idx in fast_mode_list]
				Tangents = [utils_math.GramSchmidtOrthogonalize(np.array(mesh.loops[loop_idx].tangent), n) for loop_idx, n in zip(fast_mode_list, Normals)]
				return np.array(Normals), np.array(Tangents), np.array(Bitangent_sign)
	
			return np.array(Normals), None, None
	else:
		verts_count = len(mesh.vertices)
		Normals = [np.array([0,0,0]) for i in range(verts_count)]
		mesh.calc_normals_split()
		if with_tangent:
			Bitangent_sign = [1 for i in range(verts_count)]
			Tangents = [np.array([0,0,0]) for i in range(verts_count)]
			mesh.calc_tangents()
		for face in mesh.polygons:
			for vert_idx, loop_idx in zip(face.vertices, face.loop_indices):
				Normals[vert_idx] = Normals[vert_idx] + np.array(mesh.loops[loop_idx].normal)
				if with_tangent:
					Bitangent_sign[vert_idx] = mesh.loops[loop_idx].bitangent_sign
					Tangents[vert_idx] = Tangents[vert_idx] + np.array(mesh.loops[loop_idx].tangent)

		_Normals = [utils_math.Normalize(n) for n in Normals]

		if with_tangent:
			_Tangents = [utils_math.GramSchmidtOrthogonalize(t, np.array(n)) for t, n in zip(Tangents, _Normals)]
			return np.array(_Normals), np.array(_Tangents), np.array(Bitangent_sign)
		else:
			_Tangents = None
			Bitangent_sign = None
			return np.array(_Normals), None, None

def VisualizeVectors(obj_mesh, offsets, vectors, name = "Vectors"):
	vis_obj = None
	bm = bmesh.new()
	bm.from_mesh(obj_mesh)
	num_tangents = len(vectors)

	for v in vectors:
		print(v)

	if len(offsets) == 0:
		offsets = [(0,0,0) for i in range(num_tangents)]
	if num_tangents != len(bm.verts):
		print("Cannot create vector vis due to vertex number mismatch.")
		pass
	else:
		mesh = bpy.data.meshes.new(name)  # add a new mesh
		obj = bpy.data.objects.new(name, mesh)  # add a new object using the mesh

		bpy.context.collection.objects.link(obj)
		scale = 0.02
		origins = [(offset[0] + v.co[0], offset[1] + v.co[1], offset[2] + v.co[2]) for v, offset in zip(bm.verts, offsets)]
		verts = origins + [(t[0] * scale + o[0], t[1] * scale + o[1], t[2] * scale + o[2]) for t, o in zip(vectors, origins)]
		edges = [[i,i + len(bm.verts)] for i in range(len(bm.verts))]
		mesh.from_pydata(verts, edges, [])
		vis_obj = obj

	bm.free()
	return vis_obj

def SetWeightKeys(obj, weight_keys:list):
	if len(weight_keys) != len(obj.vertex_groups):
		min_len = min(len(weight_keys), len(obj.vertex_groups))
		for vg, name in zip(obj.vertex_groups[:min_len], weight_keys[:min_len]):
			vg.name = name
		return False

	for vg, name in zip(obj.vertex_groups, weight_keys):
		vg.name = name

	return True

def BoxFromMinMax(name: str, min_position: list, max_position: list):
	mesh = bpy.data.meshes.new(name)  # add a new mesh
	obj = bpy.data.objects.new(name, mesh)  # add a new object using the mesh
	bpy.context.collection.objects.link(obj)
	minx = min_position[0]
	miny = min_position[1]
	minz = min_position[2]
	maxx = max_position[0]
	maxy = max_position[1]
	maxz = max_position[2]
	verts = [(minx, miny, minz),(minx, miny, maxz),(maxx, miny, minz),(maxx, miny, maxz),(minx, maxy, minz),(minx, maxy, maxz),(maxx, maxy, minz),(maxx, maxy, maxz)]
	faces = [[0,1,3,2], [4,5,7,6], [0,1,5,4], [2,3,7,6], [0,2,6,4], [1,3,7,5]]
	mesh.from_pydata(verts, [], faces)
	return obj

def BoxFromCenterExpand(name: str, center: list, expand: list):
	min_position = [c - e for c, e in zip(center, expand)]
	max_position = [c + e for c, e in zip(center, expand)]

	return BoxFromMinMax(name, min_position, max_position)

def SphereFromCenterRadius(name: str, center: list, radius):
	obj = BoxFromCenterExpand(name, center, [radius, radius, radius])
	obj.display_type = 'BOUNDS'
	obj.display_bounds_type = 'SPHERE'

	return obj

def GetObjBBoxMinMax(obj):
	bbox = obj.bound_box
	xs = [i[0] for i in bbox]
	ys = [i[1] for i in bbox]
	zs = [i[2] for i in bbox]
	mins = [min(xs), min(ys), min(zs)]
	maxs = [max(xs), max(ys), max(zs)]
	return mins, maxs

def GetObjBBoxCenterExpand(obj):
	mins, maxs = GetObjBBoxMinMax(obj)
	center = [(ma + mi) * 0.5 for mi, ma in zip(mins, maxs)]
	expand = [ma - ce for ma, ce in zip(maxs, center)]
	return center, expand

def ApplyAllModifiers(obj):
	selected = GetSelectedObjs(True)
	active = SetActiveObject(obj)

	for modifier in obj.modifiers:
		bpy.ops.object.modifier_apply(modifier=modifier.name)

	SetSelectObjects(selected)
	SetActiveObject(active)

def GetVertColorPerVert(obj):
    vert_number = len(obj.data.vertices)
    v_colors = [(1,1,1,1) for i in range(vert_number)]
    mesh = obj.data
    try:
        color_layer = mesh.vertex_colors[0]
    except:
        return v_colors, False
    mesh_loops = {li: loop.vertex_index for li, loop in enumerate(mesh.loops)}
    vtx_colors = {mesh_loops[li]: data.color for li, data in color_layer.data.items()}
    for idx, color in vtx_colors.items():
        v_colors[idx] = color

    return v_colors, True

def SetVertColorPerVert(obj, v_colors):
	col = obj.data.vertex_colors.active
	for poly in obj.data.polygons:
		for v_ix, l_ix in zip(poly.vertices, poly.loop_indices):
			col.data[l_ix].color = v_colors[v_ix]

def ColorToRGB888(color):
	rgb = list(color)[:-1]
	return [int(v * 255) for v in rgb]

def RGB888ToColor(rgb) -> tuple:
	return tuple([v / 255 for v in rgb] + [1])

def RGB888ToRGB565(rgb):
	r = rgb[0] >> 3
	g = rgb[1] >> 2
	b = rgb[2] >> 3
	return (r << 11) | (g << 5) | b

def RenamingBone(name:str):
	tags = utils._tag(name)
	if 'RI' in tags and name.startswith("R_"):
		bone_rename_dict[name[2:] + '.R'] = 1
		return name[2:] + '.R'
	elif 'LE' in tags and name.startswith("L_"):
		bone_rename_dict[name[2:] + '.L'] = 1
		return name[2:] + '.L'
	
	return name

def RenamingBoneList(names:list):
	return [RenamingBone(name) for name in names]

def RevertRenamingBone(name:str):
	#if name in bone_rename_dict and bone_rename_dict[name] > 0:
	#	bone_rename_dict[name] -= 1
	#else:
	#	return name

	if name.endswith('.R'):
		if name.startswith('R_'):
			return name[:-2]
		else:
			return 'R_' + name[:-2]
	elif name.endswith('.L'):
		if name.startswith('L_'):
			return name[:-2]
		else:
			return 'L_' + name[:-2]
	return name

def RevertRenamingBoneList(names:list):
	return [RevertRenamingBone(name) for name in names]

def BuildhkBufferedMesh(mesh: dict, hkaSkeleton_obj: bpy.types.Object):
	mesh_objs = []
	mesh_type = mesh['type']
	name = mesh['name']
	print(f'Reading havok cloth sim mesh: {name}.')
	matrix = mesh['localFrame']
	print(f'Local frame: {matrix}')
	T = mathutils.Matrix()
	for i in range(4):
		for j in range(4):
			T[i][j] = mesh['localFrame'][i][j]

	if mesh_type == 1: # Capsule
		mesh_obj = CapsuleFromParameters(name, mesh['capsuleEnd'], mesh['capsuleStart'], mesh['capsuleSmallRadius'], mesh['capsuleBigRadius'])
		mesh_obj.matrix_world = T
		mesh_objs.append(mesh_obj)
	elif mesh_type == 0:
		positions = mesh['positions']
		normals = mesh['normals']
		triangles = mesh['triangleIndices']
		boneWeights = utils.TransformWeightData(mesh['boneWeights'], do_normalize=True)
		bl_mesh = bpy.data.meshes.new(name = name)
		bl_mesh.from_pydata(positions, [], triangles)
		mesh_obj = bpy.data.objects.new(name, bl_mesh)
		bpy.context.scene.collection.objects.link(mesh_obj)
		mesh_obj.matrix_world = T

		for b_id, b_entry in boneWeights.items():
			vg = mesh_obj.vertex_groups.new(name = hkaSkeleton_obj.data.bones[b_id].name)
			for v_id, weight in b_entry:
				vg.add([v_id], weight, 'REPLACE')


		vis_obj = VisualizeVectors(bl_mesh, [], normals, 'normals')
		mesh_objs.append(mesh_obj)
		mesh_objs.append(vis_obj)


	if 'extraShapes' in mesh.keys():
		for sub_mesh in mesh['extraShapes']:
			mesh_objs.extend(BuildhkBufferedMesh(sub_mesh, hkaSkeleton_obj))

	return mesh_objs

def GetNodeGroupInputIdentifier(node_group, input_name):
	inputs = node_group.inputs
	id = inputs[input_name].identifier
	return id

def CapsuleFromParameters(name: str, smallEnd: list, bigEnd: list, smallRadius: float, bigRadius: float):
	mesh = bpy.data.meshes.new(name)
	obj = bpy.data.objects.new(name, mesh)

	bpy.context.collection.objects.link(obj)

	if smallRadius > bigRadius:
		smallRadius, bigRadius = bigRadius, smallRadius
		smallEnd, bigEnd = bigEnd, smallEnd

	gnmod = None
	for gnmod in obj.modifiers:
		if gnmod.type == "NODES":
			break

	if (gnmod is None) or (gnmod.type != "NODES"):
		gnmod = obj.modifiers.new("Capsule", "NODES")

	gnmod.node_group = capsule_gen.GetGeoNode()

	start_big_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Start/Big")
	end_small_id = GetNodeGroupInputIdentifier(gnmod.node_group, "End/Small")
	big_radius_id = GetNodeGroupInputIdentifier(gnmod.node_group, "bigRadius")
	small_radius_id = GetNodeGroupInputIdentifier(gnmod.node_group, "smallRadius")

	gnmod[start_big_id][0] = bigEnd[0]
	gnmod[start_big_id][1] = bigEnd[1]
	gnmod[start_big_id][2] = bigEnd[2]

	gnmod[end_small_id][0] = smallEnd[0]
	gnmod[end_small_id][1] = smallEnd[1]
	gnmod[end_small_id][2] = smallEnd[2]

	gnmod[big_radius_id] = bigRadius
	gnmod[small_radius_id] = smallRadius
	
	obj.display_type = 'WIRE'
	return obj

def SetCapsuleParameters(capsule_obj, smallEnd = None, bigEnd = None, smallRadius = None, bigRadius = None, create_if_not_exist = True):
	if capsule_obj == None:
		return
	gnmod = None
	for gnmod in capsule_obj.modifiers:
		if gnmod.type == "NODES" and gnmod.node_group.name == "Capsule_Gen":
			break

	if (gnmod is None) or (gnmod.type != "NODES") or (gnmod.node_group.name != "Capsule_Gen"):
		if not create_if_not_exist:
			return
		gnmod = capsule_obj.modifiers.new("Capsule", "NODES")

	if bigEnd is not None:
		start_big_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Start/Big")
		gnmod[start_big_id][0] = bigEnd[0]
		gnmod[start_big_id][1] = bigEnd[1]
		gnmod[start_big_id][2] = bigEnd[2]

	if smallEnd is not None:
		end_small_id = GetNodeGroupInputIdentifier(gnmod.node_group, "End/Small")
		gnmod[end_small_id][0] = smallEnd[0]
		gnmod[end_small_id][1] = smallEnd[1]
		gnmod[end_small_id][2] = smallEnd[2]

	if bigRadius is not None:
		big_radius_id = GetNodeGroupInputIdentifier(gnmod.node_group, "bigRadius")
		gnmod[big_radius_id] = bigRadius

	if smallRadius is not None:
		small_radius_id = GetNodeGroupInputIdentifier(gnmod.node_group, "smallRadius")
		gnmod[small_radius_id] = smallRadius

	gnmod.show_on_cage = True
	gnmod.show_on_cage = False

def ConstraintObjToArmatureBone(obj, armature_obj, bone_index, inherit_rotation = False):
	if armature_obj == None:
		return
	if obj == None:
		return
	if bone_index == None:
		return

	obj.constraints.clear()
	bone= armature_obj.data.bones[bone_index]
	if inherit_rotation:
		obj.matrix_world = armature_obj.matrix_world @ bone.matrix_local
	arma_const = obj.constraints.new(type = 'ARMATURE')
	_target = arma_const.targets.new()
	_target.target = armature_obj
	_target.subtarget = bone.name

def PlaneFromOriginNormal(name: str, origin, normal_dir, size = 1.0):
	mesh = bpy.data.meshes.new(name)
	obj = bpy.data.objects.new(name, mesh)

	bpy.context.collection.objects.link(obj)

	gnmod = None
	for gnmod in obj.modifiers:
		if gnmod.type == "NODES":
			break

	if (gnmod is None) or (gnmod.type != "NODES"):
		gnmod = obj.modifiers.new("Plane", "NODES")

	gnmod.node_group = plane_gen.GetGeoNode()

	normal_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Normal")
	size_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Size")

	obj.location = origin

	gnmod[normal_id][0] = normal_dir[0]
	gnmod[normal_id][1] = normal_dir[1]
	gnmod[normal_id][2] = normal_dir[2]

	gnmod[size_id] = size
	
	return obj

def SetPlaneParameters(plane_obj, origin = None, normal_dir = None, size = None, create_if_not_exist = True):
	if plane_obj == None:
		return
	gnmod = None
	for gnmod in plane_obj.modifiers:
		if gnmod.type == "NODES" and gnmod.node_group.name == "Plane_Gen":
			break

	if (gnmod is None) or (gnmod.type != "NODES") or (gnmod.node_group.name != "Plane_Gen"):
		if not create_if_not_exist:
			return
		gnmod = plane_obj.modifiers.new("Plane", "NODES")

	if origin is not None:
		plane_obj.location = origin

	if normal_dir is not None:
		normal_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Normal")
		gnmod[normal_id][0] = normal_dir[0]
		gnmod[normal_id][1] = normal_dir[1]
		gnmod[normal_id][2] = normal_dir[2]

	if size is not None:
		size_id = GetNodeGroupInputIdentifier(gnmod.node_group, "Size")
		gnmod[size_id] = size

	gnmod.show_on_cage = True
	gnmod.show_on_cage = False

def ConstraintObjsToBoneRotation(objs: list[bpy.types.Object], armature_obj, bone_index) -> bpy.types.Object:
	if armature_obj == None:
		return
	if objs == None or len(objs) == 0:
		return
	if bone_index == None:
		return

	mesh = bpy.data.meshes.new('ANCHOR_OBJ')
	anchor_obj = bpy.data.objects.new('ANCHOR_OBJ', mesh)

	bpy.context.collection.objects.link(anchor_obj)

	ConstraintObjToArmatureBone(anchor_obj, armature_obj, bone_index, True)

	for obj in objs:
		if obj == None:
			continue
		obj.constraints.clear()
		const = obj.constraints.new(type = 'COPY_ROTATION')
		const.target = anchor_obj

	return anchor_obj

def RemoveNonBoneVG(obj:bpy.types.Object, skeleton:bpy.types.Object):
	for vg in obj.vertex_groups:
		if vg.name not in skeleton.data.bones:
			obj.vertex_groups.remove(vg)

def GatherWeights(obj:bpy.types.Object, quantize_bytes = 2, max_blend_entries = 8, prune_empty_vertex_groups = True):
	vertex_groups = obj.vertex_groups
	if prune_empty_vertex_groups:
		vgrp_markers = [[vg.name, -1] for vg in vertex_groups]
	else:
		vgrp_markers = [[vg.name, i] for vg, i in zip(vertex_groups, range(len(vertex_groups)))]
	new_id = 0

	bm = bmesh.new()
	bm.from_mesh(obj.data)
	bm.verts.layers.deform.verify()

	deform = bm.verts.layers.deform.active
	
	weights = []
	_min_weight = 1 / (256 ** quantize_bytes - 2)
	for v in bm.verts:
		g = v[deform]
		
		weights.append([])
		for vg_id, weight in g.items():
			if weight > _min_weight:
				if vgrp_markers[vg_id][1] == -1:
					vgrp_markers[vg_id][1] = new_id
					new_id += 1
				weights[-1].append([vgrp_markers[vg_id][1], weight])
		
		if len(weights[-1]) > max_blend_entries:
			index_list = sorted(range(len(weights[-1])), key=lambda k: weights[-1][k], reverse=True)
			weights[-1] = [weights[-1][i] for i in index_list[:max_blend_entries]]
		
		if len(weights[-1]) == 0:
			weights[-1].append([0, 0])

	vgrp_markers = sorted(vgrp_markers, key=lambda x: x[1])
	vgrp_names = [vg[0] for vg in vgrp_markers if vg[1] != -1]

	bm.free()

	return weights, vgrp_names

def RemapBoneIdToSkeleton(weights, vgrp_names, skeleton:bpy.types.Object):
	remap = {}
	used_indices = set()
	skele_bones = [bone.name for bone in skeleton.data.bones]
	for i, bone in enumerate(vgrp_names):
		if bone in skele_bones:
			remap[i] = skele_bones.index(bone)
			used_indices.add(skele_bones.index(bone))

	for i, w in enumerate(weights):
		for j, v in enumerate(w):
			if v[0] in remap:
				weights[i][j][0] = remap[v[0]]
			else:
				print(f"Bone {v[0]} not found in skeleton.")
				return None, None
			
	return weights, list(used_indices)

def RemapBoneIdToSubset(weights, subset:list, order_subset = True):
	remap = {}
	if order_subset:
		subset = sorted(subset)
	for i, bone_id in enumerate(subset):
		remap[bone_id] = i

	for i, w in enumerate(weights):
		for j, v in enumerate(w):
			if v[0] in remap:
				weights[i][j][0] = remap[v[0]]
			else:
				print(f"Bone {v[0]} not found in subset.")
				return None, None
			
	return weights, subset

def NormalizeAndQuantizeWeights(weights, quantize_bytes = 2):
	max_value = 256 ** quantize_bytes - 1
	for i, w in enumerate(weights):
		_sum = sum([v[1] for v in w])
		weights[i] = [[v[0], int(max_value * v[1] / _sum)] for v in w]
		# Sort by weight
		weights[i] = sorted(weights[i], key=lambda x: x[1], reverse=True)
		# Make sure weights sum up to max_value
		if len(weights[i]) > 1:
			weights[i][0][1] = max_value - sum([v[1] for v in weights[i][1:]])
		else:
			weights[i][0][1] = max_value
	return weights

def RemoveMeshObj(mesh_obj):
	bpy.data.meshes.remove(mesh_obj.data)

def Numpy2MathutilsMatrix(matrix: np.ndarray) -> mathutils.Matrix:
	return mathutils.Matrix(matrix.tolist())

def Mathutils2NumpyMatrix(matrix: mathutils.Matrix) -> np.ndarray:
	return np.array(matrix).reshape((4,4))

def Numpy2MathutilsVector(vector: np.ndarray) -> mathutils.Vector:
	return mathutils.Vector(vector.flatten())

def Mathutils2NumpyVector(vector: mathutils.Vector) -> np.ndarray:
	return np.array(vector).reshape((3,1))

def GetTriVerts(mesh:bpy.types.Object, triangle:bpy.types.MeshPolygon):
	pivot1_id = triangle.vertices[0]
	pivot1_co = mesh.data.vertices[pivot1_id].co
	pivot2_id = triangle.vertices[1]
	pivot2_co = mesh.data.vertices[pivot2_id].co
	pivot3_id = triangle.vertices[2]
	pivot3_co = mesh.data.vertices[pivot3_id].co
	return pivot1_co, pivot2_co, pivot3_co

def GethclLocalBoneTransform(tri_mesh: bpy.types.Object, triangle:bpy.types.MeshPolygon, bone_world_transform:mathutils.Matrix) -> list[list[float]]:
	pivot1_co, pivot2_co, _ = GetTriVerts(tri_mesh, triangle) 
	p_1 = Mathutils2NumpyVector(pivot1_co)
	p_2 = Mathutils2NumpyVector(pivot2_co)
	center = Mathutils2NumpyVector(triangle.center)
	bone_t = Mathutils2NumpyMatrix(bone_world_transform)

	np_T = utils_math.GetBoneTransformToTriangle(p_1, p_2, center, bone_t)

	return np_T.tolist()

def GethclLocalBoneTransforms(tri_mesh: bpy.types.Object, armature_obj: bpy.types.Object, tri_indices: list, bone_indices: list):
	results = []
	for f_id, b_id in zip(tri_indices, bone_indices):
		triangle = tri_mesh.data.polygons[f_id]
		bone = armature_obj.data.bones[b_id]
		bone_t = armature_obj.matrix_world @ BoneAxisCorrectionRevert(bone.matrix_local)
		np_T = GethclLocalBoneTransform(tri_mesh, triangle, bone_t)
		results.append(np_T)

	return results

def is_plugin_debug_mode() -> bool:
	return bpy.context.scene.sgb_debug_mode == True

def TransferWeightByDistance(target_obj: bpy.types.Object, reference_obj: bpy.types.Object):
	if target_obj == None or reference_obj == None:
		return
	for r_vg in reference_obj.vertex_groups:
		if r_vg.name not in target_obj.vertex_groups:
			target_obj.vertex_groups.new(name = r_vg.name)
	original_active = SetActiveObject(target_obj)
	modifier = target_obj.modifiers.new(name = 'WeightTransfer', type='DATA_TRANSFER')
	modifier.object = reference_obj
	modifier.use_vert_data = True
	modifier.data_types_verts = {'VGROUP_WEIGHTS'}
	bpy.ops.object.modifier_apply(modifier=modifier.name)

	SetActiveObject(original_active)

def get_preferences():
    return bpy.context.preferences.addons["tool_export_mesh"].preferences

def get_preference(prop:str):
	return get_preferences().get(prop)

def get_texconv_path() -> str|None:
	texconv_path = get_preferences().texconv_path
	if texconv_path == '':
		return None
	if not os.path.exists(texconv_path) or not os.path.isfile(texconv_path):
		return None
	return texconv_path
