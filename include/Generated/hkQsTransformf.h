#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkQsTransformf : public hkHolderBase {
	public:
		using BaseType = void;
		hkVector4f translation; // Offset: 0
		hkQuaternionf rotation; // Offset: 16
		hkVector4f scale; // Offset: 32

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkQsTransformf"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
