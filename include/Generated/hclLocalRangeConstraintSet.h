#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkBool;
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tENUM, typename tSTORAGE>
	class ;

	class hclLocalRangeConstraintSet : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class LocalConstraint : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclLocalRangeConstraintSet::LocalConstraint"; };
			inline std::string GetTranscriptId() override { return "hclLocalRangeConstraintSet::LocalConstraint"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class LocalStiffnessConstraint : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint16 particleIndex; // Offset: 0
			hkUint16 referenceVertex; // Offset: 2
			hkReal maximumDistance; // Offset: 4
			hkReal maxNormalDistance; // Offset: 8
			hkReal minNormalDistance; // Offset: 12
			hkReal stiffness; // Offset: 16

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclLocalRangeConstraintSet::LocalStiffnessConstraint"; };
			inline std::string GetTranscriptId() override { return "hclLocalRangeConstraintSet::LocalStiffnessConstraint"; };
			inline uint32_t GethkClassHash() override { return 2634299948; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "particleIndex", "hkUint16" },
					{ "referenceVertex", "hkUint16" },
					{ "maximumDistance", "hkReal" },
					{ "maxNormalDistance", "hkReal" },
					{ "minNormalDistance", "hkReal" },
					{ "stiffness", "hkReal" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class ShapeType : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclLocalRangeConstraintSet::ShapeType"; };
			inline std::string GetTranscriptId() override { return "hclLocalRangeConstraintSet::ShapeType"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclLocalRangeConstraintSet::LocalConstraint, hkContainerHeapAllocator> localConstraints; // Offset: 40
		hkArray<hclLocalRangeConstraintSet::LocalStiffnessConstraint, hkContainerHeapAllocator> localStiffnessConstraints; // Offset: 56
		hkUint32 referenceMeshBufferIdx; // Offset: 72
		hkReal stiffness; // Offset: 76
		hkEnum<hclLocalRangeConstraintSet::ShapeType, hkUint32> shapeType; // Offset: 80
		hkBool applyNormalComponent; // Offset: 84

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclLocalRangeConstraintSet"; };
		inline std::string GetTranscriptId() override { return "hclLocalRangeConstraintSet"; };
		inline uint32_t GethkClassHash() override { return 3785704016; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "localConstraints", "hkArray<hclLocalRangeConstraintSet::LocalConstraint, hkContainerHeapAllocator>" },
				{ "localStiffnessConstraints", "hkArray<hclLocalRangeConstraintSet::LocalStiffnessConstraint, hkContainerHeapAllocator>" },
				{ "referenceMeshBufferIdx", "hkUint32" },
				{ "stiffness", "hkReal" },
				{ "shapeType", "hkEnum<hclLocalRangeConstraintSet::ShapeType, hkUint32>" },
				{ "applyNormalComponent", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
