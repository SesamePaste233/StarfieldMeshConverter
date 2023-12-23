#include "Generated\hkQuaternionf.h"

#include "Generated\.h"

bool hktypes::hkQuaternionf::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkQuaternionf") {
		std::cout << "hkQuaternionf::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vec")->GetValue(vec);
	return true;
}

bool hktypes::hkQuaternionf::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkQuaternionf") {
		std::cout << "hkQuaternionf::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vec")->SetValue(vec);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkQuaternionf::GetTemplateArgs() { return {
}; };

