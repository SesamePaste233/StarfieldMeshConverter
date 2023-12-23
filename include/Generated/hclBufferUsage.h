#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkBool;

	class hclBufferUsage : public hkHolderBase {
	public:
		using BaseType = void;
		T[N]<hkUint8, 4> perComponentFlags; // Offset: 0
		hkBool trianglesRead; // Offset: 4

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBufferUsage"; };
		inline std::string GetTranscriptId() override { return "hclBufferUsage"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "perComponentFlags", "T[N]<hkUint8, 4>" },
				{ "trianglesRead", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
