#pragma once
#include "hkInclude.h"

#include "Generated\hclShape.h"

namespace hktypes{
	class hclShape;

	class hclCapsuleShape : public hclShape {
	public:
		hkVector4Holder start; // Offset: 32
		hkVector4Holder end; // Offset: 48
		hkVector4Holder dir; // Offset: 64
		float radius; // Offset: 80
		float capLenSqrdInv; // Offset: 84

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
