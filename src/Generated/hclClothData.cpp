#include "Generated\hclClothData.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclClothData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothData::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothData") {
		std::cout << "hclClothData::FromInstance: Expecting hclClothData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

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

bool hktypes::hclClothData::Platform::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothData::Platform::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothData::Platform") {
		std::cout << "hclClothData::Platform::FromInstance: Expecting hclClothData::Platform but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclClothData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothData::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothData") {
		std::cout << "hclClothData::ToInstance: Expecting hclClothData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

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

bool hktypes::hclClothData::Platform::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothData::Platform::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothData::Platform") {
		std::cout << "hclClothData::Platform::ToInstance: Expecting hclClothData::Platform but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclClothData::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclClothData::Platform::GetTemplateArgs() { return {
}; };

