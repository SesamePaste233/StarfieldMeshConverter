#include "Generated\hclBendStiffnessConstraintSetMx.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclBendStiffnessConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSetMx") {
		std::cout << "hclBendStiffnessConstraintSetMx::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->GetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->GetValue(singles);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->GetValue(maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->GetValue(clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->GetValue(useRestPoseConfig);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSetMx::Batch") {
		std::cout << "hclBendStiffnessConstraintSetMx::Batch::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("weightsA")->GetValue(weightsA);
	class_instance->GetInstanceByFieldName("weightsB")->GetValue(weightsB);
	class_instance->GetInstanceByFieldName("weightsC")->GetValue(weightsC);
	class_instance->GetInstanceByFieldName("weightsD")->GetValue(weightsD);
	class_instance->GetInstanceByFieldName("bendStiffnesses")->GetValue(bendStiffnesses);
	class_instance->GetInstanceByFieldName("restCurvatures")->GetValue(restCurvatures);
	class_instance->GetInstanceByFieldName("invMassesA")->GetValue(invMassesA);
	class_instance->GetInstanceByFieldName("invMassesB")->GetValue(invMassesB);
	class_instance->GetInstanceByFieldName("invMassesC")->GetValue(invMassesC);
	class_instance->GetInstanceByFieldName("invMassesD")->GetValue(invMassesD);
	class_instance->GetInstanceByFieldName("particlesA")->GetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->GetValue(particlesB);
	class_instance->GetInstanceByFieldName("particlesC")->GetValue(particlesC);
	class_instance->GetInstanceByFieldName("particlesD")->GetValue(particlesD);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSetMx::Single") {
		std::cout << "hclBendStiffnessConstraintSetMx::Single::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSetMx") {
		std::cout << "hclBendStiffnessConstraintSetMx::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(singles);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->SetValue(maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->SetValue(clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->SetValue(useRestPoseConfig);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSetMx::Batch") {
		std::cout << "hclBendStiffnessConstraintSetMx::Batch::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("weightsA")->SetValue(weightsA);
	class_instance->GetInstanceByFieldName("weightsB")->SetValue(weightsB);
	class_instance->GetInstanceByFieldName("weightsC")->SetValue(weightsC);
	class_instance->GetInstanceByFieldName("weightsD")->SetValue(weightsD);
	class_instance->GetInstanceByFieldName("bendStiffnesses")->SetValue(bendStiffnesses);
	class_instance->GetInstanceByFieldName("restCurvatures")->SetValue(restCurvatures);
	class_instance->GetInstanceByFieldName("invMassesA")->SetValue(invMassesA);
	class_instance->GetInstanceByFieldName("invMassesB")->SetValue(invMassesB);
	class_instance->GetInstanceByFieldName("invMassesC")->SetValue(invMassesC);
	class_instance->GetInstanceByFieldName("invMassesD")->SetValue(invMassesD);
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(particlesB);
	class_instance->GetInstanceByFieldName("particlesC")->SetValue(particlesC);
	class_instance->GetInstanceByFieldName("particlesD")->SetValue(particlesD);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSetMx::Single") {
		std::cout << "hclBendStiffnessConstraintSetMx::Single::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBendStiffnessConstraintSetMx::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBendStiffnessConstraintSetMx::Batch::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBendStiffnessConstraintSetMx::Single::GetTemplateArgs() { return {
}; };

