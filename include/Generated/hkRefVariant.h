#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkRefVariant : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> ptr; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRefVariant"; };
		inline std::string GetTranscriptId() override { return "hkRefVariant"; };
		inline uint32_t GethkClassHash() override { return 3255563653; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "ptr", "T*<void>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
