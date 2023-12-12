#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hclBufferLayout : public hkHolderBase {
	public:
		class BufferElement : public hkHolderBase {
		public:
			hclRuntimeConversionInfo::VectorConversion vectorConversion; // Offset: 0
			uint8_t vectorSize; // Offset: 1
			uint8_t slotId; // Offset: 2
			uint8_t slotStart; // Offset: 3

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Slot : public hkHolderBase {
		public:
			hclBufferLayout::SlotFlags flags; // Offset: 0
			uint8_t stride; // Offset: 1

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class TriangleFormat : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class SlotFlags : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::array<hclBufferLayout::BufferElement, 4> elementsLayout; // Offset: 0
		std::array<hclBufferLayout::Slot, 4> slots; // Offset: 16
		uint8_t numSlots; // Offset: 24
		hclBufferLayout::TriangleFormat triangleFormat; // Offset: 25

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
