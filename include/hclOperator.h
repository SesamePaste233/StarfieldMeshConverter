#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include "hclClothData.h"
#include "hclClothState.h"

namespace hktypes {
	class hclOperator : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		std::string name;	// Offset: 24 Unk: 0
		uint32_t operatorID;	// Offset: 32 Unk: 0
		uint32_t type = 0;	// Offset: 36 Unk: 0
		std::vector<hclClothState::BufferAccess> usedBuffers;	// Offset: 40 Unk: 0
		std::vector<hclClothState::TransformSetAccess> usedTransformSets;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclOperator"; };
		inline std::string GetTranscriptId() override { return "hclOperator"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "operatorID", "unsigned int" },
				{ "type", "unsigned int" },
				{ "usedBuffers", "hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator>" },
				{ "usedTransformSets", "hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator>" },
			};
		};
	};

	class hclBoneSpaceDeformer : public hkHolderBase {
	public:
		using BaseType = void;
		class LocalBlockPN :public hkHolderBase {
		public:
			using BaseType = void;
			hkVector4Holder localPosition[16];	// Offset: 0 Unk: 0
			hkPackedVector3 localNormal[16];	// Offset: 128 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBoneSpaceDeformer::LocalBlockPN"; };
			inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer::LocalBlockPN"; };
			inline uint32_t GethkClassHash() override { return 1262607835; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "localPosition", "T[N]<hkVector4, 16>" },
					{ "localNormal", "T[N]<hkPackedVector3, 16>" },
				};
			};
		};

		class LocalBlockUnpackedPN :public hkHolderBase {
		public:
			using BaseType = void;
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override { return true; };
			bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
			inline std::string GethkClassName() override { return "hclBoneSpaceDeformer::LocalBlockUnpackedPN"; };
			inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer::LocalBlockUnpackedPN"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		template<uint8_t _n_blend_entries>
		class BlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;
			uint16_t vertexIndices[16];	// Offset: 0 Unk: 0
			uint16_t boneIndices[16 * _n_blend_entries];	// Offset: 32 Unk: 0
			uint8_t boneWeights[16 * _n_blend_entries];	// Offset: 32 + 32 * _n_blend_entries Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices;
				class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(_vertexIndices);
				if (_vertexIndices.size() != 16) {
					throw std::runtime_error("vertexIndices for BlendEntryBlock: size is not 16");
					return false;
				}
				std::memcpy(vertexIndices, _vertexIndices.data(), 16 * sizeof(uint16_t));

				std::vector<uint16_t> _boneIndices;
				class_instance->GetInstanceByFieldName("boneIndices")->GetValue(_boneIndices);
				if (_boneIndices.size() != 16 * _n_blend_entries) {
					throw std::runtime_error("boneIndices for BlendEntryBlock: size is not " + std::to_string(16 * _n_blend_entries));
					return false;
				}
				std::memcpy(boneIndices, _boneIndices.data(), 16 * _n_blend_entries * sizeof(uint16_t));

				std::vector<uint8_t> _boneWeights;
				class_instance->GetInstanceByFieldName("boneWeights")->GetValue(_boneWeights);
				if (_boneWeights.size() != 16 * _n_blend_entries) {
					throw std::runtime_error("boneWeights for BlendEntryBlock: size is not " + std::to_string(16 * _n_blend_entries));
					return false;
				}
				std::memcpy(boneWeights, _boneWeights.data(), 16 * _n_blend_entries * sizeof(uint8_t));

				return true;
			}
			bool ToInstance(hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices(vertexIndices, vertexIndices + 16);
				class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(_vertexIndices);

				std::vector<uint16_t> _boneIndices(boneIndices, boneIndices + 16 * _n_blend_entries);
				class_instance->GetInstanceByFieldName("boneIndices")->SetValue(_boneIndices);

				std::vector<uint8_t> _boneWeights(boneWeights, boneWeights + 16 * _n_blend_entries);
				class_instance->GetInstanceByFieldName("boneWeights")->SetValue(_boneWeights);

				return true;
			}
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};

			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> GetBoneIndicesAndWeights(std::vector<uint16_t>& transformSubset) {
				std::vector<std::vector<std::pair<uint16_t, uint8_t>>> result;
				for (int i = 0; i < 16; i++) {
					std::vector<std::pair<uint16_t, uint8_t>> boneIndicesAndWeights;
					for (int j = 0; j < _n_blend_entries; j++) {
						boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[i * _n_blend_entries + j]], boneWeights[i * _n_blend_entries + j]));
					}
					result.push_back(boneIndicesAndWeights);
				}
				return result;
			}
		};

		class FourBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;
			uint16_t vertexIndices[4];	// Offset: 0 Unk: 0
			uint16_t boneIndices[16];	// Offset: 32 Unk: 0
			uint8_t padding[8];	// Offset: 32 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices;
				class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(_vertexIndices);
				if (_vertexIndices.size() != 4) {
					throw std::runtime_error("vertexIndices for FourBlendEntryBlock: size is not 4");
					return false;
				}
				std::memcpy(vertexIndices, _vertexIndices.data(), 4 * sizeof(uint16_t));

				std::vector<uint16_t> _boneIndices;
				class_instance->GetInstanceByFieldName("boneIndices")->GetValue(_boneIndices);
				if (_boneIndices.size() != 16) {
					throw std::runtime_error("boneIndices for FourBlendEntryBlock: size is not 16");
					return false;
				}
				std::memcpy(boneIndices, _boneIndices.data(), 16 * sizeof(uint16_t));

				std::vector<uint8_t> _padding;
				class_instance->GetInstanceByFieldName("padding")->GetValue(_padding);
				if (_padding.size() != 8) {
					throw std::runtime_error("padding for FourBlendEntryBlock: size is not 8");
					return false;
				}
				std::memcpy(padding, _padding.data(), 8 * sizeof(uint8_t));

				return true;
			}
			bool ToInstance(hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices(vertexIndices, vertexIndices + 4);
				class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(_vertexIndices);

				std::vector<uint16_t> _boneIndices(boneIndices, boneIndices + 16);
				class_instance->GetInstanceByFieldName("boneIndices")->SetValue(_boneIndices);

				std::vector<uint8_t> _padding(padding, padding + 8);
				class_instance->GetInstanceByFieldName("padding")->SetValue(_padding);

				return true;
			}
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};

			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> GetBoneIndicesAndWeights(std::vector<uint16_t>& transformSubset) {
				std::vector<std::vector<std::pair<uint16_t, uint8_t>>> result;
				for (int i = 0; i < 4; i++) {
					std::vector<std::pair<uint16_t, uint8_t>> boneIndicesAndWeights;
					boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[4 * i]], 64));
					boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[4 * i + 1]], 64));
					boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[4 * i + 2]], 64));
					boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[4 * i + 3]], 63));

					result.push_back(boneIndicesAndWeights);
				}
				return result;
			}
		};

		class TwoBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;
			uint16_t vertexIndices[8];	// Offset: 0 Unk: 0
			uint16_t boneIndices[16];	// Offset: 32 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices;
				class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(_vertexIndices);
				if (_vertexIndices.size() != 8) {
					throw std::runtime_error("vertexIndices for TwoBlendEntryBlock: size is not 8");
					return false;
				}
				std::memcpy(vertexIndices, _vertexIndices.data(), 8 * sizeof(uint16_t));

				std::vector<uint16_t> _boneIndices;
				class_instance->GetInstanceByFieldName("boneIndices")->GetValue(_boneIndices);
				if (_boneIndices.size() != 16) {
					throw std::runtime_error("boneIndices for TwoBlendEntryBlock: size is not 16");
					return false;
				}
				std::memcpy(boneIndices, _boneIndices.data(), 16 * sizeof(uint16_t));

				return true;
			}
			bool ToInstance(hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices(vertexIndices, vertexIndices + 8);
				class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(_vertexIndices);

				std::vector<uint16_t> _boneIndices(boneIndices, boneIndices + 16);
				class_instance->GetInstanceByFieldName("boneIndices")->SetValue(_boneIndices);

				return true;
			}
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};

			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> GetBoneIndicesAndWeights(std::vector<uint16_t>& transformSubset) {
				std::vector<std::vector<std::pair<uint16_t, uint8_t>>> result;
				for (int i = 0; i < 8; i++) {
					std::vector<std::pair<uint16_t, uint8_t>> boneIndicesAndWeights;
					boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[2 * i]], 128));
					boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[2 * i + 1]], 127));

					result.push_back(boneIndicesAndWeights);
				}
				return result;
			}
		};
		
		class OneBlendEntryBlock : public hkHolderBase {
		public:
			using BaseType = void;
			uint16_t vertexIndices[16];	// Offset: 0 Unk: 0
			uint16_t boneIndices[16];	// Offset: 32 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices;
				class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(_vertexIndices);
				if (_vertexIndices.size() != 16) {
					throw std::runtime_error("vertexIndices for OneBlendEntryBlock: size is not 16");
					return false;
				}
				std::memcpy(vertexIndices, _vertexIndices.data(), 16 * sizeof(uint16_t));

				std::vector<uint16_t> _boneIndices;
				class_instance->GetInstanceByFieldName("boneIndices")->GetValue(_boneIndices);
				if (_boneIndices.size() != 16) {
					throw std::runtime_error("boneIndices for OneBlendEntryBlock: size is not 16");
					return false;
				}
				std::memcpy(boneIndices, _boneIndices.data(), 16 * sizeof(uint16_t));

				return true;
			}
			bool ToInstance(hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices(vertexIndices, vertexIndices + 16);
				class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(_vertexIndices);

				std::vector<uint16_t> _boneIndices(boneIndices, boneIndices + 16);
				class_instance->GetInstanceByFieldName("boneIndices")->SetValue(_boneIndices);

				return true;
			}
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};

			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> GetBoneIndicesAndWeights(std::vector<uint16_t>& transformSubset) {
				std::vector<std::vector<std::pair<uint16_t, uint8_t>>> result;
				for (int i = 0; i < 16; i++) {
					std::vector<std::pair<uint16_t, uint8_t>> boneIndicesAndWeights;
					boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[i]], 255));

					result.push_back(boneIndicesAndWeights);
				}
				return result;
			}
		};

		//using FourBlendEntryBlock = BlendEntryBlock<4>;
		using ThreeBlendEntryBlock = BlendEntryBlock<3>; // TODO

		std::vector<hclBoneSpaceDeformer::FourBlendEntryBlock> fourBlendEntries;	// Offset: 0 Unk: 0
		std::vector<hclBoneSpaceDeformer::ThreeBlendEntryBlock> threeBlendEntries;	// Offset: 16 Unk: 0
		std::vector<hclBoneSpaceDeformer::TwoBlendEntryBlock> twoBlendEntries;	// Offset: 32 Unk: 0
		std::vector<hclBoneSpaceDeformer::OneBlendEntryBlock> oneBlendEntries;	// Offset: 48 Unk: 0
		std::vector<uint8_t> controlBytes;	// Offset: 64 Unk: 0
		uint16_t startVertexIndex;	// Offset: 80 Unk: 0
		uint16_t endVertexIndex;	// Offset: 82 Unk: 0
		bool partialWrite;	// Offset: 84 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBoneSpaceDeformer"; };
		inline std::string GetTranscriptId() override { return "hclBoneSpaceDeformer"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "fourBlendEntries", "hkArray<hclBoneSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "threeBlendEntries", "hkArray<hclBoneSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "twoBlendEntries", "hkArray<hclBoneSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "oneBlendEntries", "hkArray<hclBoneSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "controlBytes", "hkArray<hkUint8, hkContainerHeapAllocator>" },
				{ "startVertexIndex", "hkUint16" },
				{ "endVertexIndex", "hkUint16" },
				{ "partialWrite", "hkBool" },
			};
		};
	};

	class hclBoneSpaceSkinOperator : public hclOperator {
	public:
		using BaseType = void;
		std::vector<uint16_t> transformSubset;	// Offset: 72 Unk: 0
		uint32_t outputBufferIndex;	// Offset: 88 Unk: 0
		uint32_t transformSetIndex;	// Offset: 92 Unk: 0
		hclBoneSpaceDeformer boneSpaceDeformer;	// Offset: 96 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBoneSpaceSkinOperator"; };
		inline std::string GetTranscriptId() override { return "hclBoneSpaceSkinOperator"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "transformSubset", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "outputBufferIndex", "hkUint32" },
				{ "transformSetIndex", "hkUint32" },
				{ "boneSpaceDeformer", "hclBoneSpaceDeformer" },
			};
		};
	};

	class hclBoneSpaceSkinPNOperator : public hclBoneSpaceSkinOperator {
	public:
		using BaseType = void;
		std::vector<hclBoneSpaceDeformer::LocalBlockPN> localPNs;	// Offset: 184 Unk: 0
		std::vector<hclBoneSpaceDeformer::LocalBlockUnpackedPN> localUnpackedPNs;	// Offset: 200 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBoneSpaceSkinPNOperator"; };
		inline std::string GetTranscriptId() override { return "hclBoneSpaceSkinPNOperator"; };
		inline uint32_t GethkClassHash() override { return 2804828730; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "localPNs", "hkArray<hclBoneSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator>" },
				{ "localUnpackedPNs", "hkArray<hclBoneSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator>" },
			};
		};
	};

	class hclObjectSpaceDeformer : public hkHolderBase {
	public:
		using BaseType = void;
		class LocalBlockPN :public hkHolderBase {
		public:
			using BaseType = void;
			hkPackedVector3 localPosition[16];	// Offset: 0 Unk: 0
			hkPackedVector3 localNormal[16];	// Offset: 128 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::LocalBlockPN"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::LocalBlockPN"; };
			inline uint32_t GethkClassHash() override { return 934674811; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "localPosition", "T[N]<hkPackedVector3, 16>" },
					{ "localNormal", "T[N]<hkPackedVector3, 16>" },
				};
			};
		};

		class LocalBlockUnpackedPN :public hkHolderBase {
		public:
			using BaseType = void;
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override { return true; };
			bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
			inline std::string GethkClassName() override { return "hclObjectSpaceDeformer::LocalBlockUnpackedPN"; };
			inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer::LocalBlockUnpackedPN"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		class EntryBlockBase {
		public:
			uint16_t vertexIndices[16];	// Offset: 0 Unk: 0
			virtual std::vector<std::vector<std::pair<uint16_t, uint8_t>>> GetBoneIndicesAndWeights(const std::vector<uint16_t>& transformSubset) = 0;
			virtual void SetWeights(const std::vector<std::vector<std::pair<uint16_t, uint8_t>>>& _boneIndicesAndWeights, const std::vector<uint16_t>& _vert_ids) = 0;
		};

		template<uint8_t _n_blend_entries>
		class BlendEntryBlock : public hkHolderBase, public EntryBlockBase {
		public:
			using BaseType = void;
			uint16_t boneIndices[16 * _n_blend_entries];	// Offset: 32 Unk: 0
			uint8_t boneWeights[16 * _n_blend_entries];	// Offset: 32 + 32 * _n_blend_entries Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices;
				class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(_vertexIndices);
				if (_vertexIndices.size() != 16) {
					throw std::runtime_error("vertexIndices for BlendEntryBlock: size is not 16");
					return false;
				}
				std::memcpy(vertexIndices, _vertexIndices.data(), 16 * sizeof(uint16_t));

				std::vector<uint16_t> _boneIndices;
				class_instance->GetInstanceByFieldName("boneIndices")->GetValue(_boneIndices);
				if (_boneIndices.size() != 16 * _n_blend_entries) {
					throw std::runtime_error("boneIndices for BlendEntryBlock: size is not " + std::to_string(16 * _n_blend_entries));
					return false;
				}
				std::memcpy(boneIndices, _boneIndices.data(), 16 * _n_blend_entries * sizeof(uint16_t));

				std::vector<uint8_t> _boneWeights;
				class_instance->GetInstanceByFieldName("boneWeights")->GetValue(_boneWeights);
				if (_boneWeights.size() != 16 * _n_blend_entries) {
					throw std::runtime_error("boneWeights for BlendEntryBlock: size is not " + std::to_string(16 * _n_blend_entries));
					return false;
				}
				std::memcpy(boneWeights, _boneWeights.data(), 16 * _n_blend_entries * sizeof(uint8_t));

				return true;
			}
			bool ToInstance(hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices(vertexIndices, vertexIndices + 16);
				class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(_vertexIndices);

				std::vector<uint16_t> _boneIndices(boneIndices, boneIndices + 16 * _n_blend_entries);
				class_instance->GetInstanceByFieldName("boneIndices")->SetValue(_boneIndices);

				std::vector<uint8_t> _boneWeights(boneWeights, boneWeights + 16 * _n_blend_entries);
				class_instance->GetInstanceByFieldName("boneWeights")->SetValue(_boneWeights);

				return true;
			}
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};

			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> GetBoneIndicesAndWeights(const std::vector<uint16_t>& transformSubset) override {
				std::vector<std::vector<std::pair<uint16_t, uint8_t>>> result;
				for (int i = 0; i < 16; i++) {
					std::vector<std::pair<uint16_t, uint8_t>> boneIndicesAndWeights;
					for (int j = 0; j < _n_blend_entries; j++) {
						boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[i * _n_blend_entries + j]], boneWeights[i * _n_blend_entries + j]));
					}
					result.push_back(boneIndicesAndWeights);
				}
				return result;
			}

			void SetWeights(const std::vector<std::vector<std::pair<uint16_t, uint8_t>>>& _boneIndicesAndWeights, const std::vector<uint16_t>& _vert_ids) override {
				assert(_vert_ids.size() == _boneIndicesAndWeights.size());
				std::vector<uint16_t> vert_ids(_vert_ids);
				std::vector<std::vector<std::pair<uint16_t, uint8_t>>> boneIndicesAndWeights(_boneIndicesAndWeights);
				for (auto& weight_pair: boneIndicesAndWeights) {
					while (weight_pair.size() < _n_blend_entries) {
						weight_pair.push_back({ weight_pair.front().first, 0 });
					}
					assert(weight_pair.size() == _n_blend_entries);
				}
				while (vert_ids.size() < 16) {
					vert_ids.push_back(vert_ids.back());
					boneIndicesAndWeights.push_back(boneIndicesAndWeights.back());
				}
				assert(vert_ids.size() == 16);
				assert(boneIndicesAndWeights.size() == 16);

				std::memcpy(vertexIndices, vert_ids.data(), 16 * sizeof(uint16_t));

				for (int i = 0; i < 16; i++) {
					for (int j = 0; j < _n_blend_entries; j++) {
						boneIndices[i * _n_blend_entries + j] = boneIndicesAndWeights[i][j].first;
						boneWeights[i * _n_blend_entries + j] = boneIndicesAndWeights[i][j].second;
					}
				}
			}
		};

		class OneBlendEntryBlock : public hkHolderBase, public EntryBlockBase {
		public:
			using BaseType = void;
			uint16_t boneIndices[16];	// Offset: 32 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices;
				class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(_vertexIndices);
				if (_vertexIndices.size() != 16) {
					throw std::runtime_error("vertexIndices for BlendEntryBlock: size is not 16");
					return false;
				}
				std::memcpy(vertexIndices, _vertexIndices.data(), 16 * sizeof(uint16_t));

				std::vector<uint16_t> _boneIndices;
				class_instance->GetInstanceByFieldName("boneIndices")->GetValue(_boneIndices);
				if (_boneIndices.size() != 16) {
					throw std::runtime_error("boneIndices for BlendEntryBlock: size is not " + std::to_string(16));
					return false;
				}
				std::memcpy(boneIndices, _boneIndices.data(), 16 * sizeof(uint16_t));

				return true;
			}
			bool ToInstance(hkreflex::hkClassInstance* instance) override {
				auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
				if (!class_instance) return false;

				std::vector<uint16_t> _vertexIndices(vertexIndices, vertexIndices + 16);
				class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(_vertexIndices);

				std::vector<uint16_t> _boneIndices(boneIndices, boneIndices + 16);
				class_instance->GetInstanceByFieldName("boneIndices")->SetValue(_boneIndices);

				return true;
			}
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};

			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> GetBoneIndicesAndWeights(const std::vector<uint16_t>& transformSubset) override {
				std::vector<std::vector<std::pair<uint16_t, uint8_t>>> result;
				for (int i = 0; i < 16; i++) {
					std::vector<std::pair<uint16_t, uint8_t>> boneIndicesAndWeights;
					boneIndicesAndWeights.push_back(std::make_pair(transformSubset[boneIndices[i]], 255));
		
					result.push_back(boneIndicesAndWeights);
				}
				return result;
			}
		
			void SetWeights(const std::vector<std::vector<std::pair<uint16_t, uint8_t>>>& _boneIndicesAndWeights, const std::vector<uint16_t>& _vert_ids) override {
				assert(_vert_ids.size() == _boneIndicesAndWeights.size());
				std::vector<uint16_t> vert_ids(_vert_ids);
				std::vector<std::vector<std::pair<uint16_t, uint8_t>>> boneIndicesAndWeights(_boneIndicesAndWeights);
				while (vert_ids.size() < 16) {
					vert_ids.push_back(vert_ids.back());
					boneIndicesAndWeights.push_back(boneIndicesAndWeights.back());
				}
				assert(vert_ids.size() == 16);
				assert(boneIndicesAndWeights.size() == 16);

				std::memcpy(vertexIndices, vert_ids.data(), 16 * sizeof(uint16_t));

				for (int i = 0; i < 16; i++) {
					boneIndices[i] = boneIndicesAndWeights[i][0].first;
				}
			}
		};

		typedef BlendEntryBlock<8> EightBlendEntryBlock;
		typedef BlendEntryBlock<7> SevenBlendEntryBlock;
		typedef BlendEntryBlock<6> SixBlendEntryBlock;
		typedef BlendEntryBlock<5> FiveBlendEntryBlock;
		typedef BlendEntryBlock<4> FourBlendEntryBlock;
		typedef BlendEntryBlock<3> ThreeBlendEntryBlock;
		typedef BlendEntryBlock<2> TwoBlendEntryBlock;

		std::vector<EightBlendEntryBlock> eightBlendEntries;	// Offset: 0 Unk: 0
		std::vector<SevenBlendEntryBlock> sevenBlendEntries;	// Offset: 16 Unk: 0
		std::vector<SixBlendEntryBlock> sixBlendEntries;	// Offset: 32 Unk: 0
		std::vector<FiveBlendEntryBlock> fiveBlendEntries;	// Offset: 48 Unk: 0
		std::vector<FourBlendEntryBlock> fourBlendEntries;	// Offset: 64 Unk: 0
		std::vector<ThreeBlendEntryBlock> threeBlendEntries;	// Offset: 80 Unk: 0
		std::vector<TwoBlendEntryBlock> twoBlendEntries;	// Offset: 96 Unk: 0
		std::vector<OneBlendEntryBlock> oneBlendEntries;	// Offset: 112 Unk: 0
		std::vector<uint8_t> controlBytes;	// Offset: 128 Unk: 0
		uint16_t startVertexIndex;	// Offset: 144 Unk: 0
		uint16_t endVertexIndex;	// Offset: 146 Unk: 0
		bool partialWrite = false;	// Offset: 148 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclObjectSpaceDeformer"; };
		inline std::string GetTranscriptId() override { return "hclObjectSpaceDeformer"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "eightBlendEntries", "hkArray<hclObjectSpaceDeformer::EightBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "sevenBlendEntries", "hkArray<hclObjectSpaceDeformer::SevenBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "sixBlendEntries", "hkArray<hclObjectSpaceDeformer::SixBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "fiveBlendEntries", "hkArray<hclObjectSpaceDeformer::FiveBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "fourBlendEntries", "hkArray<hclObjectSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "threeBlendEntries", "hkArray<hclObjectSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "twoBlendEntries", "hkArray<hclObjectSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "oneBlendEntries", "hkArray<hclObjectSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator>" },
				{ "controlBytes", "hkArray<hkUint8, hkContainerHeapAllocator>" },
				{ "startVertexIndex", "hkUint16" },
				{ "endVertexIndex", "hkUint16" },
				{ "partialWrite", "hkBool" },
			};
		};
	};

	class hclObjectSpaceSkinOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		std::vector<Eigen::Matrix4f> boneFromSkinMeshTransforms;	// Offset: 72 Unk: 0
		std::vector<uint16_t> transformSubset;	// Offset: 88 Unk: 0
		uint32_t outputBufferIndex;	// Offset: 104 Unk: 0
		uint32_t transformSetIndex;	// Offset: 108 Unk: 0
		hclObjectSpaceDeformer objectSpaceDeformer;	// Offset: 112 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclObjectSpaceSkinOperator"; };
		inline std::string GetTranscriptId() override { return "hclObjectSpaceSkinOperator"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "boneFromSkinMeshTransforms", "hkArray<hkMatrix4, hkContainerHeapAllocator>" },
				{ "transformSubset", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "outputBufferIndex", "hkUint32" },
				{ "transformSetIndex", "hkUint32" },
				{ "objectSpaceDeformer", "hclObjectSpaceDeformer" },
			};
		};
	};

	class hclObjectSpaceSkinPNOperator : public hclObjectSpaceSkinOperator {
	public:
		using BaseType = hclObjectSpaceSkinOperator;
		std::vector<hclObjectSpaceDeformer::LocalBlockPN> localPNs;	// Offset: 264 Unk: 0
		std::vector<hclObjectSpaceDeformer::LocalBlockUnpackedPN> localUnpackedPNs;	// Offset: 280 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclObjectSpaceSkinPNOperator"; };
		inline std::string GetTranscriptId() override { return "hclObjectSpaceSkinPNOperator"; };
		inline uint32_t GethkClassHash() override { return 3464584781; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "localPNs", "hkArray<hclObjectSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator>" },
				{ "localUnpackedPNs", "hkArray<hclObjectSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator>" },
			};
		};
	};

	class hclMoveParticlesOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		class VertexParticlePair : public hkHolderBase {
		public:
			using BaseType = void;
			uint16_t vertexIndex;	// Offset: 0 Unk: 0
			uint16_t particleIndex;	// Offset: 2 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclMoveParticlesOperator::VertexParticlePair"; };
			inline std::string GetTranscriptId() override { return "hclMoveParticlesOperator::VertexParticlePair"; };
			inline uint32_t GethkClassHash() override { return 3905957961; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "vertexIndex", "hkUint16" },
					{ "particleIndex", "hkUint16" },
				};
			};
		};

		std::vector<VertexParticlePair> vertexParticlePairs;	// Offset: 72 Unk: 0
		uint32_t simClothIndex;	// Offset: 88 Unk: 0
		uint32_t refBufferIdx;	// Offset: 92 Unk: 0

			// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclMoveParticlesOperator"; };
		inline std::string GetTranscriptId() override { return "hclMoveParticlesOperator"; };
		inline uint32_t GethkClassHash() override { return 1999418277; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "vertexParticlePairs", "hkArray<hclMoveParticlesOperator::VertexParticlePair, hkContainerHeapAllocator>" },
				{ "simClothIndex", "hkUint32" },
				{ "refBufferIdx", "hkUint32" },
			};
		};
	};

	class hclGatherAllVerticesOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		std::vector<short> vertexInputFromVertexOutput;	// Offset: 72 Unk: 0
		uint32_t inputBufferIdx;	// Offset: 88 Unk: 0
		uint32_t outputBufferIdx;	// Offset: 92 Unk: 0
		bool gatherNormals;	// Offset: 96 Unk: 0
		bool partialGather;	// Offset: 97 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclGatherAllVerticesOperator"; };
		inline std::string GetTranscriptId() override { return "hclGatherAllVerticesOperator"; };
		inline uint32_t GethkClassHash() override { return 2385740196; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "vertexInputFromVertexOutput", "hkArray<hkInt16, hkContainerHeapAllocator>" },
				{ "inputBufferIdx", "hkUint32" },
				{ "outputBufferIdx", "hkUint32" },
				{ "gatherNormals", "hkBool" },
				{ "partialGather", "hkBool" },
			};
		};
	};

	class hclSimulateOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		class Config : public hkHolderBase {
		public:
			using BaseType = void;
			std::string name = "Default Config";	// Offset: 0 Unk: 0
			std::vector<int> constraintExecution;	// Offset: 8 Unk: 0
			std::vector<bool> instanceCollidablesUsed;	// Offset: 24 Unk: 0
			uint8_t subSteps = 1;	// Offset: 40 Unk: 0
			uint8_t numberOfSolveIterations = 1;	// Offset: 41 Unk: 0
			bool useAllInstanceCollidables = true;	// Offset: 42 Unk: 0
			bool adaptConstraintStiffness = true;	// Offset: 43 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimulateOperator::Config"; };
			inline std::string GetTranscriptId() override { return "hclSimulateOperator::Config"; };
			inline uint32_t GethkClassHash() override { return 2651451972; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "name", "hkStringPtr" },
					{ "constraintExecution", "hkArray<hkInt32, hkContainerHeapAllocator>" },
					{ "instanceCollidablesUsed", "hkArray<hkBool, hkContainerHeapAllocator>" },
					{ "subSteps", "hkUint8" },
					{ "numberOfSolveIterations", "hkUint8" },
					{ "useAllInstanceCollidables", "hkBool" },
					{ "adaptConstraintStiffness", "hkBool" },
				};
			};
		};

		uint32_t simClothIndex;	// Offset: 72 Unk: 0
		std::vector<Config> simulateOpConfigs;	// Offset: 80 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclSimulateOperator"; };
		inline std::string GetTranscriptId() override { return "hclSimulateOperator"; };
		inline uint32_t GethkClassHash() override { return 2555309371; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "simClothIndex", "hkUint32" },
				{ "simulateOpConfigs", "hkArray<hclSimulateOperator::Config, hkContainerHeapAllocator>" },
			};
		};
	};

	class hclSimpleMeshBoneDeformOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		class TriangleBonePair : public hkHolderBase {
		public:
			using BaseType = void;
			uint16_t boneOffset;	// Offset: 0 Unk: 0
			uint16_t triangleOffset;	// Offset: 2 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimpleMeshBoneDeformOperator::TriangleBonePair"; };
			inline std::string GetTranscriptId() override { return "hclSimpleMeshBoneDeformOperator::TriangleBonePair"; };
			inline uint32_t GethkClassHash() override { return 2878957036; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "boneOffset", "hkUint16" },
					{ "triangleOffset", "hkUint16" },
				};
			};
		};

		uint32_t inputBufferIdx;	// Offset: 72 Unk: 0
		uint32_t outputTransformSetIdx;	// Offset: 76 Unk: 0
		std::vector<hclSimpleMeshBoneDeformOperator::TriangleBonePair> triangleBonePairs;	// Offset: 80 Unk: 0
		std::vector<hkMatrix4Holder> localBoneTransforms;	// Offset: 96 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclSimpleMeshBoneDeformOperator"; };
		inline std::string GetTranscriptId() override { return "hclSimpleMeshBoneDeformOperator"; };
		inline uint32_t GethkClassHash() override { return 1364889027; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "inputBufferIdx", "hkUint32" },
				{ "outputTransformSetIdx", "hkUint32" },
				{ "triangleBonePairs", "hkArray<hclSimpleMeshBoneDeformOperator::TriangleBonePair, hkContainerHeapAllocator>" },
				{ "localBoneTransforms", "hkArray<hkMatrix4, hkContainerHeapAllocator>" },
			};
		};
	};

	class hclCopyVerticesOperator : public hclOperator {
	public:
		using BaseType = hclOperator;
		uint32_t inputBufferIdx;	// Offset: 72 Unk: 0
		uint32_t outputBufferIdx;	// Offset: 76 Unk: 0
		uint32_t numberOfVertices;	// Offset: 80 Unk: 0
		uint32_t startVertexIn;	// Offset: 84 Unk: 0
		uint32_t startVertexOut;	// Offset: 88 Unk: 0
		bool copyNormals;	// Offset: 92 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclCopyVerticesOperator"; };
		inline std::string GetTranscriptId() override { return "hclCopyVerticesOperator"; };
		inline uint32_t GethkClassHash() override { return 4287559816; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "inputBufferIdx", "hkUint32" },
				{ "outputBufferIdx", "hkUint32" },
				{ "numberOfVertices", "hkUint32" },
				{ "startVertexIn", "hkUint32" },
				{ "startVertexOut", "hkUint32" },
				{ "copyNormals", "hkBool" },
			};
		};
	};
}