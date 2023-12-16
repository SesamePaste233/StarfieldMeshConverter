#pragma once
#include "hkInclude.h"

#include "Generated\hkBaseObject.h"

namespace hktypes{
	class hkBaseObject;

	class hkReferencedObject : public hkBaseObject {
	public:
		using BaseType = hkBaseObject;
		hkUlong sizeAndFlags; // Offset: 8
		hkUlong refCount; // Offset: 16

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkReferencedObject"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
