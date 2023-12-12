#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hkQsTransformf : public hkHolderBase {
	public:
		hkVector4Holder translation; // Offset: 0
		Eigen::Quaternionf rotation; // Offset: 16
		hkVector4Holder scale; // Offset: 32

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
