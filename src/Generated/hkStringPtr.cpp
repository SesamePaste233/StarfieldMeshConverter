#include "Generated\hkStringPtr.h"


bool hktypes::hkStringPtr::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkStringPtr::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkStringPtr") {
		std::cout << "hkStringPtr::FromInstance: Expecting hkStringPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("stringAndFlag")->GetValue(stringAndFlag);
	return true;
}

bool hktypes::hkStringPtr::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkStringPtr::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkStringPtr") {
		std::cout << "hkStringPtr::ToInstance: Expecting hkStringPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("stringAndFlag")->SetValue(stringAndFlag);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkStringPtr::GetTemplateArgs() { return {
}; };

