#pragma once
#include "hkInclude.h"

#include "Generated\hkArray.h"

namespace hktypes{
	template <typename tT, typename tAllocator>
	class hkArray;

	template<class tStorage>
	class hkBitFieldStorage : public hkHolderBase {
	public:
		using BaseType = void;
		hkArray<hkUint32, hkContainerHeapAllocator> words; // Offset: 0
		int numBits; // Offset: 16

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkBitFieldStorage"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
