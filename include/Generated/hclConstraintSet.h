#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkStringPtr;
	template <typename tTYPE, typename vINVALID_VALUE>
	class ;

	class hclConstraintSet : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkStringPtr name; // Offset: 24
		hkHandle<hkUint32, 2147483647> constraintId; // Offset: 32
		unsigned int type; // Offset: 36

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclConstraintSet"; };
		inline std::string GetTranscriptId() override { return "hclConstraintSet"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "constraintId", "hkHandle<hkUint32, 2147483647>" },
				{ "type", "unsigned int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
