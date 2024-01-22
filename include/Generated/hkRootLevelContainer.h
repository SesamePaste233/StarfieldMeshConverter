#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tT, typename tAllocator>
	class ;
	class hkRefVariant;
	class hkStringPtr;

	class hkRootLevelContainer : public hkHolderBase {
	public:
		using BaseType = void;
		class NamedVariant : public hkHolderBase {
		public:
			using BaseType = void;
			hkStringPtr name; // Offset: 0
			hkStringPtr className; // Offset: 8
			hkRefVariant variant; // Offset: 16

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hkRootLevelContainer::NamedVariant"; };
			inline std::string GetTranscriptId() override { return "hkRootLevelContainer::NamedVariant"; };
			inline uint32_t GethkClassHash() override { return 2807201; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "name", "hkStringPtr" },
					{ "className", "hkStringPtr" },
					{ "variant", "hkRefVariant" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hkRootLevelContainer::NamedVariant, hkContainerHeapAllocator> namedVariants; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkRootLevelContainer"; };
		inline std::string GetTranscriptId() override { return "hkRootLevelContainer"; };
		inline uint32_t GethkClassHash() override { return 54921221; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "namedVariants", "hkArray<hkRootLevelContainer::NamedVariant, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
