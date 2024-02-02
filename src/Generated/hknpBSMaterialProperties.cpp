#include "Generated\hknpBSMaterialProperties.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpBSMaterialProperties::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBSMaterialProperties") {
		std::cout << "hknpBSMaterialProperties::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("MaterialA")->GetValue(MaterialA);
	return true;
}

bool hktypes::hknpBSMaterialProperties::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBSMaterialProperties") {
		std::cout << "hknpBSMaterialProperties::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("MaterialA")->SetValue(MaterialA);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpBSMaterialProperties::GetTemplateArgs() { return {
}; };

