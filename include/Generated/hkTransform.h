#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkTransformf;

	class hkTransform : public hkTransformf {
	public:
		using BaseType = hkTransformf;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkTransform"; };
		inline std::string GetTranscriptId() override { return "hkTransform"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
