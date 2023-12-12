#pragma once
#include "hkInclude.h"

#include "Generated\hclShape.h"

namespace hktypes{
	class hclShape;

	class hclTaperedCapsuleShape : public hclShape {
	public:
		hkVector4Holder small; // Offset: 32
		hkVector4Holder big; // Offset: 48
		hkVector4Holder coneApex; // Offset: 64
		hkVector4Holder coneAxis; // Offset: 80
		hkVector4Holder lVec; // Offset: 96
		hkVector4Holder dVec; // Offset: 112
		hkVector4Holder tanThetaVecNeg; // Offset: 128
		float smallRadius; // Offset: 144
		float bigRadius; // Offset: 148
		float l; // Offset: 152
		float d; // Offset: 156
		float cosTheta; // Offset: 160
		float sinTheta; // Offset: 164
		float tanTheta; // Offset: 168
		float tanThetaSqr; // Offset: 172

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
