#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"

namespace hktypes{
	class hclOperator;

	class hclSimpleMeshBoneDeformOperator : public hclOperator {
	public:
		class TriangleBonePair : public hkHolderBase {
		public:
			uint16_t boneOffset; // Offset: 0
			uint16_t triangleOffset; // Offset: 2

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		uint32_t inputBufferIdx; // Offset: 72
		uint32_t outputTransformSetIdx; // Offset: 76
		std::vector<hclSimpleMeshBoneDeformOperator::TriangleBonePair> triangleBonePairs; // Offset: 80
		std::vector<hkMatrix4Holder> localBoneTransforms; // Offset: 96

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
