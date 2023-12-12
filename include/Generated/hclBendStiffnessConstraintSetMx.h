#pragma once
#include "hkInclude.h"

#include "Generated\hclConstraintSet.h"

namespace hktypes{
	class hclConstraintSet;

	class hclBendStiffnessConstraintSetMx : public hclConstraintSet {
	public:
		class Batch : public hkHolderBase {
		public:
			std::array<float, 4> weightsA; // Offset: 0
			std::array<float, 4> weightsB; // Offset: 16
			std::array<float, 4> weightsC; // Offset: 32
			std::array<float, 4> weightsD; // Offset: 48
			std::array<float, 4> bendStiffnesses; // Offset: 64
			std::array<float, 4> restCurvatures; // Offset: 80
			std::array<float, 4> invMassesA; // Offset: 96
			std::array<float, 4> invMassesB; // Offset: 112
			std::array<float, 4> invMassesC; // Offset: 128
			std::array<float, 4> invMassesD; // Offset: 144
			std::array<uint16_t, 4> particlesA; // Offset: 160
			std::array<uint16_t, 4> particlesB; // Offset: 168
			std::array<uint16_t, 4> particlesC; // Offset: 176
			std::array<uint16_t, 4> particlesD; // Offset: 184

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Single : public hkHolderBase {
		public:
			float weightA; // Offset: 0
			float weightB; // Offset: 4
			float weightC; // Offset: 8
			float weightD; // Offset: 12
			float bendStiffness; // Offset: 16
			float restCurvature; // Offset: 20
			float invMassA; // Offset: 24
			float invMassB; // Offset: 28
			float invMassC; // Offset: 32
			float invMassD; // Offset: 36
			uint16_t particleA; // Offset: 40
			uint16_t particleB; // Offset: 42
			uint16_t particleC; // Offset: 44
			uint16_t particleD; // Offset: 46

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclBendStiffnessConstraintSetMx::Batch> batches; // Offset: 40
		std::vector<hclBendStiffnessConstraintSetMx::Single> singles; // Offset: 56
		float maxRestPoseHeightSq; // Offset: 72
		bool clampBendStiffness; // Offset: 76
		bool useRestPoseConfig; // Offset: 77

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
