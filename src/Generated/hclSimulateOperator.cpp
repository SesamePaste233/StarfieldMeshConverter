#include "Generated\hclSimulateOperator.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclSimulateOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclSimulateOperator::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclSimulateOperator") {
		std::cout << "hclSimulateOperator::FromInstance: Expecting hclSimulateOperator but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("simClothIndex")->GetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("simulateOpConfigs")->GetValue(simulateOpConfigs);
	return true;
}

bool hktypes::hclSimulateOperator::Config::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclSimulateOperator::Config::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclSimulateOperator::Config") {
		std::cout << "hclSimulateOperator::Config::FromInstance: Expecting hclSimulateOperator::Config but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("constraintExecution")->GetValue(constraintExecution);
	class_instance->GetInstanceByFieldName("instanceCollidablesUsed")->GetValue(instanceCollidablesUsed);
	class_instance->GetInstanceByFieldName("subSteps")->GetValue(subSteps);
	class_instance->GetInstanceByFieldName("numberOfSolveIterations")->GetValue(numberOfSolveIterations);
	class_instance->GetInstanceByFieldName("useAllInstanceCollidables")->GetValue(useAllInstanceCollidables);
	class_instance->GetInstanceByFieldName("adaptConstraintStiffness")->GetValue(adaptConstraintStiffness);
	return true;
}

bool hktypes::hclSimulateOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclSimulateOperator::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclSimulateOperator") {
		std::cout << "hclSimulateOperator::ToInstance: Expecting hclSimulateOperator but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("simClothIndex")->SetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("simulateOpConfigs")->SetValue(simulateOpConfigs);
	return true;
}

bool hktypes::hclSimulateOperator::Config::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclSimulateOperator::Config::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclSimulateOperator::Config") {
		std::cout << "hclSimulateOperator::Config::ToInstance: Expecting hclSimulateOperator::Config but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("constraintExecution")->SetValue(constraintExecution);
	class_instance->GetInstanceByFieldName("instanceCollidablesUsed")->SetValue(instanceCollidablesUsed);
	class_instance->GetInstanceByFieldName("subSteps")->SetValue(subSteps);
	class_instance->GetInstanceByFieldName("numberOfSolveIterations")->SetValue(numberOfSolveIterations);
	class_instance->GetInstanceByFieldName("useAllInstanceCollidables")->SetValue(useAllInstanceCollidables);
	class_instance->GetInstanceByFieldName("adaptConstraintStiffness")->SetValue(adaptConstraintStiffness);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimulateOperator::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimulateOperator::Config::GetTemplateArgs() { return {
}; };

