#include "hknpMaterial.h"

bool hktypes::hknpMaterial::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMaterial::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMaterial") {
		std::cout << "hknpMaterial::FromInstance: Expecting hknpMaterial but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("isExclusive")->GetValue(isExclusive);
	class_instance->GetInstanceByFieldName("flags")->GetValue(flags);
	class_instance->GetInstanceByFieldName("triggerType")->GetValue(triggerType);
	class_instance->GetInstanceByFieldName("triggerManifoldTolerance")->GetValue(triggerManifoldTolerance);
	class_instance->GetInstanceByFieldName("dynamicFriction")->GetValue(dynamicFriction);
	class_instance->GetInstanceByFieldName("staticFriction")->GetValue(staticFriction);
	class_instance->GetInstanceByFieldName("restitution")->GetValue(restitution);
	class_instance->GetInstanceByFieldName("frictionCombinePolicy")->GetValue(frictionCombinePolicy);
	class_instance->GetInstanceByFieldName("restitutionCombinePolicy")->GetValue(restitutionCombinePolicy);
	class_instance->GetInstanceByFieldName("weldingTolerance")->GetValue(weldingTolerance);
	class_instance->GetInstanceByFieldName("maxContactImpulse")->GetValue(maxContactImpulse);
	class_instance->GetInstanceByFieldName("fractionOfClippedImpulseToApply")->GetValue(fractionOfClippedImpulseToApply);
	class_instance->GetInstanceByFieldName("massChangerCategory")->GetValue(massChangerCategory);
	class_instance->GetInstanceByFieldName("massChangerHeavyObjectFactor")->GetValue(massChangerHeavyObjectFactor);
	class_instance->GetInstanceByFieldName("softContactForceFactor")->GetValue(softContactForceFactor);
	class_instance->GetInstanceByFieldName("softContactDampFactor")->GetValue(softContactDampFactor);
	class_instance->GetInstanceByFieldName("softContactSeparationVelocity")->GetValue(softContactSeparationVelocity);
	//class_instance->GetInstanceByFieldName("surfaceVelocity")->GetValue(surfaceVelocity);
	class_instance->GetInstanceByFieldName("disablingCollisionsBetweenCvxCvxDynamicObjectsDistance")->GetValue(disablingCollisionsBetweenCvxCvxDynamicObjectsDistance);
	class_instance->GetInstanceByFieldName("userData")->GetValue(userData);
	return true;
}


bool hktypes::hknpMaterial::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMaterial::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMaterial") {
		std::cout << "hknpMaterial::ToInstance: Expecting hknpMaterial but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("isExclusive")->SetValue(isExclusive);
	class_instance->GetInstanceByFieldName("flags")->SetValue(flags);
	class_instance->GetInstanceByFieldName("triggerType")->SetValue(triggerType);
	class_instance->GetInstanceByFieldName("triggerManifoldTolerance")->SetValue(triggerManifoldTolerance);
	class_instance->GetInstanceByFieldName("dynamicFriction")->SetValue(dynamicFriction);
	class_instance->GetInstanceByFieldName("staticFriction")->SetValue(staticFriction);
	class_instance->GetInstanceByFieldName("restitution")->SetValue(restitution);
	class_instance->GetInstanceByFieldName("frictionCombinePolicy")->SetValue(frictionCombinePolicy);
	class_instance->GetInstanceByFieldName("restitutionCombinePolicy")->SetValue(restitutionCombinePolicy);
	class_instance->GetInstanceByFieldName("weldingTolerance")->SetValue(weldingTolerance);
	class_instance->GetInstanceByFieldName("maxContactImpulse")->SetValue(maxContactImpulse);
	class_instance->GetInstanceByFieldName("fractionOfClippedImpulseToApply")->SetValue(fractionOfClippedImpulseToApply);
	class_instance->GetInstanceByFieldName("massChangerCategory")->SetValue(massChangerCategory);
	class_instance->GetInstanceByFieldName("massChangerHeavyObjectFactor")->SetValue(massChangerHeavyObjectFactor);
	class_instance->GetInstanceByFieldName("softContactForceFactor")->SetValue(softContactForceFactor);
	class_instance->GetInstanceByFieldName("softContactDampFactor")->SetValue(softContactDampFactor);
	class_instance->GetInstanceByFieldName("softContactSeparationVelocity")->SetValue(softContactSeparationVelocity);
	//class_instance->GetInstanceByFieldName("surfaceVelocity")->SetValue(surfaceVelocity);
	class_instance->GetInstanceByFieldName("disablingCollisionsBetweenCvxCvxDynamicObjectsDistance")->SetValue(disablingCollisionsBetweenCvxCvxDynamicObjectsDistance);
	class_instance->GetInstanceByFieldName("userData")->SetValue(userData);
	return true;
}
