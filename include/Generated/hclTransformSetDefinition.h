#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"

namespace hktypes{
	class hkReferencedObject;

	class hclTransformSetDefinition : public hkReferencedObject {
	public:
		std::string name; // Offset: 24
		int type; // Offset: 32
		uint32_t numTransforms; // Offset: 36

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
