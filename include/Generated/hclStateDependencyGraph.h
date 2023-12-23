#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkBool;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclStateDependencyGraph : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class Branch : public hkHolderBase {
		public:
			using BaseType = void;
			int branchId; // Offset: 0
			hkArray<int, hkContainerHeapAllocator> stateOperatorIndices; // Offset: 8
			hkArray<int, hkContainerHeapAllocator> parentBranches; // Offset: 24
			hkArray<int, hkContainerHeapAllocator> childBranches; // Offset: 40

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStateDependencyGraph::Branch"; };
			inline std::string GetTranscriptId() override { return "hclStateDependencyGraph::Branch"; };
			inline uint32_t GethkClassHash() override { return 2493525897; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "branchId", "int" },
					{ "stateOperatorIndices", "hkArray<int, hkContainerHeapAllocator>" },
					{ "parentBranches", "hkArray<int, hkContainerHeapAllocator>" },
					{ "childBranches", "hkArray<int, hkContainerHeapAllocator>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclStateDependencyGraph::Branch, hkContainerHeapAllocator> branches; // Offset: 24
		hkArray<int, hkContainerHeapAllocator> rootBranchIds; // Offset: 40
		hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator> children; // Offset: 56
		hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator> parents; // Offset: 72
		hkBool multiThreadable; // Offset: 88

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclStateDependencyGraph"; };
		inline std::string GetTranscriptId() override { return "hclStateDependencyGraph"; };
		inline uint32_t GethkClassHash() override { return 2248211247; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "branches", "hkArray<hclStateDependencyGraph::Branch, hkContainerHeapAllocator>" },
				{ "rootBranchIds", "hkArray<int, hkContainerHeapAllocator>" },
				{ "children", "hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>" },
				{ "parents", "hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>" },
				{ "multiThreadable", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
