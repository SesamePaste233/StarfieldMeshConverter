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

	class hclClothData : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class Platform : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclClothData::Platform"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		hkStringPtr name; // Offset: 24
		hkArray<T*<hclSimClothData>, hkContainerHeapAllocator> simClothDatas; // Offset: 32
		hkArray<T*<hclBufferDefinition>, hkContainerHeapAllocator> bufferDefinitions; // Offset: 48
		hkArray<T*<hclTransformSetDefinition>, hkContainerHeapAllocator> transformSetDefinitions; // Offset: 64
		hkArray<T*<hclOperator>, hkContainerHeapAllocator> operators; // Offset: 80
		hkArray<T*<hclClothState>, hkContainerHeapAllocator> clothStateDatas; // Offset: 96
		hkArray<T*<hclStateTransition>, hkContainerHeapAllocator> stateTransitions; // Offset: 112
		hkArray<T*<hclAction>, hkContainerHeapAllocator> actions; // Offset: 128
		hkBool generatedAtRuntime; // Offset: 144
		hkEnum<hclClothData::Platform, hkUint32> targetPlatform; // Offset: 148

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclClothData"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
