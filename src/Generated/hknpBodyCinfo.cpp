#include "Generated\hknpBodyCinfo.h"

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

bool hktypes::hknpBodyCinfo::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBodyCinfo") {
		std::cout << "hknpBodyCinfo::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("shape")->GetValue(shape);
	class_instance->GetInstanceByFieldName("flags")->GetValue(flags);
	class_instance->GetInstanceByFieldName("collisionCntrl")->GetValue(collisionCntrl);
	class_instance->GetInstanceByFieldName("collisionFilterInfo")->GetValue(collisionFilterInfo);
	class_instance->GetInstanceByFieldName("materialId")->GetValue(materialId);
	class_instance->GetInstanceByFieldName("qualityId")->GetValue(qualityId);
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("userData")->GetValue(userData);
	class_instance->GetInstanceByFieldName("motionType")->GetValue(motionType);
	class_instance->GetInstanceByFieldName("position")->GetValue(position);
	class_instance->GetInstanceByFieldName("orientation")->GetValue(orientation);
	class_instance->GetInstanceByFieldName("linearVelocity")->GetValue(linearVelocity);
	class_instance->GetInstanceByFieldName("angularVelocity")->GetValue(angularVelocity);
	class_instance->GetInstanceByFieldName("mass")->GetValue(mass);
	class_instance->GetInstanceByFieldName("massDistribution")->GetValue(massDistribution);
	class_instance->GetInstanceByFieldName("dragProperties")->GetValue(dragProperties);
	class_instance->GetInstanceByFieldName("motionPropertiesId")->GetValue(motionPropertiesId);
	class_instance->GetInstanceByFieldName("desiredBodyId")->GetValue(desiredBodyId);
	class_instance->GetInstanceByFieldName("motionId")->GetValue(motionId);
	class_instance->GetInstanceByFieldName("collisionLookAheadDistance")->GetValue(collisionLookAheadDistance);
	class_instance->GetInstanceByFieldName("localFrame")->GetValue(localFrame);
	class_instance->GetInstanceByFieldName("activationPriority")->GetValue(activationPriority);
	return true;
}

bool hktypes::hknpBodyCinfo::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpBodyCinfo") {
		std::cout << "hknpBodyCinfo::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("shape")->SetValue(shape);
	class_instance->GetInstanceByFieldName("flags")->SetValue(flags);
	class_instance->GetInstanceByFieldName("collisionCntrl")->SetValue(collisionCntrl);
	class_instance->GetInstanceByFieldName("collisionFilterInfo")->SetValue(collisionFilterInfo);
	class_instance->GetInstanceByFieldName("materialId")->SetValue(materialId);
	class_instance->GetInstanceByFieldName("qualityId")->SetValue(qualityId);
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("userData")->SetValue(userData);
	class_instance->GetInstanceByFieldName("motionType")->SetValue(motionType);
	class_instance->GetInstanceByFieldName("position")->SetValue(position);
	class_instance->GetInstanceByFieldName("orientation")->SetValue(orientation);
	class_instance->GetInstanceByFieldName("linearVelocity")->SetValue(linearVelocity);
	class_instance->GetInstanceByFieldName("angularVelocity")->SetValue(angularVelocity);
	class_instance->GetInstanceByFieldName("mass")->SetValue(mass);
	class_instance->GetInstanceByFieldName("massDistribution")->SetValue(massDistribution);
	class_instance->GetInstanceByFieldName("dragProperties")->SetValue(dragProperties);
	class_instance->GetInstanceByFieldName("motionPropertiesId")->SetValue(motionPropertiesId);
	class_instance->GetInstanceByFieldName("desiredBodyId")->SetValue(desiredBodyId);
	class_instance->GetInstanceByFieldName("motionId")->SetValue(motionId);
	class_instance->GetInstanceByFieldName("collisionLookAheadDistance")->SetValue(collisionLookAheadDistance);
	class_instance->GetInstanceByFieldName("localFrame")->SetValue(localFrame);
	class_instance->GetInstanceByFieldName("activationPriority")->SetValue(activationPriority);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpBodyCinfo::GetTemplateArgs() { return {
}; };

