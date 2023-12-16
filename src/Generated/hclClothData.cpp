#include "Generated\hclClothData.h"

bool hktypes::hclClothData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothData") {
		std::cout << "hclClothData::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("simClothDatas")->GetValue(simClothDatas);
	class_instance->GetInstanceByFieldName("bufferDefinitions")->GetValue(bufferDefinitions);
	class_instance->GetInstanceByFieldName("transformSetDefinitions")->GetValue(transformSetDefinitions);
	class_instance->GetInstanceByFieldName("operators")->GetValue(operators);
	class_instance->GetInstanceByFieldName("clothStateDatas")->GetValue(clothStateDatas);
	class_instance->GetInstanceByFieldName("stateTransitions")->GetValue(stateTransitions);
	class_instance->GetInstanceByFieldName("actions")->GetValue(actions);
	class_instance->GetInstanceByFieldName("generatedAtRuntime")->GetValue(generatedAtRuntime);
	class_instance->GetInstanceByFieldName("targetPlatform")->GetValue(targetPlatform);
	return true;
}

bool hktypes::hclClothData::Platform::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothData::Platform") {
		std::cout << "hclClothData::Platform::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclClothData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothData") {
		std::cout << "hclClothData::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("simClothDatas")->SetValue(simClothDatas);
	class_instance->GetInstanceByFieldName("bufferDefinitions")->SetValue(bufferDefinitions);
	class_instance->GetInstanceByFieldName("transformSetDefinitions")->SetValue(transformSetDefinitions);
	class_instance->GetInstanceByFieldName("operators")->SetValue(operators);
	class_instance->GetInstanceByFieldName("clothStateDatas")->SetValue(clothStateDatas);
	class_instance->GetInstanceByFieldName("stateTransitions")->SetValue(stateTransitions);
	class_instance->GetInstanceByFieldName("actions")->SetValue(actions);
	class_instance->GetInstanceByFieldName("generatedAtRuntime")->SetValue(generatedAtRuntime);
	class_instance->GetInstanceByFieldName("targetPlatform")->SetValue(targetPlatform);
	return true;
}

bool hktypes::hclClothData::Platform::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothData::Platform") {
		std::cout << "hclClothData::Platform::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

inline std::vector<std::string> hktypes::hclClothData::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclClothData::Platform::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclClothData::GetFieldTypeAndNames() { return {
	{ "hkStringPtr", { "name", 24, 32 } },
	{ "hkArray<T*<hclSimClothData>, hkContainerHeapAllocator>", { "simClothDatas", 32, 32 } },
	{ "hkArray<T*<hclBufferDefinition>, hkContainerHeapAllocator>", { "bufferDefinitions", 48, 32 } },
	{ "hkArray<T*<hclTransformSetDefinition>, hkContainerHeapAllocator>", { "transformSetDefinitions", 64, 32 } },
	{ "hkArray<T*<hclOperator>, hkContainerHeapAllocator>", { "operators", 80, 32 } },
	{ "hkArray<T*<hclClothState>, hkContainerHeapAllocator>", { "clothStateDatas", 96, 32 } },
	{ "hkArray<T*<hclStateTransition>, hkContainerHeapAllocator>", { "stateTransitions", 112, 32 } },
	{ "hkArray<T*<hclAction>, hkContainerHeapAllocator>", { "actions", 128, 32 } },
	{ "hkBool", { "generatedAtRuntime", 144, 33 } },
	{ "hkEnum<hclClothData::Platform, hkUint32>", { "targetPlatform", 148, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclClothData::Platform::GetFieldTypeAndNames() { return {
}; };

