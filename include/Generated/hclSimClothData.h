#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkStringPtr;
	class hkBool;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hkVector4;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hclVirtualCollisionPointsData;

	class hclSimClothData : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class OverridableSimulationInfo : public hkHolderBase {
		public:
			using BaseType = void;
			hkVector4 gravity; // Offset: 0
			hkReal globalDampingPerSecond; // Offset: 16

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimClothData::OverridableSimulationInfo"; };
			inline std::string GetTranscriptId() override { return "hclSimClothData::OverridableSimulationInfo"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "gravity", "hkVector4" },
					{ "globalDampingPerSecond", "hkReal" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class ParticleData : public hkHolderBase {
		public:
			using BaseType = void;
			hkReal mass; // Offset: 0
			hkReal invMass; // Offset: 4
			hkReal radius; // Offset: 8
			hkReal friction; // Offset: 12

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimClothData::ParticleData"; };
			inline std::string GetTranscriptId() override { return "hclSimClothData::ParticleData"; };
			inline uint32_t GethkClassHash() override { return 2467200052; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "mass", "hkReal" },
					{ "invMass", "hkReal" },
					{ "radius", "hkReal" },
					{ "friction", "hkReal" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class CollidableTransformMap : public hkHolderBase {
		public:
			using BaseType = void;
			hkInt32 transformSetIndex; // Offset: 0
			hkArray<hkUint32, hkContainerHeapAllocator> transformIndices; // Offset: 8
			hkArray<hkMatrix4, hkContainerHeapAllocator> offsets; // Offset: 24

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimClothData::CollidableTransformMap"; };
			inline std::string GetTranscriptId() override { return "hclSimClothData::CollidableTransformMap"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "transformSetIndex", "hkInt32" },
					{ "transformIndices", "hkArray<hkUint32, hkContainerHeapAllocator>" },
					{ "offsets", "hkArray<hkMatrix4, hkContainerHeapAllocator>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class TransferMotionData : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint32 transformSetIndex; // Offset: 0
			hkUint32 transformIndex; // Offset: 4
			hkBool transferTranslationMotion; // Offset: 8
			hkReal minTranslationSpeed; // Offset: 12
			hkReal maxTranslationSpeed; // Offset: 16
			hkReal minTranslationBlend; // Offset: 20
			hkReal maxTranslationBlend; // Offset: 24
			hkBool transferRotationMotion; // Offset: 28
			hkReal minRotationSpeed; // Offset: 32
			hkReal maxRotationSpeed; // Offset: 36
			hkReal minRotationBlend; // Offset: 40
			hkReal maxRotationBlend; // Offset: 44

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimClothData::TransferMotionData"; };
			inline std::string GetTranscriptId() override { return "hclSimClothData::TransferMotionData"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "transformSetIndex", "hkUint32" },
					{ "transformIndex", "hkUint32" },
					{ "transferTranslationMotion", "hkBool" },
					{ "minTranslationSpeed", "hkReal" },
					{ "maxTranslationSpeed", "hkReal" },
					{ "minTranslationBlend", "hkReal" },
					{ "maxTranslationBlend", "hkReal" },
					{ "transferRotationMotion", "hkBool" },
					{ "minRotationSpeed", "hkReal" },
					{ "maxRotationSpeed", "hkReal" },
					{ "minRotationBlend", "hkReal" },
					{ "maxRotationBlend", "hkReal" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class LandscapeCollisionData : public hkHolderBase {
		public:
			using BaseType = void;
			hkReal landscapeRadius; // Offset: 0
			hkBool enableStuckParticleDetection; // Offset: 4
			hkReal stuckParticlesStretchFactorSq; // Offset: 8
			hkBool pinchDetectionEnabled; // Offset: 12
			hkInt8 pinchDetectionPriority; // Offset: 13
			hkReal pinchDetectionRadius; // Offset: 16
			hkReal collisionTolerance; // Offset: 20

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimClothData::LandscapeCollisionData"; };
			inline std::string GetTranscriptId() override { return "hclSimClothData::LandscapeCollisionData"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "landscapeRadius", "hkReal" },
					{ "enableStuckParticleDetection", "hkBool" },
					{ "stuckParticlesStretchFactorSq", "hkReal" },
					{ "pinchDetectionEnabled", "hkBool" },
					{ "pinchDetectionPriority", "hkInt8" },
					{ "pinchDetectionRadius", "hkReal" },
					{ "collisionTolerance", "hkReal" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class CollidablePinchingData : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimClothData::CollidablePinchingData"; };
			inline std::string GetTranscriptId() override { return "hclSimClothData::CollidablePinchingData"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkStringPtr name; // Offset: 24
		hclSimClothData::OverridableSimulationInfo simulationInfo; // Offset: 32
		hkArray<hclSimClothData::ParticleData, hkContainerHeapAllocator> particleDatas; // Offset: 64
		hkArray<hkUint16, hkContainerHeapAllocator> fixedParticles; // Offset: 80
		hkBool doNormals; // Offset: 96
		hkArray<unsigned int, hkContainerHeapAllocator> simOpIds; // Offset: 104
		hkArray<T*<hclSimClothPose>, hkContainerHeapAllocator> simClothPoses; // Offset: 120
		hkArray<T*<hclConstraintSet>, hkContainerHeapAllocator> staticConstraintSets; // Offset: 136
		hkArray<T*<hclConstraintSet>, hkContainerHeapAllocator> antiPinchConstraintSets; // Offset: 152
		hclSimClothData::CollidableTransformMap collidableTransformMap; // Offset: 168
		hkArray<T*<hclCollidable>, hkContainerHeapAllocator> perInstanceCollidables; // Offset: 208
		hkReal maxParticleRadius; // Offset: 224
		hkArray<hkUint32, hkContainerHeapAllocator> staticCollisionMasks; // Offset: 232
		hkArray<T*<hclAction>, hkContainerHeapAllocator> actions; // Offset: 248
		hkReal totalMass; // Offset: 264
		hclSimClothData::TransferMotionData transferMotionData; // Offset: 268
		hkBool transferMotionEnabled; // Offset: 316
		hkBool landscapeCollisionEnabled; // Offset: 317
		hclSimClothData::LandscapeCollisionData landscapeCollisionData; // Offset: 320
		hkUint32 numLandscapeCollidableParticles; // Offset: 344
		hkArray<hkUint16, hkContainerHeapAllocator> triangleIndices; // Offset: 352
		hkArray<hkUint8, hkContainerHeapAllocator> triangleFlips; // Offset: 368
		hkBool pinchDetectionEnabled; // Offset: 384
		hkArray<hkBool, hkContainerHeapAllocator> perParticlePinchDetectionEnabledFlags; // Offset: 392
		hkArray<hclSimClothData::CollidablePinchingData, hkContainerHeapAllocator> collidablePinchingDatas; // Offset: 408
		hkUint16 minPinchedParticleIndex; // Offset: 424
		hkUint16 maxPinchedParticleIndex; // Offset: 426
		hkUint32 maxCollisionPairs; // Offset: 428
		hclVirtualCollisionPointsData virtualCollisionPointsData; // Offset: 432

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclSimClothData"; };
		inline std::string GetTranscriptId() override { return "hclSimClothData"; };
		inline uint32_t GethkClassHash() override { return 10356195; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "simulationInfo", "hclSimClothData::OverridableSimulationInfo" },
				{ "particleDatas", "hkArray<hclSimClothData::ParticleData, hkContainerHeapAllocator>" },
				{ "fixedParticles", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "doNormals", "hkBool" },
				{ "simOpIds", "hkArray<unsigned int, hkContainerHeapAllocator>" },
				{ "simClothPoses", "hkArray<T*<hclSimClothPose>, hkContainerHeapAllocator>" },
				{ "staticConstraintSets", "hkArray<T*<hclConstraintSet>, hkContainerHeapAllocator>" },
				{ "antiPinchConstraintSets", "hkArray<T*<hclConstraintSet>, hkContainerHeapAllocator>" },
				{ "collidableTransformMap", "hclSimClothData::CollidableTransformMap" },
				{ "perInstanceCollidables", "hkArray<T*<hclCollidable>, hkContainerHeapAllocator>" },
				{ "maxParticleRadius", "hkReal" },
				{ "staticCollisionMasks", "hkArray<hkUint32, hkContainerHeapAllocator>" },
				{ "actions", "hkArray<T*<hclAction>, hkContainerHeapAllocator>" },
				{ "totalMass", "hkReal" },
				{ "transferMotionData", "hclSimClothData::TransferMotionData" },
				{ "transferMotionEnabled", "hkBool" },
				{ "landscapeCollisionEnabled", "hkBool" },
				{ "landscapeCollisionData", "hclSimClothData::LandscapeCollisionData" },
				{ "numLandscapeCollidableParticles", "hkUint32" },
				{ "triangleIndices", "hkArray<hkUint16, hkContainerHeapAllocator>" },
				{ "triangleFlips", "hkArray<hkUint8, hkContainerHeapAllocator>" },
				{ "pinchDetectionEnabled", "hkBool" },
				{ "perParticlePinchDetectionEnabledFlags", "hkArray<hkBool, hkContainerHeapAllocator>" },
				{ "collidablePinchingDatas", "hkArray<hclSimClothData::CollidablePinchingData, hkContainerHeapAllocator>" },
				{ "minPinchedParticleIndex", "hkUint16" },
				{ "maxPinchedParticleIndex", "hkUint16" },
				{ "maxCollisionPairs", "hkUint32" },
				{ "virtualCollisionPointsData", "hclVirtualCollisionPointsData" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
