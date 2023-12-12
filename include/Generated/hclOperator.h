#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclClothState::BufferAccess.h"
#include "Generated\hclClothState::TransformSetAccess.h"

namespace hktypes{
	class hkReferencedObject;
	class hclClothState::BufferAccess;
	class hclClothState::TransformSetAccess;

	class hclOperator : public hkReferencedObject {
	public:
		std::string name; // Offset: 24
		uint32_t operatorID; // Offset: 32
		uint32_t type; // Offset: 36
		std::vector<hclClothState::BufferAccess> usedBuffers; // Offset: 40
		std::vector<hclClothState::TransformSetAccess> usedTransformSets; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
