#include "Generated\hkArray.h"

bool hktypes::hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

bool hktypes::hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

inline std::vector<std::string> hktypes::hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	"tT",
	"tAllocator",
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>::GetFieldTypeAndNames() { return {
	{ "T*<void>", { "m_data", 0, 34 } },
	{ "int", { "m_size", 8, 34 } },
	{ "int", { "m_capacityAndFlags", 12, 34 } },
}; };

