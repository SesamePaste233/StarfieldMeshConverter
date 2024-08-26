#include "Generated\hkReferencedObject.h"

#include "Generated\.h"

bool hktypes::hkReferencedObject::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkReferencedObject::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkReferencedObject") {
		std::cout << "hkReferencedObject::FromInstance: Expecting hkReferencedObject but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkBaseObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("sizeAndFlags")->GetValue(sizeAndFlags);
	class_instance->GetInstanceByFieldName("refCount")->GetValue(refCount);
	return true;
}

bool hktypes::hkReferencedObject::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkReferencedObject::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkReferencedObject") {
		std::cout << "hkReferencedObject::ToInstance: Expecting hkReferencedObject but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkBaseObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("sizeAndFlags")->SetValue(sizeAndFlags);
	class_instance->GetInstanceByFieldName("refCount")->SetValue(refCount);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkReferencedObject::GetTemplateArgs() { return {
}; };

