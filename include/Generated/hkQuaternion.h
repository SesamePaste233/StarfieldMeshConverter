#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkQuaternionf;

	class hkQuaternion : public hkQuaternionf {
	public:
		using BaseType = hkQuaternionf;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkQuaternion"; };
		inline std::string GetTranscriptId() override { return "hkQuaternion"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
