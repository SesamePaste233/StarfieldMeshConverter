#include "Generated\hclCollidable.h"

bool hktypes::hclCollidable::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCollidable") {
		std::cout << "hclCollidable::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("transform")->GetValue(transform);
	class_instance->GetInstanceByFieldName("linearVelocity")->GetValue(linearVelocity);
	class_instance->GetInstanceByFieldName("angularVelocity")->GetValue(angularVelocity);
	class_instance->GetInstanceByFieldName("userData")->GetValue(userData);
	class_instance->GetInstanceByFieldName("shape")->GetValue(shape);
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->GetValue(pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->GetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->GetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("virtualCollisionPointCollisionEnabled")->GetValue(virtualCollisionPointCollisionEnabled);
	class_instance->GetInstanceByFieldName("enabled")->GetValue(enabled);
	return true;
}

bool hktypes::hclCollidable::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCollidable") {
		std::cout << "hclCollidable::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("transform")->SetValue(transform);
	class_instance->GetInstanceByFieldName("linearVelocity")->SetValue(linearVelocity);
	class_instance->GetInstanceByFieldName("angularVelocity")->SetValue(angularVelocity);
	class_instance->GetInstanceByFieldName("userData")->SetValue(userData);
	class_instance->GetInstanceByFieldName("shape")->SetValue(shape);
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->SetValue(pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->SetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("virtualCollisionPointCollisionEnabled")->SetValue(virtualCollisionPointCollisionEnabled);
	class_instance->GetInstanceByFieldName("enabled")->SetValue(enabled);
	return true;
}

inline std::vector<std::string> hktypes::hclCollidable::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclCollidable::GetFieldTypeAndNames() { return {
	{ "hkTransform", { "transform", 32, 32 } },
	{ "hkVector4", { "linearVelocity", 96, 32 } },
	{ "hkVector4", { "angularVelocity", 112, 32 } },
	{ "hkUint64", { "userData", 128, 160 } },
	{ "T*<hclShape>", { "shape", 136, 32 } },
	{ "hkStringPtr", { "name", 144, 32 } },
	{ "hkReal", { "pinchDetectionRadius", 152, 32 } },
	{ "hkInt8", { "pinchDetectionPriority", 156, 32 } },
	{ "hkBool", { "pinchDetectionEnabled", 157, 32 } },
	{ "hkBool", { "virtualCollisionPointCollisionEnabled", 158, 32 } },
	{ "hkBool", { "enabled", 159, 32 } },
}; };

