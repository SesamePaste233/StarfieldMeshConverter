#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkPackedVector3;

	class hkCompressedMassProperties : public hkHolderBase {
	public:
		using BaseType = void;
		hkPackedVector3 centerOfMass; // Offset: 0
		hkPackedVector3 inertia; // Offset: 8
		T[N]<short, 4> majorAxisSpace; // Offset: 16
		hkReal mass; // Offset: 24
		hkReal volume; // Offset: 28

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkCompressedMassProperties"; };
		inline std::string GetTranscriptId() override { return "hkCompressedMassProperties"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "centerOfMass", "hkPackedVector3" },
				{ "inertia", "hkPackedVector3" },
				{ "majorAxisSpace", "T[N]<short, 4>" },
				{ "mass", "hkReal" },
				{ "volume", "hkReal" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
