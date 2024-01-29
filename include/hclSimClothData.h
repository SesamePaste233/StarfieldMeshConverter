#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include "hclShape.h"

namespace hktypes {
	class hkMatrix4Holder;
	class hkVector4Holder;
	class hclShape;
	class hclSimClothData;

	template<class tStorage>
	requires utils::_is_integer_t<tStorage>
	class hkHandle;

	class hclConstraintSet : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		std::string name;	// Offset: 24 Unk: 0
		hkHandle<uint32_t> constraintId;	// Offset: 32 Unk: 0
		uint32_t type = 0;	// Offset: 36 Unk: 0

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

		virtual void CollectBoneUsage(std::vector<uint32_t>& bone_indices) {};
		virtual int ConstraintPriority() { return 0; };
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
			inline std::string GethkClassName() override { return "hclVolumeConstraint::FrameData"; };
			inline std::string GetTranscriptId() override { return "hclVolumeConstraint::FrameData"; };
			inline uint32_t GethkClassHash() override { return 216840356; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "frameVector", "hkVector4" },
					{ "particleIndex", "hkUint16" },
					{ "weight", "hkReal" },
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
			inline std::string GethkClassName() override { return "hclVolumeConstraint::ApplyData"; };
			inline std::string GetTranscriptId() override { return "hclVolumeConstraint::ApplyData"; };
			inline uint32_t GethkClassHash() override { return 504243264; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "frameVector", "hkVector4" },
					{ "particleIndex", "hkUint16" },
					{ "stiffness", "hkReal" },
				};
			};
		};

		std::vector<hclVolumeConstraint::FrameData> frameDatas;	// Offset: 40 Unk: 0
		std::vector<hclVolumeConstraint::ApplyData> applyDatas;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclVolumeConstraint"; };
		inline std::string GetTranscriptId() override { return "hclVolumeConstraint"; };
		inline uint32_t GethkClassHash() override { return 600065596; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "frameDatas", "hkArray<hclVolumeConstraint::FrameData, hkContainerHeapAllocator>" },
				{ "applyDatas", "hkArray<hclVolumeConstraint::ApplyData, hkContainerHeapAllocator>" },
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

		inline void CollectBoneUsage(std::vector<uint32_t>& bone_indices) override {
			std::set<uint32_t> bone_set;
			for (auto& bone_plane : bonePlanes) {
				bone_set.insert(bone_plane.transformIndex);
			}
			bone_indices.insert(bone_indices.end(), bone_set.begin(), bone_set.end());
		}

		inline int ConstraintPriority() override {
			return 5;
		}

		inline void AddBonePlane(hkVector4Holder planeEquationBone, uint16_t particleIndex, uint16_t transformIndex, float stiffness) {
			BonePlane bone_plane;
			bone_plane.planeEquationBone = planeEquationBone;
			bone_plane.particleIndex = particleIndex;
			bone_plane.transformIndex = transformIndex;
			bone_plane.stiffness = stiffness;
			bonePlanes.push_back(bone_plane);
		}

		inline void AddBonePlane(Eigen::Vector3f planeNormalDir, uint16_t particleIndex, uint16_t transformIndex, float stiffness) {
			BonePlane bone_plane;
			bone_plane.planeEquationBone = hkVector4Holder::FromVector3f(planeNormalDir, 1.f);
			bone_plane.particleIndex = particleIndex;
			bone_plane.transformIndex = transformIndex;
			bone_plane.stiffness = stiffness;
			bonePlanes.push_back(bone_plane);
		}
	};

	class hclLocalRangeConstraintSet : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class LocalConstraint : public hkHolderBase {
		public:
			using BaseType = void;
			uint16_t particleIndex; // Offset: 0
			uint16_t referenceVertex; // Offset: 2
			float maximumDistance; // Offset: 4
			float maxNormalDistance; // Offset: 8
			float minNormalDistance; // Offset: 12

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclLocalRangeConstraintSet::LocalConstraint"; };
			inline std::string GetTranscriptId() override { return "hclLocalRangeConstraintSet::LocalConstraint"; };
			inline uint32_t GethkClassHash() override { return 2381122027; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "particleIndex", "hkUint16" },
					{ "referenceVertex", "hkUint16" },
					{ "maximumDistance", "hkReal" },
					{ "maxNormalDistance", "hkReal" },
					{ "minNormalDistance", "hkReal" },
				};
			};
		};

		class LocalStiffnessConstraint : public hkHolderBase {
		public:
			using BaseType = void;
			uint16_t particleIndex;	// Offset: 0 Unk: 0
			uint16_t referenceVertex;	// Offset: 2 Unk: 0
			float maximumDistance;	// Offset: 4 Unk: 0
			float maxNormalDistance;	// Offset: 8 Unk: 0
			float minNormalDistance;	// Offset: 12 Unk: 0
			float stiffness;	// Offset: 16 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclLocalRangeConstraintSet::LocalStiffnessConstraint"; };
			inline std::string GetTranscriptId() override { return "hclLocalRangeConstraintSet::LocalStiffnessConstraint"; };
			inline uint32_t GethkClassHash() override { return 2634299948; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "particleIndex", "hkUint16" },
					{ "referenceVertex", "hkUint16" },
					{ "maximumDistance", "hkReal" },
					{ "maxNormalDistance", "hkReal" },
					{ "minNormalDistance", "hkReal" },
					{ "stiffness", "hkReal" },
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
		float stiffness = 1.f;	// Offset: 76 Unk: 0
		ShapeType shapeType = ShapeType::ST_SPHERE;	// Offset: 80 Unk: 0
		bool applyNormalComponent = false;	// Offset: 84 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclLocalRangeConstraintSet"; };
		inline std::string GetTranscriptId() override { return "hclLocalRangeConstraintSet"; };
		inline uint32_t GethkClassHash() override { return 3785704016; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "localConstraints", "hkArray<hclLocalRangeConstraintSet::LocalConstraint, hkContainerHeapAllocator>" },
				{ "localStiffnessConstraints", "hkArray<hclLocalRangeConstraintSet::LocalStiffnessConstraint, hkContainerHeapAllocator>" },
				{ "referenceMeshBufferIdx", "hkUint32" },
				{ "stiffness", "hkReal" },
				{ "shapeType", "hkEnum<hclLocalRangeConstraintSet::ShapeType, hkUint32>" },
				{ "applyNormalComponent", "hkBool" },
			};
		};

		inline int ConstraintPriority() override {
			return 6;
		}

		inline void AddConstraintPair(uint16_t particleIndex, uint16_t referenceVertex, float maximumDistance, float maxNormalDistance, float minNormalDistance, float stiffness) {
			if (stiffness == 1.f) {
				LocalConstraint local_constraint;
				local_constraint.particleIndex = particleIndex;
				local_constraint.referenceVertex = referenceVertex;
				local_constraint.maximumDistance = maximumDistance;
				local_constraint.maxNormalDistance = maxNormalDistance;
				local_constraint.minNormalDistance = minNormalDistance;
				localConstraints.push_back(local_constraint);
			}
			else {
				LocalStiffnessConstraint local_stiffness_constraint;
				local_stiffness_constraint.particleIndex = particleIndex;
				local_stiffness_constraint.referenceVertex = referenceVertex;
				local_stiffness_constraint.maximumDistance = maximumDistance;
				local_stiffness_constraint.maxNormalDistance = maxNormalDistance;
				local_stiffness_constraint.minNormalDistance = minNormalDistance;
				local_stiffness_constraint.stiffness = stiffness;
				localStiffnessConstraints.push_back(local_stiffness_constraint);
			}
		}
	};

	class hclCompressibleLinkConstraintSetMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Batch : public hkHolderBase {
		public:
			using BaseType = void;
			std::array<float, 4> restLengths;	// Offset: 0 Unk: 0
			std::array<float, 4> compressionLengths;	// Offset: 16 Unk: 0
			std::array<float, 4> stiffnessesA;	// Offset: 32 Unk: 0
			std::array<float, 4> stiffnessesB;	// Offset: 48 Unk: 0
			std::array<uint16_t, 4> particlesA;	// Offset: 64 Unk: 0
			std::array<uint16_t, 4> particlesB;	// Offset: 72 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclCompressibleLinkConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclCompressibleLinkConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 4253223837; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLengths", "T[N]<hkReal, 4>" },
					{ "compressionLengths", "T[N]<hkReal, 4>" },
					{ "stiffnessesA", "T[N]<hkReal, 4>" },
					{ "stiffnessesB", "T[N]<hkReal, 4>" },
					{ "particlesA", "T[N]<hkUint16, 4>" },
					{ "particlesB", "T[N]<hkUint16, 4>" },
				};
			};
		};

		class Single : public hclConstraintSet {
		public:
			using BaseType = void;
			float restLength;	// Offset: 0 Unk: 0
			float compressionLength;	// Offset: 4 Unk: 0
			float stiffnessA;	// Offset: 8 Unk: 0
			float stiffnessB;	// Offset: 12 Unk: 0
			uint16_t particleA;	// Offset: 16 Unk: 0
			uint16_t particleB;	// Offset: 18 Unk: 0

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclCompressibleLinkConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclCompressibleLinkConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 523401191; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "restLength", "hkReal" },
					{ "compressionLength", "hkReal" },
					{ "stiffnessA", "hkReal" },
					{ "stiffnessB", "hkReal" },
					{ "particleA", "hkUint16" },
					{ "particleB", "hkUint16" },
				};
			};
		};

		std::vector<hclCompressibleLinkConstraintSetMx::Batch> batches;	// Offset: 40 Unk: 0
		std::vector<hclCompressibleLinkConstraintSetMx::Single> singles;	// Offset: 56 Unk: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclCompressibleLinkConstraintSetMx"; };
		inline std::string GetTranscriptId() override { return "hclCompressibleLinkConstraintSetMx"; };
		inline uint32_t GethkClassHash() override { return 3230409386; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "batches", "hkArray<hclCompressibleLinkConstraintSetMx::Batch, hkContainerHeapAllocator>" },
				{ "singles", "hkArray<hclCompressibleLinkConstraintSetMx::Single, hkContainerHeapAllocator>" },
			};
		};

		inline int ConstraintPriority() override {
			return 1;
		}
	};

	class hclBendStiffnessConstraintSetMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class Batch : public hkHolderBase {
		public:
			using BaseType = void;
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
			inline std::string GethkClassName() override { return "hclBendStiffnessConstraintSetMx::Batch"; };
			inline std::string GetTranscriptId() override { return "hclBendStiffnessConstraintSetMx::Batch"; };
			inline uint32_t GethkClassHash() override { return 1314719274; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "weightsA", "T[N]<hkReal, 4>" },
					{ "weightsB", "T[N]<hkReal, 4>" },
					{ "weightsC", "T[N]<hkReal, 4>" },
					{ "weightsD", "T[N]<hkReal, 4>" },
					{ "bendStiffnesses", "T[N]<hkReal, 4>" },
					{ "restCurvatures", "T[N]<hkReal, 4>" },
					{ "invMassesA", "T[N]<hkReal, 4>" },
					{ "invMassesB", "T[N]<hkReal, 4>" },
					{ "invMassesC", "T[N]<hkReal, 4>" },
					{ "invMassesD", "T[N]<hkReal, 4>" },
					{ "particlesA", "T[N]<hkUint16, 4>" },
					{ "particlesB", "T[N]<hkUint16, 4>" },
					{ "particlesC", "T[N]<hkUint16, 4>" },
					{ "particlesD", "T[N]<hkUint16, 4>" },
				};
			};
		};

		class Single : public hkHolderBase {
		public:
			using BaseType = void;
			float weightA; // Offset: 0
			float weightB; // Offset: 4
			float weightC; // Offset: 8
			float weightD; // Offset: 12
			float bendStiffness; // Offset: 16
			float restCurvature; // Offset: 20
			float invMassA; // Offset: 24
			float invMassB; // Offset: 28
			float invMassC; // Offset: 32
			float invMassD; // Offset: 36
			uint16_t particleA; // Offset: 40
			uint16_t particleB; // Offset: 42
			uint16_t particleC; // Offset: 44
			uint16_t particleD; // Offset: 46
			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclBendStiffnessConstraintSetMx::Single"; };
			inline std::string GetTranscriptId() override { return "hclBendStiffnessConstraintSetMx::Single"; };
			inline uint32_t GethkClassHash() override { return 535526491; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "weightA", "hkReal" },
					{ "weightB", "hkReal" },
					{ "weightC", "hkReal" },
					{ "weightD", "hkReal" },
					{ "bendStiffness", "hkReal" },
					{ "restCurvature", "hkReal" },
					{ "invMassA", "hkReal" },
					{ "invMassB", "hkReal" },
					{ "invMassC", "hkReal" },
					{ "invMassD", "hkReal" },
					{ "particleA", "hkUint16" },
					{ "particleB", "hkUint16" },
					{ "particleC", "hkUint16" },
					{ "particleD", "hkUint16" },
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
		inline std::string GethkClassName() override { return "hclBendStiffnessConstraintSetMx"; };
		inline std::string GetTranscriptId() override { return "hclBendStiffnessConstraintSetMx"; };
		inline uint32_t GethkClassHash() override { return 111263749; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "batches", "hkArray<hclBendStiffnessConstraintSetMx::Batch, hkContainerHeapAllocator>" },
				{ "singles", "hkArray<hclBendStiffnessConstraintSetMx::Single, hkContainerHeapAllocator>" },
				{ "maxRestPoseHeightSq", "hkReal" },
				{ "clampBendStiffness", "hkBool" },
				{ "useRestPoseConfig", "hkBool" },
			};
		};

		inline int ConstraintPriority() override {
			return 2;
		}
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

		inline int ConstraintPriority() override {
			return 3;
		}

		inline void MergeSingles() {
			uint16_t fours = singles.size() / 4;
			uint16_t i = 0;
			for (; i < fours; ++i) {
				Batch batch;
				for (uint16_t j = 0; j < 4; ++j) {
					batch.restLengths[j] = singles[i * 4 + j].restLength;
					batch.stiffnessesA[j] = singles[i * 4 + j].stiffnessA;
					batch.stiffnessesB[j] = singles[i * 4 + j].stiffnessB;
					batch.particlesA[j] = singles[i * 4 + j].particleA;
					batch.particlesB[j] = singles[i * 4 + j].particleB;
				}
				batches.push_back(batch);
			}
			if (fours > 0) {
				singles.erase(singles.begin(), singles.begin() + fours * 4);
			}
		}

		inline void AddLinkImpl(uint16_t particleA, uint16_t particleB, float stiffnessA, float stiffnessB, float restLength) {
			hclStandardLinkConstraintSetMx::Single link;
			link.particleA = particleA;
			link.particleB = particleB;
			link.stiffnessA = stiffnessA;
			link.stiffnessB = stiffnessB;
			link.restLength = restLength;
			singles.push_back(link);
		}

		void AddDefaultLink(hclSimClothData* cloth_data, uint16_t particleA, uint16_t particleB, float stiffness);
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

		inline int ConstraintPriority() override {
			return 1;
		}

		inline void MergeSingles() {
			uint16_t fours = singles.size() / 4;
			uint16_t i = 0;
			for (; i < fours; ++i) {
				Batch batch;
				for (uint16_t j = 0; j < 4; ++j) {
					batch.restLengths[j] = singles[i * 4 + j].restLength;
					batch.stiffnesses[j] = singles[i * 4 + j].stiffness;
					batch.particlesA[j] = singles[i * 4 + j].particleA;
					batch.particlesB[j] = singles[i * 4 + j].particleB;
				}
				batches.push_back(batch);
			}
			if (fours > 0) {
				singles.erase(singles.begin(), singles.begin() + fours * 4);
			}
		}

		inline void AddLinkImpl(uint16_t particleA, uint16_t particleB, float stiffness, float restLength) {
			Single link;
			link.particleA = particleA;
			link.particleB = particleB;
			link.stiffness = stiffness;
			link.restLength = restLength;
			singles.push_back(link);
		}

		void AddDefaultLink(hclSimClothData* cloth_data, uint16_t particleA, uint16_t particleB, float stiffness);
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
		uint64_t userData = 0; // Offset: 128
		hclShape* shape;  // Offset: 136
		std::string name; // Offset: 144
		float pinchDetectionRadius = 0.01f;
		int8_t pinchDetectionPriority = 0;
		bool pinchDetectionEnabled = false;
		bool virtualCollisionPointCollisionEnabled = false; // Offset: 158
		bool enabled = true; // Offset: 159

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
			float radius = 0.020000;
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

			inline void SetMass(float mass) {
				this->mass = mass;
				if (mass != 0)
					this->invMass = 1.0f / mass;
				else
					this->invMass = 0;
			}
		};

		class CollidableTransformMap : public hkHolderBase {
		public:
			using BaseType = void;
			int transformSetIndex = -1;
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
			uint32_t transformSetIndex = 0;	// Offset: 0 Unk: 0
			uint32_t transformIndex;	// Offset: 4 Unk: 0
			bool transferTranslationMotion = true;	// Offset: 8 Unk: 0
			float minTranslationSpeed = 0.0f;	// Offset: 12 Unk: 0
			float maxTranslationSpeed = 10.0f;	// Offset: 16 Unk: 0
			float minTranslationBlend = 0.6f;	// Offset: 20 Unk: 0
			float maxTranslationBlend = 0.6f;	// Offset: 24 Unk: 0
			bool transferRotationMotion = true;	// Offset: 28 Unk: 0
			float minRotationSpeed = 30.f;	// Offset: 32 Unk: 0
			float maxRotationSpeed = 90.f;	// Offset: 36 Unk: 0
			float minRotationBlend = 0.0f;	// Offset: 40 Unk: 0
			float maxRotationBlend = 0.6f;	// Offset: 44 Unk: 0

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
			float landscapeRadius = 0.05f;	// Offset: 0 Unk: 0
			bool enableStuckParticleDetection = false;	// Offset: 4 Unk: 0
			float stuckParticlesStretchFactorSq = 9.f;	// Offset: 8 Unk: 0
			bool pinchDetectionEnabled = false;	// Offset: 12 Unk: 0
			int8_t pinchDetectionPriority = 0;	// Offset: 13 Unk: 0
			float pinchDetectionRadius = 0.f;	// Offset: 16 Unk: 0
			float collisionTolerance = 0.2f;	// Offset: 20 Unk: 0

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
			bool pinchDetectionEnabled = false; // Offset: 0
			int8_t pinchDetectionPriority = 0; // Offset: 1
			float pinchDetectionRadius = 0.01f; // Offset: 4

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

		std::string name = "DefaultSimCloth";	// Offset: 24 Unk: 0
		OverridableSimulationInfo simulationInfo;	// Offset: 32 Unk: 0
		std::vector<ParticleData> particleDatas;	// Offset: 64 Unk: 0
		std::vector<uint16_t> fixedParticles;	// Offset: 80 Unk: 0
		bool doNormals = true;	// Offset: 96 Unk: 0
		std::vector<uint32_t> simOpIds;	// Offset: 104 Unk: 0
		std::vector<hclSimClothPose*> simClothPoses;	// Offset: 120 Unk: 0
		std::vector<hclConstraintSet*> staticConstraintSets;	// Offset: 136 Unk: 0
		std::vector<hclConstraintSet*> antiPinchConstraintSets;	// Offset: 152 Unk: 0
		CollidableTransformMap collidableTransformMap;	// Offset: 168 Unk: 0
		std::vector<hclCollidable*> perInstanceCollidables;	// Offset: 208 Unk: 0
		float maxParticleRadius = 0.02f;	// Offset: 224 Unk: 0
		std::vector<uint32_t> staticCollisionMasks;	// Offset: 232 Unk: 0
		//std::vector<hclAction*> actions;	// Offset: 248 Unk: 0
		float totalMass = 0.f;	// Offset: 264 Unk: 0
		TransferMotionData transferMotionData;	// Offset: 268 Unk: 0
		bool transferMotionEnabled = true;	// Offset: 316 Unk: 0
		bool landscapeCollisionEnabled = false;	// Offset: 317 Unk: 0
		LandscapeCollisionData landscapeCollisionData;	// Offset: 320 Unk: 0
		uint32_t numLandscapeCollidableParticles = 0;	// Offset: 344 Unk: 0
		std::vector<uint16_t> triangleIndices;	// Offset: 352 Unk: 0
		std::vector<uint8_t> triangleFlips;	// Offset: 368 Unk: 0
		bool pinchDetectionEnabled = false;	// Offset: 384 Unk: 0
		std::vector<bool> perParticlePinchDetectionEnabledFlags;	// Offset: 392 Unk: 0
		std::vector<hclSimClothData::CollidablePinchingData> collidablePinchingDatas;	// Offset: 408 Unk: 0
		uint16_t minPinchedParticleIndex = 0;	// Offset: 424 Unk: 0
		uint16_t maxPinchedParticleIndex = 0;	// Offset: 426 Unk: 0
		uint32_t maxCollisionPairs = 0;	// Offset: 428 Unk: 0
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

		inline void SetDefaultPoses(hclBufferedMeshObj* mesh) {
			mesh->ToSimClothData(this);
		}

		inline void SetDefaultPoses(std::vector<std::vector<float>> positions, std::vector<uint16_t> triangleIndices) {
			hclSimClothPose* pose = new hclSimClothPose();
			pose->name = "DefaultClothPose";

			auto num_particles = positions.size();

			assert(triangleIndices.size() % 3 == 0);
			auto num_triangles = triangleIndices.size() / 3;

			for (auto& old_p : this->simClothPoses) {
				if (old_p) {
					delete old_p;
				}
			}
			this->simClothPoses.clear();

			for (auto& p : positions) {
				auto pos = hkVector4Holder::FromVector3f(Eigen::Vector3f(p[0], p[1], p[2]), 1.f);
				pose->positions.push_back(pos);
			}

			this->simClothPoses.push_back(pose);

			this->triangleIndices = triangleIndices;

			this->triangleFlips.clear();
			for (size_t i = 0; i * 8 < num_triangles; i++) {
				this->triangleFlips.push_back(0);
			}

			this->particleDatas.clear();
			this->fixedParticles.clear();
			this->staticCollisionMasks.clear();
			this->perParticlePinchDetectionEnabledFlags.clear();
			for (uint32_t i = 0; i < num_particles; i++) {
				this->particleDatas.push_back(hclSimClothData::ParticleData());
				this->staticCollisionMasks.push_back(0);
				this->perParticlePinchDetectionEnabledFlags.push_back(false);
			}

			return;
		}

		inline void AddConstraintSet(hclConstraintSet* constraint_set) {
			constraint_set->constraintId.value = this->staticConstraintSets.size();
			this->staticConstraintSets.push_back(constraint_set);
		}

		inline bool IsFixedParticle(uint16_t particle_id) {
			return std::find(this->fixedParticles.begin(), this->fixedParticles.end(), particle_id) != this->fixedParticles.end();
		}

		inline void SetMassUnsafe(uint16_t particle_id, float mass) {
			this->particleDatas[particle_id].SetMass(mass);
		}

		inline void SetRadius(uint16_t particle_id, float radius) {
			this->particleDatas[particle_id].radius = radius;
			if (radius > this->maxParticleRadius) {
				this->maxParticleRadius = radius;
			}
		}

		inline void SetFriction(uint16_t particle_id, float friction) {
			this->particleDatas[particle_id].friction = friction;
		}

		inline void DistributeMass(float total_mass) {
			uint32_t num_moving_particles = this->simClothPoses[0]->positions.size() - this->fixedParticles.size();
			float mass = total_mass / num_moving_particles;
			for (uint16_t p_id = 0; p_id < this->particleDatas.size(); ++p_id) {
				this->particleDatas[p_id].SetMass(mass);
			}
			for (uint16_t p_id : this->fixedParticles) {
				this->particleDatas[p_id].SetMass(0);
			}
			this->totalMass = mass * num_moving_particles;
		}

		inline void RedistributeMass() {
			uint32_t num_moving_particles = this->simClothPoses[0]->positions.size() - this->fixedParticles.size();
			float mass = this->totalMass / num_moving_particles;
			for (uint16_t p_id = 0; p_id < this->particleDatas.size(); ++p_id) {
				this->particleDatas[p_id].SetMass(mass);
			}
			for (uint16_t p_id : this->fixedParticles) {
				this->particleDatas[p_id].SetMass(0);
			}
			this->totalMass = mass * num_moving_particles;
		}

		inline void SetFixedParticles(std::vector<uint16_t> fixed_particles) {
			this->fixedParticles = fixed_particles;
			this->RedistributeMass();
		}

		inline void SetStaticCollisionMasks(uint8_t collidable_id, std::vector<uint16_t> collidable_particles) {
			if (collidable_id >= 32 || collidable_id >= this->perInstanceCollidables.size()) {
				std::cout << "Invalid collidable id: " << collidable_id << std::endl;
				throw std::runtime_error("Invalid collidable id");
			}
			uint32_t collidable_bit = (uint32_t)1 << collidable_id;
			for (uint16_t p_id = 0; p_id < this->particleDatas.size(); ++p_id) {
				this->staticCollisionMasks[p_id] &= ~(collidable_bit);
			}
			for (auto p_id : collidable_particles) {
				this->staticCollisionMasks[p_id] |= collidable_bit;
			}
		}

		inline void SetStaticCollisionMasks(std::string collidable_name, std::vector<uint16_t> collidable_particles) {
			uint8_t collidable_id = this->GetCollidableId(collidable_name);
			if (collidable_id == uint8_t(-1)) {
				std::cout << "Invalid collidable name: " << collidable_name << std::endl;
				throw std::runtime_error("Invalid collidable name");
			}
			this->SetStaticCollisionMasks(collidable_id, collidable_particles);
		}

		inline uint8_t GetCollidableId(std::string collidable_name) {
			for (uint8_t i = 0; i < this->perInstanceCollidables.size(); ++i) {
				if (this->perInstanceCollidables[i]->name == collidable_name) {
					return i;
				}
			}
			return uint8_t(-1);
		}

		inline void SetTransferMotionBone(uint32_t bone_id) {
			this->transferMotionData.transformIndex = bone_id;
		}

		inline void Finalize() {
			for (uint16_t p_id : this->fixedParticles) {
				this->particleDatas[p_id].SetMass(0);
			}
			this->fixedParticles.clear();
			this->totalMass = 0;
			for (uint16_t p_id = 0; p_id < this->particleDatas.size(); ++p_id) {
				if (this->particleDatas[p_id].mass == 0) {
					this->fixedParticles.push_back(p_id);
				}
				else {
					this->totalMass += this->particleDatas[p_id].mass;
				}
			}
			for (auto& p_id : this->fixedParticles) {
				this->staticCollisionMasks[p_id] = 0;
			}
			this->maxParticleRadius = 0;
			for (auto& p_data : this->particleDatas) {
				if (p_data.radius > this->maxParticleRadius) {
					this->maxParticleRadius = p_data.radius;
				}
			}
		}
	};
}