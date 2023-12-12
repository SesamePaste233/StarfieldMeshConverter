#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"
#include "Generated\hclObjectSpaceDeformer.h"

namespace hktypes{
	class hclOperator;
	class hclObjectSpaceDeformer;

	class hclObjectSpaceSkinOperator : public hclOperator {
	public:
		std::vector<hkMatrix4Holder> boneFromSkinMeshTransforms; // Offset: 72
		std::vector<uint16_t> transformSubset; // Offset: 88
		uint32_t outputBufferIndex; // Offset: 104
		uint32_t transformSetIndex; // Offset: 108
		hclObjectSpaceDeformer objectSpaceDeformer; // Offset: 112

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
