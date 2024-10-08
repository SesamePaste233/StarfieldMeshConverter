#include "Generated\hkVector4.h"

#include "Generated\.h"

bool hktypes::hkVector4::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkVector4::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkVector4") {
		std::cout << "hkVector4::FromInstance: Expecting hkVector4 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkVector4f::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hkVector4::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkVector4::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkVector4") {
		std::cout << "hkVector4::ToInstance: Expecting hkVector4 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkVector4f::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkVector4::GetTemplateArgs() { return {
}; };

