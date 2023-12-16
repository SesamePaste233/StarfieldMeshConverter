#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;

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
			static inline std::string GethkClassName() { return "hclStateDependencyGraph::Branch"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkArray<hclStateDependencyGraph::Branch, hkContainerHeapAllocator> branches; // Offset: 24
		hkArray<int, hkContainerHeapAllocator> rootBranchIds; // Offset: 40
		hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator> children; // Offset: 56
		hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator> parents; // Offset: 72
		hkBool multiThreadable; // Offset: 88

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclStateDependencyGraph"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
