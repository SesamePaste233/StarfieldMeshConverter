#include "Generated\hclObjectSpaceSkinOperator.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclObjectSpaceSkinOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceSkinOperator") {
		std::cout << "hclObjectSpaceSkinOperator::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

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

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceSkinOperator") {
		std::cout << "hclObjectSpaceSkinOperator::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("boneFromSkinMeshTransforms")->SetValue(boneFromSkinMeshTransforms);
	class_instance->GetInstanceByFieldName("transformSubset")->SetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->SetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("objectSpaceDeformer")->SetValue(objectSpaceDeformer);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceSkinOperator::GetTemplateArgs() { return {
}; };

