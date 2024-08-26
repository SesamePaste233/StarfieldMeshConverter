#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkStringPtr;
	class hknpCollisionFlags;
	template <typename tTYPE>
	class ;
	class hkVector4;
	class hkQuaternion;
	class hknpCollisionControl;
	template <typename tTYPE>
	class ;
	template <typename tTYPE>
	class ;
	class hknpBodyId;
	template <typename tTYPE>
	class ;

	class hknpBodyCinfo : public hkHolderBase {
	public:
		using BaseType = void;
		hkRefPtr<hknpShape> shape; // Offset: 0
		hknpCollisionFlags flags; // Offset: 8
		hknpCollisionControl collisionCntrl; // Offset: 12
		hkUint32 collisionFilterInfo; // Offset: 16
		unsigned short materialId; // Offset: 20
		unsigned char qualityId; // Offset: 22
		hkStringPtr name; // Offset: 24
		hkUint64 userData; // Offset: 32
		unsigned char motionType; // Offset: 40
		hkVector4 position; // Offset: 48
		hkQuaternion orientation; // Offset: 64
		hkVector4 linearVelocity; // Offset: 80
		hkVector4 angularVelocity; // Offset: 96
		hkReal mass; // Offset: 112
		hkRefPtr<hknpRefMassDistribution> massDistribution; // Offset: 120
		hkRefPtr<hknpRefDragProperties> dragProperties; // Offset: 128
		unsigned short motionPropertiesId; // Offset: 136
		hknpBodyId desiredBodyId; // Offset: 140
		unsigned int motionId; // Offset: 144
		hkReal collisionLookAheadDistance; // Offset: 148
		hkRefPtr<hkLocalFrame> localFrame; // Offset: 152
		hkInt8 activationPriority; // Offset: 160

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
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
