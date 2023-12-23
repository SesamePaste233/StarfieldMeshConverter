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
		using BaseType = hkReferencedObject;
		std::string name;	// Offset: 24 Unk: 0
		hkHandle<uint32_t> constraintId;	// Offset: 32 Unk: 0
		uint32_t type;	// Offset: 36 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclConstraintSet"; };
		inline std::string GetTranscriptId() override { return "hclConstraintSet"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "constraintId", "hkHandle<hkUint32, 2147483647>" },
				{ "type", "unsigned int" },
			};
		};
	};

	class hclVolumeConstraint : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class FrameData : public hkHolderBase {
		public:
			using BaseType = void;
			hkVector4Holder frameVector;	// Offset: 0 Unk: 0
			uint16_t particleIndex;	// Offset: 16 Unk: 0
			float weight;	// Offset: 20 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		class ApplyData : public hkHolderBase {
		public:
			using BaseType = void;
			hkVector4Holder frameVector;	// Offset: 0 Unk: 0
			uint16_t particleIndex;	// Offset: 16 Unk: 0
			float stiffness;	// Offset: 20 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		std::vector<hclVolumeConstraint::FrameData> frameDatas;	// Offset: 40 Unk: 0
		std::vector<hclVolumeConstraint::ApplyData> applyDatas;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
	};

	class hclBonePlanesConstraintSet : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class BonePlane : public hkHolderBase {
		public:
			using BaseType = void;
			hkVector4Holder planeEquationBone;	// Offset: 0 Unk: 0
			uint16_t particleIndex;	// Offset: 16 Unk: 0
			uint16_t transformIndex;	// Offset: 18 Unk: 0
			float stiffness;	// Offset: 20 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBonePlanesConstraintSet::BonePlane"; };
			inline std::string GetTranscriptId() override { return "hclBonePlanesConstraintSet::BonePlane"; };
			inline uint32_t GethkClassHash() override { return 3326918113; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "planeEquationBone", "hkVector4" },
					{ "particleIndex", "hkUint16" },
					{ "transformIndex", "hkUint16" },
					{ "stiffness", "hkReal" },
				};
			};
		};
		std::vector<BonePlane> bonePlanes;	// Offset: 40 Unk: 0
		uint32_t transformSetIndex;	// Offset: 56 Unk: 0
		
		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclBonePlanesConstraintSet"; };
		inline std::string GetTranscriptId() override { return "hclBonePlanesConstraintSet"; };
		inline uint32_t GethkClassHash() override { return 2481738222; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "bonePlanes", "hkArray<hclBonePlanesConstraintSet::BonePlane, hkContainerHeapAllocator>" },
				{ "transformSetIndex", "hkUint32" },
			};
		};
	};

	class hclLocalRangeConstraintSet : public hclConstraintSet {
	public:
		class LocalConstraint : public hkHolderBase {
		public:
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override { return true; };
			bool ToInstance(hkreflex::hkClassInstance* instance) override { return true; };
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
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
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
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
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
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
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
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
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		std::vector<hclCompressibleLinkConstraintSetMx::Batch> batches;	// Offset: 40 Unk: 0
		std::vector<hclCompressibleLinkConstraintSetMx::Single> singles;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
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
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		class Single : public hkHolderBase {
		public:
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return ""; };
			inline std::string GetTranscriptId() override { return ""; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		std::vector<hclBendStiffnessConstraintSetMx::Batch> batches;	// Offset: 40 Unk: 0
		std::vector<hclBendStiffnessConstraintSetMx::Single> singles;	// Offset: 56 Unk: 0
		float maxRestPoseHeightSq;	// Offset: 72 Unk: 0
		bool clampBendStiffness;	// Offset: 76 Unk: 0
		bool useRestPoseConfig;	// Offset: 77 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return ""; };
		inline std::string GetTranscriptId() override { return ""; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
			};
		};
	};

	class hclStandardLinkConstraintSetMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Batch : public hkHolderBase {
		public:
			using BaseType = void;
			float restLengths[4];	// Offset: 0 Unk: 0
			float stiffnessesA[4];	// Offset: 16 Unk: 0
			float stiffnessesB[4];	// Offset: 32 Unk: 0
			uint16_t particlesA[4];	// Offset: 48 Unk: 0
			uint16_t particlesB[4];	// Offset: 56 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStandardLinkConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclStandardLinkConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		class Single : public hkHolderBase {
		public:
			using BaseType = void;
			float restLength;	// Offset: 0 Unk: 0
			float stiffnessA;	// Offset: 4 Unk: 0
			float stiffnessB;	// Offset: 8 Unk: 0
			uint16_t particleA;	// Offset: 12 Unk: 0
			uint16_t particleB;	// Offset: 14 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStandardLinkConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclStandardLinkConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 2457992725; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLength", "hkReal" },
					{ "stiffnessA", "hkReal" },
					{ "stiffnessB", "hkReal" },
					{ "particleA", "hkUint16" },
					{ "particleB", "hkUint16" },
				};
			};
		};

		std::vector<Batch> batches;	// Offset: 40 Unk: 0
		std::vector<Single> singles;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclStandardLinkConstraintSetMx"; };
		inline std::string GetTranscriptId() override { return "hclStandardLinkConstraintSetMx"; };
		inline uint32_t GethkClassHash() override { return 4021914366; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "batches", "hkArray<hclStandardLinkConstraintSetMx::Batch, hkContainerHeapAllocator>" },
				{ "singles", "hkArray<hclStandardLinkConstraintSetMx::Single, hkContainerHeapAllocator>" },
			};
		};
	};

	class hclStretchLinkConstraintSetMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Batch : public hkHolderBase {
		public:
			using BaseType = void;
			std::array<float, 4> restLengths;	// Offset: 0 Unk: 0
			std::array<float, 4> stiffnesses;	// Offset: 16 Unk: 0
			std::array<uint16_t, 4> particlesA;	// Offset: 32 Unk: 0
			std::array<uint16_t, 4> particlesB;	// Offset: 40 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStretchLinkConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclStretchLinkConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 1860398617; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLengths", "T[N]<hkReal, 4>" },
					{ "stiffnesses", "T[N]<hkReal, 4>" },
					{ "particlesA", "T[N]<hkUint16, 4>" },
					{ "particlesB", "T[N]<hkUint16, 4>" },
				};
			};
		};

		class Single : public hkHolderBase {
		public:
			using BaseType = void;
			float restLength;	// Offset: 0 Unk: 0
			float stiffness;	// Offset: 4 Unk: 0
			uint32_t particleA;	// Offset: 8 Unk: 0
			uint32_t particleB;	// Offset: 12 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclStretchLinkConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclStretchLinkConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
		};

		std::vector<Batch> batches;	// Offset: 40 Unk: 0
		std::vector<Single> singles;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclStretchLinkConstraintSetMx"; };
		inline std::string GetTranscriptId() override { return "hclStretchLinkConstraintSetMx"; };
		inline uint32_t GethkClassHash() override { return 3791460596; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "batches", "hkArray<hclStretchLinkConstraintSetMx::Batch, hkContainerHeapAllocator>" },
				{ "singles", "hkArray<hclStretchLinkConstraintSetMx::Single, hkContainerHeapAllocator>" },
			};
		};
	};

	class hclSimClothPose : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		std::string name;	// Offset: 24 Unk: 0
		std::vector<hkVector4Holder> positions;	// Offset: 32 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclSimClothPose"; };
		inline std::string GetTranscriptId() override { return "hclSimClothPose"; };
		inline uint32_t GethkClassHash() override { return 2913572451; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "positions", "hkArray<hkVector4, hkContainerHeapAllocator>" },
			};
		};
	};

	class hclCollidable : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkMatrix4Holder transform;  // Offset: 32
		hkVector4Holder linearVelocity; // Offset: 96
		hkVector4Holder angularVelocity; // Offset: 112
		uint64_t userData; // Offset: 128
		hclShape* shape;  // Offset: 136
		std::string name; // Offset: 144
		float pinchDetectionRadius;
		int8_t pinchDetectionPriority;
		bool pinchDetectionEnabled;
		bool virtualCollisionPointCollisionEnabled; // Offset: 158
		bool enabled; // Offset: 159

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclCollidable"; };
		inline std::string GetTranscriptId() override { return "hclCollidable"; };
		inline uint32_t GethkClassHash() override { return 93767303; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "transform", "hkTransform" },
				{ "linearVelocity", "hkVector4" },
				{ "angularVelocity", "hkVector4" },
				{ "userData", "hkUint64" },
				{ "shape", "T*<hclShape>" },
				{ "name", "hkStringPtr" },
				{ "pinchDetectionRadius", "hkReal" },
				{ "pinchDetectionPriority", "hkInt8" },
				{ "pinchDetectionEnabled", "hkBool" },
				{ "virtualCollisionPointCollisionEnabled", "hkBool" },
				{ "enabled", "hkBool" },
			};
		};
	};

	class hclSimClothData : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class OverridableSimulationInfo : public hkHolderBase {
		public:
			using BaseType = void;
			Eigen::Vector4f gravity;	// Offset: 0 Unk: 0
			float globalDampingPerSecond;	// Offset: 16 Unk: 0

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
		};

		class ParticleData : public hkHolderBase {
		public:
			using BaseType = void;
			float mass = 1.000000;
			float invMass = 1.000000;
			float radius = 0.000000;
			float friction = 0.500000;

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
		};

		class CollidableTransformMap : public hkHolderBase {
		public:
			using BaseType = void;
			int transformSetIndex;
			std::vector<uint32_t> transformIndices;
			std::vector<hkMatrix4Holder> offsets;

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
		};

		class TransferMotionData : public hkHolderBase {
		public:
			using BaseType = void;
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
		};

		class LandscapeCollisionData :public hkHolderBase {
		public:
			using BaseType = void;
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
		};

		class CollidablePinchingData : public hkHolderBase {
		public:
			using BaseType = void;
			bool pinchDetectionEnabled; // Offset: 0
			int8_t pinchDetectionPriority; // Offset: 1
			float pinchDetectionRadius; // Offset: 4

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclSimClothData::CollidablePinchingData"; };
			inline std::string GetTranscriptId() override { return "hclSimClothData::CollidablePinchingData"; };
			inline uint32_t GethkClassHash() override { return 3233440473; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "pinchDetectionEnabled", "hkBool" },
					{ "pinchDetectionPriority", "hkInt8" },
					{ "pinchDetectionRadius", "hkReal" },
				};
			};
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
	};
}