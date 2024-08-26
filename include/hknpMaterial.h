#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include "hknpBodyCinfo.h"

namespace hktypes {
	enum class hknpCollisionFlags : uint32_t;

	class hknpMaterial : public hkHolderBase {
	public:
		using BaseType = void;
		enum class TriggerType : uint8_t {
			// Unknown
		};

		enum class CombinePolicy : uint8_t {
			// Unknown
		};

		enum class MassChangerCategory : uint8_t {
			// Unknown
		};

		std::string name; // Offset: 0
		uint32_t isExclusive; // Offset: 8
		hknpCollisionFlags flags; // Offset: 12
		hknpMaterial::TriggerType triggerType; // Offset: 16
		hkUFloat8 triggerManifoldTolerance; // Offset: 17
		hkHalf16 dynamicFriction; // Offset: 18
		hkHalf16 staticFriction; // Offset: 20
		hkHalf16 restitution; // Offset: 22
		hknpMaterial::CombinePolicy frictionCombinePolicy; // Offset: 24
		hknpMaterial::CombinePolicy restitutionCombinePolicy; // Offset: 25
		float weldingTolerance; // Offset: 28
		float maxContactImpulse; // Offset: 32
		float fractionOfClippedImpulseToApply; // Offset: 36
		hknpMaterial::MassChangerCategory massChangerCategory; // Offset: 40
		hkHalf16 massChangerHeavyObjectFactor; // Offset: 42
		hkHalf16 softContactForceFactor; // Offset: 44
		hkHalf16 softContactDampFactor; // Offset: 46
		hkUFloat8 softContactSeparationVelocity; // Offset: 48
		//hknpSurfaceVelocity* surfaceVelocity; // Offset: 56
		hkHalf16 disablingCollisionsBetweenCvxCvxDynamicObjectsDistance; // Offset: 64
		uint64_t userData; // Offset: 72

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpMaterial"; };
		inline std::string GetTranscriptId() override { return "hknpMaterial"; };
		inline uint32_t GethkClassHash() override { return 1672333247; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "isExclusive", "hkUint32" },
				{ "flags", "hknpCollisionFlags" },
				{ "triggerType", "hkEnum<hknpMaterial::TriggerType, hkUint8>" },
				{ "triggerManifoldTolerance", "hkUFloat8" },
				{ "dynamicFriction", "hkHalf16" },
				{ "staticFriction", "hkHalf16" },
				{ "restitution", "hkHalf16" },
				{ "frictionCombinePolicy", "hkEnum<hknpMaterial::CombinePolicy, hkUint8>" },
				{ "restitutionCombinePolicy", "hkEnum<hknpMaterial::CombinePolicy, hkUint8>" },
				{ "weldingTolerance", "hkReal" },
				{ "maxContactImpulse", "hkReal" },
				{ "fractionOfClippedImpulseToApply", "hkReal" },
				{ "massChangerCategory", "hkEnum<hknpMaterial::MassChangerCategory, hkUint8>" },
				{ "massChangerHeavyObjectFactor", "hkHalf16" },
				{ "softContactForceFactor", "hkHalf16" },
				{ "softContactDampFactor", "hkHalf16" },
				{ "softContactSeparationVelocity", "hkUFloat8" },
				{ "surfaceVelocity", "T*<hknpSurfaceVelocity>" },
				{ "disablingCollisionsBetweenCvxCvxDynamicObjectsDistance", "hkHalf16" },
				{ "userData", "hkUint64" },
			};
		};
	};
}