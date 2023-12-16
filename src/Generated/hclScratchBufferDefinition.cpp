#include "Generated\hclScratchBufferDefinition.h"

bool hktypes::hclScratchBufferDefinition::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclScratchBufferDefinition") {
		std::cout << "hclScratchBufferDefinition::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclBufferDefinition::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("triangleIndices")->GetValue(triangleIndices);
	class_instance->GetInstanceByFieldName("storeNormals")->GetValue(storeNormals);
	class_instance->GetInstanceByFieldName("storeTangentsAndBiTangents")->GetValue(storeTangentsAndBiTangents);
	return true;
}

bool hktypes::hclScratchBufferDefinition::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclScratchBufferDefinition") {
		std::cout << "hclScratchBufferDefinition::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclBufferDefinition::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("triangleIndices")->SetValue(triangleIndices);
	class_instance->GetInstanceByFieldName("storeNormals")->SetValue(storeNormals);
	class_instance->GetInstanceByFieldName("storeTangentsAndBiTangents")->SetValue(storeTangentsAndBiTangents);
	return true;
}

inline std::vector<std::string> hktypes::hclScratchBufferDefinition::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclScratchBufferDefinition::GetFieldTypeAndNames() { return {
	{ "hkArray<hkUint16, hkContainerHeapAllocator>", { "triangleIndices", 88, 32 } },
	{ "hkBool", { "storeNormals", 104, 32 } },
	{ "hkBool", { "storeTangentsAndBiTangents", 105, 32 } },
}; };

