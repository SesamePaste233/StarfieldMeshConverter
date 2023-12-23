#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tStorage>
	class ;

	template <typename tStorage>
	class hkBitFieldBase;
	template<>
	class hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>> : public hkHolderBase {
	public:
		using BaseType = void;
		hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>> storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkBitFieldBase"; };
		inline std::string GetTranscriptId() override { return "hkBitFieldBase<hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
