#include "Generated\hkaBone.h"

bool hktypes::hkaBone::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaBone") {
		std::cout << "hkaBone::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("lockTranslation")->GetValue(lockTranslation);
	return true;
}

bool hktypes::hkaBone::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaBone") {
		std::cout << "hkaBone::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("lockTranslation")->SetValue(lockTranslation);
	return true;
}

inline std::vector<std::string> hktypes::hkaBone::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkaBone::GetFieldTypeAndNames() { return {
	{ "hkStringPtr", { "name", 0, 32 } },
	{ "hkBool", { "lockTranslation", 8, 32 } },
}; };

