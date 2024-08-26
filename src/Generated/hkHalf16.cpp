#include "Generated\hkHalf16.h"


bool hktypes::hkHalf16::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkHalf16::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkHalf16") {
		std::cout << "hkHalf16::FromInstance: Expecting hkHalf16 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("value")->GetValue(value);
	return true;
}

bool hktypes::hkHalf16::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkHalf16::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkHalf16") {
		std::cout << "hkHalf16::ToInstance: Expecting hkHalf16 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("value")->SetValue(value);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkHalf16::GetTemplateArgs() { return {
}; };

