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
			T[N]<hkReal, 4> restLengths; // Offset: 0
			T[N]<hkReal, 4> stiffnessesA; // Offset: 16
			T[N]<hkReal, 4> stiffnessesB; // Offset: 32
			T[N]<hkUint16, 4> particlesA; // Offset: 48
			T[N]<hkUint16, 4> particlesB; // Offset: 56

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStandardLinkConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclStandardLinkConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 516152436; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLengths", "T[N]<hkReal, 4>" },
					{ "stiffnessesA", "T[N]<hkReal, 4>" },
					{ "stiffnessesB", "T[N]<hkReal, 4>" },
					{ "particlesA", "T[N]<hkUint16, 4>" },
					{ "particlesB", "T[N]<hkUint16, 4>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class Single : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStandardLinkConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclStandardLinkConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
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
