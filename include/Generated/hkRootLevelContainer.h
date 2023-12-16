#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class hkArray;

	class hkRootLevelContainer : public hkHolderBase {
	public:
		using BaseType = void;
		class NamedVariant : public hkHolderBase {
		public:
			using BaseType = void;
			hkStringPtr name; // Offset: 0
			hkStringPtr className; // Offset: 8
			hkRefVariant variant; // Offset: 16

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hkRootLevelContainer::NamedVariant"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkArray<hkRootLevelContainer::NamedVariant, hkContainerHeapAllocator> namedVariants; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkRootLevelContainer"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
