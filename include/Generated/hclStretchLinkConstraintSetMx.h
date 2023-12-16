#pragma once
#include "hkInclude.h"

#include "Generated\hclConstraintSet.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;

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
			static inline std::string GethkClassName() { return "hclStretchLinkConstraintSetMx::Batch"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class Single : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclStretchLinkConstraintSetMx::Single"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkArray<hclStretchLinkConstraintSetMx::Batch, hkContainerHeapAllocator> batches; // Offset: 40
		hkArray<hclStretchLinkConstraintSetMx::Single, hkContainerHeapAllocator> singles; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclStretchLinkConstraintSetMx"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
