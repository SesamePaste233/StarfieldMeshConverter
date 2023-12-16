#include "Generated\hkBitFieldBase.h"

bool hktypes::hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBitFieldBase") {
		std::cout << "hkBitFieldBase::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

bool hktypes::hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBitFieldBase") {
		std::cout << "hkBitFieldBase::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

inline std::vector<std::string> hktypes::hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::GetTemplateArgs() { return {
	"tStorage",
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::GetFieldTypeAndNames() { return {
	{ "hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>", { "storage", 0, 34 } },
}; };

