#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkHalf16 : public hkHolderBase {
	public:
		using BaseType = void;
		hkInt16 value; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkHalf16"; };
		inline std::string GetTranscriptId() override { return "hkHalf16"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "value", "hkInt16" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
