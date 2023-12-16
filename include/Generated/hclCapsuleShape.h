#pragma once
#include "hkInclude.h"

#include "Generated\hclShape.h"

namespace hktypes{
	class hclShape;

	class hclCapsuleShape : public hclShape {
	public:
		using BaseType = hclShape;
		hkVector4 start; // Offset: 32
		hkVector4 end; // Offset: 48
		hkVector4 dir; // Offset: 64
		hkReal radius; // Offset: 80
		hkReal capLenSqrdInv; // Offset: 84

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclCapsuleShape"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
