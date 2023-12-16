#include "Generated\hkQsTransformf.h"

bool hktypes::hkQsTransformf::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkQsTransformf") {
		std::cout << "hkQsTransformf::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("translation")->GetValue(translation);
	class_instance->GetInstanceByFieldName("rotation")->GetValue(rotation);
	class_instance->GetInstanceByFieldName("scale")->GetValue(scale);
	return true;
}

bool hktypes::hkQsTransformf::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkQsTransformf") {
		std::cout << "hkQsTransformf::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("translation")->SetValue(translation);
	class_instance->GetInstanceByFieldName("rotation")->SetValue(rotation);
	class_instance->GetInstanceByFieldName("scale")->SetValue(scale);
	return true;
}

inline std::vector<std::string> hktypes::hkQsTransformf::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkQsTransformf::GetFieldTypeAndNames() { return {
	{ "hkVector4f", { "translation", 0, 32 } },
	{ "hkQuaternionf", { "rotation", 16, 32 } },
	{ "hkVector4f", { "scale", 32, 32 } },
}; };

