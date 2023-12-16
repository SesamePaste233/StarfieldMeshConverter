#include "Generated\hclBufferUsage.h"

bool hktypes::hclBufferUsage::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferUsage") {
		std::cout << "hclBufferUsage::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("perComponentFlags")->GetValue(perComponentFlags);
	class_instance->GetInstanceByFieldName("trianglesRead")->GetValue(trianglesRead);
	return true;
}

bool hktypes::hclBufferUsage::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferUsage") {
		std::cout << "hclBufferUsage::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("perComponentFlags")->SetValue(perComponentFlags);
	class_instance->GetInstanceByFieldName("trianglesRead")->SetValue(trianglesRead);
	return true;
}

inline std::vector<std::string> hktypes::hclBufferUsage::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclBufferUsage::GetFieldTypeAndNames() { return {
	{ "T[N]<hkUint8, 4>", { "perComponentFlags", 0, 32 } },
	{ "hkBool", { "trianglesRead", 4, 32 } },
}; };

