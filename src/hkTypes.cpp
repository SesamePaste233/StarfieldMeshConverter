#include "hkTypes.h"

bool hktypes::hkQsTransform::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hkQsTransformf") {
		std::cout << "hkQsTransform::FromInstance: type_name is not hkQsTransformf" << std::endl;
		return false;
	}

	auto t_inst = class_instance->GetArrayByFieldName<double>("translation");
	auto r_inst = class_instance->GetArrayByFieldName<double>("rotation");
	auto s_inst = class_instance->GetArrayByFieldName<double>("scale");

	this->translation = Eigen::Vector4f(t_inst[0], t_inst[1], t_inst[2], t_inst[3]);
	this->rotation = Eigen::Quaternionf(r_inst[3], r_inst[0], r_inst[1], r_inst[2]);
	this->scale = Eigen::Vector4f(s_inst[0], s_inst[1], s_inst[2], s_inst[3]);

	return true;
}

bool hktypes::hkQsTransform::ToInstance(hkreflex::hkClassInstance* instance)
{
	return false;
}

Eigen::Matrix4f hktypes::hkQsTransform::getMatrix(bool force_M44_1)
{
	Eigen::Matrix4f result;
	result.setIdentity();
	result.block<3, 3>(0, 0) = this->rotation.toRotationMatrix();
	result.block<4, 1>(0, 3) = this->translation.block<4, 1>(0, 0);

	if (force_M44_1) {
		result(3, 3) = 1.0f;
	}

	return result;
}

Eigen::Vector4f hktypes::hkQsTransform::getRotatedDir(Eigen::Vector4f& dir, Eigen::Quaternionf& rot)
{
	Eigen::Vector4f result;
	// Extract the scalar (real) part of the quaternion
	float qreal = rot.w();

	// Calculate q^2 - 0.5
	float q2minus1 = qreal * qreal - 0.5f;

	// Calculate the contribution of the imaginary part of the quaternion
	result = dir * q2minus1;

	// Calculate the dot product of the imaginary part of the quaternion and the direction vector
	float imagDotDir = rot.vec().dot(dir.head<3>());

	// Add the contribution of the cross product of the imaginary part and the direction vector
	result.head<3>() += rot.vec() * imagDotDir;

	// Calculate the cross product of the imaginary part and the direction vector
	Eigen::Vector3f imagCrossDir = rot.vec().cross(dir.head<3>());

	// Add the contribution of the cross product multiplied by the scalar part of the quaternion
	result.head<3>() += imagCrossDir * qreal;

	// The fourth component remains unchanged
	return result + result;
}

hktypes::hkQsTransform hktypes::hkQsTransform::fromMultiplied(hkQsTransform& a, hkQsTransform& b)
{
	hkQsTransform result;
	result.translation = a.translation + getRotatedDir(b.translation, a.rotation);
	result.rotation = a.rotation * b.rotation;
	result.scale = a.scale.cwiseProduct(b.scale);
	return result;
}

bool hktypes::hkaBoneHolder::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaBone") {
		std::cout << "hkaBoneHolder::FromInstance: type_name is not hkaBone" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");
	this->lock_translation = class_instance->GetBoolByFieldName("lockTranslation");

	return true;
}

bool hktypes::hkaBoneHolder::ToInstance(hkreflex::hkClassInstance* instance)
{
	return false;
}

bool hktypes::hkaSkeletonHolder::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaSkeleton") {
		std::cout << "hkaSkeletonHolder::FromInstance: type_name is not hkaSkeleton" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");

	auto parent_indices = class_instance->GetArrayByFieldName<int16_t>("parentIndices");

	auto bones_v = class_instance->GetArrayByFieldName<hkaBoneHolder>("bones");

	auto reference_pose = class_instance->GetArrayByFieldName<hkQsTransform>("referencePose");

	std::vector<hkaBoneHolder*> bones;

	for (int i = 0; i < bones_v.size(); i++) {
		auto b_ptr = new hkaBoneHolder(bones_v[i]);
		b_ptr->transform = reference_pose[i];
		bones.push_back(b_ptr);
	}

	for (int i = 0; i < bones.size(); ++i) {
		auto bone = bones[i];
		auto parent_index = parent_indices[i];
		if (parent_index == -1) {
			this->root = bone;
			bone->world_transform = bone->transform;
		}
		else {
			bone->parent = bones[parent_index];
			bones[parent_index]->children.push_back(bone);
			bone->world_transform = hktypes::hkQsTransform::fromMultiplied(bone->parent->world_transform, bone->transform);
		}
	}

	return true;
}

bool hktypes::hkaSkeletonHolder::ToInstance(hkreflex::hkClassInstance* instance)
{
	return false;
}

void hktypes::hkaSkeletonHolder::TraverseBones(std::function<void(hkaBoneHolder*)> pre_order_func, std::function<void(hkaBoneHolder*)> post_order_func = [](hkaBoneHolder*)->void {})
{
	std::function<void(hkaBoneHolder*)> traverse = [&](hkaBoneHolder* bone) {
		pre_order_func(bone);
		for (auto child : bone->children) {
			traverse(child);
		}
		post_order_func(bone);
	};

	traverse(this->root);
}

nlohmann::json hktypes::hkaSkeletonHolder::ToJson(hkaBoneHolder* cur_bone)
{
	if (cur_bone == nullptr) {
		cur_bone = this->root;
	}
	nlohmann::json serialized;

	serialized["name"] = cur_bone->name;
	serialized["lock_translation"] = cur_bone->lock_translation;

	auto matrix = cur_bone->world_transform.getMatrix(true);

	auto rtn = utils::xf::toAxis(matrix, 0.07);

	serialized["head"].push_back(rtn.first.x());
	serialized["head"].push_back(rtn.first.y());
	serialized["head"].push_back(rtn.first.z());
	serialized["tail"].push_back(rtn.second.x());
	serialized["tail"].push_back(rtn.second.y());
	serialized["tail"].push_back(rtn.second.z());
	for (int i = 0; i < 4; ++i) {
		serialized["matrix"].push_back(nlohmann::json::array());
		for (int j = 0; j < 4; ++j) {
			serialized["matrix"][i].push_back(matrix(i, j));
		}
	}

	for (auto child : cur_bone->children) {
		if (child == nullptr) {
			continue;
		}
		serialized["children"].push_back(ToJson(child));
	}

	return serialized;
}
