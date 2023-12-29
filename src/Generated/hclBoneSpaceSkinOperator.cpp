#include "Generated\hclBoneSpaceSkinOperator.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclBoneSpaceSkinOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceSkinOperator") {
		std::cout << "hclBoneSpaceSkinOperator::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("transformSubset")->GetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->GetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("boneSpaceDeformer")->GetValue(boneSpaceDeformer);
	return true;
}

bool hktypes::hclBoneSpaceSkinOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceSkinOperator") {
		std::cout << "hclBoneSpaceSkinOperator::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("transformSubset")->SetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->SetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("boneSpaceDeformer")->SetValue(boneSpaceDeformer);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceSkinOperator::GetTemplateArgs() { return {
}; };

