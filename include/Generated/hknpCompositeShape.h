#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hknpShape;

	class hknpCompositeShape : public hknpShape {
	public:
		using BaseType = hknpShape;
		hkUint32 shapeTagCodecInfo; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpCompositeShape"; };
		inline std::string GetTranscriptId() override { return "hknpCompositeShape"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "shapeTagCodecInfo", "hkUint32" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
