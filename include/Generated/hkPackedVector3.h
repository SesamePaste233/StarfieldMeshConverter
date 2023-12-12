#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkPackedVector3 : public hkHolderBase {
	public:
		std::array<short, 4> values; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
