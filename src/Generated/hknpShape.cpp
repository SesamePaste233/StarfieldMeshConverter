#include "Generated\hknpShape.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpShape::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpShape") {
		std::cout << "hknpShape::FromInstance: Expecting hknpShape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("flags")->GetValue(flags);
	class_instance->GetInstanceByFieldName("type")->GetValue(type);
	class_instance->GetInstanceByFieldName("numShapeKeyBits")->GetValue(numShapeKeyBits);
	class_instance->GetInstanceByFieldName("dispatchType")->GetValue(dispatchType);
	class_instance->GetInstanceByFieldName("convexRadius")->GetValue(convexRadius);
	class_instance->GetInstanceByFieldName("userData")->GetValue(userData);
	class_instance->GetInstanceByFieldName("properties")->GetValue(properties);
	return true;
}

bool hktypes::hknpShape::FlagsEnum::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpShape::FlagsEnum::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpShape::FlagsEnum") {
		std::cout << "hknpShape::FlagsEnum::FromInstance: Expecting hknpShape::FlagsEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hknpShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpShape::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpShape") {
		std::cout << "hknpShape::ToInstance: Expecting hknpShape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("flags")->SetValue(flags);
	class_instance->GetInstanceByFieldName("type")->SetValue(type);
	class_instance->GetInstanceByFieldName("numShapeKeyBits")->SetValue(numShapeKeyBits);
	class_instance->GetInstanceByFieldName("dispatchType")->SetValue(dispatchType);
	class_instance->GetInstanceByFieldName("convexRadius")->SetValue(convexRadius);
	class_instance->GetInstanceByFieldName("userData")->SetValue(userData);
	class_instance->GetInstanceByFieldName("properties")->SetValue(properties);
	return true;
}

bool hktypes::hknpShape::FlagsEnum::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpShape::FlagsEnum::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpShape::FlagsEnum") {
		std::cout << "hknpShape::FlagsEnum::ToInstance: Expecting hknpShape::FlagsEnum but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpShape::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpShape::FlagsEnum::GetTemplateArgs() { return {
}; };

