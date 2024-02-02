#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkcdSimdTree;
	class hkcdStaticMeshTree::Connectivity;
	class hknpCompressedMeshShapeTree;

	class hknpCompressedMeshShapeData : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hknpCompressedMeshShapeTree meshTree; // Offset: 32
		hkcdSimdTree simdTree; // Offset: 192
		hkcdStaticMeshTree::Connectivity connectivity; // Offset: 216
		bool hasSimdTree; // Offset: 264

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpCompressedMeshShapeData"; };
		inline std::string GetTranscriptId() override { return "hknpCompressedMeshShapeData"; };
		inline uint32_t GethkClassHash() override { return 3359157891; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "meshTree", "hknpCompressedMeshShapeTree" },
				{ "simdTree", "hkcdSimdTree" },
				{ "connectivity", "hkcdStaticMeshTree::Connectivity" },
				{ "hasSimdTree", "bool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
