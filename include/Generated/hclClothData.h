#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclSimClothData.h"
#include "Generated\hclBufferDefinition.h"
#include "Generated\hclTransformSetDefinition.h"
#include "Generated\hclOperator.h"
#include "Generated\hclClothState.h"

namespace hktypes{
	class hkReferencedObject;
	class hclSimClothData;
	class hclBufferDefinition;
	class hclTransformSetDefinition;
	class hclOperator;
	class hclClothState;

	class hclClothData : public hkReferencedObject {
	public:
		class Platform : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::string name; // Offset: 24
		std::vector<hclSimClothData*> simClothDatas; // Offset: 32
		std::vector<hclBufferDefinition*> bufferDefinitions; // Offset: 48
		std::vector<hclTransformSetDefinition*> transformSetDefinitions; // Offset: 64
		std::vector<hclOperator*> operators; // Offset: 80
		std::vector<hclClothState*> clothStateDatas; // Offset: 96
		std::vector<hclStateTransition*> stateTransitions; // Offset: 112
		std::vector<hclAction*> actions; // Offset: 128
		bool generatedAtRuntime; // Offset: 144
		hclClothData::Platform targetPlatform; // Offset: 148

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
