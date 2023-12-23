#pragma once
#include "hkInclude.h"


namespace hktypes{
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
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclVirtualCollisionPointsData : public hkHolderBase {
	public:
		using BaseType = void;
		class Block : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::Block"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::Block"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class BarycentricDictionaryEntry : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::BarycentricDictionaryEntry"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::BarycentricDictionaryEntry"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class BarycentricPair : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::BarycentricPair"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::BarycentricPair"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class EdgeFanSection : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::EdgeFanSection"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::EdgeFanSection"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class EdgeFan : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::EdgeFan"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::EdgeFan"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class TriangleFanSection : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::TriangleFanSection"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::TriangleFanSection"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class TriangleFan : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::TriangleFan"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::TriangleFan"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class EdgeFanLandscape : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::EdgeFanLandscape"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::EdgeFanLandscape"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class TriangleFanLandscape : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData::TriangleFanLandscape"; };
			inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData::TriangleFanLandscape"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclVirtualCollisionPointsData::Block, hkContainerHeapAllocator> blocks; // Offset: 0
		hkUint16 numVCPoints; // Offset: 16
		hkArray<hkUint16, hkContainerHeapAllocator> landscapeParticlesBlockIndex; // Offset: 24
		hkUint16 numLandscapeVCPoints; // Offset: 40
		hkArray<hkReal, hkContainerHeapAllocator> edgeBarycentricsDictionary; // Offset: 48
		hkArray<hclVirtualCollisionPointsData::BarycentricDictionaryEntry, hkContainerHeapAllocator> edgeDictionaryEntries; // Offset: 64
		hkArray<hclVirtualCollisionPointsData::BarycentricPair, hkContainerHeapAllocator> triangleBarycentricsDictionary; // Offset: 80
		hkArray<hclVirtualCollisionPointsData::BarycentricDictionaryEntry, hkContainerHeapAllocator> triangleDictionaryEntries; // Offset: 96
		hkArray<hclVirtualCollisionPointsData::EdgeFanSection, hkContainerHeapAllocator> edges; // Offset: 112
		hkArray<hclVirtualCollisionPointsData::EdgeFan, hkContainerHeapAllocator> edgeFans; // Offset: 128
		hkArray<hclVirtualCollisionPointsData::TriangleFanSection, hkContainerHeapAllocator> triangles; // Offset: 144
		hkArray<hclVirtualCollisionPointsData::TriangleFan, hkContainerHeapAllocator> triangleFans; // Offset: 160
		hkArray<hclVirtualCollisionPointsData::EdgeFanSection, hkContainerHeapAllocator> edgesLandscape; // Offset: 176
		hkArray<hclVirtualCollisionPointsData::EdgeFanLandscape, hkContainerHeapAllocator> edgeFansLandscape; // Offset: 192
		hkArray<hclVirtualCollisionPointsData::TriangleFanSection, hkContainerHeapAllocator> trianglesLandscape; // Offset: 208
		hkArray<hclVirtualCollisionPointsData::TriangleFanLandscape, hkContainerHeapAllocator> triangleFansLandscape; // Offset: 224
		hkArray<hkUint16, hkContainerHeapAllocator> edgeFanIndices; // Offset: 240
		hkArray<hkUint16, hkContainerHeapAllocator> triangleFanIndices; // Offset: 256
		hkArray<hkUint16, hkContainerHeapAllocator> edgeFanIndicesLandscape; // Offset: 272
		hkArray<hkUint16, hkContainerHeapAllocator> triangleFanIndicesLandscape; // Offset: 288

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclVirtualCollisionPointsData"; };
		inline std::string GetTranscriptId() override { return "hclVirtualCollisionPointsData"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "blocks", "hkArray<hclVirtualCollisionPointsData::Block, hkContainerHeapAllocator>" },
				{ "numVCPoints", "hkUint16" },
				{ "landscapeParticlesBlockIndex", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "numLandscapeVCPoints", "hkUint16" },
				{ "edgeBarycentricsDictionary", "hkArray<hkReal, hkContainerHeapAllocator>" },
				{ "edgeDictionaryEntries", "hkArray<hclVirtualCollisionPointsData::BarycentricDictionaryEntry, hkContainerHeapAllocator>" },
				{ "triangleBarycentricsDictionary", "hkArray<hclVirtualCollisionPointsData::BarycentricPair, hkContainerHeapAllocator>" },
				{ "triangleDictionaryEntries", "hkArray<hclVirtualCollisionPointsData::BarycentricDictionaryEntry, hkContainerHeapAllocator>" },
				{ "edges", "hkArray<hclVirtualCollisionPointsData::EdgeFanSection, hkContainerHeapAllocator>" },
				{ "edgeFans", "hkArray<hclVirtualCollisionPointsData::EdgeFan, hkContainerHeapAllocator>" },
				{ "triangles", "hkArray<hclVirtualCollisionPointsData::TriangleFanSection, hkContainerHeapAllocator>" },
				{ "triangleFans", "hkArray<hclVirtualCollisionPointsData::TriangleFan, hkContainerHeapAllocator>" },
				{ "edgesLandscape", "hkArray<hclVirtualCollisionPointsData::EdgeFanSection, hkContainerHeapAllocator>" },
				{ "edgeFansLandscape", "hkArray<hclVirtualCollisionPointsData::EdgeFanLandscape, hkContainerHeapAllocator>" },
				{ "trianglesLandscape", "hkArray<hclVirtualCollisionPointsData::TriangleFanSection, hkContainerHeapAllocator>" },
				{ "triangleFansLandscape", "hkArray<hclVirtualCollisionPointsData::TriangleFanLandscape, hkContainerHeapAllocator>" },
				{ "edgeFanIndices", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "triangleFanIndices", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "edgeFanIndicesLandscape", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "triangleFanIndicesLandscape", "hkArray<hkUint16, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
