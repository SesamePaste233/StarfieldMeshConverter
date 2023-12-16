#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"

namespace hktypes{
	class hkReferencedObject;

	class hclTransformSetDefinition : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkStringPtr name; // Offset: 24
		hkInt32 type; // Offset: 32
		hkUint32 numTransforms; // Offset: 36

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclTransformSetDefinition"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
