#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkStringPtr;
	class hkBool;

	class hkaBone : public hkHolderBase {
	public:
		using BaseType = void;
		hkStringPtr name; // Offset: 0
		hkBool lockTranslation; // Offset: 8

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkaBone"; };
		inline std::string GetTranscriptId() override { return "hkaBone"; };
		inline uint32_t GethkClassHash() override { return 704422420; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "lockTranslation", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
