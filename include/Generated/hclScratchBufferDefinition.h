#pragma once
#include "hkInclude.h"

#include "Generated\hclBufferDefinition.h"

namespace hktypes{
	class hclBufferDefinition;

	class hclScratchBufferDefinition : public hclBufferDefinition {
	public:
		std::vector<uint16_t> triangleIndices; // Offset: 88
		bool storeNormals; // Offset: 104
		bool storeTangentsAndBiTangents; // Offset: 105

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
