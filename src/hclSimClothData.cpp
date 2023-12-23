#include "hclSimClothData.h"

bool hktypes::hclConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclConstraintSet") {
		std::cout << "hclConstraintSet::FromInstance: type_name is not hclConstraintSet" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");
	class_instance->GetInstanceByFieldName("constraintId")->GetValue(this->constraintId);
	this->type = class_instance->GetUIntByFieldName("type");

	return true;
}

bool hktypes::hclConstraintSet::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclConstraintSet") {
		std::cout << "hclConstraintSet::FromInstance: type_name is not hclConstraintSet" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(this->name);
	class_instance->GetInstanceByFieldName("constraintId")->SetValue(this->constraintId);
	class_instance->GetInstanceByFieldName("type")->SetValue(this->type);

	return true;
}

bool hktypes::hclVolumeConstraint::FrameData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclVolumeConstraint::FrameData") {
		std::cout << "hclVolumeConstraint::FrameData::FromInstance: type_name is not hclVolumeConstraint::FrameData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("frameVector")->GetValue(this->frameVector);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(this->particleIndex);
	class_instance->GetInstanceByFieldName("weight")->GetValue(this->weight);

	return true;
}

bool hktypes::hclVolumeConstraint::FrameData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclVolumeConstraint::FrameData") {
		std::cout << "hclVolumeConstraint::FrameData::FromInstance: type_name is not hclVolumeConstraint::FrameData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("frameVector")->SetValue(this->frameVector);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(this->particleIndex);
	class_instance->GetInstanceByFieldName("weight")->SetValue(this->weight);

	return true;
}

bool hktypes::hclVolumeConstraint::ApplyData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclVolumeConstraint::ApplyData") {
		std::cout << "hclVolumeConstraint::ApplyData::FromInstance: type_name is not hclVolumeConstraint::ApplyData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("frameVector")->GetValue(this->frameVector);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(this->particleIndex);
	class_instance->GetInstanceByFieldName("stiffness")->GetValue(this->stiffness);

	return true;
}

bool hktypes::hclVolumeConstraint::ApplyData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclVolumeConstraint::ApplyData") {
		std::cout << "hclVolumeConstraint::ApplyData::FromInstance: type_name is not hclVolumeConstraint::ApplyData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("frameVector")->SetValue(this->frameVector);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(this->particleIndex);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(this->stiffness);

	return true;
}

bool hktypes::hclVolumeConstraint::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclVolumeConstraint") {
		std::cout << "hclVolumeConstraint::FromInstance: type_name is not hclVolumeConstraint" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("frameDatas")->GetValue(this->frameDatas);
	class_instance->GetInstanceByFieldName("applyDatas")->GetValue(this->applyDatas);

	return true;
}

bool hktypes::hclVolumeConstraint::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclVolumeConstraint") {
		std::cout << "hclVolumeConstraint::FromInstance: type_name is not hclVolumeConstraint" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("frameDatas")->SetValue(this->frameDatas);
	class_instance->GetInstanceByFieldName("applyDatas")->SetValue(this->applyDatas);

	return true;
}

bool hktypes::hclLocalRangeConstraintSet::LocalStiffnessConstraint::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclLocalRangeConstraintSet::LocalStiffnessConstraint") {
		std::cout << "hclLocalRangeConstraintSet::LocalStiffnessConstraint::FromInstance: type_name is not hclLocalRangeConstraintSet::LocalStiffnessConstraint" << std::endl;
		return false;
	}

	this->particleIndex = class_instance->GetUIntByFieldName("particleIndex");
	this->referenceVertex = class_instance->GetUIntByFieldName("referenceVertex");
	this->maximumDistance = class_instance->GetFloatByFieldName("maximumDistance");
	this->maxNormalDistance = class_instance->GetFloatByFieldName("maxNormalDistance");
	this->minNormalDistance = class_instance->GetFloatByFieldName("minNormalDistance");
	this->stiffness = class_instance->GetFloatByFieldName("stiffness");

	return true;
}

bool hktypes::hclLocalRangeConstraintSet::LocalStiffnessConstraint::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclLocalRangeConstraintSet::LocalStiffnessConstraint") {
		std::cout << "hclLocalRangeConstraintSet::LocalStiffnessConstraint::FromInstance: type_name is not hclLocalRangeConstraintSet::LocalStiffnessConstraint" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(this->particleIndex);
	class_instance->GetInstanceByFieldName("referenceVertex")->SetValue(this->referenceVertex);
	class_instance->GetInstanceByFieldName("maximumDistance")->SetValue(this->maximumDistance);
	class_instance->GetInstanceByFieldName("maxNormalDistance")->SetValue(this->maxNormalDistance);
	class_instance->GetInstanceByFieldName("minNormalDistance")->SetValue(this->minNormalDistance);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(this->stiffness);

	return true;
}

bool hktypes::hclLocalRangeConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclLocalRangeConstraintSet") {
		std::cout << "hclLocalRangeConstraintSet::FromInstance: type_name is not hclLocalRangeConstraintSet" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	this->localConstraints = class_instance->GetArrayByFieldName<LocalConstraint>("localConstraints");
	this->localStiffnessConstraints = class_instance->GetArrayByFieldName<LocalStiffnessConstraint>("localStiffnessConstraints");
	this->referenceMeshBufferIdx = class_instance->GetUIntByFieldName("referenceMeshBufferIdx");
	this->stiffness = class_instance->GetFloatByFieldName("stiffness");
	this->shapeType = (ShapeType)class_instance->GetUIntByFieldName("shapeType");
	this->applyNormalComponent = class_instance->GetBoolByFieldName("applyNormalComponent");

	return true;
}

bool hktypes::hclLocalRangeConstraintSet::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclLocalRangeConstraintSet") {
		std::cout << "hclLocalRangeConstraintSet::FromInstance: type_name is not hclLocalRangeConstraintSet" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("localConstraints")->SetValue(this->localConstraints);
	class_instance->GetInstanceByFieldName("localStiffnessConstraints")->SetValue(this->localStiffnessConstraints);
	class_instance->GetInstanceByFieldName("referenceMeshBufferIdx")->SetValue(this->referenceMeshBufferIdx);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(this->stiffness);
	uint32_t _shape_type = (uint32_t)this->shapeType;
	class_instance->GetInstanceByFieldName("shapeType")->SetValue(_shape_type);
	class_instance->GetInstanceByFieldName("applyNormalComponent")->SetValue(this->applyNormalComponent);

	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclCompressibleLinkConstraintSetMx::Batch") {
		std::cout << "hclCompressibleLinkConstraintSetMx::Batch::FromInstance: type_name is not hclCompressibleLinkConstraintSetMx::Batch" << std::endl;
		return false;
	}

	auto restLengths = class_instance->GetArrayByFieldName<float>("restLengths");
	for (int i = 0; i < 4; ++i) {
		this->restLengths[i] = restLengths[i];
	}

	auto compressionLengths = class_instance->GetArrayByFieldName<float>("compressionLengths");
	for (int i = 0; i < 4; ++i) {
		this->compressionLengths[i] = compressionLengths[i];
	}

	auto stiffnessesA = class_instance->GetArrayByFieldName<float>("stiffnessesA");
	for (int i = 0; i < 4; ++i) {
		this->stiffnessesA[i] = stiffnessesA[i];
	}

	auto stiffnessesB = class_instance->GetArrayByFieldName<float>("stiffnessesB");
	for (int i = 0; i < 4; ++i) {
		this->stiffnessesB[i] = stiffnessesB[i];
	}

	auto particlesA = class_instance->GetArrayByFieldName<uint16_t>("particlesA");
	for (int i = 0; i < 4; ++i) {
		this->particlesA[i] = particlesA[i];
	}

	auto particlesB = class_instance->GetArrayByFieldName<uint16_t>("particlesB");
	for (int i = 0; i < 4; ++i) {
		this->particlesB[i] = particlesB[i];
	}

	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclCompressibleLinkConstraintSetMx::Batch") {
		std::cout << "hclCompressibleLinkConstraintSetMx::Batch::FromInstance: type_name is not hclCompressibleLinkConstraintSetMx::Batch" << std::endl;
		return false;
	}

	std::vector<float> _rest_lengths = { this->restLengths[0], this->restLengths[1], this->restLengths[2], this->restLengths[3] };
	class_instance->GetInstanceByFieldName("restLengths")->SetValue(_rest_lengths);

	std::vector<float> _compression_lengths = { this->compressionLengths[0], this->compressionLengths[1], this->compressionLengths[2], this->compressionLengths[3] };
	class_instance->GetInstanceByFieldName("compressionLengths")->SetValue(_compression_lengths);

	std::vector<float> _stiffnesses_a = { this->stiffnessesA[0], this->stiffnessesA[1], this->stiffnessesA[2], this->stiffnessesA[3] };
	class_instance->GetInstanceByFieldName("stiffnessesA")->SetValue(_stiffnesses_a);

	std::vector<float> _stiffnesses_b = { this->stiffnessesB[0], this->stiffnessesB[1], this->stiffnessesB[2], this->stiffnessesB[3] };
	class_instance->GetInstanceByFieldName("stiffnessesB")->SetValue(_stiffnesses_b);

	std::vector<uint16_t> _particles_a = { this->particlesA[0], this->particlesA[1], this->particlesA[2], this->particlesA[3] };
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(_particles_a);

	std::vector<uint16_t> _particles_b = { this->particlesB[0], this->particlesB[1], this->particlesB[2], this->particlesB[3] };
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(_particles_b);

	return true;

}

bool hktypes::hclCompressibleLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclCompressibleLinkConstraintSetMx::Single") {
		std::cout << "hclCompressibleLinkConstraintSetMx::Single::FromInstance: type_name is not hclCompressibleLinkConstraintSetMx::Single" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLength")->GetValue(this->restLength);
	class_instance->GetInstanceByFieldName("compressionLength")->GetValue(this->compressionLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->GetValue(this->stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->GetValue(this->stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->GetValue(this->particleA);
	class_instance->GetInstanceByFieldName("particleB")->GetValue(this->particleB);

	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclCompressibleLinkConstraintSetMx::Single") {
		std::cout << "hclCompressibleLinkConstraintSetMx::Single::FromInstance: type_name is not hclCompressibleLinkConstraintSetMx::Single" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLength")->SetValue(this->restLength);
	class_instance->GetInstanceByFieldName("compressionLength")->SetValue(this->compressionLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->SetValue(this->stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->SetValue(this->stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(this->particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(this->particleB);

	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclCompressibleLinkConstraintSetMx") {
		std::cout << "hclCompressibleLinkConstraintSetMx::FromInstance: type_name is not hclCompressibleLinkConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	this->batches = class_instance->GetArrayByFieldName<Batch>("batches");
	this->singles = class_instance->GetArrayByFieldName<Single>("singles");

	return true;
}

bool hktypes::hclCompressibleLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclCompressibleLinkConstraintSetMx") {
		std::cout << "hclCompressibleLinkConstraintSetMx::FromInstance: type_name is not hclCompressibleLinkConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(this->batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(this->singles);

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclBendStiffnessConstraintSetMx::Batch") {
		std::cout << "hclBendStiffnessConstraintSetMx::Batch::FromInstance: type_name is not hclBendStiffnessConstraintSetMx::Batch" << std::endl;
		return false;
	}

	std::vector<float> weightsA;
	class_instance->GetInstanceByFieldName("weightsA")->GetValue(weightsA);
	for (int i = 0; i < 4; ++i) {
		this->weightsA[i] = weightsA[i];
	}

	std::vector<float> weightsB;
	class_instance->GetInstanceByFieldName("weightsB")->GetValue(weightsB);
	for (int i = 0; i < 4; ++i) {
		this->weightsB[i] = weightsB[i];
	}

	std::vector<float> weightsC;
	class_instance->GetInstanceByFieldName("weightsC")->GetValue(weightsC);
	for (int i = 0; i < 4; ++i) {
		this->weightsC[i] = weightsC[i];
	}

	std::vector<float> weightsD;
	class_instance->GetInstanceByFieldName("weightsD")->GetValue(weightsD);
	for (int i = 0; i < 4; ++i) {
		this->weightsD[i] = weightsD[i];
	}

	std::vector<float> bendStiffnesses;
	class_instance->GetInstanceByFieldName("bendStiffnesses")->GetValue(bendStiffnesses);
	for (int i = 0; i < 4; ++i) {
		this->bendStiffnesses[i] = bendStiffnesses[i];
	}

	std::vector<float> restCurvatures;
	class_instance->GetInstanceByFieldName("restCurvatures")->GetValue(restCurvatures);
	for (int i = 0; i < 4; ++i) {
		this->restCurvatures[i] = restCurvatures[i];
	}

	std::vector<float> invMassesA;
	class_instance->GetInstanceByFieldName("invMassesA")->GetValue(invMassesA);
	for (int i = 0; i < 4; ++i) {
		this->invMassesA[i] = invMassesA[i];
	}

	std::vector<float> invMassesB;
	class_instance->GetInstanceByFieldName("invMassesB")->GetValue(invMassesB);
	for (int i = 0; i < 4; ++i) {
		this->invMassesB[i] = invMassesB[i];
	}

	std::vector<float> invMassesC;
	class_instance->GetInstanceByFieldName("invMassesC")->GetValue(invMassesC);
	for (int i = 0; i < 4; ++i) {
		this->invMassesC[i] = invMassesC[i];
	}

	std::vector<float> invMassesD;
	class_instance->GetInstanceByFieldName("invMassesD")->GetValue(invMassesD);
	for (int i = 0; i < 4; ++i) {
		this->invMassesD[i] = invMassesD[i];
	}

	std::vector<uint16_t> particlesA;
	class_instance->GetInstanceByFieldName("particlesA")->GetValue(particlesA);
	for (int i = 0; i < 4; ++i) {
		this->particlesA[i] = particlesA[i];
	}

	std::vector<uint16_t> particlesB;
	class_instance->GetInstanceByFieldName("particlesB")->GetValue(particlesB);
	for (int i = 0; i < 4; ++i) {
		this->particlesB[i] = particlesB[i];
	}

	std::vector<uint16_t> particlesC;
	class_instance->GetInstanceByFieldName("particlesC")->GetValue(particlesC);
	for (int i = 0; i < 4; ++i) {
		this->particlesC[i] = particlesC[i];
	}

	std::vector<uint16_t> particlesD;
	class_instance->GetInstanceByFieldName("particlesD")->GetValue(particlesD);
	for (int i = 0; i < 4; ++i) {
		this->particlesD[i] = particlesD[i];
	}

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclBendStiffnessConstraintSetMx::Batch") {
		std::cout << "hclBendStiffnessConstraintSetMx::Batch::FromInstance: type_name is not hclBendStiffnessConstraintSetMx::Batch" << std::endl;
		return false;
	}

	std::vector<float> _weights_a = { this->weightsA[0], this->weightsA[1], this->weightsA[2], this->weightsA[3] };
	class_instance->GetInstanceByFieldName("weightsA")->SetValue(_weights_a);

	std::vector<float> _weights_b = { this->weightsB[0], this->weightsB[1], this->weightsB[2], this->weightsB[3] };
	class_instance->GetInstanceByFieldName("weightsB")->SetValue(_weights_b);

	std::vector<float> _weights_c = { this->weightsC[0], this->weightsC[1], this->weightsC[2], this->weightsC[3] };
	class_instance->GetInstanceByFieldName("weightsC")->SetValue(_weights_c);

	std::vector<float> _weights_d = { this->weightsD[0], this->weightsD[1], this->weightsD[2], this->weightsD[3] };
	class_instance->GetInstanceByFieldName("weightsD")->SetValue(_weights_d);

	std::vector<float> _bend_stiffnesses = { this->bendStiffnesses[0], this->bendStiffnesses[1], this->bendStiffnesses[2], this->bendStiffnesses[3] };
	class_instance->GetInstanceByFieldName("bendStiffnesses")->SetValue(_bend_stiffnesses);

	std::vector<float> _rest_curvatures = { this->restCurvatures[0], this->restCurvatures[1], this->restCurvatures[2], this->restCurvatures[3] };
	class_instance->GetInstanceByFieldName("restCurvatures")->SetValue(_rest_curvatures);

	std::vector<float> _inv_masses_a = { this->invMassesA[0], this->invMassesA[1], this->invMassesA[2], this->invMassesA[3] };
	class_instance->GetInstanceByFieldName("invMassesA")->SetValue(_inv_masses_a);

	std::vector<float> _inv_masses_b = { this->invMassesB[0], this->invMassesB[1], this->invMassesB[2], this->invMassesB[3] };
	class_instance->GetInstanceByFieldName("invMassesB")->SetValue(_inv_masses_b);

	std::vector<float> _inv_masses_c = { this->invMassesC[0], this->invMassesC[1], this->invMassesC[2], this->invMassesC[3] };
	class_instance->GetInstanceByFieldName("invMassesC")->SetValue(_inv_masses_c);

	std::vector<float> _inv_masses_d = { this->invMassesD[0], this->invMassesD[1], this->invMassesD[2], this->invMassesD[3] };
	class_instance->GetInstanceByFieldName("invMassesD")->SetValue(_inv_masses_d);

	std::vector<uint16_t> _particles_a = { this->particlesA[0], this->particlesA[1], this->particlesA[2], this->particlesA[3] };
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(_particles_a);

	std::vector<uint16_t> _particles_b = { this->particlesB[0], this->particlesB[1], this->particlesB[2], this->particlesB[3] };
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(_particles_b);

	std::vector<uint16_t> _particles_c = { this->particlesC[0], this->particlesC[1], this->particlesC[2], this->particlesC[3] };
	class_instance->GetInstanceByFieldName("particlesC")->SetValue(_particles_c);

	std::vector<uint16_t> _particles_d = { this->particlesD[0], this->particlesD[1], this->particlesD[2], this->particlesD[3] };
	class_instance->GetInstanceByFieldName("particlesD")->SetValue(_particles_d);

	return true;

}

bool hktypes::hclBendStiffnessConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclBendStiffnessConstraintSetMx::Single") {
		std::cout << "hclBendStiffnessConstraintSetMx::Single::FromInstance: type_name is not hclBendStiffnessConstraintSetMx::Single" << std::endl;
		return false;
	}

	// TODO

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclBendStiffnessConstraintSetMx::Single") {
		std::cout << "hclBendStiffnessConstraintSetMx::Single::FromInstance: type_name is not hclBendStiffnessConstraintSetMx::Single" << std::endl;
		return false;
	}

	// TODO

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclBendStiffnessConstraintSetMx") {
		std::cout << "hclBendStiffnessConstraintSetMx::FromInstance: type_name is not hclBendStiffnessConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->GetValue(this->batches);
	class_instance->GetInstanceByFieldName("singles")->GetValue(this->singles);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->GetValue(this->maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->GetValue(this->clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->GetValue(this->useRestPoseConfig);

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclBendStiffnessConstraintSetMx") {
		std::cout << "hclBendStiffnessConstraintSetMx::FromInstance: type_name is not hclBendStiffnessConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(this->batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(this->singles);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->SetValue(this->maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->SetValue(this->clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->SetValue(this->useRestPoseConfig);

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStandardLinkConstraintSetMx::Batch") {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::FromInstance: type_name is not hclStandardLinkConstraintSetMx::Batch" << std::endl;
		return false;
	}

	auto restLengths = class_instance->GetArrayByFieldName<float>("restLengths");
	for (int i = 0; i < 4; ++i) {
		this->restLengths[i] = restLengths[i];
	}

	auto stiffnessesA = class_instance->GetArrayByFieldName<float>("stiffnessesA");
	for (int i = 0; i < 4; ++i) {
		this->stiffnessesA[i] = stiffnessesA[i];
	}

	auto stiffnessesB = class_instance->GetArrayByFieldName<float>("stiffnessesB");
	for (int i = 0; i < 4; ++i) {
		this->stiffnessesB[i] = stiffnessesB[i];
	}

	auto particlesA = class_instance->GetArrayByFieldName<uint16_t>("particlesA");
	for (int i = 0; i < 4; ++i) {
		this->particlesA[i] = particlesA[i];
	}

	auto particlesB = class_instance->GetArrayByFieldName<uint16_t>("particlesB");
	for (int i = 0; i < 4; ++i) {
		this->particlesB[i] = particlesB[i];
	}

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStandardLinkConstraintSetMx::Batch") {
		std::cout << "hclStandardLinkConstraintSetMx::Batch::FromInstance: type_name is not hclStandardLinkConstraintSetMx::Batch" << std::endl;
		return false;
	}

	std::vector<float> _rest_lengths = { this->restLengths[0], this->restLengths[1], this->restLengths[2], this->restLengths[3] };
	class_instance->GetInstanceByFieldName("restLengths")->SetValue(_rest_lengths);

	std::vector<float> _stiffnesses_a = { this->stiffnessesA[0], this->stiffnessesA[1], this->stiffnessesA[2], this->stiffnessesA[3] };
	class_instance->GetInstanceByFieldName("stiffnessesA")->SetValue(_stiffnesses_a);

	std::vector<float> _stiffnesses_b = { this->stiffnessesB[0], this->stiffnessesB[1], this->stiffnessesB[2], this->stiffnessesB[3] };
	class_instance->GetInstanceByFieldName("stiffnessesB")->SetValue(_stiffnesses_b);

	std::vector<uint16_t> _particles_a = { this->particlesA[0], this->particlesA[1], this->particlesA[2], this->particlesA[3] };
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(_particles_a);

	std::vector<uint16_t> _particles_b = { this->particlesB[0], this->particlesB[1], this->particlesB[2], this->particlesB[3] };
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(_particles_b);

	return true;

}

bool hktypes::hclStandardLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStandardLinkConstraintSetMx::Single") {
		std::cout << "hclStandardLinkConstraintSetMx::Single::FromInstance: type_name is not hclStandardLinkConstraintSetMx::Single" << std::endl;
		return false;
	}

	this->restLength = class_instance->GetFloatByFieldName("restLength");
	this->stiffnessA = class_instance->GetFloatByFieldName("stiffnessA");
	this->stiffnessB = class_instance->GetFloatByFieldName("stiffnessB");
	this->particleA = class_instance->GetUIntByFieldName("particleA");
	this->particleB = class_instance->GetUIntByFieldName("particleB");

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStandardLinkConstraintSetMx::Single") {
		std::cout << "hclStandardLinkConstraintSetMx::Single::FromInstance: type_name is not hclStandardLinkConstraintSetMx::Single" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLength")->SetValue(this->restLength);
	class_instance->GetInstanceByFieldName("stiffnessA")->SetValue(this->stiffnessA);
	class_instance->GetInstanceByFieldName("stiffnessB")->SetValue(this->stiffnessB);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(this->particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(this->particleB);

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::FromInstance: type_name is not hclStandardLinkConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	this->batches = class_instance->GetArrayByFieldName<Batch>("batches");
	this->singles = class_instance->GetArrayByFieldName<Single>("singles");

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::FromInstance: type_name is not hclStandardLinkConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(this->batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(this->singles);

	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::FromInstance: type_name is not hclStretchLinkConstraintSetMx::Batch" << std::endl;
		return false;
	}

	auto restLengths = class_instance->GetArrayByFieldName<float>("restLengths");
	for (int i = 0; i < 4; ++i) {
		this->restLengths[i] = restLengths[i];
	}

	auto stiffnesses = class_instance->GetArrayByFieldName<float>("stiffnesses");
	for (int i = 0; i < 4; ++i) {
		this->stiffnesses[i] = stiffnesses[i];
	}

	auto particlesA = class_instance->GetArrayByFieldName<uint16_t>("particlesA");
	for (int i = 0; i < 4; ++i) {
		this->particlesA[i] = particlesA[i];
	}

	auto particlesB = class_instance->GetArrayByFieldName<uint16_t>("particlesB");
	for (int i = 0; i < 4; ++i) {
		this->particlesB[i] = particlesB[i];
	}

	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::FromInstance: type_name is not hclStretchLinkConstraintSetMx::Batch" << std::endl;
		return false;
	}

	std::vector<float> _rest_lengths = { this->restLengths[0], this->restLengths[1], this->restLengths[2], this->restLengths[3] };
	class_instance->GetInstanceByFieldName("restLengths")->SetValue(_rest_lengths);

	std::vector<float> _stiffnesses_a = { this->stiffnesses[0], this->stiffnesses[1], this->stiffnesses[2], this->stiffnesses[3] };
	class_instance->GetInstanceByFieldName("stiffnessesA")->SetValue(_stiffnesses_a);

	std::vector<uint16_t> _particles_a = { this->particlesA[0], this->particlesA[1], this->particlesA[2], this->particlesA[3] };
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(_particles_a);

	std::vector<uint16_t> _particles_b = { this->particlesB[0], this->particlesB[1], this->particlesB[2], this->particlesB[3] };
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(_particles_b);

	return true;

}

bool hktypes::hclStretchLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStretchLinkConstraintSetMx::Single") {
		std::cout << "hclStretchLinkConstraintSetMx::Single::FromInstance: type_name is not hclStretchLinkConstraintSetMx::Single" << std::endl;
		return false;
	}

	this->restLength = class_instance->GetFloatByFieldName("restLength");
	this->stiffness = class_instance->GetFloatByFieldName("stiffness");
	this->particleA = class_instance->GetUIntByFieldName("particleA");
	this->particleB = class_instance->GetUIntByFieldName("particleB");

	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStretchLinkConstraintSetMx::Single") {
		std::cout << "hclStretchLinkConstraintSetMx::Single::FromInstance: type_name is not hclStretchLinkConstraintSetMx::Single" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("restLength")->SetValue(this->restLength);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(this->stiffness);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(this->particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(this->particleB);

	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStretchLinkConstraintSetMx") {
		std::cout << "hclStretchLinkConstraintSetMx::FromInstance: type_name is not hclStretchLinkConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	this->batches = class_instance->GetArrayByFieldName<Batch>("batches");
	this->singles = class_instance->GetArrayByFieldName<Single>("singles");

	return true;
}

bool hktypes::hclStretchLinkConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStretchLinkConstraintSetMx") {
		std::cout << "hclStretchLinkConstraintSetMx::FromInstance: type_name is not hclStretchLinkConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(this->batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(this->singles);

	return true;
}

bool hktypes::hclSimClothPose::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothPose") {
		std::cout << "hclSimClothPose::FromInstance: type_name is not hclSimClothPose" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");

	class_instance->GetInstanceByFieldName("positions")->GetValue(positions);

	return true;
}

bool hktypes::hclSimClothPose::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothPose") {
		std::cout << "hclSimClothPose::FromInstance: type_name is not hclSimClothPose" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(this->name);

	class_instance->GetInstanceByFieldName("positions")->SetValue(positions);

	return true;
}

bool hktypes::hclSimClothData::OverridableSimulationInfo::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::OverridableSimulationInfo") {
		std::cout << "hclSimClothData::OverridableSimulationInfo::FromInstance: type_name is not hclSimClothData::OverridableSimulationInfo" << std::endl;
		return false;
	}

	std::vector<float> _gravity = class_instance->GetArrayByFieldName<float>("gravity");
	for (int i = 0; i < 4; ++i) {
		this->gravity[i] = _gravity[i];
	}

	this->globalDampingPerSecond = class_instance->GetFloatByFieldName("globalDampingPerSecond");

	return true;
}

bool hktypes::hclSimClothData::OverridableSimulationInfo::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::OverridableSimulationInfo") {
		std::cout << "hclSimClothData::OverridableSimulationInfo::FromInstance: type_name is not hclSimClothData::OverridableSimulationInfo" << std::endl;
		return false;
	}

	std::vector<float> _gravity = { this->gravity[0], this->gravity[1], this->gravity[2], this->gravity[3] };
	class_instance->GetInstanceByFieldName("gravity")->SetValue(_gravity);

	class_instance->GetInstanceByFieldName("globalDampingPerSecond")->SetValue(this->globalDampingPerSecond);

	return true;
}

bool hktypes::hclSimClothData::ParticleData::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::ParticleData") {
		std::cout << "hclSimClothData::ParticleData::FromInstance: type_name is not hclSimClothData::ParticleData" << std::endl;
		return false;
	}

	this->mass = class_instance->GetFloatByFieldName("mass");
	this->invMass = class_instance->GetFloatByFieldName("invMass");
	this->radius = class_instance->GetFloatByFieldName("radius");
	this->friction = class_instance->GetFloatByFieldName("friction");

	return true;
}

bool hktypes::hclSimClothData::ParticleData::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::ParticleData") {
		std::cout << "hclSimClothData::ParticleData::FromInstance: type_name is not hclSimClothData::ParticleData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("mass")->SetValue(this->mass);
	class_instance->GetInstanceByFieldName("invMass")->SetValue(this->invMass);
	class_instance->GetInstanceByFieldName("radius")->SetValue(this->radius);
	class_instance->GetInstanceByFieldName("friction")->SetValue(this->friction);

	return true;
}

bool hktypes::hclSimClothData::CollidableTransformMap::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::CollidableTransformMap") {
		std::cout << "hclSimClothData::CollidableTransformMap::FromInstance: type_name is not hclSimClothData::CollidableTransformMap" << std::endl;
		return false;
	}

	this->transformSetIndex = class_instance->GetIntByFieldName("transformSetIndex");
	this->offsets = class_instance->GetArrayByFieldName<hkMatrix4Holder>("offsets");
	this->transformIndices = class_instance->GetArrayByFieldName<uint32_t>("transformIndices");

	return true;
}

bool hktypes::hclSimClothData::CollidableTransformMap::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::CollidableTransformMap") {
		std::cout << "hclSimClothData::CollidableTransformMap::FromInstance: type_name is not hclSimClothData::CollidableTransformMap" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(this->transformSetIndex);
	class_instance->GetInstanceByFieldName("offsets")->SetValue(this->offsets);
	class_instance->GetInstanceByFieldName("transformIndices")->SetValue(this->transformIndices);

	return true;
}

bool hktypes::hclSimClothData::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData") {
		std::cout << "hclSimClothData::FromInstance: type_name is not hclSimClothData" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");
	class_instance->GetInstanceByFieldName("simulationInfo")->GetValue(this->simulationInfo);
	this->particleDatas = class_instance->GetArrayByFieldName<ParticleData>("particleDatas");
	this->fixedParticles = class_instance->GetArrayByFieldName<uint16_t>("fixedParticles");
	this->doNormals = class_instance->GetBoolByFieldName("doNormals");
	this->simOpIds = class_instance->GetArrayByFieldName<uint32_t>("simOpIds");
	this->simClothPoses = class_instance->GetArrayOfPointersByFieldName<hclSimClothPose>("simClothPoses");
	this->staticConstraintSets = class_instance->GetArrayOfPointersByFieldName<hclConstraintSet>("staticConstraintSets");
	this->antiPinchConstraintSets = class_instance->GetArrayOfPointersByFieldName<hclConstraintSet>("antiPinchConstraintSets");
	class_instance->GetInstanceByFieldName("collidableTransformMap")->GetValue(this->collidableTransformMap);
	this->perInstanceCollidables = class_instance->GetArrayOfPointersByFieldName<hclCollidable>("perInstanceCollidables");
	this->maxParticleRadius = class_instance->GetFloatByFieldName("maxParticleRadius");
	this->staticCollisionMasks = class_instance->GetArrayByFieldName<uint32_t>("staticCollisionMasks");
	this->totalMass = class_instance->GetFloatByFieldName("totalMass");
	class_instance->GetInstanceByFieldName("transferMotionData")->GetValue(this->transferMotionData);
	this->transferMotionEnabled = class_instance->GetBoolByFieldName("transferMotionEnabled");
	this->landscapeCollisionEnabled = class_instance->GetBoolByFieldName("landscapeCollisionEnabled");
	class_instance->GetInstanceByFieldName("landscapeCollisionData")->GetValue(this->landscapeCollisionData);
	this->numLandscapeCollidableParticles = class_instance->GetUIntByFieldName("numLandscapeCollidableParticles");
	this->triangleIndices = class_instance->GetArrayByFieldName<uint16_t>("triangleIndices");
	this->triangleFlips = class_instance->GetArrayByFieldName<uint8_t>("triangleFlips");
	this->pinchDetectionEnabled = class_instance->GetBoolByFieldName("pinchDetectionEnabled");
	this->perParticlePinchDetectionEnabledFlags = class_instance->GetArrayByFieldName<bool>("perParticlePinchDetectionEnabledFlags");
	this->minPinchedParticleIndex = class_instance->GetUIntByFieldName("minPinchedParticleIndex");
	this->maxPinchedParticleIndex = class_instance->GetUIntByFieldName("maxPinchedParticleIndex");
	this->maxCollisionPairs = class_instance->GetUIntByFieldName("maxCollisionPairs");

	return true;
}

bool hktypes::hclSimClothData::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData") {
		std::cout << "hclSimClothData::FromInstance: type_name is not hclSimClothData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(this->name);
	class_instance->GetInstanceByFieldName("simulationInfo")->SetValue(this->simulationInfo);
	class_instance->GetInstanceByFieldName("particleDatas")->SetValue(this->particleDatas);
	class_instance->GetInstanceByFieldName("fixedParticles")->SetValue(this->fixedParticles);
	class_instance->GetInstanceByFieldName("doNormals")->SetValue(this->doNormals);
	class_instance->GetInstanceByFieldName("simOpIds")->SetValue(this->simOpIds);
	std::vector<hclSimClothPose> _sim_cloth_poses;
	for (int i = 0; i < this->simClothPoses.size(); ++i) {
		_sim_cloth_poses.push_back(*this->simClothPoses[i]);
	}
	class_instance->GetInstanceByFieldName("simClothPoses")->SetValue(_sim_cloth_poses);

	std::vector<hclConstraintSet> _static_constraint_sets;
	for (int i = 0; i < this->staticConstraintSets.size(); ++i) {
		_static_constraint_sets.push_back(*this->staticConstraintSets[i]);
	}
	class_instance->GetInstanceByFieldName("staticConstraintSets")->SetValue(_static_constraint_sets);

	std::vector<hclConstraintSet> _anti_pinch_constraint_sets;
	for (int i = 0; i < this->antiPinchConstraintSets.size(); ++i) {
		_anti_pinch_constraint_sets.push_back(*this->antiPinchConstraintSets[i]);
	}
	class_instance->GetInstanceByFieldName("antiPinchConstraintSets")->SetValue(_anti_pinch_constraint_sets);

	class_instance->GetInstanceByFieldName("collidableTransformMap")->SetValue(this->collidableTransformMap);

	std::vector<hclCollidable> _per_instance_collidables;
	for (int i = 0; i < this->perInstanceCollidables.size(); ++i) {
		_per_instance_collidables.push_back(*this->perInstanceCollidables[i]);
	}
	class_instance->GetInstanceByFieldName("perInstanceCollidables")->SetValue(_per_instance_collidables);

	class_instance->GetInstanceByFieldName("maxParticleRadius")->SetValue(this->maxParticleRadius);
	class_instance->GetInstanceByFieldName("staticCollisionMasks")->SetValue(this->staticCollisionMasks);
	class_instance->GetInstanceByFieldName("totalMass")->SetValue(this->totalMass);
	class_instance->GetInstanceByFieldName("transferMotionData")->SetValue(this->transferMotionData);
	class_instance->GetInstanceByFieldName("transferMotionEnabled")->SetValue(this->transferMotionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionEnabled")->SetValue(this->landscapeCollisionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionData")->SetValue(this->landscapeCollisionData);
	class_instance->GetInstanceByFieldName("numLandscapeCollidableParticles")->SetValue(this->numLandscapeCollidableParticles);
	class_instance->GetInstanceByFieldName("triangleIndices")->SetValue(this->triangleIndices);
	class_instance->GetInstanceByFieldName("triangleFlips")->SetValue(this->triangleFlips);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(this->pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("perParticlePinchDetectionEnabledFlags")->SetValue(this->perParticlePinchDetectionEnabledFlags);
	class_instance->GetInstanceByFieldName("minPinchedParticleIndex")->SetValue(this->minPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxPinchedParticleIndex")->SetValue(this->maxPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxCollisionPairs")->SetValue(this->maxCollisionPairs);

	return true;
}

bool hktypes::hclCollidable::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclCollidable") {
		std::cout << "hclCollidable::FromInstance: type_name is not hclCollidable" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");
	class_instance->GetInstanceByFieldName("transform")->GetValue(this->transform);
	class_instance->GetInstanceByFieldName("linearVelocity")->GetValue(this->linearVelocity);
	class_instance->GetInstanceByFieldName("angularVelocity")->GetValue(this->angularVelocity);
	this->pinchDetectionEnabled = class_instance->GetBoolByFieldName("pinchDetectionEnabled");
	this->pinchDetectionRadius = class_instance->GetFloatByFieldName("pinchDetectionRadius");
	this->pinchDetectionPriority = class_instance->GetIntByFieldName("pinchDetectionPriority");
	class_instance->GetInstanceByFieldName("shape")->GetValue(this->shape);

	return true;
}

bool hktypes::hclCollidable::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclCollidable") {
		std::cout << "hclCollidable::FromInstance: type_name is not hclCollidable" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(this->name);
	class_instance->GetInstanceByFieldName("transform")->SetValue(this->transform);
	class_instance->GetInstanceByFieldName("linearVelocity")->SetValue(this->linearVelocity);
	class_instance->GetInstanceByFieldName("angularVelocity")->SetValue(this->angularVelocity);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(this->pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->SetValue(this->pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->SetValue(this->pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("shape")->SetValue(this->shape);

	return true;
}

bool hktypes::hclSimClothData::TransferMotionData::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::TransferMotionData") {
		std::cout << "hclSimClothData::TransferMotionData::FromInstance: type_name is not hclSimClothData::TransferMotionData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(this->transformSetIndex);
	class_instance->GetInstanceByFieldName("transformIndex")->GetValue(this->transformIndex);
	class_instance->GetInstanceByFieldName("transferTranslationMotion")->GetValue(this->transferTranslationMotion);
	class_instance->GetInstanceByFieldName("minTranslationSpeed")->GetValue(this->minTranslationSpeed);
	class_instance->GetInstanceByFieldName("maxTranslationSpeed")->GetValue(this->maxTranslationSpeed);
	class_instance->GetInstanceByFieldName("minTranslationBlend")->GetValue(this->minTranslationBlend);
	class_instance->GetInstanceByFieldName("maxTranslationBlend")->GetValue(this->maxTranslationBlend);
	class_instance->GetInstanceByFieldName("transferRotationMotion")->GetValue(this->transferRotationMotion);
	class_instance->GetInstanceByFieldName("minRotationSpeed")->GetValue(this->minRotationSpeed);
	class_instance->GetInstanceByFieldName("maxRotationSpeed")->GetValue(this->maxRotationSpeed);
	class_instance->GetInstanceByFieldName("minRotationBlend")->GetValue(this->minRotationBlend);
	class_instance->GetInstanceByFieldName("maxRotationBlend")->GetValue(this->maxRotationBlend);

	return true;
}

bool hktypes::hclSimClothData::TransferMotionData::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::TransferMotionData") {
		std::cout << "hclSimClothData::TransferMotionData::FromInstance: type_name is not hclSimClothData::TransferMotionData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(this->transformSetIndex);
	class_instance->GetInstanceByFieldName("transformIndex")->SetValue(this->transformIndex);
	class_instance->GetInstanceByFieldName("transferTranslationMotion")->SetValue(this->transferTranslationMotion);
	class_instance->GetInstanceByFieldName("minTranslationSpeed")->SetValue(this->minTranslationSpeed);
	class_instance->GetInstanceByFieldName("maxTranslationSpeed")->SetValue(this->maxTranslationSpeed);
	class_instance->GetInstanceByFieldName("minTranslationBlend")->SetValue(this->minTranslationBlend);
	class_instance->GetInstanceByFieldName("maxTranslationBlend")->SetValue(this->maxTranslationBlend);
	class_instance->GetInstanceByFieldName("transferRotationMotion")->SetValue(this->transferRotationMotion);
	class_instance->GetInstanceByFieldName("minRotationSpeed")->SetValue(this->minRotationSpeed);
	class_instance->GetInstanceByFieldName("maxRotationSpeed")->SetValue(this->maxRotationSpeed);
	class_instance->GetInstanceByFieldName("minRotationBlend")->SetValue(this->minRotationBlend);
	class_instance->GetInstanceByFieldName("maxRotationBlend")->SetValue(this->maxRotationBlend);

	return true;
}

bool hktypes::hclSimClothData::LandscapeCollisionData::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclSimClothData::LandscapeCollisionData") {
		std::cout << "hclSimClothData::LandscapeCollisionData::FromInstance: type_name is not hclSimClothData::LandscapeCollisionData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("landscapeRadius")->GetValue(this->landscapeRadius);
	class_instance->GetInstanceByFieldName("enableStuckParticleDetection")->GetValue(this->enableStuckParticleDetection);
	class_instance->GetInstanceByFieldName("stuckParticlesStretchFactorSq")->GetValue(this->stuckParticlesStretchFactorSq);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->GetValue(this->pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->GetValue(this->pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->GetValue(this->pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("collisionTolerance")->GetValue(this->collisionTolerance);

	return true;
}

bool hktypes::hclSimClothData::LandscapeCollisionData::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclSimClothData::LandscapeCollisionData") {
		std::cout << "hclSimClothData::LandscapeCollisionData::FromInstance: type_name is not hclSimClothData::LandscapeCollisionData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("landscapeRadius")->SetValue(this->landscapeRadius);
	class_instance->GetInstanceByFieldName("enableStuckParticleDetection")->SetValue(this->enableStuckParticleDetection);
	class_instance->GetInstanceByFieldName("stuckParticlesStretchFactorSq")->SetValue(this->stuckParticlesStretchFactorSq);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(this->pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->SetValue(this->pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->SetValue(this->pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("collisionTolerance")->SetValue(this->collisionTolerance);

	return true;
}

bool hktypes::hclBonePlanesConstraintSet::BonePlane::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclBonePlanesConstraintSet::BonePlane") {
		std::cout << "hclBonePlanesConstraintSet::BonePlane::FromInstance: type_name is not hclBonePlanesConstraintSet::BonePlane" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("planeEquationBone")->GetValue(this->planeEquationBone);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(this->particleIndex);
	class_instance->GetInstanceByFieldName("transformIndex")->GetValue(this->transformIndex);
	class_instance->GetInstanceByFieldName("stiffness")->GetValue(this->stiffness);

	return true;
}

bool hktypes::hclBonePlanesConstraintSet::BonePlane::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclBonePlanesConstraintSet::BonePlane") {
		std::cout << "hclBonePlanesConstraintSet::BonePlane::FromInstance: type_name is not hclBonePlanesConstraintSet::BonePlane" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("planeEquationBone")->SetValue(this->planeEquationBone);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(this->particleIndex);
	class_instance->GetInstanceByFieldName("transformIndex")->SetValue(this->transformIndex);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(this->stiffness);

	return true;
}

bool hktypes::hclBonePlanesConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclBonePlanesConstraintSet") {
		std::cout << "hclBonePlanesConstraintSet::FromInstance: type_name is not hclBonePlanesConstraintSet" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("bonePlanes")->GetValue(this->bonePlanes);
	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(this->transformSetIndex);

	return true;
}

bool hktypes::hclBonePlanesConstraintSet::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclBonePlanesConstraintSet") {
		std::cout << "hclBonePlanesConstraintSet::FromInstance: type_name is not hclBonePlanesConstraintSet" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("bonePlanes")->SetValue(this->bonePlanes);
	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(this->transformSetIndex);

	return true;
}

bool hktypes::hclSimClothData::CollidablePinchingData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::CollidablePinchingData") {
		std::cout << "hclSimClothData::CollidablePinchingData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->GetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->GetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->GetValue(pinchDetectionRadius);
	return true;
}

bool hktypes::hclSimClothData::CollidablePinchingData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclSimClothData::CollidablePinchingData") {
		std::cout << "hclSimClothData::CollidablePinchingData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->SetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->SetValue(pinchDetectionRadius);
	return true;
}