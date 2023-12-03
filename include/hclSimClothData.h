#pragma once
#include "hkTypes.h"

namespace hktypes {

	class hclConstraintSet : public hkReferencedObject {
	public:
		std::string name;	// Offset: 24 Unk: 0
		uint32_t constraintId;	// Offset: 32 Unk: 0
		uint32_t type;	// Offset: 36 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclLocalRangeConstraintSet : public hclConstraintSet {
	public:
		class LocalConstraint : public hkHolderBase {
		public:
			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override { return true; };
			bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
		};

		class LocalStiffnessConstraint : public hkHolderBase {
		public:
			uint16_t particleIndex;	// Offset: 0 Unk: 0
			uint16_t referenceVertex;	// Offset: 2 Unk: 0
			float maximumDistance;	// Offset: 4 Unk: 0
			float maxNormalDistance;	// Offset: 8 Unk: 0
			float minNormalDistance;	// Offset: 12 Unk: 0
			float stiffness;	// Offset: 16 Unk: 0

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		enum ShapeType : uint32_t {
			ST_SPHERE = 0,
			ST_CAPSULE = 1,
			ST_PLANE = 2,
			ST_BOX = 3,
			ST_CYLINDER = 4,
			ST_CONVEX = 5,
			ST_TRIANGLE = 6,
			ST_TETRA = 7,
			ST_USER = 8,
			ST_MAX_ID = 9,
		};

		std::vector<LocalConstraint> localConstraints;	// Offset: 40 Unk: 0
		std::vector<LocalStiffnessConstraint> localStiffnessConstraints;	// Offset: 56 Unk: 0
		uint32_t referenceMeshBufferIdx;	// Offset: 72 Unk: 0
		float stiffness;	// Offset: 76 Unk: 0
		ShapeType shapeType;	// Offset: 80 Unk: 0
		bool applyNormalComponent;	// Offset: 84 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclStandardLinkConstraintSetMx : public hclConstraintSet {
	public:
		class Batch : public hkHolderBase {
			float restLengths[4];	// Offset: 0 Unk: 0
			float stiffnessesA[4];	// Offset: 16 Unk: 0
			float stiffnessesB[4];	// Offset: 32 Unk: 0
			uint16_t particlesA[4];	// Offset: 48 Unk: 0
			uint16_t particlesB[4];	// Offset: 56 Unk: 0

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Single : public hkHolderBase {
			float restLength;	// Offset: 0 Unk: 0
			float stiffnessA;	// Offset: 4 Unk: 0
			float stiffnessB;	// Offset: 8 Unk: 0
			uint16_t particleA;	// Offset: 12 Unk: 0
			uint16_t particleB;	// Offset: 14 Unk: 0

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<Batch> batches;	// Offset: 40 Unk: 0
		std::vector<Single> singles;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclSimClothPose : public hkReferencedObject {
	public:
		std::string name;	// Offset: 24 Unk: 0
		std::vector<hkVector4Holder> positions;	// Offset: 32 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclShape : public hkReferencedObject {
	public:
		uint64_t unk_data;	// Offset: 24 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override { return true; };
		bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
	};

	class hclCollidable : public hkReferencedObject {
	public:
		std::string name;	// Offset: 24 Unk: 0
		hkMatrix4Holder transform;
		hkVector4Holder linearVelocity;
		hkVector4Holder angularVelocity;
		bool pinchDetectionEnabled;
		int8_t pinchDetectionPriority;
		float pinchDetectionRadius;
		hclShape shape;

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclSimClothData : public hkReferencedObject {
	public:
		class OverridableSimulationInfo : public hkHolderBase {
		public:
			Eigen::Vector4f gravity;	// Offset: 0 Unk: 0
			float globalDampingPerSecond;	// Offset: 16 Unk: 0

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class ParticleData : public hkHolderBase {
		public:
			float mass = 1.000000;
			float invMass = 1.000000;
			float radius = 0.000000;
			float friction = 0.500000;

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class CollidableTransformMap : public hkHolderBase {
		public:
			int transformSetIndex;
			std::vector<uint32_t> transformIndices;
			std::vector<hkMatrix4Holder> offsets;

			// Extra
			bool FromInstance(hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::string name;	// Offset: 24 Unk: 0
		OverridableSimulationInfo simulationInfo;	// Offset: 32 Unk: 0
		std::vector<ParticleData> particleDatas;	// Offset: 64 Unk: 0
		std::vector<uint16_t> fixedParticles;	// Offset: 80 Unk: 0
		bool doNormals;	// Offset: 96 Unk: 0
		std::vector<uint32_t> simOpIds;	// Offset: 104 Unk: 0
		std::vector<hclSimClothPose*> simClothPoses;	// Offset: 120 Unk: 0
		std::vector<hclConstraintSet*> staticConstraintSets;	// Offset: 136 Unk: 0
		std::vector<hclConstraintSet*> antiPinchConstraintSets;	// Offset: 152 Unk: 0
		CollidableTransformMap collidableTransformMap;	// Offset: 168 Unk: 0
		std::vector<hclCollidable*> perInstanceCollidables;	// Offset: 208 Unk: 0
		float maxParticleRadius;	// Offset: 224 Unk: 0
		std::vector<uint32_t> staticCollisionMasks;	// Offset: 232 Unk: 0
		//hkArray<T*, hkContainerHeapAllocator> actions;	// Offset: 248 Unk: 0
		float totalMass;	// Offset: 264 Unk: 0
		//hclSimClothData::TransferMotionData transferMotionData;	// Offset: 268 Unk: 0
		bool transferMotionEnabled;	// Offset: 316 Unk: 0
		bool landscapeCollisionEnabled;	// Offset: 317 Unk: 0
		//hclSimClothData::LandscapeCollisionData landscapeCollisionData;	// Offset: 320 Unk: 0
		uint32_t numLandscapeCollidableParticles;	// Offset: 344 Unk: 0
		std::vector<uint16_t> triangleIndices;	// Offset: 352 Unk: 0
		std::vector<uint8_t> triangleFlips;	// Offset: 368 Unk: 0
		bool pinchDetectionEnabled;	// Offset: 384 Unk: 0
		std::vector<bool> perParticlePinchDetectionEnabledFlags;	// Offset: 392 Unk: 0
		//std::vector<hclSimClothData::CollidablePinchingData> collidablePinchingDatas;	// Offset: 408 Unk: 0
		uint16_t minPinchedParticleIndex;	// Offset: 424 Unk: 0
		uint16_t maxPinchedParticleIndex;	// Offset: 426 Unk: 0
		uint32_t maxCollisionPairs;	// Offset: 428 Unk: 0
		//hclVirtualCollisionPointsData virtualCollisionPointsData;	// Offset: 432 Unk: 0

		// Extra
		bool FromInstance(hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}