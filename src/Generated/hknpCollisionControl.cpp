#include "Generated\hknpCollisionControl.h"

#include "Generated\.h"

bool hktypes::hknpCollisionControl::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpCollisionControl::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpCollisionControl") {
		std::cout << "hknpCollisionControl::FromInstance: Expecting hknpCollisionControl but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkFlags<hknpCollisionControl::Enum, unsigned short>::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hknpCollisionControl::Enum::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpCollisionControl::Enum::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpCollisionControl::Enum") {
		std::cout << "hknpCollisionControl::Enum::FromInstance: Expecting hknpCollisionControl::Enum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hknpCollisionControl::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpCollisionControl::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpCollisionControl") {
		std::cout << "hknpCollisionControl::ToInstance: Expecting hknpCollisionControl but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkFlags<hknpCollisionControl::Enum, unsigned short>::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hknpCollisionControl::Enum::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpCollisionControl::Enum::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpCollisionControl::Enum") {
		std::cout << "hknpCollisionControl::Enum::ToInstance: Expecting hknpCollisionControl::Enum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpCollisionControl::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpCollisionControl::Enum::GetTemplateArgs() { return {
}; };

