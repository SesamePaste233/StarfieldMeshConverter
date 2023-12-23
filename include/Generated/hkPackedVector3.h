#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkPackedVector3 : public hkHolderBase {
	public:
		using BaseType = void;
		T[N]<hkInt16, 4> values; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkPackedVector3"; };
		inline std::string GetTranscriptId() override { return "hkPackedVector3"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "values", "T[N]<hkInt16, 4>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
