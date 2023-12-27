#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkStringPtr;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclOperator : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkStringPtr name; // Offset: 24
		unsigned int operatorID; // Offset: 32
		unsigned int type; // Offset: 36
		hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator> usedBuffers; // Offset: 40
		hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator> usedTransformSets; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclOperator"; };
		inline std::string GetTranscriptId() override { return "hclOperator"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "operatorID", "unsigned int" },
				{ "type", "unsigned int" },
				{ "usedBuffers", "hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator>" },
				{ "usedTransformSets", "hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
