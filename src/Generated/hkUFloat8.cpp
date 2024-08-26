#include "Generated\hkUFloat8.h"


bool hktypes::hkUFloat8::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkUFloat8::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkUFloat8") {
		std::cout << "hkUFloat8::FromInstance: Expecting hkUFloat8 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("value")->GetValue(value);
	return true;
}

bool hktypes::hkUFloat8::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkUFloat8::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkUFloat8") {
		std::cout << "hkUFloat8::ToInstance: Expecting hkUFloat8 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("value")->SetValue(value);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkUFloat8::GetTemplateArgs() { return {
}; };

