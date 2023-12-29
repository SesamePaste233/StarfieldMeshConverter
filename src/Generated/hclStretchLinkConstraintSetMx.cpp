#include "Generated\hclStretchLinkConstraintSetMx.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclStretchLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStretchLinkConstraintSetMx") {
		std::cout << "hclStretchLinkConstraintSetMx::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->GetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->GetValue(singles);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("restLengths")->GetValue(restLengths);
	class_instance->GetInstanceByFieldName("stiffnesses")->GetValue(stiffnesses);
	class_instance->GetInstanceByFieldName("particlesA")->GetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->GetValue(particlesB);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Single") {
		std::cout << "hclStretchLinkConstraintSetMx::Single::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("restLength")->GetValue(restLength);
	class_instance->GetInstanceByFieldName("stiffness")->GetValue(stiffness);
	class_instance->GetInstanceByFieldName("particleA")->GetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->GetValue(particleB);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStretchLinkConstraintSetMx") {
		std::cout << "hclStretchLinkConstraintSetMx::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(singles);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("restLengths")->SetValue(restLengths);
	class_instance->GetInstanceByFieldName("stiffnesses")->SetValue(stiffnesses);
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(particlesB);
	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Single") {
		std::cout << "hclStretchLinkConstraintSetMx::Single::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("restLength")->SetValue(restLength);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(stiffness);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(particleB);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStretchLinkConstraintSetMx::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStretchLinkConstraintSetMx::Batch::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStretchLinkConstraintSetMx::Single::GetTemplateArgs() { return {
}; };

