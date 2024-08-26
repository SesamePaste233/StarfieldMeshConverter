#include "Generated\hknpConvexShape.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpConvexShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexShape::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexShape") {
		std::cout << "hknpConvexShape::FromInstance: Expecting hknpConvexShape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("maxAllowedPenetration")->GetValue(maxAllowedPenetration);
	class_instance->GetInstanceByFieldName("hull")->GetValue(hull);
	return true;
}

bool hktypes::hknpConvexShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexShape::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexShape") {
		std::cout << "hknpConvexShape::ToInstance: Expecting hknpConvexShape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("maxAllowedPenetration")->SetValue(maxAllowedPenetration);
	class_instance->GetInstanceByFieldName("hull")->SetValue(hull);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpConvexShape::GetTemplateArgs() { return {
}; };

