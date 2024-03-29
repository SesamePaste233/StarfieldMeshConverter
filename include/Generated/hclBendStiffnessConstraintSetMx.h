#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkBool;
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclBendStiffnessConstraintSetMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Batch : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkReal, 4> weightsA; // Offset: 0
			T[N]<hkReal, 4> weightsB; // Offset: 16
			T[N]<hkReal, 4> weightsC; // Offset: 32
			T[N]<hkReal, 4> weightsD; // Offset: 48
			T[N]<hkReal, 4> bendStiffnesses; // Offset: 64
			T[N]<hkReal, 4> restCurvatures; // Offset: 80
			T[N]<hkReal, 4> invMassesA; // Offset: 96
			T[N]<hkReal, 4> invMassesB; // Offset: 112
			T[N]<hkReal, 4> invMassesC; // Offset: 128
			T[N]<hkReal, 4> invMassesD; // Offset: 144
			T[N]<hkUint16, 4> particlesA; // Offset: 160
			T[N]<hkUint16, 4> particlesB; // Offset: 168
			T[N]<hkUint16, 4> particlesC; // Offset: 176
			T[N]<hkUint16, 4> particlesD; // Offset: 184

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBendStiffnessConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclBendStiffnessConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 1314719274; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "weightsA", "T[N]<hkReal, 4>" },
					{ "weightsB", "T[N]<hkReal, 4>" },
					{ "weightsC", "T[N]<hkReal, 4>" },
					{ "weightsD", "T[N]<hkReal, 4>" },
					{ "bendStiffnesses", "T[N]<hkReal, 4>" },
					{ "restCurvatures", "T[N]<hkReal, 4>" },
					{ "invMassesA", "T[N]<hkReal, 4>" },
					{ "invMassesB", "T[N]<hkReal, 4>" },
					{ "invMassesC", "T[N]<hkReal, 4>" },
					{ "invMassesD", "T[N]<hkReal, 4>" },
					{ "particlesA", "T[N]<hkUint16, 4>" },
					{ "particlesB", "T[N]<hkUint16, 4>" },
					{ "particlesC", "T[N]<hkUint16, 4>" },
					{ "particlesD", "T[N]<hkUint16, 4>" },
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
			inline std::string GethkClassName() override { return "hclBendStiffnessConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclBendStiffnessConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclBendStiffnessConstraintSetMx::Batch, hkContainerHeapAllocator> batches; // Offset: 40
		hkArray<hclBendStiffnessConstraintSetMx::Single, hkContainerHeapAllocator> singles; // Offset: 56
		hkReal maxRestPoseHeightSq; // Offset: 72
		hkBool clampBendStiffness; // Offset: 76
		hkBool useRestPoseConfig; // Offset: 77

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBendStiffnessConstraintSetMx"; };
		inline std::string GetTranscriptId() override { return "hclBendStiffnessConstraintSetMx"; };
		inline uint32_t GethkClassHash() override { return 111263749; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "batches", "hkArray<hclBendStiffnessConstraintSetMx::Batch, hkContainerHeapAllocator>" },
				{ "singles", "hkArray<hclBendStiffnessConstraintSetMx::Single, hkContainerHeapAllocator>" },
				{ "maxRestPoseHeightSq", "hkReal" },
				{ "clampBendStiffness", "hkBool" },
				{ "useRestPoseConfig", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
