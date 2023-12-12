#include "Generated\hkReferencedObject.h"

bool hktypes::hkReferencedObject::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkReferencedObject") {
		std::cout << "hkReferencedObject::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkBaseObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("sizeAndFlags")->GetValue(sizeAndFlags);
	class_instance->GetInstanceByFieldName("refCount")->GetValue(refCount);
	return true;
}

bool hktypes::hkReferencedObject::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkReferencedObject") {
		std::cout << "hkReferencedObject::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkBaseObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("sizeAndFlags")->SetValue(sizeAndFlags);
	class_instance->GetInstanceByFieldName("refCount")->SetValue(refCount);
	return true;
}

