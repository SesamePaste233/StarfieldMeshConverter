#include "Generated\hkHandle.h"

bool hktypes::hkHandle<hkUint32, 2147483647>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkHandle") {
		std::cout << "hkHandle::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("value")->GetValue(value);
	return true;
}

bool hktypes::hkHandle<hkUint32, 2147483647>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkHandle") {
		std::cout << "hkHandle::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("value")->SetValue(value);
	return true;
}

inline std::vector<std::string> hktypes::hkHandle<hkUint32, 2147483647>::GetTemplateArgs() { return {
	"tTYPE",
	"vINVALID_VALUE",
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkHandle<hkUint32, 2147483647>::GetFieldTypeAndNames() { return {
	{ "hkUint32", { "value", 0, 34 } },
}; };

