#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tFT>
	class ;

	class hkRotationf : public hkRotationImpl<float> {
	public:
		using BaseType = hkRotationImpl<float>;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRotationf"; };
		inline std::string GetTranscriptId() override { return "hkRotationf"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
