#include "Generated\hknpBodyId.h"


bool hktypes::hknpBodyId::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBodyId") {
		std::cout << "hknpBodyId::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("serialAndIndex")->GetValue(serialAndIndex);
	return true;
}

bool hktypes::hknpBodyId::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBodyId") {
		std::cout << "hknpBodyId::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("serialAndIndex")->SetValue(serialAndIndex);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpBodyId::GetTemplateArgs() { return {
}; };

