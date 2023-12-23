#include "Generated\hkRotationImpl.h"

#include "Generated\.h"

template<>
bool hktypes::hkRotationImpl<float>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkRotationImpl") {
		std::cout << "hkRotationImpl::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkMatrix3Impl<float>::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

template<>
bool hktypes::hkRotationImpl<float>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkRotationImpl") {
		std::cout << "hkRotationImpl::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkMatrix3Impl<float>::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRotationImpl<float>::GetTemplateArgs() { return {
	{"tFT", "float"},
}; };

