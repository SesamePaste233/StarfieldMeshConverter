#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tTYPE>
	class ;

	class hkRefCountedProperties : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class Entry : public hkHolderBase {
		public:
			using BaseType = void;
			hkRefPtr<hkReferencedObject> object; // Offset: 0
			hkUint16 key; // Offset: 8
			hkUint16 flags; // Offset: 10

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hkRefCountedProperties::Entry"; };
			inline std::string GetTranscriptId() override { return "hkRefCountedProperties::Entry"; };
			inline uint32_t GethkClassHash() override { return 3846323405; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "object", "hkRefPtr<hkReferencedObject>" },
					{ "key", "hkUint16" },
					{ "flags", "hkUint16" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator> entries; // Offset: 24

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRefCountedProperties"; };
		inline std::string GetTranscriptId() override { return "hkRefCountedProperties"; };
		inline uint32_t GethkClassHash() override { return 4226104209; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "entries", "hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
