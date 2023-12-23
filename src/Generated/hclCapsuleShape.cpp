#include "Generated\hclCapsuleShape.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclCapsuleShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclCapsuleShape") {
		std::cout << "hclCapsuleShape::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("start")->GetValue(start);
	class_instance->GetInstanceByFieldName("end")->GetValue(end);
	class_instance->GetInstanceByFieldName("dir")->GetValue(dir);
	class_instance->GetInstanceByFieldName("radius")->GetValue(radius);
	class_instance->GetInstanceByFieldName("capLenSqrdInv")->GetValue(capLenSqrdInv);
	return true;
}

bool hktypes::hclCapsuleShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclCapsuleShape") {
		std::cout << "hclCapsuleShape::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("start")->SetValue(start);
	class_instance->GetInstanceByFieldName("end")->SetValue(end);
	class_instance->GetInstanceByFieldName("dir")->SetValue(dir);
	class_instance->GetInstanceByFieldName("radius")->SetValue(radius);
	class_instance->GetInstanceByFieldName("capLenSqrdInv")->SetValue(capLenSqrdInv);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclCapsuleShape::GetTemplateArgs() { return {
}; };

