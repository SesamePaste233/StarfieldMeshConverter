#pragma once
#include "hkInclude.h"

#include "Generated\hclObjectSpaceSkinOperator.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hclObjectSpaceSkinOperator;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;

	class hclObjectSpaceSkinPNOperator : public hclObjectSpaceSkinOperator {
	public:
		using BaseType = hclObjectSpaceSkinOperator;
		hkArray<hclObjectSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator> localPNs; // Offset: 264
		hkArray<hclObjectSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator> localUnpackedPNs; // Offset: 280

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclObjectSpaceSkinPNOperator"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
