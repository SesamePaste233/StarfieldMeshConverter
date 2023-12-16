#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class hkArray;

	class hclMoveParticlesOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		class VertexParticlePair : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint16 vertexIndex; // Offset: 0
			hkUint16 particleIndex; // Offset: 2

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclMoveParticlesOperator::VertexParticlePair"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkArray<hclMoveParticlesOperator::VertexParticlePair, hkContainerHeapAllocator> vertexParticlePairs; // Offset: 72
		hkUint32 simClothIndex; // Offset: 88
		hkUint32 refBufferIdx; // Offset: 92

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclMoveParticlesOperator"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
