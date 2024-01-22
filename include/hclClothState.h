#pragma once
#include "hkInclude.h"
#include "hkTypes.h"

namespace hktypes {
	class hkBitField;

	class hclTransformSetUsage : public hkHolderBase {
	public:
		using BaseType = void;
		class TransformTracker : public hkHolderBase {
		public:
			using BaseType = void;
			hkBitField read;	// Offset: 0 Unk: 0
			hkBitField readBeforeWrite;	// Offset: 24 Unk: 0
			hkBitField written;	// Offset: 48 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() { return "hclTransformSetUsage::TransformTracker"; };
			inline std::string GetTranscriptId() { return "hclTransformSetUsage::TransformTracker"; };
			inline uint32_t GethkClassHash() { return 51977619; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
				return {
					{ "read", "hkBitField" },
					{ "readBeforeWrite", "hkBitField" },
					{ "written", "hkBitField" },
				};
			};
		};

		enum UsageFlags : uint8_t {
			None = 0,
			UF_Read = 1 << 0,
			UF_Write = 1 << 1,
			UF_ReadBeforeWrite = 1 << 3,
		};

		uint8_t perComponentFlags[2] = { 0,0 };	// Offset: 0 Unk: 0
		std::vector<TransformTracker> perComponentTransformTrackers;	// Offset: 8 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() { return "hclTransformSetUsage"; };
		inline std::string GetTranscriptId() { return "hclTransformSetUsage"; };
		inline uint32_t GethkClassHash() { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
			return {
				{ "perComponentFlags", "T[N]<hkUint8, 2>" },
				{ "perComponentTransformTrackers", "hkArray<hclTransformSetUsage::TransformTracker, hkContainerHeapAllocator>" },
			};
		};


		inline void SetNumBitsForAll(int num_bits) {
			for (auto& tracker : perComponentTransformTrackers) {
				tracker.read.SetNumBits(num_bits);
				tracker.readBeforeWrite.SetNumBits(num_bits);
				tracker.written.SetNumBits(num_bits);
			}
		}

		template<typename _elem_t>
		requires utils::_unsigned_integer_t<_elem_t>
		inline bool AddUsage(uint8_t component_index, uint8_t usage_flags, std::vector<_elem_t> accessed_ids) {
			if (accessed_ids.empty())
				return false;
			if (component_index >= 2)
				return false;
			std::vector<uint32_t> accessed_ids_32(accessed_ids.begin(), accessed_ids.end());
			perComponentFlags[component_index] |= usage_flags;
			if (usage_flags & UsageFlags::UF_Read) {
				auto& record = perComponentTransformTrackers[component_index].read;
				record = record | hkBitField(accessed_ids_32, record.GetNumBits());
			}
			if (usage_flags & UsageFlags::UF_ReadBeforeWrite) {
				auto& record = perComponentTransformTrackers[component_index].readBeforeWrite;
				record = record | hkBitField(accessed_ids_32, record.GetNumBits());
			}
			if (usage_flags & UsageFlags::UF_Write) {
				auto& record = perComponentTransformTrackers[component_index].written;
				record = record | hkBitField(accessed_ids_32, record.GetNumBits());
			}
		};
	};

	class hclBufferUsage : public hkHolderBase {
	public:
		enum ComponentFlags : uint8_t {
			CF_Position = 0,
			CF_Normal = 1,
			CF_Tangent = 2,
			CF_Bitangent = 3,
			CF_Total = 4,
		};

		using BaseType = void;
		uint8_t perComponentFlags[4] = { 0,0,0,0 };	// Offset: 0 Unk: 0
		bool trianglesRead = false;	// Offset: 4 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() { return "hclBufferUsage"; };
		inline std::string GetTranscriptId() { return "hclBufferUsage"; };
		inline uint32_t GethkClassHash() { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
			return {
				{ "perComponentFlags", "T[N]<hkUint8, 4>" },
				{ "trianglesRead", "hkBool" },
			};
		};
	};

	class hclStateDependencyGraph : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class Branch : public hkHolderBase {
		public:
			using BaseType = void;
			int branchId;	// Offset: 0 Unk: 0
			std::vector<int> stateOperatorIndices;	// Offset: 8 Unk: 0
			std::vector<int> parentBranches;	// Offset: 24 Unk: 0
			std::vector<int> childBranches;	// Offset: 40 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() { return "hclStateDependencyGraph::Branch"; };
			inline std::string GetTranscriptId() { return "hclStateDependencyGraph::Branch"; };
			inline uint32_t GethkClassHash() { return 2493525897; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
				return {
					{ "branchId", "int" },
					{ "stateOperatorIndices", "hkArray<int, hkContainerHeapAllocator>" },
					{ "parentBranches", "hkArray<int, hkContainerHeapAllocator>" },
					{ "childBranches", "hkArray<int, hkContainerHeapAllocator>" },
				};
			};
		};

		std::vector<hclStateDependencyGraph::Branch> branches;	// Offset: 24 Unk: 0
		std::vector<int> rootBranchIds;	// Offset: 40 Unk: 0
		std::vector<std::vector<int>> children;	// Offset: 56 Unk: 0
		std::vector<std::vector<int>> parents;	// Offset: 72 Unk: 0
		bool multiThreadable;	// Offset: 88 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() { return "hclStateDependencyGraph"; };
		inline std::string GetTranscriptId() { return "hclStateDependencyGraph"; };
		inline uint32_t GethkClassHash() { return 2248211247; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
			return {
				{ "branches", "hkArray<hclStateDependencyGraph::Branch, hkContainerHeapAllocator>" },
				{ "rootBranchIds", "hkArray<int, hkContainerHeapAllocator>" },
				{ "children", "hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>" },
				{ "parents", "hkArray<hkArray<int, hkContainerHeapAllocator>, hkContainerHeapAllocator>" },
				{ "multiThreadable", "hkBool" },
			};
		};
	};

	class hclClothState : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class BufferAccess : public hkHolderBase {
		public:
			using BaseType = void;
			uint32_t bufferIndex;	// Offset: 0 Unk: 0
			hclBufferUsage bufferUsage;	// Offset: 4 Unk: 0
			uint32_t shadowBufferIndex;	// Offset: 12 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() { return "hclClothState::BufferAccess"; };
			inline std::string GetTranscriptId() { return "hclClothState::BufferAccess"; };
			inline uint32_t GethkClassHash() { return 746522671; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
				return {
					{ "bufferIndex", "hkUint32" },
					{ "bufferUsage", "hclBufferUsage" },
					{ "shadowBufferIndex", "hkUint32" },
				};
			};
		};
		class TransformSetAccess : public hkHolderBase {
		public:
			using BaseType = void;
			uint32_t transformSetIndex;	// Offset: 0 Unk: 0
			hclTransformSetUsage transformSetUsage;	// Offset: 8 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() { return "hclClothState::TransformSetAccess"; };
			inline std::string GetTranscriptId() { return "hclClothState::TransformSetAccess"; };
			inline uint32_t GethkClassHash() { return 3568223325; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
				return {
					{ "transformSetIndex", "hkUint32" },
					{ "transformSetUsage", "hclTransformSetUsage" },
				};
			};
		};

		std::string name;	// Offset: 24 Unk: 0
		std::vector<uint32_t> operators;	// Offset: 32 Unk: 0
		std::vector<hclClothState::BufferAccess> usedBuffers;	// Offset: 48 Unk: 0
		std::vector<hclClothState::TransformSetAccess> usedTransformSets;	// Offset: 64 Unk: 0
		std::vector<uint32_t> usedSimCloths;	// Offset: 80 Unk: 0
		hclStateDependencyGraph* dependencyGraph;	// Offset: 96 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() { return "hclClothState"; };
		inline std::string GetTranscriptId() { return "hclClothState"; };
		inline uint32_t GethkClassHash() { return 1309046206; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() {
			return {
				{ "name", "hkStringPtr" },
				{ "operators", "hkArray<hkUint32, hkContainerHeapAllocator>" },
				{ "usedBuffers", "hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator>" },
				{ "usedTransformSets", "hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator>" },
				{ "usedSimCloths", "hkArray<hkUint32, hkContainerHeapAllocator>" },
				{ "dependencyGraph", "T*<hclStateDependencyGraph>" },
			};
		};
	};
}