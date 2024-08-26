#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkContainerHeapAllocator;
	class hknpMotionProperties;
	class hknpPhysicsSystemData::bodyCinfoWithAttachment;
	class hknpConstraintCinfo;
	class hknpMaterial;
	class hkRefCountedProperties::Entry;

	template <typename tT, typename tAllocator>
	class hkArray;
	template<>
	class hkArray<hknpMaterial, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hknpMaterial, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 826489242; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "m_data", "T*<void>" },
				{ "m_size", "int" },
				{ "m_capacityAndFlags", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkArray<hknpMotionProperties, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hknpMotionProperties, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 3270913392; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "m_data", "T*<void>" },
				{ "m_size", "int" },
				{ "m_capacityAndFlags", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkArray<hknpPhysicsSystemData::bodyCinfoWithAttachment, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hknpPhysicsSystemData::bodyCinfoWithAttachment, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 901024981; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "m_data", "T*<void>" },
				{ "m_size", "int" },
				{ "m_capacityAndFlags", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkArray<hknpConstraintCinfo, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hknpConstraintCinfo, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "m_data", "T*<void>" },
				{ "m_size", "int" },
				{ "m_capacityAndFlags", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

	template<>
	class hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1457274167; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "m_data", "T*<void>" },
				{ "m_size", "int" },
				{ "m_capacityAndFlags", "int" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
