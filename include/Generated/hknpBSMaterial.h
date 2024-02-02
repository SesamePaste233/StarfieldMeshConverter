#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;

	class hknpBSMaterial : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkUint32 uiFilterInfo; // Offset: 24
		hkUint32 uiMaterialCRC; // Offset: 28

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpBSMaterial"; };
		inline std::string GetTranscriptId() override { return "hknpBSMaterial"; };
		inline uint32_t GethkClassHash() override { return 2317202776; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "uiFilterInfo", "hkUint32" },
				{ "uiMaterialCRC", "hkUint32" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
