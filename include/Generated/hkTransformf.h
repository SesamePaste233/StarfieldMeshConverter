#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4f;
	class hkRotationf;

	class hkTransformf : public hkHolderBase {
	public:
		using BaseType = void;
		hkRotationf rotation; // Offset: 0
		hkVector4f translation; // Offset: 48

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkTransformf"; };
		inline std::string GetTranscriptId() override { return "hkTransformf"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "rotation", "hkRotationf" },
				{ "translation", "hkVector4f" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
