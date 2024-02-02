#include "Generated\hkAabb.h"

#include "Generated\.h"

bool hktypes::hkAabb::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkAabb") {
		std::cout << "hkAabb::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("min")->GetValue(min);
	class_instance->GetInstanceByFieldName("max")->GetValue(max);
	return true;
}

bool hktypes::hkAabb::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkAabb") {
		std::cout << "hkAabb::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("min")->SetValue(min);
	class_instance->GetInstanceByFieldName("max")->SetValue(max);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkAabb::GetTemplateArgs() { return {
}; };

