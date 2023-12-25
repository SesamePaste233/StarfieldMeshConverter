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

		uint8_t perComponentFlags[2];	// Offset: 0 Unk: 0
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
	};

	class hclBufferUsage : public hkHolderBase {
	public:
		using BaseType = void;
		uint8_t perComponentFlags[4];	// Offset: 0 Unk: 0
		bool trianglesRead;	// Offset: 4 Unk: 0

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