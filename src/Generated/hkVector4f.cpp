#include "Generated\hkVector4f.h"


bool hktypes::hkVector4f::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkVector4f") {
		std::cout << "hkVector4f::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hkVector4f::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkVector4f") {
		std::cout << "hkVector4f::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkVector4f::GetTemplateArgs() { return {
}; };

