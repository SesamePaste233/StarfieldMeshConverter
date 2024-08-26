#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkFloat3 : public hkHolderBase {
	public:
		using BaseType = void;
		float x; // Offset: 0
		float y; // Offset: 4
		float z; // Offset: 8

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkFloat3"; };
		inline std::string GetTranscriptId() override { return "hkFloat3"; };
		inline uint32_t GethkClassHash() override { return 1488974649; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "x", "float" },
				{ "y", "float" },
				{ "z", "float" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
