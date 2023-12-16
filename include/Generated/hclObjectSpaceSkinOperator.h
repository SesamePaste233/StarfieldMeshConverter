#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hclObjectSpaceDeformer.h"

namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	class hclObjectSpaceDeformer;

	class hclObjectSpaceSkinOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		hkArray<hkMatrix4, hkContainerHeapAllocator> boneFromSkinMeshTransforms; // Offset: 72
		hkArray<hkUint16, hkContainerHeapAllocator> transformSubset; // Offset: 88
		hkUint32 outputBufferIndex; // Offset: 104
		hkUint32 transformSetIndex; // Offset: 108
		hclObjectSpaceDeformer objectSpaceDeformer; // Offset: 112

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclObjectSpaceSkinOperator"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
