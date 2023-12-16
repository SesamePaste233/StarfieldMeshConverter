#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclShape.h"

namespace hktypes{
	class hkReferencedObject;
	class hclShape;

	class hclCollidable : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkTransform transform; // Offset: 32
		hkVector4 linearVelocity; // Offset: 96
		hkVector4 angularVelocity; // Offset: 112
		hkUint64 userData; // Offset: 128
		T*<hclShape> shape; // Offset: 136
		hkStringPtr name; // Offset: 144
		hkReal pinchDetectionRadius; // Offset: 152
		hkInt8 pinchDetectionPriority; // Offset: 156
		hkBool pinchDetectionEnabled; // Offset: 157
		hkBool virtualCollisionPointCollisionEnabled; // Offset: 158
		hkBool enabled; // Offset: 159

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclCollidable"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
