#include "hkPhysics.h"

void hkphysics::hkPhysicsDataBuilder::Initialize(BuildTarget build_type)
{
	this->build_target = build_type;
	switch (build_type) {
	case BuildTarget_GenericClothSim:
		InitializeGenericClothSim_Impl();
		this->build_target_initialized = true;
		break;
	default:
		throw std::exception("Invalid build target");
		break;
	}
}

bool hkphysics::hkPhysicsDataBuilder::CheckValid(std::underlying_type_t<BuildTarget> required_build_types, bool throw_if_fail)
{
	if (!this->build_target_initialized) {
		std::cout << "Build target not initialized" << std::endl;
		if (throw_if_fail) {
			throw std::exception("Build target not initialized");
		}
		return false;
	}

	if (this->build_target & ~required_build_types) {
		std::cout << "Invalid build target" << std::endl;
		if (throw_if_fail) {
			throw std::exception("Invalid build target");
		}
		return false;
	}

	return true;
}


void hkphysics::hkPhysicsDataBuilder::SetGenericClothSimGravity(float x, float y, float z)
{
	CheckValid(BuildTarget_GenericClothSim);

	this->hcl_sim_cloth_data->simulationInfo.gravity.x() = x;
	this->hcl_sim_cloth_data->simulationInfo.gravity.y() = y;
	this->hcl_sim_cloth_data->simulationInfo.gravity.z() = z;
	this->hcl_sim_cloth_data->simulationInfo.gravity.w() = 1.f;
}

void hkphysics::hkPhysicsDataBuilder::SetGenericClothSimGlobalDamping(float damping)
{
	CheckValid(BuildTarget_GenericClothSim);

	this->hcl_sim_cloth_data->simulationInfo.globalDampingPerSecond = damping;
}

void hkphysics::hkPhysicsDataBuilder::SetSkeleton(hktypes::hkaSkeleton& skeleton)
{
	using namespace hktypes;

	CheckValid(BuildTarget_GenericClothSim);

	auto& skeleton_var = dynamic_cast<hkRootLevelContainer*>(this->target_instance)->GetNamedVariant("hkaSkeleton");
	if (skeleton_var.variant != nullptr) {
		delete skeleton_var.variant;
		skeleton_var.variant = nullptr;
		this->hka_skeleton = nullptr;
	}

	this->hka_skeleton = skeleton.Clone();
	this->hka_skeleton->name = "Root";
	this->hcl_cloth_data->transformSetDefinitions[0]->numTransforms = this->hka_skeleton->bones.size();
	skeleton_var.variant = this->hka_skeleton;
}

void hkphysics::hkPhysicsDataBuilder::SetSimClothDefaultMesh(hktypes::hclBufferedMeshObj& mesh) {
	CheckValid(BuildTarget_GenericClothSim);
	hcl_sim_cloth_data->SetDefaultPoses(&mesh);
}

void hkphysics::hkPhysicsDataBuilder::SetSimClothAttrsFromJson(nlohmann::json& json)
{
	using namespace hktypes;

	CheckValid(BuildTarget_GenericClothSim);

	auto& sim_cloth_data = this->hcl_sim_cloth_data;

	if (json.contains("gravity")) {
		auto& gravity = json["gravity"];
		SetGenericClothSimGravity(gravity[0], gravity[1], gravity[2]);
	}

	if (json.contains("globalDamping")) {
		SetGenericClothSimGlobalDamping(json["globalDamping"]);
	}

	if (json.contains("fixedParticles")) {
		std::vector<uint16_t> fixed_particles;
		for (auto& fixed_particle : json["fixedParticles"]) {
			fixed_particles.push_back(fixed_particle);
		}
		sim_cloth_data->SetFixedParticles(fixed_particles);
	}

	if (json.contains("totalMass")) {
		sim_cloth_data->DistributeMass(json["totalMass"]);
	}

	if (json.contains("transferMotionBone")) {
		std::string bone_name = json["transferMotionBone"];
		auto bone_id = this->hka_skeleton->GetBoneIndex(bone_name);
		if (bone_id != uint16_t(-1)) {
			sim_cloth_data->SetTransferMotionBone(bone_id);
		}
		else {
			std::cout << "Warning: Invalid skeleton or bone name: "<< bone_name << std::endl;
			throw std::runtime_error("Invalid skeleton or bone name");
		}
	}

	if (json.contains("customRadius")) {
		for (auto& custom_radius : json["customRadius"]) {
			uint16_t p_id = custom_radius["particle"];
			float r = custom_radius["radius"];
			sim_cloth_data->SetRadius(p_id, r);
		}
	}

	if (json.contains("customFriction")) {
		for (auto& custom_fric : json["customFriction"]) {
			uint16_t p_id = custom_fric["particle"];
			float f = custom_fric["friction"];
			sim_cloth_data->SetFriction(p_id, f);
		}
	}

}

void hkphysics::hkPhysicsDataBuilder::InitializeGenericClothSim_Impl()
{
	using namespace hktypes;

	ClearTarget();

	this->target_instance = new hkRootLevelContainer();

	auto hk_root_level_container = dynamic_cast<hkRootLevelContainer*>(this->target_instance);

	hkRootLevelContainer::NamedVariant hclClothData_variant;
	hclClothData_variant.className = "hclClothData";

	hclClothData* hcl_cloth_data = new hclClothData();
	hclClothData_variant.variant = hcl_cloth_data;
	this->hcl_cloth_data = hcl_cloth_data;

	hk_root_level_container->namedVariants.push_back(hclClothData_variant);

	hkRootLevelContainer::NamedVariant hka_skeleton_variant;
	hka_skeleton_variant.className = "hkaSkeleton";
	hka_skeleton_variant.variant = nullptr;

	hk_root_level_container->namedVariants.push_back(hka_skeleton_variant);

	hclSimClothData* hcl_sim_cloth_data = new hclSimClothData();
	hcl_cloth_data->simClothDatas.push_back(hcl_sim_cloth_data);
	this->hcl_sim_cloth_data = hcl_sim_cloth_data;

	hcl_sim_cloth_data->name = "Simulation Cloth";
	hcl_sim_cloth_data->doNormals = true;
	hcl_sim_cloth_data->transferMotionEnabled = true;
	hcl_sim_cloth_data->landscapeCollisionEnabled = false;
	hcl_sim_cloth_data->numLandscapeCollidableParticles = 0;
	hcl_sim_cloth_data->pinchDetectionEnabled = false;
	hcl_sim_cloth_data->minPinchedParticleIndex = 0;
	hcl_sim_cloth_data->maxPinchedParticleIndex = 0;
	hcl_sim_cloth_data->maxCollisionPairs = 0;

	hclSimClothPose* hcl_sim_cloth_pose = new hclSimClothPose();
	hcl_sim_cloth_data->simClothPoses.push_back(hcl_sim_cloth_pose);
	this->hcl_sim_cloth_pose = hcl_sim_cloth_pose;

	hcl_sim_cloth_pose->name = "DefaultClothPose";

	hclScratchBufferDefinition* hcl_scratch_buffer_definition = new hclScratchBufferDefinition();
	hcl_cloth_data->bufferDefinitions.push_back(hcl_scratch_buffer_definition);
	this->hcl_buffer_definitions.push_back(hcl_scratch_buffer_definition);
	*hcl_scratch_buffer_definition = hktypes::DefaultScratchBufferDefinition();

	hclBufferDefinition* hcl_buffer_definition = new hclBufferDefinition();
	hcl_cloth_data->bufferDefinitions.push_back(hcl_buffer_definition);
	this->hcl_buffer_definitions.push_back(hcl_buffer_definition);
	*hcl_buffer_definition = hktypes::DefaultBufferDefinitionWithTriangles();

	hclTransformSetDefinition* hcl_transform_set_definition = new hclTransformSetDefinition();
	hcl_cloth_data->transformSetDefinitions.push_back(hcl_transform_set_definition);
	this->hcl_transform_set_definition = hcl_transform_set_definition;
	hcl_transform_set_definition->name = "Root Transforms";
	hcl_transform_set_definition->type = 1;

	hclClothState* hcl_cloth_state_simulate = new hclClothState();
	hcl_cloth_data->clothStateDatas.push_back(hcl_cloth_state_simulate);
	hcl_cloth_state_simulate->name = "Simulate";
	hcl_cloth_state_simulate->usedSimCloths.push_back(0);

	hclClothState* hcl_cloth_state_animate = new hclClothState();
	hcl_cloth_data->clothStateDatas.push_back(hcl_cloth_state_animate);
	hcl_cloth_state_animate->name = "Animate";
	hcl_cloth_state_animate->usedSimCloths.push_back(0);

	hcl_cloth_data->generatedAtRuntime = false;
	hcl_cloth_data->targetPlatform = hktypes::hclClothData::Platform(this->build_target_platform);
}
