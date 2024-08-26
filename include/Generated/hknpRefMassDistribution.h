#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hknpMassDistribution;

	class hknpRefMassDistribution : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hknpMassDistribution massDistribution; // Offset: 32

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpRefMassDistribution"; };
		inline std::string GetTranscriptId() override { return "hknpRefMassDistribution"; };
		inline uint32_t GethkClassHash() override { return 46991855; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "massDistribution", "hknpMassDistribution" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
