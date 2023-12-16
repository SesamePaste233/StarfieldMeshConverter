#include "Generated\hkaSkeleton.h"

bool hktypes::hkaSkeleton::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaSkeleton") {
		std::cout << "hkaSkeleton::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("parentIndices")->GetValue(parentIndices);
	class_instance->GetInstanceByFieldName("bones")->GetValue(bones);
	class_instance->GetInstanceByFieldName("referencePose")->GetValue(referencePose);
	class_instance->GetInstanceByFieldName("referenceFloats")->GetValue(referenceFloats);
	class_instance->GetInstanceByFieldName("floatSlots")->GetValue(floatSlots);
	class_instance->GetInstanceByFieldName("localFrames")->GetValue(localFrames);
	class_instance->GetInstanceByFieldName("partitions")->GetValue(partitions);
	return true;
}

bool hktypes::hkaSkeleton::LocalFrameOnBone::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaSkeleton::LocalFrameOnBone") {
		std::cout << "hkaSkeleton::LocalFrameOnBone::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hkaSkeleton::Partition::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaSkeleton::Partition") {
		std::cout << "hkaSkeleton::Partition::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hkaSkeleton::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaSkeleton") {
		std::cout << "hkaSkeleton::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("parentIndices")->SetValue(parentIndices);
	class_instance->GetInstanceByFieldName("bones")->SetValue(bones);
	class_instance->GetInstanceByFieldName("referencePose")->SetValue(referencePose);
	class_instance->GetInstanceByFieldName("referenceFloats")->SetValue(referenceFloats);
	class_instance->GetInstanceByFieldName("floatSlots")->SetValue(floatSlots);
	class_instance->GetInstanceByFieldName("localFrames")->SetValue(localFrames);
	class_instance->GetInstanceByFieldName("partitions")->SetValue(partitions);
	return true;
}

bool hktypes::hkaSkeleton::LocalFrameOnBone::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaSkeleton::LocalFrameOnBone") {
		std::cout << "hkaSkeleton::LocalFrameOnBone::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hkaSkeleton::Partition::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkaSkeleton::Partition") {
		std::cout << "hkaSkeleton::Partition::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

inline std::vector<std::string> hktypes::hkaSkeleton::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hkaSkeleton::LocalFrameOnBone::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hkaSkeleton::Partition::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkaSkeleton::GetFieldTypeAndNames() { return {
	{ "hkStringPtr", { "name", 24, 32 } },
	{ "hkArray<hkInt16, hkContainerHeapAllocator>", { "parentIndices", 32, 32 } },
	{ "hkArray<hkaBone, hkContainerHeapAllocator>", { "bones", 48, 32 } },
	{ "hkArray<hkQsTransform, hkContainerHeapAllocator>", { "referencePose", 64, 32 } },
	{ "hkArray<hkReal, hkContainerHeapAllocator>", { "referenceFloats", 80, 32 } },
	{ "hkArray<hkStringPtr, hkContainerHeapAllocator>", { "floatSlots", 96, 32 } },
	{ "hkArray<hkaSkeleton::LocalFrameOnBone, hkContainerHeapAllocator>", { "localFrames", 112, 32 } },
	{ "hkArray<hkaSkeleton::Partition, hkContainerHeapAllocator>", { "partitions", 128, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkaSkeleton::LocalFrameOnBone::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hkaSkeleton::Partition::GetFieldTypeAndNames() { return {
}; };

