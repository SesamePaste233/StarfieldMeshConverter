#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tStorage>
	class ;

	class hkBitField : public hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>> {
	public:
		using BaseType = hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkBitField"; };
		inline std::string GetTranscriptId() override { return "hkBitField"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
