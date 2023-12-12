#pragma once
#include "hkInclude.h"

#include "Generated\hkBitField.h"

namespace hktypes{
	class hkBitField;

	class hclTransformSetUsage : public hkHolderBase {
	public:
		class TransformTracker : public hkHolderBase {
		public:
			hkBitField read; // Offset: 0
			hkBitField readBeforeWrite; // Offset: 24
			hkBitField written; // Offset: 48

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::array<uint8_t, 2> perComponentFlags; // Offset: 0
		std::vector<hclTransformSetUsage::TransformTracker> perComponentTransformTrackers; // Offset: 8

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
