#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hknpCollisionFlags::Enum;
	class hknpCollisionControl::Enum;
	class hknpShape::FlagsEnum;

	template <typename tBITS, typename tSTORAGE>
	class hkFlags;
	template<>
	class hkFlags<hknpCollisionFlags::Enum, int> : public hkHolderBase {
	public:
		using BaseType = void;
		int storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkFlags"; };
		inline std::string GetTranscriptId() override { return "hkFlags<hknpCollisionFlags::Enum, int>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkFlags<hknpCollisionControl::Enum, unsigned short> : public hkHolderBase {
	public:
		using BaseType = void;
		unsigned short storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkFlags"; };
		inline std::string GetTranscriptId() override { return "hkFlags<hknpCollisionControl::Enum, unsigned short>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "unsigned short" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkFlags<hknpShape::FlagsEnum, hkUint16> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint16 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkFlags"; };
		inline std::string GetTranscriptId() override { return "hkFlags<hknpShape::FlagsEnum, hkUint16>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint16" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
