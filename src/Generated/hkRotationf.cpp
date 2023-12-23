#include "Generated\hkRotationf.h"

#include "Generated\.h"

bool hktypes::hkRotationf::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkRotationf") {
		std::cout << "hkRotationf::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkRotationImpl<float>::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hkRotationf::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkRotationf") {
		std::cout << "hkRotationf::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkRotationImpl<float>::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkRotationf::GetTemplateArgs() { return {
}; };

