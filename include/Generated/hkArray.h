#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkRootLevelContainer::NamedVariant;
	class hkContainerHeapAllocator;
	class hkStringPtr;
	class hkBool;
	class hkaSkeleton::LocalFrameOnBone;
	class hkaSkeleton::Partition;
	class hkaBone;
	class hkQsTransform;
	class hclSimClothData::ParticleData;
	class hkVector4;
	class hkMatrix4;
	class hclSimClothData::CollidablePinchingData;
	class hclVirtualCollisionPointsData::Block;
	class hclVirtualCollisionPointsData::BarycentricDictionaryEntry;
	class hclVirtualCollisionPointsData::BarycentricPair;
	class hclVirtualCollisionPointsData::EdgeFanSection;
	class hclVirtualCollisionPointsData::EdgeFanLandscape;
	class hclVirtualCollisionPointsData::TriangleFanLandscape;
	class hclVirtualCollisionPointsData::EdgeFan;
	class hclVirtualCollisionPointsData::TriangleFanSection;
	class hclVirtualCollisionPointsData::TriangleFan;
	class hclBoneSpaceDeformer::LocalBlockUnpackedPN;
	class hclBoneSpaceDeformer::LocalBlockPN;
	class hclTransformSetUsage::TransformTracker;
	class hclBoneSpaceDeformer::FourBlendEntryBlock;
	class hclClothState::TransformSetAccess;
	class hclBoneSpaceDeformer::TwoBlendEntryBlock;
	class hclBoneSpaceDeformer::ThreeBlendEntryBlock;
	class hclBoneSpaceDeformer::OneBlendEntryBlock;
	class hclClothState::BufferAccess;
	class hclMoveParticlesOperator::VertexParticlePair;
	class hclSimulateOperator::Config;
	class hclSimpleMeshBoneDeformOperator::TriangleBonePair;
	class hclStandardLinkConstraintSetMx::Single;
	class hclStretchLinkConstraintSetMx::Batch;
	class hclVolumeConstraint::FrameData;
	class hclVolumeConstraint::ApplyData;
	class hclStateDependencyGraph::Branch;
	class hclStandardLinkConstraintSetMx::Batch;
	class hclStretchLinkConstraintSetMx::Single;
	template <typename tT, typename tAllocator>
	class ;

	template <typename tT, typename tAllocator>
	class hkArray;
	template<>
	class hkArray<hkRootLevelContainer::NamedVariant, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkRootLevelContainer::NamedVariant, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 4795907; };
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
	class hkArray<T*<hclSimClothData>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclSimClothData>, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1695698019; };
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
	class hkArray<T*<hclBufferDefinition>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclBufferDefinition>, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 555785177; };
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
	class hkArray<T*<hclTransformSetDefinition>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclTransformSetDefinition>, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 3207022210; };
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
	class hkArray<T*<hclOperator>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclOperator>, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2440619171; };
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
	class hkArray<T*<hclClothState>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclClothState>, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 4218927663; };
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
	class hkArray<T*<hclStateTransition>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclStateTransition>, hkContainerHeapAllocator>"; };
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
	class hkArray<T*<hclAction>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclAction>, hkContainerHeapAllocator>"; };
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
	class hkArray<hkInt16, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkInt16, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 98675557; };
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
	class hkArray<hkaBone, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkaBone, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1104707901; };
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
	class hkArray<hkQsTransform, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkQsTransform, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1748241175; };
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
	class hkArray<hkReal, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkReal, hkContainerHeapAllocator>"; };
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
	class hkArray<hkStringPtr, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkStringPtr, hkContainerHeapAllocator>"; };
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
	class hkArray<hkaSkeleton::LocalFrameOnBone, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkaSkeleton::LocalFrameOnBone, hkContainerHeapAllocator>"; };
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
	class hkArray<hkaSkeleton::Partition, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkaSkeleton::Partition, hkContainerHeapAllocator>"; };
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
	class hkArray<hclSimClothData::ParticleData, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclSimClothData::ParticleData, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1696446906; };
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
	class hkArray<T*<hclSimClothPose>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclSimClothPose>, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1590729342; };
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
	class hkArray<T*<hclConstraintSet>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclConstraintSet>, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 314306038; };
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
	class hkArray<T*<hclCollidable>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<T*<hclCollidable>, hkContainerHeapAllocator>"; };
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
		inline uint32_t GethkClassHash() override { return 3424536584; };
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
	class hkArray<hkBool, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkBool, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1890273061; };
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
	class hkArray<hclSimClothData::CollidablePinchingData, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclSimClothData::CollidablePinchingData, hkContainerHeapAllocator>"; };
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
	class hkArray<hkMatrix4, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkMatrix4, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1515717676; };
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
	class hkArray<hclVirtualCollisionPointsData::Block, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::Block, hkContainerHeapAllocator>"; };
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
	class hkArray<hclVirtualCollisionPointsData::BarycentricDictionaryEntry, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::BarycentricDictionaryEntry, hkContainerHeapAllocator>"; };
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
	class hkArray<hclVirtualCollisionPointsData::BarycentricPair, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::BarycentricPair, hkContainerHeapAllocator>"; };
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
	class hkArray<hclVirtualCollisionPointsData::EdgeFanSection, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::EdgeFanSection, hkContainerHeapAllocator>"; };
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
	class hkArray<hclVirtualCollisionPointsData::EdgeFan, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::EdgeFan, hkContainerHeapAllocator>"; };
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
	class hkArray<hclVirtualCollisionPointsData::TriangleFanSection, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::TriangleFanSection, hkContainerHeapAllocator>"; };
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
	class hkArray<hclVirtualCollisionPointsData::TriangleFan, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::TriangleFan, hkContainerHeapAllocator>"; };
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
	class hkArray<hclVirtualCollisionPointsData::EdgeFanLandscape, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::EdgeFanLandscape, hkContainerHeapAllocator>"; };
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
	class hkArray<hclVirtualCollisionPointsData::TriangleFanLandscape, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVirtualCollisionPointsData::TriangleFanLandscape, hkContainerHeapAllocator>"; };
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
	class hkArray<hclBoneSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclBoneSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1350568881; };
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
	class hkArray<hclBoneSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclBoneSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator>"; };
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
	class hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1317352235; };
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
	class hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2942566491; };
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
	class hkArray<hclBoneSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclBoneSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator>"; };
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
	class hkArray<hclBoneSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclBoneSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator>"; };
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
	class hkArray<hclBoneSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclBoneSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator>"; };
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
	class hkArray<hclBoneSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclBoneSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2657341099; };
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
	class hkArray<hclTransformSetUsage::TransformTracker, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclTransformSetUsage::TransformTracker, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 254929971; };
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
	class hkArray<hclMoveParticlesOperator::VertexParticlePair, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclMoveParticlesOperator::VertexParticlePair, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1922890526; };
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
	class hkArray<hclSimulateOperator::Config, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclSimulateOperator::Config, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 963867960; };
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
	class hkArray<hkInt32, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkInt32, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2820258051; };
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
	class hkArray<hclSimpleMeshBoneDeformOperator::TriangleBonePair, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclSimpleMeshBoneDeformOperator::TriangleBonePair, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 4041920656; };
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
	class hkArray<hkVector4, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkVector4, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 3786493259; };
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
	class hkArray<hclStandardLinkConstraintSetMx::Batch, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclStandardLinkConstraintSetMx::Batch, hkContainerHeapAllocator>"; };
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
	class hkArray<hclStandardLinkConstraintSetMx::Single, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclStandardLinkConstraintSetMx::Single, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 976442399; };
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
	class hkArray<hclStretchLinkConstraintSetMx::Batch, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclStretchLinkConstraintSetMx::Batch, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 1722526888; };
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
	class hkArray<hclStretchLinkConstraintSetMx::Single, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclStretchLinkConstraintSetMx::Single, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2747523813; };
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
	class hkArray<hclVolumeConstraint::FrameData, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVolumeConstraint::FrameData, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 813055124; };
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
	class hkArray<hclVolumeConstraint::ApplyData, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclVolumeConstraint::ApplyData, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2906277312; };
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
	class hkArray<hclStateDependencyGraph::Branch, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hclStateDependencyGraph::Branch, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 4056487534; };
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
	class hkArray<int, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<int, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2200381860; };
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
	class hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator> : public hkHolderBase {
	public:
		using BaseType = void;
		T*<void> m_data; // Offset: 0
		int m_size; // Offset: 8
		int m_capacityAndFlags; // Offset: 12

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkArray"; };
		inline std::string GetTranscriptId() override { return "hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>"; };
		inline uint32_t GethkClassHash() override { return 2287831965; };
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
