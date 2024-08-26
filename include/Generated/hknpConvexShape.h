#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkHalf16;
	class hknpShape;
	class hknpConvexHull;

	class hknpConvexShape : public hknpShape {
	public:
		using BaseType = hknpShape;
		hkHalf16 maxAllowedPenetration; // Offset: 56
		hknpConvexHull hull; // Offset: 60

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpConvexShape"; };
		inline std::string GetTranscriptId() override { return "hknpConvexShape"; };
		inline uint32_t GethkClassHash() override { return 3798386044; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "maxAllowedPenetration", "hkHalf16" },
				{ "hull", "hknpConvexHull" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
