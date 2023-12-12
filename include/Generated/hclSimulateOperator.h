#pragma once
#include "hkInclude.h"

#include "Generated\hclOperator.h"

namespace hktypes{
	class hclOperator;

	class hclSimulateOperator : public hclOperator {
	public:
		class Config : public hkHolderBase {
		public:
			std::string name; // Offset: 0
			std::vector<int> constraintExecution; // Offset: 8
			std::vector<bool> instanceCollidablesUsed; // Offset: 24
			uint8_t subSteps; // Offset: 40
			uint8_t numberOfSolveIterations; // Offset: 41
			bool useAllInstanceCollidables; // Offset: 42
			bool adaptConstraintStiffness; // Offset: 43

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		uint32_t simClothIndex; // Offset: 72
		std::vector<hclSimulateOperator::Config> simulateOpConfigs; // Offset: 80

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
