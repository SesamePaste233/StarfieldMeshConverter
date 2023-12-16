#pragma once
#include "hkInclude.h"

#include "Generated\hclBufferDefinition.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hclBufferDefinition;
	template <typename tT, typename tAllocator>
	class hkArray;

	class hclScratchBufferDefinition : public hclBufferDefinition {
	public:
		using BaseType = hclBufferDefinition;
		hkArray<hkUint16, hkContainerHeapAllocator> triangleIndices; // Offset: 88
		hkBool storeNormals; // Offset: 104
		hkBool storeTangentsAndBiTangents; // Offset: 105

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclScratchBufferDefinition"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
