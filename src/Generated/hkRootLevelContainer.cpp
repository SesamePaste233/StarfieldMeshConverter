#include "Generated\hkRootLevelContainer.h"

bool hktypes::hkRootLevelContainer::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkRootLevelContainer") {
		std::cout << "hkRootLevelContainer::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("namedVariants")->GetValue(namedVariants);
	return true;
}

bool hktypes::hkRootLevelContainer::NamedVariant::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkRootLevelContainer::NamedVariant") {
		std::cout << "hkRootLevelContainer::NamedVariant::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("className")->GetValue(className);
	class_instance->GetInstanceByFieldName("variant")->GetValue(variant);
	return true;
}

bool hktypes::hkRootLevelContainer::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkRootLevelContainer") {
		std::cout << "hkRootLevelContainer::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("namedVariants")->SetValue(namedVariants);
	return true;
}

bool hktypes::hkRootLevelContainer::NamedVariant::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkRootLevelContainer::NamedVariant") {
		std::cout << "hkRootLevelContainer::NamedVariant::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("className")->SetValue(className);
	class_instance->GetInstanceByFieldName("variant")->SetValue(variant);
	return true;
}

inline std::vector<std::string> hktypes::hkRootLevelContainer::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hkRootLevelContainer::NamedVariant::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkRootLevelContainer::GetFieldTypeAndNames() { return {
	{ "hkArray<hkRootLevelContainer::NamedVariant, hkContainerHeapAllocator>", { "namedVariants", 0, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkRootLevelContainer::NamedVariant::GetFieldTypeAndNames() { return {
	{ "hkStringPtr", { "name", 0, 36 } },
	{ "hkStringPtr", { "className", 8, 36 } },
	{ "hkRefVariant", { "variant", 16, 36 } },
}; };

