#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hclBoneSpaceSkinOperator;

	class hclBoneSpaceSkinPNOperator : public hclBoneSpaceSkinOperator {
	public:
		using BaseType = hclBoneSpaceSkinOperator;
		hkArray<hclBoneSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator> localPNs; // Offset: 184
		hkArray<hclBoneSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator> localUnpackedPNs; // Offset: 200

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBoneSpaceSkinPNOperator"; };
		inline std::string GetTranscriptId() override { return "hclBoneSpaceSkinPNOperator"; };
		inline uint32_t GethkClassHash() override { return 2804828730; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "localPNs", "hkArray<hclBoneSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator>" },
				{ "localUnpackedPNs", "hkArray<hclBoneSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
