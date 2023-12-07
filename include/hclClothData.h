#pragma once
#include "hkInclude.h"
#include "hclSimClothData.h"
#include "hclOperator.h"
#include "hclClothState.h"

namespace hktypes {
	class hclSimClothData;
	class hclOperator;
	class hclClothState;

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
		enum Platform : uint32_t
		{
			HCL_PLATFORM_INVALID = 0,
			HCL_PLATFORM_WIN32 = 1,
			HCL_PLATFORM_X64 = 2,
			HCL_PLATFORM_MACPPC = 4,
			HCL_PLATFORM_IOS = 8,
			HCL_PLATFORM_MAC386 = 16,
			HCL_PLATFORM_PS3 = 32,
			HCL_PLATFORM_XBOX360 = 64,
			HCL_PLATFORM_WII = 128,
			HCL_PLATFORM_LRB = 256,
			HCL_PLATFORM_LINUX = 512,
			HCL_PLATFORM_PSVITA = 1024,
			HCL_PLATFORM_ANDROID = 2048,
			HCL_PLATFORM_CTR = 4096,
			HCL_PLATFORM_WIIU = 8192,
			HCL_PLATFORM_PS4 = 16384,
			HCL_PLATFORM_XBOXONE = 32768,
			HCL_PLATFORM_MAC64 = 65536,
			HCL_PLATFORM_NX = 131072,
			HCL_PLATFORM_GDK = 262144,
			HCL_PLATFORM_COOKER = 524288
		};

		std::string name = "Character Bone Deforming Clothing";
		std::vector<hclSimClothData*> simClothDatas;
		std::vector<hclBufferDefinition*> bufferDefinitions;
		std::vector<hclTransformSetDefinition*> transformSetDefinitions;
		std::vector<hclOperator*> operators;
		std::vector<hclClothState*> clothStateDatas;
		//std::vector<hclStateTransition*> stateTransitions;	// Offset: 112 Unk: 0
		//std::vector<hclAction*> actions;	// Offset: 128 Unk: 0
		bool generatedAtRuntime;	// Offset: 144 Unk: 0
		hclClothData::Platform targetPlatform;	// Offset: 148 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}