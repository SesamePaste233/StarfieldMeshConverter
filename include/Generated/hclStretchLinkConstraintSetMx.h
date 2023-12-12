#pragma once
#include "hkInclude.h"

#include "Generated\hclConstraintSet.h"

namespace hktypes{
	class hclConstraintSet;

	class hclStretchLinkConstraintSetMx : public hclConstraintSet {
	public:
		class Batch : public hkHolderBase {
		public:
			std::array<float, 4> restLengths; // Offset: 0
			std::array<float, 4> stiffnesses; // Offset: 16
			std::array<uint16_t, 4> particlesA; // Offset: 32
			std::array<uint16_t, 4> particlesB; // Offset: 40

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Single : public hkHolderBase {
		public:
			float restLength; // Offset: 0
			float stiffness; // Offset: 4
			uint32_t particleA; // Offset: 8
			uint32_t particleB; // Offset: 12

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclStretchLinkConstraintSetMx::Batch> batches; // Offset: 40
		std::vector<hclStretchLinkConstraintSetMx::Single> singles; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
