#include "xfUtils.h"

Eigen::Matrix4f utils::xf::createTransformationMatrix(const Eigen::Matrix3f& R, const Eigen::Vector3f& t, float s)
{
	Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

	// Fill in the upper-left 3x3 submatrix with the rotation matrix
	T_4x4.block(0, 0, 3, 3) = R;

	// Fill in the rightmost column with the translation vector and scaling
	T_4x4(0, 3) = t.x();
	T_4x4(1, 3) = t.y();
	T_4x4(2, 3) = t.z();

	// Apply scaling in the diagonal elements
	T_4x4(0, 0) *= s;
	T_4x4(1, 1) *= s;
	T_4x4(2, 2) *= s;

	return T_4x4;
}

Eigen::Matrix4f utils::xf::createTransformationMatrix(const float R[3][3], const float t[3])
{
	Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

	// Fill in the upper-left 3x3 submatrix with the rotation matrix
	T_4x4.block(0, 0, 3, 3) <<
		R[0][0], R[0][1], R[0][2],
		R[1][0], R[1][1], R[1][2],
		R[2][0], R[2][1], R[2][2];

	// Fill in the rightmost column with the translation vector and scaling
	T_4x4(0, 3) = t[0];
	T_4x4(1, 3) = t[1];
	T_4x4(2, 3) = t[2];

	return T_4x4;
}

Eigen::Matrix4f utils::xf::createTransformationMatrix(const float R[3][3])
{
	Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

	// Fill in the upper-left 3x3 submatrix with the rotation matrix
	T_4x4.block(0, 0, 3, 3) <<
		R[0][0], R[0][1], R[0][2],
		R[1][0], R[1][1], R[1][2],
		R[2][0], R[2][1], R[2][2];


	return T_4x4;
}

Eigen::Matrix4f utils::xf::createTransformationMatrix(const float t[3])
{
	Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

	// Fill in the rightmost column with the translation vector and scaling
	T_4x4(0, 3) = t[0];
	T_4x4(1, 3) = t[1];
	T_4x4(2, 3) = t[2];


	return T_4x4;
}

Eigen::Matrix4f utils::xf::createTransformationMatrix(const float s)
{
	Eigen::Matrix4f T_4x4 = Eigen::Matrix4f::Identity();

	// Apply scaling in the diagonal elements
	T_4x4(0, 0) *= s;
	T_4x4(1, 1) *= s;
	T_4x4(2, 2) *= s;

	return T_4x4;
}

Eigen::Vector4f utils::xf::fromTransform(const float t[3])
{
	Eigen::Vector4f T_4x4 = Eigen::Vector4f::Zero();

	// Fill in the rightmost column with the translation vector and scaling
	T_4x4(0) = t[0];
	T_4x4(1) = t[1];
	T_4x4(2) = t[2];
	T_4x4(3) = 1;

	return T_4x4;
}

std::pair<Eigen::Vector3f, Eigen::Vector3f> utils::xf::toAxis(Eigen::Matrix4f& Trans, float length)
{
	Eigen::Vector4f start_point_homogeneous(0, 0, 0, 1);
	Eigen::Vector4f end_point_homogeneous(0, 0, length, 1);

	// Transform the start and end points
	Eigen::Vector4f transformed_start_point = Trans * start_point_homogeneous;
	Eigen::Vector4f transformed_end_point = Trans * end_point_homogeneous;

	// Convert from homogeneous coordinates to 3D Cartesian coordinates
	Eigen::Vector3f transformed_start_3d = transformed_start_point.hnormalized();
	Eigen::Vector3f transformed_end_3d = transformed_end_point.hnormalized();

	return std::make_pair(transformed_start_3d, transformed_end_3d);
}

Eigen::Matrix4f utils::xf::toAxis(Eigen::Matrix4f& Trans, Eigen::Matrix4f& old_axis)
{
	return Trans * old_axis;
}

void utils::xf::decomposeTransformation(const Eigen::Matrix4f& T_4x4, Eigen::Matrix4f& R_4x4, Eigen::Matrix4f& t_4x4)
{
	// Create 4x4 matrices for R_4x4 and t_4x4
	R_4x4.setIdentity();
	R_4x4.block(0, 0, 3, 3) = T_4x4.block(0, 0, 3, 3);

	t_4x4.setIdentity();
	t_4x4.block(0, 3, 3, 1) = T_4x4.block(0, 3, 3, 1);

}

Eigen::Matrix4f utils::xf::quickInverse(const Eigen::Matrix4f& T)
{
	Eigen::Matrix4f T_inv = Eigen::Matrix4f::Identity();
	T_inv.block(0, 0, 3, 3) = T.block(0, 0, 3, 3).transpose();
	T_inv.block(0, 3, 3, 1) = -T_inv.block(0, 0, 3, 3) * T.block(0, 3, 3, 1);
	T_inv(3, 3) = 1;
	return T_inv;
}

