#include "Generated\hkPackedVector3.h"

bool hktypes::hkPackedVector3::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("values")->GetValue(values);
	return true;
}

bool hktypes::hkPackedVector3::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("values")->SetValue(values);
	return true;
}

inline std::vector<std::string> hktypes::hkPackedVector3::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkPackedVector3::GetFieldTypeAndNames() { return {
	{ "T[N]<hkInt16, 4>", { "values", 0, 160 } },
}; };

