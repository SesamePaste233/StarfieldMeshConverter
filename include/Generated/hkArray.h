#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hknpMaterial;
	class hkContainerHeapAllocator;
	class hknpMotionProperties;
	class hknpPhysicsSystemData::bodyCinfoWithAttachment;
	class hknpConstraintCinfo;
	class hknpShapeInstance;
	class hkcdStaticMeshTree::Connectivity::SectionHeader;
	template <typename tTYPE, typename vINVALID_VALUE>
	class ;
	class hkRefCountedProperties::Entry;
	class hkcdSimdTree::Node;
	class hkcdStaticMeshTree::Section;
	class hkcdStaticMeshTree::Primitive;
	class hkcdCompressedAabbCodecs::Aabb5BytesCodec;
	class hkcdDefaultStaticMeshTree::PrimitiveDataRun;
	class hkcdCompressedAabbCodecs::Aabb4BytesCodec;
	class hknpBSMaterial;

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
	class hkArray<hknpShapeInstance, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hknpShapeInstance, hkContainerHeapAllocator>"; };
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
	class hkArray<hkUint32, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkUint32, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 849507687; };
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

	template<>
	class hkArray<hkcdSimdTree::Node, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkcdSimdTree::Node, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1929334989; };
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
	class hkArray<hkcdStaticMeshTree::Connectivity::SectionHeader, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkcdStaticMeshTree::Connectivity::SectionHeader, hkContainerHeapAllocator>"; };
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
	class hkArray<hkUint8, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkUint8, hkContainerHeapAllocator>"; };
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
	class hkArray<hkHandle<hkUint32, 4294967295>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkHandle<hkUint32, 4294967295>, hkContainerHeapAllocator>"; };
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
	class hkArray<unsigned int, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<unsigned int, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 3719940695; };
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
	class hkArray<unsigned long long, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<unsigned long long, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 635902075; };
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
	class hkArray<hkcdDefaultStaticMeshTree::PrimitiveDataRun, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkcdDefaultStaticMeshTree::PrimitiveDataRun, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 82878480; };
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
	class hkArray<hkcdStaticMeshTree::Section, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkcdStaticMeshTree::Section, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 624237927; };
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
	class hkArray<hkcdStaticMeshTree::Primitive, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkcdStaticMeshTree::Primitive, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 741138255; };
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
	class hkArray<hkUint16, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkUint16, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2673501953; };
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
	class hkArray<hkcdCompressedAabbCodecs::Aabb5BytesCodec, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkcdCompressedAabbCodecs::Aabb5BytesCodec, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 896082027; };
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
	class hkArray<hkcdCompressedAabbCodecs::Aabb4BytesCodec, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkcdCompressedAabbCodecs::Aabb4BytesCodec, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1688681074; };
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
	class hkArray<hknpBSMaterial, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hknpBSMaterial, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1934436793; };
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
