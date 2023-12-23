#include "Generated\hclStandardLinkConstraintSetMx.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclStandardLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->GetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->GetValue(singles);
	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Batch") {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Single") {
		std::cout << "hclStandardLinkConstraintSetMx::Single::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("restLength")->GetValue(restLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->GetValue(stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->GetValue(stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->GetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->GetValue(particleB);
	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(singles);
	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Batch") {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Single") {
		std::cout << "hclStandardLinkConstraintSetMx::Single::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("restLength")->SetValue(restLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->SetValue(stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->SetValue(stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(particleB);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStandardLinkConstraintSetMx::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStandardLinkConstraintSetMx::Batch::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStandardLinkConstraintSetMx::Single::GetTemplateArgs() { return {
}; };

