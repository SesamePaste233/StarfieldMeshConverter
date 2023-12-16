#pragma once
#include "hkInclude.h"

#include "Generated\hkBitField.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hkBitField;
	template <typename tT, typename tAllocator>
	class hkArray;

	class hclTransformSetUsage : public hkHolderBase {
	public:
		using BaseType = void;
		class TransformTracker : public hkHolderBase {
		public:
			using BaseType = void;
			hkBitField read; // Offset: 0
			hkBitField readBeforeWrite; // Offset: 24
			hkBitField written; // Offset: 48

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclTransformSetUsage::TransformTracker"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		T[N]<hkUint8, 2> perComponentFlags; // Offset: 0
		hkArray<hclTransformSetUsage::TransformTracker, hkContainerHeapAllocator> perComponentTransformTrackers; // Offset: 8

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclTransformSetUsage"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
