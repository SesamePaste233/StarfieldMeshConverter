#include "Generated\hclObjectSpaceSkinOperator.h"

bool hktypes::hclObjectSpaceSkinOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceSkinOperator") {
		std::cout << "hclObjectSpaceSkinOperator::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("boneFromSkinMeshTransforms")->GetValue(boneFromSkinMeshTransforms);
	class_instance->GetInstanceByFieldName("transformSubset")->GetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->GetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("objectSpaceDeformer")->GetValue(objectSpaceDeformer);
	return true;
}

bool hktypes::hclObjectSpaceSkinOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceSkinOperator") {
		std::cout << "hclObjectSpaceSkinOperator::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("boneFromSkinMeshTransforms")->SetValue(boneFromSkinMeshTransforms);
	class_instance->GetInstanceByFieldName("transformSubset")->SetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->SetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("objectSpaceDeformer")->SetValue(objectSpaceDeformer);
	return true;
}

inline std::vector<std::string> hktypes::hclObjectSpaceSkinOperator::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceSkinOperator::GetFieldTypeAndNames() { return {
	{ "hkArray<hkMatrix4, hkContainerHeapAllocator>", { "boneFromSkinMeshTransforms", 72, 32 } },
	{ "hkArray<hkUint16, hkContainerHeapAllocator>", { "transformSubset", 88, 32 } },
	{ "hkUint32", { "outputBufferIndex", 104, 32 } },
	{ "hkUint32", { "transformSetIndex", 108, 32 } },
	{ "hclObjectSpaceDeformer", { "objectSpaceDeformer", 112, 32 } },
}; };

