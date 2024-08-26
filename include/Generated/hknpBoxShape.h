#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkTransformf;
	class hknpConvexShape;

	class hknpBoxShape : public hknpConvexShape {
	public:
		using BaseType = hknpConvexShape;
		hkTransformf obb; // Offset: 112

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpBoxShape"; };
		inline std::string GetTranscriptId() override { return "hknpBoxShape"; };
		inline uint32_t GethkClassHash() override { return 1121152354; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "obb", "hkTransformf" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
