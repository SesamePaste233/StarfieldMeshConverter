#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclSimpleMeshBoneDeformOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		class TriangleBonePair : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint16 boneOffset; // Offset: 0
			hkUint16 triangleOffset; // Offset: 2

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimpleMeshBoneDeformOperator::TriangleBonePair"; };
			inline std::string GetTranscriptId() override { return "hclSimpleMeshBoneDeformOperator::TriangleBonePair"; };
			inline uint32_t GethkClassHash() override { return 2878957036; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "boneOffset", "hkUint16" },
					{ "triangleOffset", "hkUint16" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkUint32 inputBufferIdx; // Offset: 72
		hkUint32 outputTransformSetIdx; // Offset: 76
		hkArray<hclSimpleMeshBoneDeformOperator::TriangleBonePair, hkContainerHeapAllocator> triangleBonePairs; // Offset: 80
		hkArray<hkMatrix4, hkContainerHeapAllocator> localBoneTransforms; // Offset: 96

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclSimpleMeshBoneDeformOperator"; };
		inline std::string GetTranscriptId() override { return "hclSimpleMeshBoneDeformOperator"; };
		inline uint32_t GethkClassHash() override { return 1364889027; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "inputBufferIdx", "hkUint32" },
				{ "outputTransformSetIdx", "hkUint32" },
				{ "triangleBonePairs", "hkArray<hclSimpleMeshBoneDeformOperator::TriangleBonePair, hkContainerHeapAllocator>" },
				{ "localBoneTransforms", "hkArray<hkMatrix4, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
