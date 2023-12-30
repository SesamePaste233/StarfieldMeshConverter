#pragma once
#include "hkReflDataSerializeContext.h"

namespace hkphysics {
	class hkPhysicsDataBuilder {
	public:
		enum BuildTarget : uint8_t {
			BuildTarget_None = 0,
			BuildTarget_GenericClothSim = 1 << 0,
		};

		// Build Target
		hktypes::hkHolderBase* target_instance = nullptr;
		BuildTarget build_target = BuildTarget_None;
		bool build_target_initialized = false;
		hktypes::hclClothData::Platform build_target_platform = hktypes::hclClothData::Platform::HCL_PLATFORM_X64;

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

		// Generic Cloth Sim Only
		void SetSkeleton(hktypes::hkaSkeleton& skeleton);

	protected:
		// References
		hktypes::hclClothData* hcl_cloth_data = nullptr;
		hktypes::hclSimClothData* hcl_sim_cloth_data = nullptr;
		hktypes::hclSimClothPose* hcl_sim_cloth_pose = nullptr;
		hktypes::hkaSkeleton* hka_skeleton = nullptr;
		std::vector<hktypes::hclBufferDefinition*> hcl_buffer_definitions;
		hktypes::hclTransformSetDefinition* hcl_transform_set_definition = nullptr;

		void InitializeGenericClothSim_Impl();
	};
}