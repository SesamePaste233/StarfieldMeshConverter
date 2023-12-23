#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkVector4f : public hkHolderBase {
	public:
		using BaseType = void;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkVector4f"; };
		inline std::string GetTranscriptId() override { return "hkVector4f"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
