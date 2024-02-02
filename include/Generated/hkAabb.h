#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4;

	class hkAabb : public hkHolderBase {
	public:
		using BaseType = void;
		hkVector4 min; // Offset: 0
		hkVector4 max; // Offset: 16

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkAabb"; };
		inline std::string GetTranscriptId() override { return "hkAabb"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "min", "hkVector4" },
				{ "max", "hkVector4" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
