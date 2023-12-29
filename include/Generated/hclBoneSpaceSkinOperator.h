#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class ;
	class hclBoneSpaceDeformer;

	class hclBoneSpaceSkinOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		hkArray<hkUint16, hkContainerHeapAllocator> transformSubset; // Offset: 72
		hkUint32 outputBufferIndex; // Offset: 88
		hkUint32 transformSetIndex; // Offset: 92
		hclBoneSpaceDeformer boneSpaceDeformer; // Offset: 96

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBoneSpaceSkinOperator"; };
		inline std::string GetTranscriptId() override { return "hclBoneSpaceSkinOperator"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "transformSubset", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "outputBufferIndex", "hkUint32" },
				{ "transformSetIndex", "hkUint32" },
				{ "boneSpaceDeformer", "hclBoneSpaceDeformer" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
