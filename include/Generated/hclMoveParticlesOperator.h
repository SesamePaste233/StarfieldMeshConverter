#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class ;

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
			inline std::string GethkClassName() override { return "hclMoveParticlesOperator::VertexParticlePair"; };
			inline std::string GetTranscriptId() override { return "hclMoveParticlesOperator::VertexParticlePair"; };
			inline uint32_t GethkClassHash() override { return 3905957961; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vertexIndex", "hkUint16" },
					{ "particleIndex", "hkUint16" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclMoveParticlesOperator::VertexParticlePair, hkContainerHeapAllocator> vertexParticlePairs; // Offset: 72
		hkUint32 simClothIndex; // Offset: 88
		hkUint32 refBufferIdx; // Offset: 92

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclMoveParticlesOperator"; };
		inline std::string GetTranscriptId() override { return "hclMoveParticlesOperator"; };
		inline uint32_t GethkClassHash() override { return 1999418277; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "vertexParticlePairs", "hkArray<hclMoveParticlesOperator::VertexParticlePair, hkContainerHeapAllocator>" },
				{ "simClothIndex", "hkUint32" },
				{ "refBufferIdx", "hkUint32" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
