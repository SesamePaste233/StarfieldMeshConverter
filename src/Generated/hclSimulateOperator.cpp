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

inline std::vector<std::string> hktypes::hclSimulateOperator::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclSimulateOperator::Config::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclSimulateOperator::GetFieldTypeAndNames() { return {
	{ "hkUint32", { "simClothIndex", 72, 32 } },
	{ "hkArray<hclSimulateOperator::Config, hkContainerHeapAllocator>", { "simulateOpConfigs", 80, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclSimulateOperator::Config::GetFieldTypeAndNames() { return {
	{ "hkStringPtr", { "name", 0, 32 } },
	{ "hkArray<hkInt32, hkContainerHeapAllocator>", { "constraintExecution", 8, 32 } },
	{ "hkArray<hkBool, hkContainerHeapAllocator>", { "instanceCollidablesUsed", 24, 32 } },
	{ "hkUint8", { "subSteps", 40, 32 } },
	{ "hkUint8", { "numberOfSolveIterations", 41, 32 } },
	{ "hkBool", { "useAllInstanceCollidables", 42, 32 } },
	{ "hkBool", { "adaptConstraintStiffness", 43, 32 } },
}; };

