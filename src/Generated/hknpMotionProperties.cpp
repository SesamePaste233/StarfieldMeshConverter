#include "Generated\hknpMotionProperties.h"

#include "Generated\.h"

bool hktypes::hknpMotionProperties::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMotionProperties::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMotionProperties") {
		std::cout << "hknpMotionProperties::FromInstance: Expecting hknpMotionProperties but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("isExclusive")->GetValue(isExclusive);
	class_instance->GetInstanceByFieldName("flags")->GetValue(flags);
	class_instance->GetInstanceByFieldName("gravityFactor")->GetValue(gravityFactor);
	class_instance->GetInstanceByFieldName("timeFactor")->GetValue(timeFactor);
	class_instance->GetInstanceByFieldName("maxLinearSpeed")->GetValue(maxLinearSpeed);
	class_instance->GetInstanceByFieldName("maxAngularSpeed")->GetValue(maxAngularSpeed);
	class_instance->GetInstanceByFieldName("linearDamping")->GetValue(linearDamping);
	class_instance->GetInstanceByFieldName("angularDamping")->GetValue(angularDamping);
	class_instance->GetInstanceByFieldName("solverStabilizationSpeedThreshold")->GetValue(solverStabilizationSpeedThreshold);
	class_instance->GetInstanceByFieldName("solverStabilizationSpeedReduction")->GetValue(solverStabilizationSpeedReduction);
	class_instance->GetInstanceByFieldName("deactivationSettings")->GetValue(deactivationSettings);
	class_instance->GetInstanceByFieldName("fullCastSettings")->GetValue(fullCastSettings);
	return true;
}

bool hktypes::hknpMotionProperties::DeactivationSettings::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMotionProperties::DeactivationSettings::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMotionProperties::DeactivationSettings") {
		std::cout << "hknpMotionProperties::DeactivationSettings::FromInstance: Expecting hknpMotionProperties::DeactivationSettings but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("maxDistSqrd")->GetValue(maxDistSqrd);
	class_instance->GetInstanceByFieldName("maxRotSqrd")->GetValue(maxRotSqrd);
	class_instance->GetInstanceByFieldName("invBlockSize")->GetValue(invBlockSize);
	class_instance->GetInstanceByFieldName("pathingUpperThreshold")->GetValue(pathingUpperThreshold);
	class_instance->GetInstanceByFieldName("pathingLowerThreshold")->GetValue(pathingLowerThreshold);
	class_instance->GetInstanceByFieldName("numDeactivationFrequencyPasses")->GetValue(numDeactivationFrequencyPasses);
	class_instance->GetInstanceByFieldName("deactivationVelocityScaleSquare")->GetValue(deactivationVelocityScaleSquare);
	class_instance->GetInstanceByFieldName("minimumPathingVelocityScaleSquare")->GetValue(minimumPathingVelocityScaleSquare);
	class_instance->GetInstanceByFieldName("spikingVelocityScaleThresholdSquared")->GetValue(spikingVelocityScaleThresholdSquared);
	class_instance->GetInstanceByFieldName("minimumSpikingVelocityScaleSquared")->GetValue(minimumSpikingVelocityScaleSquared);
	return true;
}

bool hktypes::hknpMotionProperties::FullCastSettings::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMotionProperties::FullCastSettings::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMotionProperties::FullCastSettings") {
		std::cout << "hknpMotionProperties::FullCastSettings::FromInstance: Expecting hknpMotionProperties::FullCastSettings but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("minSeparation")->GetValue(minSeparation);
	class_instance->GetInstanceByFieldName("minExtraSeparation")->GetValue(minExtraSeparation);
	class_instance->GetInstanceByFieldName("toiSeparation")->GetValue(toiSeparation);
	class_instance->GetInstanceByFieldName("toiExtraSeparation")->GetValue(toiExtraSeparation);
	class_instance->GetInstanceByFieldName("toiAccuracy")->GetValue(toiAccuracy);
	class_instance->GetInstanceByFieldName("relativeSafeDeltaTime")->GetValue(relativeSafeDeltaTime);
	class_instance->GetInstanceByFieldName("absoluteSafeDeltaTime")->GetValue(absoluteSafeDeltaTime);
	class_instance->GetInstanceByFieldName("keepTime")->GetValue(keepTime);
	class_instance->GetInstanceByFieldName("keepDistance")->GetValue(keepDistance);
	class_instance->GetInstanceByFieldName("maxIterations")->GetValue(maxIterations);
	return true;
}

bool hktypes::hknpMotionProperties::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMotionProperties::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMotionProperties") {
		std::cout << "hknpMotionProperties::ToInstance: Expecting hknpMotionProperties but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("isExclusive")->SetValue(isExclusive);
	class_instance->GetInstanceByFieldName("flags")->SetValue(flags);
	class_instance->GetInstanceByFieldName("gravityFactor")->SetValue(gravityFactor);
	class_instance->GetInstanceByFieldName("timeFactor")->SetValue(timeFactor);
	class_instance->GetInstanceByFieldName("maxLinearSpeed")->SetValue(maxLinearSpeed);
	class_instance->GetInstanceByFieldName("maxAngularSpeed")->SetValue(maxAngularSpeed);
	class_instance->GetInstanceByFieldName("linearDamping")->SetValue(linearDamping);
	class_instance->GetInstanceByFieldName("angularDamping")->SetValue(angularDamping);
	class_instance->GetInstanceByFieldName("solverStabilizationSpeedThreshold")->SetValue(solverStabilizationSpeedThreshold);
	class_instance->GetInstanceByFieldName("solverStabilizationSpeedReduction")->SetValue(solverStabilizationSpeedReduction);
	class_instance->GetInstanceByFieldName("deactivationSettings")->SetValue(deactivationSettings);
	class_instance->GetInstanceByFieldName("fullCastSettings")->SetValue(fullCastSettings);
	return true;
}

bool hktypes::hknpMotionProperties::DeactivationSettings::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMotionProperties::DeactivationSettings::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMotionProperties::DeactivationSettings") {
		std::cout << "hknpMotionProperties::DeactivationSettings::ToInstance: Expecting hknpMotionProperties::DeactivationSettings but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("maxDistSqrd")->SetValue(maxDistSqrd);
	class_instance->GetInstanceByFieldName("maxRotSqrd")->SetValue(maxRotSqrd);
	class_instance->GetInstanceByFieldName("invBlockSize")->SetValue(invBlockSize);
	class_instance->GetInstanceByFieldName("pathingUpperThreshold")->SetValue(pathingUpperThreshold);
	class_instance->GetInstanceByFieldName("pathingLowerThreshold")->SetValue(pathingLowerThreshold);
	class_instance->GetInstanceByFieldName("numDeactivationFrequencyPasses")->SetValue(numDeactivationFrequencyPasses);
	class_instance->GetInstanceByFieldName("deactivationVelocityScaleSquare")->SetValue(deactivationVelocityScaleSquare);
	class_instance->GetInstanceByFieldName("minimumPathingVelocityScaleSquare")->SetValue(minimumPathingVelocityScaleSquare);
	class_instance->GetInstanceByFieldName("spikingVelocityScaleThresholdSquared")->SetValue(spikingVelocityScaleThresholdSquared);
	class_instance->GetInstanceByFieldName("minimumSpikingVelocityScaleSquared")->SetValue(minimumSpikingVelocityScaleSquared);
	return true;
}

bool hktypes::hknpMotionProperties::FullCastSettings::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpMotionProperties::FullCastSettings::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpMotionProperties::FullCastSettings") {
		std::cout << "hknpMotionProperties::FullCastSettings::ToInstance: Expecting hknpMotionProperties::FullCastSettings but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("minSeparation")->SetValue(minSeparation);
	class_instance->GetInstanceByFieldName("minExtraSeparation")->SetValue(minExtraSeparation);
	class_instance->GetInstanceByFieldName("toiSeparation")->SetValue(toiSeparation);
	class_instance->GetInstanceByFieldName("toiExtraSeparation")->SetValue(toiExtraSeparation);
	class_instance->GetInstanceByFieldName("toiAccuracy")->SetValue(toiAccuracy);
	class_instance->GetInstanceByFieldName("relativeSafeDeltaTime")->SetValue(relativeSafeDeltaTime);
	class_instance->GetInstanceByFieldName("absoluteSafeDeltaTime")->SetValue(absoluteSafeDeltaTime);
	class_instance->GetInstanceByFieldName("keepTime")->SetValue(keepTime);
	class_instance->GetInstanceByFieldName("keepDistance")->SetValue(keepDistance);
	class_instance->GetInstanceByFieldName("maxIterations")->SetValue(maxIterations);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpMotionProperties::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpMotionProperties::DeactivationSettings::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpMotionProperties::FullCastSettings::GetTemplateArgs() { return {
}; };

