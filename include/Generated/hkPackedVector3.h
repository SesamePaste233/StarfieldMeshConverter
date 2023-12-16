#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkPackedVector3 : public hkHolderBase {
	public:
		using BaseType = void;
		T[N]<hkInt16, 4> values; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkPackedVector3"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
