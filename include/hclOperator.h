#pragma once
#include "hkTypes.h"

namespace hktypes {
	class hclClothState : public hkReferencedObject {
	public:
		class BufferAccess : public hkHolderBase {
		};
		class TransformSetAccess : public hkHolderBase {
		};

		std::string name;
		std::vector<uint32_t> operators;
		std::vector<BufferAccess> usedBuffers;
		std::vector<TransformSetAccess> usedTransformSets;
		std::vector<uint32_t> usedSimCloths;

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclOperator : public hkReferencedObject {
	public:
		std::string name;	// Offset: 24 Unk: 0
		uint32_t operatorID;	// Offset: 32 Unk: 0
		uint32_t type;	// Offset: 36 Unk: 0
		std::vector<hclClothState::BufferAccess> usedBuffers;	// Offset: 40 Unk: 0
		std::vector<hclClothState::TransformSetAccess> usedTransformSets;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}