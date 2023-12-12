#pragma once
#include "hkInclude.h"

#include "Generated\hkPackedVector3.h"

namespace hktypes{
	class hkPackedVector3;

	class hclObjectSpaceDeformer : public hkHolderBase {
	public:
		class LocalBlockPN : public hkHolderBase {
		public:
			std::array<hkPackedVector3, 16> localPosition; // Offset: 0
			std::array<hkPackedVector3, 16> localNormal; // Offset: 128

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class LocalBlockUnpackedPN : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class EightBlendEntryBlock : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class SevenBlendEntryBlock : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class SixBlendEntryBlock : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class FiveBlendEntryBlock : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class FourBlendEntryBlock : public hkHolderBase {
		public:
			std::array<uint16_t, 16> vertexIndices; // Offset: 0
			std::array<uint16_t, 64> boneIndices; // Offset: 32
			std::array<uint8_t, 64> boneWeights; // Offset: 160

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class ThreeBlendEntryBlock : public hkHolderBase {
		public:
			std::array<uint16_t, 16> vertexIndices; // Offset: 0
			std::array<uint16_t, 48> boneIndices; // Offset: 32
			std::array<uint8_t, 48> boneWeights; // Offset: 128

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class TwoBlendEntryBlock : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class OneBlendEntryBlock : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclObjectSpaceDeformer::EightBlendEntryBlock> eightBlendEntries; // Offset: 0
		std::vector<hclObjectSpaceDeformer::SevenBlendEntryBlock> sevenBlendEntries; // Offset: 16
		std::vector<hclObjectSpaceDeformer::SixBlendEntryBlock> sixBlendEntries; // Offset: 32
		std::vector<hclObjectSpaceDeformer::FiveBlendEntryBlock> fiveBlendEntries; // Offset: 48
		std::vector<hclObjectSpaceDeformer::FourBlendEntryBlock> fourBlendEntries; // Offset: 64
		std::vector<hclObjectSpaceDeformer::ThreeBlendEntryBlock> threeBlendEntries; // Offset: 80
		std::vector<hclObjectSpaceDeformer::TwoBlendEntryBlock> twoBlendEntries; // Offset: 96
		std::vector<hclObjectSpaceDeformer::OneBlendEntryBlock> oneBlendEntries; // Offset: 112
		std::vector<uint8_t> controlBytes; // Offset: 128
		uint16_t startVertexIndex; // Offset: 144
		uint16_t endVertexIndex; // Offset: 146
		bool partialWrite; // Offset: 148

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
