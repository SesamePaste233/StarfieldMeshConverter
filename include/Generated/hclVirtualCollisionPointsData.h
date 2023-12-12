#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hclVirtualCollisionPointsData : public hkHolderBase {
	public:
		class Block : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class BarycentricDictionaryEntry : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class BarycentricPair : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class EdgeFanSection : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class EdgeFan : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class TriangleFanSection : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class TriangleFan : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class EdgeFanLandscape : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class TriangleFanLandscape : public hkHolderBase {
		public:

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclVirtualCollisionPointsData::Block> blocks; // Offset: 0
		uint16_t numVCPoints; // Offset: 16
		std::vector<uint16_t> landscapeParticlesBlockIndex; // Offset: 24
		uint16_t numLandscapeVCPoints; // Offset: 40
		std::vector<float> edgeBarycentricsDictionary; // Offset: 48
		std::vector<hclVirtualCollisionPointsData::BarycentricDictionaryEntry> edgeDictionaryEntries; // Offset: 64
		std::vector<hclVirtualCollisionPointsData::BarycentricPair> triangleBarycentricsDictionary; // Offset: 80
		std::vector<hclVirtualCollisionPointsData::BarycentricDictionaryEntry> triangleDictionaryEntries; // Offset: 96
		std::vector<hclVirtualCollisionPointsData::EdgeFanSection> edges; // Offset: 112
		std::vector<hclVirtualCollisionPointsData::EdgeFan> edgeFans; // Offset: 128
		std::vector<hclVirtualCollisionPointsData::TriangleFanSection> triangles; // Offset: 144
		std::vector<hclVirtualCollisionPointsData::TriangleFan> triangleFans; // Offset: 160
		std::vector<hclVirtualCollisionPointsData::EdgeFanSection> edgesLandscape; // Offset: 176
		std::vector<hclVirtualCollisionPointsData::EdgeFanLandscape> edgeFansLandscape; // Offset: 192
		std::vector<hclVirtualCollisionPointsData::TriangleFanSection> trianglesLandscape; // Offset: 208
		std::vector<hclVirtualCollisionPointsData::TriangleFanLandscape> triangleFansLandscape; // Offset: 224
		std::vector<uint16_t> edgeFanIndices; // Offset: 240
		std::vector<uint16_t> triangleFanIndices; // Offset: 256
		std::vector<uint16_t> edgeFanIndicesLandscape; // Offset: 272
		std::vector<uint16_t> triangleFanIndicesLandscape; // Offset: 288

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
