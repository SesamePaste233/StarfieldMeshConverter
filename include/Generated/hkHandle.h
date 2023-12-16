#pragma once
#include "hkInclude.h"


namespace hktypes{

	template<class tTYPE, class vINVALID_VALUE>
	class hkHandle : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint32 value; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkHandle"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
