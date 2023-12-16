#include "Generated\hclStandardLinkConstraintSetMx.h"

bool hktypes::hclStandardLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->GetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->GetValue(singles);
	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Batch") {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Single") {
		std::cout << "hclStandardLinkConstraintSetMx::Single::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLength")->GetValue(restLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->GetValue(stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->GetValue(stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->GetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->GetValue(particleB);
	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(singles);
	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Batch") {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Single") {
		std::cout << "hclStandardLinkConstraintSetMx::Single::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLength")->SetValue(restLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->SetValue(stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->SetValue(stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(particleB);
	return true;
}

inline std::vector<std::string> hktypes::hclStandardLinkConstraintSetMx::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclStandardLinkConstraintSetMx::Batch::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclStandardLinkConstraintSetMx::Single::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclStandardLinkConstraintSetMx::GetFieldTypeAndNames() { return {
	{ "hkArray<hclStandardLinkConstraintSetMx::Batch, hkContainerHeapAllocator>", { "batches", 40, 32 } },
	{ "hkArray<hclStandardLinkConstraintSetMx::Single, hkContainerHeapAllocator>", { "singles", 56, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclStandardLinkConstraintSetMx::Batch::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclStandardLinkConstraintSetMx::Single::GetFieldTypeAndNames() { return {
	{ "hkReal", { "restLength", 0, 32 } },
	{ "hkReal", { "stiffnessA", 4, 32 } },
	{ "hkReal", { "stiffnessB", 8, 32 } },
	{ "hkUint16", { "particleA", 12, 32 } },
	{ "hkUint16", { "particleB", 14, 32 } },
}; };

