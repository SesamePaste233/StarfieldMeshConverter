#include "Generated\hkHandle.h"


template<>
bool hktypes::hkHandle<hkUint32, 2147483647>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkHandle::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkHandle") {
		std::cout << "hkHandle::FromInstance: Expecting hkHandle but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("value")->GetValue(value);
	return true;
}

template<>
bool hktypes::hkHandle<hkUint32, 2147483647>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkHandle::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkHandle") {
		std::cout << "hkHandle::ToInstance: Expecting hkHandle but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("value")->SetValue(value);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkHandle<hkUint32, 2147483647>::GetTemplateArgs() { return {
	{"tTYPE", "hkUint32"},
	{"vINVALID_VALUE", "2147483647"},
}; };

