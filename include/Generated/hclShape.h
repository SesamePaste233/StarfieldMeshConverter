#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;

	class hclShape : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		int type; // Offset: 24

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclShape"; };
		inline std::string GetTranscriptId() override { return "hclShape"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "type", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
