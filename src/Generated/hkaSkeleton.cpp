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

