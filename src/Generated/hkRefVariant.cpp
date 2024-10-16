#include "Generated\hkRefVariant.h"


bool hktypes::hkRefVariant::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefVariant::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefVariant") {
		std::cout << "hkRefVariant::FromInstance: Expecting hkRefVariant but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->GetValue(ptr);
	return true;
}

bool hktypes::hkRefVariant::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefVariant::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefVariant") {
		std::cout << "hkRefVariant::ToInstance: Expecting hkRefVariant but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->SetValue(ptr);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefVariant::GetTemplateArgs() { return {
}; };

