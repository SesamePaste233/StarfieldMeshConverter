#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclBufferLayout.h"

namespace hktypes{
	class hkReferencedObject;
	class hclBufferLayout;

	class hclBufferDefinition : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkStringPtr meshName; // Offset: 24
		hkStringPtr bufferName; // Offset: 32
		hkInt32 type; // Offset: 40
		hkInt32 subType; // Offset: 44
		hkUint32 numVertices; // Offset: 48
		hkUint32 numTriangles; // Offset: 52
		hclBufferLayout bufferLayout; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclBufferDefinition"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
