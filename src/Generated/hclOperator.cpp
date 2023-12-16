#include "Generated\hclOperator.h"

bool hktypes::hclOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclOperator") {
		std::cout << "hclOperator::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("operatorID")->GetValue(operatorID);
	class_instance->GetInstanceByFieldName("type")->GetValue(type);
	class_instance->GetInstanceByFieldName("usedBuffers")->GetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->GetValue(usedTransformSets);
	return true;
}

bool hktypes::hclOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclOperator") {
		std::cout << "hclOperator::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("operatorID")->SetValue(operatorID);
	class_instance->GetInstanceByFieldName("type")->SetValue(type);
	class_instance->GetInstanceByFieldName("usedBuffers")->SetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->SetValue(usedTransformSets);
	return true;
}

inline std::vector<std::string> hktypes::hclOperator::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclOperator::GetFieldTypeAndNames() { return {
	{ "hkStringPtr", { "name", 24, 32 } },
	{ "unsigned int", { "operatorID", 32, 32 } },
	{ "unsigned int", { "type", 36, 33 } },
	{ "hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator>", { "usedBuffers", 40, 32 } },
	{ "hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator>", { "usedTransformSets", 56, 32 } },
}; };

