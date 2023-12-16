#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hkHandle.h"

namespace hktypes{
	class hkReferencedObject;
	template <typename tTYPE, typename vINVALID_VALUE>
	class hkHandle;

	class hclConstraintSet : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkStringPtr name; // Offset: 24
		hkHandle<hkUint32, 2147483647> constraintId; // Offset: 32
		unsigned int type; // Offset: 36

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclConstraintSet"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
