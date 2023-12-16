#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class hkArray;

	class hclGatherAllVerticesOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		hkArray<hkInt16, hkContainerHeapAllocator> vertexInputFromVertexOutput; // Offset: 72
		hkUint32 inputBufferIdx; // Offset: 88
		hkUint32 outputBufferIdx; // Offset: 92
		hkBool gatherNormals; // Offset: 96
		hkBool partialGather; // Offset: 97

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclGatherAllVerticesOperator"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
