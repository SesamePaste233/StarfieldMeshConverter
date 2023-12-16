#pragma once
#include "hkInclude.h"

#include "Generated\hkBitFieldStorage.h"

namespace hktypes{
	template<class tStorage>
	class hkBitFieldStorage<tStorage>;

	template<class tStorage>
	class hkBitFieldBase : public hkHolderBase {
	public:
		using BaseType = void;
		hkBitFieldStorage<tStorage> storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkBitFieldBase"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
