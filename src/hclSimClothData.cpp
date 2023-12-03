#include "hclSimClothData.h"

bool hktypes::hclConstraintSet::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclConstraintSet") {
		std::cout << "hclConstraintSet::FromInstance: type_name is not hclConstraintSet" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");
	this->constraintId = class_instance->GetUIntByFieldName("constraintId");
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

bool hktypes::hclLocalRangeConstraintSet::LocalStiffnessConstraint::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

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

bool hktypes::hclLocalRangeConstraintSet::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclLocalRangeConstraintSet") {
		std::cout << "hclLocalRangeConstraintSet::FromInstance: type_name is not hclLocalRangeConstraintSet" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("class_parent")->GetValue(*(hclConstraintSet*)this);
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

	class_instance->GetInstanceByFieldName("class_parent")->SetValue(*(hclConstraintSet*)this);
	class_instance->GetInstanceByFieldName("localConstraints")->SetValue(this->localConstraints);
	class_instance->GetInstanceByFieldName("localStiffnessConstraints")->SetValue(this->localStiffnessConstraints);
	class_instance->GetInstanceByFieldName("referenceMeshBufferIdx")->SetValue(this->referenceMeshBufferIdx);
	class_instance->GetInstanceByFieldName("stiffness")->SetValue(this->stiffness);
	uint32_t _shape_type = (uint32_t)this->shapeType;
	class_instance->GetInstanceByFieldName("shapeType")->SetValue(_shape_type);
	class_instance->GetInstanceByFieldName("applyNormalComponent")->SetValue(this->applyNormalComponent);

	return true;
}

bool hktypes::hclStandardLinkConstraintSetMx::Batch::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

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

bool hktypes::hclStandardLinkConstraintSetMx::Single::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

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

bool hktypes::hclStandardLinkConstraintSetMx::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclStandardLinkConstraintSetMx") {
		std::cout << "hclStandardLinkConstraintSetMx::FromInstance: type_name is not hclStandardLinkConstraintSetMx" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("class_parent")->GetValue(*(hclConstraintSet*)this);
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

	class_instance->GetInstanceByFieldName("class_parent")->SetValue(*(hclConstraintSet*)this);
	class_instance->GetInstanceByFieldName("batches")->SetValue(this->batches);
	class_instance->GetInstanceByFieldName("singles")->SetValue(this->singles);

	return true;
}

bool hktypes::hclSimClothPose::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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

bool hktypes::hclSimClothData::OverridableSimulationInfo::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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

bool hktypes::hclSimClothData::ParticleData::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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

bool hktypes::hclSimClothData::CollidableTransformMap::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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

bool hktypes::hclSimClothData::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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
	this->transferMotionEnabled = class_instance->GetBoolByFieldName("transferMotionEnabled");
	this->landscapeCollisionEnabled = class_instance->GetBoolByFieldName("landscapeCollisionEnabled");
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
	class_instance->GetInstanceByFieldName("transferMotionEnabled")->SetValue(this->transferMotionEnabled);
	class_instance->GetInstanceByFieldName("landscapeCollisionEnabled")->SetValue(this->landscapeCollisionEnabled);
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

bool hktypes::hclCollidable::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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