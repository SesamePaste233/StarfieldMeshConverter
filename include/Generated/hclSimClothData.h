#pragma once
#include "hkInclude.h"

#include "Generated\hkReferencedObject.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hkArray.h"
#include "Generated\hclVirtualCollisionPointsData.h"

namespace hktypes{
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
	template <typename tT, typename tAllocator>
	class hkArray;
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
			static inline std::string GethkClassName() { return "hclSimClothData::OverridableSimulationInfo"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
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
			static inline std::string GethkClassName() { return "hclSimClothData::ParticleData"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
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
			static inline std::string GethkClassName() { return "hclSimClothData::CollidableTransformMap"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
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
			static inline std::string GethkClassName() { return "hclSimClothData::TransferMotionData"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
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
			static inline std::string GethkClassName() { return "hclSimClothData::LandscapeCollisionData"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
		};

		class CollidablePinchingData : public hkHolderBase {
		public:
			using BaseType = void;
			hkBool pinchDetectionEnabled; // Offset: 0
			hkInt8 pinchDetectionPriority; // Offset: 1
			hkReal pinchDetectionRadius; // Offset: 4

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			static inline std::string GethkClassName() { return "hclSimClothData::CollidablePinchingData"; };
			static inline std::vector<std::string> GetTemplateArgs();
			static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
			static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
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
		static inline std::string GethkClassName() { return "hclSimClothData"; };
		static inline std::vector<std::string> GetTemplateArgs();
		static inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> GetFieldTypeAndNames();
		static inline hkreflex::hkClassBase::DefinitionPropertyBag GetPropertyBag();
	};
}
