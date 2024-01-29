import bpy
import mathutils
import numpy as np

def QueryCloserFaces(tri_mesh_obj: bpy.types.Object, num_queries: int, center, query_func = None):
	'''
		tri_mesh_obj: the mesh object to query
		num_queries: number of queries to perform
		center: the center of the query sphere
		query_func: query_func(face: bpy.types.MeshPolygon) -> result

		return: a list of tuples (face_index, result, distance)
	'''
	mesh = tri_mesh_obj.data
	size = len(mesh.polygons)
	kd = mathutils.kdtree.KDTree(size)

	for i, f in enumerate(mesh.polygons):
		kd.insert(f.center, i)

	kd.balance()

	if query_func == None:
		query_func = lambda x: None
	results = [(index, query_func(mesh.polygons[index]), dist) for (co, index, dist) in kd.find_n(center, num_queries)]
	
	results = sorted(results, key=lambda x: x[2])

	return results

def QueryCloserFacesMultiple(tri_mesh_obj: bpy.types.Object, num_queries_per_center: int, centers: list, query_func = None):
	'''
		tri_mesh_obj: the mesh object to query
		num_queries_per_center: number of queries to perform per center
		centers: a list of centers
		query_func: query_func(face: bpy.types.MeshPolygon, center) -> result

		return: a list of lists of tuples (face_index, result, distance)
	'''
	mesh = tri_mesh_obj.data
	size = len(mesh.polygons)
	kd = mathutils.kdtree.KDTree(size)

	for i, f in enumerate(mesh.polygons):
		kd.insert(f.center, i)

	kd.balance()

	if query_func == None:
		query_func = lambda x: None
	results = []
	for center in centers:
		result_center = [(index, query_func(mesh.polygons[index], center), dist) for (co, index, dist) in kd.find_n(center, num_queries_per_center)]
		results.append(sorted(result_center, key=lambda x: x[2]))

	return results

def Normalize(vec):
	n = np.linalg.norm(np.array(vec))
	if n == 0:
		return vec
	return [v/n for v in vec]

def GetTriVerts(mesh:bpy.types.Object, triangle:bpy.types.MeshPolygon):
	pivot1_id = triangle.vertices[0]
	pivot1_co = mesh.data.vertices[pivot1_id].co
	pivot2_id = triangle.vertices[1]
	pivot2_co = mesh.data.vertices[pivot2_id].co
	pivot3_id = triangle.vertices[2]
	pivot3_co = mesh.data.vertices[pivot3_id].co
	return pivot1_co, pivot2_co, pivot3_co

def TriangleEdgeDistances(pivot1, pivot2, pivot3, query_pt):
	# Calculate the distance from the query point to each edge of the triangle
	edge1 = np.array(pivot2) - np.array(pivot1)
	edge2 = np.array(pivot3) - np.array(pivot2)
	edge3 = np.array(pivot1) - np.array(pivot3)

	edge1_len = np.linalg.norm(edge1)
	edge2_len = np.linalg.norm(edge2)
	edge3_len = np.linalg.norm(edge3)

	edge1 = Normalize(edge1)
	edge2 = Normalize(edge2)
	edge3 = Normalize(edge3)

	query_pt = np.array(query_pt)

	# Calculate the distance from the query point to each edge of the triangle
	dist1 = np.linalg.norm(np.cross(edge1, query_pt - pivot1)) / edge1_len
	dist2 = np.linalg.norm(np.cross(edge2, query_pt - pivot2)) / edge2_len
	dist3 = np.linalg.norm(np.cross(edge3, query_pt - pivot3)) / edge3_len

	return dist1, dist2, dist3

def GetBoneTransformToTriangle(pivot1: np.ndarray, pivot2: np.ndarray, center: np.ndarray, bone_transform: np.ndarray):
	'''
	Sets the bone transform to the triangle defined by first two pivots and the center of triangle. Specially made for hclSimpleMeshBoneDeformOperator.
		pivot1: np.array([x,y,z])
		pivot2: np.array([x,y,z])
		center: np.array([x,y,z])
		bone_transform: np.array([4x4])

		return: np.array([4x4])
	'''
	p1 = pivot1.reshape(1, -1)
	p2 = pivot2.reshape(1, -1)
	c = center.reshape(1, -1)

	c_1 = p1 - c
	c_2 = p2 - c
	c_3 = np.cross(c_1, c_2)
	f_c = c

	M = np.array([
		[c_1[0, 0], c_2[0, 0], c_3[0, 0], f_c[0, 0]],
		[c_1[0, 1], c_2[0, 1], c_3[0, 1], f_c[0, 1]],
		[c_1[0, 2], c_2[0, 2], c_3[0, 2], f_c[0, 2]],
		[0,0,0,1]
	])

	return (np.linalg.inv(M) @ bone_transform).T
	
def _collect_childern_bones_recursive(bone: bpy.types.Bone, tree: dict[str, list[dict]], only_in_list: set[str] = None, pre_order_func = None) -> None:
	for child in bone.children:
		if only_in_list is not None and child.name not in only_in_list:
			continue
		subtree = {child.name: []}
		if pre_order_func is not None:
			pre_order_func(bone, child)
		_collect_childern_bones_recursive(child, subtree, only_in_list, pre_order_func)
		tree[bone.name].append(subtree)

def GetClothBoneSubTrees(armature_obj: bpy.types.Object, cloth_bones_list: list[str], factor = 0.8) -> tuple[list[dict], dict[str, float], dict[str, int]]:
	cloth_bones = set(cloth_bones_list)
	bone_subtrees = []
	traversed = {k: False for k in cloth_bones}
	leaf_bones = []
	subtree_roots = set()
	for bone_name in cloth_bones:
		bone = armature_obj.data.bones[bone_name]
		if len(bone.children) == 0:
			leaf_bones.append(bone)
			traversed[bone_name] = True

	for bone in leaf_bones:
		while bone.parent is not None and bone.parent.name in cloth_bones:
			bone = bone.parent
			traversed[bone.name] = True
		if bone.parent is None:
			raise Exception(f"Cloth bone {bone.name} is not a child of any non-cloth bone.")
		else:
			subtree_roots.add(bone.parent)
	
	if not all(traversed.values()):
		names = [k for k, v in traversed.items() if not v]
		raise Exception(f"Some cloth bones has non-cloth bone children. \'{names}\'")
	
	cloth_bone_factors = {k: 1.0 for k in cloth_bones | set([r.name for r in subtree_roots])}
	cloth_bone_subtree_ids = {k: -1 for k in cloth_bones | set([r.name for r in subtree_roots])}
	i = 0
	def _pre_order_func(parent: bpy.types.Bone, child: bpy.types.Bone):
		nonlocal cloth_bone_factors, cloth_bone_subtree_ids, i
		cloth_bone_subtree_ids[child.name] = i
		if parent.name not in cloth_bones:
			cloth_bone_factors[child.name] = factor
		else:
			cloth_bone_factors[child.name] = cloth_bone_factors[parent.name] * factor

	for root in subtree_roots:
		subtree = {root.name: []}
		cloth_bone_subtree_ids[root.name] = i
		_collect_childern_bones_recursive(root, subtree, cloth_bones, _pre_order_func)
		bone_subtrees.append(subtree)
		i += 1

	return bone_subtrees, cloth_bone_factors, cloth_bone_subtree_ids

def AssignPointsToSubTrees(subtrees_node_centers: dict[str, mathutils.Vector], node_subtree_ids: dict[str, int], points) -> tuple[list[int], list[float]]:
	node_name_list = list(subtrees_node_centers.keys())
	kdtree = mathutils.kdtree.KDTree(len(subtrees_node_centers))
	for i, center in enumerate(subtrees_node_centers.values()):
		kdtree.insert(center, i)

	kdtree.balance()
	tree_ids = []
	distances = []
	for p in points:
		_, index, dist = kdtree.find(p)
		tree_ids.append(node_subtree_ids[node_name_list[index]])
		distances.append(dist)

	return tree_ids, distances

def GaussianDistanceWeightingScheme(subtree_node_centers: list, node_weight_factors: list[float], points, sigma = 1.0) -> list[float]:
	two_sigma_sq = 2 * sigma * sigma
	if all([f == node_weight_factors[0] for f in node_weight_factors]):
		return [node_weight_factors[0] for _ in points]
	
	p_factors = []
	for p in points:
		p_center = np.array(p)
		d_vec = [p_center - np.array(center) for center in subtree_node_centers]
		# Gaussian kernel
		weights = [np.exp(-v.dot(v) / two_sigma_sq) for v in d_vec]
		# Convert to distribution
		weights = [w / sum(weights) for w in weights]
		p_factor = sum([w * f for w, f in zip(weights, node_weight_factors)])
		p_factors.append(p_factor)

	return p_factors
			