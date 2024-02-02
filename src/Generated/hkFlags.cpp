#include "Generated\hkFlags.h"

#include "Generated\hknpCollisionFlags.h"
#include "Generated\hknpCollisionControl.h"
#include "Generated\hknpShape.h"

template<>
bool hktypes::hkFlags<hknpCollisionFlags::Enum, int>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkFlags") {
		std::cout << "hkFlags::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkFlags<hknpCollisionFlags::Enum, int>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkFlags") {
		std::cout << "hkFlags::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkFlags<hknpCollisionFlags::Enum, int>::GetTemplateArgs() { return {
	{"tBITS", "hknpCollisionFlags::Enum"},
	{"tSTORAGE", "int"},
}; };

template<>
bool hktypes::hkFlags<hknpCollisionControl::Enum, unsigned short>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkFlags") {
		std::cout << "hkFlags::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkFlags<hknpCollisionControl::Enum, unsigned short>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkFlags") {
		std::cout << "hkFlags::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkFlags<hknpCollisionControl::Enum, unsigned short>::GetTemplateArgs() { return {
	{"tBITS", "hknpCollisionControl::Enum"},
	{"tSTORAGE", "unsigned short"},
}; };

template<>
bool hktypes::hkFlags<hknpShape::FlagsEnum, hkUint16>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkFlags") {
		std::cout << "hkFlags::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkFlags<hknpShape::FlagsEnum, hkUint16>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkFlags") {
		std::cout << "hkFlags::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkFlags<hknpShape::FlagsEnum, hkUint16>::GetTemplateArgs() { return {
	{"tBITS", "hknpShape::FlagsEnum"},
	{"tSTORAGE", "hkUint16"},
}; };

