#include "Generated\hclStretchLinkConstraintSetMx.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclStretchLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStretchLinkConstraintSetMx::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx") {
		std::cout << "hclStretchLinkConstraintSetMx::FromInstance: Expecting hclStretchLinkConstraintSetMx but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::FromInstance: Expecting hclStretchLinkConstraintSetMx::Batch but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclStretchLinkConstraintSetMx::Single::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Single") {
		std::cout << "hclStretchLinkConstraintSetMx::Single::FromInstance: Expecting hclStretchLinkConstraintSetMx::Single but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStretchLinkConstraintSetMx::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx") {
		std::cout << "hclStretchLinkConstraintSetMx::ToInstance: Expecting hclStretchLinkConstraintSetMx but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::ToInstance: Expecting hclStretchLinkConstraintSetMx::Batch but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclStretchLinkConstraintSetMx::Single::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Single") {
		std::cout << "hclStretchLinkConstraintSetMx::Single::ToInstance: Expecting hclStretchLinkConstraintSetMx::Single but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStretchLinkConstraintSetMx::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStretchLinkConstraintSetMx::Batch::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStretchLinkConstraintSetMx::Single::GetTemplateArgs() { return {
}; };

