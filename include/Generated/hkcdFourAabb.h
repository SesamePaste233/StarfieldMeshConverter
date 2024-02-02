#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4;

	class hkcdFourAabb : public hkHolderBase {
	public:
		using BaseType = void;
		hkVector4 lx; // Offset: 0
		hkVector4 hx; // Offset: 16
		hkVector4 ly; // Offset: 32
		hkVector4 hy; // Offset: 48
		hkVector4 lz; // Offset: 64
		hkVector4 hz; // Offset: 80

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkcdFourAabb"; };
		inline std::string GetTranscriptId() override { return "hkcdFourAabb"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "lx", "hkVector4" },
				{ "hx", "hkVector4" },
				{ "ly", "hkVector4" },
				{ "hy", "hkVector4" },
				{ "lz", "hkVector4" },
				{ "hz", "hkVector4" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
