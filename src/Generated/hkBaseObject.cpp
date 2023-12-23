#include "Generated\hkBaseObject.h"


bool hktypes::hkBaseObject::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkBaseObject") {
		std::cout << "hkBaseObject::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hkBaseObject::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkBaseObject") {
		std::cout << "hkBaseObject::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkBaseObject::GetTemplateArgs() { return {
}; };

