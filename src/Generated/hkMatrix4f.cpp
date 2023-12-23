#include "Generated\hkMatrix4f.h"

#include "Generated\.h"

bool hktypes::hkMatrix4f::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkMatrix4f") {
		std::cout << "hkMatrix4f::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkMatrix4Impl<float>::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hkMatrix4f::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkMatrix4f") {
		std::cout << "hkMatrix4f::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkMatrix4Impl<float>::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkMatrix4f::GetTemplateArgs() { return {
}; };

