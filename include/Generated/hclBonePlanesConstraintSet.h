#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclConstraintSet;
	class hkVector4;
	template <typename tT, typename tAllocator>
	class ;

	class hclBonePlanesConstraintSet : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class BonePlane : public hkHolderBase {
		public:
			using BaseType = void;
			hkVector4 planeEquationBone; // Offset: 0
			hkUint16 particleIndex; // Offset: 16
			hkUint16 transformIndex; // Offset: 18
			hkReal stiffness; // Offset: 20

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBonePlanesConstraintSet::BonePlane"; };
			inline std::string GetTranscriptId() override { return "hclBonePlanesConstraintSet::BonePlane"; };
			inline uint32_t GethkClassHash() override { return 3326918113; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "planeEquationBone", "hkVector4" },
					{ "particleIndex", "hkUint16" },
					{ "transformIndex", "hkUint16" },
					{ "stiffness", "hkReal" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclBonePlanesConstraintSet::BonePlane, hkContainerHeapAllocator> bonePlanes; // Offset: 40
		hkUint32 transformSetIndex; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBonePlanesConstraintSet"; };
		inline std::string GetTranscriptId() override { return "hclBonePlanesConstraintSet"; };
		inline uint32_t GethkClassHash() override { return 2481738222; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "bonePlanes", "hkArray<hclBonePlanesConstraintSet::BonePlane, hkContainerHeapAllocator>" },
				{ "transformSetIndex", "hkUint32" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
