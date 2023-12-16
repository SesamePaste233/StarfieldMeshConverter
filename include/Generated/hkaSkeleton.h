#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"

namespace hktypes{
	class hkReferencedObject;
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

	class hkaSkeleton : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class LocalFrameOnBone : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hkaSkeleton::LocalFrameOnBone"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class Partition : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hkaSkeleton::Partition"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkStringPtr name; // Offset: 24
		hkArray<hkInt16, hkContainerHeapAllocator> parentIndices; // Offset: 32
		hkArray<hkaBone, hkContainerHeapAllocator> bones; // Offset: 48
		hkArray<hkQsTransform, hkContainerHeapAllocator> referencePose; // Offset: 64
		hkArray<hkReal, hkContainerHeapAllocator> referenceFloats; // Offset: 80
		hkArray<hkStringPtr, hkContainerHeapAllocator> floatSlots; // Offset: 96
		hkArray<hkaSkeleton::LocalFrameOnBone, hkContainerHeapAllocator> localFrames; // Offset: 112
		hkArray<hkaSkeleton::Partition, hkContainerHeapAllocator> partitions; // Offset: 128

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hkaSkeleton"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
