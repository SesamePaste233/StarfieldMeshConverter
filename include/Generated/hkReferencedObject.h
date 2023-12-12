#pragma once
#include "hkInclude.h"

#include "Generated\hkBaseObject.h"

namespace hktypes{
	class hkBaseObject;

	class hkReferencedObject : public hkBaseObject {
	public:
		uint64_t sizeAndFlags; // Offset: 8
		uint64_t refCount; // Offset: 16

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
