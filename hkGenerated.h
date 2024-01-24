#pragma once

#include "hkBaseCTypes.h"
// Class No.191
// Mapped to c type: hkArray
template<class tT=hkArray<int, hkContainerHeapAllocator>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.190
// Mapped to c type: hkArray
template<class tT=int, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.189
// Mapped to c type: hclStateDependencyGraph::Branch
class hclStateDependencyGraph::Branch {
	int branchId;	// Offset: 0 Unk: 0
	hkArray stateOperatorIndices;	// Offset: 8 Unk: 0
	hkArray parentBranches;	// Offset: 24 Unk: 0
	hkArray childBranches;	// Offset: 40 Unk: 0
};

// Class No.188
// Mapped to c type: hkArray
template<class tT=hclStateDependencyGraph::Branch, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.187
// Mapped to c type: hclStretchLinkConstraintSetMx::Single
class hclStretchLinkConstraintSetMx::Single;	// [Undefined]

// Class No.186
// Mapped to c type: hkArray
template<class tT=hclStretchLinkConstraintSetMx::Single, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.185
// Mapped to c type: hclStretchLinkConstraintSetMx::Batch
class hclStretchLinkConstraintSetMx::Batch {
	std::array<hkReal, 4> restLengths;	// Offset: 0 Unk: 0
	std::array<hkReal, 4> stiffnesses;	// Offset: 16 Unk: 0
	std::array<hkUint16, 4> particlesA;	// Offset: 32 Unk: 0
	std::array<hkUint16, 4> particlesB;	// Offset: 40 Unk: 0
};

// Class No.184
// Mapped to c type: hkArray
template<class tT=hclStretchLinkConstraintSetMx::Batch, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.183
// Mapped to c type: hclStretchLinkConstraintSetMx
class hclStretchLinkConstraintSetMx : public hclConstraintSet {
	hkArray batches;	// Offset: 40 Unk: 0
	hkArray singles;	// Offset: 56 Unk: 0
};

// Class No.182
// Mapped to c type: std::array<hkUint16, 4>
template<class tT=hkUint16, class vN=4>
class T[N] {
};

// Class No.181
// Mapped to c type: std::array<hkReal, 4>
template<class tT=hkReal, class vN=4>
class T[N] {
};

// Class No.180
// Mapped to c type: hkHandle
template<class tTYPE=hkUint32, class vINVALID_VALUE=2147483647>
class hkHandle {
	hkUint32 value;	// Offset: 0 Unk: 0
};

// Class No.179
// Mapped to c type: hclStandardLinkConstraintSetMx::Single
class hclStandardLinkConstraintSetMx::Single;	// [Undefined]

// Class No.178
// Mapped to c type: hkArray
template<class tT=hclStandardLinkConstraintSetMx::Single, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.177
// Mapped to c type: hclStandardLinkConstraintSetMx::Batch
class hclStandardLinkConstraintSetMx::Batch {
	std::array<hkReal, 4> restLengths;	// Offset: 0 Unk: 0
	std::array<hkReal, 4> stiffnessesA;	// Offset: 16 Unk: 0
	std::array<hkReal, 4> stiffnessesB;	// Offset: 32 Unk: 0
	std::array<hkUint16, 4> particlesA;	// Offset: 48 Unk: 0
	std::array<hkUint16, 4> particlesB;	// Offset: 56 Unk: 0
};

// Class No.176
// Mapped to c type: hkArray
template<class tT=hclStandardLinkConstraintSetMx::Batch, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.175
// Mapped to c type: hclStandardLinkConstraintSetMx
class hclStandardLinkConstraintSetMx : public hclConstraintSet {
	hkArray batches;	// Offset: 40 Unk: 0
	hkArray singles;	// Offset: 56 Unk: 0
};

// Class No.174
// Mapped to c type: hkArray
template<class tT=hkVector4, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.173
// Mapped to c type: hclStateDependencyGraph
class hclStateDependencyGraph : public hkReferencedObject {
	hkArray branches;	// Offset: 24 Unk: 0
	hkArray rootBranchIds;	// Offset: 40 Unk: 0
	hkArray children;	// Offset: 56 Unk: 0
	hkArray parents;	// Offset: 72 Unk: 0
	hkBool multiThreadable;	// Offset: 88 Unk: 0
};

// Class No.172
// Mapped to c type: hclStateDependencyGraph*
template<class tT=hclStateDependencyGraph>
class T* {
};

// Class No.171
// Mapped to c type: hclGatherAllVerticesOperator
class hclGatherAllVerticesOperator : public hclOperator {
	hkArray vertexInputFromVertexOutput;	// Offset: 72 Unk: 0
	hkUint32 inputBufferIdx;	// Offset: 88 Unk: 0
	hkUint32 outputBufferIdx;	// Offset: 92 Unk: 0
	hkBool gatherNormals;	// Offset: 96 Unk: 0
	hkBool partialGather;	// Offset: 97 Unk: 0
};

// Class No.170
// Mapped to c type: hkMatrix4Impl
template<class tFT=float>
class hkMatrix4Impl {
	hkVector4f col0;	// Offset: 0 Unk: 0
	hkVector4f col1;	// Offset: 16 Unk: 0
	hkVector4f col2;	// Offset: 32 Unk: 0
	hkVector4f col3;	// Offset: 48 Unk: 0
};

// Class No.169
// Mapped to c type: hkMatrix4f
class hkMatrix4f : public hkMatrix4Impl<float> {
};

// Class No.168
// Mapped to c type: hclSimpleMeshBoneDeformOperator::TriangleBonePair
class hclSimpleMeshBoneDeformOperator::TriangleBonePair {
	hkUint16 boneOffset;	// Offset: 0 Unk: 0
	hkUint16 triangleOffset;	// Offset: 2 Unk: 0
};

// Class No.167
// Mapped to c type: hkArray
template<class tT=hclSimpleMeshBoneDeformOperator::TriangleBonePair, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.166
// Mapped to c type: hclSimpleMeshBoneDeformOperator
class hclSimpleMeshBoneDeformOperator : public hclOperator {
	hkUint32 inputBufferIdx;	// Offset: 72 Unk: 0
	hkUint32 outputTransformSetIdx;	// Offset: 76 Unk: 0
	hkArray triangleBonePairs;	// Offset: 80 Unk: 0
	hkArray localBoneTransforms;	// Offset: 96 Unk: 0
};

// Class No.165
// Mapped to c type: hkArray
template<class tT=hkInt32, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.164
// Mapped to c type: hclSimulateOperator::Config
class hclSimulateOperator::Config {
	hkStringPtr name;	// Offset: 0 Unk: 0
	hkArray constraintExecution;	// Offset: 8 Unk: 0
	hkArray instanceCollidablesUsed;	// Offset: 24 Unk: 0
	hkUint8 subSteps;	// Offset: 40 Unk: 0
	hkUint8 numberOfSolveIterations;	// Offset: 41 Unk: 0
	hkBool useAllInstanceCollidables;	// Offset: 42 Unk: 0
	hkBool adaptConstraintStiffness;	// Offset: 43 Unk: 0
};

// Class No.163
// Mapped to c type: hkArray
template<class tT=hclSimulateOperator::Config, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.162
// Mapped to c type: hclSimulateOperator
class hclSimulateOperator : public hclOperator {
	hkUint32 simClothIndex;	// Offset: 72 Unk: 0
	hkArray simulateOpConfigs;	// Offset: 80 Unk: 0
};

// Class No.161
// Mapped to c type: hclMoveParticlesOperator::VertexParticlePair
class hclMoveParticlesOperator::VertexParticlePair {
	hkUint16 vertexIndex;	// Offset: 0 Unk: 0
	hkUint16 particleIndex;	// Offset: 2 Unk: 0
};

// Class No.160
// Mapped to c type: hkArray
template<class tT=hclMoveParticlesOperator::VertexParticlePair, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.159
// Mapped to c type: hclMoveParticlesOperator
class hclMoveParticlesOperator : public hclOperator {
	hkArray vertexParticlePairs;	// Offset: 72 Unk: 0
	hkUint32 simClothIndex;	// Offset: 88 Unk: 0
	hkUint32 refBufferIdx;	// Offset: 92 Unk: 0
};

// Class No.158
// Mapped to c type: hkBitFieldStorage
template<class tStorage=hkArray<hkUint32, hkContainerHeapAllocator>>
class hkBitFieldStorage {
	hkArray words;	// Offset: 0 Unk: 0
	int numBits;	// Offset: 16 Unk: 0
};

// Class No.157
// Mapped to c type: hkBitFieldBase
template<class tStorage=hkBitFieldStorage<hkArray>>
class hkBitFieldBase {
	hkBitFieldStorage storage;	// Offset: 0 Unk: 0
};

// Class No.156
// Mapped to c type: hkBitField
class hkBitField : public hkBitFieldBase<hkBitFieldStorage> {
};

// Class No.155
// Mapped to c type: std::array<hkInt16, 4>
template<class tT=hkInt16, class vN=4>
class T[N] {
};

// Class No.154
// Mapped to c type: hkPackedVector3
class hkPackedVector3 {
	std::array<hkInt16, 4> values;	// Offset: 0 Unk: 3
};

// Class No.153
// Mapped to c type: std::array<hkPackedVector3, 16>
template<class tT=hkPackedVector3, class vN=16>
class T[N] {
};

// Class No.152
// Mapped to c type: std::array<hkVector4, 16>
template<class tT=hkVector4, class vN=16>
class T[N] {
};

// Class No.151
// Mapped to c type: std::array<hkUint16, 16>
template<class tT=hkUint16, class vN=16>
class T[N] {
};

// Class No.150
// Mapped to c type: std::array<hkUint16, 8>
template<class tT=hkUint16, class vN=8>
class T[N] {
};

// Class No.149
// Mapped to c type: hclTransformSetUsage::TransformTracker
class hclTransformSetUsage::TransformTracker {
	hkBitField read;	// Offset: 0 Unk: 0
	hkBitField readBeforeWrite;	// Offset: 24 Unk: 0
	hkBitField written;	// Offset: 48 Unk: 0
};

// Class No.148
// Mapped to c type: hkArray
template<class tT=hclTransformSetUsage::TransformTracker, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.147
// Mapped to c type: std::array<hkUint8, 2>
template<class tT=hkUint8, class vN=2>
class T[N] {
};

// Class No.146
// Mapped to c type: hclTransformSetUsage
class hclTransformSetUsage {
	std::array<hkUint8, 2> perComponentFlags;	// Offset: 0 Unk: 0
	hkArray perComponentTransformTrackers;	// Offset: 8 Unk: 0
};

// Class No.145
// Mapped to c type: std::array<hkUint8, 4>
template<class tT=hkUint8, class vN=4>
class T[N] {
};

// Class No.144
// Mapped to c type: hclBufferUsage
class hclBufferUsage {
	std::array<hkUint8, 4> perComponentFlags;	// Offset: 0 Unk: 0
	hkBool trianglesRead;	// Offset: 4 Unk: 0
};

// Class No.143
// Mapped to c type: hclBoneSpaceDeformer::OneBlendEntryBlock
class hclBoneSpaceDeformer::OneBlendEntryBlock {
	std::array<hkUint16, 16> vertexIndices;	// Offset: 0 Unk: 0
	std::array<hkUint16, 16> boneIndices;	// Offset: 32 Unk: 0
};

// Class No.142
// Mapped to c type: hkArray
template<class tT=hclBoneSpaceDeformer::OneBlendEntryBlock, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.141
// Mapped to c type: hclBoneSpaceDeformer::TwoBlendEntryBlock
class hclBoneSpaceDeformer::TwoBlendEntryBlock {
	std::array<hkUint16, 8> vertexIndices;	// Offset: 0 Unk: 0
	std::array<hkUint16, 16> boneIndices;	// Offset: 16 Unk: 0
};

// Class No.140
// Mapped to c type: hkArray
template<class tT=hclBoneSpaceDeformer::TwoBlendEntryBlock, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.139
// Mapped to c type: hclBoneSpaceDeformer::ThreeBlendEntryBlock
class hclBoneSpaceDeformer::ThreeBlendEntryBlock;	// [Undefined]

// Class No.138
// Mapped to c type: hkArray
template<class tT=hclBoneSpaceDeformer::ThreeBlendEntryBlock, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.137
// Mapped to c type: hclBoneSpaceDeformer::FourBlendEntryBlock
class hclBoneSpaceDeformer::FourBlendEntryBlock;	// [Undefined]

// Class No.136
// Mapped to c type: hkArray
template<class tT=hclBoneSpaceDeformer::FourBlendEntryBlock, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.135
// Mapped to c type: hclClothState::TransformSetAccess
class hclClothState::TransformSetAccess {
	hkUint32 transformSetIndex;	// Offset: 0 Unk: 0
	hclTransformSetUsage transformSetUsage;	// Offset: 8 Unk: 0
};

// Class No.134
// Mapped to c type: hkArray
template<class tT=hclClothState::TransformSetAccess, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.133
// Mapped to c type: hclClothState::BufferAccess
class hclClothState::BufferAccess {
	hkUint32 bufferIndex;	// Offset: 0 Unk: 0
	hclBufferUsage bufferUsage;	// Offset: 4 Unk: 0
	hkUint32 shadowBufferIndex;	// Offset: 12 Unk: 0
};

// Class No.132
// Mapped to c type: hkArray
template<class tT=hclClothState::BufferAccess, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.131
// Mapped to c type: hclBoneSpaceDeformer
class hclBoneSpaceDeformer {
	hkArray fourBlendEntries;	// Offset: 0 Unk: 0
	hkArray threeBlendEntries;	// Offset: 16 Unk: 0
	hkArray twoBlendEntries;	// Offset: 32 Unk: 0
	hkArray oneBlendEntries;	// Offset: 48 Unk: 0
	hkArray controlBytes;	// Offset: 64 Unk: 0
	hkUint16 startVertexIndex;	// Offset: 80 Unk: 0
	hkUint16 endVertexIndex;	// Offset: 82 Unk: 0
	hkBool partialWrite;	// Offset: 84 Unk: 0
};

// Class No.130
// Mapped to c type: hclBoneSpaceDeformer::LocalBlockUnpackedPN
class hclBoneSpaceDeformer::LocalBlockUnpackedPN;	// [Undefined]

// Class No.129
// Mapped to c type: hkArray
template<class tT=hclBoneSpaceDeformer::LocalBlockUnpackedPN, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.128
// Mapped to c type: hclBoneSpaceDeformer::LocalBlockPN
class hclBoneSpaceDeformer::LocalBlockPN {
	std::array<hkVector4, 16> localPosition;	// Offset: 0 Unk: 0
	std::array<hkPackedVector3, 16> localNormal;	// Offset: 256 Unk: 0
};

// Class No.127
// Mapped to c type: hkArray
template<class tT=hclBoneSpaceDeformer::LocalBlockPN, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.126
// Mapped to c type: hclBoneSpaceSkinOperator
class hclBoneSpaceSkinOperator : public hclOperator {
	hkArray transformSubset;	// Offset: 72 Unk: 0
	hkUint32 outputBufferIndex;	// Offset: 88 Unk: 0
	hkUint32 transformSetIndex;	// Offset: 92 Unk: 0
	hclBoneSpaceDeformer boneSpaceDeformer;	// Offset: 96 Unk: 0
};

// Class No.125
// Mapped to c type: hclBoneSpaceSkinPNOperator
class hclBoneSpaceSkinPNOperator : public hclBoneSpaceSkinOperator {
	hkArray localPNs;	// Offset: 184 Unk: 0
	hkArray localUnpackedPNs;	// Offset: 200 Unk: 0
};

// Class No.124
// Mapped to c type: hclBufferLayout::SlotFlags
class hclBufferLayout::SlotFlags;	// [Undefined]

// Class No.123
// Mapped to c type: hkEnum
template<class tENUM=hclBufferLayout::SlotFlags, class tSTORAGE=hkUint8>
class hkEnum {
	hkUint8 storage;	// Offset: 0 Unk: 0
};

// Class No.122
// Mapped to c type: hclRuntimeConversionInfo::VectorConversion
class hclRuntimeConversionInfo::VectorConversion;	// [Undefined]

// Class No.121
// Mapped to c type: hkEnum
template<class tENUM=hclRuntimeConversionInfo::VectorConversion, class tSTORAGE=hkUint8>
class hkEnum {
	hkUint8 storage;	// Offset: 0 Unk: 0
};

// Class No.120
// Mapped to c type: hclBufferLayout::TriangleFormat
class hclBufferLayout::TriangleFormat;	// [Undefined]

// Class No.119
// Mapped to c type: hkEnum
template<class tENUM=hclBufferLayout::TriangleFormat, class tSTORAGE=hkUint8>
class hkEnum {
	hkUint8 storage;	// Offset: 0 Unk: 0
};

// Class No.118
// Mapped to c type: hclBufferLayout::Slot
class hclBufferLayout::Slot {
	hkEnum flags;	// Offset: 0 Unk: 0
	hkUint8 stride;	// Offset: 1 Unk: 0
};

// Class No.117
// Mapped to c type: std::array<hclBufferLayout::Slot, 4>
template<class tT=hclBufferLayout::Slot, class vN=4>
class T[N] {
};

// Class No.116
// Mapped to c type: hclBufferLayout::BufferElement
class hclBufferLayout::BufferElement {
	hkEnum vectorConversion;	// Offset: 0 Unk: 0
	hkUint8 vectorSize;	// Offset: 1 Unk: 0
	hkUint8 slotId;	// Offset: 2 Unk: 0
	hkUint8 slotStart;	// Offset: 3 Unk: 0
};

// Class No.115
// Mapped to c type: std::array<hclBufferLayout::BufferElement, 4>
template<class tT=hclBufferLayout::BufferElement, class vN=4>
class T[N] {
};

// Class No.114
// Mapped to c type: hclBufferLayout
class hclBufferLayout {
	std::array<hclBufferLayout::BufferElement, 4> elementsLayout;	// Offset: 0 Unk: 0
	std::array<hclBufferLayout::Slot, 4> slots;	// Offset: 16 Unk: 0
	hkUint8 numSlots;	// Offset: 24 Unk: 0
	hkEnum triangleFormat;	// Offset: 25 Unk: 0
};

// Class No.113
// Mapped to c type: hclScratchBufferDefinition
class hclScratchBufferDefinition : public hclBufferDefinition {
	hkArray triangleIndices;	// Offset: 88 Unk: 0
	hkBool storeNormals;	// Offset: 104 Unk: 0
	hkBool storeTangentsAndBiTangents;	// Offset: 105 Unk: 0
};

// Class No.112
// Mapped to c type: unsigned char
class unsigned char {
};

// Class No.111
// Mapped to c type: signed char
class signed char {
};

// Class No.110
// Mapped to c type: hclVirtualCollisionPointsData::TriangleFanLandscape
class hclVirtualCollisionPointsData::TriangleFanLandscape;	// [Undefined]

// Class No.109
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::TriangleFanLandscape, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.108
// Mapped to c type: hclVirtualCollisionPointsData::EdgeFanLandscape
class hclVirtualCollisionPointsData::EdgeFanLandscape;	// [Undefined]

// Class No.107
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::EdgeFanLandscape, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.106
// Mapped to c type: hclVirtualCollisionPointsData::TriangleFan
class hclVirtualCollisionPointsData::TriangleFan;	// [Undefined]

// Class No.105
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::TriangleFan, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.104
// Mapped to c type: hclVirtualCollisionPointsData::TriangleFanSection
class hclVirtualCollisionPointsData::TriangleFanSection;	// [Undefined]

// Class No.103
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::TriangleFanSection, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.102
// Mapped to c type: hclVirtualCollisionPointsData::EdgeFan
class hclVirtualCollisionPointsData::EdgeFan;	// [Undefined]

// Class No.101
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::EdgeFan, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.100
// Mapped to c type: hclVirtualCollisionPointsData::EdgeFanSection
class hclVirtualCollisionPointsData::EdgeFanSection;	// [Undefined]

// Class No.99
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::EdgeFanSection, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.98
// Mapped to c type: hclVirtualCollisionPointsData::BarycentricPair
class hclVirtualCollisionPointsData::BarycentricPair;	// [Undefined]

// Class No.97
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::BarycentricPair, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.96
// Mapped to c type: hclVirtualCollisionPointsData::BarycentricDictionaryEntry
class hclVirtualCollisionPointsData::BarycentricDictionaryEntry;	// [Undefined]

// Class No.95
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::BarycentricDictionaryEntry, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.94
// Mapped to c type: hclVirtualCollisionPointsData::Block
class hclVirtualCollisionPointsData::Block;	// [Undefined]

// Class No.93
// Mapped to c type: hkArray
template<class tT=hclVirtualCollisionPointsData::Block, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.92
// Mapped to c type: unsigned short
class unsigned short {
};

// Class No.91
// Mapped to c type: hkInt8
class hkInt8 : public signed char {
};

// Class No.90
// Mapped to c type: hkMatrix4
class hkMatrix4 : public hkMatrix4f {
};

// Class No.89
// Mapped to c type: hkArray
template<class tT=hkMatrix4, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.88
// Mapped to c type: hkInt32
class hkInt32 : public int {
};

// Class No.87
// Mapped to c type: hkVector4
class hkVector4 : public hkVector4f {
};

// Class No.86
// Mapped to c type: hclVirtualCollisionPointsData
class hclVirtualCollisionPointsData {
	hkArray blocks;	// Offset: 0 Unk: 0
	hkUint16 numVCPoints;	// Offset: 16 Unk: 0
	hkArray landscapeParticlesBlockIndex;	// Offset: 24 Unk: 0
	hkUint16 numLandscapeVCPoints;	// Offset: 40 Unk: 0
	hkArray edgeBarycentricsDictionary;	// Offset: 48 Unk: 0
	hkArray edgeDictionaryEntries;	// Offset: 64 Unk: 0
	hkArray triangleBarycentricsDictionary;	// Offset: 80 Unk: 0
	hkArray triangleDictionaryEntries;	// Offset: 96 Unk: 0
	hkArray edges;	// Offset: 112 Unk: 0
	hkArray edgeFans;	// Offset: 128 Unk: 0
	hkArray triangles;	// Offset: 144 Unk: 0
	hkArray triangleFans;	// Offset: 160 Unk: 0
	hkArray edgesLandscape;	// Offset: 176 Unk: 0
	hkArray edgeFansLandscape;	// Offset: 192 Unk: 0
	hkArray trianglesLandscape;	// Offset: 208 Unk: 0
	hkArray triangleFansLandscape;	// Offset: 224 Unk: 0
	hkArray edgeFanIndices;	// Offset: 240 Unk: 0
	hkArray triangleFanIndices;	// Offset: 256 Unk: 0
	hkArray edgeFanIndicesLandscape;	// Offset: 272 Unk: 0
	hkArray triangleFanIndicesLandscape;	// Offset: 288 Unk: 0
};

// Class No.85
// Mapped to c type: hclSimClothData::CollidablePinchingData
class hclSimClothData::CollidablePinchingData;	// [Undefined]

// Class No.84
// Mapped to c type: hkArray
template<class tT=hclSimClothData::CollidablePinchingData, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.83
// Mapped to c type: hkArray
template<class tT=hkBool, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.82
// Mapped to c type: hkUint8
class hkUint8 : public unsigned char {
};

// Class No.81
// Mapped to c type: hkArray
template<class tT=hkUint8, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.80
// Mapped to c type: hclSimClothData::LandscapeCollisionData
class hclSimClothData::LandscapeCollisionData {
	hkReal landscapeRadius;	// Offset: 0 Unk: 0
	hkBool enableStuckParticleDetection;	// Offset: 4 Unk: 0
	hkReal stuckParticlesStretchFactorSq;	// Offset: 8 Unk: 0
	hkBool pinchDetectionEnabled;	// Offset: 12 Unk: 0
	hkInt8 pinchDetectionPriority;	// Offset: 13 Unk: 0
	hkReal pinchDetectionRadius;	// Offset: 16 Unk: 0
	hkReal collisionTolerance;	// Offset: 20 Unk: 0
};

// Class No.79
// Mapped to c type: hclSimClothData::TransferMotionData
class hclSimClothData::TransferMotionData {
	hkUint32 transformSetIndex;	// Offset: 0 Unk: 0
	hkUint32 transformIndex;	// Offset: 4 Unk: 0
	hkBool transferTranslationMotion;	// Offset: 8 Unk: 0
	hkReal minTranslationSpeed;	// Offset: 12 Unk: 0
	hkReal maxTranslationSpeed;	// Offset: 16 Unk: 0
	hkReal minTranslationBlend;	// Offset: 20 Unk: 0
	hkReal maxTranslationBlend;	// Offset: 24 Unk: 0
	hkBool transferRotationMotion;	// Offset: 28 Unk: 0
	hkReal minRotationSpeed;	// Offset: 32 Unk: 0
	hkReal maxRotationSpeed;	// Offset: 36 Unk: 0
	hkReal minRotationBlend;	// Offset: 40 Unk: 0
	hkReal maxRotationBlend;	// Offset: 44 Unk: 0
};

// Class No.78
// Mapped to c type: hkArray
template<class tT=hkUint32, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.77
// Mapped to c type: hclCollidable
class hclCollidable;	// [Undefined]

// Class No.76
// Mapped to c type: hclCollidable*
template<class tT=hclCollidable>
class T*;	// [Undefined]

// Class No.75
// Mapped to c type: hkArray
template<class tT=T*<hclCollidable>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.74
// Mapped to c type: hclSimClothData::CollidableTransformMap
class hclSimClothData::CollidableTransformMap {
	hkInt32 transformSetIndex;	// Offset: 0 Unk: 0
	hkArray transformIndices;	// Offset: 8 Unk: 0
	hkArray offsets;	// Offset: 24 Unk: 0
};

// Class No.73
// Mapped to c type: hclConstraintSet
class hclConstraintSet : public hkReferencedObject {
	hkStringPtr name;	// Offset: 24 Unk: 0
	hkHandle constraintId;	// Offset: 32 Unk: 0
	unsigned int type;	// Offset: 36 Unk: 0
};

// Class No.72
// Mapped to c type: hclConstraintSet*
template<class tT=hclConstraintSet>
class T* {
};

// Class No.71
// Mapped to c type: hkArray
template<class tT=T*<hclConstraintSet>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.70
// Mapped to c type: hclSimClothPose
class hclSimClothPose : public hkReferencedObject {
	hkStringPtr name;	// Offset: 24 Unk: 0
	hkArray positions;	// Offset: 32 Unk: 0
};

// Class No.69
// Mapped to c type: hclSimClothPose*
template<class tT=hclSimClothPose>
class T* {
};

// Class No.68
// Mapped to c type: hkArray
template<class tT=T*<hclSimClothPose>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.67
// Mapped to c type: hkArray
template<class tT=unsigned int, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.66
// Mapped to c type: hkUint16
class hkUint16 : public unsigned short {
};

// Class No.65
// Mapped to c type: hkArray
template<class tT=hkUint16, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.64
// Mapped to c type: hclSimClothData::ParticleData
class hclSimClothData::ParticleData {
	hkReal mass;	// Offset: 0 Unk: 0
	hkReal invMass;	// Offset: 4 Unk: 0
	hkReal radius;	// Offset: 8 Unk: 0
	hkReal friction;	// Offset: 12 Unk: 0
};

// Class No.63
// Mapped to c type: hkArray
template<class tT=hclSimClothData::ParticleData, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.62
// Mapped to c type: hclSimClothData::OverridableSimulationInfo
class hclSimClothData::OverridableSimulationInfo {
	hkVector4 gravity;	// Offset: 0 Unk: 0
	hkReal globalDampingPerSecond;	// Offset: 16 Unk: 0
};

// Class No.61
// Mapped to c type: float
class float {
};

// Class No.60
// Mapped to c type: hkQuaternionf
class hkQuaternionf {
	hkVector4f vec;	// Offset: 0 Unk: 0
};

// Class No.59
// Mapped to c type: hkVector4f
class hkVector4f {
};

// Class No.58
// Mapped to c type: hkQsTransformf
class hkQsTransformf {
	hkVector4f translation;	// Offset: 0 Unk: 0
	hkQuaternionf rotation;	// Offset: 16 Unk: 0
	hkVector4f scale;	// Offset: 32 Unk: 0
};

// Class No.57
// Mapped to c type: short
class short {
};

// Class No.56
// Mapped to c type: hkaSkeleton::Partition
class hkaSkeleton::Partition;	// [Undefined]

// Class No.55
// Mapped to c type: hkArray
template<class tT=hkaSkeleton::Partition, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.54
// Mapped to c type: hkaSkeleton::LocalFrameOnBone
class hkaSkeleton::LocalFrameOnBone;	// [Undefined]

// Class No.53
// Mapped to c type: hkArray
template<class tT=hkaSkeleton::LocalFrameOnBone, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.52
// Mapped to c type: hkArray
template<class tT=hkStringPtr, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.51
// Mapped to c type: hkReal
class hkReal : public float {
};

// Class No.50
// Mapped to c type: hkArray
template<class tT=hkReal, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.49
// Mapped to c type: hkQsTransform
class hkQsTransform : public hkQsTransformf {
};

// Class No.48
// Mapped to c type: hkArray
template<class tT=hkQsTransform, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.47
// Mapped to c type: hkaBone
class hkaBone {
	hkStringPtr name;	// Offset: 0 Unk: 0
	hkBool lockTranslation;	// Offset: 8 Unk: 0
};

// Class No.46
// Mapped to c type: hkArray
template<class tT=hkaBone, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.45
// Mapped to c type: hkInt16
class hkInt16 : public short {
};

// Class No.44
// Mapped to c type: hkArray
template<class tT=hkInt16, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.43
// Mapped to c type: hkaSkeleton
class hkaSkeleton : public hkReferencedObject {
	hkStringPtr name;	// Offset: 24 Unk: 0
	hkArray parentIndices;	// Offset: 32 Unk: 0
	hkArray bones;	// Offset: 48 Unk: 0
	hkArray referencePose;	// Offset: 64 Unk: 0
	hkArray referenceFloats;	// Offset: 80 Unk: 0
	hkArray floatSlots;	// Offset: 96 Unk: 0
	hkArray localFrames;	// Offset: 112 Unk: 0
	hkArray partitions;	// Offset: 128 Unk: 0
};

// Class No.42
// Mapped to c type: unsigned int
class unsigned int {
};

// Class No.41
// Mapped to c type: unsigned long long
class unsigned long long {
};

// Class No.40
// Mapped to c type: hkUlong
class hkUlong : public unsigned long long {
};

// Class No.39
// Mapped to c type: hkBaseObject
class hkBaseObject {
};

// Class No.38
// Mapped to c type: hkUint32
class hkUint32 : public unsigned int {
};

// Class No.37
// Mapped to c type: hclClothData::Platform
class hclClothData::Platform;	// [Undefined]

// Class No.36
// Mapped to c type: hkEnum
template<class tENUM=hclClothData::Platform, class tSTORAGE=hkUint32>
class hkEnum {
	hkUint32 storage;	// Offset: 0 Unk: 0
};

// Class No.35
// Mapped to c type: hkBool
class hkBool {
	char bool;	// Offset: 0 Unk: 0
};

// Class No.34
// Mapped to c type: hclAction
class hclAction;	// [Undefined]

// Class No.33
// Mapped to c type: hclAction*
template<class tT=hclAction>
class T*;	// [Undefined]

// Class No.32
// Mapped to c type: hkArray
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
// Mapped to c type: hclStateTransition*
template<class tT=hclStateTransition>
class T*;	// [Undefined]

// Class No.29
// Mapped to c type: hkArray
template<class tT=T*<hclStateTransition>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.28
// Mapped to c type: hclClothState
class hclClothState : public hkReferencedObject {
	hkStringPtr name;	// Offset: 24 Unk: 0
	hkArray operators;	// Offset: 32 Unk: 0
	hkArray usedBuffers;	// Offset: 48 Unk: 0
	hkArray usedTransformSets;	// Offset: 64 Unk: 0
	hkArray usedSimCloths;	// Offset: 80 Unk: 0
	hclStateDependencyGraph* dependencyGraph;	// Offset: 96 Unk: 0
};

// Class No.27
// Mapped to c type: hclClothState*
template<class tT=hclClothState>
class T* {
};

// Class No.26
// Mapped to c type: hkArray
template<class tT=T*<hclClothState>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.25
// Mapped to c type: hclOperator
class hclOperator : public hkReferencedObject {
	hkStringPtr name;	// Offset: 24 Unk: 0
	unsigned int operatorID;	// Offset: 32 Unk: 0
	unsigned int type;	// Offset: 36 Unk: 0
	hkArray usedBuffers;	// Offset: 40 Unk: 0
	hkArray usedTransformSets;	// Offset: 56 Unk: 0
};

// Class No.24
// Mapped to c type: hclOperator*
template<class tT=hclOperator>
class T* {
};

// Class No.23
// Mapped to c type: hkArray
template<class tT=T*<hclOperator>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.22
// Mapped to c type: hclTransformSetDefinition
class hclTransformSetDefinition : public hkReferencedObject {
	hkStringPtr name;	// Offset: 24 Unk: 0
	hkInt32 type;	// Offset: 32 Unk: 0
	hkUint32 numTransforms;	// Offset: 36 Unk: 0
};

// Class No.21
// Mapped to c type: hclTransformSetDefinition*
template<class tT=hclTransformSetDefinition>
class T* {
};

// Class No.20
// Mapped to c type: hkArray
template<class tT=T*<hclTransformSetDefinition>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.19
// Mapped to c type: hclBufferDefinition
class hclBufferDefinition : public hkReferencedObject {
	hkStringPtr meshName;	// Offset: 24 Unk: 0
	hkStringPtr bufferName;	// Offset: 32 Unk: 0
	hkInt32 type;	// Offset: 40 Unk: 0
	hkInt32 subType;	// Offset: 44 Unk: 0
	hkUint32 numVertices;	// Offset: 48 Unk: 0
	hkUint32 numTriangles;	// Offset: 52 Unk: 0
	hclBufferLayout bufferLayout;	// Offset: 56 Unk: 0
};

// Class No.18
// Mapped to c type: hclBufferDefinition*
template<class tT=hclBufferDefinition>
class T* {
};

// Class No.17
// Mapped to c type: hkArray
template<class tT=T*<hclBufferDefinition>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.16
// Mapped to c type: hclSimClothData
class hclSimClothData : public hkReferencedObject {
	hkStringPtr name;	// Offset: 24 Unk: 0
	hclSimClothData::OverridableSimulationInfo simulationInfo;	// Offset: 32 Unk: 0
	hkArray particleDatas;	// Offset: 64 Unk: 0
	hkArray fixedParticles;	// Offset: 80 Unk: 0
	hkBool doNormals;	// Offset: 96 Unk: 0
	hkArray simOpIds;	// Offset: 104 Unk: 0
	hkArray simClothPoses;	// Offset: 120 Unk: 0
	hkArray staticConstraintSets;	// Offset: 136 Unk: 0
	hkArray antiPinchConstraintSets;	// Offset: 152 Unk: 0
	hclSimClothData::CollidableTransformMap collidableTransformMap;	// Offset: 168 Unk: 0
	hkArray perInstanceCollidables;	// Offset: 208 Unk: 0
	hkReal maxParticleRadius;	// Offset: 224 Unk: 0
	hkArray staticCollisionMasks;	// Offset: 232 Unk: 0
	hkArray actions;	// Offset: 248 Unk: 0
	hkReal totalMass;	// Offset: 264 Unk: 0
	hclSimClothData::TransferMotionData transferMotionData;	// Offset: 268 Unk: 0
	hkBool transferMotionEnabled;	// Offset: 316 Unk: 0
	hkBool landscapeCollisionEnabled;	// Offset: 317 Unk: 0
	hclSimClothData::LandscapeCollisionData landscapeCollisionData;	// Offset: 320 Unk: 0
	hkUint32 numLandscapeCollidableParticles;	// Offset: 344 Unk: 0
	hkArray triangleIndices;	// Offset: 352 Unk: 0
	hkArray triangleFlips;	// Offset: 368 Unk: 0
	hkBool pinchDetectionEnabled;	// Offset: 384 Unk: 0
	hkArray perParticlePinchDetectionEnabledFlags;	// Offset: 392 Unk: 0
	hkArray collidablePinchingDatas;	// Offset: 408 Unk: 0
	hkUint16 minPinchedParticleIndex;	// Offset: 424 Unk: 0
	hkUint16 maxPinchedParticleIndex;	// Offset: 426 Unk: 0
	hkUint32 maxCollisionPairs;	// Offset: 428 Unk: 0
	hclVirtualCollisionPointsData virtualCollisionPointsData;	// Offset: 432 Unk: 0
};

// Class No.15
// Mapped to c type: hclSimClothData*
template<class tT=hclSimClothData>
class T* {
};

// Class No.14
// Mapped to c type: hkArray
template<class tT=T*<hclSimClothData>, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.13
// Mapped to c type: hclClothData
class hclClothData : public hkReferencedObject {
	hkStringPtr name;	// Offset: 24 Unk: 0
	hkArray simClothDatas;	// Offset: 32 Unk: 0
	hkArray bufferDefinitions;	// Offset: 48 Unk: 0
	hkArray transformSetDefinitions;	// Offset: 64 Unk: 0
	hkArray operators;	// Offset: 80 Unk: 0
	hkArray clothStateDatas;	// Offset: 96 Unk: 0
	hkArray stateTransitions;	// Offset: 112 Unk: 0
	hkArray actions;	// Offset: 128 Unk: 0
	hkBool generatedAtRuntime;	// Offset: 144 Unk: 0
	hkEnum targetPlatform;	// Offset: 148 Unk: 0
};

// Class No.12
// Mapped to c type: char
class char {
};

// Class No.11
// Mapped to c type: hkReferencedObject
class hkReferencedObject : public hkBaseObject {
	hkUlong sizeAndFlags;	// Offset: 8 Unk: 0
	hkUlong refCount;	// Offset: 16 Unk: 0
};

// Class No.10
// Mapped to c type: char*
class char* {
};

// Class No.9
// Mapped to c type: hkRefVariant
class hkRefVariant {
	void* ptr;	// Offset: 0 Unk: 0
};

// Class No.8
// Mapped to c type: hkStringPtr
class hkStringPtr {
	char* stringAndFlag;	// Offset: 0 Unk: 0
};

// Class No.7
// Mapped to c type: int
class int {
};

// Class No.6
// Mapped to c type: void
class void;	// [Undefined]

// Class No.5
// Mapped to c type: void*
template<class tT=void>
class T* {
};

// Class No.4
// Mapped to c type: hkContainerHeapAllocator
class hkContainerHeapAllocator;	// [Undefined]

// Class No.3
// Mapped to c type: hkRootLevelContainer::NamedVariant
class hkRootLevelContainer::NamedVariant {
	hkStringPtr name;	// Offset: 0 Unk: 0
	hkStringPtr className;	// Offset: 8 Unk: 0
	hkRefVariant variant;	// Offset: 16 Unk: 0
};

// Class No.2
// Mapped to c type: hkArray
template<class tT=hkRootLevelContainer::NamedVariant, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.1
// Mapped to c type: hkRootLevelContainer
class hkRootLevelContainer {
	hkArray namedVariants;	// Offset: 0 Unk: 0
};

