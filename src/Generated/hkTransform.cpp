#include "Generated\hkTransform.h"

#include "Generated\.h"

bool hktypes::hkTransform::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkTransform") {
		std::cout << "hkTransform::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkTransformf::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hkTransform::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkTransform") {
		std::cout << "hkTransform::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkTransformf::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkTransform::GetTemplateArgs() { return {
}; };

