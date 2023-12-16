#include "Generated\hclConstraintSet.h"

bool hktypes::hclConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclConstraintSet") {
		std::cout << "hclConstraintSet::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("constraintId")->GetValue(constraintId);
	class_instance->GetInstanceByFieldName("type")->GetValue(type);
	return true;
}

bool hktypes::hclConstraintSet::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclConstraintSet") {
		std::cout << "hclConstraintSet::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("constraintId")->SetValue(constraintId);
	class_instance->GetInstanceByFieldName("type")->SetValue(type);
	return true;
}

inline std::vector<std::string> hktypes::hclConstraintSet::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclConstraintSet::GetFieldTypeAndNames() { return {
	{ "hkStringPtr", { "name", 24, 32 } },
	{ "hkHandle<hkUint32, 2147483647>", { "constraintId", 32, 32 } },
	{ "unsigned int", { "type", 36, 35 } },
}; };

