#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkBool : public hkHolderBase {
	public:
		using BaseType = void;
		char bool; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkBool"; };
		inline std::string GetTranscriptId() override { return "hkBool"; };
		inline uint32_t GethkClassHash() override { return 2172449542; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "bool", "char" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
