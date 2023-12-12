#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkaBone : public hkHolderBase {
	public:
		std::string name; // Offset: 0
		bool lockTranslation; // Offset: 8

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
