#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hclSimClothPose.h"
#include "Generated\hclConstraintSet.h"
#include "Generated\hclCollidable.h"
#include "Generated\hclVirtualCollisionPointsData.h"

namespace hktypes{
	class hkReferencedObject;
	class hclSimClothPose;
	class hclConstraintSet;
	class hclCollidable;
	class hclVirtualCollisionPointsData;

	class hclSimClothData : public hkReferencedObject {
	public:
		class OverridableSimulationInfo : public hkHolderBase {
		public:
			hkVector4Holder gravity; // Offset: 0
			float globalDampingPerSecond; // Offset: 16

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class ParticleData : public hkHolderBase {
		public:
			float mass; // Offset: 0
			float invMass; // Offset: 4
			float radius; // Offset: 8
			float friction; // Offset: 12

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class CollidableTransformMap : public hkHolderBase {
		public:
			int transformSetIndex; // Offset: 0
			std::vector<uint32_t> transformIndices; // Offset: 8
			std::vector<hkMatrix4Holder> offsets; // Offset: 24

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class TransferMotionData : public hkHolderBase {
		public:
			uint32_t transformSetIndex; // Offset: 0
			uint32_t transformIndex; // Offset: 4
			bool transferTranslationMotion; // Offset: 8
			float minTranslationSpeed; // Offset: 12
			float maxTranslationSpeed; // Offset: 16
			float minTranslationBlend; // Offset: 20
			float maxTranslationBlend; // Offset: 24
			bool transferRotationMotion; // Offset: 28
			float minRotationSpeed; // Offset: 32
			float maxRotationSpeed; // Offset: 36
			float minRotationBlend; // Offset: 40
			float maxRotationBlend; // Offset: 44

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class LandscapeCollisionData : public hkHolderBase {
		public:
			float landscapeRadius; // Offset: 0
			bool enableStuckParticleDetection; // Offset: 4
			float stuckParticlesStretchFactorSq; // Offset: 8
			bool pinchDetectionEnabled; // Offset: 12
			int8_t pinchDetectionPriority; // Offset: 13
			float pinchDetectionRadius; // Offset: 16
			float collisionTolerance; // Offset: 20

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		class CollidablePinchingData : public hkHolderBase {
		public:
			bool pinchDetectionEnabled; // Offset: 0
			int8_t pinchDetectionPriority; // Offset: 1
			float pinchDetectionRadius; // Offset: 4

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
		};

		std::string name; // Offset: 24
		hclSimClothData::OverridableSimulationInfo simulationInfo; // Offset: 32
		std::vector<hclSimClothData::ParticleData> particleDatas; // Offset: 64
		std::vector<uint16_t> fixedParticles; // Offset: 80
		bool doNormals; // Offset: 96
		std::vector<uint32_t> simOpIds; // Offset: 104
		std::vector<hclSimClothPose*> simClothPoses; // Offset: 120
		std::vector<hclConstraintSet*> staticConstraintSets; // Offset: 136
		std::vector<hclConstraintSet*> antiPinchConstraintSets; // Offset: 152
		hclSimClothData::CollidableTransformMap collidableTransformMap; // Offset: 168
		std::vector<hclCollidable*> perInstanceCollidables; // Offset: 208
		float maxParticleRadius; // Offset: 224
		std::vector<uint32_t> staticCollisionMasks; // Offset: 232
		std::vector<hclAction*> actions; // Offset: 248
		float totalMass; // Offset: 264
		hclSimClothData::TransferMotionData transferMotionData; // Offset: 268
		bool transferMotionEnabled; // Offset: 316
		bool landscapeCollisionEnabled; // Offset: 317
		hclSimClothData::LandscapeCollisionData landscapeCollisionData; // Offset: 320
		uint32_t numLandscapeCollidableParticles; // Offset: 344
		std::vector<uint16_t> triangleIndices; // Offset: 352
		std::vector<uint8_t> triangleFlips; // Offset: 368
		bool pinchDetectionEnabled; // Offset: 384
		std::vector<bool> perParticlePinchDetectionEnabledFlags; // Offset: 392
		std::vector<hclSimClothData::CollidablePinchingData> collidablePinchingDatas; // Offset: 408
		uint16_t minPinchedParticleIndex; // Offset: 424
		uint16_t maxPinchedParticleIndex; // Offset: 426
		uint32_t maxCollisionPairs; // Offset: 428
		hclVirtualCollisionPointsData virtualCollisionPointsData; // Offset: 432

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
	};
}
