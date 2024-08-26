#include "Generated\hknpShapeMassProperties.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpShapeMassProperties::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpShapeMassProperties::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpShapeMassProperties") {
		std::cout << "hknpShapeMassProperties::FromInstance: Expecting hknpShapeMassProperties but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("compressedMassProperties")->GetValue(compressedMassProperties);
	return true;
}

bool hktypes::hknpShapeMassProperties::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpShapeMassProperties::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpShapeMassProperties") {
		std::cout << "hknpShapeMassProperties::ToInstance: Expecting hknpShapeMassProperties but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("compressedMassProperties")->SetValue(compressedMassProperties);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpShapeMassProperties::GetTemplateArgs() { return {
}; };

