#pragma once
#include "hkInclude.h"


namespace hktypes{

	template<class tT, class tAllocator>
	class hkArray : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkArray"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
