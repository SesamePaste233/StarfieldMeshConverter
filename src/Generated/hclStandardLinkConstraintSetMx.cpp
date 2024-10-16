#include "Generated\hclStandardLinkConstraintSetMx.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclStandardLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStandardLinkConstraintSetMx::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::FromInstance: Expecting hclStandardLinkConstraintSetMx but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Batch") {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::FromInstance: Expecting hclStandardLinkConstraintSetMx::Batch but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("restLengths")->GetValue(restLengths);
	class_instance->GetInstanceByFieldName("stiffnessesA")->GetValue(stiffnessesA);
	class_instance->GetInstanceByFieldName("stiffnessesB")->GetValue(stiffnessesB);
	class_instance->GetInstanceByFieldName("particlesA")->GetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->GetValue(particlesB);
	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStandardLinkConstraintSetMx::Single::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Single") {
		std::cout << "hclStandardLinkConstraintSetMx::Single::FromInstance: Expecting hclStandardLinkConstraintSetMx::Single but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStandardLinkConstraintSetMx::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::ToInstance: Expecting hclStandardLinkConstraintSetMx but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Batch") {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::ToInstance: Expecting hclStandardLinkConstraintSetMx::Batch but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("restLengths")->SetValue(restLengths);
	class_instance->GetInstanceByFieldName("stiffnessesA")->SetValue(stiffnessesA);
	class_instance->GetInstanceByFieldName("stiffnessesB")->SetValue(stiffnessesB);
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(particlesB);
	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStandardLinkConstraintSetMx::Single::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Single") {
		std::cout << "hclStandardLinkConstraintSetMx::Single::ToInstance: Expecting hclStandardLinkConstraintSetMx::Single but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStandardLinkConstraintSetMx::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStandardLinkConstraintSetMx::Batch::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStandardLinkConstraintSetMx::Single::GetTemplateArgs() { return {
}; };

