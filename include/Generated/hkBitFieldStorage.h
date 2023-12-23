#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tT, typename tAllocator>
	class ;

	template <typename tStorage>
	class hkBitFieldStorage;
	template<>
	class hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>> : public hkHolderBase {
	public:
		using BaseType = void;
		hkArray<hkUint32, hkContainerHeapAllocator> words; // Offset: 0
		int numBits; // Offset: 16

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkBitFieldStorage"; };
		inline std::string GetTranscriptId() override { return "hkBitFieldStorage<hkArray<hkUint32, hkContainerHeapAllocator>>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "words", "hkArray<hkUint32, hkContainerHeapAllocator>" },
				{ "numBits", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
