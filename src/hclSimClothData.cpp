#include "hclSimClothData.h"

bool hktypes::hclConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclConstraintSet") {
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

	if (class_instance->type->type_name != "hclConstraintSet") {
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
	if (class_instance->type->type_name != "hclVolumeConstraint::FrameData") {
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
	if (class_instance->type->type_name != "hclVolumeConstraint::FrameData") {
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
	if (class_instance->type->type_name != "hclVolumeConstraint::ApplyData") {
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
	if (class_instance->type->type_name != "hclVolumeConstraint::ApplyData") {
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
	if (class_instance->type->type_name != "hclVolumeConstraint") {
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
	if (class_instance->type->type_name != "hclVolumeConstraint") {
		std::cout << "hclVolumeConstraint::FromInstance: type_name is not hclVolumeConstraint" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("frameDatas")->SetValue(this->frameDatas);
	class_instance->GetInstanceByFieldName("applyDatas")->SetValue(this->applyDatas);

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

bool hktypes::hclLocalRangeConstraintSet::LocalStiffnessConstraint::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclLocalRangeConstraintSet::LocalStiffnessConstraint") {
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

	if (class_instance->type->type_name != "hclLocalRangeConstraintSet::LocalStiffnessConstraint") {
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

	if (class_instance->type->type_name != "hclLocalRangeConstraintSet") {
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

	if (class_instance->type->type_name != "hclLocalRangeConstraintSet") {
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

	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx::Batch") {
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

	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx::Batch") {
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

	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx::Single") {
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

	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx::Single") {
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

	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx") {
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

	if (class_instance->type->type_name != "hclCompressibleLinkConstraintSetMx") {
		std::cout << "hclCompressibleLinkConstraintSetMx::FromInstance: type_name is not hclCompressibleLinkConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(this->batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(this->singles);

	return true;
}

bool hktypes::hclBendStiffnessConstraintSet::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSet") {
		std::cout << "hclBendStiffnessConstraintSet::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("links")->GetValue(links);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->GetValue(maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->GetValue(clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->GetValue(useRestPoseConfig);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSet::Link::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSet::Link") {
		std::cout << "hclBendStiffnessConstraintSet::Link::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("weightA")->GetValue(weightA);
	class_instance->GetInstanceByFieldName("weightB")->GetValue(weightB);
	class_instance->GetInstanceByFieldName("weightC")->GetValue(weightC);
	class_instance->GetInstanceByFieldName("weightD")->GetValue(weightD);
	class_instance->GetInstanceByFieldName("bendStiffness")->GetValue(bendStiffness);
	class_instance->GetInstanceByFieldName("restCurvature")->GetValue(restCurvature);
	class_instance->GetInstanceByFieldName("particleA")->GetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->GetValue(particleB);
	class_instance->GetInstanceByFieldName("particleC")->GetValue(particleC);
	class_instance->GetInstanceByFieldName("particleD")->GetValue(particleD);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSet::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSet") {
		std::cout << "hclBendStiffnessConstraintSet::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("links")->SetValue(links);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->SetValue(maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->SetValue(clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->SetValue(useRestPoseConfig);
	return true;
}

bool hktypes::hclBendStiffnessConstraintSet::Link::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSet::Link") {
		std::cout << "hclBendStiffnessConstraintSet::Link::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("weightA")->SetValue(weightA);
	class_instance->GetInstanceByFieldName("weightB")->SetValue(weightB);
	class_instance->GetInstanceByFieldName("weightC")->SetValue(weightC);
	class_instance->GetInstanceByFieldName("weightD")->SetValue(weightD);
	class_instance->GetInstanceByFieldName("bendStiffness")->SetValue(bendStiffness);
	class_instance->GetInstanceByFieldName("restCurvature")->SetValue(restCurvature);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(particleB);
	class_instance->GetInstanceByFieldName("particleC")->SetValue(particleC);
	class_instance->GetInstanceByFieldName("particleD")->SetValue(particleD);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBendStiffnessConstraintSet::GetTemplateArgs() {
	return {
	};
};

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBendStiffnessConstraintSet::Link::GetTemplateArgs() {
	return {
	};
};

bool hktypes::hclBendStiffnessConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBendStiffnessConstraintSetMx::Batch") {
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

	for (int i = 0; i < 4; ++i) {
		std::cout << "(" << particlesA[i] << ", " << particlesB[i] << ", " << particlesC[i] << ", " << particlesD[i] << "),\n";
	}

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Batch::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBendStiffnessConstraintSetMx::Batch") {
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

bool hktypes::hclBendStiffnessConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSetMx::Single") {
		std::cout << "hclBendStiffnessConstraintSetMx::Single::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("weightA")->GetValue(weightA);
	class_instance->GetInstanceByFieldName("weightB")->GetValue(weightB);
	class_instance->GetInstanceByFieldName("weightC")->GetValue(weightC);
	class_instance->GetInstanceByFieldName("weightD")->GetValue(weightD);
	class_instance->GetInstanceByFieldName("bendStiffness")->GetValue(bendStiffness);
	class_instance->GetInstanceByFieldName("restCurvature")->GetValue(restCurvature);
	class_instance->GetInstanceByFieldName("invMassA")->GetValue(invMassA);
	class_instance->GetInstanceByFieldName("invMassB")->GetValue(invMassB);
	class_instance->GetInstanceByFieldName("invMassC")->GetValue(invMassC);
	class_instance->GetInstanceByFieldName("invMassD")->GetValue(invMassD);
	class_instance->GetInstanceByFieldName("particleA")->GetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->GetValue(particleB);
	class_instance->GetInstanceByFieldName("particleC")->GetValue(particleC);
	class_instance->GetInstanceByFieldName("particleD")->GetValue(particleD);

	std::cout << "(" << particleA << ", " << particleB << ", " << particleC << ", " << particleD << "),\n";

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::Single::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBendStiffnessConstraintSetMx::Single") {
		std::cout << "hclBendStiffnessConstraintSetMx::Single::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("weightA")->SetValue(weightA);
	class_instance->GetInstanceByFieldName("weightB")->SetValue(weightB);
	class_instance->GetInstanceByFieldName("weightC")->SetValue(weightC);
	class_instance->GetInstanceByFieldName("weightD")->SetValue(weightD);
	class_instance->GetInstanceByFieldName("bendStiffness")->SetValue(bendStiffness);
	class_instance->GetInstanceByFieldName("restCurvature")->SetValue(restCurvature);
	class_instance->GetInstanceByFieldName("invMassA")->SetValue(invMassA);
	class_instance->GetInstanceByFieldName("invMassB")->SetValue(invMassB);
	class_instance->GetInstanceByFieldName("invMassC")->SetValue(invMassC);
	class_instance->GetInstanceByFieldName("invMassD")->SetValue(invMassD);
	class_instance->GetInstanceByFieldName("particleA")->SetValue(particleA);
	class_instance->GetInstanceByFieldName("particleB")->SetValue(particleB);
	class_instance->GetInstanceByFieldName("particleC")->SetValue(particleC);
	class_instance->GetInstanceByFieldName("particleD")->SetValue(particleD);

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBendStiffnessConstraintSetMx") {
		std::cout << "hclBendStiffnessConstraintSetMx::FromInstance: type_name is not hclBendStiffnessConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	std::cout << "Batch: " << std::endl;
	class_instance->GetInstanceByFieldName("batches")->GetValue(this->batches);
	std::cout << "Single: " << std::endl;
	class_instance->GetInstanceByFieldName("singles")->GetValue(this->singles);
	class_instance->GetInstanceByFieldName("maxRestPoseHeightSq")->GetValue(this->maxRestPoseHeightSq);
	class_instance->GetInstanceByFieldName("clampBendStiffness")->GetValue(this->clampBendStiffness);
	class_instance->GetInstanceByFieldName("useRestPoseConfig")->GetValue(this->useRestPoseConfig);

	return true;
}

bool hktypes::hclBendStiffnessConstraintSetMx::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBendStiffnessConstraintSetMx") {
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

void hktypes::hclBendStiffnessConstraintSetMx::FromDefaultPose(hktypes::hclSimClothData* sim_cloth_data, std::vector<std::vector<uint16_t>> edges, std::vector<float> stiffnesses, float stiffness_default) {
	this->singles.clear();
	this->batches.clear();
	
	auto& default_positions = sim_cloth_data->simClothPoses[0]->positions;
	auto& particle_datas = sim_cloth_data->particleDatas;
	auto& default_triangles = sim_cloth_data->triangleIndices;
	std::vector<float> particle_invMasses;
	for (auto& p : particle_datas) {
		particle_invMasses.push_back(p.invMass);
	}
	std::vector<Eigen::Vector3d> positions;
	for (auto& p : default_positions) {
		auto vec3f = p.ToVector3f();
		positions.push_back(Eigen::Vector3d(vec3f.x(), vec3f.y(), vec3f.z()));
	}

	std::vector<std::vector<uint16_t>> triangles = utils::split_vector(default_triangles, 3);

	std::unordered_map<utils::CommutativePair<uint16_t>, float, utils::CommutativePair<uint16_t>::Hash> edge_set;

	for (size_t i = 0; i < edges.size(); ++i) {
		auto& edge = edges[i];
		auto& stiffness = stiffnesses[i];
		edge_set[utils::CommutativePair<uint16_t>(edge[0], edge[1])] = stiffness;
	}

	std::unordered_map<utils::CommutativePair<uint16_t>, std::vector<std::pair<uint32_t, uint16_t>>, utils::CommutativePair<uint16_t>::Hash> common_edges;

	uint32_t num_triangles = triangles.size();
	for (uint32_t i = 0; i < num_triangles; ++i) {
		auto& triangle = triangles[i];
		common_edges[utils::CommutativePair<uint16_t>(triangle[0], triangle[1])].push_back({ i, triangle[2] });
		common_edges[utils::CommutativePair<uint16_t>(triangle[1], triangle[2])].push_back({ i, triangle[0] });
		common_edges[utils::CommutativePair<uint16_t>(triangle[2], triangle[0])].push_back({ i, triangle[1] });
	}
	float maxRestPoseHeightSq = 0.f;
	for (auto& edge : common_edges) {
		if (edge_set.find(edge.first) != edge_set.end()) { // TODO: now it's edge_exclude
			continue;
		}
		auto& all_wings = edge.second;
		if (all_wings.size() < 2) {
			continue;
		}
		//auto& stiffness = edge_set[edge.first];
		auto wings = utils::combinations(all_wings, 2);
		for (auto& wing_vertices : wings) {
			// Might need to order the wings, but should work fine if not
			Eigen::Vector3d e21 = positions[wing_vertices[0].second];
			auto inv_mass_e21 = particle_invMasses[wing_vertices[0].second];
			Eigen::Vector3d e22 = positions[wing_vertices[1].second];
			auto inv_mass_e22 = particle_invMasses[wing_vertices[1].second];
			Eigen::Vector3d e11 = positions[edge.first.lower];
			auto inv_mass_e11 = particle_invMasses[edge.first.lower];
			Eigen::Vector3d e12 = positions[edge.first.upper];
			auto inv_mass_e12 = particle_invMasses[edge.first.upper];
			Eigen::Vector3d na_e11_e12_e22 = (e11 - e22).cross(e12 - e22);
			float l21 = na_e11_e12_e22.norm();
			Eigen::Vector3d na_e11_e21_e22 = (e11 - e22).cross(e21 - e22);
			float l12 = na_e11_e21_e22.norm();
			Eigen::Vector3d na_e11_e12_e21 = (e12 - e21).cross(e11 - e21);
			float l22 = na_e11_e12_e21.norm();
			Eigen::Vector3d na_e12_e21_e22 = (e22 - e21).cross(e12 - e21);
			float l11 = na_e12_e21_e22.norm();
			float w22 = l22 / (l21 + l22);
			float w21 = l21 / (l21 + l22);
			float w12 = -l12 / (l11 + l12);
			float w11 = -l11 / (l11 + l12);

			Eigen::Vector3d n22 = na_e11_e12_e22 / l21;
			Eigen::Vector3d n21 = na_e11_e12_e21 / l22;
			Eigen::Vector3d dn = n22 - n21;

			Eigen::Vector3d e1 = e12 - e11;
			Eigen::Vector3d e2 = e22 - e21;
			Eigen::Vector3d L = e21 * w21 + e22 * w22 + e11 * w11 + e12 * w12;

			float curvature = 0.f;

			if (L.norm() > 1e-4) {
				Eigen::Vector3d dir = L.cross(e1);

				Eigen::Vector3d common_n = e1.cross(e2).normalized();
				float len_L = (e11 - e21).dot(common_n);
				float len_L_sq = len_L * len_L * 64; // Don't know why it's 64 but it fits the observations
				if (len_L_sq > maxRestPoseHeightSq) {
					maxRestPoseHeightSq = len_L_sq;
				}

				curvature = -(dn.dot(dir) / e2.dot(dir));
			}


			float avg_inv_mass = 0.25 * (inv_mass_e21 + inv_mass_e22 + inv_mass_e11 + inv_mass_e12);

			hclBendStiffnessConstraintSetMx::Single single;
			single.weightA = w21;
			single.weightB = w22;
			single.weightC = w11;
			single.weightD = w12;
			single.bendStiffness = - stiffness_default / avg_inv_mass; // TODO: replace with stiffness
			single.restCurvature = curvature;
			single.invMassA = inv_mass_e21;
			single.invMassB = inv_mass_e22;
			single.invMassC = inv_mass_e11;
			single.invMassD = inv_mass_e12;
			single.particleA = wing_vertices[0].second;
			single.particleB = wing_vertices[1].second;
			single.particleC = edge.first.lower;
			single.particleD = edge.first.upper;
			this->singles.push_back(single);
		}
	}

	this->clampBendStiffness = true;
	this->useRestPoseConfig = true;
	this->maxRestPoseHeightSq = maxRestPoseHeightSq;
}

bool hktypes::hclStandardLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Batch") {
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

	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Batch") {
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

	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Single") {
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

	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx::Single") {
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

	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx") {
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

	if (class_instance->type->type_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::FromInstance: type_name is not hclStandardLinkConstraintSetMx" << std::endl;
		return false;
	}

	hclConstraintSet::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("batches")->SetValue(this->batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(this->singles);

	return true;
}

void hktypes::hclStandardLinkConstraintSetMx::AddDefaultLink(hclSimClothData* cloth_data, uint16_t particleA, uint16_t particleB, float stiffness)
{
	auto posA = cloth_data->simClothPoses[0]->positions[particleA].ToVector3f();
	auto posB = cloth_data->simClothPoses[0]->positions[particleB].ToVector3f();
	float restLength = (posA - posB).norm();
	float stiffnessA = 0.5f * stiffness;
	float stiffnessB = -0.5f * stiffness;
	bool is_A_fixed = cloth_data->IsFixedParticle(particleA);
	bool is_B_fixed = cloth_data->IsFixedParticle(particleB);
	if (is_A_fixed && is_B_fixed) {
		return;
	}
	else if (is_A_fixed) {
		stiffnessA = 0;
		stiffnessB = -stiffness;
	}
	else if (is_B_fixed) {
		stiffnessA = stiffness;
		stiffnessB = -0;
	}
	AddLinkImpl(particleA, particleB, stiffnessA, stiffnessB, restLength);
}

bool hktypes::hclStretchLinkConstraintSetMx::Batch::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Batch") {
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

	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Batch") {
		std::cout << "hclStretchLinkConstraintSetMx::Batch::FromInstance: type_name is not hclStretchLinkConstraintSetMx::Batch" << std::endl;
		return false;
	}

	std::vector<float> _rest_lengths = { this->restLengths[0], this->restLengths[1], this->restLengths[2], this->restLengths[3] };
	class_instance->GetInstanceByFieldName("restLengths")->SetValue(_rest_lengths);

	std::vector<float> _stiffnesses = { this->stiffnesses[0], this->stiffnesses[1], this->stiffnesses[2], this->stiffnesses[3] };
	class_instance->GetInstanceByFieldName("stiffnesses")->SetValue(_stiffnesses);

	std::vector<uint16_t> _particles_a = { this->particlesA[0], this->particlesA[1], this->particlesA[2], this->particlesA[3] };
	class_instance->GetInstanceByFieldName("particlesA")->SetValue(_particles_a);

	std::vector<uint16_t> _particles_b = { this->particlesB[0], this->particlesB[1], this->particlesB[2], this->particlesB[3] };
	class_instance->GetInstanceByFieldName("particlesB")->SetValue(_particles_b);

	return true;

}

void hktypes::hclStretchLinkConstraintSetMx::AddDefaultLink(hclSimClothData* cloth_data, uint16_t particleA, uint16_t particleB, float stiffness)
{
	auto posA = cloth_data->simClothPoses[0]->positions[particleA].ToVector3f();
	auto posB = cloth_data->simClothPoses[0]->positions[particleB].ToVector3f();
	float restLength = (posA - posB).norm();
	bool is_A_fixed = cloth_data->IsFixedParticle(particleA);
	bool is_B_fixed = cloth_data->IsFixedParticle(particleB);
	uint16_t _particleA = particleA;	
	uint16_t _particleB = particleB;
	if (is_A_fixed && is_B_fixed) {
		return;
	}
	else if (is_A_fixed) {
		// Do nothing
	}
	else if (is_B_fixed) {
		// Switch A and B
		_particleA = particleB;
		_particleB = particleA;
	}
	AddLinkImpl(_particleA, _particleB, stiffness, restLength);
}

bool hktypes::hclStretchLinkConstraintSetMx::Single::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Single") {
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

	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx::Single") {
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

	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx") {
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

	if (class_instance->type->type_name != "hclStretchLinkConstraintSetMx") {
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
	if (class_instance->type->type_name != "hclSimClothPose") {
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
	if (class_instance->type->type_name != "hclSimClothPose") {
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
	if (class_instance->type->type_name != "hclSimClothData::OverridableSimulationInfo") {
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
	if (class_instance->type->type_name != "hclSimClothData::OverridableSimulationInfo") {
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
	if (class_instance->type->type_name != "hclSimClothData::ParticleData") {
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
	if (class_instance->type->type_name != "hclSimClothData::ParticleData") {
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
	if (class_instance->type->type_name != "hclSimClothData::CollidableTransformMap") {
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
	if (class_instance->type->type_name != "hclSimClothData::CollidableTransformMap") {
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
	if (class_instance->type->type_name != "hclSimClothData") {
		std::cout << "hclSimClothData::FromInstance: type_name is not hclSimClothData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("simulationInfo")->GetValue(simulationInfo);
	class_instance->GetInstanceByFieldName("particleDatas")->GetValue(particleDatas);
	class_instance->GetInstanceByFieldName("fixedParticles")->GetValue(fixedParticles);
	class_instance->GetInstanceByFieldName("doNormals")->GetValue(doNormals);
	class_instance->GetInstanceByFieldName("simOpIds")->GetValue(simOpIds);
	class_instance->GetInstanceByFieldName("simClothPoses")->GetValue(simClothPoses);
	class_instance->GetInstanceByFieldName("staticConstraintSets")->GetValue(staticConstraintSets);
	class_instance->GetInstanceByFieldName("antiPinchConstraintSets")->GetValue(antiPinchConstraintSets);
	class_instance->GetInstanceByFieldName("collidableTransformMap")->GetValue(collidableTransformMap);
	class_instance->GetInstanceByFieldName("perInstanceCollidables")->GetValue(perInstanceCollidables);
	class_instance->GetInstanceByFieldName("maxParticleRadius")->GetValue(maxParticleRadius);
	class_instance->GetInstanceByFieldName("staticCollisionMasks")->GetValue(staticCollisionMasks);
	//class_instance->GetInstanceByFieldName("actions")->GetValue(actions);
	class_instance->GetInstanceByFieldName("totalMass")->GetValue(totalMass);
	class_instance->GetInstanceByFieldName("transferMotionData")->GetValue(transferMotionData);
	class_instance->GetInstanceByFieldName("transferMotionEnabled")->GetValue(transferMotionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionEnabled")->GetValue(landscapeCollisionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionData")->GetValue(landscapeCollisionData);
	class_instance->GetInstanceByFieldName("numLandscapeCollidableParticles")->GetValue(numLandscapeCollidableParticles);
	class_instance->GetInstanceByFieldName("triangleIndices")->GetValue(triangleIndices);
	class_instance->GetInstanceByFieldName("triangleFlips")->GetValue(triangleFlips);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->GetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("perParticlePinchDetectionEnabledFlags")->GetValue(perParticlePinchDetectionEnabledFlags);
	class_instance->GetInstanceByFieldName("collidablePinchingDatas")->GetValue(collidablePinchingDatas);
	class_instance->GetInstanceByFieldName("minPinchedParticleIndex")->GetValue(minPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxPinchedParticleIndex")->GetValue(maxPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxCollisionPairs")->GetValue(maxCollisionPairs);
	//class_instance->GetInstanceByFieldName("virtualCollisionPointsData")->GetValue(virtualCollisionPointsData);

	for (auto constraint : this->staticConstraintSets) {
		std::cout << "Constraint: " << constraint->GethkClassName() << std::endl;
	}

	return true;
}

bool hktypes::hclSimClothData::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimClothData") {
		std::cout << "hclSimClothData::FromInstance: type_name is not hclSimClothData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("simulationInfo")->SetValue(simulationInfo);
	class_instance->GetInstanceByFieldName("particleDatas")->SetValue(particleDatas);
	class_instance->GetInstanceByFieldName("fixedParticles")->SetValue(fixedParticles);
	class_instance->GetInstanceByFieldName("doNormals")->SetValue(doNormals);
	class_instance->GetInstanceByFieldName("simOpIds")->SetValue(simOpIds);
	class_instance->GetInstanceByFieldName("simClothPoses")->SetValue(simClothPoses);
	class_instance->GetInstanceByFieldName("staticConstraintSets")->SetValue(staticConstraintSets);
	class_instance->GetInstanceByFieldName("antiPinchConstraintSets")->SetValue(antiPinchConstraintSets);
	class_instance->GetInstanceByFieldName("collidableTransformMap")->SetValue(collidableTransformMap);
	class_instance->GetInstanceByFieldName("perInstanceCollidables")->SetValue(perInstanceCollidables);
	class_instance->GetInstanceByFieldName("maxParticleRadius")->SetValue(maxParticleRadius);
	class_instance->GetInstanceByFieldName("staticCollisionMasks")->SetValue(staticCollisionMasks);
	//class_instance->GetInstanceByFieldName("actions")->SetValue(actions);
	class_instance->GetInstanceByFieldName("totalMass")->SetValue(totalMass);
	class_instance->GetInstanceByFieldName("transferMotionData")->SetValue(transferMotionData);
	class_instance->GetInstanceByFieldName("transferMotionEnabled")->SetValue(transferMotionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionEnabled")->SetValue(landscapeCollisionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionData")->SetValue(landscapeCollisionData);
	class_instance->GetInstanceByFieldName("numLandscapeCollidableParticles")->SetValue(numLandscapeCollidableParticles);
	class_instance->GetInstanceByFieldName("triangleIndices")->SetValue(triangleIndices);
	class_instance->GetInstanceByFieldName("triangleFlips")->SetValue(triangleFlips);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("perParticlePinchDetectionEnabledFlags")->SetValue(perParticlePinchDetectionEnabledFlags);
	class_instance->GetInstanceByFieldName("collidablePinchingDatas")->SetValue(collidablePinchingDatas);
	class_instance->GetInstanceByFieldName("minPinchedParticleIndex")->SetValue(minPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxPinchedParticleIndex")->SetValue(maxPinchedParticleIndex);
	class_instance->GetInstanceByFieldName("maxCollisionPairs")->SetValue(maxCollisionPairs);
	//class_instance->GetInstanceByFieldName("virtualCollisionPointsData")->SetValue(virtualCollisionPointsData);

	return true;
}

bool hktypes::hclCollidable::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCollidable") {
		std::cout << "hclCollidable::FromInstance: type_name is not hclCollidable" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transform")->GetValue(transform);
	class_instance->GetInstanceByFieldName("linearVelocity")->GetValue(linearVelocity);
	class_instance->GetInstanceByFieldName("angularVelocity")->GetValue(angularVelocity);
	class_instance->GetInstanceByFieldName("userData")->GetValue(userData);
	class_instance->GetInstanceByFieldName("shape")->GetValue(shape);
	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->GetValue(pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->GetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->GetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("virtualCollisionPointCollisionEnabled")->GetValue(virtualCollisionPointCollisionEnabled);
	class_instance->GetInstanceByFieldName("enabled")->GetValue(enabled);

	return true;
}

bool hktypes::hclCollidable::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCollidable") {
		std::cout << "hclCollidable::FromInstance: type_name is not hclCollidable" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transform")->SetValue(transform);
	class_instance->GetInstanceByFieldName("linearVelocity")->SetValue(linearVelocity);
	class_instance->GetInstanceByFieldName("angularVelocity")->SetValue(angularVelocity);
	class_instance->GetInstanceByFieldName("userData")->SetValue(userData);
	class_instance->GetInstanceByFieldName("shape")->SetValue(shape);
	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("pinchDetectionRadius")->SetValue(pinchDetectionRadius);
	class_instance->GetInstanceByFieldName("pinchDetectionPriority")->SetValue(pinchDetectionPriority);
	class_instance->GetInstanceByFieldName("pinchDetectionEnabled")->SetValue(pinchDetectionEnabled);
	class_instance->GetInstanceByFieldName("virtualCollisionPointCollisionEnabled")->SetValue(virtualCollisionPointCollisionEnabled);
	class_instance->GetInstanceByFieldName("enabled")->SetValue(enabled);

	return true;
}

bool hktypes::hclSimClothData::TransferMotionData::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimClothData::TransferMotionData") {
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
	if (class_instance->type->type_name != "hclSimClothData::TransferMotionData") {
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
	if (class_instance->type->type_name != "hclSimClothData::LandscapeCollisionData") {
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

	if (class_instance->type->type_name != "hclSimClothData::LandscapeCollisionData") {
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
	if (class_instance->type->type_name != "hclBonePlanesConstraintSet::BonePlane") {
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

	if (class_instance->type->type_name != "hclBonePlanesConstraintSet::BonePlane") {
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
	if (class_instance->type->type_name != "hclBonePlanesConstraintSet") {
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

	if (class_instance->type->type_name != "hclBonePlanesConstraintSet") {
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