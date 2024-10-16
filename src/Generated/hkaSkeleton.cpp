#include "Generated\hkaSkeleton.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hkaSkeleton::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkaSkeleton::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkaSkeleton") {
		std::cout << "hkaSkeleton::FromInstance: Expecting hkaSkeleton but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

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

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkaSkeleton::LocalFrameOnBone::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkaSkeleton::LocalFrameOnBone") {
		std::cout << "hkaSkeleton::LocalFrameOnBone::FromInstance: Expecting hkaSkeleton::LocalFrameOnBone but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hkaSkeleton::Partition::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkaSkeleton::Partition::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkaSkeleton::Partition") {
		std::cout << "hkaSkeleton::Partition::FromInstance: Expecting hkaSkeleton::Partition but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hkaSkeleton::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkaSkeleton::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkaSkeleton") {
		std::cout << "hkaSkeleton::ToInstance: Expecting hkaSkeleton but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

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

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkaSkeleton::LocalFrameOnBone::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkaSkeleton::LocalFrameOnBone") {
		std::cout << "hkaSkeleton::LocalFrameOnBone::ToInstance: Expecting hkaSkeleton::LocalFrameOnBone but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hkaSkeleton::Partition::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkaSkeleton::Partition::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkaSkeleton::Partition") {
		std::cout << "hkaSkeleton::Partition::ToInstance: Expecting hkaSkeleton::Partition but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkaSkeleton::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hkaSkeleton::LocalFrameOnBone::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hkaSkeleton::Partition::GetTemplateArgs() { return {
}; };

