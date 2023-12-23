#include "Generated\hclObjectSpaceSkinPNOperator.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclObjectSpaceSkinPNOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceSkinPNOperator") {
		std::cout << "hclObjectSpaceSkinPNOperator::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclObjectSpaceSkinOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("localPNs")->GetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->GetValue(localUnpackedPNs);
	return true;
}

bool hktypes::hclObjectSpaceSkinPNOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceSkinPNOperator") {
		std::cout << "hclObjectSpaceSkinPNOperator::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclObjectSpaceSkinOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("localPNs")->SetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->SetValue(localUnpackedPNs);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceSkinPNOperator::GetTemplateArgs() { return {
}; };

