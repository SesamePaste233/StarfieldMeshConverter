#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"

namespace hktypes{
	class hkReferencedObject;

	class hclStateDependencyGraph : public hkReferencedObject {
	public:
		class Branch : public hkHolderBase {
		public:
			int branchId; // Offset: 0
			std::vector<int> stateOperatorIndices; // Offset: 8
			std::vector<int> parentBranches; // Offset: 24
			std::vector<int> childBranches; // Offset: 40

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclStateDependencyGraph::Branch> branches; // Offset: 24
		std::vector<int> rootBranchIds; // Offset: 40
		std::vector<std::vector<int>> children; // Offset: 56
		std::vector<std::vector<int>> parents; // Offset: 72
		bool multiThreadable; // Offset: 88

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
