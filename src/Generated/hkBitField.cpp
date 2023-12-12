#include "Generated\hkBitField.h"

bool hktypes::hkBitField::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBitField") {
		std::cout << "hkBitField::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hkBitField::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBitField") {
		std::cout << "hkBitField::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

