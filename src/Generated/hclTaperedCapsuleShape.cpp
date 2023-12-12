#include "Generated\hclTaperedCapsuleShape.h"

bool hktypes::hclTaperedCapsuleShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTaperedCapsuleShape") {
		std::cout << "hclTaperedCapsuleShape::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("small")->GetValue(small);
	class_instance->GetInstanceByFieldName("big")->GetValue(big);
	class_instance->GetInstanceByFieldName("coneApex")->GetValue(coneApex);
	class_instance->GetInstanceByFieldName("coneAxis")->GetValue(coneAxis);
	class_instance->GetInstanceByFieldName("lVec")->GetValue(lVec);
	class_instance->GetInstanceByFieldName("dVec")->GetValue(dVec);
	class_instance->GetInstanceByFieldName("tanThetaVecNeg")->GetValue(tanThetaVecNeg);
	class_instance->GetInstanceByFieldName("smallRadius")->GetValue(smallRadius);
	class_instance->GetInstanceByFieldName("bigRadius")->GetValue(bigRadius);
	class_instance->GetInstanceByFieldName("l")->GetValue(l);
	class_instance->GetInstanceByFieldName("d")->GetValue(d);
	class_instance->GetInstanceByFieldName("cosTheta")->GetValue(cosTheta);
	class_instance->GetInstanceByFieldName("sinTheta")->GetValue(sinTheta);
	class_instance->GetInstanceByFieldName("tanTheta")->GetValue(tanTheta);
	class_instance->GetInstanceByFieldName("tanThetaSqr")->GetValue(tanThetaSqr);
	return true;
}

bool hktypes::hclTaperedCapsuleShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTaperedCapsuleShape") {
		std::cout << "hclTaperedCapsuleShape::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("small")->SetValue(small);
	class_instance->GetInstanceByFieldName("big")->SetValue(big);
	class_instance->GetInstanceByFieldName("coneApex")->SetValue(coneApex);
	class_instance->GetInstanceByFieldName("coneAxis")->SetValue(coneAxis);
	class_instance->GetInstanceByFieldName("lVec")->SetValue(lVec);
	class_instance->GetInstanceByFieldName("dVec")->SetValue(dVec);
	class_instance->GetInstanceByFieldName("tanThetaVecNeg")->SetValue(tanThetaVecNeg);
	class_instance->GetInstanceByFieldName("smallRadius")->SetValue(smallRadius);
	class_instance->GetInstanceByFieldName("bigRadius")->SetValue(bigRadius);
	class_instance->GetInstanceByFieldName("l")->SetValue(l);
	class_instance->GetInstanceByFieldName("d")->SetValue(d);
	class_instance->GetInstanceByFieldName("cosTheta")->SetValue(cosTheta);
	class_instance->GetInstanceByFieldName("sinTheta")->SetValue(sinTheta);
	class_instance->GetInstanceByFieldName("tanTheta")->SetValue(tanTheta);
	class_instance->GetInstanceByFieldName("tanThetaSqr")->SetValue(tanThetaSqr);
	return true;
}

