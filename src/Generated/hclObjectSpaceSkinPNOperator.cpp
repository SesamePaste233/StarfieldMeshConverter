#include "Generated\hclObjectSpaceSkinPNOperator.h"

bool hktypes::hclObjectSpaceSkinPNOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceSkinPNOperator") {
		std::cout << "hclObjectSpaceSkinPNOperator::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclObjectSpaceSkinOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("localPNs")->GetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->GetValue(localUnpackedPNs);
	return true;
}

bool hktypes::hclObjectSpaceSkinPNOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceSkinPNOperator") {
		std::cout << "hclObjectSpaceSkinPNOperator::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclObjectSpaceSkinOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("localPNs")->SetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->SetValue(localUnpackedPNs);
	return true;
}

inline std::vector<std::string> hktypes::hclObjectSpaceSkinPNOperator::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceSkinPNOperator::GetFieldTypeAndNames() { return {
	{ "hkArray<hclObjectSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator>", { "localPNs", 264, 32 } },
	{ "hkArray<hclObjectSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator>", { "localUnpackedPNs", 280, 32 } },
}; };

