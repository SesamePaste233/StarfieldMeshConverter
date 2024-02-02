#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class ;

	class hknpBSMaterialProperties : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkArray<hknpBSMaterial, hkContainerHeapAllocator> MaterialA; // Offset: 24

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpBSMaterialProperties"; };
		inline std::string GetTranscriptId() override { return "hknpBSMaterialProperties"; };
		inline uint32_t GethkClassHash() override { return 1963405616; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "MaterialA", "hkArray<hknpBSMaterial, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
