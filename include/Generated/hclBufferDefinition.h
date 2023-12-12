#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclBufferLayout.h"

namespace hktypes{
	class hkReferencedObject;
	class hclBufferLayout;

	class hclBufferDefinition : public hkReferencedObject {
	public:
		std::string meshName; // Offset: 24
		std::string bufferName; // Offset: 32
		int type; // Offset: 40
		int subType; // Offset: 44
		uint32_t numVertices; // Offset: 48
		uint32_t numTriangles; // Offset: 52
		hclBufferLayout bufferLayout; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
