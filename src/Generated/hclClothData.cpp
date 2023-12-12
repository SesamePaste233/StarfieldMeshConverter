#include "Generated\hclClothData.h"

bool hktypes::hclClothData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothData") {
		std::cout << "hclClothData::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("simClothDatas")->GetValue(simClothDatas);
	class_instance->GetInstanceByFieldName("bufferDefinitions")->GetValue(bufferDefinitions);
	class_instance->GetInstanceByFieldName("transformSetDefinitions")->GetValue(transformSetDefinitions);
	class_instance->GetInstanceByFieldName("operators")->GetValue(operators);
	class_instance->GetInstanceByFieldName("clothStateDatas")->GetValue(clothStateDatas);
	class_instance->GetInstanceByFieldName("stateTransitions")->GetValue(stateTransitions);
	class_instance->GetInstanceByFieldName("actions")->GetValue(actions);
	class_instance->GetInstanceByFieldName("generatedAtRuntime")->GetValue(generatedAtRuntime);
	class_instance->GetInstanceByFieldName("targetPlatform")->GetValue(targetPlatform);
	return true;
}

bool hktypes::hclClothData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothData") {
		std::cout << "hclClothData::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("simClothDatas")->SetValue(simClothDatas);
	class_instance->GetInstanceByFieldName("bufferDefinitions")->SetValue(bufferDefinitions);
	class_instance->GetInstanceByFieldName("transformSetDefinitions")->SetValue(transformSetDefinitions);
	class_instance->GetInstanceByFieldName("operators")->SetValue(operators);
	class_instance->GetInstanceByFieldName("clothStateDatas")->SetValue(clothStateDatas);
	class_instance->GetInstanceByFieldName("stateTransitions")->SetValue(stateTransitions);
	class_instance->GetInstanceByFieldName("actions")->SetValue(actions);
	class_instance->GetInstanceByFieldName("generatedAtRuntime")->SetValue(generatedAtRuntime);
	class_instance->GetInstanceByFieldName("targetPlatform")->SetValue(targetPlatform);
	return true;
}

