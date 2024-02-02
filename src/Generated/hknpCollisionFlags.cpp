#include "Generated\hknpCollisionFlags.h"

#include "Generated\.h"

bool hktypes::hknpCollisionFlags::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCollisionFlags") {
		std::cout << "hknpCollisionFlags::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkFlags<hknpCollisionFlags::Enum, int>::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hknpCollisionFlags::Enum::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCollisionFlags::Enum") {
		std::cout << "hknpCollisionFlags::Enum::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hknpCollisionFlags::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCollisionFlags") {
		std::cout << "hknpCollisionFlags::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkFlags<hknpCollisionFlags::Enum, int>::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hknpCollisionFlags::Enum::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCollisionFlags::Enum") {
		std::cout << "hknpCollisionFlags::Enum::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpCollisionFlags::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpCollisionFlags::Enum::GetTemplateArgs() { return {
}; };

