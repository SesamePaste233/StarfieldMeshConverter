#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4f;

	class hkVector4 : public hkVector4f {
	public:
		using BaseType = hkVector4f;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkVector4"; };
		inline std::string GetTranscriptId() override { return "hkVector4"; };
		inline uint32_t GethkClassHash() override { return 1544414121; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
