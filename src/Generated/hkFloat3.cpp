#include "Generated\hkFloat3.h"


bool hktypes::hkFloat3::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkFloat3::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkFloat3") {
		std::cout << "hkFloat3::FromInstance: Expecting hkFloat3 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("x")->GetValue(x);
	class_instance->GetInstanceByFieldName("y")->GetValue(y);
	class_instance->GetInstanceByFieldName("z")->GetValue(z);
	return true;
}

bool hktypes::hkFloat3::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkFloat3::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkFloat3") {
		std::cout << "hkFloat3::ToInstance: Expecting hkFloat3 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("x")->SetValue(x);
	class_instance->GetInstanceByFieldName("y")->SetValue(y);
	class_instance->GetInstanceByFieldName("z")->SetValue(z);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkFloat3::GetTemplateArgs() { return {
}; };

