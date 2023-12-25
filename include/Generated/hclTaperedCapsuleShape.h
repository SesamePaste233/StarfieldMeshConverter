#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4;
	class hclShape;

	class hclTaperedCapsuleShape : public hclShape {
	public:
		using BaseType = hclShape;
		hkVector4 small; // Offset: 32
		hkVector4 big; // Offset: 48
		hkVector4 coneApex; // Offset: 64
		hkVector4 coneAxis; // Offset: 80
		hkVector4 lVec; // Offset: 96
		hkVector4 dVec; // Offset: 112
		hkVector4 tanThetaVecNeg; // Offset: 128
		hkReal smallRadius; // Offset: 144
		hkReal bigRadius; // Offset: 148
		hkReal l; // Offset: 152
		hkReal d; // Offset: 156
		hkReal cosTheta; // Offset: 160
		hkReal sinTheta; // Offset: 164
		hkReal tanTheta; // Offset: 168
		hkReal tanThetaSqr; // Offset: 172

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclTaperedCapsuleShape"; };
		inline std::string GetTranscriptId() override { return "hclTaperedCapsuleShape"; };
		inline uint32_t GethkClassHash() override { return 4196181205; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "small", "hkVector4" },
				{ "big", "hkVector4" },
				{ "coneApex", "hkVector4" },
				{ "coneAxis", "hkVector4" },
				{ "lVec", "hkVector4" },
				{ "dVec", "hkVector4" },
				{ "tanThetaVecNeg", "hkVector4" },
				{ "smallRadius", "hkReal" },
				{ "bigRadius", "hkReal" },
				{ "l", "hkReal" },
				{ "d", "hkReal" },
				{ "cosTheta", "hkReal" },
				{ "sinTheta", "hkReal" },
				{ "tanTheta", "hkReal" },
				{ "tanThetaSqr", "hkReal" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
