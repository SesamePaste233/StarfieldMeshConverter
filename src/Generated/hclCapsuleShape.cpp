#include "Generated\hclCapsuleShape.h"

bool hktypes::hclCapsuleShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCapsuleShape") {
		std::cout << "hclCapsuleShape::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("start")->GetValue(start);
	class_instance->GetInstanceByFieldName("end")->GetValue(end);
	class_instance->GetInstanceByFieldName("dir")->GetValue(dir);
	class_instance->GetInstanceByFieldName("radius")->GetValue(radius);
	class_instance->GetInstanceByFieldName("capLenSqrdInv")->GetValue(capLenSqrdInv);
	return true;
}

bool hktypes::hclCapsuleShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCapsuleShape") {
		std::cout << "hclCapsuleShape::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("start")->SetValue(start);
	class_instance->GetInstanceByFieldName("end")->SetValue(end);
	class_instance->GetInstanceByFieldName("dir")->SetValue(dir);
	class_instance->GetInstanceByFieldName("radius")->SetValue(radius);
	class_instance->GetInstanceByFieldName("capLenSqrdInv")->SetValue(capLenSqrdInv);
	return true;
}

inline std::vector<std::string> hktypes::hclCapsuleShape::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclCapsuleShape::GetFieldTypeAndNames() { return {
	{ "hkVector4", { "start", 32, 34 } },
	{ "hkVector4", { "end", 48, 34 } },
	{ "hkVector4", { "dir", 64, 34 } },
	{ "hkReal", { "radius", 80, 34 } },
	{ "hkReal", { "capLenSqrdInv", 84, 34 } },
}; };

