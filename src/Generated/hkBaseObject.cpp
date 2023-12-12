#include "Generated\hkBaseObject.h"

bool hktypes::hkBaseObject::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBaseObject") {
		std::cout << "hkBaseObject::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hkBaseObject::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBaseObject") {
		std::cout << "hkBaseObject::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

