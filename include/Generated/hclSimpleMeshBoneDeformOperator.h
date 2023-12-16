#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;

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
			static inline std::string GethkClassName() { return "hclSimpleMeshBoneDeformOperator::TriangleBonePair"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkUint32 inputBufferIdx; // Offset: 72
		hkUint32 outputTransformSetIdx; // Offset: 76
		hkArray<hclSimpleMeshBoneDeformOperator::TriangleBonePair, hkContainerHeapAllocator> triangleBonePairs; // Offset: 80
		hkArray<hkMatrix4, hkContainerHeapAllocator> localBoneTransforms; // Offset: 96

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclSimpleMeshBoneDeformOperator"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
