#include "Generated\hkQsTransformf.h"

bool hktypes::hkQsTransformf::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkQsTransformf") {
		std::cout << "hkQsTransformf::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("translation")->GetValue(translation);
	class_instance->GetInstanceByFieldName("rotation")->GetValue(rotation);
	class_instance->GetInstanceByFieldName("scale")->GetValue(scale);
	return true;
}

bool hktypes::hkQsTransformf::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkQsTransformf") {
		std::cout << "hkQsTransformf::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("translation")->SetValue(translation);
	class_instance->GetInstanceByFieldName("rotation")->SetValue(rotation);
	class_instance->GetInstanceByFieldName("scale")->SetValue(scale);
	return true;
}

