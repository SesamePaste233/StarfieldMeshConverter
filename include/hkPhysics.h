#pragma once
#include "hkReflDataSerializeContext.h"

namespace hkphysics {
	class hkClothSimBuilder {
	public:
		// Build Target
		hktypes::hkRootLevelContainer* target;

		// Components
		float gravity[3] = { 0.0f, 0.0f, -9.81f };
		float global_damping = 0.2f;
		float total_mass = 1.0f;
		float particle_radius = 0.2f;
		hktypes::hkaSkeleton* skeleton;
		hktypes::hclBufferedMeshObj* simulation_mesh;
		std::vector<hktypes::hclBufferedMeshObj*> collision_meshes;
	};
}