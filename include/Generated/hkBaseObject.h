#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkBaseObject : public hkHolderBase {
	public:

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
