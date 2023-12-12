#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hkaBone.h"
#include "Generated\hkQsTransformf.h"

namespace hktypes{
	class hkReferencedObject;
	class hkaBone;
	class hkQsTransformf;

	class hkaSkeleton : public hkReferencedObject {
	public:
		class LocalFrameOnBone : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Partition : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::string name; // Offset: 24
		std::vector<short> parentIndices; // Offset: 32
		std::vector<hkaBone> bones; // Offset: 48
		std::vector<hkQsTransformf> referencePose; // Offset: 64
		std::vector<float> referenceFloats; // Offset: 80
		std::vector<std::string> floatSlots; // Offset: 96
		std::vector<hkaSkeleton::LocalFrameOnBone> localFrames; // Offset: 112
		std::vector<hkaSkeleton::Partition> partitions; // Offset: 128

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
