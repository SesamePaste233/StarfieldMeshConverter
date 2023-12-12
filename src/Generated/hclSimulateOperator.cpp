#include "Generated\hclSimulateOperator.h"

bool hktypes::hclSimulateOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimulateOperator") {
		std::cout << "hclSimulateOperator::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("simClothIndex")->GetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("simulateOpConfigs")->GetValue(simulateOpConfigs);
	return true;
}

bool hktypes::hclSimulateOperator::Config::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimulateOperator::Config") {
		std::cout << "hclSimulateOperator::Config::FromInstance: Wrong type!" << std::endl;
		return false;
	}

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
	if (class_instance->type->type_name != "hclSimulateOperator") {
		std::cout << "hclSimulateOperator::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("simClothIndex")->SetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("simulateOpConfigs")->SetValue(simulateOpConfigs);
	return true;
}

bool hktypes::hclSimulateOperator::Config::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimulateOperator::Config") {
		std::cout << "hclSimulateOperator::Config::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("constraintExecution")->SetValue(constraintExecution);
	class_instance->GetInstanceByFieldName("instanceCollidablesUsed")->SetValue(instanceCollidablesUsed);
	class_instance->GetInstanceByFieldName("subSteps")->SetValue(subSteps);
	class_instance->GetInstanceByFieldName("numberOfSolveIterations")->SetValue(numberOfSolveIterations);
	class_instance->GetInstanceByFieldName("useAllInstanceCollidables")->SetValue(useAllInstanceCollidables);
	class_instance->GetInstanceByFieldName("adaptConstraintStiffness")->SetValue(adaptConstraintStiffness);
	return true;
}

