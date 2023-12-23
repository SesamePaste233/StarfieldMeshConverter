#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tFT>
	class ;

	class hkMatrix4f : public hkMatrix4Impl<float> {
	public:
		using BaseType = hkMatrix4Impl<float>;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkMatrix4f"; };
		inline std::string GetTranscriptId() override { return "hkMatrix4f"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
