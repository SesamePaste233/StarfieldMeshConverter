#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4f;

	class hkQuaternionf : public hkHolderBase {
	public:
		using BaseType = void;
		hkVector4f vec; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkQuaternionf"; };
		inline std::string GetTranscriptId() override { return "hkQuaternionf"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "vec", "hkVector4f" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
