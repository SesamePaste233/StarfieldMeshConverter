#include "Generated\hkPackedVector3.h"


bool hktypes::hkPackedVector3::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("values")->GetValue(values);
	return true;
}

bool hktypes::hkPackedVector3::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("values")->SetValue(values);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkPackedVector3::GetTemplateArgs() { return {
}; };

