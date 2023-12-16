#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hclOperator;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;

	class hclSimulateOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		class Config : public hkHolderBase {
		public:
			using BaseType = void;
			hkStringPtr name; // Offset: 0
			hkArray<hkInt32, hkContainerHeapAllocator> constraintExecution; // Offset: 8
			hkArray<hkBool, hkContainerHeapAllocator> instanceCollidablesUsed; // Offset: 24
			hkUint8 subSteps; // Offset: 40
			hkUint8 numberOfSolveIterations; // Offset: 41
			hkBool useAllInstanceCollidables; // Offset: 42
			hkBool adaptConstraintStiffness; // Offset: 43

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclSimulateOperator::Config"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkUint32 simClothIndex; // Offset: 72
		hkArray<hclSimulateOperator::Config, hkContainerHeapAllocator> simulateOpConfigs; // Offset: 80

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclSimulateOperator"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
