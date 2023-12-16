#include "Generated\hclStretchLinkConstraintSetMx.h"

bool hktypes::hclStretchLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx") {
		std::cout << "hclStretchLinkConstraintSetMx::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->GetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->GetValue(singles);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLengths")->GetValue(restLengths);
	class_instance->GetInstanceByFieldName("stiffnesses")->GetValue(stiffnesses);
	class_instance->GetInstanceByFieldName("particlesA")->GetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->GetValue(particlesB);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Single") {
		std::cout << "hclStretchLinkConstraintSetMx::Single::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx") {
		std::cout << "hclStretchLinkConstraintSetMx::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(singles);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLengths")->SetValue(restLengths);
	class_instance->GetInstanceByFieldName("stiffnesses")->SetValue(stiffnesses);
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(particlesB);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Single") {
		std::cout << "hclStretchLinkConstraintSetMx::Single::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

inline std::vector<std::string> hktypes::hclStretchLinkConstraintSetMx::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclStretchLinkConstraintSetMx::Batch::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclStretchLinkConstraintSetMx::Single::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclStretchLinkConstraintSetMx::GetFieldTypeAndNames() { return {
	{ "hkArray<hclStretchLinkConstraintSetMx::Batch, hkContainerHeapAllocator>", { "batches", 40, 32 } },
	{ "hkArray<hclStretchLinkConstraintSetMx::Single, hkContainerHeapAllocator>", { "singles", 56, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclStretchLinkConstraintSetMx::Batch::GetFieldTypeAndNames() { return {
	{ "T[N]<hkReal, 4>", { "restLengths", 0, 32 } },
	{ "T[N]<hkReal, 4>", { "stiffnesses", 16, 32 } },
	{ "T[N]<hkUint16, 4>", { "particlesA", 32, 32 } },
	{ "T[N]<hkUint16, 4>", { "particlesB", 40, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclStretchLinkConstraintSetMx::Single::GetFieldTypeAndNames() { return {
}; };

