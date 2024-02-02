#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkStringPtr;
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class ;

	class hclSimClothPose : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkStringPtr name; // Offset: 24
		hkArray<hkVector4, hkContainerHeapAllocator> positions; // Offset: 32

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclSimClothPose"; };
		inline std::string GetTranscriptId() override { return "hclSimClothPose"; };
		inline uint32_t GethkClassHash() override { return 2913572451; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "positions", "hkArray<hkVector4, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
