#include "Generated\hclClothState.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclClothState::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothState::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothState") {
		std::cout << "hclClothState::FromInstance: Expecting hclClothState but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("operators")->GetValue(operators);
	class_instance->GetInstanceByFieldName("usedBuffers")->GetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->GetValue(usedTransformSets);
	class_instance->GetInstanceByFieldName("usedSimCloths")->GetValue(usedSimCloths);
	class_instance->GetInstanceByFieldName("dependencyGraph")->GetValue(dependencyGraph);
	return true;
}

bool hktypes::hclClothState::BufferAccess::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothState::BufferAccess::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothState::BufferAccess") {
		std::cout << "hclClothState::BufferAccess::FromInstance: Expecting hclClothState::BufferAccess but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("bufferIndex")->GetValue(bufferIndex);
	class_instance->GetInstanceByFieldName("bufferUsage")->GetValue(bufferUsage);
	class_instance->GetInstanceByFieldName("shadowBufferIndex")->GetValue(shadowBufferIndex);
	return true;
}

bool hktypes::hclClothState::TransformSetAccess::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothState::TransformSetAccess::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothState::TransformSetAccess") {
		std::cout << "hclClothState::TransformSetAccess::FromInstance: Expecting hclClothState::TransformSetAccess but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformSetUsage")->GetValue(transformSetUsage);
	return true;
}

bool hktypes::hclClothState::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothState::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothState") {
		std::cout << "hclClothState::ToInstance: Expecting hclClothState but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("operators")->SetValue(operators);
	class_instance->GetInstanceByFieldName("usedBuffers")->SetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->SetValue(usedTransformSets);
	class_instance->GetInstanceByFieldName("usedSimCloths")->SetValue(usedSimCloths);
	class_instance->GetInstanceByFieldName("dependencyGraph")->SetValue(dependencyGraph);
	return true;
}

bool hktypes::hclClothState::BufferAccess::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothState::BufferAccess::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothState::BufferAccess") {
		std::cout << "hclClothState::BufferAccess::ToInstance: Expecting hclClothState::BufferAccess but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("bufferIndex")->SetValue(bufferIndex);
	class_instance->GetInstanceByFieldName("bufferUsage")->SetValue(bufferUsage);
	class_instance->GetInstanceByFieldName("shadowBufferIndex")->SetValue(shadowBufferIndex);
	return true;
}

bool hktypes::hclClothState::TransformSetAccess::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclClothState::TransformSetAccess::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclClothState::TransformSetAccess") {
		std::cout << "hclClothState::TransformSetAccess::ToInstance: Expecting hclClothState::TransformSetAccess but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformSetUsage")->SetValue(transformSetUsage);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclClothState::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclClothState::BufferAccess::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclClothState::TransformSetAccess::GetTemplateArgs() { return {
}; };

