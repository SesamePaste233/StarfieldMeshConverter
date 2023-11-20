#pragma once

#include "hkBaseCTypes.h"
// Class No.93
// Original: T[N]<hkInt16, 4> Mapped to c type : short[4]


// Class No.92
// Original: T[N]<short, 4> Mapped to c type : short[4]


// Class No.91
// Mapped to c type: hkPackedVector3
class hkPackedVector3 {
	short[4] values;	// Offset: 0 Unk: 3
};

// Class No.90
// Mapped to c type: hkCompressedMassProperties
class hkCompressedMassProperties {
	hkPackedVector3 centerOfMass;	// Offset: 0 Unk: 3
	hkPackedVector3 inertia;	// Offset: 8 Unk: 3
	short[4] majorAxisSpace;	// Offset: 16 Unk: 3
	float mass;	// Offset: 24 Unk: 0
	float volume;	// Offset: 28 Unk: 0
};

// Class No.89
// Mapped to c type: hknpShapeMassProperties
class hknpShapeMassProperties : public hkReferencedObject {
	hkCompressedMassProperties compressedMassProperties;	// Offset: 24 Unk: 3
};

// Class No.88
// Original: hkRefPtr<hkReferencedObject> Mapped to c type : hkReferencedObject


// Class No.87
// Mapped to c type: hkRefCountedProperties::Entry
class hkRefCountedProperties::Entry {
	hkReferencedObject object;	// Offset: 0 Unk: 0
	uint16_t key;	// Offset: 8 Unk: 0
	uint16_t flags;	// Offset: 10 Unk: 0
};

// Class No.86
// Original: hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator> Mapped to c type : std::vector<hkRefCountedProperties::Entry>


// Class No.85
// Mapped to c type: hknpMassDistribution
class hknpMassDistribution {
	Vector4 centerOfMassAndVolume;	// Offset: 0 Unk: 0
	Quaternion majorAxisSpace;	// Offset: 16 Unk: 0
	Vector4 inertiaTensor;	// Offset: 32 Unk: 0
};

// Class No.84
// Original: T[N]<hkUint8, 1> Mapped to c type : uint8_t[1]


// Class No.83
// Original: hkInt32 Mapped to c type : int


// Class No.82
// Mapped to c type: hknpConvexHull::Edge
class hknpConvexHull::Edge {
	uint16_t faceIndex;	// Offset: 0 Unk: 0
	uint8_t edgeIndex;	// Offset: 2 Unk: 0
	uint8_t[1] padding;	// Offset: 3 Unk: 0
};

// Class No.81
// Original: hkRelArray<hknpConvexHull::Edge> Mapped to c type : std::vector<hknpConvexHull::Edge>


// Class No.80
// Original: hkRelArray<hkUint8> Mapped to c type : std::vector<uint8_t>


// Class No.79
// Mapped to c type: hknpConvexHull::Face
class hknpConvexHull::Face {
	uint16_t firstIndex;	// Offset: 0 Unk: 0
	uint8_t numIndices;	// Offset: 2 Unk: 0
	uint8_t minHalfAngle;	// Offset: 3 Unk: 0
};

// Class No.78
// Original: hkRelArray<hknpConvexHull::Face> Mapped to c type : std::vector<hknpConvexHull::Face>


// Class No.77
// Original: hkRelArray<hkVector4> Mapped to c type : std::vector<Vector4>


// Class No.76
// Mapped to c type: hkFloat3
class hkFloat3 {
	float x;	// Offset: 0 Unk: 0
	float y;	// Offset: 4 Unk: 0
	float z;	// Offset: 8 Unk: 0
};

// Class No.75
// Original: hkRelArray<hkFloat3> Mapped to c type : std::vector<hkFloat3>


// Class No.74
// Mapped to c type: hkRefCountedProperties
class hkRefCountedProperties : public hkReferencedObject {
	std::vector<hkRefCountedProperties::Entry> entries;	// Offset: 24 Unk: 0
};

// Class No.73
// Original: hkRefPtr<hkRefCountedProperties> Mapped to c type : hkRefCountedProperties


// Class No.72
// Mapped to c type: hknpCollisionDispatchType::Enum
class hknpCollisionDispatchType::Enum;	// [Undefined]

// Class No.71
// Original: hkEnum<hknpCollisionDispatchType::Enum, hkUint8> Mapped to c type : hknpCollisionDispatchType::Enum


// Class No.70
// Mapped to c type: hknpShapeType::Enum
class hknpShapeType::Enum;	// [Undefined]

// Class No.69
// Original: hkEnum<hknpShapeType::Enum, hkUint8> Mapped to c type : hknpShapeType::Enum


// Class No.68
// Original: hkUint16 Mapped to c type : uint16_t


// Class No.67
// Mapped to c type: hknpShape::FlagsEnum
class hknpShape::FlagsEnum;	// [Undefined]

// Class No.66
// Original: hkFlags<hknpShape::FlagsEnum, hkUint16> Mapped to c type : hknpShape::FlagsEnum


// Class No.65
// Mapped to c type: hknpConvexHull
class hknpConvexHull {
	std::vector<hkFloat3> vertices;	// Offset: 0 Unk: 0
	std::vector<Vector4> planes;	// Offset: 8 Unk: 0 //Facing towards the center of the hull
	std::vector<hknpConvexHull::Face> faces;	// Offset: 16 Unk: 0
	std::vector<uint8_t> indices;	// Offset: 24 Unk: 0
	std::vector<hknpConvexHull::Edge> faceLinks;	// Offset: 32 Unk: 0
	std::vector<hknpConvexHull::Edge> vertexEdges;	// Offset: 40 Unk: 0
};

// Class No.64
// Mapped to c type: hknpConvexShape
class hknpConvexShape : public hknpShape {
	float maxAllowedPenetration;	// Offset: 56 Unk: 0
	hknpConvexHull hull;	// Offset: 60 Unk: 0
};

// Class No.63
// Original: signed char Mapped to c type : int8_t


// Class No.62
// Original: hkQuaternionf Mapped to c type : Quaternion


// Class No.61
// Original: hkVector4f Mapped to c type : Vector4


// Class No.60
// Mapped to c type: hknpCollisionControl::Enum
class hknpCollisionControl::Enum;	// [Undefined]

// Class No.59
// Original: hkFlags<hknpCollisionControl::Enum, unsigned short> Mapped to c type : hknpCollisionControl::Enum


// Class No.58
// Original: hkInt8 Mapped to c type : int8_t


// Class No.57
// Mapped to c type: hkLocalFrame
class hkLocalFrame;	// [Undefined]

// Class No.56
// Original: hkRefPtr<hkLocalFrame> Mapped to c type : hkLocalFrame


// Class No.55
// Mapped to c type: hknpBodyId
class hknpBodyId {
	uint32_t serialAndIndex;	// Offset: 0 Unk: 0
};

// Class No.54
// Mapped to c type: hknpRefDragProperties
class hknpRefDragProperties;	// [Undefined]

// Class No.53
// Original: hkRefPtr<hknpRefDragProperties> Mapped to c type : hknpRefDragProperties


// Class No.52
// Mapped to c type: hknpRefMassDistribution
class hknpRefMassDistribution : public hkReferencedObject {
	hknpMassDistribution massDistribution;	// Offset: 32 Unk: 0
};

// Class No.51
// Original: hkRefPtr<hknpRefMassDistribution> Mapped to c type : hknpRefMassDistribution


// Class No.50
// Original: hkQuaternion Mapped to c type : Quaternion


// Class No.49
// Original: hkVector4 Mapped to c type : Vector4


// Class No.48
// Original: unsigned short Mapped to c type : uint16_t


// Class No.47
// Mapped to c type: hknpCollisionControl
class hknpCollisionControl : public hkFlags<hknpCollisionControl::Enum, unsigned short> {
};

// Class No.46
// Mapped to c type: hknpShape
class hknpShape : public hkReferencedObject {
	hknpShape::FlagsEnum flags;	// Offset: 24 Unk: 0
	hknpShapeType::Enum type;	// Offset: 26 Unk: 0
	uint8_t numShapeKeyBits;	// Offset: 27 Unk: 0
	hknpCollisionDispatchType::Enum dispatchType;	// Offset: 28 Unk: 0
	float convexRadius;	// Offset: 32 Unk: 0
	uint64_t userData;	// Offset: 40 Unk: 0
	hkRefCountedProperties properties;	// Offset: 48 Unk: 0
};

// Class No.45
// Original: hkRefPtr<hknpShape> Mapped to c type : hknpShape


// Class No.44
// Mapped to c type: hknpBodyCinfo
class hknpBodyCinfo {
	hknpShape shape;	// Offset: 0 Unk: 0
	hknpCollisionFlags flags;	// Offset: 8 Unk: 0
	hknpCollisionControl collisionCntrl;	// Offset: 12 Unk: 0
	uint32_t collisionFilterInfo;	// Offset: 16 Unk: 0
	uint16_t materialId;	// Offset: 20 Unk: 0
	uint8_t qualityId;	// Offset: 22 Unk: 0
	std::string name;	// Offset: 24 Unk: 0
	uint64_t userData;	// Offset: 32 Unk: 3
	uint8_t motionType;	// Offset: 40 Unk: 0
	Vector4 position;	// Offset: 48 Unk: 0
	Quaternion orientation;	// Offset: 64 Unk: 0
	Vector4 linearVelocity;	// Offset: 80 Unk: 0
	Vector4 angularVelocity;	// Offset: 96 Unk: 0
	float mass;	// Offset: 112 Unk: 0
	hknpRefMassDistribution massDistribution;	// Offset: 120 Unk: 0
	hknpRefDragProperties dragProperties;	// Offset: 128 Unk: 0
	uint16_t motionPropertiesId;	// Offset: 136 Unk: 0
	hknpBodyId desiredBodyId;	// Offset: 140 Unk: 0
	uint32_t motionId;	// Offset: 144 Unk: 0
	float collisionLookAheadDistance;	// Offset: 148 Unk: 0
	hkLocalFrame localFrame;	// Offset: 152 Unk: 0
	int8_t activationPriority;	// Offset: 160 Unk: 0
};

// Class No.43
// Mapped to c type: hknpMotionProperties::FullCastSettings
class hknpMotionProperties::FullCastSettings {
	float minSeparation;	// Offset: 0 Unk: 0
	float minExtraSeparation;	// Offset: 4 Unk: 0
	float toiSeparation;	// Offset: 8 Unk: 0
	float toiExtraSeparation;	// Offset: 12 Unk: 0
	float toiAccuracy;	// Offset: 16 Unk: 0
	float relativeSafeDeltaTime;	// Offset: 20 Unk: 0
	float absoluteSafeDeltaTime;	// Offset: 24 Unk: 0
	float keepTime;	// Offset: 28 Unk: 0
	float keepDistance;	// Offset: 32 Unk: 0
	int maxIterations;	// Offset: 36 Unk: 0
};

// Class No.42
// Mapped to c type: hknpMotionProperties::DeactivationSettings
class hknpMotionProperties::DeactivationSettings {
	float maxDistSqrd;	// Offset: 0 Unk: 0
	float maxRotSqrd;	// Offset: 4 Unk: 0
	float invBlockSize;	// Offset: 8 Unk: 0
	short pathingUpperThreshold;	// Offset: 12 Unk: 0
	short pathingLowerThreshold;	// Offset: 14 Unk: 0
	uint8_t numDeactivationFrequencyPasses;	// Offset: 16 Unk: 0
	uint8_t deactivationVelocityScaleSquare;	// Offset: 17 Unk: 0
	uint8_t minimumPathingVelocityScaleSquare;	// Offset: 18 Unk: 0
	uint8_t spikingVelocityScaleThresholdSquared;	// Offset: 19 Unk: 0
	uint8_t minimumSpikingVelocityScaleSquared;	// Offset: 20 Unk: 0
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
// Original: hkInt16 Mapped to c type : short


// Class No.38
// Mapped to c type: hknpCollisionFlags::Enum
class hknpCollisionFlags::Enum;	// [Undefined]

// Class No.37
// Mapped to c type: hkFlags<hknpCollisionFlags::Enum, int>
template<tBITS=hknpCollisionFlags::Enum, tSTORAGE=int>
class hkFlags {
	int storage;	// Offset: 0 Unk: 0
};

// Class No.36
// Original: unsigned int Mapped to c type : uint32_t


// Class No.35
// Original: hkUint64 Mapped to c type : uint64_t


// Class No.34
// Mapped to c type: hknpSurfaceVelocity
class hknpSurfaceVelocity;	// [Undefined]

// Class No.33
// Original: T*<hknpSurfaceVelocity> Mapped to c type : hknpSurfaceVelocity


// Class No.32
// Mapped to c type: hknpMaterial::MassChangerCategory
class hknpMaterial::MassChangerCategory;	// [Undefined]

// Class No.31
// Original: hkEnum<hknpMaterial::MassChangerCategory, hkUint8> Mapped to c type : hknpMaterial::MassChangerCategory


// Class No.30
// Original: hkReal Mapped to c type : float


// Class No.29
// Mapped to c type: hknpMaterial::CombinePolicy
class hknpMaterial::CombinePolicy;	// [Undefined]

// Class No.28
// Original: hkEnum<hknpMaterial::CombinePolicy, hkUint8> Mapped to c type : hknpMaterial::CombinePolicy


// Class No.27
// Original: hkHalf16 Mapped to c type : float


// Class No.26
// Mapped to c type: hkUFloat8
class hkUFloat8 {
	uint8_t value;	// Offset: 0 Unk: 0
};

// Class No.25
// Mapped to c type: hknpMaterial::TriggerType
class hknpMaterial::TriggerType;	// [Undefined]

// Class No.24
// Original: hkEnum<hknpMaterial::TriggerType, hkUint8> Mapped to c type : hknpMaterial::TriggerType


// Class No.23
// Mapped to c type: hknpCollisionFlags
class hknpCollisionFlags : public hkFlags<hknpCollisionFlags::Enum, int> {
};

// Class No.22
// Original: hkUint32 Mapped to c type : uint32_t


// Class No.21
// Original: unsigned long long Mapped to c type : uint64_t


// Class No.20
// Original: unsigned char Mapped to c type : uint8_t


// Class No.19
// Original: char* Mapped to c type : std::string


// Class No.18
// Mapped to c type: int
class int {
};

// Class No.17
// Mapped to c type: void
class void;	// [Undefined]

// Class No.16
// Original: T*<void> Mapped to c type : object


// Class No.15
// Original: hkUlong Mapped to c type : uint64_t


// Class No.14
// Mapped to c type: hkBaseObject
class hkBaseObject {
};

// Class No.13
// Original: hkUint8 Mapped to c type : uint8_t


// Class No.12
// Original: hkStringPtr Mapped to c type : std::string


// Class No.11
// Mapped to c type: hknpConstraintCinfo
class hknpConstraintCinfo;	// [Undefined]

// Class No.10
// Original: hkArray<hknpConstraintCinfo, hkContainerHeapAllocator> Mapped to c type : std::vector<hknpConstraintCinfo>


// Class No.9
// Mapped to c type: hknpPhysicsSystemData::bodyCinfoWithAttachment
class hknpPhysicsSystemData::bodyCinfoWithAttachment : public hknpBodyCinfo {
	int attachedBody;	// Offset: 176 Unk: 0
};

// Class No.8
// Original: hkArray<hknpPhysicsSystemData::bodyCinfoWithAttachment, hkContainerHeapAllocator> Mapped to c type : std::vector<hknpPhysicsSystemData::bodyCinfoWithAttachment>


// Class No.7
// Mapped to c type: hknpMotionProperties
class hknpMotionProperties {
	uint32_t isExclusive;	// Offset: 0 Unk: 15
	hknpCollisionFlags flags;	// Offset: 4 Unk: 0
	float gravityFactor;	// Offset: 8 Unk: 0
	float timeFactor;	// Offset: 12 Unk: 0
	float maxLinearSpeed;	// Offset: 16 Unk: 0
	float maxAngularSpeed;	// Offset: 20 Unk: 0
	float linearDamping;	// Offset: 24 Unk: 0
	float angularDamping;	// Offset: 28 Unk: 0
	float solverStabilizationSpeedThreshold;	// Offset: 32 Unk: 0
	float solverStabilizationSpeedReduction;	// Offset: 36 Unk: 0
	hknpMotionProperties::DeactivationSettings deactivationSettings;	// Offset: 40 Unk: 0
	hknpMotionProperties::FullCastSettings fullCastSettings;	// Offset: 64 Unk: 0
};

// Class No.6
// Original: hkArray<hknpMotionProperties, hkContainerHeapAllocator> Mapped to c type : std::vector<hknpMotionProperties>


// Class No.5
// Mapped to c type: hkContainerHeapAllocator
class hkContainerHeapAllocator;	// [Undefined]

// Class No.4
// Mapped to c type: hknpMaterial
class hknpMaterial {
	std::string name;	// Offset: 0 Unk: 4
	uint32_t isExclusive;	// Offset: 8 Unk: 0
	hknpCollisionFlags flags;	// Offset: 12 Unk: 0
	hknpMaterial::TriggerType triggerType;	// Offset: 16 Unk: 0
	hkUFloat8 triggerManifoldTolerance;	// Offset: 17 Unk: 0
	float dynamicFriction;	// Offset: 18 Unk: 0
	float staticFriction;	// Offset: 20 Unk: 0
	float restitution;	// Offset: 22 Unk: 0
	hknpMaterial::CombinePolicy frictionCombinePolicy;	// Offset: 24 Unk: 0
	hknpMaterial::CombinePolicy restitutionCombinePolicy;	// Offset: 25 Unk: 0
	float weldingTolerance;	// Offset: 28 Unk: 0
	float maxContactImpulse;	// Offset: 32 Unk: 0
	float fractionOfClippedImpulseToApply;	// Offset: 36 Unk: 0
	hknpMaterial::MassChangerCategory massChangerCategory;	// Offset: 40 Unk: 0
	float massChangerHeavyObjectFactor;	// Offset: 42 Unk: 0
	float softContactForceFactor;	// Offset: 44 Unk: 0
	float softContactDampFactor;	// Offset: 46 Unk: 0
	hkUFloat8 softContactSeparationVelocity;	// Offset: 48 Unk: 0
	hknpSurfaceVelocity surfaceVelocity;	// Offset: 56 Unk: 0
	float disablingCollisionsBetweenCvxCvxDynamicObjectsDistance;	// Offset: 64 Unk: 0
	uint64_t userData;	// Offset: 72 Unk: 3
};

// Class No.3
// Original: hkArray<hknpMaterial, hkContainerHeapAllocator> Mapped to c type : std::vector<hknpMaterial>


// Class No.2
// Mapped to c type: hkReferencedObject
class hkReferencedObject : public hkBaseObject {
	uint64_t sizeAndFlags;	// Offset: 8 Unk: 0
	uint64_t refCount;	// Offset: 16 Unk: 0
};

// Class No.1
// Mapped to c type: hknpPhysicsSystemData
class hknpPhysicsSystemData : public hkReferencedObject {
	std::vector<hknpMaterial> materials;	// Offset: 24 Unk: 0
	std::vector<hknpMotionProperties> motionProperties;	// Offset: 40 Unk: 0
	std::vector<hknpPhysicsSystemData::bodyCinfoWithAttachment> bodyCinfos;	// Offset: 56 Unk: 0
	std::vector<hknpConstraintCinfo> constraintCinfos;	// Offset: 72 Unk: 0
	std::string name;	// Offset: 88 Unk: 0
	uint8_t microStepMultiplier;	// Offset: 96 Unk: 0
};

