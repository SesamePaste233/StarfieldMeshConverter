#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"

namespace hktypes{
	class hkReferencedObject;

	class hkRootLevelContainer : public hkHolderBase {
	public:
		class NamedVariant : public hkHolderBase {
		public:
			std::string name; // Offset: 0
			std::string className; // Offset: 8
			hkReferencedObject* variant; // Offset: 16

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hkRootLevelContainer::NamedVariant> namedVariants; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
