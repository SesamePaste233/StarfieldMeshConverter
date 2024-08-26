#include "Generated\hkQuaternionf.h"

#include "Generated\.h"

bool hktypes::hkQuaternionf::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkQuaternionf::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkQuaternionf") {
		std::cout << "hkQuaternionf::FromInstance: Expecting hkQuaternionf but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vec")->GetValue(vec);
	return true;
}

bool hktypes::hkQuaternionf::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkQuaternionf::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkQuaternionf") {
		std::cout << "hkQuaternionf::ToInstance: Expecting hkQuaternionf but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vec")->SetValue(vec);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkQuaternionf::GetTemplateArgs() { return {
}; };

