#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkUFloat8 : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 value; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkUFloat8"; };
		inline std::string GetTranscriptId() override { return "hkUFloat8"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "value", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
