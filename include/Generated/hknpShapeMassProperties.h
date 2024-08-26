#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkCompressedMassProperties;

	class hknpShapeMassProperties : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkCompressedMassProperties compressedMassProperties; // Offset: 24

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpShapeMassProperties"; };
		inline std::string GetTranscriptId() override { return "hknpShapeMassProperties"; };
		inline uint32_t GethkClassHash() override { return 4217350405; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "compressedMassProperties", "hkCompressedMassProperties" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
