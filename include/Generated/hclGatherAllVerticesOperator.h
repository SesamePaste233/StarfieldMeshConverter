#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"

namespace hktypes{
	class hclOperator;

	class hclGatherAllVerticesOperator : public hclOperator {
	public:
		std::vector<short> vertexInputFromVertexOutput; // Offset: 72
		uint32_t inputBufferIdx; // Offset: 88
		uint32_t outputBufferIdx; // Offset: 92
		bool gatherNormals; // Offset: 96
		bool partialGather; // Offset: 97

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
