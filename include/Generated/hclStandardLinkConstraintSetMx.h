#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclStandardLinkConstraintSetMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Batch : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStandardLinkConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclStandardLinkConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class Single : public hkHolderBase {
		public:
			using BaseType = void;
			hkReal restLength; // Offset: 0
			hkReal stiffnessA; // Offset: 4
			hkReal stiffnessB; // Offset: 8
			hkUint16 particleA; // Offset: 12
			hkUint16 particleB; // Offset: 14

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStandardLinkConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclStandardLinkConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 2457992725; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLength", "hkReal" },
					{ "stiffnessA", "hkReal" },
					{ "stiffnessB", "hkReal" },
					{ "particleA", "hkUint16" },
					{ "particleB", "hkUint16" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclStandardLinkConstraintSetMx::Batch, hkContainerHeapAllocator> batches; // Offset: 40
		hkArray<hclStandardLinkConstraintSetMx::Single, hkContainerHeapAllocator> singles; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclStandardLinkConstraintSetMx"; };
		inline std::string GetTranscriptId() override { return "hclStandardLinkConstraintSetMx"; };
		inline uint32_t GethkClassHash() override { return 4021914366; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "batches", "hkArray<hclStandardLinkConstraintSetMx::Batch, hkContainerHeapAllocator>" },
				{ "singles", "hkArray<hclStandardLinkConstraintSetMx::Single, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
