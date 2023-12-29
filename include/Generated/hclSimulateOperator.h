#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkStringPtr;
	class hclOperator;
	class hkBool;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

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
			inline std::string GethkClassName() override { return "hclSimulateOperator::Config"; };
			inline std::string GetTranscriptId() override { return "hclSimulateOperator::Config"; };
			inline uint32_t GethkClassHash() override { return 2651451972; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "name", "hkStringPtr" },
					{ "constraintExecution", "hkArray<hkInt32, hkContainerHeapAllocator>" },
					{ "instanceCollidablesUsed", "hkArray<hkBool, hkContainerHeapAllocator>" },
					{ "subSteps", "hkUint8" },
					{ "numberOfSolveIterations", "hkUint8" },
					{ "useAllInstanceCollidables", "hkBool" },
					{ "adaptConstraintStiffness", "hkBool" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkUint32 simClothIndex; // Offset: 72
		hkArray<hclSimulateOperator::Config, hkContainerHeapAllocator> simulateOpConfigs; // Offset: 80

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclSimulateOperator"; };
		inline std::string GetTranscriptId() override { return "hclSimulateOperator"; };
		inline uint32_t GethkClassHash() override { return 2555309371; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "simClothIndex", "hkUint32" },
				{ "simulateOpConfigs", "hkArray<hclSimulateOperator::Config, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
