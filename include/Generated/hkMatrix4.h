#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkMatrix4f;

	class hkMatrix4 : public hkMatrix4f {
	public:
		using BaseType = hkMatrix4f;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkMatrix4"; };
		inline std::string GetTranscriptId() override { return "hkMatrix4"; };
		inline uint32_t GethkClassHash() override { return 1346083038; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
