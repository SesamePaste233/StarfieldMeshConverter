#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tENUM, typename tSTORAGE>
	class ;
	template <typename tENUM, typename tSTORAGE>
	class ;
	template <typename tENUM, typename tSTORAGE>
	class ;

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
			inline std::string GethkClassName() override { return "hclBufferLayout::BufferElement"; };
			inline std::string GetTranscriptId() override { return "hclBufferLayout::BufferElement"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vectorConversion", "hkEnum<hclRuntimeConversionInfo::VectorConversion, hkUint8>" },
					{ "vectorSize", "hkUint8" },
					{ "slotId", "hkUint8" },
					{ "slotStart", "hkUint8" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class Slot : public hkHolderBase {
		public:
			using BaseType = void;
			hkEnum<hclBufferLayout::SlotFlags, hkUint8> flags; // Offset: 0
			hkUint8 stride; // Offset: 1

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBufferLayout::Slot"; };
			inline std::string GetTranscriptId() override { return "hclBufferLayout::Slot"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "flags", "hkEnum<hclBufferLayout::SlotFlags, hkUint8>" },
					{ "stride", "hkUint8" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class TriangleFormat : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBufferLayout::TriangleFormat"; };
			inline std::string GetTranscriptId() override { return "hclBufferLayout::TriangleFormat"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class SlotFlags : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBufferLayout::SlotFlags"; };
			inline std::string GetTranscriptId() override { return "hclBufferLayout::SlotFlags"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		T[N]<hclBufferLayout::BufferElement, 4> elementsLayout; // Offset: 0
		T[N]<hclBufferLayout::Slot, 4> slots; // Offset: 16
		hkUint8 numSlots; // Offset: 24
		hkEnum<hclBufferLayout::TriangleFormat, hkUint8> triangleFormat; // Offset: 25

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBufferLayout"; };
		inline std::string GetTranscriptId() override { return "hclBufferLayout"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "elementsLayout", "T[N]<hclBufferLayout::BufferElement, 4>" },
				{ "slots", "T[N]<hclBufferLayout::Slot, 4>" },
				{ "numSlots", "hkUint8" },
				{ "triangleFormat", "hkEnum<hclBufferLayout::TriangleFormat, hkUint8>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
