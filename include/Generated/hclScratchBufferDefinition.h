#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclBufferDefinition;
	class hkBool;
	template <typename tT, typename tAllocator>
	class ;

	class hclScratchBufferDefinition : public hclBufferDefinition {
	public:
		using BaseType = hclBufferDefinition;
		hkArray<hkUint16, hkContainerHeapAllocator> triangleIndices; // Offset: 88
		hkBool storeNormals; // Offset: 104
		hkBool storeTangentsAndBiTangents; // Offset: 105

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclScratchBufferDefinition"; };
		inline std::string GetTranscriptId() override { return "hclScratchBufferDefinition"; };
		inline uint32_t GethkClassHash() override { return 387079732; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "triangleIndices", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "storeNormals", "hkBool" },
				{ "storeTangentsAndBiTangents", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
