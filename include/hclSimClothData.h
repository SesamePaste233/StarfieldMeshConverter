#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include "hclShape.h"

namespace hktypes {
	class hkMatrix4Holder;
	class hkVector4Holder;
	class hclShape;

	template<class tStorage>
	requires utils::_is_integer_t<tStorage>
	class hkHandle;

	class hclConstraintSet : public hkReferencedObject {
	public:
		std::string name;	// Offset: 24 Unk: 0
		hkHandle<uint32_t> constraintId;	// Offset: 32 Unk: 0
		uint32_t type;	// Offset: 36 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclVolumeConstraint : public hclConstraintSet {
	public:
		class FrameData : public hkHolderBase {
			hkVector4Holder frameVector;	// Offset: 0 Unk: 0
			uint16_t particleIndex;	// Offset: 16 Unk: 0
			float weight;	// Offset: 20 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class ApplyData : public hkHolderBase {
			hkVector4Holder frameVector;	// Offset: 0 Unk: 0
			uint16_t particleIndex;	// Offset: 16 Unk: 0
			float stiffness;	// Offset: 20 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclVolumeConstraint::FrameData> frameDatas;	// Offset: 40 Unk: 0
		std::vector<hclVolumeConstraint::ApplyData> applyDatas;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclBonePlanesConstraintSet : public hclConstraintSet {
	public:
		class BonePlane : public hkHolderBase {
		public:
			hkVector4Holder planeEquationBone;	// Offset: 0 Unk: 0
			uint16_t particleIndex;	// Offset: 16 Unk: 0
			uint16_t transformIndex;	// Offset: 18 Unk: 0
			float stiffness;	// Offset: 20 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};
		std::vector<BonePlane> bonePlanes;	// Offset: 40 Unk: 0
		uint32_t transformSetIndex;	// Offset: 56 Unk: 0
		
		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclLocalRangeConstraintSet : public hclConstraintSet {
	public:
		class LocalConstraint : public hkHolderBase {
		public:
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override { return true; };
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
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
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
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclCompressibleLinkConstraintSetMx : public hclConstraintSet {
	public:
		class Batch : public hkHolderBase {
		public:
			std::array<float, 4> restLengths;	// Offset: 0 Unk: 0
			std::array<float, 4> compressionLengths;	// Offset: 16 Unk: 0
			std::array<float, 4> stiffnessesA;	// Offset: 32 Unk: 0
			std::array<float, 4> stiffnessesB;	// Offset: 48 Unk: 0
			std::array<uint16_t, 4> particlesA;	// Offset: 64 Unk: 0
			std::array<uint16_t, 4> particlesB;	// Offset: 72 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Single : public hclConstraintSet {
		public:
			float restLength;	// Offset: 0 Unk: 0
			float compressionLength;	// Offset: 4 Unk: 0
			float stiffnessA;	// Offset: 8 Unk: 0
			float stiffnessB;	// Offset: 12 Unk: 0
			uint16_t particleA;	// Offset: 16 Unk: 0
			uint16_t particleB;	// Offset: 18 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclCompressibleLinkConstraintSetMx::Batch> batches;	// Offset: 40 Unk: 0
		std::vector<hclCompressibleLinkConstraintSetMx::Single> singles;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclBendStiffnessConstraintSetMx : public hclConstraintSet {
	public:
		class Batch : public hkHolderBase {
		public:
			std::array<float, 4> weightsA;	// Offset: 0 Unk: 0
			std::array<float, 4> weightsB;	// Offset: 16 Unk: 0
			std::array<float, 4> weightsC;	// Offset: 32 Unk: 0
			std::array<float, 4> weightsD;	// Offset: 48 Unk: 0
			std::array<float, 4> bendStiffnesses;	// Offset: 64 Unk: 0
			std::array<float, 4> restCurvatures;	// Offset: 80 Unk: 0
			std::array<float, 4> invMassesA;	// Offset: 96 Unk: 0
			std::array<float, 4> invMassesB;	// Offset: 112 Unk: 0
			std::array<float, 4> invMassesC;	// Offset: 128 Unk: 0
			std::array<float, 4> invMassesD;	// Offset: 144 Unk: 0
			std::array<uint16_t, 4> particlesA;	// Offset: 160 Unk: 0
			std::array<uint16_t, 4> particlesB;	// Offset: 168 Unk: 0
			std::array<uint16_t, 4> particlesC;	// Offset: 176 Unk: 0
			std::array<uint16_t, 4> particlesD;	// Offset: 184 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Single : public hkHolderBase {
		public:
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<hclBendStiffnessConstraintSetMx::Batch> batches;	// Offset: 40 Unk: 0
		std::vector<hclBendStiffnessConstraintSetMx::Single> singles;	// Offset: 56 Unk: 0
		float maxRestPoseHeightSq;	// Offset: 72 Unk: 0
		bool clampBendStiffness;	// Offset: 76 Unk: 0
		bool useRestPoseConfig;	// Offset: 77 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
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
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Single : public hkHolderBase {
			float restLength;	// Offset: 0 Unk: 0
			float stiffnessA;	// Offset: 4 Unk: 0
			float stiffnessB;	// Offset: 8 Unk: 0
			uint16_t particleA;	// Offset: 12 Unk: 0
			uint16_t particleB;	// Offset: 14 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<Batch> batches;	// Offset: 40 Unk: 0
		std::vector<Single> singles;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclStretchLinkConstraintSetMx : public hclConstraintSet {
	public:
		class Batch : public hkHolderBase {
			std::array<float, 4> restLengths;	// Offset: 0 Unk: 0
			std::array<float, 4> stiffnesses;	// Offset: 16 Unk: 0
			std::array<uint16_t, 4> particlesA;	// Offset: 32 Unk: 0
			std::array<uint16_t, 4> particlesB;	// Offset: 40 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class Single : public hkHolderBase {
			float restLength;	// Offset: 0 Unk: 0
			float stiffness;	// Offset: 4 Unk: 0
			uint32_t particleA;	// Offset: 8 Unk: 0
			uint32_t particleB;	// Offset: 12 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::vector<Batch> batches;	// Offset: 40 Unk: 0
		std::vector<Single> singles;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclSimClothPose : public hkReferencedObject {
	public:
		std::string name;	// Offset: 24 Unk: 0
		std::vector<hkVector4Holder> positions;	// Offset: 32 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
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
		hclShape* shape;

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};

	class hclSimClothData : public hkReferencedObject {
	public:
		class OverridableSimulationInfo : public hkHolderBase {
		public:
			Eigen::Vector4f gravity;	// Offset: 0 Unk: 0
			float globalDampingPerSecond;	// Offset: 16 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class ParticleData : public hkHolderBase {
		public:
			float mass = 1.000000;
			float invMass = 1.000000;
			float radius = 0.000000;
			float friction = 0.500000;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class CollidableTransformMap : public hkHolderBase {
		public:
			int transformSetIndex;
			std::vector<uint32_t> transformIndices;
			std::vector<hkMatrix4Holder> offsets;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class TransferMotionData : public hkHolderBase {
		public:
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

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class LandscapeCollisionData :public hkHolderBase {
		public:
			float landscapeRadius;	// Offset: 0 Unk: 0
			bool enableStuckParticleDetection;	// Offset: 4 Unk: 0
			float stuckParticlesStretchFactorSq;	// Offset: 8 Unk: 0
			bool pinchDetectionEnabled;	// Offset: 12 Unk: 0
			int8_t pinchDetectionPriority;	// Offset: 13 Unk: 0
			float pinchDetectionRadius;	// Offset: 16 Unk: 0
			float collisionTolerance;	// Offset: 20 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
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
		//std::vector<hclAction*> actions;	// Offset: 248 Unk: 0
		float totalMass;	// Offset: 264 Unk: 0
		TransferMotionData transferMotionData;	// Offset: 268 Unk: 0
		bool transferMotionEnabled;	// Offset: 316 Unk: 0
		bool landscapeCollisionEnabled;	// Offset: 317 Unk: 0
		LandscapeCollisionData landscapeCollisionData;	// Offset: 320 Unk: 0
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
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}