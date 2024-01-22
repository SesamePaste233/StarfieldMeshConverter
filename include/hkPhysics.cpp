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

bool hkphysics::hkPhysicsDataBuilder::ParseJson(nlohmann::json& json)
{
	if (!json.contains("data") || !json["data"].contains("target")) {
		std::cout << "Warning: Invalid json file" << std::endl;
	}

	auto& physics_data = json["data"];
	std::string target = json["data"]["target"];
	if (target == "GenericClothSim") {
		std::string factory_signature = physics_data["factory"];
		if (factory_signature != "TwoStatesPhysicsData") {
			std::cout << "Warning: Invalid factory signature \"" << factory_signature << "\"" << std::endl;
			return false;
		}

		auto& cloth_data = physics_data["cloth_data"];
		auto& particles = cloth_data["particles"];
		auto& driver = physics_data["bone_driver_data"];
		
		std::vector<std::vector<float>> positions;
		std::vector<std::vector<float>> normals;
		std::vector<std::vector<std::pair<uint16_t, uint8_t>>> weights;
		std::vector<uint16_t> used_bone_ids = json["used_indices"];
		std::vector<uint16_t> triangle_indices = json["mesh_indices"];
		std::vector<uint16_t> fixed_particles;
		std::vector<float> gravity = cloth_data["gravity_vector"];
		std::vector<std::string> bone_list = cloth_data["bone_list"];
		uint8_t subSteps = cloth_data["sub_steps"];
		uint8_t solverIterations = cloth_data["solver_iterations"];
		float global_damping = cloth_data["global_damping_per_second"];

		int num_particles = 0;
		for (auto& particle : particles) {
			std::vector<float> position = particle["position"];
			std::vector<float> normal = particle["normal"];
			positions.push_back(position);
			normals.push_back(normal);
			if (particle["is_fixed"]) {
				fixed_particles.push_back(num_particles);
			}
			++num_particles;
		}

		for (auto& weight : json["weights"]) {
			std::vector<std::pair<uint16_t, uint8_t>> weight_list;
			for (auto& bone_weight : weight) {
				weight_list.push_back(std::make_pair(bone_weight[0], bone_weight[1]));
			}
			weights.push_back(weight_list);
		}

		hktypes::hkaSkeleton skeleton;
		skeleton.FromJson(json["armature"]);

		uint16_t bone_id = 0;
		std::map<uint16_t, uint16_t> bone_id_map;
		for (auto& bone_name : bone_list) {
			auto skeleton_bone_id = skeleton.GetBoneIndex(bone_name);
			if (skeleton_bone_id == (uint16_t)-1) {
				std::cout << "Warning: Invalid bone name \"" << bone_name << "\"" << std::endl;
				return false;
			}
			bone_id_map[bone_id] = skeleton_bone_id;
		}


		this->Initialize(BuildTarget_GenericClothSim);

		this->SetGenericClothSimGravity(gravity[0], gravity[1], gravity[2]);
		this->SetGenericClothSimGlobalDamping(global_damping);

		this->SetSimClothDefaultMesh(positions, triangle_indices);

		this->SetSkeleton(skeleton);

		this->hcl_sim_cloth_data->fixedParticles = fixed_particles;
		for (size_t i = 0; i < particles.size(); ++i) {
			this->hcl_sim_cloth_data->SetMassUnsafe(i, particles[i]["mass"]);
			this->hcl_sim_cloth_data->SetRadius(i, particles[i]["radius"]);
			this->hcl_sim_cloth_data->SetFriction(i, particles[i]["friction"]);
		}

		this->hcl_sim_cloth_data->SetTransferMotionBone(bone_id_map[cloth_data["pivot"]]);

		for (auto& collider: cloth_data["colliders"]) {
			hktypes::hclBufferedMeshObj coll;
			if (collider["collider"] == "Capsule") {
				coll.FromJson(collider);
				std::string bone_name = bone_list[collider["bone"]];
				this->AddSimClothCollisionMesh(coll, bone_name);
				this->hcl_sim_cloth_data->SetStaticCollisionMasks(coll.name, collider["collision_mask"]);
			}
			else {
				std::cout << "Warning: Invalid collider type \"" << collider["collider"] << "\"" << std::endl;
				return false;
			}
		}

		for (auto& constraint: cloth_data["constraints"]) {
			std::string type = constraint["constraint"];
			std::string name = constraint["name"];
			if (type == "StandardLink") {
				auto constraint_ptr = this->AddConstraintSet(type, name);
				auto standard_link = dynamic_cast<hktypes::hclStandardLinkConstraintSetMx*>(constraint_ptr);

				for (auto& link : constraint["links"]) {
					standard_link->AddDefaultLink(this->hcl_sim_cloth_data, link["particleA"], link["particleB"], link["stiffness"]);
				}

				standard_link->MergeSingles();
			}
			else {
				std::cout << "Warning: Invalid constraint type \"" << type << "\"" << std::endl;
				return false;
			}
		}

		hktypes::hclObjectSpaceSkinPNOperator* skin_operator = hktypes::AllocateObjectSpaceSkinPNOperator(
			this->hka_skeleton, 
			used_bone_ids,
			positions,
			normals,
			weights
		);

		hktypes::hclMoveParticlesOperator* move_particles_operator = hktypes::AllocateMoveParticlesOperator(
			fixed_particles
		);

		hktypes::hclSimulateOperator* simulate_operator = hktypes::AllocateSimulateOperator(
			this->hcl_sim_cloth_data,
			this->hcl_transform_set_definition,
			subSteps,
			solverIterations
		);

		hktypes::hclOperator* bone_deform_operator = nullptr;
		if (driver["factory"] == "SimpleTriangleBoneDriver") {
			std::vector<uint16_t> cloth_bone_ids = driver["cloth_bones"];
			std::vector<uint16_t> face_indices = driver["face_indices"];
			auto& local_transforms = driver["local_bone_transforms"];

			std::vector<std::pair<uint16_t, uint16_t>> bone_triangle_pairs;
			std::vector<Eigen::Matrix4f> local_bone_transforms;
			for (size_t i = 0; i < cloth_bone_ids.size(); ++i) {
				bone_triangle_pairs.push_back(std::make_pair(cloth_bone_ids[i], face_indices[i]));
				auto& t = local_transforms[i];
				Eigen::Matrix4f transform;
				transform << t[0][0], t[0][1], t[0][2], t[0][3],
					t[1][0], t[1][1], t[1][2], t[1][3],
					t[2][0], t[2][1], t[2][2], t[2][3],
					t[3][0], t[3][1], t[3][2], t[3][3];
				local_bone_transforms.push_back(transform);
			}

			hktypes::hclSimpleMeshBoneDeformOperator* simple_mesh_bone_deform_operator = hktypes::AllocateSimpleMeshBoneDeformOperator(
				bone_triangle_pairs,
				local_bone_transforms
			);

			bone_deform_operator = simple_mesh_bone_deform_operator;
		}
		else {
			std::cout << "Warning: Invalid bone driver factory \"" << driver["factory"] << "\"" << std::endl;
			return false;
		}

		hktypes::hclCopyVerticesOperator* copy_vertices_operator = hktypes::AllocateCopyVerticesOperator(
			num_particles
		);

		this->AddOperator(skin_operator);
		this->AddOperator(move_particles_operator);
		this->AddOperator(simulate_operator);
		this->hcl_sim_cloth_data->simOpIds.push_back(simulate_operator->operatorID);
		this->AddOperator(bone_deform_operator);
		this->AddOperator(copy_vertices_operator);

		hktypes::SetClothStateOperators(this->simulate_cloth_state, { 
			skin_operator, 
			move_particles_operator, 
			simulate_operator,
			bone_deform_operator
		});

		hktypes::SetClothStateOperators(this->animate_cloth_state, { 
			skin_operator,
			copy_vertices_operator,
			bone_deform_operator
		});

		this->build_target_finished = true;
		return true;
	}
	else {
		std::cout << "Warning: Invalid target \"" << target << "\"" << std::endl;
		return false;
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
	uint32_t num_vertices = mesh.positions.size();
	uint32_t num_triangles = mesh.triangleIndices.size() / 3;

	hcl_sim_cloth_data->SetDefaultPoses(&mesh);

	this->hcl_buffer_definitions[0]->numVertices = num_vertices;
	this->hcl_buffer_definitions[0]->numTriangles = 0;
	this->hcl_buffer_definitions[1]->numVertices = num_vertices;
	this->hcl_buffer_definitions[1]->numTriangles = num_triangles;
}

void hkphysics::hkPhysicsDataBuilder::SetSimClothDefaultMesh(std::vector<std::vector<float>>& positions, std::vector<uint16_t>& triangleIndices)
{
	CheckValid(BuildTarget_GenericClothSim);
	uint32_t num_vertices = positions.size();
	uint32_t num_triangles = triangleIndices.size() / 3;

	hcl_sim_cloth_data->SetDefaultPoses(positions, triangleIndices);

	this->hcl_buffer_definitions[0]->numVertices = num_vertices;
	this->hcl_buffer_definitions[0]->numTriangles = 0;
	this->hcl_buffer_definitions[1]->numVertices = num_vertices;
	this->hcl_buffer_definitions[1]->numTriangles = num_triangles;
}

void hkphysics::hkPhysicsDataBuilder::AddSimClothCollisionMesh(hktypes::hclBufferedMeshObj& mesh, std::string bind_bone_name)
{
	CheckValid(BuildTarget_GenericClothSim);
	if (hcl_sim_cloth_data->perInstanceCollidables.size() >= 32){
		std::cout << "Warning: Maximum number of collidables reached at 32. Skipping AddSimClothCollisionMesh." << std::endl;
		return;
	}

	auto collidable = hktypes::AllocateCollidableFromMesh(mesh);
	if (collidable != nullptr) {
		hcl_sim_cloth_data->perInstanceCollidables.push_back(collidable);
		auto bone_id = this->hka_skeleton->GetBoneIndex(bind_bone_name);
		assert(bone_id != (uint16_t)-1);
		hcl_sim_cloth_data->collidableTransformMap.transformSetIndex = 0;
		hcl_sim_cloth_data->collidableTransformMap.transformIndices.push_back(bone_id);
		hcl_sim_cloth_data->collidableTransformMap.offsets.push_back(hktypes::hkMatrix4Holder());
	}
	else {
		std::cout << "Warning: Invalid mesh for collision" << std::endl;
		throw std::runtime_error("Invalid mesh for collision");
	}
}

hktypes::hclConstraintSet* hkphysics::hkPhysicsDataBuilder::AddConstraintSet(std::string type, std::string name)
{
	CheckValid(BuildTarget_GenericClothSim);
	if (type == "StandardLink") {
		auto constraint = hktypes::AllocateConstraint(type, name);
		if (constraint == nullptr) {
			std::cout << "Warning: Invalid constraint type \"" << type << "\"" << std::endl;
			throw std::runtime_error("Invalid constraint type");
		}

		return constraint;
	}
	else {
		std::cout << "Warning: Invalid constraint type \"" << type << "\"" << std::endl;
		throw std::runtime_error("Invalid constraint type");
	}
}

void hkphysics::hkPhysicsDataBuilder::AddOperator(hktypes::hclOperator* physics_operator)
{
	CheckValid(BuildTarget_GenericClothSim);
	physics_operator->operatorID = (uint32_t)this->hcl_cloth_data->operators.size();
	this->hcl_cloth_data->operators.push_back(physics_operator);
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
	this->simulate_cloth_state = hcl_cloth_state_simulate;
	hcl_cloth_state_simulate->usedSimCloths.push_back(0);

	hclClothState* hcl_cloth_state_animate = new hclClothState();
	hcl_cloth_data->clothStateDatas.push_back(hcl_cloth_state_animate);
	hcl_cloth_state_animate->name = "Animate";
	this->animate_cloth_state = hcl_cloth_state_animate;
	hcl_cloth_state_animate->usedSimCloths.push_back(0);

	hcl_cloth_data->generatedAtRuntime = false;
	hcl_cloth_data->targetPlatform = hktypes::hclClothData::Platform(this->build_target_platform);
}
