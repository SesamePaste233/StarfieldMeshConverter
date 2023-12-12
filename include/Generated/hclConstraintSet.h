#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hkHandle<hkUint32, 2147483647>.h"

namespace hktypes{
	class hkReferencedObject;
	class hkHandle<hkUint32, 2147483647>;

	class hclConstraintSet : public hkReferencedObject {
	public:
		std::string name; // Offset: 24
		hkHandle<uint32_t> constraintId; // Offset: 32
		uint32_t type; // Offset: 36

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
