#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkBaseObject;

	class hkReferencedObject : public hkBaseObject {
	public:
		using BaseType = hkBaseObject;
		hkUlong sizeAndFlags; // Offset: 8
		hkUlong refCount; // Offset: 16

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkReferencedObject"; };
		inline std::string GetTranscriptId() override { return "hkReferencedObject"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "sizeAndFlags", "hkUlong" },
				{ "refCount", "hkUlong" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
