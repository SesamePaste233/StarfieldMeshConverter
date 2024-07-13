import numpy as np
import mathutils

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

def NormalizeVec(vec):
	vectors = np.array(vec)
	norms = np.linalg.norm(vectors)
	np.divide(vectors, norms, out=vectors, where=norms != 0)
	return vectors

def NormalizeRows(matrix:np.ndarray) -> None:
	norms = np.linalg.norm(matrix, axis=1, keepdims=True)
	np.divide(matrix, norms, out=matrix, where=norms != 0)

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

def bounded_vector_substraction(n0: np.ndarray, nt: np.ndarray) -> np.ndarray:
	'''
	Substracts two vectors while keeping the result in the range of max(abs(result)) <= 1 .
		n0: np.array([x,y,z]) * n_row
		nt: np.array([x,y,z]) * n_row
		return: dn = k * nt - n0 * n_row, s.t. max(abs(dn)) <= 1
	'''
	k_limit = n0/nt + np.abs(1/nt)
	k_limit = np.nan_to_num(k_limit, nan = 1)
	k_limit = np.hstack((k_limit, np.ones((k_limit.shape[0], 1))))

	k = np.min(k_limit, axis=1)

	dn = k[:, np.newaxis] * nt - n0

	return dn

def batch_rotation_matrices(vec1_stack:np.ndarray, vec2_stack:np.ndarray):
    """
    Compute rotation matrices that align each pair of vectors from vec1_stack to vec2_stack.
    
    :param vec1_stack: An array of shape (N, 3) representing N source vectors.
    :param vec2_stack: An array of shape (N, 3) representing N destination vectors.
    :return: An array of shape (N, 3, 3) containing the rotation matrices.
    """
    assert vec1_stack.shape == vec2_stack.shape, "Input stacks must have the same shape."
    assert vec1_stack.shape[1] == 3, "Each vector must be 3-dimensional."
    
    num_vectors = vec1_stack.shape[0]
    
    vs = np.cross(vec1_stack, vec2_stack)
    cs = np.einsum('ij,ij->i', vec1_stack, vec2_stack)
    ss = np.linalg.norm(vs, axis=1)

    # Compute the skew-symmetric cross-product matrix
    kmat = np.zeros((num_vectors, 3, 3))
    kmat[:, 0, 1] = -vs[:, 2]
    kmat[:, 0, 2] = vs[:, 1]
    kmat[:, 1, 0] = vs[:, 2]
    kmat[:, 1, 2] = -vs[:, 0]
    kmat[:, 2, 0] = -vs[:, 1]
    kmat[:, 2, 1] = vs[:, 0]
    
    # Compute the rotation matrix
    mask = ss != 0
    R = np.eye(3)[np.newaxis].repeat(num_vectors, axis=0)

    masked_kmat = kmat[mask]
    dot_kmat = np.einsum('ijk,ikl->ijl', masked_kmat, masked_kmat)
    multiplier = ((1 - cs[mask]) / (ss[mask] ** 2))[..., np.newaxis, np.newaxis]
    R[mask] += masked_kmat + dot_kmat * multiplier
    return R

def apply_mat_to_all(matrix:mathutils.Matrix, vectors:np.ndarray) -> np.ndarray:
	"""Given matrix m and vectors [v1,v2,...], computes [m@v1,m@v2,...]"""
	# Linear part
	m = matrix.to_3x3() if len(matrix) == 4 else matrix
	res = np.matmul(vectors, np.array(m.transposed()))
	# Translation part
	if len(matrix) == 4:
		res += np.array(matrix.translation)
	return res