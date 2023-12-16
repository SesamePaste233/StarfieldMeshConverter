#pragma once
#include "hkInclude.h"


namespace hktypes{

	class hclBufferLayout : public hkHolderBase {
	public:
		using BaseType = void;
		class BufferElement : public hkHolderBase {
		public:
			using BaseType = void;
			hkEnum<hclRuntimeConversionInfo::VectorConversion, hkUint8> vectorConversion; // Offset: 0
			hkUint8 vectorSize; // Offset: 1
			hkUint8 slotId; // Offset: 2
			hkUint8 slotStart; // Offset: 3

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclBufferLayout::BufferElement"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class Slot : public hkHolderBase {
		public:
			using BaseType = void;
			hkEnum<hclBufferLayout::SlotFlags, hkUint8> flags; // Offset: 0
			hkUint8 stride; // Offset: 1

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclBufferLayout::Slot"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class TriangleFormat : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclBufferLayout::TriangleFormat"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class SlotFlags : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclBufferLayout::SlotFlags"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		T[N]<hclBufferLayout::BufferElement, 4> elementsLayout; // Offset: 0
		T[N]<hclBufferLayout::Slot, 4> slots; // Offset: 16
		hkUint8 numSlots; // Offset: 24
		hkEnum<hclBufferLayout::TriangleFormat, hkUint8> triangleFormat; // Offset: 25

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		static inline std::string GethkClassName() { return "hclBufferLayout"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
