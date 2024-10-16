#include "Generated\hkaBone.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hkaBone::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkaBone::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkaBone") {
		std::cout << "hkaBone::FromInstance: Expecting hkaBone but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("lockTranslation")->GetValue(lockTranslation);
	return true;
}

bool hktypes::hkaBone::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkaBone::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkaBone") {
		std::cout << "hkaBone::ToInstance: Expecting hkaBone but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("lockTranslation")->SetValue(lockTranslation);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkaBone::GetTemplateArgs() { return {
}; };

