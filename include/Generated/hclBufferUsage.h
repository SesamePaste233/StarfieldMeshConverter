#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hclBufferUsage : public hkHolderBase {
	public:
		using BaseType = void;
		T[N]<hkUint8, 4> perComponentFlags; // Offset: 0
		hkBool trianglesRead; // Offset: 4

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclBufferUsage"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
