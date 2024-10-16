#include "Generated\hclScratchBufferDefinition.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclScratchBufferDefinition::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclScratchBufferDefinition::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclScratchBufferDefinition") {
		std::cout << "hclScratchBufferDefinition::FromInstance: Expecting hclScratchBufferDefinition but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclBufferDefinition::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("triangleIndices")->GetValue(triangleIndices);
	class_instance->GetInstanceByFieldName("storeNormals")->GetValue(storeNormals);
	class_instance->GetInstanceByFieldName("storeTangentsAndBiTangents")->GetValue(storeTangentsAndBiTangents);
	return true;
}

bool hktypes::hclScratchBufferDefinition::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclScratchBufferDefinition::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclScratchBufferDefinition") {
		std::cout << "hclScratchBufferDefinition::ToInstance: Expecting hclScratchBufferDefinition but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclBufferDefinition::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("triangleIndices")->SetValue(triangleIndices);
	class_instance->GetInstanceByFieldName("storeNormals")->SetValue(storeNormals);
	class_instance->GetInstanceByFieldName("storeTangentsAndBiTangents")->SetValue(storeTangentsAndBiTangents);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclScratchBufferDefinition::GetTemplateArgs() { return {
}; };

