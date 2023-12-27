#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkStringPtr;

	class hclTransformSetDefinition : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkStringPtr name; // Offset: 24
		hkInt32 type; // Offset: 32
		hkUint32 numTransforms; // Offset: 36

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclTransformSetDefinition"; };
		inline std::string GetTranscriptId() override { return "hclTransformSetDefinition"; };
		inline uint32_t GethkClassHash() override { return 1127359486; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "type", "hkInt32" },
				{ "numTransforms", "hkUint32" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
