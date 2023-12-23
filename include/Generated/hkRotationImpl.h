#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tFT>
	class ;

	template <typename tFT>
	class hkRotationImpl;
	template<>
	class hkRotationImpl<float> : public hkMatrix3Impl<float> {
	public:
		using BaseType = hkMatrix3Impl<float>;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRotationImpl"; };
		inline std::string GetTranscriptId() override { return "hkRotationImpl<float>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
