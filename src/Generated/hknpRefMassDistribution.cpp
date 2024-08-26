#include "Generated\hknpRefMassDistribution.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpRefMassDistribution::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpRefMassDistribution::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpRefMassDistribution") {
		std::cout << "hknpRefMassDistribution::FromInstance: Expecting hknpRefMassDistribution but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("massDistribution")->GetValue(massDistribution);
	return true;
}

bool hktypes::hknpRefMassDistribution::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpRefMassDistribution::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpRefMassDistribution") {
		std::cout << "hknpRefMassDistribution::ToInstance: Expecting hknpRefMassDistribution but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("massDistribution")->SetValue(massDistribution);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpRefMassDistribution::GetTemplateArgs() { return {
}; };

