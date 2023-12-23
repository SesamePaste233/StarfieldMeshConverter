#include "Generated\hkMatrix3Impl.h"

#include "Generated\.h"

template<>
bool hktypes::hkMatrix3Impl<float>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkMatrix3Impl") {
		std::cout << "hkMatrix3Impl::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("col0")->GetValue(col0);
	class_instance->GetInstanceByFieldName("col1")->GetValue(col1);
	class_instance->GetInstanceByFieldName("col2")->GetValue(col2);
	return true;
}

template<>
bool hktypes::hkMatrix3Impl<float>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkMatrix3Impl") {
		std::cout << "hkMatrix3Impl::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("col0")->SetValue(col0);
	class_instance->GetInstanceByFieldName("col1")->SetValue(col1);
	class_instance->GetInstanceByFieldName("col2")->SetValue(col2);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkMatrix3Impl<float>::GetTemplateArgs() { return {
	{"tFT", "float"},
}; };

