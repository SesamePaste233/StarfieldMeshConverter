#include "hknpPhysicsSystemData.h"

bool hktypes::hknpPhysicsSystemData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpPhysicsSystemData::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpPhysicsSystemData") {
		std::cout << "hknpPhysicsSystemData::FromInstance: Expecting hknpPhysicsSystemData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("materials")->GetValue(materials);
	class_instance->GetInstanceByFieldName("motionProperties")->GetValue(motionProperties);
	class_instance->GetInstanceByFieldName("bodyCinfos")->GetValue(bodyCinfos);
	//class_instance->GetInstanceByFieldName("constraintCinfos")->GetValue(constraintCinfos);
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("microStepMultiplier")->GetValue(microStepMultiplier);
	return true;
}

bool hktypes::hknpPhysicsSystemData::bodyCinfoWithAttachment::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpPhysicsSystemData::bodyCinfoWithAttachment::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpPhysicsSystemData::bodyCinfoWithAttachment") {
		std::cout << "hknpPhysicsSystemData::bodyCinfoWithAttachment::FromInstance: Expecting hknpPhysicsSystemData::bodyCinfoWithAttachment but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpBodyCinfo::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("attachedBody")->GetValue(attachedBody);
	return true;
}

bool hktypes::hknpPhysicsSystemData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpPhysicsSystemData::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpPhysicsSystemData") {
		std::cout << "hknpPhysicsSystemData::ToInstance: Expecting hknpPhysicsSystemData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("materials")->SetValue(materials);
	class_instance->GetInstanceByFieldName("motionProperties")->SetValue(motionProperties);
	class_instance->GetInstanceByFieldName("bodyCinfos")->SetValue(bodyCinfos);
	//class_instance->GetInstanceByFieldName("constraintCinfos")->SetValue(constraintCinfos);
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("microStepMultiplier")->SetValue(microStepMultiplier);
	return true;
}

bool hktypes::hknpPhysicsSystemData::bodyCinfoWithAttachment::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpPhysicsSystemData::bodyCinfoWithAttachment::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpPhysicsSystemData::bodyCinfoWithAttachment") {
		std::cout << "hknpPhysicsSystemData::bodyCinfoWithAttachment::ToInstance: Expecting hknpPhysicsSystemData::bodyCinfoWithAttachment but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpBodyCinfo::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("attachedBody")->SetValue(attachedBody);
	return true;
}