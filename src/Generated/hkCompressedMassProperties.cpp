#include "Generated\hkCompressedMassProperties.h"

#include "Generated\.h"

bool hktypes::hkCompressedMassProperties::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkCompressedMassProperties::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkCompressedMassProperties") {
		std::cout << "hkCompressedMassProperties::FromInstance: Expecting hkCompressedMassProperties but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("centerOfMass")->GetValue(centerOfMass);
	class_instance->GetInstanceByFieldName("inertia")->GetValue(inertia);
	class_instance->GetInstanceByFieldName("majorAxisSpace")->GetValue(majorAxisSpace);
	class_instance->GetInstanceByFieldName("mass")->GetValue(mass);
	class_instance->GetInstanceByFieldName("volume")->GetValue(volume);
	return true;
}

bool hktypes::hkCompressedMassProperties::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkCompressedMassProperties::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkCompressedMassProperties") {
		std::cout << "hkCompressedMassProperties::ToInstance: Expecting hkCompressedMassProperties but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("centerOfMass")->SetValue(centerOfMass);
	class_instance->GetInstanceByFieldName("inertia")->SetValue(inertia);
	class_instance->GetInstanceByFieldName("majorAxisSpace")->SetValue(majorAxisSpace);
	class_instance->GetInstanceByFieldName("mass")->SetValue(mass);
	class_instance->GetInstanceByFieldName("volume")->SetValue(volume);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkCompressedMassProperties::GetTemplateArgs() { return {
}; };

