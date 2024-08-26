#include "Generated\hknpBoxShape.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpBoxShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBoxShape") {
		std::cout << "hknpBoxShape::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpConvexShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("obb")->GetValue(obb);
	return true;
}

bool hktypes::hknpBoxShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBoxShape") {
		std::cout << "hknpBoxShape::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpConvexShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("obb")->SetValue(obb);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpBoxShape::GetTemplateArgs() { return {
}; };

