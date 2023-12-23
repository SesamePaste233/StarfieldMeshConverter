#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4f;

	template <typename tFT>
	class hkMatrix4Impl;
	template<>
	class hkMatrix4Impl<float> : public hkHolderBase {
	public:
		using BaseType = void;
		hkVector4f col0; // Offset: 0
		hkVector4f col1; // Offset: 16
		hkVector4f col2; // Offset: 32
		hkVector4f col3; // Offset: 48

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkMatrix4Impl"; };
		inline std::string GetTranscriptId() override { return "hkMatrix4Impl<float>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "col0", "hkVector4f" },
				{ "col1", "hkVector4f" },
				{ "col2", "hkVector4f" },
				{ "col3", "hkVector4f" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
