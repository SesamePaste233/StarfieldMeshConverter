#include "Generated\hclLocalRangeConstraintSet.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclLocalRangeConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclLocalRangeConstraintSet") {
		std::cout << "hclLocalRangeConstraintSet::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

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

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclLocalRangeConstraintSet::LocalConstraint") {
		std::cout << "hclLocalRangeConstraintSet::LocalConstraint::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	class_instance->GetInstanceByFieldName("referenceVertex")->GetValue(referenceVertex);
	class_instance->GetInstanceByFieldName("maximumDistance")->GetValue(maximumDistance);
	class_instance->GetInstanceByFieldName("maxNormalDistance")->GetValue(maxNormalDistance);
	class_instance->GetInstanceByFieldName("minNormalDistance")->GetValue(minNormalDistance);
	return true;
}

bool hktypes::hclLocalRangeConstraintSet::LocalStiffnessConstraint::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclLocalRangeConstraintSet::LocalStiffnessConstraint") {
		std::cout << "hclLocalRangeConstraintSet::LocalStiffnessConstraint::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclLocalRangeConstraintSet::ShapeType::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclLocalRangeConstraintSet::ShapeType") {
		std::cout << "hclLocalRangeConstraintSet::ShapeType::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclLocalRangeConstraintSet::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclLocalRangeConstraintSet") {
		std::cout << "hclLocalRangeConstraintSet::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

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

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclLocalRangeConstraintSet::LocalConstraint") {
		std::cout << "hclLocalRangeConstraintSet::LocalConstraint::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	class_instance->GetInstanceByFieldName("referenceVertex")->SetValue(referenceVertex);
	class_instance->GetInstanceByFieldName("maximumDistance")->SetValue(maximumDistance);
	class_instance->GetInstanceByFieldName("maxNormalDistance")->SetValue(maxNormalDistance);
	class_instance->GetInstanceByFieldName("minNormalDistance")->SetValue(minNormalDistance);
	return true;
}

bool hktypes::hclLocalRangeConstraintSet::LocalStiffnessConstraint::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclLocalRangeConstraintSet::LocalStiffnessConstraint") {
		std::cout << "hclLocalRangeConstraintSet::LocalStiffnessConstraint::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclLocalRangeConstraintSet::ShapeType::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclLocalRangeConstraintSet::ShapeType") {
		std::cout << "hclLocalRangeConstraintSet::ShapeType::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclLocalRangeConstraintSet::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclLocalRangeConstraintSet::LocalConstraint::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclLocalRangeConstraintSet::LocalStiffnessConstraint::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclLocalRangeConstraintSet::ShapeType::GetTemplateArgs() { return {
}; };

