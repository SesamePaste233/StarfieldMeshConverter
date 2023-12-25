#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclOperator;
	class hkBool;

	class hclCopyVerticesOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		hkUint32 inputBufferIdx; // Offset: 72
		hkUint32 outputBufferIdx; // Offset: 76
		hkUint32 numberOfVertices; // Offset: 80
		hkUint32 startVertexIn; // Offset: 84
		hkUint32 startVertexOut; // Offset: 88
		hkBool copyNormals; // Offset: 92

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclCopyVerticesOperator"; };
		inline std::string GetTranscriptId() override { return "hclCopyVerticesOperator"; };
		inline uint32_t GethkClassHash() override { return 4200025597; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "inputBufferIdx", "hkUint32" },
				{ "outputBufferIdx", "hkUint32" },
				{ "numberOfVertices", "hkUint32" },
				{ "startVertexIn", "hkUint32" },
				{ "startVertexOut", "hkUint32" },
				{ "copyNormals", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
