#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclBufferUsage.h"
#include "Generated\hclTransformSetUsage.h"
#include "Generated\hclStateDependencyGraph.h"

namespace hktypes{
	class hkReferencedObject;
	class hclBufferUsage;
	class hclTransformSetUsage;
	class hclStateDependencyGraph;

	class hclClothState : public hkReferencedObject {
	public:
		class BufferAccess : public hkHolderBase {
		public:
			uint32_t bufferIndex; // Offset: 0
			hclBufferUsage bufferUsage; // Offset: 4
			uint32_t shadowBufferIndex; // Offset: 12

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class TransformSetAccess : public hkHolderBase {
		public:
			uint32_t transformSetIndex; // Offset: 0
			hclTransformSetUsage transformSetUsage; // Offset: 8

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::string name; // Offset: 24
		std::vector<uint32_t> operators; // Offset: 32
		std::vector<hclClothState::BufferAccess> usedBuffers; // Offset: 48
		std::vector<hclClothState::TransformSetAccess> usedTransformSets; // Offset: 64
		std::vector<uint32_t> usedSimCloths; // Offset: 80
		hclStateDependencyGraph* dependencyGraph; // Offset: 96

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
