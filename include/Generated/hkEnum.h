#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclClothData::Platform;
	class hclBufferLayout::TriangleFormat;
	class hclRuntimeConversionInfo::VectorConversion;
	class hclBufferLayout::SlotFlags;

	template <typename tENUM, typename tSTORAGE>
	class hkEnum;
	template<>
	class hkEnum<hclClothData::Platform, hkUint32> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint32 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hclClothData::Platform, hkUint32>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint32" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkEnum<hclBufferLayout::TriangleFormat, hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hclBufferLayout::TriangleFormat, hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkEnum<hclRuntimeConversionInfo::VectorConversion, hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hclRuntimeConversionInfo::VectorConversion, hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkEnum<hclBufferLayout::SlotFlags, hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hclBufferLayout::SlotFlags, hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
