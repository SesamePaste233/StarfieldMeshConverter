#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkQsTransformf;

	class hkQsTransform : public hkQsTransformf {
	public:
		using BaseType = hkQsTransformf;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkQsTransform"; };
		inline std::string GetTranscriptId() override { return "hkQsTransform"; };
		inline uint32_t GethkClassHash() override { return 973428694; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
