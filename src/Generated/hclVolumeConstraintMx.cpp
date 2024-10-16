#include "Generated\hclVolumeConstraintMx.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclVolumeConstraintMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVolumeConstraintMx::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVolumeConstraintMx") {
		std::cout << "hclVolumeConstraintMx::FromInstance: Expecting hclVolumeConstraintMx but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("frameBatchDatas")->GetValue(frameBatchDatas);
	class_instance->GetInstanceByFieldName("applyBatchDatas")->GetValue(applyBatchDatas);
	return true;
}

bool hktypes::hclVolumeConstraintMx::FrameBatchData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVolumeConstraintMx::FrameBatchData::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVolumeConstraintMx::FrameBatchData") {
		std::cout << "hclVolumeConstraintMx::FrameBatchData::FromInstance: Expecting hclVolumeConstraintMx::FrameBatchData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("frameVector")->GetValue(frameVector);
	class_instance->GetInstanceByFieldName("weight")->GetValue(weight);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	return true;
}

bool hktypes::hclVolumeConstraintMx::ApplyBatchData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVolumeConstraintMx::ApplyBatchData::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVolumeConstraintMx::ApplyBatchData") {
		std::cout << "hclVolumeConstraintMx::ApplyBatchData::FromInstance: Expecting hclVolumeConstraintMx::ApplyBatchData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("frameVector")->GetValue(frameVector);
	class_instance->GetInstanceByFieldName("stiffness")->GetValue(stiffness);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	return true;
}

bool hktypes::hclVolumeConstraintMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVolumeConstraintMx::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVolumeConstraintMx") {
		std::cout << "hclVolumeConstraintMx::ToInstance: Expecting hclVolumeConstraintMx but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("frameBatchDatas")->SetValue(frameBatchDatas);
	class_instance->GetInstanceByFieldName("applyBatchDatas")->SetValue(applyBatchDatas);
	return true;
}

bool hktypes::hclVolumeConstraintMx::FrameBatchData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVolumeConstraintMx::FrameBatchData::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVolumeConstraintMx::FrameBatchData") {
		std::cout << "hclVolumeConstraintMx::FrameBatchData::ToInstance: Expecting hclVolumeConstraintMx::FrameBatchData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("frameVector")->SetValue(frameVector);
	class_instance->GetInstanceByFieldName("weight")->SetValue(weight);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	return true;
}

bool hktypes::hclVolumeConstraintMx::ApplyBatchData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVolumeConstraintMx::ApplyBatchData::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVolumeConstraintMx::ApplyBatchData") {
		std::cout << "hclVolumeConstraintMx::ApplyBatchData::ToInstance: Expecting hclVolumeConstraintMx::ApplyBatchData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("frameVector")->SetValue(frameVector);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(stiffness);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVolumeConstraintMx::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVolumeConstraintMx::FrameBatchData::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVolumeConstraintMx::ApplyBatchData::GetTemplateArgs() { return {
}; };

