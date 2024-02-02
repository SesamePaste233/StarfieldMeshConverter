#include "Generated\hclBendStiffnessConstraintSet.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclBendStiffnessConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSet") {
		std::cout << "hclBendStiffnessConstraintSet::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("links")->GetValue(links);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->GetValue(maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->GetValue(clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->GetValue(useRestPoseConfig);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSet::Link::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSet::Link") {
		std::cout << "hclBendStiffnessConstraintSet::Link::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("weightA")->GetValue(weightA);
	class_instance->GetInstanceByFieldName("weightB")->GetValue(weightB);
	class_instance->GetInstanceByFieldName("weightC")->GetValue(weightC);
	class_instance->GetInstanceByFieldName("weightD")->GetValue(weightD);
	class_instance->GetInstanceByFieldName("bendStiffness")->GetValue(bendStiffness);
	class_instance->GetInstanceByFieldName("restCurvature")->GetValue(restCurvature);
	class_instance->GetInstanceByFieldName("particleA")->GetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->GetValue(particleB);
	class_instance->GetInstanceByFieldName("particleC")->GetValue(particleC);
	class_instance->GetInstanceByFieldName("particleD")->GetValue(particleD);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSet::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSet") {
		std::cout << "hclBendStiffnessConstraintSet::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("links")->SetValue(links);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->SetValue(maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->SetValue(clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->SetValue(useRestPoseConfig);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSet::Link::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSet::Link") {
		std::cout << "hclBendStiffnessConstraintSet::Link::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("weightA")->SetValue(weightA);
	class_instance->GetInstanceByFieldName("weightB")->SetValue(weightB);
	class_instance->GetInstanceByFieldName("weightC")->SetValue(weightC);
	class_instance->GetInstanceByFieldName("weightD")->SetValue(weightD);
	class_instance->GetInstanceByFieldName("bendStiffness")->SetValue(bendStiffness);
	class_instance->GetInstanceByFieldName("restCurvature")->SetValue(restCurvature);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(particleB);
	class_instance->GetInstanceByFieldName("particleC")->SetValue(particleC);
	class_instance->GetInstanceByFieldName("particleD")->SetValue(particleD);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBendStiffnessConstraintSet::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBendStiffnessConstraintSet::Link::GetTemplateArgs() { return {
}; };

