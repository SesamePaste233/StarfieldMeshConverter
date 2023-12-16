#include "Generated\hclCompressibleLinkConstraintSetMx.h"

bool hktypes::hclCompressibleLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx") {
		std::cout << "hclCompressibleLinkConstraintSetMx::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->GetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->GetValue(singles);
	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx::Batch") {
		std::cout << "hclCompressibleLinkConstraintSetMx::Batch::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLengths")->GetValue(restLengths);
	class_instance->GetInstanceByFieldName("compressionLengths")->GetValue(compressionLengths);
	class_instance->GetInstanceByFieldName("stiffnessesA")->GetValue(stiffnessesA);
	class_instance->GetInstanceByFieldName("stiffnessesB")->GetValue(stiffnessesB);
	class_instance->GetInstanceByFieldName("particlesA")->GetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->GetValue(particlesB);
	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx::Single") {
		std::cout << "hclCompressibleLinkConstraintSetMx::Single::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLength")->GetValue(restLength);
	class_instance->GetInstanceByFieldName("compressionLength")->GetValue(compressionLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->GetValue(stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->GetValue(stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->GetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->GetValue(particleB);
	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx") {
		std::cout << "hclCompressibleLinkConstraintSetMx::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(singles);
	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx::Batch") {
		std::cout << "hclCompressibleLinkConstraintSetMx::Batch::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLengths")->SetValue(restLengths);
	class_instance->GetInstanceByFieldName("compressionLengths")->SetValue(compressionLengths);
	class_instance->GetInstanceByFieldName("stiffnessesA")->SetValue(stiffnessesA);
	class_instance->GetInstanceByFieldName("stiffnessesB")->SetValue(stiffnessesB);
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(particlesA);
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(particlesB);
	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx::Single") {
		std::cout << "hclCompressibleLinkConstraintSetMx::Single::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLength")->SetValue(restLength);
	class_instance->GetInstanceByFieldName("compressionLength")->SetValue(compressionLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->SetValue(stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->SetValue(stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(particleB);
	return true;
}

