#include "Generated\hkEnum.h"

#include "Generated\hknpMaterial.h"
#include "Generated\hknpMaterial.h"
#include "Generated\hknpMaterial.h"
#include "Generated\hknpShapeType.h"
#include "Generated\hknpCollisionDispatchType.h"

template<>
bool hktypes::hkEnum<hknpMaterial::TriggerType, hkUint8>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::FromInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkEnum<hknpMaterial::TriggerType, hkUint8>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::ToInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkEnum<hknpMaterial::TriggerType, hkUint8>::GetTemplateArgs() { return {
	{"tENUM", "hknpMaterial::TriggerType"},
	{"tSTORAGE", "hkUint8"},
}; };

template<>
bool hktypes::hkEnum<hknpMaterial::CombinePolicy, hkUint8>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::FromInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkEnum<hknpMaterial::CombinePolicy, hkUint8>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::ToInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkEnum<hknpMaterial::CombinePolicy, hkUint8>::GetTemplateArgs() { return {
	{"tENUM", "hknpMaterial::CombinePolicy"},
	{"tSTORAGE", "hkUint8"},
}; };

template<>
bool hktypes::hkEnum<hknpMaterial::MassChangerCategory, hkUint8>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::FromInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkEnum<hknpMaterial::MassChangerCategory, hkUint8>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::ToInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkEnum<hknpMaterial::MassChangerCategory, hkUint8>::GetTemplateArgs() { return {
	{"tENUM", "hknpMaterial::MassChangerCategory"},
	{"tSTORAGE", "hkUint8"},
}; };

template<>
bool hktypes::hkEnum<hknpShapeType::Enum, hkUint8>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::FromInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkEnum<hknpShapeType::Enum, hkUint8>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::ToInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkEnum<hknpShapeType::Enum, hkUint8>::GetTemplateArgs() { return {
	{"tENUM", "hknpShapeType::Enum"},
	{"tSTORAGE", "hkUint8"},
}; };

template<>
bool hktypes::hkEnum<hknpCollisionDispatchType::Enum, hkUint8>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::FromInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->GetValue(storage);
	return true;
}

template<>
bool hktypes::hkEnum<hknpCollisionDispatchType::Enum, hkUint8>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkEnum::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkEnum") {
		std::cout << "hkEnum::ToInstance: Expecting hkEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("storage")->SetValue(storage);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkEnum<hknpCollisionDispatchType::Enum, hkUint8>::GetTemplateArgs() { return {
	{"tENUM", "hknpCollisionDispatchType::Enum"},
	{"tSTORAGE", "hkUint8"},
}; };

