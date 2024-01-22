import numpy as np

def GramSchmidtOrthogonalize(tangent, normal):
	# Project the tangent vector onto the normal vector
	projection = np.dot(tangent, normal) * normal

	# Subtract the projection from the original tangent to make it orthogonal to the normal
	orthogonal_tangent = tangent - projection

	# Handle degenerated tangents
	norm = np.linalg.norm(orthogonal_tangent)

	if norm == 0:
		normalized_orthogonal_tangent = np.array([normal[1],normal[2],normal[0]])
	else:
		# Normalize the resulting orthogonal tangent
		normalized_orthogonal_tangent = orthogonal_tangent / np.linalg.norm(orthogonal_tangent)

	return normalized_orthogonal_tangent

def Normalize(vec):
	n = np.linalg.norm(np.array(vec))
	if n == 0:
		return vec
	return [v/n for v in vec]

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