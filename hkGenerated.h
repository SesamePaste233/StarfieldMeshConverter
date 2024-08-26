#pragma once

#include "hkBaseCTypes.h"
// Class No.93
// Mapped to c type: std::array<hkInt16, 4>
template<class tT=hkInt16, class vN=4>
class T[N] {
};

// Class No.92
// Mapped to c type: std::array<short, 4>
template<class tT=short, class vN=4>
class T[N] {
};

// Class No.91
// Mapped to c type: hkPackedVector3
class hkPackedVector3 {
	std::array<hkInt16, 4> values;	// Offset: 0 Unk: 3
};

// Class No.90
// Mapped to c type: hkCompressedMassProperties
class hkCompressedMassProperties {
	hkPackedVector3 centerOfMass;	// Offset: 0 Unk: 3
	hkPackedVector3 inertia;	// Offset: 8 Unk: 3
	std::array<short, 4> majorAxisSpace;	// Offset: 16 Unk: 3
	hkReal mass;	// Offset: 24 Unk: 0
	hkReal volume;	// Offset: 28 Unk: 0
};

// Class No.89
// Mapped to c type: hknpShapeMassProperties
class hknpShapeMassProperties : public hkReferencedObject {
	hkCompressedMassProperties compressedMassProperties;	// Offset: 24 Unk: 3
};

// Class No.88
// Mapped to c type: hkRefPtr
template<class tTYPE=hkReferencedObject>
class hkRefPtr {
	void* ptr;	// Offset: 0 Unk: 0
};

// Class No.87
// Mapped to c type: hkRefCountedProperties::Entry
class hkRefCountedProperties::Entry {
	hkRefPtr object;	// Offset: 0 Unk: 0
	hkUint16 key;	// Offset: 8 Unk: 0
	hkUint16 flags;	// Offset: 10 Unk: 0
};

// Class No.86
// Mapped to c type: hkArray
template<class tT=hkRefCountedProperties::Entry, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.85
// Mapped to c type: hknpMassDistribution
class hknpMassDistribution {
	hkVector4 centerOfMassAndVolume;	// Offset: 0 Unk: 0
	hkQuaternion majorAxisSpace;	// Offset: 16 Unk: 0
	hkVector4 inertiaTensor;	// Offset: 32 Unk: 0
};

// Class No.84
// Mapped to c type: std::array<hkUint8, 1>
template<class tT=hkUint8, class vN=1>
class T[N] {
};

// Class No.83
// Mapped to c type: hkInt32
class hkInt32 : public int {
};

// Class No.82
// Mapped to c type: hknpConvexHull::Edge
class hknpConvexHull::Edge {
	hkUint16 faceIndex;	// Offset: 0 Unk: 0
	hkUint8 edgeIndex;	// Offset: 2 Unk: 0
	std::array<hkUint8, 1> padding;	// Offset: 3 Unk: 0
};

// Class No.81
// Mapped to c type: hkRelArray
template<class tT=hknpConvexHull::Edge>
class hkRelArray {
	hkInt32 offset;	// Offset: 0 Unk: 0
	int size;	// Offset: 4 Unk: 0
};

// Class No.80
// Mapped to c type: hkRelArray
template<class tT=hkUint8>
class hkRelArray {
	hkInt32 offset;	// Offset: 0 Unk: 0
	int size;	// Offset: 4 Unk: 0
};

// Class No.79
// Mapped to c type: hknpConvexHull::Face
class hknpConvexHull::Face {
	hkUint16 firstIndex;	// Offset: 0 Unk: 0
	hkUint8 numIndices;	// Offset: 2 Unk: 0
	hkUint8 minHalfAngle;	// Offset: 3 Unk: 0
};

// Class No.78
// Mapped to c type: hkRelArray
template<class tT=hknpConvexHull::Face>
class hkRelArray {
	hkInt32 offset;	// Offset: 0 Unk: 0
	int size;	// Offset: 4 Unk: 0
};

// Class No.77
// Mapped to c type: hkRelArray
template<class tT=hkVector4>
class hkRelArray {
	hkInt32 offset;	// Offset: 0 Unk: 0
	int size;	// Offset: 4 Unk: 0
};

// Class No.76
// Mapped to c type: hkFloat3
class hkFloat3 {
	float x;	// Offset: 0 Unk: 0
	float y;	// Offset: 4 Unk: 0
	float z;	// Offset: 8 Unk: 0
};

// Class No.75
// Mapped to c type: hkRelArray
template<class tT=hkFloat3>
class hkRelArray {
	hkInt32 offset;	// Offset: 0 Unk: 0
	int size;	// Offset: 4 Unk: 0
};

// Class No.74
// Mapped to c type: hkRefCountedProperties
class hkRefCountedProperties : public hkReferencedObject {
	hkArray entries;	// Offset: 24 Unk: 0
};

// Class No.73
// Mapped to c type: hkRefPtr
template<class tTYPE=hkRefCountedProperties>
class hkRefPtr {
	void* ptr;	// Offset: 0 Unk: 0
};

// Class No.72
// Mapped to c type: hknpCollisionDispatchType::Enum
class hknpCollisionDispatchType::Enum;	// [Undefined]

// Class No.71
// Mapped to c type: hkEnum
template<class tENUM=hknpCollisionDispatchType::Enum, class tSTORAGE=hkUint8>
class hkEnum {
	hkUint8 storage;	// Offset: 0 Unk: 0
};

// Class No.70
// Mapped to c type: hknpShapeType::Enum
class hknpShapeType::Enum;	// [Undefined]

// Class No.69
// Mapped to c type: hkEnum
template<class tENUM=hknpShapeType::Enum, class tSTORAGE=hkUint8>
class hkEnum {
	hkUint8 storage;	// Offset: 0 Unk: 0
};

// Class No.68
// Mapped to c type: hkUint16
class hkUint16 : public unsigned short {
};

// Class No.67
// Mapped to c type: hknpShape::FlagsEnum
class hknpShape::FlagsEnum;	// [Undefined]

// Class No.66
// Mapped to c type: hkFlags
template<class tBITS=hknpShape::FlagsEnum, class tSTORAGE=hkUint16>
class hkFlags {
	hkUint16 storage;	// Offset: 0 Unk: 0
};

// Class No.65
// Mapped to c type: hknpConvexHull
class hknpConvexHull {
	hkRelArray vertices;	// Offset: 0 Unk: 0
	hkRelArray planes;	// Offset: 8 Unk: 0
	hkRelArray faces;	// Offset: 16 Unk: 0
	hkRelArray indices;	// Offset: 24 Unk: 0
	hkRelArray faceLinks;	// Offset: 32 Unk: 0
	hkRelArray vertexEdges;	// Offset: 40 Unk: 0
};

// Class No.64
// Mapped to c type: hknpConvexShape
class hknpConvexShape : public hknpShape {
	hkHalf16 maxAllowedPenetration;	// Offset: 56 Unk: 0
	hknpConvexHull hull;	// Offset: 60 Unk: 0
};

// Class No.63
// Mapped to c type: signed char
class signed char {
};

// Class No.62
// Mapped to c type: hkQuaternionf
class hkQuaternionf {
	hkVector4f vec;	// Offset: 0 Unk: 0
};

// Class No.61
// Mapped to c type: hkVector4f
class hkVector4f {
};

// Class No.60
// Mapped to c type: hknpCollisionControl::Enum
class hknpCollisionControl::Enum;	// [Undefined]

// Class No.59
// Mapped to c type: hkFlags
template<class tBITS=hknpCollisionControl::Enum, class tSTORAGE=unsigned short>
class hkFlags {
	unsigned short storage;	// Offset: 0 Unk: 0
};

// Class No.58
// Mapped to c type: hkInt8
class hkInt8 : public signed char {
};

// Class No.57
// Mapped to c type: hkLocalFrame
class hkLocalFrame;	// [Undefined]

// Class No.56
// Mapped to c type: hkRefPtr
template<class tTYPE=hkLocalFrame>
class hkRefPtr {
	void* ptr;	// Offset: 0 Unk: 0
};

// Class No.55
// Mapped to c type: hknpBodyId
class hknpBodyId {
	hkUint32 serialAndIndex;	// Offset: 0 Unk: 0
};

// Class No.54
// Mapped to c type: hknpRefDragProperties
class hknpRefDragProperties;	// [Undefined]

// Class No.53
// Mapped to c type: hkRefPtr
template<class tTYPE=hknpRefDragProperties>
class hkRefPtr {
	void* ptr;	// Offset: 0 Unk: 0
};

// Class No.52
// Mapped to c type: hknpRefMassDistribution
class hknpRefMassDistribution : public hkReferencedObject {
	hknpMassDistribution massDistribution;	// Offset: 32 Unk: 0
};

// Class No.51
// Mapped to c type: hkRefPtr
template<class tTYPE=hknpRefMassDistribution>
class hkRefPtr {
	void* ptr;	// Offset: 0 Unk: 0
};

// Class No.50
// Mapped to c type: hkQuaternion
class hkQuaternion : public hkQuaternionf {
};

// Class No.49
// Mapped to c type: hkVector4
class hkVector4 : public hkVector4f {
};

// Class No.48
// Mapped to c type: unsigned short
class unsigned short {
};

// Class No.47
// Mapped to c type: hknpCollisionControl
class hknpCollisionControl : public hkFlags<hknpCollisionControl::Enum, unsigned short> {
};

// Class No.46
// Mapped to c type: hknpShape
class hknpShape : public hkReferencedObject {
	hkFlags flags;	// Offset: 24 Unk: 0
	hkEnum type;	// Offset: 26 Unk: 0
	hkUint8 numShapeKeyBits;	// Offset: 27 Unk: 0
	hkEnum dispatchType;	// Offset: 28 Unk: 0
	hkReal convexRadius;	// Offset: 32 Unk: 0
	hkUint64 userData;	// Offset: 40 Unk: 0
	hkRefPtr properties;	// Offset: 48 Unk: 0
};

// Class No.45
// Mapped to c type: hkRefPtr
template<class tTYPE=hknpShape>
class hkRefPtr {
	void* ptr;	// Offset: 0 Unk: 0
};

// Class No.44
// Mapped to c type: hknpBodyCinfo
class hknpBodyCinfo {
	hkRefPtr shape;	// Offset: 0 Unk: 0
	hknpCollisionFlags flags;	// Offset: 8 Unk: 0
	hknpCollisionControl collisionCntrl;	// Offset: 12 Unk: 0
	hkUint32 collisionFilterInfo;	// Offset: 16 Unk: 0
	unsigned short materialId;	// Offset: 20 Unk: 0
	unsigned char qualityId;	// Offset: 22 Unk: 0
	hkStringPtr name;	// Offset: 24 Unk: 0
	hkUint64 userData;	// Offset: 32 Unk: 3
	unsigned char motionType;	// Offset: 40 Unk: 0
	hkVector4 position;	// Offset: 48 Unk: 0
	hkQuaternion orientation;	// Offset: 64 Unk: 0
	hkVector4 linearVelocity;	// Offset: 80 Unk: 0
	hkVector4 angularVelocity;	// Offset: 96 Unk: 0
	hkReal mass;	// Offset: 112 Unk: 0
	hkRefPtr massDistribution;	// Offset: 120 Unk: 0
	hkRefPtr dragProperties;	// Offset: 128 Unk: 0
	unsigned short motionPropertiesId;	// Offset: 136 Unk: 0
	hknpBodyId desiredBodyId;	// Offset: 140 Unk: 0
	unsigned int motionId;	// Offset: 144 Unk: 0
	hkReal collisionLookAheadDistance;	// Offset: 148 Unk: 0
	hkRefPtr localFrame;	// Offset: 152 Unk: 0
	hkInt8 activationPriority;	// Offset: 160 Unk: 0
};

// Class No.43
// Mapped to c type: hknpMotionProperties::FullCastSettings
class hknpMotionProperties::FullCastSettings {
	hkReal minSeparation;	// Offset: 0 Unk: 0
	hkReal minExtraSeparation;	// Offset: 4 Unk: 0
	hkReal toiSeparation;	// Offset: 8 Unk: 0
	hkReal toiExtraSeparation;	// Offset: 12 Unk: 0
	hkReal toiAccuracy;	// Offset: 16 Unk: 0
	hkReal relativeSafeDeltaTime;	// Offset: 20 Unk: 0
	hkReal absoluteSafeDeltaTime;	// Offset: 24 Unk: 0
	hkReal keepTime;	// Offset: 28 Unk: 0
	hkReal keepDistance;	// Offset: 32 Unk: 0
	int maxIterations;	// Offset: 36 Unk: 0
};

// Class No.42
// Mapped to c type: hknpMotionProperties::DeactivationSettings
class hknpMotionProperties::DeactivationSettings {
	hkReal maxDistSqrd;	// Offset: 0 Unk: 0
	hkReal maxRotSqrd;	// Offset: 4 Unk: 0
	hkReal invBlockSize;	// Offset: 8 Unk: 0
	hkInt16 pathingUpperThreshold;	// Offset: 12 Unk: 0
	hkInt16 pathingLowerThreshold;	// Offset: 14 Unk: 0
	hkUint8 numDeactivationFrequencyPasses;	// Offset: 16 Unk: 0
	hkUint8 deactivationVelocityScaleSquare;	// Offset: 17 Unk: 0
	hkUint8 minimumPathingVelocityScaleSquare;	// Offset: 18 Unk: 0
	hkUint8 spikingVelocityScaleThresholdSquared;	// Offset: 19 Unk: 0
	hkUint8 minimumSpikingVelocityScaleSquared;	// Offset: 20 Unk: 0
};

// Class No.41
// Mapped to c type: short
class short {
};

// Class No.40
// Mapped to c type: float
class float {
};

// Class No.39
// Mapped to c type: hkInt16
class hkInt16 : public short {
};

// Class No.38
// Mapped to c type: hknpCollisionFlags::Enum
class hknpCollisionFlags::Enum;	// [Undefined]

// Class No.37
// Mapped to c type: hkFlags
template<class tBITS=hknpCollisionFlags::Enum, class tSTORAGE=int>
class hkFlags {
	int storage;	// Offset: 0 Unk: 0
};

// Class No.36
// Mapped to c type: unsigned int
class unsigned int {
};

// Class No.35
// Mapped to c type: hkUint64
class hkUint64 : public unsigned long long {
};

// Class No.34
// Mapped to c type: hknpSurfaceVelocity
class hknpSurfaceVelocity;	// [Undefined]

// Class No.33
// Mapped to c type: hknpSurfaceVelocity*
template<class tT=hknpSurfaceVelocity>
class T* {
};

// Class No.32
// Mapped to c type: hknpMaterial::MassChangerCategory
class hknpMaterial::MassChangerCategory;	// [Undefined]

// Class No.31
// Mapped to c type: hkEnum
template<class tENUM=hknpMaterial::MassChangerCategory, class tSTORAGE=hkUint8>
class hkEnum {
	hkUint8 storage;	// Offset: 0 Unk: 0
};

// Class No.30
// Mapped to c type: hkReal
class hkReal : public float {
};

// Class No.29
// Mapped to c type: hknpMaterial::CombinePolicy
class hknpMaterial::CombinePolicy;	// [Undefined]

// Class No.28
// Mapped to c type: hkEnum
template<class tENUM=hknpMaterial::CombinePolicy, class tSTORAGE=hkUint8>
class hkEnum {
	hkUint8 storage;	// Offset: 0 Unk: 0
};

// Class No.27
// Mapped to c type: hkHalf16
class hkHalf16 {
	hkInt16 value;	// Offset: 0 Unk: 0
};

// Class No.26
// Mapped to c type: hkUFloat8
class hkUFloat8 {
	hkUint8 value;	// Offset: 0 Unk: 0
};

// Class No.25
// Mapped to c type: hknpMaterial::TriggerType
class hknpMaterial::TriggerType;	// [Undefined]

// Class No.24
// Mapped to c type: hkEnum
template<class tENUM=hknpMaterial::TriggerType, class tSTORAGE=hkUint8>
class hkEnum {
	hkUint8 storage;	// Offset: 0 Unk: 0
};

// Class No.23
// Mapped to c type: hknpCollisionFlags
class hknpCollisionFlags : public hkFlags<hknpCollisionFlags::Enum, int> {
};

// Class No.22
// Mapped to c type: hkUint32
class hkUint32 : public unsigned int {
};

// Class No.21
// Mapped to c type: unsigned long long
class unsigned long long {
};

// Class No.20
// Mapped to c type: unsigned char
class unsigned char {
};

// Class No.19
// Mapped to c type: char*
class char* {
};

// Class No.18
// Mapped to c type: int
class int {
};

// Class No.17
// Mapped to c type: void
class void;	// [Undefined]

// Class No.16
// Mapped to c type: void*
template<class tT=void>
class T* {
};

// Class No.15
// Mapped to c type: hkUlong
class hkUlong : public unsigned long long {
};

// Class No.14
// Mapped to c type: hkBaseObject
class hkBaseObject {
};

// Class No.13
// Mapped to c type: hkUint8
class hkUint8 : public unsigned char {
};

// Class No.12
// Mapped to c type: hkStringPtr
class hkStringPtr {
	char* stringAndFlag;	// Offset: 0 Unk: 0
};

// Class No.11
// Mapped to c type: hknpConstraintCinfo
class hknpConstraintCinfo;	// [Undefined]

// Class No.10
// Mapped to c type: hkArray
template<class tT=hknpConstraintCinfo, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.9
// Mapped to c type: hknpPhysicsSystemData::bodyCinfoWithAttachment
class hknpPhysicsSystemData::bodyCinfoWithAttachment : public hknpBodyCinfo {
	int attachedBody;	// Offset: 176 Unk: 0
};

// Class No.8
// Mapped to c type: hkArray
template<class tT=hknpPhysicsSystemData::bodyCinfoWithAttachment, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.7
// Mapped to c type: hknpMotionProperties
class hknpMotionProperties {
	hkUint32 isExclusive;	// Offset: 0 Unk: 15
	hknpCollisionFlags flags;	// Offset: 4 Unk: 0
	hkReal gravityFactor;	// Offset: 8 Unk: 0
	hkReal timeFactor;	// Offset: 12 Unk: 0
	hkReal maxLinearSpeed;	// Offset: 16 Unk: 0
	hkReal maxAngularSpeed;	// Offset: 20 Unk: 0
	hkReal linearDamping;	// Offset: 24 Unk: 0
	hkReal angularDamping;	// Offset: 28 Unk: 0
	hkReal solverStabilizationSpeedThreshold;	// Offset: 32 Unk: 0
	hkReal solverStabilizationSpeedReduction;	// Offset: 36 Unk: 0
	hknpMotionProperties::DeactivationSettings deactivationSettings;	// Offset: 40 Unk: 0
	hknpMotionProperties::FullCastSettings fullCastSettings;	// Offset: 64 Unk: 0
};

// Class No.6
// Mapped to c type: hkArray
template<class tT=hknpMotionProperties, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.5
// Mapped to c type: hkContainerHeapAllocator
class hkContainerHeapAllocator;	// [Undefined]

// Class No.4
// Mapped to c type: hknpMaterial
class hknpMaterial {
	hkStringPtr name;	// Offset: 0 Unk: 4
	hkUint32 isExclusive;	// Offset: 8 Unk: 0
	hknpCollisionFlags flags;	// Offset: 12 Unk: 0
	hkEnum triggerType;	// Offset: 16 Unk: 0
	hkUFloat8 triggerManifoldTolerance;	// Offset: 17 Unk: 0
	hkHalf16 dynamicFriction;	// Offset: 18 Unk: 0
	hkHalf16 staticFriction;	// Offset: 20 Unk: 0
	hkHalf16 restitution;	// Offset: 22 Unk: 0
	hkEnum frictionCombinePolicy;	// Offset: 24 Unk: 0
	hkEnum restitutionCombinePolicy;	// Offset: 25 Unk: 0
	hkReal weldingTolerance;	// Offset: 28 Unk: 0
	hkReal maxContactImpulse;	// Offset: 32 Unk: 0
	hkReal fractionOfClippedImpulseToApply;	// Offset: 36 Unk: 0
	hkEnum massChangerCategory;	// Offset: 40 Unk: 0
	hkHalf16 massChangerHeavyObjectFactor;	// Offset: 42 Unk: 0
	hkHalf16 softContactForceFactor;	// Offset: 44 Unk: 0
	hkHalf16 softContactDampFactor;	// Offset: 46 Unk: 0
	hkUFloat8 softContactSeparationVelocity;	// Offset: 48 Unk: 0
	hknpSurfaceVelocity* surfaceVelocity;	// Offset: 56 Unk: 0
	hkHalf16 disablingCollisionsBetweenCvxCvxDynamicObjectsDistance;	// Offset: 64 Unk: 0
	hkUint64 userData;	// Offset: 72 Unk: 3
};

// Class No.3
// Mapped to c type: hkArray
template<class tT=hknpMaterial, class tAllocator=hkContainerHeapAllocator>
class hkArray {
	void* m_data;	// Offset: 0 Unk: 0
	int m_size;	// Offset: 8 Unk: 0
	int m_capacityAndFlags;	// Offset: 12 Unk: 0
};

// Class No.2
// Mapped to c type: hkReferencedObject
class hkReferencedObject : public hkBaseObject {
	hkUlong sizeAndFlags;	// Offset: 8 Unk: 0
	hkUlong refCount;	// Offset: 16 Unk: 0
};

// Class No.1
// Mapped to c type: hknpPhysicsSystemData
class hknpPhysicsSystemData : public hkReferencedObject {
	hkArray materials;	// Offset: 24 Unk: 0
	hkArray motionProperties;	// Offset: 40 Unk: 0
	hkArray bodyCinfos;	// Offset: 56 Unk: 0
	hkArray constraintCinfos;	// Offset: 72 Unk: 0
	hkStringPtr name;	// Offset: 88 Unk: 0
	hkUint8 microStepMultiplier;	// Offset: 96 Unk: 0
};

