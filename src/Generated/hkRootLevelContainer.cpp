#include "Generated\hkRootLevelContainer.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hkRootLevelContainer::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRootLevelContainer::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRootLevelContainer") {
		std::cout << "hkRootLevelContainer::FromInstance: Expecting hkRootLevelContainer but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("namedVariants")->GetValue(namedVariants);
	return true;
}

bool hktypes::hkRootLevelContainer::NamedVariant::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRootLevelContainer::NamedVariant::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRootLevelContainer::NamedVariant") {
		std::cout << "hkRootLevelContainer::NamedVariant::FromInstance: Expecting hkRootLevelContainer::NamedVariant but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("className")->GetValue(className);
	class_instance->GetInstanceByFieldName("variant")->GetValue(variant);
	return true;
}

bool hktypes::hkRootLevelContainer::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRootLevelContainer::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRootLevelContainer") {
		std::cout << "hkRootLevelContainer::ToInstance: Expecting hkRootLevelContainer but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("namedVariants")->SetValue(namedVariants);
	return true;
}

bool hktypes::hkRootLevelContainer::NamedVariant::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRootLevelContainer::NamedVariant::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRootLevelContainer::NamedVariant") {
		std::cout << "hkRootLevelContainer::NamedVariant::ToInstance: Expecting hkRootLevelContainer::NamedVariant but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("className")->SetValue(className);
	class_instance->GetInstanceByFieldName("variant")->SetValue(variant);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkRootLevelContainer::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hkRootLevelContainer::NamedVariant::GetTemplateArgs() { return {
}; };

