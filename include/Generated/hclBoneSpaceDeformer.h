#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkBool;
	class hkVector4f;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hkPackedVector3;

	class hclBoneSpaceDeformer : public hkHolderBase {
	public:
		using BaseType = void;
		class LocalBlockPN : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkVector4, 16> localPosition; // Offset: 0
			T[N]<hkPackedVector3, 16> localNormal; // Offset: 256

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBoneSpaceDeformer::LocalBlockPN"; };
			inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer::LocalBlockPN"; };
			inline uint32_t GethkClassHash() override { return 1262607835; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "localPosition", "T[N]<hkVector4, 16>" },
					{ "localNormal", "T[N]<hkPackedVector3, 16>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class LocalBlockUnpackedPN : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBoneSpaceDeformer::LocalBlockUnpackedPN"; };
			inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer::LocalBlockUnpackedPN"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class FourBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBoneSpaceDeformer::FourBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer::FourBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class ThreeBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBoneSpaceDeformer::ThreeBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer::ThreeBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class TwoBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkUint16, 8> vertexIndices; // Offset: 0
			T[N]<hkUint16, 16> boneIndices; // Offset: 16

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBoneSpaceDeformer::TwoBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer::TwoBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 2640620584; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vertexIndices", "T[N]<hkUint16, 8>" },
					{ "boneIndices", "T[N]<hkUint16, 16>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class OneBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkUint16, 16> vertexIndices; // Offset: 0
			T[N]<hkUint16, 16> boneIndices; // Offset: 32

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBoneSpaceDeformer::OneBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer::OneBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 2248773505; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vertexIndices", "T[N]<hkUint16, 16>" },
					{ "boneIndices", "T[N]<hkUint16, 16>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclBoneSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator> fourBlendEntries; // Offset: 0
		hkArray<hclBoneSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator> threeBlendEntries; // Offset: 16
		hkArray<hclBoneSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator> twoBlendEntries; // Offset: 32
		hkArray<hclBoneSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator> oneBlendEntries; // Offset: 48
		hkArray<hkUint8, hkContainerHeapAllocator> controlBytes; // Offset: 64
		hkUint16 startVertexIndex; // Offset: 80
		hkUint16 endVertexIndex; // Offset: 82
		hkBool partialWrite; // Offset: 84

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBoneSpaceDeformer"; };
		inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "fourBlendEntries", "hkArray<hclBoneSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "threeBlendEntries", "hkArray<hclBoneSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "twoBlendEntries", "hkArray<hclBoneSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "oneBlendEntries", "hkArray<hclBoneSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "controlBytes", "hkArray<hkUint8, hkContainerHeapAllocator>" },
				{ "startVertexIndex", "hkUint16" },
				{ "endVertexIndex", "hkUint16" },
				{ "partialWrite", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
