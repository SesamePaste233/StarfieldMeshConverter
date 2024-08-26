#include "Generated\hknpBodyId.h"


bool hktypes::hknpBodyId::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpBodyId::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpBodyId") {
		std::cout << "hknpBodyId::FromInstance: Expecting hknpBodyId but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("serialAndIndex")->GetValue(serialAndIndex);
	return true;
}

bool hktypes::hknpBodyId::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpBodyId::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpBodyId") {
		std::cout << "hknpBodyId::ToInstance: Expecting hknpBodyId but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("serialAndIndex")->SetValue(serialAndIndex);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpBodyId::GetTemplateArgs() { return {
}; };

