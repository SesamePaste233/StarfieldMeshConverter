#include "Generated\hkPackedVector3.h"


bool hktypes::hkPackedVector3::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkPackedVector3::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::FromInstance: Expecting hkPackedVector3 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("values")->GetValue(values);
	return true;
}

bool hktypes::hkPackedVector3::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkPackedVector3::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::ToInstance: Expecting hkPackedVector3 but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("values")->SetValue(values);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkPackedVector3::GetTemplateArgs() { return {
}; };

