#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"

namespace hktypes{
	class hkReferencedObject;

	class hclShape : public hkReferencedObject {
	public:
		int type; // Offset: 24

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
