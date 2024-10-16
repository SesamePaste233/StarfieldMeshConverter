#include "Generated\hclSimpleMeshBoneDeformOperator.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclSimpleMeshBoneDeformOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclSimpleMeshBoneDeformOperator::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator") {
		std::cout << "hclSimpleMeshBoneDeformOperator::FromInstance: Expecting hclSimpleMeshBoneDeformOperator but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("inputBufferIdx")->GetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputTransformSetIdx")->GetValue(outputTransformSetIdx);
	class_instance->GetInstanceByFieldName("triangleBonePairs")->GetValue(triangleBonePairs);
	class_instance->GetInstanceByFieldName("localBoneTransforms")->GetValue(localBoneTransforms);
	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclSimpleMeshBoneDeformOperator::TriangleBonePair::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator::TriangleBonePair") {
		std::cout << "hclSimpleMeshBoneDeformOperator::TriangleBonePair::FromInstance: Expecting hclSimpleMeshBoneDeformOperator::TriangleBonePair but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("boneOffset")->GetValue(boneOffset);
	class_instance->GetInstanceByFieldName("triangleOffset")->GetValue(triangleOffset);
	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclSimpleMeshBoneDeformOperator::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator") {
		std::cout << "hclSimpleMeshBoneDeformOperator::ToInstance: Expecting hclSimpleMeshBoneDeformOperator but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("inputBufferIdx")->SetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputTransformSetIdx")->SetValue(outputTransformSetIdx);
	class_instance->GetInstanceByFieldName("triangleBonePairs")->SetValue(triangleBonePairs);
	class_instance->GetInstanceByFieldName("localBoneTransforms")->SetValue(localBoneTransforms);
	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclSimpleMeshBoneDeformOperator::TriangleBonePair::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator::TriangleBonePair") {
		std::cout << "hclSimpleMeshBoneDeformOperator::TriangleBonePair::ToInstance: Expecting hclSimpleMeshBoneDeformOperator::TriangleBonePair but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("boneOffset")->SetValue(boneOffset);
	class_instance->GetInstanceByFieldName("triangleOffset")->SetValue(triangleOffset);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimpleMeshBoneDeformOperator::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::GetTemplateArgs() { return {
}; };

