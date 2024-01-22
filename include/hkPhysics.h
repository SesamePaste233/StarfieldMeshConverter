#pragma once
#include "hkReflDataSerializeContext.h"
namespace hktypes {
	class hclBufferedMeshObj;
	class hclClothData;
	class hclClothState;
	class hclSimClothData;
	class hclSimClothPose;
	class hkaSkeleton;
	class hclBufferDefinition;
	class hclTransformSetDefinition;
	class hkHolderBase;
	class hclConstraintSet;
	class hclOperator;
}

namespace hkphysics {
	class hkPhysicsDataBuilder {
	public:
		enum Platform : uint32_t
		{
			HCL_PLATFORM_INVALID = 0,
			HCL_PLATFORM_WIN32 = 1,
			HCL_PLATFORM_X64 = 2,
			HCL_PLATFORM_MACPPC = 4,
			HCL_PLATFORM_IOS = 8,
			HCL_PLATFORM_MAC386 = 16,
			HCL_PLATFORM_PS3 = 32,
			HCL_PLATFORM_XBOX360 = 64,
			HCL_PLATFORM_WII = 128,
			HCL_PLATFORM_LRB = 256,
			HCL_PLATFORM_LINUX = 512,
			HCL_PLATFORM_PSVITA = 1024,
			HCL_PLATFORM_ANDROID = 2048,
			HCL_PLATFORM_CTR = 4096,
			HCL_PLATFORM_WIIU = 8192,
			HCL_PLATFORM_PS4 = 16384,
			HCL_PLATFORM_XBOXONE = 32768,
			HCL_PLATFORM_MAC64 = 65536,
			HCL_PLATFORM_NX = 131072,
			HCL_PLATFORM_GDK = 262144,
			HCL_PLATFORM_COOKER = 524288
		};

		enum BuildTarget : uint8_t {
			BuildTarget_None = 0,
			BuildTarget_GenericClothSim = 1 << 0,
		};

		// Build Target
		hktypes::hkHolderBase* target_instance = nullptr;
		BuildTarget build_target = BuildTarget_None;
		bool build_target_initialized = false;
		bool build_target_finished = false;
		Platform build_target_platform = HCL_PLATFORM_X64;

		// Components
		float gravity[3] = { 0.0f, 0.0f, -9.81f };
		float global_damping = 0.2f;
		float total_mass = 1.0f;
		float particle_radius = 0.2f;
		hktypes::hclBufferedMeshObj* simulation_mesh;
		std::vector<hktypes::hclBufferedMeshObj*> collision_meshes;

		inline void ClearTarget() {
			if (target_instance != nullptr) {
				delete target_instance;
				target_instance = nullptr;
			}
		}

		inline hktypes::hkHolderBase& GetTarget() {
			return *target_instance;
		}

		bool CheckValid(std::underlying_type_t<BuildTarget> required_build_types, bool throw_if_fail = true);

		void Initialize(BuildTarget build_type);

		bool ParseJson(nlohmann::json& json);

		// Generic Cloth Sim Only
		void SetGenericClothSimGravity(float x, float y, float z);
		inline void SetGenericClothSimGravity(std::array<float, 3> gravity) {
			SetGenericClothSimGravity(gravity[0], gravity[1], gravity[2]);
		}
		void SetGenericClothSimGlobalDamping(float damping);
		void SetSkeleton(hktypes::hkaSkeleton& skeleton);
		void SetSimClothDefaultMesh(hktypes::hclBufferedMeshObj& mesh);
		void SetSimClothDefaultMesh(std::vector<std::vector<float>>& positions, std::vector<uint16_t>& triangleIndices);
		void AddSimClothCollisionMesh(hktypes::hclBufferedMeshObj& mesh, std::string bind_bone_name);
		hktypes::hclConstraintSet* AddConstraintSet(std::string type, std::string name);
		void AddOperator(hktypes::hclOperator* physics_operator);

	protected:
		// References
		hktypes::hclClothData* hcl_cloth_data = nullptr;
		hktypes::hclSimClothData* hcl_sim_cloth_data = nullptr;
		hktypes::hclSimClothPose* hcl_sim_cloth_pose = nullptr;
		hktypes::hkaSkeleton* hka_skeleton = nullptr;
		std::vector<hktypes::hclBufferDefinition*> hcl_buffer_definitions;
		hktypes::hclTransformSetDefinition* hcl_transform_set_definition = nullptr;
		hktypes::hclClothState* simulate_cloth_state = nullptr;
		hktypes::hclClothState* animate_cloth_state = nullptr;

		void InitializeGenericClothSim_Impl();
	};
}