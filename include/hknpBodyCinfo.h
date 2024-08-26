#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include "hknpShape.h"

namespace hktypes {
	class hknpShape;

	enum class hknpCollisionFlags : uint32_t {
		// Unknown
	};

	enum class hknpCollisionControl : uint32_t {
		// Unknown
	};

	class hknpMassDistribution : public hkHolderBase {
	public:
		using BaseType = void;
		hkVector4Holder centerOfMassAndVolume; // Offset: 0
		hkQuaternionHolder majorAxisSpace; // Offset: 16
		hkVector4Holder inertiaTensor; // Offset: 32

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpMassDistribution"; };
		inline std::string GetTranscriptId() override { return "hknpMassDistribution"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "centerOfMassAndVolume", "hkVector4" },
				{ "majorAxisSpace", "hkQuaternion" },
				{ "inertiaTensor", "hkVector4" },
			};
		};
	};

	class hknpRefMassDistribution : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hknpMassDistribution massDistribution; // Offset: 32

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpRefMassDistribution"; };
		inline std::string GetTranscriptId() override { return "hknpRefMassDistribution"; };
		inline uint32_t GethkClassHash() override { return 46991855; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "massDistribution", "hknpMassDistribution" },
			};
		};
	};

	class hknpBodyId : public hkHolderBase {
	public:
		using BaseType = void;
		uint32_t serialAndIndex; // Offset: 0

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpBodyId"; };
		inline std::string GetTranscriptId() override { return "hknpBodyId"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "serialAndIndex", "hkUint32" },
			};
		};
	};

	class hknpBodyCinfo : public hkHolderBase {
	public:
		using BaseType = void;
		hknpShape* shape; // Offset: 0
		hknpCollisionFlags flags; // Offset: 8
		hknpCollisionControl collisionCntrl; // Offset: 12
		uint32_t collisionFilterInfo; // Offset: 16
		unsigned short materialId; // Offset: 20
		unsigned char qualityId; // Offset: 22
		std::string name; // Offset: 24
		uint64_t userData; // Offset: 32
		unsigned char motionType; // Offset: 40
		hkVector4Holder position; // Offset: 48
		hkQuaternionHolder orientation; // Offset: 64
		hkVector4Holder linearVelocity; // Offset: 80
		hkVector4Holder angularVelocity; // Offset: 96
		float mass; // Offset: 112
		hknpRefMassDistribution* massDistribution; // Offset: 120
		//hknpRefDragProperties* dragProperties; // Offset: 128 Always nullptr
		unsigned short motionPropertiesId; // Offset: 136
		hknpBodyId desiredBodyId; // Offset: 140
		unsigned int motionId; // Offset: 144
		float collisionLookAheadDistance; // Offset: 148
		//hkLocalFrame* localFrame; // Offset: 152 Always nullptr
		int8_t activationPriority; // Offset: 160

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpBodyCinfo"; };
		inline std::string GetTranscriptId() override { return "hknpBodyCinfo"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "shape", "hkRefPtr<hknpShape>" },
				{ "flags", "hknpCollisionFlags" },
				{ "collisionCntrl", "hknpCollisionControl" },
				{ "collisionFilterInfo", "hkUint32" },
				{ "materialId", "unsigned short" },
				{ "qualityId", "unsigned char" },
				{ "name", "hkStringPtr" },
				{ "userData", "hkUint64" },
				{ "motionType", "unsigned char" },
				{ "position", "hkVector4" },
				{ "orientation", "hkQuaternion" },
				{ "linearVelocity", "hkVector4" },
				{ "angularVelocity", "hkVector4" },
				{ "mass", "hkReal" },
				{ "massDistribution", "hkRefPtr<hknpRefMassDistribution>" },
				{ "dragProperties", "hkRefPtr<hknpRefDragProperties>" },
				{ "motionPropertiesId", "unsigned short" },
				{ "desiredBodyId", "hknpBodyId" },
				{ "motionId", "unsigned int" },
				{ "collisionLookAheadDistance", "hkReal" },
				{ "localFrame", "hkRefPtr<hkLocalFrame>" },
				{ "activationPriority", "hkInt8" },
			};
		};
	};
}