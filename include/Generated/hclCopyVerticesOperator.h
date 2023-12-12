#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"

namespace hktypes{
	class hclOperator;

	class hclCopyVerticesOperator : public hclOperator {
	public:
		uint32_t inputBufferIdx; // Offset: 72
		uint32_t outputBufferIdx; // Offset: 76
		uint32_t numberOfVertices; // Offset: 80
		uint32_t startVertexIn; // Offset: 84
		uint32_t startVertexOut; // Offset: 88
		bool copyNormals; // Offset: 92

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
