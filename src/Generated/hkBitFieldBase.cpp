#include "Generated\hkBitFieldBase.h"

#include "Generated\.h"

template<>
bool hktypes::hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkBitFieldBase::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkBitFieldBase") {
		std::cout << "hkBitFieldBase::FromInstance: Expecting hkBitFieldBase but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkBitFieldBase::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkBitFieldBase") {
		std::cout << "hkBitFieldBase::ToInstance: Expecting hkBitFieldBase but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::GetTemplateArgs() { return {
	{"tStorage", "hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>"},
}; };

