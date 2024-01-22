#include "hclShape.h"

bool hktypes::hclShape::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclShape") {
		std::cout << "hclShape::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("type")->GetValue(type);

	return true;
}

bool hktypes::hclShape::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclShape") {
		std::cout << "hclShape::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("type")->SetValue(type);

	return true;
}

bool hktypes::hclCapsuleShape::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCapsuleShape") {
		std::cout << "hclCapsuleShape::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("start")->GetValue(start);
	class_instance->GetInstanceByFieldName("end")->GetValue(end);
	class_instance->GetInstanceByFieldName("dir")->GetValue(dir);
	class_instance->GetInstanceByFieldName("radius")->GetValue(radius);
	class_instance->GetInstanceByFieldName("capLenSqrdInv")->GetValue(capLenSqrdInv);

	return true;
}

bool hktypes::hclCapsuleShape::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCapsuleShape") {
		std::cout << "hclCapsuleShape::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("start")->SetValue(start);
	class_instance->GetInstanceByFieldName("end")->SetValue(end);
	class_instance->GetInstanceByFieldName("dir")->SetValue(dir);
	class_instance->GetInstanceByFieldName("radius")->SetValue(radius);
	class_instance->GetInstanceByFieldName("capLenSqrdInv")->SetValue(capLenSqrdInv);

	return true;
}

hktypes::hclBufferedMeshObj hktypes::hclCapsuleShape::ToVisualizeMeshObj()
{
	auto ret = hclBufferedMeshObj();
	ret.shapeType = hclBufferedMeshObj::ShapeType::Capsule;
	ret.name = "Capsule";

	ret.capsuleBigRadius = radius;
	ret.capsuleSmallRadius = radius;

	Eigen::Vector3f vec_start = start.ToVector3f();
	Eigen::Vector3f vec_end = end.ToVector3f();

	ret.capsuleStart = { vec_start[0], vec_start[1], vec_start[2] };
	ret.capsuleEnd = { vec_end[0], vec_end[1], vec_end[2] };

	return ret;
}

void hktypes::hclCapsuleShape::FromParameters(const std::array<float, 3> a_start, const std::array<float, 3> a_end, const float a_radius)
{
	start = hkVector4Holder(a_start[0], a_start[1], a_start[2], 0);
	end = hkVector4Holder(a_end[0], a_end[1], a_end[2], 0);
	radius = a_radius;

	dir = hkVector4Holder::FromVector3f((end.ToVector3f() - start.ToVector3f()).normalized());

	capLenSqrdInv = 1 / (end.ToVector3f() - start.ToVector3f()).squaredNorm();
}

bool hktypes::hclTaperedCapsuleShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTaperedCapsuleShape") {
		std::cout << "hclTaperedCapsuleShape::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("small")->GetValue(m_small);
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
	class_instance->GetInstanceByFieldName("small")->SetValue(m_small);
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

hktypes::hclBufferedMeshObj hktypes::hclTaperedCapsuleShape::ToVisualizeMeshObj()
{
	auto ret = hclBufferedMeshObj();
	ret.shapeType = hclBufferedMeshObj::ShapeType::Capsule;
	ret.name = "TaperedCapsule";

	ret.capsuleBigRadius = bigRadius;
	ret.capsuleSmallRadius = smallRadius;

	Eigen::Vector3f vec_start = big.ToVector3f();
	Eigen::Vector3f vec_end = m_small.ToVector3f();

	ret.capsuleStart = { vec_start[0], vec_start[1], vec_start[2] };
	ret.capsuleEnd = { vec_end[0], vec_end[1], vec_end[2] };

	return ret;
}

void hktypes::hclTaperedCapsuleShape::FromParameters(const std::array<float, 3> a_small, const std::array<float, 3> a_big, const float a_smallRadius, const float a_bigRadius)
{
	m_small = hkVector4Holder(a_small[0], a_small[1], a_small[2], 0);
	big = hkVector4Holder(a_big[0], a_big[1], a_big[2], 0);
	smallRadius = a_smallRadius;
	bigRadius = a_bigRadius;

	float k = smallRadius / (smallRadius - bigRadius);
	coneApex = hkVector4Holder::FromVector4f(k * (big.ToVector4f() - m_small.ToVector4f()) + m_small.ToVector4f());

	coneAxis = hkVector4Holder::FromVector3f((big.ToVector3f() - m_small.ToVector3f()).normalized());

	l = (big.ToVector3f() - m_small.ToVector3f()).norm();
	d = (coneApex.ToVector3f() - m_small.ToVector3f()).norm();

	lVec = hkVector4Holder(l, l, l, l);
	dVec = hkVector4Holder(d, d, d, d);

	sinTheta = smallRadius / d;
	cosTheta = sqrt(1 - sinTheta * sinTheta);
	tanTheta = sinTheta / cosTheta;
	tanThetaSqr = tanTheta * tanTheta;

	tanThetaVecNeg = hkVector4Holder(-tanTheta, -tanTheta, -tanTheta, -tanTheta);
}
