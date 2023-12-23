#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hclObjectSpaceDeformer;

	class hclObjectSpaceSkinOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		hkArray<hkMatrix4, hkContainerHeapAllocator> boneFromSkinMeshTransforms; // Offset: 72
		hkArray<hkUint16, hkContainerHeapAllocator> transformSubset; // Offset: 88
		hkUint32 outputBufferIndex; // Offset: 104
		hkUint32 transformSetIndex; // Offset: 108
		hclObjectSpaceDeformer objectSpaceDeformer; // Offset: 112

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclObjectSpaceSkinOperator"; };
		inline std::string GetTranscriptId() override { return "hclObjectSpaceSkinOperator"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "boneFromSkinMeshTransforms", "hkArray<hkMatrix4, hkContainerHeapAllocator>" },
				{ "transformSubset", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "outputBufferIndex", "hkUint32" },
				{ "transformSetIndex", "hkUint32" },
				{ "objectSpaceDeformer", "hclObjectSpaceDeformer" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
