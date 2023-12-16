#include "Generated\hclTransformSetUsage.h"

bool hktypes::hclTransformSetUsage::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTransformSetUsage") {
		std::cout << "hclTransformSetUsage::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("perComponentFlags")->GetValue(perComponentFlags);
	class_instance->GetInstanceByFieldName("perComponentTransformTrackers")->GetValue(perComponentTransformTrackers);
	return true;
}

bool hktypes::hclTransformSetUsage::TransformTracker::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTransformSetUsage::TransformTracker") {
		std::cout << "hclTransformSetUsage::TransformTracker::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("read")->GetValue(read);
	class_instance->GetInstanceByFieldName("readBeforeWrite")->GetValue(readBeforeWrite);
	class_instance->GetInstanceByFieldName("written")->GetValue(written);
	return true;
}

bool hktypes::hclTransformSetUsage::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTransformSetUsage") {
		std::cout << "hclTransformSetUsage::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("perComponentFlags")->SetValue(perComponentFlags);
	class_instance->GetInstanceByFieldName("perComponentTransformTrackers")->SetValue(perComponentTransformTrackers);
	return true;
}

bool hktypes::hclTransformSetUsage::TransformTracker::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTransformSetUsage::TransformTracker") {
		std::cout << "hclTransformSetUsage::TransformTracker::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("read")->SetValue(read);
	class_instance->GetInstanceByFieldName("readBeforeWrite")->SetValue(readBeforeWrite);
	class_instance->GetInstanceByFieldName("written")->SetValue(written);
	return true;
}

inline std::vector<std::string> hktypes::hclTransformSetUsage::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclTransformSetUsage::TransformTracker::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclTransformSetUsage::GetFieldTypeAndNames() { return {
	{ "T[N]<hkUint8, 2>", { "perComponentFlags", 0, 32 } },
	{ "hkArray<hclTransformSetUsage::TransformTracker, hkContainerHeapAllocator>", { "perComponentTransformTrackers", 8, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclTransformSetUsage::TransformTracker::GetFieldTypeAndNames() { return {
	{ "hkBitField", { "read", 0, 32 } },
	{ "hkBitField", { "readBeforeWrite", 24, 32 } },
	{ "hkBitField", { "written", 48, 32 } },
}; };

