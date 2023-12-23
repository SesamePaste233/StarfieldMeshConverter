#include "Generated\hkTransformf.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hkTransformf::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkTransformf") {
		std::cout << "hkTransformf::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("rotation")->GetValue(rotation);
	class_instance->GetInstanceByFieldName("translation")->GetValue(translation);
	return true;
}

bool hktypes::hkTransformf::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkTransformf") {
		std::cout << "hkTransformf::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("rotation")->SetValue(rotation);
	class_instance->GetInstanceByFieldName("translation")->SetValue(translation);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkTransformf::GetTemplateArgs() { return {
}; };

