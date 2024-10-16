#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkBool;
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
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hkPackedVector3;

	class hclObjectSpaceDeformer : public hkHolderBase {
	public:
		using BaseType = void;
		class LocalBlockPN : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkPackedVector3, 16> localPosition; // Offset: 0
			T[N]<hkPackedVector3, 16> localNormal; // Offset: 128

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::LocalBlockPN"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::LocalBlockPN"; };
			inline uint32_t GethkClassHash() override { return 934674811; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "localPosition", "T[N]<hkPackedVector3, 16>" },
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
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::LocalBlockUnpackedPN"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::LocalBlockUnpackedPN"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class EightBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::EightBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::EightBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class SevenBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::SevenBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::SevenBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class SixBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::SixBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::SixBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class FiveBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::FiveBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::FiveBlendEntryBlock"; };
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
			T[N]<hkUint16, 16> vertexIndices; // Offset: 0
			T[N]<hkUint16, 64> boneIndices; // Offset: 32
			T[N]<hkUint8, 64> boneWeights; // Offset: 160

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::FourBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::FourBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 94201665; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vertexIndices", "T[N]<hkUint16, 16>" },
					{ "boneIndices", "T[N]<hkUint16, 64>" },
					{ "boneWeights", "T[N]<hkUint8, 64>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class ThreeBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkUint16, 16> vertexIndices; // Offset: 0
			T[N]<hkUint16, 48> boneIndices; // Offset: 32
			T[N]<hkUint8, 48> boneWeights; // Offset: 128

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::ThreeBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::ThreeBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 3839925180; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vertexIndices", "T[N]<hkUint16, 16>" },
					{ "boneIndices", "T[N]<hkUint16, 48>" },
					{ "boneWeights", "T[N]<hkUint8, 48>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class TwoBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkUint16, 16> vertexIndices; // Offset: 0
			T[N]<hkUint16, 32> boneIndices; // Offset: 32
			T[N]<hkUint8, 32> boneWeights; // Offset: 96

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::TwoBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::TwoBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 2865152819; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vertexIndices", "T[N]<hkUint16, 16>" },
					{ "boneIndices", "T[N]<hkUint16, 32>" },
					{ "boneWeights", "T[N]<hkUint8, 32>" },
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
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::OneBlendEntryBlock"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::OneBlendEntryBlock"; };
			inline uint32_t GethkClassHash() override { return 3517680068; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vertexIndices", "T[N]<hkUint16, 16>" },
					{ "boneIndices", "T[N]<hkUint16, 16>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclObjectSpaceDeformer::EightBlendEntryBlock, hkContainerHeapAllocator> eightBlendEntries; // Offset: 0
		hkArray<hclObjectSpaceDeformer::SevenBlendEntryBlock, hkContainerHeapAllocator> sevenBlendEntries; // Offset: 16
		hkArray<hclObjectSpaceDeformer::SixBlendEntryBlock, hkContainerHeapAllocator> sixBlendEntries; // Offset: 32
		hkArray<hclObjectSpaceDeformer::FiveBlendEntryBlock, hkContainerHeapAllocator> fiveBlendEntries; // Offset: 48
		hkArray<hclObjectSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator> fourBlendEntries; // Offset: 64
		hkArray<hclObjectSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator> threeBlendEntries; // Offset: 80
		hkArray<hclObjectSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator> twoBlendEntries; // Offset: 96
		hkArray<hclObjectSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator> oneBlendEntries; // Offset: 112
		hkArray<hkUint8, hkContainerHeapAllocator> controlBytes; // Offset: 128
		hkUint16 startVertexIndex; // Offset: 144
		hkUint16 endVertexIndex; // Offset: 146
		hkBool partialWrite; // Offset: 148

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclObjectSpaceDeformer"; };
		inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "eightBlendEntries", "hkArray<hclObjectSpaceDeformer::EightBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "sevenBlendEntries", "hkArray<hclObjectSpaceDeformer::SevenBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "sixBlendEntries", "hkArray<hclObjectSpaceDeformer::SixBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "fiveBlendEntries", "hkArray<hclObjectSpaceDeformer::FiveBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "fourBlendEntries", "hkArray<hclObjectSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "threeBlendEntries", "hkArray<hclObjectSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "twoBlendEntries", "hkArray<hclObjectSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "oneBlendEntries", "hkArray<hclObjectSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "controlBytes", "hkArray<hkUint8, hkContainerHeapAllocator>" },
				{ "startVertexIndex", "hkUint16" },
				{ "endVertexIndex", "hkUint16" },
				{ "partialWrite", "hkBool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
