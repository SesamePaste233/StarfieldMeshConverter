#pragma once
#include "hkInclude.h"

#include "Generated\hclConstraintSet.h"

namespace hktypes{
	class hclConstraintSet;

	class hclLocalRangeConstraintSet : public hclConstraintSet {
	public:
		class LocalConstraint : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class LocalStiffnessConstraint : public hkHolderBase {
		public:
			uint16_t particleIndex; // Offset: 0
			uint16_t referenceVertex; // Offset: 2
			float maximumDistance; // Offset: 4
			float maxNormalDistance; // Offset: 8
			float minNormalDistance; // Offset: 12
			float stiffness; // Offset: 16

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class ShapeType : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclLocalRangeConstraintSet::LocalConstraint> localConstraints; // Offset: 40
		std::vector<hclLocalRangeConstraintSet::LocalStiffnessConstraint> localStiffnessConstraints; // Offset: 56
		uint32_t referenceMeshBufferIdx; // Offset: 72
		float stiffness; // Offset: 76
		hclLocalRangeConstraintSet::ShapeType shapeType; // Offset: 80
		bool applyNormalComponent; // Offset: 84

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
