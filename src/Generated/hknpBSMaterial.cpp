#include "Generated\hknpBSMaterial.h"

#include "Generated\.h"

bool hktypes::hknpBSMaterial::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBSMaterial") {
		std::cout << "hknpBSMaterial::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("uiFilterInfo")->GetValue(uiFilterInfo);
	class_instance->GetInstanceByFieldName("uiMaterialCRC")->GetValue(uiMaterialCRC);
	return true;
}

bool hktypes::hknpBSMaterial::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBSMaterial") {
		std::cout << "hknpBSMaterial::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("uiFilterInfo")->SetValue(uiFilterInfo);
	class_instance->GetInstanceByFieldName("uiMaterialCRC")->SetValue(uiMaterialCRC);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpBSMaterial::GetTemplateArgs() { return {
}; };

