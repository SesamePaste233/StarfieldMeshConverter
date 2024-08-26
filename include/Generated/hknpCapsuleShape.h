#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hknpConvexShape;

	class hknpCapsuleShape : public hknpConvexShape {
	public:
		using BaseType = hknpConvexShape;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpCapsuleShape"; };
		inline std::string GetTranscriptId() override { return "hknpCapsuleShape"; };
		inline uint32_t GethkClassHash() override { return 474742631; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
