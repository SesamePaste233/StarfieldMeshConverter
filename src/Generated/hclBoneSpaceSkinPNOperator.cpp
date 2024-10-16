#include "Generated\hclBoneSpaceSkinPNOperator.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclBoneSpaceSkinPNOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceSkinPNOperator::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceSkinPNOperator") {
		std::cout << "hclBoneSpaceSkinPNOperator::FromInstance: Expecting hclBoneSpaceSkinPNOperator but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclBoneSpaceSkinOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("localPNs")->GetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->GetValue(localUnpackedPNs);
	return true;
}

bool hktypes::hclBoneSpaceSkinPNOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceSkinPNOperator::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceSkinPNOperator") {
		std::cout << "hclBoneSpaceSkinPNOperator::ToInstance: Expecting hclBoneSpaceSkinPNOperator but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclBoneSpaceSkinOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("localPNs")->SetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->SetValue(localUnpackedPNs);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceSkinPNOperator::GetTemplateArgs() { return {
}; };

