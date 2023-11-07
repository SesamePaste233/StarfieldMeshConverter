import bpy
import bmesh
import os
import numpy as np

from utils_math import Normalize, GramSchmidtOrthogonalize

read_only_marker = '[READONLY]'
mix_normal = False

def open_folder(initial_directory):

	# Set the window manager to the current context
	wm = bpy.context.window_manager

	# Call the file browser operator
	bpy.ops.wm.path_open(filepath=initial_directory)
						 
def update_path(utils_p):
	utils_path = bpy.path.abspath(utils_p)
	temp_path = os.path.join(utils_path, 'Temp')
	
	return utils_path,temp_path

def SetSelectObjects(objs):
	original_selected = bpy.context.selected_objects
	bpy.ops.object.select_all(action='DESELECT')
	for obj in objs:
		if obj != None:
			obj.select_set(state=True)
	return original_selected

def GetActiveObject():
	return bpy.context.active_object

def SetActiveObject(obj):
	original_active = GetActiveObject()
	#bpy.ops.object.select_all(action='DESELECT')
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

def PreprocessAndProxy(old_obj, use_world_origin, convert_to_mesh = True):
	if old_obj and old_obj.type == 'MESH':
		
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

		bpy.ops.object.select_all(action='DESELECT')
		new_obj.select_set(True)
		if convert_to_mesh:
			bpy.ops.object.convert(target='MESH')

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
		
		# Triangulate the mesh
		bmesh.ops.triangulate(bm, faces=bm.faces)

		bm.to_mesh(selected_obj.data)
		bm.free()
		
		bpy.ops.object.select_all(action='DESELECT')
		selected_obj.select_set(True)

		bpy.ops.object.shade_smooth(use_auto_smooth=True)

		modifier = selected_obj.modifiers.new(name = selected_obj.name, type='DATA_TRANSFER')
		modifier.object = old_obj
		modifier.use_loop_data = True
		modifier.data_types_loops = {'CUSTOM_NORMAL'}
		modifier.use_max_distance = True
		modifier.max_distance = 0.001
		modifier.loop_mapping = "TOPOLOGY"

		bpy.ops.object.modifier_apply(modifier=modifier.name)

		return old_obj, selected_obj
	else:
		print("No valid object is selected.")
		return old_obj, None
	
def IsReadOnly(obj):
	return read_only_marker in obj.name

def IsMesh(obj):
	return obj.type == 'MESH'

def GetSelectedObjs(exclude_active):
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

def SmoothPerimeterNormal(active_obj, selected_obj_list, apply_as_mesh = False, base_obj = None):
	if active_obj in selected_obj_list:
		selected_obj_list.remove(active_obj)
	
	if apply_as_mesh:
		original_active = SetActiveObject(active_obj)

	if base_obj:
		modifier = active_obj.modifiers.new(name = base_obj.name, type='DATA_TRANSFER')
		modifier.object = base_obj
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

	_Normals = [Normalize(n) for n in Normals]

	if with_tangent:
		_Tangents = [GramSchmidtOrthogonalize(t, np.array(n)) for t, n in zip(Tangents, _Normals)]
	else:
		_Tangents = None
		Bitangent_sign = None

	return _Normals, _Tangents, Bitangent_sign

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