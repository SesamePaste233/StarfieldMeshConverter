#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hknpBodyId : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint32 serialAndIndex; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpBodyId"; };
		inline std::string GetTranscriptId() override { return "hknpBodyId"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "serialAndIndex", "hkUint32" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
