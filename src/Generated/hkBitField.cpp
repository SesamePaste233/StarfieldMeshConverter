#include "Generated\hkBitField.h"

#include "Generated\.h"

bool hktypes::hkBitField::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkBitField") {
		std::cout << "hkBitField::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hkBitField::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkBitField") {
		std::cout << "hkBitField::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkBitField::GetTemplateArgs() { return {
}; };

