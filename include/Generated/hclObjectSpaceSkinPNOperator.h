#pragma once
#include "hkInclude.h"

#include "Generated\hclObjectSpaceSkinOperator.h"
#include "Generated\hclObjectSpaceDeformer::LocalBlockPN.h"

namespace hktypes{
	class hclObjectSpaceSkinOperator;
	class hclObjectSpaceDeformer::LocalBlockPN;

	class hclObjectSpaceSkinPNOperator : public hclObjectSpaceSkinOperator {
	public:
		std::vector<hclObjectSpaceDeformer::LocalBlockPN> localPNs; // Offset: 264
		std::vector<hclObjectSpaceDeformer::LocalBlockUnpackedPN> localUnpackedPNs; // Offset: 280

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
