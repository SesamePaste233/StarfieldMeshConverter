#include "Generated\hkcdFourAabb.h"

#include "Generated\.h"

bool hktypes::hkcdFourAabb::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdFourAabb") {
		std::cout << "hkcdFourAabb::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("lx")->GetValue(lx);
	class_instance->GetInstanceByFieldName("hx")->GetValue(hx);
	class_instance->GetInstanceByFieldName("ly")->GetValue(ly);
	class_instance->GetInstanceByFieldName("hy")->GetValue(hy);
	class_instance->GetInstanceByFieldName("lz")->GetValue(lz);
	class_instance->GetInstanceByFieldName("hz")->GetValue(hz);
	return true;
}

bool hktypes::hkcdFourAabb::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdFourAabb") {
		std::cout << "hkcdFourAabb::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("lx")->SetValue(lx);
	class_instance->GetInstanceByFieldName("hx")->SetValue(hx);
	class_instance->GetInstanceByFieldName("ly")->SetValue(ly);
	class_instance->GetInstanceByFieldName("hy")->SetValue(hy);
	class_instance->GetInstanceByFieldName("lz")->SetValue(lz);
	class_instance->GetInstanceByFieldName("hz")->SetValue(hz);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkcdFourAabb::GetTemplateArgs() { return {
}; };

