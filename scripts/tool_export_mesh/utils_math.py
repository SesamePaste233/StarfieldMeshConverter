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


def estimate_homography_3d(src_points, dst_points):
	"""
	Estimate the homography matrix from 3D source points to 3D destination points.

	Parameters:
	src_points (numpy.ndarray): Nx3 array of source points in 3D.
	dst_points (numpy.ndarray): Nx3 array of destination points in 3D.

	Returns:
	numpy.ndarray: 4x4 homography matrix.
	"""
	assert src_points.shape == dst_points.shape, "Source and destination points must have the same shape."
	assert src_points.shape[1] == 3, "Points must be 3D."

	num_points = src_points.shape[0]
	if num_points < 5:
		raise ValueError("At least 5 points are required to estimate the homography matrix.")

	# Construct the A matrix
	A = np.zeros((3 * num_points, 16))
	for i in range(num_points):
		x, y, z = src_points[i]
		u, v, w = dst_points[i]

		A[3 * i] = np.array([x, y, z, 1, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0, -u*x, -u*y, -u*z, -u])
		A[3 * i + 1] = np.array([0, 0, 0, 0, x, y, z, 1, 0, 0, 0, 0, -v*x, -v*y, -v*z, -v])
		A[3 * i + 2] = np.array([0, 0, 0, 0, 0, 0, 0, 0, x, y, z, 1, -w*x, -w*y, -w*z, -w])

	# Solve A @ h = 0 using SVD
	_, _, V = np.linalg.svd(A)
	H = V[-1].reshape(4, 4)

	return H

