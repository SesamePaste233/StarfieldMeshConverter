#include "Generated\hclClothState.h"

bool hktypes::hclClothState::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState") {
		std::cout << "hclClothState::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("operators")->GetValue(operators);
	class_instance->GetInstanceByFieldName("usedBuffers")->GetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->GetValue(usedTransformSets);
	class_instance->GetInstanceByFieldName("usedSimCloths")->GetValue(usedSimCloths);
	class_instance->GetInstanceByFieldName("dependencyGraph")->GetValue(dependencyGraph);
	return true;
}

bool hktypes::hclClothState::BufferAccess::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState::BufferAccess") {
		std::cout << "hclClothState::BufferAccess::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("bufferIndex")->GetValue(bufferIndex);
	class_instance->GetInstanceByFieldName("bufferUsage")->GetValue(bufferUsage);
	class_instance->GetInstanceByFieldName("shadowBufferIndex")->GetValue(shadowBufferIndex);
	return true;
}

bool hktypes::hclClothState::TransformSetAccess::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState::TransformSetAccess") {
		std::cout << "hclClothState::TransformSetAccess::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformSetUsage")->GetValue(transformSetUsage);
	return true;
}

bool hktypes::hclClothState::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState") {
		std::cout << "hclClothState::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("operators")->SetValue(operators);
	class_instance->GetInstanceByFieldName("usedBuffers")->SetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->SetValue(usedTransformSets);
	class_instance->GetInstanceByFieldName("usedSimCloths")->SetValue(usedSimCloths);
	class_instance->GetInstanceByFieldName("dependencyGraph")->SetValue(dependencyGraph);
	return true;
}

bool hktypes::hclClothState::BufferAccess::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState::BufferAccess") {
		std::cout << "hclClothState::BufferAccess::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("bufferIndex")->SetValue(bufferIndex);
	class_instance->GetInstanceByFieldName("bufferUsage")->SetValue(bufferUsage);
	class_instance->GetInstanceByFieldName("shadowBufferIndex")->SetValue(shadowBufferIndex);
	return true;
}

bool hktypes::hclClothState::TransformSetAccess::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState::TransformSetAccess") {
		std::cout << "hclClothState::TransformSetAccess::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformSetUsage")->SetValue(transformSetUsage);
	return true;
}

inline std::vector<std::string> hktypes::hclClothState::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclClothState::BufferAccess::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclClothState::TransformSetAccess::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclClothState::GetFieldTypeAndNames() { return {
	{ "hkStringPtr", { "name", 24, 32 } },
	{ "hkArray<hkUint32, hkContainerHeapAllocator>", { "operators", 32, 32 } },
	{ "hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator>", { "usedBuffers", 48, 32 } },
	{ "hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator>", { "usedTransformSets", 64, 32 } },
	{ "hkArray<hkUint32, hkContainerHeapAllocator>", { "usedSimCloths", 80, 32 } },
	{ "T*<hclStateDependencyGraph>", { "dependencyGraph", 96, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclClothState::BufferAccess::GetFieldTypeAndNames() { return {
	{ "hkUint32", { "bufferIndex", 0, 32 } },
	{ "hclBufferUsage", { "bufferUsage", 4, 32 } },
	{ "hkUint32", { "shadowBufferIndex", 12, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclClothState::TransformSetAccess::GetFieldTypeAndNames() { return {
	{ "hkUint32", { "transformSetIndex", 0, 32 } },
	{ "hclTransformSetUsage", { "transformSetUsage", 8, 32 } },
}; };

