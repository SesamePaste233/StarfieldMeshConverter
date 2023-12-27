#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclStretchLinkConstraintSetMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Batch : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkReal, 4> restLengths; // Offset: 0
			T[N]<hkReal, 4> stiffnesses; // Offset: 16
			T[N]<hkUint16, 4> particlesA; // Offset: 32
			T[N]<hkUint16, 4> particlesB; // Offset: 40

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStretchLinkConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclStretchLinkConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 1860398617; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLengths", "T[N]<hkReal, 4>" },
					{ "stiffnesses", "T[N]<hkReal, 4>" },
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
			inline std::string GethkClassName() override { return "hclStretchLinkConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclStretchLinkConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclStretchLinkConstraintSetMx::Batch, hkContainerHeapAllocator> batches; // Offset: 40
		hkArray<hclStretchLinkConstraintSetMx::Single, hkContainerHeapAllocator> singles; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclStretchLinkConstraintSetMx"; };
		inline std::string GetTranscriptId() override { return "hclStretchLinkConstraintSetMx"; };
		inline uint32_t GethkClassHash() override { return 3791460596; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "batches", "hkArray<hclStretchLinkConstraintSetMx::Batch, hkContainerHeapAllocator>" },
				{ "singles", "hkArray<hclStretchLinkConstraintSetMx::Single, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
