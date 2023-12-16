#include "Generated\hclLocalRangeConstraintSet.h"

bool hktypes::hclLocalRangeConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclLocalRangeConstraintSet") {
		std::cout << "hclLocalRangeConstraintSet::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("localConstraints")->GetValue(localConstraints);
	class_instance->GetInstanceByFieldName("localStiffnessConstraints")->GetValue(localStiffnessConstraints);
	class_instance->GetInstanceByFieldName("referenceMeshBufferIdx")->GetValue(referenceMeshBufferIdx);
	class_instance->GetInstanceByFieldName("stiffness")->GetValue(stiffness);
	class_instance->GetInstanceByFieldName("shapeType")->GetValue(shapeType);
	class_instance->GetInstanceByFieldName("applyNormalComponent")->GetValue(applyNormalComponent);
	return true;
}

bool hktypes::hclLocalRangeConstraintSet::LocalConstraint::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclLocalRangeConstraintSet::LocalConstraint") {
		std::cout << "hclLocalRangeConstraintSet::LocalConstraint::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	class_instance->GetInstanceByFieldName("referenceVertex")->GetValue(referenceVertex);
	class_instance->GetInstanceByFieldName("maximumDistance")->GetValue(maximumDistance);
	class_instance->GetInstanceByFieldName("maxNormalDistance")->GetValue(maxNormalDistance);
	class_instance->GetInstanceByFieldName("minNormalDistance")->GetValue(minNormalDistance);
	return true;
}

bool hktypes::hclLocalRangeConstraintSet::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclLocalRangeConstraintSet") {
		std::cout << "hclLocalRangeConstraintSet::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("localConstraints")->SetValue(localConstraints);
	class_instance->GetInstanceByFieldName("localStiffnessConstraints")->SetValue(localStiffnessConstraints);
	class_instance->GetInstanceByFieldName("referenceMeshBufferIdx")->SetValue(referenceMeshBufferIdx);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(stiffness);
	class_instance->GetInstanceByFieldName("shapeType")->SetValue(shapeType);
	class_instance->GetInstanceByFieldName("applyNormalComponent")->SetValue(applyNormalComponent);
	return true;
}

bool hktypes::hclLocalRangeConstraintSet::LocalConstraint::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclLocalRangeConstraintSet::LocalConstraint") {
		std::cout << "hclLocalRangeConstraintSet::LocalConstraint::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	class_instance->GetInstanceByFieldName("referenceVertex")->SetValue(referenceVertex);
	class_instance->GetInstanceByFieldName("maximumDistance")->SetValue(maximumDistance);
	class_instance->GetInstanceByFieldName("maxNormalDistance")->SetValue(maxNormalDistance);
	class_instance->GetInstanceByFieldName("minNormalDistance")->SetValue(minNormalDistance);
	return true;
}

