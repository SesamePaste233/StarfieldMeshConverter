#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclBufferUsage.h"
#include "Generated\hclTransformSetUsage.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hclStateDependencyGraph.h"

namespace hktypes{
	class hkReferencedObject;
	class hclBufferUsage;
	class hclTransformSetUsage;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	class hclStateDependencyGraph;

	class hclClothState : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class BufferAccess : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint32 bufferIndex; // Offset: 0
			hclBufferUsage bufferUsage; // Offset: 4
			hkUint32 shadowBufferIndex; // Offset: 12

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclClothState::BufferAccess"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class TransformSetAccess : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint32 transformSetIndex; // Offset: 0
			hclTransformSetUsage transformSetUsage; // Offset: 8

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclClothState::TransformSetAccess"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkStringPtr name; // Offset: 24
		hkArray<hkUint32, hkContainerHeapAllocator> operators; // Offset: 32
		hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator> usedBuffers; // Offset: 48
		hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator> usedTransformSets; // Offset: 64
		hkArray<hkUint32, hkContainerHeapAllocator> usedSimCloths; // Offset: 80
		T*<hclStateDependencyGraph> dependencyGraph; // Offset: 96

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclClothState"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
