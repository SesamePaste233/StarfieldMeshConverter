#include "hkTypes.h"

bool hktypes::hkQsTransform::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hkQsTransformf") {
		std::cout << "hkQsTransform::FromInstance: type_name is not hkQsTransform" << std::endl;
		return false;
	}

	auto t_inst = class_instance->GetArrayByFieldName<double>("translation");
	auto r_inst = class_instance->GetArrayByFieldName<double>("rotation");
	auto s_inst = class_instance->GetArrayByFieldName<double>("scale");

	this->translation = Eigen::Vector4f(t_inst[0], t_inst[1], t_inst[2], t_inst[3]);
	this->rotation = Eigen::Quaternionf(r_inst[0], r_inst[1], r_inst[2], r_inst[3]);
	this->scale = Eigen::Vector4f(s_inst[0], s_inst[1], s_inst[2], s_inst[3]);

	return true;
}

bool hktypes::hkQsTransform::ToInstance(hkreflex::hkClassInstance* instance)
{
	return false;
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
		}
		else {
			bone->parent = bones[parent_index];
			bones[parent_index]->children.push_back(bone);
		}
	}

	return true;
}

bool hktypes::hkaSkeletonHolder::ToInstance(hkreflex::hkClassInstance* instance)
{
	return false;
}
