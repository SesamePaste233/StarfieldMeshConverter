#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclOperator;
	class hkBool;
	template <typename tT, typename tAllocator>
	class ;

	class hclGatherAllVerticesOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		hkArray<hkInt16, hkContainerHeapAllocator> vertexInputFromVertexOutput; // Offset: 72
		hkUint32 inputBufferIdx; // Offset: 88
		hkUint32 outputBufferIdx; // Offset: 92
		hkBool gatherNormals; // Offset: 96
		hkBool partialGather; // Offset: 97

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclGatherAllVerticesOperator"; };
		inline std::string GetTranscriptId() override { return "hclGatherAllVerticesOperator"; };
		inline uint32_t GethkClassHash() override { return 2385740196; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "vertexInputFromVertexOutput", "hkArray<hkInt16, hkContainerHeapAllocator>" },
				{ "inputBufferIdx", "hkUint32" },
				{ "outputBufferIdx", "hkUint32" },
				{ "gatherNormals", "hkBool" },
				{ "partialGather", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
