#include "Generated\hclSimClothData.h"

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
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclSimClothData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData") {
		std::cout << "hclSimClothData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("simulationInfo")->GetValue(simulationInfo);
	class_instance->GetInstanceByFieldName("particleDatas")->GetValue(particleDatas);
	class_instance->GetInstanceByFieldName("fixedParticles")->GetValue(fixedParticles);
	class_instance->GetInstanceByFieldName("doNormals")->GetValue(doNormals);
	class_instance->GetInstanceByFieldName("simOpIds")->GetValue(simOpIds);
	class_instance->GetInstanceByFieldName("simClothPoses")->GetValue(simClothPoses);
	class_instance->GetInstanceByFieldName("staticConstraintSets")->GetValue(staticConstraintSets);
	class_instance->GetInstanceByFieldName("antiPinchConstraintSets")->GetValue(antiPinchConstraintSets);
	class_instance->GetInstanceByFieldName("collidableTransformMap")->GetValue(collidableTransformMap);
	class_instance->GetInstanceByFieldName("perInstanceCollidables")->GetValue(perInstanceCollidables);
	class_instance->GetInstanceByFieldName("maxParticleRadius")->GetValue(maxParticleRadius);
	class_instance->GetInstanceByFieldName("staticCollisionMasks")->GetValue(staticCollisionMasks);
	class_instance->GetInstanceByFieldName("actions")->GetValue(actions);
	class_instance->GetInstanceByFieldName("totalMass")->GetValue(totalMass);
	class_instance->GetInstanceByFieldName("transferMotionData")->GetValue(transferMotionData);
	class_instance->GetInstanceByFieldName("transferMotionEnabled")->GetValue(transferMotionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionEnabled")->GetValue(landscapeCollisionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionData")->GetValue(landscapeCollisionData);
	class_instance->GetInstanceByFieldName("numLandscapeCollidableParticles")->GetValue(numLandscapeCollidableParticles);
	class_instance->GetInstanceByFieldName("triangleIndices")->GetValue(triangleIndices);
	class_instance->GetInstanceByFieldName("triangleFlips")->GetValue(triangleFlips);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->GetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("perParticlePinchDetectionEnabledFlags")->GetValue(perParticlePinchDetectionEnabledFlags);
	class_instance->GetInstanceByFieldName("collidablePinchingDatas")->GetValue(collidablePinchingDatas);
	class_instance->GetInstanceByFieldName("minPinchedParticleIndex")->GetValue(minPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxPinchedParticleIndex")->GetValue(maxPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxCollisionPairs")->GetValue(maxCollisionPairs);
	class_instance->GetInstanceByFieldName("virtualCollisionPointsData")->GetValue(virtualCollisionPointsData);
	return true;
}

bool hktypes::hclSimClothData::OverridableSimulationInfo::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::OverridableSimulationInfo") {
		std::cout << "hclSimClothData::OverridableSimulationInfo::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("gravity")->GetValue(gravity);
	class_instance->GetInstanceByFieldName("globalDampingPerSecond")->GetValue(globalDampingPerSecond);
	return true;
}

bool hktypes::hclSimClothData::ParticleData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::ParticleData") {
		std::cout << "hclSimClothData::ParticleData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("mass")->GetValue(mass);
	class_instance->GetInstanceByFieldName("invMass")->GetValue(invMass);
	class_instance->GetInstanceByFieldName("radius")->GetValue(radius);
	class_instance->GetInstanceByFieldName("friction")->GetValue(friction);
	return true;
}

bool hktypes::hclSimClothData::CollidableTransformMap::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::CollidableTransformMap") {
		std::cout << "hclSimClothData::CollidableTransformMap::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformIndices")->GetValue(transformIndices);
	class_instance->GetInstanceByFieldName("offsets")->GetValue(offsets);
	return true;
}

bool hktypes::hclSimClothData::TransferMotionData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::TransferMotionData") {
		std::cout << "hclSimClothData::TransferMotionData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformIndex")->GetValue(transformIndex);
	class_instance->GetInstanceByFieldName("transferTranslationMotion")->GetValue(transferTranslationMotion);
	class_instance->GetInstanceByFieldName("minTranslationSpeed")->GetValue(minTranslationSpeed);
	class_instance->GetInstanceByFieldName("maxTranslationSpeed")->GetValue(maxTranslationSpeed);
	class_instance->GetInstanceByFieldName("minTranslationBlend")->GetValue(minTranslationBlend);
	class_instance->GetInstanceByFieldName("maxTranslationBlend")->GetValue(maxTranslationBlend);
	class_instance->GetInstanceByFieldName("transferRotationMotion")->GetValue(transferRotationMotion);
	class_instance->GetInstanceByFieldName("minRotationSpeed")->GetValue(minRotationSpeed);
	class_instance->GetInstanceByFieldName("maxRotationSpeed")->GetValue(maxRotationSpeed);
	class_instance->GetInstanceByFieldName("minRotationBlend")->GetValue(minRotationBlend);
	class_instance->GetInstanceByFieldName("maxRotationBlend")->GetValue(maxRotationBlend);
	return true;
}

bool hktypes::hclSimClothData::LandscapeCollisionData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::LandscapeCollisionData") {
		std::cout << "hclSimClothData::LandscapeCollisionData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("landscapeRadius")->GetValue(landscapeRadius);
	class_instance->GetInstanceByFieldName("enableStuckParticleDetection")->GetValue(enableStuckParticleDetection);
	class_instance->GetInstanceByFieldName("stuckParticlesStretchFactorSq")->GetValue(stuckParticlesStretchFactorSq);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->GetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->GetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->GetValue(pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("collisionTolerance")->GetValue(collisionTolerance);
	return true;
}

bool hktypes::hclSimClothData::CollidablePinchingData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::CollidablePinchingData") {
		std::cout << "hclSimClothData::CollidablePinchingData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->GetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->GetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->GetValue(pinchDetectionRadius);
	return true;
}

bool hktypes::hclSimClothData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData") {
		std::cout << "hclSimClothData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("simulationInfo")->SetValue(simulationInfo);
	class_instance->GetInstanceByFieldName("particleDatas")->SetValue(particleDatas);
	class_instance->GetInstanceByFieldName("fixedParticles")->SetValue(fixedParticles);
	class_instance->GetInstanceByFieldName("doNormals")->SetValue(doNormals);
	class_instance->GetInstanceByFieldName("simOpIds")->SetValue(simOpIds);
	class_instance->GetInstanceByFieldName("simClothPoses")->SetValue(simClothPoses);
	class_instance->GetInstanceByFieldName("staticConstraintSets")->SetValue(staticConstraintSets);
	class_instance->GetInstanceByFieldName("antiPinchConstraintSets")->SetValue(antiPinchConstraintSets);
	class_instance->GetInstanceByFieldName("collidableTransformMap")->SetValue(collidableTransformMap);
	class_instance->GetInstanceByFieldName("perInstanceCollidables")->SetValue(perInstanceCollidables);
	class_instance->GetInstanceByFieldName("maxParticleRadius")->SetValue(maxParticleRadius);
	class_instance->GetInstanceByFieldName("staticCollisionMasks")->SetValue(staticCollisionMasks);
	class_instance->GetInstanceByFieldName("actions")->SetValue(actions);
	class_instance->GetInstanceByFieldName("totalMass")->SetValue(totalMass);
	class_instance->GetInstanceByFieldName("transferMotionData")->SetValue(transferMotionData);
	class_instance->GetInstanceByFieldName("transferMotionEnabled")->SetValue(transferMotionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionEnabled")->SetValue(landscapeCollisionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionData")->SetValue(landscapeCollisionData);
	class_instance->GetInstanceByFieldName("numLandscapeCollidableParticles")->SetValue(numLandscapeCollidableParticles);
	class_instance->GetInstanceByFieldName("triangleIndices")->SetValue(triangleIndices);
	class_instance->GetInstanceByFieldName("triangleFlips")->SetValue(triangleFlips);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("perParticlePinchDetectionEnabledFlags")->SetValue(perParticlePinchDetectionEnabledFlags);
	class_instance->GetInstanceByFieldName("collidablePinchingDatas")->SetValue(collidablePinchingDatas);
	class_instance->GetInstanceByFieldName("minPinchedParticleIndex")->SetValue(minPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxPinchedParticleIndex")->SetValue(maxPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxCollisionPairs")->SetValue(maxCollisionPairs);
	class_instance->GetInstanceByFieldName("virtualCollisionPointsData")->SetValue(virtualCollisionPointsData);
	return true;
}

bool hktypes::hclSimClothData::OverridableSimulationInfo::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::OverridableSimulationInfo") {
		std::cout << "hclSimClothData::OverridableSimulationInfo::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("gravity")->SetValue(gravity);
	class_instance->GetInstanceByFieldName("globalDampingPerSecond")->SetValue(globalDampingPerSecond);
	return true;
}

bool hktypes::hclSimClothData::ParticleData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::ParticleData") {
		std::cout << "hclSimClothData::ParticleData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("mass")->SetValue(mass);
	class_instance->GetInstanceByFieldName("invMass")->SetValue(invMass);
	class_instance->GetInstanceByFieldName("radius")->SetValue(radius);
	class_instance->GetInstanceByFieldName("friction")->SetValue(friction);
	return true;
}

bool hktypes::hclSimClothData::CollidableTransformMap::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::CollidableTransformMap") {
		std::cout << "hclSimClothData::CollidableTransformMap::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformIndices")->SetValue(transformIndices);
	class_instance->GetInstanceByFieldName("offsets")->SetValue(offsets);
	return true;
}

bool hktypes::hclSimClothData::TransferMotionData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::TransferMotionData") {
		std::cout << "hclSimClothData::TransferMotionData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformIndex")->SetValue(transformIndex);
	class_instance->GetInstanceByFieldName("transferTranslationMotion")->SetValue(transferTranslationMotion);
	class_instance->GetInstanceByFieldName("minTranslationSpeed")->SetValue(minTranslationSpeed);
	class_instance->GetInstanceByFieldName("maxTranslationSpeed")->SetValue(maxTranslationSpeed);
	class_instance->GetInstanceByFieldName("minTranslationBlend")->SetValue(minTranslationBlend);
	class_instance->GetInstanceByFieldName("maxTranslationBlend")->SetValue(maxTranslationBlend);
	class_instance->GetInstanceByFieldName("transferRotationMotion")->SetValue(transferRotationMotion);
	class_instance->GetInstanceByFieldName("minRotationSpeed")->SetValue(minRotationSpeed);
	class_instance->GetInstanceByFieldName("maxRotationSpeed")->SetValue(maxRotationSpeed);
	class_instance->GetInstanceByFieldName("minRotationBlend")->SetValue(minRotationBlend);
	class_instance->GetInstanceByFieldName("maxRotationBlend")->SetValue(maxRotationBlend);
	return true;
}

bool hktypes::hclSimClothData::LandscapeCollisionData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::LandscapeCollisionData") {
		std::cout << "hclSimClothData::LandscapeCollisionData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("landscapeRadius")->SetValue(landscapeRadius);
	class_instance->GetInstanceByFieldName("enableStuckParticleDetection")->SetValue(enableStuckParticleDetection);
	class_instance->GetInstanceByFieldName("stuckParticlesStretchFactorSq")->SetValue(stuckParticlesStretchFactorSq);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->SetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->SetValue(pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("collisionTolerance")->SetValue(collisionTolerance);
	return true;
}

bool hktypes::hclSimClothData::CollidablePinchingData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::CollidablePinchingData") {
		std::cout << "hclSimClothData::CollidablePinchingData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->SetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->SetValue(pinchDetectionRadius);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimClothData::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimClothData::OverridableSimulationInfo::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimClothData::ParticleData::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimClothData::CollidableTransformMap::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimClothData::TransferMotionData::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimClothData::LandscapeCollisionData::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclSimClothData::CollidablePinchingData::GetTemplateArgs() { return {
}; };

