#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tT, typename tAllocator>
	class ;
	class hclObjectSpaceSkinOperator;
	template <typename tT, typename tAllocator>
	class ;

	class hclObjectSpaceSkinPNOperator : public hclObjectSpaceSkinOperator {
	public:
		using BaseType = hclObjectSpaceSkinOperator;
		hkArray<hclObjectSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator> localPNs; // Offset: 264
		hkArray<hclObjectSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator> localUnpackedPNs; // Offset: 280

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclObjectSpaceSkinPNOperator"; };
		inline std::string GetTranscriptId() override { return "hclObjectSpaceSkinPNOperator"; };
		inline uint32_t GethkClassHash() override { return 3464584781; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "localPNs", "hkArray<hclObjectSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator>" },
				{ "localUnpackedPNs", "hkArray<hclObjectSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
