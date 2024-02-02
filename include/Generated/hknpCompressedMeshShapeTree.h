#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkcdDefaultStaticMeshTree;

	class hknpCompressedMeshShapeTree : public hkcdDefaultStaticMeshTree {
	public:
		using BaseType = hkcdDefaultStaticMeshTree;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpCompressedMeshShapeTree"; };
		inline std::string GetTranscriptId() override { return "hknpCompressedMeshShapeTree"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
