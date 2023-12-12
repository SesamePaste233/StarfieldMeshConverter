#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclShape.h"

namespace hktypes{
	class hkReferencedObject;
	class hclShape;

	class hclCollidable : public hkReferencedObject {
	public:
		hkMatrix4Holder transform; // Offset: 32
		hkVector4Holder linearVelocity; // Offset: 96
		hkVector4Holder angularVelocity; // Offset: 112
		uint64_t userData; // Offset: 128
		hclShape* shape; // Offset: 136
		std::string name; // Offset: 144
		float pinchDetectionRadius; // Offset: 152
		int8_t pinchDetectionPriority; // Offset: 156
		bool pinchDetectionEnabled; // Offset: 157
		bool virtualCollisionPointCollisionEnabled; // Offset: 158
		bool enabled; // Offset: 159

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
