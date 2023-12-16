#pragma once
#include "hkInclude.h"

#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"

namespace hktypes{
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;

	class hclVirtualCollisionPointsData : public hkHolderBase {
	public:
		using BaseType = void;
		class Block : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::Block"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class BarycentricDictionaryEntry : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::BarycentricDictionaryEntry"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class BarycentricPair : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::BarycentricPair"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class EdgeFanSection : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::EdgeFanSection"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class EdgeFan : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::EdgeFan"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class TriangleFanSection : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::TriangleFanSection"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class TriangleFan : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::TriangleFan"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class EdgeFanLandscape : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::EdgeFanLandscape"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class TriangleFanLandscape : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData::TriangleFanLandscape"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
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
		static inline std::string GethkClassName() { return "hclVirtualCollisionPointsData"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
