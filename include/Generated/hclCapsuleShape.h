#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4;
	class hclShape;

	class hclCapsuleShape : public hclShape {
	public:
		using BaseType = hclShape;
		hkVector4 start; // Offset: 32
		hkVector4 end; // Offset: 48
		hkVector4 dir; // Offset: 64
		hkReal radius; // Offset: 80
		hkReal capLenSqrdInv; // Offset: 84

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclCapsuleShape"; };
		inline std::string GetTranscriptId() override { return "hclCapsuleShape"; };
		inline uint32_t GethkClassHash() override { return 2819961333; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "start", "hkVector4" },
				{ "end", "hkVector4" },
				{ "dir", "hkVector4" },
				{ "radius", "hkReal" },
				{ "capLenSqrdInv", "hkReal" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
