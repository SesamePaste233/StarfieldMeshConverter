#pragma once
#include "hkInclude.h"
#include "hkTypes.h"

namespace hktypes {
	class hkBitField;

	class hclTransformSetUsage : public hkHolderBase {
	public:
		class TransformTracker : public hkHolderBase {
			hkBitField read;	// Offset: 0 Unk: 0
			hkBitField readBeforeWrite;	// Offset: 24 Unk: 0
			hkBitField written;	// Offset: 48 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		uint8_t perComponentFlags[2];	// Offset: 0 Unk: 0
		std::vector<TransformTracker> perComponentTransformTrackers;	// Offset: 8 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclBufferUsage : public hkHolderBase {
	public:
		uint8_t perComponentFlags[4];	// Offset: 0 Unk: 0
		bool trianglesRead;	// Offset: 4 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclStateDependencyGraph : public hkReferencedObject {
	public:
		class Branch : public hkHolderBase {
		public:
			int branchId;	// Offset: 0 Unk: 0
			std::vector<int> stateOperatorIndices;	// Offset: 8 Unk: 0
			std::vector<int> parentBranches;	// Offset: 24 Unk: 0
			std::vector<int> childBranches;	// Offset: 40 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclStateDependencyGraph::Branch> branches;	// Offset: 24 Unk: 0
		std::vector<int> rootBranchIds;	// Offset: 40 Unk: 0
		std::vector<std::vector<int>> children;	// Offset: 56 Unk: 0
		std::vector<std::vector<int>> parents;	// Offset: 72 Unk: 0
		bool multiThreadable;	// Offset: 88 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclClothState : public hkReferencedObject {
	public:
		class BufferAccess : public hkHolderBase {
			uint32_t bufferIndex;	// Offset: 0 Unk: 0
			hclBufferUsage bufferUsage;	// Offset: 4 Unk: 0
			uint32_t shadowBufferIndex;	// Offset: 12 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};
		class TransformSetAccess : public hkHolderBase {
			uint32_t transformSetIndex;	// Offset: 0 Unk: 0
			hclTransformSetUsage transformSetUsage;	// Offset: 8 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::string name;	// Offset: 24 Unk: 0
		std::vector<uint32_t> operators;	// Offset: 32 Unk: 0
		std::vector<hclClothState::BufferAccess> usedBuffers;	// Offset: 48 Unk: 0
		std::vector<hclClothState::TransformSetAccess> usedTransformSets;	// Offset: 64 Unk: 0
		std::vector<uint32_t> usedSimCloths;	// Offset: 80 Unk: 0
		hclStateDependencyGraph* dependencyGraph;	// Offset: 96 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}