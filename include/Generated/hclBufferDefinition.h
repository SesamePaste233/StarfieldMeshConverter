#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkStringPtr;
	class hclBufferLayout;

	class hclBufferDefinition : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkStringPtr meshName; // Offset: 24
		hkStringPtr bufferName; // Offset: 32
		hkInt32 type; // Offset: 40
		hkInt32 subType; // Offset: 44
		hkUint32 numVertices; // Offset: 48
		hkUint32 numTriangles; // Offset: 52
		hclBufferLayout bufferLayout; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBufferDefinition"; };
		inline std::string GetTranscriptId() override { return "hclBufferDefinition"; };
		inline uint32_t GethkClassHash() override { return 1534215538; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "meshName", "hkStringPtr" },
				{ "bufferName", "hkStringPtr" },
				{ "type", "hkInt32" },
				{ "subType", "hkInt32" },
				{ "numVertices", "hkUint32" },
				{ "numTriangles", "hkUint32" },
				{ "bufferLayout", "hclBufferLayout" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
