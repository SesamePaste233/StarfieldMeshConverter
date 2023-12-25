#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclCompressibleLinkConstraintSetMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Batch : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkReal, 4> restLengths; // Offset: 0
			T[N]<hkReal, 4> compressionLengths; // Offset: 16
			T[N]<hkReal, 4> stiffnessesA; // Offset: 32
			T[N]<hkReal, 4> stiffnessesB; // Offset: 48
			T[N]<hkUint16, 4> particlesA; // Offset: 64
			T[N]<hkUint16, 4> particlesB; // Offset: 72

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclCompressibleLinkConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclCompressibleLinkConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 4253223837; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLengths", "T[N]<hkReal, 4>" },
					{ "compressionLengths", "T[N]<hkReal, 4>" },
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
			hkReal restLength; // Offset: 0
			hkReal compressionLength; // Offset: 4
			hkReal stiffnessA; // Offset: 8
			hkReal stiffnessB; // Offset: 12
			hkUint16 particleA; // Offset: 16
			hkUint16 particleB; // Offset: 18

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclCompressibleLinkConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclCompressibleLinkConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 523401191; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLength", "hkReal" },
					{ "compressionLength", "hkReal" },
					{ "stiffnessA", "hkReal" },
					{ "stiffnessB", "hkReal" },
					{ "particleA", "hkUint16" },
					{ "particleB", "hkUint16" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclCompressibleLinkConstraintSetMx::Batch, hkContainerHeapAllocator> batches; // Offset: 40
		hkArray<hclCompressibleLinkConstraintSetMx::Single, hkContainerHeapAllocator> singles; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclCompressibleLinkConstraintSetMx"; };
		inline std::string GetTranscriptId() override { return "hclCompressibleLinkConstraintSetMx"; };
		inline uint32_t GethkClassHash() override { return 3230409386; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "batches", "hkArray<hclCompressibleLinkConstraintSetMx::Batch, hkContainerHeapAllocator>" },
				{ "singles", "hkArray<hclCompressibleLinkConstraintSetMx::Single, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
