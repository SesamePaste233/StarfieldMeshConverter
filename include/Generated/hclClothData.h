#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkStringPtr;
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tENUM, typename tSTORAGE>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hkBool;
	template <typename tT, typename tAllocator>
	class ;

	class hclClothData : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class Platform : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclClothData::Platform"; };
			inline std::string GetTranscriptId() override { return "hclClothData::Platform"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkStringPtr name; // Offset: 24
		hkArray<T*<hclSimClothData>, hkContainerHeapAllocator> simClothDatas; // Offset: 32
		hkArray<T*<hclBufferDefinition>, hkContainerHeapAllocator> bufferDefinitions; // Offset: 48
		hkArray<T*<hclTransformSetDefinition>, hkContainerHeapAllocator> transformSetDefinitions; // Offset: 64
		hkArray<T*<hclOperator>, hkContainerHeapAllocator> operators; // Offset: 80
		hkArray<T*<hclClothState>, hkContainerHeapAllocator> clothStateDatas; // Offset: 96
		hkArray<T*<hclStateTransition>, hkContainerHeapAllocator> stateTransitions; // Offset: 112
		hkArray<T*<hclAction>, hkContainerHeapAllocator> actions; // Offset: 128
		hkBool generatedAtRuntime; // Offset: 144
		hkEnum<hclClothData::Platform, hkUint32> targetPlatform; // Offset: 148

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclClothData"; };
		inline std::string GetTranscriptId() override { return "hclClothData"; };
		inline uint32_t GethkClassHash() override { return 3195387577; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "simClothDatas", "hkArray<T*<hclSimClothData>, hkContainerHeapAllocator>" },
				{ "bufferDefinitions", "hkArray<T*<hclBufferDefinition>, hkContainerHeapAllocator>" },
				{ "transformSetDefinitions", "hkArray<T*<hclTransformSetDefinition>, hkContainerHeapAllocator>" },
				{ "operators", "hkArray<T*<hclOperator>, hkContainerHeapAllocator>" },
				{ "clothStateDatas", "hkArray<T*<hclClothState>, hkContainerHeapAllocator>" },
				{ "stateTransitions", "hkArray<T*<hclStateTransition>, hkContainerHeapAllocator>" },
				{ "actions", "hkArray<T*<hclAction>, hkContainerHeapAllocator>" },
				{ "generatedAtRuntime", "hkBool" },
				{ "targetPlatform", "hkEnum<hclClothData::Platform, hkUint32>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
