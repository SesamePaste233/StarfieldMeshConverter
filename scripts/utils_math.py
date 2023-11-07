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
	n = np.linalg.norm(vec)
	if n == 0:
		return vec
	return vec / n