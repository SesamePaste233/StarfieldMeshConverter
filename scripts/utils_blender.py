import bpy
import bmesh
import os
import numpy as np

import utils_math

read_only_marker = '[READONLY]'
mix_normal = False

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

def PreprocessAndProxy(old_obj, use_world_origin, operator, convert_to_mesh = True):
	if old_obj and old_obj.type == 'MESH':
		
		if old_obj.data.shape_keys != None and old_obj.data.shape_keys.key_blocks != None:
			key_blocks = old_obj.data.shape_keys.key_blocks
			if key_blocks[0].name == 'Basis':
				keys = old_obj.data.shape_keys.key_blocks.keys()
				shape_key_index = keys.index('Basis')
				old_obj.active_shape_key_index = shape_key_index
		
		#SetActiveObject(old_obj, True)
		#bpy.ops.object.mode_set(mode='EDIT')
		#bpy.ops.mesh.select_mode(use_extend=False, use_expand=False, type='EDGE')
		#bpy.ops.mesh.select_all(action='DESELECT')
		#bpy.ops.mesh.select_non_manifold(extend=False, use_boundary=False, use_multi_face = True,use_non_contiguous = True, use_verts = False)
		#has_double_faces = False
		#__obj = bpy.context.edit_object
		#__me = __obj.data

		#double_faces_verts = []

		#__bm = bmesh.from_edit_mesh(__me)
		#for __e in __bm.edges:
		#	if __e.select:
		#		has_double_faces = True
		#		double_faces_verts.append(__e.verts[0].index)
		#		double_faces_verts.append(__e.verts[1].index)
		#		break
		#if has_double_faces:
		#	operator.report({'ERROR'}, f"There are double faces in your model! They are highlighted in selection mode.")
		#	return None, None
		
		#bpy.ops.object.mode_set(mode='OBJECT')

		#double_faces_vg = old_obj.vertex_groups.new(name='DOUBLE_FACES_VERTS')
		#double_faces_vg.add(double_faces_verts, 1,'REPLACE')

		#__bm.free()

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

		#bpy.ops.object.shade_smooth(use_auto_smooth=True)
		
		#modifier1 = base_obj.modifiers.new(name = base_obj.name, type='DATA_TRANSFER')
		#modifier1.object = old_obj
		#modifier1.vertex_group = double_faces_vg.name
		#modifier1.use_loop_data = True
		#modifier1.invert_vertex_group = True
		#modifier1.data_types_loops = {'CUSTOM_NORMAL'}
		#modifier1.use_max_distance = True
		#modifier1.max_distance = 0.001
		#modifier1.loop_mapping = "TOPOLOGY"

		#bpy.ops.object.modifier_apply(modifier=modifier1.name)

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
		
		bpy.ops.object.modifier_apply(modifier=modifier2.name)
		
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

def move_object_to_collection(objs, coll):
	for obj in objs:
		if obj != None:
			old_colls = [c for c in obj.users_collection]
			for c in old_colls:
				if c != None:
					c.objects.unlink(obj)
			coll.objects.link(obj)
	
def move_object_to_parent(objs, parent):
	for obj in objs:
		if obj != None and parent != None:
			obj.parent = parent


def SmoothPerimeterNormal(active_obj, selected_obj_list, apply_as_mesh = False, base_obj = None):
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
		modifier.loop_mapping = "TOPOLOGY"
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

def GetNormalTangents(mesh, with_tangent = True):
	verts_count = len(mesh.vertices)
	Normals = [np.array([0,0,0]) for i in range(verts_count)]
	if with_tangent:
		Bitangent_sign = [1 for i in range(verts_count)]
		Tangents = [np.array([0,0,0]) for i in range(verts_count)]

	mesh.calc_normals_split()
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
	else:
		_Tangents = None
		Bitangent_sign = None

	return np.array(_Normals), np.array(_Tangents), Bitangent_sign

def VisualizeVectors(obj_mesh, offsets, vectors, name = "Vectors"):
	bm = bmesh.new()
	bm.from_mesh(obj_mesh)
	num_tangents = len(vectors)
	if num_tangents != len(bm.verts) or len(offsets) != len(bm.verts):
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

	bm.free()

def SetWeightKeys(obj, weight_keys:list):
	if len(weight_keys) != len(obj.vertex_groups):
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
	col = obj.data.vertex_colors.active
	if col == None:
		col = obj.data.vertex_colors[0]
	vert_number = len(obj.data.vertices)
	v_colors = [[] for i in range(vert_number)]
	for poly in obj.data.polygons:
		for v_ix, l_ix in zip(poly.vertices, poly.loop_indices):
			v_colors[v_ix] = col.data[l_ix].color

	return v_colors

def SetVertColorPerVert(obj, v_colors):
	col = obj.data.vertex_colors.active
	for poly in obj.data.polygons:
		for v_ix, l_ix in zip(poly.vertices, poly.loop_indices):
			col.data[l_ix].color = v_colors[v_ix]

def ColorToLightness(color):
	rgb = list(color)[:-1]
	_max = max(rgb)
	_min = min(rgb)
	return 0.5 * (_max + _min)