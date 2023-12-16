#pragma once
#include "hkInclude.h"

#include "Generated\hclConstraintSet.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class hkArray;

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
			static inline std::string GethkClassName() { return "hclBonePlanesConstraintSet::BonePlane"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkArray<hclBonePlanesConstraintSet::BonePlane, hkContainerHeapAllocator> bonePlanes; // Offset: 40
		hkUint32 transformSetIndex; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclBonePlanesConstraintSet"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
