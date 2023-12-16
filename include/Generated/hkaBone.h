#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkaBone : public hkHolderBase {
	public:
		using BaseType = void;
		hkStringPtr name; // Offset: 0
		hkBool lockTranslation; // Offset: 8

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkaBone"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
