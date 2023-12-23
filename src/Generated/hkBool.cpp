#include "Generated\hkBool.h"


bool hktypes::hkBool::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkBool") {
		std::cout << "hkBool::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("bool")->GetValue(bool);
	return true;
}

bool hktypes::hkBool::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkBool") {
		std::cout << "hkBool::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("bool")->SetValue(bool);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkBool::GetTemplateArgs() { return {
}; };

