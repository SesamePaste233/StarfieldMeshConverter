#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hclBufferUsage : public hkHolderBase {
	public:
		std::array<uint8_t, 4> perComponentFlags; // Offset: 0
		bool trianglesRead; // Offset: 4

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
