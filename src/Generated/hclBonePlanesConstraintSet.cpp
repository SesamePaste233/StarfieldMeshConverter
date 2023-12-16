#include "Generated\hclBonePlanesConstraintSet.h"

bool hktypes::hclBonePlanesConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBonePlanesConstraintSet") {
		std::cout << "hclBonePlanesConstraintSet::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("bonePlanes")->GetValue(bonePlanes);
	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	return true;
}

bool hktypes::hclBonePlanesConstraintSet::BonePlane::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBonePlanesConstraintSet::BonePlane") {
		std::cout << "hclBonePlanesConstraintSet::BonePlane::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("planeEquationBone")->GetValue(planeEquationBone);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	class_instance->GetInstanceByFieldName("transformIndex")->GetValue(transformIndex);
	class_instance->GetInstanceByFieldName("stiffness")->GetValue(stiffness);
	return true;
}

bool hktypes::hclBonePlanesConstraintSet::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBonePlanesConstraintSet") {
		std::cout << "hclBonePlanesConstraintSet::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("bonePlanes")->SetValue(bonePlanes);
	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	return true;
}

bool hktypes::hclBonePlanesConstraintSet::BonePlane::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBonePlanesConstraintSet::BonePlane") {
		std::cout << "hclBonePlanesConstraintSet::BonePlane::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("planeEquationBone")->SetValue(planeEquationBone);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	class_instance->GetInstanceByFieldName("transformIndex")->SetValue(transformIndex);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(stiffness);
	return true;
}

inline std::vector<std::string> hktypes::hclBonePlanesConstraintSet::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclBonePlanesConstraintSet::BonePlane::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclBonePlanesConstraintSet::GetFieldTypeAndNames() { return {
	{ "hkArray<hclBonePlanesConstraintSet::BonePlane, hkContainerHeapAllocator>", { "bonePlanes", 40, 32 } },
	{ "hkUint32", { "transformSetIndex", 56, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclBonePlanesConstraintSet::BonePlane::GetFieldTypeAndNames() { return {
	{ "hkVector4", { "planeEquationBone", 0, 32 } },
	{ "hkUint16", { "particleIndex", 16, 32 } },
	{ "hkUint16", { "transformIndex", 18, 32 } },
	{ "hkReal", { "stiffness", 20, 32 } },
}; };

