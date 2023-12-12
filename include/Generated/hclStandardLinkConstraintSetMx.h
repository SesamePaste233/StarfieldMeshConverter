#pragma once
#include "hkInclude.h"

#include "Generated\hclConstraintSet.h"

namespace hktypes{
	class hclConstraintSet;

	class hclStandardLinkConstraintSetMx : public hclConstraintSet {
	public:
		class Batch : public hkHolderBase {
		public:
			std::array<float, 4> restLengths; // Offset: 0
			std::array<float, 4> stiffnessesA; // Offset: 16
			std::array<float, 4> stiffnessesB; // Offset: 32
			std::array<uint16_t, 4> particlesA; // Offset: 48
			std::array<uint16_t, 4> particlesB; // Offset: 56

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Single : public hkHolderBase {
		public:
			float restLength; // Offset: 0
			float stiffnessA; // Offset: 4
			float stiffnessB; // Offset: 8
			uint16_t particleA; // Offset: 12
			uint16_t particleB; // Offset: 14

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclStandardLinkConstraintSetMx::Batch> batches; // Offset: 40
		std::vector<hclStandardLinkConstraintSetMx::Single> singles; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
