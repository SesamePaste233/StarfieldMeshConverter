#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hknpCollisionFlags;

	class hknpMotionProperties : public hkHolderBase {
	public:
		using BaseType = void;
		class DeactivationSettings : public hkHolderBase {
		public:
			using BaseType = void;
			hkReal maxDistSqrd; // Offset: 0
			hkReal maxRotSqrd; // Offset: 4
			hkReal invBlockSize; // Offset: 8
			hkInt16 pathingUpperThreshold; // Offset: 12
			hkInt16 pathingLowerThreshold; // Offset: 14
			hkUint8 numDeactivationFrequencyPasses; // Offset: 16
			hkUint8 deactivationVelocityScaleSquare; // Offset: 17
			hkUint8 minimumPathingVelocityScaleSquare; // Offset: 18
			hkUint8 spikingVelocityScaleThresholdSquared; // Offset: 19
			hkUint8 minimumSpikingVelocityScaleSquared; // Offset: 20

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpMotionProperties::DeactivationSettings"; };
			inline std::string GetTranscriptId() override { return "hknpMotionProperties::DeactivationSettings"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "maxDistSqrd", "hkReal" },
					{ "maxRotSqrd", "hkReal" },
					{ "invBlockSize", "hkReal" },
					{ "pathingUpperThreshold", "hkInt16" },
					{ "pathingLowerThreshold", "hkInt16" },
					{ "numDeactivationFrequencyPasses", "hkUint8" },
					{ "deactivationVelocityScaleSquare", "hkUint8" },
					{ "minimumPathingVelocityScaleSquare", "hkUint8" },
					{ "spikingVelocityScaleThresholdSquared", "hkUint8" },
					{ "minimumSpikingVelocityScaleSquared", "hkUint8" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class FullCastSettings : public hkHolderBase {
		public:
			using BaseType = void;
			hkReal minSeparation; // Offset: 0
			hkReal minExtraSeparation; // Offset: 4
			hkReal toiSeparation; // Offset: 8
			hkReal toiExtraSeparation; // Offset: 12
			hkReal toiAccuracy; // Offset: 16
			hkReal relativeSafeDeltaTime; // Offset: 20
			hkReal absoluteSafeDeltaTime; // Offset: 24
			hkReal keepTime; // Offset: 28
			hkReal keepDistance; // Offset: 32
			int maxIterations; // Offset: 36

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpMotionProperties::FullCastSettings"; };
			inline std::string GetTranscriptId() override { return "hknpMotionProperties::FullCastSettings"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "minSeparation", "hkReal" },
					{ "minExtraSeparation", "hkReal" },
					{ "toiSeparation", "hkReal" },
					{ "toiExtraSeparation", "hkReal" },
					{ "toiAccuracy", "hkReal" },
					{ "relativeSafeDeltaTime", "hkReal" },
					{ "absoluteSafeDeltaTime", "hkReal" },
					{ "keepTime", "hkReal" },
					{ "keepDistance", "hkReal" },
					{ "maxIterations", "int" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkUint32 isExclusive; // Offset: 0
		hknpCollisionFlags flags; // Offset: 4
		hkReal gravityFactor; // Offset: 8
		hkReal timeFactor; // Offset: 12
		hkReal maxLinearSpeed; // Offset: 16
		hkReal maxAngularSpeed; // Offset: 20
		hkReal linearDamping; // Offset: 24
		hkReal angularDamping; // Offset: 28
		hkReal solverStabilizationSpeedThreshold; // Offset: 32
		hkReal solverStabilizationSpeedReduction; // Offset: 36
		hknpMotionProperties::DeactivationSettings deactivationSettings; // Offset: 40
		hknpMotionProperties::FullCastSettings fullCastSettings; // Offset: 64

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpMotionProperties"; };
		inline std::string GetTranscriptId() override { return "hknpMotionProperties"; };
		inline uint32_t GethkClassHash() override { return 4188560537; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "isExclusive", "hkUint32" },
				{ "flags", "hknpCollisionFlags" },
				{ "gravityFactor", "hkReal" },
				{ "timeFactor", "hkReal" },
				{ "maxLinearSpeed", "hkReal" },
				{ "maxAngularSpeed", "hkReal" },
				{ "linearDamping", "hkReal" },
				{ "angularDamping", "hkReal" },
				{ "solverStabilizationSpeedThreshold", "hkReal" },
				{ "solverStabilizationSpeedReduction", "hkReal" },
				{ "deactivationSettings", "hknpMotionProperties::DeactivationSettings" },
				{ "fullCastSettings", "hknpMotionProperties::FullCastSettings" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
