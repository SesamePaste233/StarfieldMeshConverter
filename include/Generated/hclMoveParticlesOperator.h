#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"

namespace hktypes{
	class hclOperator;

	class hclMoveParticlesOperator : public hclOperator {
	public:
		class VertexParticlePair : public hkHolderBase {
		public:
			uint16_t vertexIndex; // Offset: 0
			uint16_t particleIndex; // Offset: 2

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclMoveParticlesOperator::VertexParticlePair> vertexParticlePairs; // Offset: 72
		uint32_t simClothIndex; // Offset: 88
		uint32_t refBufferIdx; // Offset: 92

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
