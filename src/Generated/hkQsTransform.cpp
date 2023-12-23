#include "Generated\hkQsTransform.h"

#include "Generated\.h"

bool hktypes::hkQsTransform::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkQsTransform") {
		std::cout << "hkQsTransform::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkQsTransformf::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hkQsTransform::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkQsTransform") {
		std::cout << "hkQsTransform::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkQsTransformf::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkQsTransform::GetTemplateArgs() { return {
}; };

