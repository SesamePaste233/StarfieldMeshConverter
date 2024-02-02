#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkBool;
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class ;

	class hclBendStiffnessConstraintSet : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Link : public hkHolderBase {
		public:
			using BaseType = void;
			hkReal weightA; // Offset: 0
			hkReal weightB; // Offset: 4
			hkReal weightC; // Offset: 8
			hkReal weightD; // Offset: 12
			hkReal bendStiffness; // Offset: 16
			hkReal restCurvature; // Offset: 20
			hkUint16 particleA; // Offset: 24
			hkUint16 particleB; // Offset: 26
			hkUint16 particleC; // Offset: 28
			hkUint16 particleD; // Offset: 30

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBendStiffnessConstraintSet::Link"; };
			inline std::string GetTranscriptId() override { return "hclBendStiffnessConstraintSet::Link"; };
			inline uint32_t GethkClassHash() override { return 275062867; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "weightA", "hkReal" },
					{ "weightB", "hkReal" },
					{ "weightC", "hkReal" },
					{ "weightD", "hkReal" },
					{ "bendStiffness", "hkReal" },
					{ "restCurvature", "hkReal" },
					{ "particleA", "hkUint16" },
					{ "particleB", "hkUint16" },
					{ "particleC", "hkUint16" },
					{ "particleD", "hkUint16" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclBendStiffnessConstraintSet::Link, hkContainerHeapAllocator> links; // Offset: 40
		hkReal maxRestPoseHeightSq; // Offset: 56
		hkBool clampBendStiffness; // Offset: 60
		hkBool useRestPoseConfig; // Offset: 61

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBendStiffnessConstraintSet"; };
		inline std::string GetTranscriptId() override { return "hclBendStiffnessConstraintSet"; };
		inline uint32_t GethkClassHash() override { return 967254011; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "links", "hkArray<hclBendStiffnessConstraintSet::Link, hkContainerHeapAllocator>" },
				{ "maxRestPoseHeightSq", "hkReal" },
				{ "clampBendStiffness", "hkBool" },
				{ "useRestPoseConfig", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
