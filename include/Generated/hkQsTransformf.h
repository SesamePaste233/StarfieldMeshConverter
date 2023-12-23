#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4f;
	class hkQuaternionf;

	class hkQsTransformf : public hkHolderBase {
	public:
		using BaseType = void;
		hkVector4f translation; // Offset: 0
		hkQuaternionf rotation; // Offset: 16
		hkVector4f scale; // Offset: 32

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkQsTransformf"; };
		inline std::string GetTranscriptId() override { return "hkQsTransformf"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "translation", "hkVector4f" },
				{ "rotation", "hkQuaternionf" },
				{ "scale", "hkVector4f" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
