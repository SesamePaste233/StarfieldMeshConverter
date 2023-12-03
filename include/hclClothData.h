#pragma once
#include "hkTypes.h"

namespace hktypes {
	class hclSimClothData;
	class hkReferencedObject;

	class hclRuntimeConversionInfo : public hkReferencedObject {
	public:
		enum VectorConversion : uint8_t {
			VC_FLOAT4 = 0,
			VC_FLOAT3 = 1,
			VC_BYTE4 = 2,
			VC_SHORT3 = 3,
			VC_HFLOAT3 = 4,
			VC_CUSTOM_A = 20,
			VC_CUSTOM_B = 21,
			VC_CUSTOM_C = 22,
			VC_CUSTOM_D = 23,
			VC_CUSTOM_E = 24,
			VC_NONE = 250,
		};
	};

	class hclBufferLayout : public hkHolderBase {
	public:
		enum TriangleFormat : uint8_t {
			TF_THREE_INT32S = 0,
			TF_THREE_INT16S = 1,
			TF_OTHER = 2,
		};

		enum SlotFlags : uint8_t {
			F_NO_ALIGNED_START = 0,
			SF_16BYTE_ALIGNED_START = 1,
			SF_64BYTE_ALIGNED_START = 3,
		};

		class BufferElement : public hkHolderBase {
		public:
			hclRuntimeConversionInfo::VectorConversion vectorConversion;
			uint8_t vectorSize;	// Offset: 1 Unk: 0
			uint8_t slotId;	// Offset: 2 Unk: 0
			uint8_t slotStart;	// Offset: 3 Unk: 0

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Slot : public hkHolderBase {
		public:
			hclBufferLayout::SlotFlags flags;	// Offset: 0 Unk: 0
			uint8_t stride;	// Offset: 1 Unk: 0

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::array<hclBufferLayout::BufferElement, 4> elementsLayout;	// Offset: 0 Unk: 0
		std::array<hclBufferLayout::Slot, 4> slots;	// Offset: 16 Unk: 0
		uint8_t numSlots;	// Offset: 24 Unk: 0
		hclBufferLayout::TriangleFormat triangleFormat;	// Offset: 25 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclBufferDefinition : public hkReferencedObject {
	public:
		std::string meshName;	// Offset: 24 Unk: 0
		std::string bufferName;	// Offset: 32 Unk: 0
		int type;	// Offset: 40 Unk: 0
		int subType;	// Offset: 44 Unk: 0
		uint32_t numVertices;	// Offset: 48 Unk: 0
		uint32_t numTriangles;	// Offset: 52 Unk: 0
		hclBufferLayout bufferLayout;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclScratchBufferDefinition : public hclBufferDefinition {
	public:
		std::vector<uint16_t> triangleIndices;	// Offset: 88 Unk: 0
		bool storeNormals;	// Offset: 104 Unk: 0
		bool storeTangentsAndBiTangents;	// Offset: 105 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclTransformSetDefinition : public hkReferencedObject {
	public:
		std::string name;	// Offset: 24 Unk: 0
		int type;	// Offset: 32 Unk: 0
		uint32_t numTransforms;	// Offset: 36 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;

	};

	class hclClothData : public hkReferencedObject {
	public:
		std::string name = "Character Bone Deforming Clothing";

		std::vector<hclSimClothData*> simClothDatas;

		std::vector<hclBufferDefinition*> bufferDefinitions;

		std::vector<hclTransformSetDefinition*> transformSetDefinitions;

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}