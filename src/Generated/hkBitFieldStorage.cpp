#include "Generated\hkBitFieldStorage.h"

#include "Generated\.h"

template<>
bool hktypes::hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkBitFieldStorage") {
		std::cout << "hkBitFieldStorage::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("words")->GetValue(words);
	class_instance->GetInstanceByFieldName("numBits")->GetValue(numBits);
	return true;
}

template<>
bool hktypes::hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkBitFieldStorage") {
		std::cout << "hkBitFieldStorage::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("words")->SetValue(words);
	class_instance->GetInstanceByFieldName("numBits")->SetValue(numBits);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>::GetTemplateArgs() { return {
	{"tStorage", "hkArray<hkUint32, hkContainerHeapAllocator>"},
}; };

