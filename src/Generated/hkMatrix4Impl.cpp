#include "Generated\hkMatrix4Impl.h"

#include "Generated\.h"

template<>
bool hktypes::hkMatrix4Impl<float>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkMatrix4Impl::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkMatrix4Impl") {
		std::cout << "hkMatrix4Impl::FromInstance: Expecting hkMatrix4Impl but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("col0")->GetValue(col0);
	class_instance->GetInstanceByFieldName("col1")->GetValue(col1);
	class_instance->GetInstanceByFieldName("col2")->GetValue(col2);
	class_instance->GetInstanceByFieldName("col3")->GetValue(col3);
	return true;
}

template<>
bool hktypes::hkMatrix4Impl<float>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkMatrix4Impl::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkMatrix4Impl") {
		std::cout << "hkMatrix4Impl::ToInstance: Expecting hkMatrix4Impl but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("col0")->SetValue(col0);
	class_instance->GetInstanceByFieldName("col1")->SetValue(col1);
	class_instance->GetInstanceByFieldName("col2")->SetValue(col2);
	class_instance->GetInstanceByFieldName("col3")->SetValue(col3);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkMatrix4Impl<float>::GetTemplateArgs() { return {
	{"tFT", "float"},
}; };

