#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkStringPtr : public hkHolderBase {
	public:
		using BaseType = void;
		char* stringAndFlag; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkStringPtr"; };
		inline std::string GetTranscriptId() override { return "hkStringPtr"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "stringAndFlag", "char*" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
