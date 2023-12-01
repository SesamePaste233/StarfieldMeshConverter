#pragma once

#include "hkBaseCTypes.h"
// Class No.201
// Mapped to c type: hkArray<hkArray, hkContainerHeapAllocator>
template<class tT=hkArray<int, hkContainerHeapAllocator>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.200
// Original: hkArray<int, hkContainerHeapAllocator> Mapped to c type : std::vector<int>


// Class No.199
// Mapped to c type: hclStateDependencyGraph::Branch
class hclStateDependencyGraph::Branch {
	int branchId;	// Offset: 0 Unk: 0
	std::vector<int> stateOperatorIndices;	// Offset: 8 Unk: 0
	std::vector<int> parentBranches;	// Offset: 24 Unk: 0
	std::vector<int> childBranches;	// Offset: 40 Unk: 0
};

// Class No.198
// Original: hkArray<hclStateDependencyGraph::Branch, hkContainerHeapAllocator> Mapped to c type : std::vector<hclStateDependencyGraph::Branch>


// Class No.197
// Mapped to c type: hclLocalRangeConstraintSet::ShapeType
class hclLocalRangeConstraintSet::ShapeType;	// [Undefined]

// Class No.196
// Original: hkEnum<hclLocalRangeConstraintSet::ShapeType, hkUint32> Mapped to c type : hclLocalRangeConstraintSet::ShapeType


// Class No.195
// Mapped to c type: hclLocalRangeConstraintSet::LocalStiffnessConstraint
class hclLocalRangeConstraintSet::LocalStiffnessConstraint {
	uint16_t particleIndex;	// Offset: 0 Unk: 0
	uint16_t referenceVertex;	// Offset: 2 Unk: 0
	float maximumDistance;	// Offset: 4 Unk: 0
	float maxNormalDistance;	// Offset: 8 Unk: 0
	float minNormalDistance;	// Offset: 12 Unk: 0
	float stiffness;	// Offset: 16 Unk: 0
};

// Class No.194
// Mapped to c type: hkArray<hclLocalRangeConstraintSet::LocalStiffnessConstraint, hkContainerHeapAllocator>
template<class tT=hclLocalRangeConstraintSet::LocalStiffnessConstraint, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.193
// Mapped to c type: hclLocalRangeConstraintSet::LocalConstraint
class hclLocalRangeConstraintSet::LocalConstraint;	// [Undefined]

// Class No.192
// Original: hkArray<hclLocalRangeConstraintSet::LocalConstraint, hkContainerHeapAllocator> Mapped to c type : std::vector<hclLocalRangeConstraintSet::LocalConstraint>


// Class No.191
// Mapped to c type: hclLocalRangeConstraintSet
class hclLocalRangeConstraintSet : public hclConstraintSet {
	std::vector<hclLocalRangeConstraintSet::LocalConstraint> localConstraints;	// Offset: 40 Unk: 0
	hkArray<hclLocalRangeConstraintSet::LocalStiffnessConstraint, hkContainerHeapAllocator> localStiffnessConstraints;	// Offset: 56 Unk: 0
	uint32_t referenceMeshBufferIdx;	// Offset: 72 Unk: 0
	float stiffness;	// Offset: 76 Unk: 0
	hclLocalRangeConstraintSet::ShapeType shapeType;	// Offset: 80 Unk: 0
	bool applyNormalComponent;	// Offset: 84 Unk: 0
};

// Class No.190
// Original: T[N]<hkUint16, 4> Mapped to c type : std::array<uint16_t, 4>


// Class No.189
// Original: T[N]<hkReal, 4> Mapped to c type : std::array<float, 4>


// Class No.188
// Original: hkHandle<hkUint32, 2147483647> Mapped to c type : hkHandle<uint32_t>


// Class No.187
// Mapped to c type: hclStandardLinkConstraintSetMx::Single
class hclStandardLinkConstraintSetMx::Single {
	float restLength;	// Offset: 0 Unk: 0
	float stiffnessA;	// Offset: 4 Unk: 0
	float stiffnessB;	// Offset: 8 Unk: 0
	uint16_t particleA;	// Offset: 12 Unk: 0
	uint16_t particleB;	// Offset: 14 Unk: 0
};

// Class No.186
// Original: hkArray<hclStandardLinkConstraintSetMx::Single, hkContainerHeapAllocator> Mapped to c type : std::vector<hclStandardLinkConstraintSetMx::Single>


// Class No.185
// Mapped to c type: hclStandardLinkConstraintSetMx::Batch
class hclStandardLinkConstraintSetMx::Batch {
	std::array<float, 4> restLengths;	// Offset: 0 Unk: 0
	std::array<float, 4> stiffnessesA;	// Offset: 16 Unk: 0
	std::array<float, 4> stiffnessesB;	// Offset: 32 Unk: 0
	std::array<uint16_t, 4> particlesA;	// Offset: 48 Unk: 0
	std::array<uint16_t, 4> particlesB;	// Offset: 56 Unk: 0
};

// Class No.184
// Original: hkArray<hclStandardLinkConstraintSetMx::Batch, hkContainerHeapAllocator> Mapped to c type : std::vector<hclStandardLinkConstraintSetMx::Batch>


// Class No.183
// Mapped to c type: hclStandardLinkConstraintSetMx
class hclStandardLinkConstraintSetMx : public hclConstraintSet {
	std::vector<hclStandardLinkConstraintSetMx::Batch> batches;	// Offset: 40 Unk: 0
	std::vector<hclStandardLinkConstraintSetMx::Single> singles;	// Offset: 56 Unk: 0
};

// Class No.182
// Original: hkArray<hkVector4, hkContainerHeapAllocator> Mapped to c type : std::vector<Vector4>


// Class No.181
// Mapped to c type: hclStateDependencyGraph
class hclStateDependencyGraph : public hkReferencedObject {
	std::vector<hclStateDependencyGraph::Branch> branches;	// Offset: 24 Unk: 0
	std::vector<int> rootBranchIds;	// Offset: 40 Unk: 0
	hkArray<hkArray, hkContainerHeapAllocator> children;	// Offset: 56 Unk: 0
	hkArray<hkArray, hkContainerHeapAllocator> parents;	// Offset: 72 Unk: 0
	bool multiThreadable;	// Offset: 88 Unk: 0
};

// Class No.180
// Original: T*<hclStateDependencyGraph> Mapped to c type : hclStateDependencyGraph


// Class No.179
// Mapped to c type: hclCopyVerticesOperator
class hclCopyVerticesOperator : public hclOperator {
	uint32_t inputBufferIdx;	// Offset: 72 Unk: 0
	uint32_t outputBufferIdx;	// Offset: 76 Unk: 0
	uint32_t numberOfVertices;	// Offset: 80 Unk: 0
	uint32_t startVertexIn;	// Offset: 84 Unk: 0
	uint32_t startVertexOut;	// Offset: 88 Unk: 0
	bool copyNormals;	// Offset: 92 Unk: 0
};

// Class No.178
// Mapped to c type: hclSimpleMeshBoneDeformOperator::TriangleBonePair
class hclSimpleMeshBoneDeformOperator::TriangleBonePair {
	uint16_t boneOffset;	// Offset: 0 Unk: 0
	uint16_t triangleOffset;	// Offset: 2 Unk: 0
};

// Class No.177
// Original: hkArray<hclSimpleMeshBoneDeformOperator::TriangleBonePair, hkContainerHeapAllocator> Mapped to c type : std::vector<hclSimpleMeshBoneDeformOperator::TriangleBonePair>


// Class No.176
// Mapped to c type: hclSimpleMeshBoneDeformOperator
class hclSimpleMeshBoneDeformOperator : public hclOperator {
	uint32_t inputBufferIdx;	// Offset: 72 Unk: 0
	uint32_t outputTransformSetIdx;	// Offset: 76 Unk: 0
	std::vector<hclSimpleMeshBoneDeformOperator::TriangleBonePair> triangleBonePairs;	// Offset: 80 Unk: 0
	std::vector<Eigen::Matrix4f> localBoneTransforms;	// Offset: 96 Unk: 0
};

// Class No.175
// Original: hkArray<hkInt32, hkContainerHeapAllocator> Mapped to c type : std::vector<int>


// Class No.174
// Mapped to c type: hclSimulateOperator::Config
class hclSimulateOperator::Config {
	std::string name;	// Offset: 0 Unk: 0
	std::vector<int> constraintExecution;	// Offset: 8 Unk: 0
	std::vector<bool> instanceCollidablesUsed;	// Offset: 24 Unk: 0
	uint8_t subSteps;	// Offset: 40 Unk: 0
	uint8_t numberOfSolveIterations;	// Offset: 41 Unk: 0
	bool useAllInstanceCollidables;	// Offset: 42 Unk: 0
	bool adaptConstraintStiffness;	// Offset: 43 Unk: 0
};

// Class No.173
// Original: hkArray<hclSimulateOperator::Config, hkContainerHeapAllocator> Mapped to c type : std::vector<hclSimulateOperator::Config>


// Class No.172
// Mapped to c type: hclSimulateOperator
class hclSimulateOperator : public hclOperator {
	uint32_t simClothIndex;	// Offset: 72 Unk: 0
	std::vector<hclSimulateOperator::Config> simulateOpConfigs;	// Offset: 80 Unk: 0
};

// Class No.171
// Mapped to c type: hclMoveParticlesOperator::VertexParticlePair
class hclMoveParticlesOperator::VertexParticlePair {
	uint16_t vertexIndex;	// Offset: 0 Unk: 0
	uint16_t particleIndex;	// Offset: 2 Unk: 0
};

// Class No.170
// Original: hkArray<hclMoveParticlesOperator::VertexParticlePair, hkContainerHeapAllocator> Mapped to c type : std::vector<hclMoveParticlesOperator::VertexParticlePair>


// Class No.169
// Mapped to c type: hclMoveParticlesOperator
class hclMoveParticlesOperator : public hclOperator {
	std::vector<hclMoveParticlesOperator::VertexParticlePair> vertexParticlePairs;	// Offset: 72 Unk: 0
	uint32_t simClothIndex;	// Offset: 88 Unk: 0
	uint32_t refBufferIdx;	// Offset: 92 Unk: 0
};

// Class No.168
// Mapped to c type: hkBitFieldStorage<hkArray>
template<class tStorage=hkArray<hkUint32, hkContainerHeapAllocator>>
class hkBitFieldStorage {
	std::vector<uint32_t> words;	// Offset: 0 Unk: 0
	int numBits;	// Offset: 16 Unk: 0
};

// Class No.167
// Mapped to c type: hkBitFieldBase<hkBitFieldStorage>
template<class tStorage=hkBitFieldStorage<hkArray>>
class hkBitFieldBase {
	hkBitFieldStorage<hkArray> storage;	// Offset: 0 Unk: 0
};

// Class No.166
// Mapped to c type: hkBitField
class hkBitField : public hkBitFieldBase<hkBitFieldStorage> {
};

// Class No.165
// Original: T[N]<hkInt16, 4> Mapped to c type : std::array<short, 4>


// Class No.164
// Mapped to c type: hkPackedVector3
class hkPackedVector3 {
	std::array<short, 4> values;	// Offset: 0 Unk: 3
};

// Class No.163
// Original: T[N]<hkPackedVector3, 16> Mapped to c type : std::array<hkPackedVector3, 16>


// Class No.162
// Original: T[N]<hkUint8, 48> Mapped to c type : std::array<uint8_t, 48>


// Class No.161
// Original: T[N]<hkUint16, 48> Mapped to c type : std::array<uint16_t, 48>


// Class No.160
// Original: T[N]<hkUint16, 16> Mapped to c type : std::array<uint16_t, 16>


// Class No.159
// Original: hkMatrix4Impl<float> Mapped to c type : Eigen::Matrix4f


// Class No.158
// Mapped to c type: hkMatrix4f
class hkMatrix4f : public hkMatrix4Impl<float> {
};

// Class No.157
// Mapped to c type: hclTransformSetUsage::TransformTracker
class hclTransformSetUsage::TransformTracker {
	hkBitField read;	// Offset: 0 Unk: 0
	hkBitField readBeforeWrite;	// Offset: 24 Unk: 0
	hkBitField written;	// Offset: 48 Unk: 0
};

// Class No.156
// Original: hkArray<hclTransformSetUsage::TransformTracker, hkContainerHeapAllocator> Mapped to c type : std::vector<hclTransformSetUsage::TransformTracker>


// Class No.155
// Original: T[N]<hkUint8, 2> Mapped to c type : std::array<uint8_t, 2>


// Class No.154
// Mapped to c type: hclTransformSetUsage
class hclTransformSetUsage {
	std::array<uint8_t, 2> perComponentFlags;	// Offset: 0 Unk: 0
	std::vector<hclTransformSetUsage::TransformTracker> perComponentTransformTrackers;	// Offset: 8 Unk: 0
};

// Class No.153
// Original: T[N]<hkUint8, 4> Mapped to c type : std::array<uint8_t, 4>


// Class No.152
// Mapped to c type: hclBufferUsage
class hclBufferUsage {
	std::array<uint8_t, 4> perComponentFlags;	// Offset: 0 Unk: 0
	bool trianglesRead;	// Offset: 4 Unk: 0
};

// Class No.151
// Mapped to c type: hclObjectSpaceDeformer::OneBlendEntryBlock
class hclObjectSpaceDeformer::OneBlendEntryBlock;	// [Undefined]

// Class No.150
// Original: hkArray<hclObjectSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::OneBlendEntryBlock>


// Class No.149
// Mapped to c type: hclObjectSpaceDeformer::TwoBlendEntryBlock
class hclObjectSpaceDeformer::TwoBlendEntryBlock;	// [Undefined]

// Class No.148
// Original: hkArray<hclObjectSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::TwoBlendEntryBlock>


// Class No.147
// Mapped to c type: hclObjectSpaceDeformer::ThreeBlendEntryBlock
class hclObjectSpaceDeformer::ThreeBlendEntryBlock {
	std::array<uint16_t, 16> vertexIndices;	// Offset: 0 Unk: 0
	std::array<uint16_t, 48> boneIndices;	// Offset: 32 Unk: 0
	std::array<uint8_t, 48> boneWeights;	// Offset: 128 Unk: 0
};

// Class No.146
// Original: hkArray<hclObjectSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::ThreeBlendEntryBlock>


// Class No.145
// Mapped to c type: hclObjectSpaceDeformer::FourBlendEntryBlock
class hclObjectSpaceDeformer::FourBlendEntryBlock;	// [Undefined]

// Class No.144
// Original: hkArray<hclObjectSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::FourBlendEntryBlock>


// Class No.143
// Mapped to c type: hclObjectSpaceDeformer::FiveBlendEntryBlock
class hclObjectSpaceDeformer::FiveBlendEntryBlock;	// [Undefined]

// Class No.142
// Original: hkArray<hclObjectSpaceDeformer::FiveBlendEntryBlock, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::FiveBlendEntryBlock>


// Class No.141
// Mapped to c type: hclObjectSpaceDeformer::SixBlendEntryBlock
class hclObjectSpaceDeformer::SixBlendEntryBlock;	// [Undefined]

// Class No.140
// Original: hkArray<hclObjectSpaceDeformer::SixBlendEntryBlock, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::SixBlendEntryBlock>


// Class No.139
// Mapped to c type: hclObjectSpaceDeformer::SevenBlendEntryBlock
class hclObjectSpaceDeformer::SevenBlendEntryBlock;	// [Undefined]

// Class No.138
// Original: hkArray<hclObjectSpaceDeformer::SevenBlendEntryBlock, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::SevenBlendEntryBlock>


// Class No.137
// Mapped to c type: hclObjectSpaceDeformer::EightBlendEntryBlock
class hclObjectSpaceDeformer::EightBlendEntryBlock;	// [Undefined]

// Class No.136
// Original: hkArray<hclObjectSpaceDeformer::EightBlendEntryBlock, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::EightBlendEntryBlock>


// Class No.135
// Mapped to c type: hclClothState::TransformSetAccess
class hclClothState::TransformSetAccess {
	uint32_t transformSetIndex;	// Offset: 0 Unk: 0
	hclTransformSetUsage transformSetUsage;	// Offset: 8 Unk: 0
};

// Class No.134
// Original: hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator> Mapped to c type : std::vector<hclClothState::TransformSetAccess>


// Class No.133
// Mapped to c type: hclClothState::BufferAccess
class hclClothState::BufferAccess {
	uint32_t bufferIndex;	// Offset: 0 Unk: 0
	hclBufferUsage bufferUsage;	// Offset: 4 Unk: 0
	uint32_t shadowBufferIndex;	// Offset: 12 Unk: 0
};

// Class No.132
// Original: hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator> Mapped to c type : std::vector<hclClothState::BufferAccess>


// Class No.131
// Mapped to c type: hclObjectSpaceDeformer
class hclObjectSpaceDeformer {
	std::vector<hclObjectSpaceDeformer::EightBlendEntryBlock> eightBlendEntries;	// Offset: 0 Unk: 0
	std::vector<hclObjectSpaceDeformer::SevenBlendEntryBlock> sevenBlendEntries;	// Offset: 16 Unk: 0
	std::vector<hclObjectSpaceDeformer::SixBlendEntryBlock> sixBlendEntries;	// Offset: 32 Unk: 0
	std::vector<hclObjectSpaceDeformer::FiveBlendEntryBlock> fiveBlendEntries;	// Offset: 48 Unk: 0
	std::vector<hclObjectSpaceDeformer::FourBlendEntryBlock> fourBlendEntries;	// Offset: 64 Unk: 0
	std::vector<hclObjectSpaceDeformer::ThreeBlendEntryBlock> threeBlendEntries;	// Offset: 80 Unk: 0
	std::vector<hclObjectSpaceDeformer::TwoBlendEntryBlock> twoBlendEntries;	// Offset: 96 Unk: 0
	std::vector<hclObjectSpaceDeformer::OneBlendEntryBlock> oneBlendEntries;	// Offset: 112 Unk: 0
	std::vector<uint8_t> controlBytes;	// Offset: 128 Unk: 0
	uint16_t startVertexIndex;	// Offset: 144 Unk: 0
	uint16_t endVertexIndex;	// Offset: 146 Unk: 0
	bool partialWrite;	// Offset: 148 Unk: 0
};

// Class No.130
// Mapped to c type: hclObjectSpaceDeformer::LocalBlockUnpackedPN
class hclObjectSpaceDeformer::LocalBlockUnpackedPN;	// [Undefined]

// Class No.129
// Original: hkArray<hclObjectSpaceDeformer::LocalBlockUnpackedPN, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::LocalBlockUnpackedPN>


// Class No.128
// Mapped to c type: hclObjectSpaceDeformer::LocalBlockPN
class hclObjectSpaceDeformer::LocalBlockPN {
	std::array<hkPackedVector3, 16> localPosition;	// Offset: 0 Unk: 0
	std::array<hkPackedVector3, 16> localNormal;	// Offset: 128 Unk: 0
};

// Class No.127
// Original: hkArray<hclObjectSpaceDeformer::LocalBlockPN, hkContainerHeapAllocator> Mapped to c type : std::vector<hclObjectSpaceDeformer::LocalBlockPN>


// Class No.126
// Mapped to c type: hclObjectSpaceSkinOperator
class hclObjectSpaceSkinOperator : public hclOperator {
	std::vector<Eigen::Matrix4f> boneFromSkinMeshTransforms;	// Offset: 72 Unk: 0
	std::vector<uint16_t> transformSubset;	// Offset: 88 Unk: 0
	uint32_t outputBufferIndex;	// Offset: 104 Unk: 0
	uint32_t transformSetIndex;	// Offset: 108 Unk: 0
	hclObjectSpaceDeformer objectSpaceDeformer;	// Offset: 112 Unk: 0
};

// Class No.125
// Mapped to c type: hclObjectSpaceSkinPNOperator
class hclObjectSpaceSkinPNOperator : public hclObjectSpaceSkinOperator {
	std::vector<hclObjectSpaceDeformer::LocalBlockPN> localPNs;	// Offset: 264 Unk: 0
	std::vector<hclObjectSpaceDeformer::LocalBlockUnpackedPN> localUnpackedPNs;	// Offset: 280 Unk: 0
};

// Class No.124
// Mapped to c type: hclBufferLayout::SlotFlags
class hclBufferLayout::SlotFlags;	// [Undefined]

// Class No.123
// Original: hkEnum<hclBufferLayout::SlotFlags, hkUint8> Mapped to c type : hclBufferLayout::SlotFlags


// Class No.122
// Mapped to c type: hclRuntimeConversionInfo::VectorConversion
class hclRuntimeConversionInfo::VectorConversion;	// [Undefined]

// Class No.121
// Original: hkEnum<hclRuntimeConversionInfo::VectorConversion, hkUint8> Mapped to c type : hclRuntimeConversionInfo::VectorConversion


// Class No.120
// Mapped to c type: hclBufferLayout::TriangleFormat
class hclBufferLayout::TriangleFormat;	// [Undefined]

// Class No.119
// Original: hkEnum<hclBufferLayout::TriangleFormat, hkUint8> Mapped to c type : hclBufferLayout::TriangleFormat


// Class No.118
// Mapped to c type: hclBufferLayout::Slot
class hclBufferLayout::Slot {
	hclBufferLayout::SlotFlags flags;	// Offset: 0 Unk: 0
	uint8_t stride;	// Offset: 1 Unk: 0
};

// Class No.117
// Original: T[N]<hclBufferLayout::Slot, 4> Mapped to c type : std::array<hclBufferLayout::Slot, 4>


// Class No.116
// Mapped to c type: hclBufferLayout::BufferElement
class hclBufferLayout::BufferElement {
	hclRuntimeConversionInfo::VectorConversion vectorConversion;	// Offset: 0 Unk: 0
	uint8_t vectorSize;	// Offset: 1 Unk: 0
	uint8_t slotId;	// Offset: 2 Unk: 0
	uint8_t slotStart;	// Offset: 3 Unk: 0
};

// Class No.115
// Original: T[N]<hclBufferLayout::BufferElement, 4> Mapped to c type : std::array<hclBufferLayout::BufferElement, 4>


// Class No.114
// Mapped to c type: hclBufferLayout
class hclBufferLayout {
	std::array<hclBufferLayout::BufferElement, 4> elementsLayout;	// Offset: 0 Unk: 0
	std::array<hclBufferLayout::Slot, 4> slots;	// Offset: 16 Unk: 0
	uint8_t numSlots;	// Offset: 24 Unk: 0
	hclBufferLayout::TriangleFormat triangleFormat;	// Offset: 25 Unk: 0
};

// Class No.113
// Mapped to c type: hclScratchBufferDefinition
class hclScratchBufferDefinition : public hclBufferDefinition {
	std::vector<uint16_t> triangleIndices;	// Offset: 88 Unk: 0
	bool storeNormals;	// Offset: 104 Unk: 0
	bool storeTangentsAndBiTangents;	// Offset: 105 Unk: 0
};

// Class No.112
// Original: unsigned char Mapped to c type : uint8_t


// Class No.111
// Original: signed char Mapped to c type : int8_t


// Class No.110
// Mapped to c type: hclVirtualCollisionPointsData::TriangleFanLandscape
class hclVirtualCollisionPointsData::TriangleFanLandscape;	// [Undefined]

// Class No.109
// Original: hkArray<hclVirtualCollisionPointsData::TriangleFanLandscape, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::TriangleFanLandscape>


// Class No.108
// Mapped to c type: hclVirtualCollisionPointsData::EdgeFanLandscape
class hclVirtualCollisionPointsData::EdgeFanLandscape;	// [Undefined]

// Class No.107
// Original: hkArray<hclVirtualCollisionPointsData::EdgeFanLandscape, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::EdgeFanLandscape>


// Class No.106
// Mapped to c type: hclVirtualCollisionPointsData::TriangleFan
class hclVirtualCollisionPointsData::TriangleFan;	// [Undefined]

// Class No.105
// Original: hkArray<hclVirtualCollisionPointsData::TriangleFan, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::TriangleFan>


// Class No.104
// Mapped to c type: hclVirtualCollisionPointsData::TriangleFanSection
class hclVirtualCollisionPointsData::TriangleFanSection;	// [Undefined]

// Class No.103
// Original: hkArray<hclVirtualCollisionPointsData::TriangleFanSection, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::TriangleFanSection>


// Class No.102
// Mapped to c type: hclVirtualCollisionPointsData::EdgeFan
class hclVirtualCollisionPointsData::EdgeFan;	// [Undefined]

// Class No.101
// Original: hkArray<hclVirtualCollisionPointsData::EdgeFan, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::EdgeFan>


// Class No.100
// Mapped to c type: hclVirtualCollisionPointsData::EdgeFanSection
class hclVirtualCollisionPointsData::EdgeFanSection;	// [Undefined]

// Class No.99
// Original: hkArray<hclVirtualCollisionPointsData::EdgeFanSection, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::EdgeFanSection>


// Class No.98
// Mapped to c type: hclVirtualCollisionPointsData::BarycentricPair
class hclVirtualCollisionPointsData::BarycentricPair;	// [Undefined]

// Class No.97
// Original: hkArray<hclVirtualCollisionPointsData::BarycentricPair, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::BarycentricPair>


// Class No.96
// Mapped to c type: hclVirtualCollisionPointsData::BarycentricDictionaryEntry
class hclVirtualCollisionPointsData::BarycentricDictionaryEntry;	// [Undefined]

// Class No.95
// Original: hkArray<hclVirtualCollisionPointsData::BarycentricDictionaryEntry, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::BarycentricDictionaryEntry>


// Class No.94
// Mapped to c type: hclVirtualCollisionPointsData::Block
class hclVirtualCollisionPointsData::Block;	// [Undefined]

// Class No.93
// Original: hkArray<hclVirtualCollisionPointsData::Block, hkContainerHeapAllocator> Mapped to c type : std::vector<hclVirtualCollisionPointsData::Block>


// Class No.92
// Original: unsigned short Mapped to c type : uint16_t


// Class No.91
// Original: hkInt8 Mapped to c type : int8_t


// Class No.90
// Original: hkMatrix4 Mapped to c type : Eigen::Matrix4f


// Class No.89
// Original: hkArray<hkMatrix4, hkContainerHeapAllocator> Mapped to c type : std::vector<Eigen::Matrix4f>


// Class No.88
// Original: hkInt32 Mapped to c type : int


// Class No.87
// Original: hkVector4 Mapped to c type : Eigen::Vector4f


// Class No.86
// Mapped to c type: hclVirtualCollisionPointsData
class hclVirtualCollisionPointsData {
	std::vector<hclVirtualCollisionPointsData::Block> blocks;	// Offset: 0 Unk: 0
	uint16_t numVCPoints;	// Offset: 16 Unk: 0
	std::vector<uint16_t> landscapeParticlesBlockIndex;	// Offset: 24 Unk: 0
	uint16_t numLandscapeVCPoints;	// Offset: 40 Unk: 0
	std::vector<float> edgeBarycentricsDictionary;	// Offset: 48 Unk: 0
	std::vector<hclVirtualCollisionPointsData::BarycentricDictionaryEntry> edgeDictionaryEntries;	// Offset: 64 Unk: 0
	std::vector<hclVirtualCollisionPointsData::BarycentricPair> triangleBarycentricsDictionary;	// Offset: 80 Unk: 0
	std::vector<hclVirtualCollisionPointsData::BarycentricDictionaryEntry> triangleDictionaryEntries;	// Offset: 96 Unk: 0
	std::vector<hclVirtualCollisionPointsData::EdgeFanSection> edges;	// Offset: 112 Unk: 0
	std::vector<hclVirtualCollisionPointsData::EdgeFan> edgeFans;	// Offset: 128 Unk: 0
	std::vector<hclVirtualCollisionPointsData::TriangleFanSection> triangles;	// Offset: 144 Unk: 0
	std::vector<hclVirtualCollisionPointsData::TriangleFan> triangleFans;	// Offset: 160 Unk: 0
	std::vector<hclVirtualCollisionPointsData::EdgeFanSection> edgesLandscape;	// Offset: 176 Unk: 0
	std::vector<hclVirtualCollisionPointsData::EdgeFanLandscape> edgeFansLandscape;	// Offset: 192 Unk: 0
	std::vector<hclVirtualCollisionPointsData::TriangleFanSection> trianglesLandscape;	// Offset: 208 Unk: 0
	std::vector<hclVirtualCollisionPointsData::TriangleFanLandscape> triangleFansLandscape;	// Offset: 224 Unk: 0
	std::vector<uint16_t> edgeFanIndices;	// Offset: 240 Unk: 0
	std::vector<uint16_t> triangleFanIndices;	// Offset: 256 Unk: 0
	std::vector<uint16_t> edgeFanIndicesLandscape;	// Offset: 272 Unk: 0
	std::vector<uint16_t> triangleFanIndicesLandscape;	// Offset: 288 Unk: 0
};

// Class No.85
// Mapped to c type: hclSimClothData::CollidablePinchingData
class hclSimClothData::CollidablePinchingData;	// [Undefined]

// Class No.84
// Original: hkArray<hclSimClothData::CollidablePinchingData, hkContainerHeapAllocator> Mapped to c type : std::vector<hclSimClothData::CollidablePinchingData>


// Class No.83
// Original: hkArray<hkBool, hkContainerHeapAllocator> Mapped to c type : std::vector<bool>


// Class No.82
// Original: hkUint8 Mapped to c type : uint8_t


// Class No.81
// Original: hkArray<hkUint8, hkContainerHeapAllocator> Mapped to c type : std::vector<uint8_t>


// Class No.80
// Mapped to c type: hclSimClothData::LandscapeCollisionData
class hclSimClothData::LandscapeCollisionData {
	float landscapeRadius;	// Offset: 0 Unk: 0
	bool enableStuckParticleDetection;	// Offset: 4 Unk: 0
	float stuckParticlesStretchFactorSq;	// Offset: 8 Unk: 0
	bool pinchDetectionEnabled;	// Offset: 12 Unk: 0
	int8_t pinchDetectionPriority;	// Offset: 13 Unk: 0
	float pinchDetectionRadius;	// Offset: 16 Unk: 0
	float collisionTolerance;	// Offset: 20 Unk: 0
};

// Class No.79
// Mapped to c type: hclSimClothData::TransferMotionData
class hclSimClothData::TransferMotionData {
	uint32_t transformSetIndex;	// Offset: 0 Unk: 0
	uint32_t transformIndex;	// Offset: 4 Unk: 0
	bool transferTranslationMotion;	// Offset: 8 Unk: 0
	float minTranslationSpeed;	// Offset: 12 Unk: 0
	float maxTranslationSpeed;	// Offset: 16 Unk: 0
	float minTranslationBlend;	// Offset: 20 Unk: 0
	float maxTranslationBlend;	// Offset: 24 Unk: 0
	bool transferRotationMotion;	// Offset: 28 Unk: 0
	float minRotationSpeed;	// Offset: 32 Unk: 0
	float maxRotationSpeed;	// Offset: 36 Unk: 0
	float minRotationBlend;	// Offset: 40 Unk: 0
	float maxRotationBlend;	// Offset: 44 Unk: 0
};

// Class No.78
// Original: hkArray<hkUint32, hkContainerHeapAllocator> Mapped to c type : std::vector<uint32_t>


// Class No.77
// Mapped to c type: hclCollidable
class hclCollidable;	// [Undefined]

// Class No.76
// Original: T*<hclCollidable> Mapped to c type : hclCollidable


// Class No.75
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclCollidable>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.74
// Mapped to c type: hclSimClothData::CollidableTransformMap
class hclSimClothData::CollidableTransformMap {
	int transformSetIndex;	// Offset: 0 Unk: 0
	std::vector<uint32_t> transformIndices;	// Offset: 8 Unk: 0
	std::vector<Eigen::Matrix4f> offsets;	// Offset: 24 Unk: 0
};

// Class No.73
// Mapped to c type: hclConstraintSet
class hclConstraintSet : public hkReferencedObject {
	std::string name;	// Offset: 24 Unk: 0
	hkHandle<uint32_t> constraintId;	// Offset: 32 Unk: 0
	uint32_t type;	// Offset: 36 Unk: 0
};

// Class No.72
// Original: T*<hclConstraintSet> Mapped to c type : hclConstraintSet


// Class No.71
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclConstraintSet>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.70
// Mapped to c type: hclSimClothPose
class hclSimClothPose : public hkReferencedObject {
	std::string name;	// Offset: 24 Unk: 0
	std::vector<Vector4> positions;	// Offset: 32 Unk: 0
};

// Class No.69
// Original: T*<hclSimClothPose> Mapped to c type : hclSimClothPose


// Class No.68
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclSimClothPose>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.67
// Original: hkArray<unsigned int, hkContainerHeapAllocator> Mapped to c type : std::vector<uint32_t>


// Class No.66
// Original: hkUint16 Mapped to c type : uint16_t


// Class No.65
// Original: hkArray<hkUint16, hkContainerHeapAllocator> Mapped to c type : std::vector<uint16_t>


// Class No.64
// Mapped to c type: hclSimClothData::ParticleData
class hclSimClothData::ParticleData {
	float mass;	// Offset: 0 Unk: 0
	float invMass;	// Offset: 4 Unk: 0
	float radius;	// Offset: 8 Unk: 0
	float friction;	// Offset: 12 Unk: 0
};

// Class No.63
// Original: hkArray<hclSimClothData::ParticleData, hkContainerHeapAllocator> Mapped to c type : std::vector<hclSimClothData::ParticleData>


// Class No.62
// Mapped to c type: hclSimClothData::OverridableSimulationInfo
class hclSimClothData::OverridableSimulationInfo {
	Eigen::Vector4f gravity;	// Offset: 0 Unk: 0
	float globalDampingPerSecond;	// Offset: 16 Unk: 0
};

// Class No.61
// Mapped to c type: float
class float {
};

// Class No.60
// Original: hkQuaternionf Mapped to c type : Eigen::Quaternionf


// Class No.59
// Original: hkVector4f Mapped to c type : Eigen::Vector4f


// Class No.58
// Mapped to c type: hkQsTransformf
class hkQsTransformf {
	Eigen::Vector4f translation;	// Offset: 0 Unk: 0
	Eigen::Quaternionf rotation;	// Offset: 16 Unk: 0
	Eigen::Vector4f scale;	// Offset: 32 Unk: 0
};

// Class No.57
// Mapped to c type: short
class short {
};

// Class No.56
// Mapped to c type: hkaSkeleton::Partition
class hkaSkeleton::Partition;	// [Undefined]

// Class No.55
// Original: hkArray<hkaSkeleton::Partition, hkContainerHeapAllocator> Mapped to c type : std::vector<hkaSkeleton::Partition>


// Class No.54
// Mapped to c type: hkaSkeleton::LocalFrameOnBone
class hkaSkeleton::LocalFrameOnBone;	// [Undefined]

// Class No.53
// Original: hkArray<hkaSkeleton::LocalFrameOnBone, hkContainerHeapAllocator> Mapped to c type : std::vector<hkaSkeleton::LocalFrameOnBone>


// Class No.52
// Original: hkArray<hkStringPtr, hkContainerHeapAllocator> Mapped to c type : std::vector<std::string>


// Class No.51
// Original: hkReal Mapped to c type : float


// Class No.50
// Original: hkArray<hkReal, hkContainerHeapAllocator> Mapped to c type : std::vector<float>


// Class No.49
// Mapped to c type: hkQsTransform
class hkQsTransform : public hkQsTransformf {
};

// Class No.48
// Original: hkArray<hkQsTransform, hkContainerHeapAllocator> Mapped to c type : std::vector<hkQsTransform>


// Class No.47
// Mapped to c type: hkaBone
class hkaBone {
	std::string name;	// Offset: 0 Unk: 0
	bool lockTranslation;	// Offset: 8 Unk: 0
};

// Class No.46
// Original: hkArray<hkaBone, hkContainerHeapAllocator> Mapped to c type : std::vector<hkaBone>


// Class No.45
// Original: hkInt16 Mapped to c type : short


// Class No.44
// Original: hkArray<hkInt16, hkContainerHeapAllocator> Mapped to c type : std::vector<short>


// Class No.43
// Mapped to c type: hkaSkeleton
class hkaSkeleton : public hkReferencedObject {
	std::string name;	// Offset: 24 Unk: 0
	std::vector<short> parentIndices;	// Offset: 32 Unk: 0
	std::vector<hkaBone> bones;	// Offset: 48 Unk: 0
	std::vector<hkQsTransform> referencePose;	// Offset: 64 Unk: 0
	std::vector<float> referenceFloats;	// Offset: 80 Unk: 0
	std::vector<std::string> floatSlots;	// Offset: 96 Unk: 0
	std::vector<hkaSkeleton::LocalFrameOnBone> localFrames;	// Offset: 112 Unk: 0
	std::vector<hkaSkeleton::Partition> partitions;	// Offset: 128 Unk: 0
};

// Class No.42
// Original: unsigned int Mapped to c type : uint32_t


// Class No.41
// Original: unsigned long long Mapped to c type : uint64_t


// Class No.40
// Original: hkUlong Mapped to c type : uint64_t


// Class No.39
// Mapped to c type: hkBaseObject
class hkBaseObject {
};

// Class No.38
// Original: hkUint32 Mapped to c type : uint32_t


// Class No.37
// Mapped to c type: hclClothData::Platform
class hclClothData::Platform;	// [Undefined]

// Class No.36
// Original: hkEnum<hclClothData::Platform, hkUint32> Mapped to c type : hclClothData::Platform


// Class No.35
// Original: hkBool Mapped to c type : bool


// Class No.34
// Mapped to c type: hclAction
class hclAction;	// [Undefined]

// Class No.33
// Original: T*<hclAction> Mapped to c type : hclAction


// Class No.32
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclAction>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.31
// Mapped to c type: hclStateTransition
class hclStateTransition;	// [Undefined]

// Class No.30
// Original: T*<hclStateTransition> Mapped to c type : hclStateTransition


// Class No.29
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclStateTransition>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.28
// Mapped to c type: hclClothState
class hclClothState : public hkReferencedObject {
	std::string name;	// Offset: 24 Unk: 0
	std::vector<uint32_t> operators;	// Offset: 32 Unk: 0
	std::vector<hclClothState::BufferAccess> usedBuffers;	// Offset: 48 Unk: 0
	std::vector<hclClothState::TransformSetAccess> usedTransformSets;	// Offset: 64 Unk: 0
	std::vector<uint32_t> usedSimCloths;	// Offset: 80 Unk: 0
	hclStateDependencyGraph dependencyGraph;	// Offset: 96 Unk: 0
};

// Class No.27
// Original: T*<hclClothState> Mapped to c type : hclClothState


// Class No.26
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclClothState>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.25
// Mapped to c type: hclOperator
class hclOperator : public hkReferencedObject {
	std::string name;	// Offset: 24 Unk: 0
	uint32_t operatorID;	// Offset: 32 Unk: 0
	uint32_t type;	// Offset: 36 Unk: 0
	std::vector<hclClothState::BufferAccess> usedBuffers;	// Offset: 40 Unk: 0
	std::vector<hclClothState::TransformSetAccess> usedTransformSets;	// Offset: 56 Unk: 0
};

// Class No.24
// Original: T*<hclOperator> Mapped to c type : hclOperator


// Class No.23
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclOperator>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.22
// Mapped to c type: hclTransformSetDefinition
class hclTransformSetDefinition : public hkReferencedObject {
	std::string name;	// Offset: 24 Unk: 0
	int type;	// Offset: 32 Unk: 0
	uint32_t numTransforms;	// Offset: 36 Unk: 0
};

// Class No.21
// Original: T*<hclTransformSetDefinition> Mapped to c type : hclTransformSetDefinition


// Class No.20
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclTransformSetDefinition>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.19
// Mapped to c type: hclBufferDefinition
class hclBufferDefinition : public hkReferencedObject {
	std::string meshName;	// Offset: 24 Unk: 0
	std::string bufferName;	// Offset: 32 Unk: 0
	int type;	// Offset: 40 Unk: 0
	int subType;	// Offset: 44 Unk: 0
	uint32_t numVertices;	// Offset: 48 Unk: 0
	uint32_t numTriangles;	// Offset: 52 Unk: 0
	hclBufferLayout bufferLayout;	// Offset: 56 Unk: 0
};

// Class No.18
// Original: T*<hclBufferDefinition> Mapped to c type : hclBufferDefinition


// Class No.17
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclBufferDefinition>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.16
// Mapped to c type: hclSimClothData
class hclSimClothData : public hkReferencedObject {
	std::string name;	// Offset: 24 Unk: 0
	hclSimClothData::OverridableSimulationInfo simulationInfo;	// Offset: 32 Unk: 0
	std::vector<hclSimClothData::ParticleData> particleDatas;	// Offset: 64 Unk: 0
	std::vector<uint16_t> fixedParticles;	// Offset: 80 Unk: 0
	bool doNormals;	// Offset: 96 Unk: 0
	std::vector<uint32_t> simOpIds;	// Offset: 104 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> simClothPoses;	// Offset: 120 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> staticConstraintSets;	// Offset: 136 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> antiPinchConstraintSets;	// Offset: 152 Unk: 0
	hclSimClothData::CollidableTransformMap collidableTransformMap;	// Offset: 168 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> perInstanceCollidables;	// Offset: 208 Unk: 0
	float maxParticleRadius;	// Offset: 224 Unk: 0
	std::vector<uint32_t> staticCollisionMasks;	// Offset: 232 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> actions;	// Offset: 248 Unk: 0
	float totalMass;	// Offset: 264 Unk: 0
	hclSimClothData::TransferMotionData transferMotionData;	// Offset: 268 Unk: 0
	bool transferMotionEnabled;	// Offset: 316 Unk: 0
	bool landscapeCollisionEnabled;	// Offset: 317 Unk: 0
	hclSimClothData::LandscapeCollisionData landscapeCollisionData;	// Offset: 320 Unk: 0
	uint32_t numLandscapeCollidableParticles;	// Offset: 344 Unk: 0
	std::vector<uint16_t> triangleIndices;	// Offset: 352 Unk: 0
	std::vector<uint8_t> triangleFlips;	// Offset: 368 Unk: 0
	bool pinchDetectionEnabled;	// Offset: 384 Unk: 0
	std::vector<bool> perParticlePinchDetectionEnabledFlags;	// Offset: 392 Unk: 0
	std::vector<hclSimClothData::CollidablePinchingData> collidablePinchingDatas;	// Offset: 408 Unk: 0
	uint16_t minPinchedParticleIndex;	// Offset: 424 Unk: 0
	uint16_t maxPinchedParticleIndex;	// Offset: 426 Unk: 0
	uint32_t maxCollisionPairs;	// Offset: 428 Unk: 0
	hclVirtualCollisionPointsData virtualCollisionPointsData;	// Offset: 432 Unk: 0
};

// Class No.15
// Original: T*<hclSimClothData> Mapped to c type : hclSimClothData


// Class No.14
// Mapped to c type: hkArray<T*, hkContainerHeapAllocator>
template<class tT=T*<hclSimClothData>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.13
// Mapped to c type: hclClothData
class hclClothData : public hkReferencedObject {
	std::string name;	// Offset: 24 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> simClothDatas;	// Offset: 32 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> bufferDefinitions;	// Offset: 48 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> transformSetDefinitions;	// Offset: 64 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> operators;	// Offset: 80 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> clothStateDatas;	// Offset: 96 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> stateTransitions;	// Offset: 112 Unk: 0
	hkArray<T*, hkContainerHeapAllocator> actions;	// Offset: 128 Unk: 0
	bool generatedAtRuntime;	// Offset: 144 Unk: 0
	hclClothData::Platform targetPlatform;	// Offset: 148 Unk: 0
};

// Class No.12
// Original: char Mapped to c type : uint8_t


// Class No.11
// Mapped to c type: hkReferencedObject
class hkReferencedObject : public hkBaseObject {
	uint64_t sizeAndFlags;	// Offset: 8 Unk: 0
	uint64_t refCount;	// Offset: 16 Unk: 0
};

// Class No.10
// Original: char* Mapped to c type : std::string


// Class No.9
// Original: hkRefVariant Mapped to c type : hkReferencedObject


// Class No.8
// Original: hkStringPtr Mapped to c type : std::string


// Class No.7
// Mapped to c type: int
class int {
};

// Class No.6
// Mapped to c type: void
class void;	// [Undefined]

// Class No.5
// Original: T*<void> Mapped to c type : void*


// Class No.4
// Mapped to c type: hkContainerHeapAllocator
class hkContainerHeapAllocator;	// [Undefined]

// Class No.3
// Mapped to c type: hkRootLevelContainer::NamedVariant
class hkRootLevelContainer::NamedVariant {
	std::string name;	// Offset: 0 Unk: 0
	std::string className;	// Offset: 8 Unk: 0
	hkReferencedObject variant;	// Offset: 16 Unk: 0
};

// Class No.2
// Original: hkArray<hkRootLevelContainer::NamedVariant, hkContainerHeapAllocator> Mapped to c type : std::vector<hkRootLevelContainer::NamedVariant>


// Class No.1
// Mapped to c type: hkRootLevelContainer
class hkRootLevelContainer {
	std::vector<hkRootLevelContainer::NamedVariant> namedVariants;	// Offset: 0 Unk: 0
};

