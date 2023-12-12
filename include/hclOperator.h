#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include "hclClothData.h"
#include "hclClothState.h"

namespace hktypes {
	class hclOperator : public hkReferencedObject {
	public:
		std::string name;	// Offset: 24 Unk: 0
		uint32_t operatorID;	// Offset: 32 Unk: 0
		uint32_t type;	// Offset: 36 Unk: 0
		std::vector<hclClothState::BufferAccess> usedBuffers;	// Offset: 40 Unk: 0
		std::vector<hclClothState::TransformSetAccess> usedTransformSets;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclBoneSpaceDeformer : public hkHolderBase {
	public:
		class LocalBlockPN :public hkHolderBase {
		public:
			hkVector4Holder localPosition[16];	// Offset: 0 Unk: 0
			hkPackedVector3 localNormal[16];	// Offset: 128 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class LocalBlockUnpackedPN :public hkHolderBase {
		public:
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override { return true; };
			bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
		};

		template<uint8_t _n_blend_entries>
		class BlendEntryBlock : public hkHolderBase {
		public:
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

		class OneBlendEntryBlock : public hkHolderBase {
		public:
			uint16_t vertexIndices[16];	// Offset: 0 Unk: 0
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

		using FourBlendEntryBlock = BlendEntryBlock<4>;
		using ThreeBlendEntryBlock = BlendEntryBlock<3>;
		using TwoBlendEntryBlock = BlendEntryBlock<2>;

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
	};

	class hclBoneSpaceSkinOperator : public hclOperator {
	public:
		std::vector<uint16_t> transformSubset;	// Offset: 72 Unk: 0
		uint32_t outputBufferIndex;	// Offset: 88 Unk: 0
		uint32_t transformSetIndex;	// Offset: 92 Unk: 0
		hclBoneSpaceDeformer boneSpaceDeformer;	// Offset: 96 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclBoneSpaceSkinPNOperator : public hclBoneSpaceSkinOperator {
	public:
		std::vector<hclBoneSpaceDeformer::LocalBlockPN> localPNs;	// Offset: 184 Unk: 0
		std::vector<hclBoneSpaceDeformer::LocalBlockUnpackedPN> localUnpackedPNs;	// Offset: 200 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclObjectSpaceDeformer : public hkHolderBase {
	public:
		class LocalBlockPN :public hkHolderBase {
		public:
			hkPackedVector3 localPosition[16];	// Offset: 0 Unk: 0
			hkPackedVector3 localNormal[16];	// Offset: 128 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class LocalBlockUnpackedPN :public hkHolderBase {
		public:
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override { return true; };
			bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
		};

		template<uint8_t _n_blend_entries>
		class BlendEntryBlock : public hkHolderBase {
		public:
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

		class OneBlendEntryBlock : public hkHolderBase {
		public:
			uint16_t vertexIndices[16];	// Offset: 0 Unk: 0
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
		bool partialWrite;	// Offset: 148 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclObjectSpaceSkinOperator : public hclOperator {
	public:
		std::vector<Eigen::Matrix4f> boneFromSkinMeshTransforms;	// Offset: 72 Unk: 0
		std::vector<uint16_t> transformSubset;	// Offset: 88 Unk: 0
		uint32_t outputBufferIndex;	// Offset: 104 Unk: 0
		uint32_t transformSetIndex;	// Offset: 108 Unk: 0
		hclObjectSpaceDeformer objectSpaceDeformer;	// Offset: 112 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclObjectSpaceSkinPNOperator : public hclObjectSpaceSkinOperator {
	public:
		std::vector<hclObjectSpaceDeformer::LocalBlockPN> localPNs;	// Offset: 264 Unk: 0
		std::vector<hclObjectSpaceDeformer::LocalBlockUnpackedPN> localUnpackedPNs;	// Offset: 280 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclMoveParticlesOperator : public hclOperator {
	public:
		class VertexParticlePair : public hkHolderBase {
		public:
			uint16_t vertexIndex;	// Offset: 0 Unk: 0
			uint16_t particleIndex;	// Offset: 2 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<VertexParticlePair> vertexParticlePairs;	// Offset: 72 Unk: 0
		uint32_t simClothIndex;	// Offset: 88 Unk: 0
		uint32_t refBufferIdx;	// Offset: 92 Unk: 0

			// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclGatherAllVerticesOperator : public hclOperator {
	public:
		std::vector<short> vertexInputFromVertexOutput;	// Offset: 72 Unk: 0
		uint32_t inputBufferIdx;	// Offset: 88 Unk: 0
		uint32_t outputBufferIdx;	// Offset: 92 Unk: 0
		bool gatherNormals;	// Offset: 96 Unk: 0
		bool partialGather;	// Offset: 97 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclSimulateOperator : public hclOperator {
	public:
		class Config : public hkHolderBase {
		public:
			std::string name;	// Offset: 0 Unk: 0
			std::vector<int> constraintExecution;	// Offset: 8 Unk: 0
			std::vector<bool> instanceCollidablesUsed;	// Offset: 24 Unk: 0
			uint8_t subSteps;	// Offset: 40 Unk: 0
			uint8_t numberOfSolveIterations;	// Offset: 41 Unk: 0
			bool useAllInstanceCollidables;	// Offset: 42 Unk: 0
			bool adaptConstraintStiffness;	// Offset: 43 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		uint32_t simClothIndex;	// Offset: 72 Unk: 0
		std::vector<Config> simulateOpConfigs;	// Offset: 80 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclSimpleMeshBoneDeformOperator : public hclOperator {
	public:
		class TriangleBonePair : public hkHolderBase {
		public:
			uint16_t boneOffset;	// Offset: 0 Unk: 0
			uint16_t triangleOffset;	// Offset: 2 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		uint32_t inputBufferIdx;	// Offset: 72 Unk: 0
		uint32_t outputTransformSetIdx;	// Offset: 76 Unk: 0
		std::vector<hclSimpleMeshBoneDeformOperator::TriangleBonePair> triangleBonePairs;	// Offset: 80 Unk: 0
		std::vector<hkMatrix4Holder> localBoneTransforms;	// Offset: 96 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclCopyVerticesOperator : public hclOperator {
	public:
		uint32_t inputBufferIdx;	// Offset: 72 Unk: 0
		uint32_t outputBufferIdx;	// Offset: 76 Unk: 0
		uint32_t numberOfVertices;	// Offset: 80 Unk: 0
		uint32_t startVertexIn;	// Offset: 84 Unk: 0
		uint32_t startVertexOut;	// Offset: 88 Unk: 0
		bool copyNormals;	// Offset: 92 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}