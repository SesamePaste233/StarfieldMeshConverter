#include "Generated\hclTransformSetDefinition.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclTransformSetDefinition::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclTransformSetDefinition::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclTransformSetDefinition") {
		std::cout << "hclTransformSetDefinition::FromInstance: Expecting hclTransformSetDefinition but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("type")->GetValue(type);
	class_instance->GetInstanceByFieldName("numTransforms")->GetValue(numTransforms);
	return true;
}

bool hktypes::hclTransformSetDefinition::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclTransformSetDefinition::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclTransformSetDefinition") {
		std::cout << "hclTransformSetDefinition::ToInstance: Expecting hclTransformSetDefinition but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("type")->SetValue(type);
	class_instance->GetInstanceByFieldName("numTransforms")->SetValue(numTransforms);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclTransformSetDefinition::GetTemplateArgs() { return {
}; };

