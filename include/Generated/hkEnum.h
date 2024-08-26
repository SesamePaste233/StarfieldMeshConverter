#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hknpMaterial::CombinePolicy;
	class hknpMaterial::TriggerType;
	class hknpMaterial::MassChangerCategory;
	class hknpShapeType::Enum;
	class hknpCollisionDispatchType::Enum;

	template <typename tENUM, typename tSTORAGE>
	class hkEnum;
	template<>
	class hkEnum<hknpMaterial::TriggerType, hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hknpMaterial::TriggerType, hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkEnum<hknpMaterial::CombinePolicy, hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hknpMaterial::CombinePolicy, hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkEnum<hknpMaterial::MassChangerCategory, hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hknpMaterial::MassChangerCategory, hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkEnum<hknpShapeType::Enum, hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hknpShapeType::Enum, hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkEnum<hknpCollisionDispatchType::Enum, hkUint8> : public hkHolderBase {
	public:
		using BaseType = void;
		hkUint8 storage; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkEnum"; };
		inline std::string GetTranscriptId() override { return "hkEnum<hknpCollisionDispatchType::Enum, hkUint8>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "storage", "hkUint8" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
