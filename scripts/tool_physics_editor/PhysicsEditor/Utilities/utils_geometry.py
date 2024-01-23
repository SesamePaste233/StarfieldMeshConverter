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