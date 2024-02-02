#include "Generated\hknpCompositeShape.h"

#include "Generated\.h"

bool hktypes::hknpCompositeShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCompositeShape") {
		std::cout << "hknpCompositeShape::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("shapeTagCodecInfo")->GetValue(shapeTagCodecInfo);
	return true;
}

bool hktypes::hknpCompositeShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCompositeShape") {
		std::cout << "hknpCompositeShape::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("shapeTagCodecInfo")->SetValue(shapeTagCodecInfo);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpCompositeShape::GetTemplateArgs() { return {
}; };

