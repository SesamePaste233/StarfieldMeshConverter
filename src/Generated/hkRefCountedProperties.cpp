#include "Generated\hkRefCountedProperties.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hkRefCountedProperties::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkRefCountedProperties") {
		std::cout << "hkRefCountedProperties::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("entries")->GetValue(entries);
	return true;
}

bool hktypes::hkRefCountedProperties::Entry::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkRefCountedProperties::Entry") {
		std::cout << "hkRefCountedProperties::Entry::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("object")->GetValue(object);
	class_instance->GetInstanceByFieldName("key")->GetValue(key);
	class_instance->GetInstanceByFieldName("flags")->GetValue(flags);
	return true;
}

bool hktypes::hkRefCountedProperties::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkRefCountedProperties") {
		std::cout << "hkRefCountedProperties::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("entries")->SetValue(entries);
	return true;
}

bool hktypes::hkRefCountedProperties::Entry::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkRefCountedProperties::Entry") {
		std::cout << "hkRefCountedProperties::Entry::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("object")->SetValue(object);
	class_instance->GetInstanceByFieldName("key")->SetValue(key);
	class_instance->GetInstanceByFieldName("flags")->SetValue(flags);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefCountedProperties::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefCountedProperties::Entry::GetTemplateArgs() { return {
}; };

