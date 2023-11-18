#pragma once
#include <Eigen/Dense>

namespace utils {
	namespace xf {
		Eigen::Matrix4f createTransformationMatrix(const Eigen::Matrix3f& R, const Eigen::Vector3f& t, float s);

		Eigen::Matrix4f createTransformationMatrix(const float R[3][3], const float t[3]);

		Eigen::Matrix4f createTransformationMatrix(const float R[3][3]);

		Eigen::Matrix4f createTransformationMatrix(const float t[3]);

		Eigen::Matrix4f createTransformationMatrix(const float s);

		Eigen::Vector4f fromTransform(const float t[3]);

		std::pair<Eigen::Vector3f, Eigen::Vector3f> toAxis(Eigen::Matrix4f& Trans, float length = 1);

		Eigen::Matrix4f toAxis(Eigen::Matrix4f& Trans, Eigen::Matrix4f& old_axis);

		void decomposeTransformation(const Eigen::Matrix4f& T_4x4, Eigen::Matrix4f& R_4x4, Eigen::Matrix4f& t_4x4);

		Eigen::Matrix4f quickInverse(const Eigen::Matrix4f& T);
	}
}