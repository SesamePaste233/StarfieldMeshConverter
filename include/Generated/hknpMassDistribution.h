#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4;
	class hkQuaternion;

	class hknpMassDistribution : public hkHolderBase {
	public:
		using BaseType = void;
		hkVector4 centerOfMassAndVolume; // Offset: 0
		hkQuaternion majorAxisSpace; // Offset: 16
		hkVector4 inertiaTensor; // Offset: 32

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpMassDistribution"; };
		inline std::string GetTranscriptId() override { return "hknpMassDistribution"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "centerOfMassAndVolume", "hkVector4" },
				{ "majorAxisSpace", "hkQuaternion" },
				{ "inertiaTensor", "hkVector4" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
