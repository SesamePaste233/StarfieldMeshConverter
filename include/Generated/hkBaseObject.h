#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkBaseObject : public hkHolderBase {
	public:
		using BaseType = void;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkBaseObject"; };
		inline std::string GetTranscriptId() override { return "hkBaseObject"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
