#include "Generated\hclVolumeConstraint.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclVolumeConstraint::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVolumeConstraint") {
		std::cout << "hclVolumeConstraint::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("frameDatas")->GetValue(frameDatas);
	class_instance->GetInstanceByFieldName("applyDatas")->GetValue(applyDatas);
	return true;
}

bool hktypes::hclVolumeConstraint::FrameData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVolumeConstraint::FrameData") {
		std::cout << "hclVolumeConstraint::FrameData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("frameVector")->GetValue(frameVector);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	class_instance->GetInstanceByFieldName("weight")->GetValue(weight);
	return true;
}

bool hktypes::hclVolumeConstraint::ApplyData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVolumeConstraint::ApplyData") {
		std::cout << "hclVolumeConstraint::ApplyData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("frameVector")->GetValue(frameVector);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	class_instance->GetInstanceByFieldName("stiffness")->GetValue(stiffness);
	return true;
}

bool hktypes::hclVolumeConstraint::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVolumeConstraint") {
		std::cout << "hclVolumeConstraint::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("frameDatas")->SetValue(frameDatas);
	class_instance->GetInstanceByFieldName("applyDatas")->SetValue(applyDatas);
	return true;
}

bool hktypes::hclVolumeConstraint::FrameData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVolumeConstraint::FrameData") {
		std::cout << "hclVolumeConstraint::FrameData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("frameVector")->SetValue(frameVector);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	class_instance->GetInstanceByFieldName("weight")->SetValue(weight);
	return true;
}

bool hktypes::hclVolumeConstraint::ApplyData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVolumeConstraint::ApplyData") {
		std::cout << "hclVolumeConstraint::ApplyData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("frameVector")->SetValue(frameVector);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(stiffness);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVolumeConstraint::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVolumeConstraint::FrameData::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVolumeConstraint::ApplyData::GetTemplateArgs() { return {
}; };

