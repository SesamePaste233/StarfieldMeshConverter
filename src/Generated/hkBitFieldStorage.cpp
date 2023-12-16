#include "Generated\hkBitFieldStorage.h"

bool hktypes::hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBitFieldStorage") {
		std::cout << "hkBitFieldStorage::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("words")->GetValue(words);
	class_instance->GetInstanceByFieldName("numBits")->GetValue(numBits);
	return true;
}

bool hktypes::hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBitFieldStorage") {
		std::cout << "hkBitFieldStorage::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("words")->SetValue(words);
	class_instance->GetInstanceByFieldName("numBits")->SetValue(numBits);
	return true;
}

inline std::vector<std::string> hktypes::hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>::GetTemplateArgs() { return {
	"tStorage",
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>::GetFieldTypeAndNames() { return {
	{ "hkArray<hkUint32, hkContainerHeapAllocator>", { "words", 0, 32 } },
	{ "int", { "numBits", 16, 32 } },
}; };

