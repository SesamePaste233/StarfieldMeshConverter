#include "Generated\hknpMassDistribution.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpMassDistribution::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMassDistribution::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMassDistribution") {
		std::cout << "hknpMassDistribution::FromInstance: Expecting hknpMassDistribution but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("centerOfMassAndVolume")->GetValue(centerOfMassAndVolume);
	class_instance->GetInstanceByFieldName("majorAxisSpace")->GetValue(majorAxisSpace);
	class_instance->GetInstanceByFieldName("inertiaTensor")->GetValue(inertiaTensor);
	return true;
}

bool hktypes::hknpMassDistribution::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMassDistribution::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMassDistribution") {
		std::cout << "hknpMassDistribution::ToInstance: Expecting hknpMassDistribution but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("centerOfMassAndVolume")->SetValue(centerOfMassAndVolume);
	class_instance->GetInstanceByFieldName("majorAxisSpace")->SetValue(majorAxisSpace);
	class_instance->GetInstanceByFieldName("inertiaTensor")->SetValue(inertiaTensor);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpMassDistribution::GetTemplateArgs() { return {
}; };

