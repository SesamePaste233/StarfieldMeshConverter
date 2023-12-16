#include "Generated\hclSimpleMeshBoneDeformOperator.h"

bool hktypes::hclSimpleMeshBoneDeformOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator") {
		std::cout << "hclSimpleMeshBoneDeformOperator::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("inputBufferIdx")->GetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputTransformSetIdx")->GetValue(outputTransformSetIdx);
	class_instance->GetInstanceByFieldName("triangleBonePairs")->GetValue(triangleBonePairs);
	class_instance->GetInstanceByFieldName("localBoneTransforms")->GetValue(localBoneTransforms);
	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator::TriangleBonePair") {
		std::cout << "hclSimpleMeshBoneDeformOperator::TriangleBonePair::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("boneOffset")->GetValue(boneOffset);
	class_instance->GetInstanceByFieldName("triangleOffset")->GetValue(triangleOffset);
	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator") {
		std::cout << "hclSimpleMeshBoneDeformOperator::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("inputBufferIdx")->SetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputTransformSetIdx")->SetValue(outputTransformSetIdx);
	class_instance->GetInstanceByFieldName("triangleBonePairs")->SetValue(triangleBonePairs);
	class_instance->GetInstanceByFieldName("localBoneTransforms")->SetValue(localBoneTransforms);
	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator::TriangleBonePair") {
		std::cout << "hclSimpleMeshBoneDeformOperator::TriangleBonePair::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("boneOffset")->SetValue(boneOffset);
	class_instance->GetInstanceByFieldName("triangleOffset")->SetValue(triangleOffset);
	return true;
}

inline std::vector<std::string> hktypes::hclSimpleMeshBoneDeformOperator::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclSimpleMeshBoneDeformOperator::GetFieldTypeAndNames() { return {
	{ "hkUint32", { "inputBufferIdx", 72, 32 } },
	{ "hkUint32", { "outputTransformSetIdx", 76, 32 } },
	{ "hkArray<hclSimpleMeshBoneDeformOperator::TriangleBonePair, hkContainerHeapAllocator>", { "triangleBonePairs", 80, 32 } },
	{ "hkArray<hkMatrix4, hkContainerHeapAllocator>", { "localBoneTransforms", 96, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::GetFieldTypeAndNames() { return {
	{ "hkUint16", { "boneOffset", 0, 32 } },
	{ "hkUint16", { "triangleOffset", 2, 32 } },
}; };

