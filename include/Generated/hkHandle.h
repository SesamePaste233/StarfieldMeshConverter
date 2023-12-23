#pragma once
#include "hkInclude.h"


namespace hktypes{

	template <typename tTYPE, typename vINVALID_VALUE>
	class hkHandle;
	template<>
	class hkHandle<hkUint32, 2147483647> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint32 value; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkHandle"; };
		inline std::string GetTranscriptId() override { return "hkHandle<hkUint32, 2147483647>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "value", "hkUint32" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
