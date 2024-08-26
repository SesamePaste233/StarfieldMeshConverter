#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include "hknpBodyCinfo.h"

namespace hktypes {
	enum class hknpCollisionFlags : uint32_t;

	class hknpMotionProperties : public hkHolderBase {
	public:
		using BaseType = void;
		class DeactivationSettings : public hkHolderBase {
		public:
			using BaseType = void;
			float maxDistSqrd = 0.002500;
			float maxRotSqrd = 0.002500;
			float invBlockSize = 1.000000;
			short pathingUpperThreshold = 26623;
			short pathingLowerThreshold = -26213;
			unsigned char numDeactivationFrequencyPasses = 4;
			unsigned char deactivationVelocityScaleSquare = 115;
			unsigned char minimumPathingVelocityScaleSquare = 117;
			unsigned char spikingVelocityScaleThresholdSquared = 6;
			unsigned char minimumSpikingVelocityScaleSquared = 115;

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
		};

		class FullCastSettings : public hkHolderBase {
		public:
			using BaseType = void;
			float minSeparation = -0.500000;
			float minExtraSeparation = -0.125000;
			float toiSeparation = -0.250000;
			float toiExtraSeparation = -0.087500;
			float toiAccuracy = 0.010000;
			float relativeSafeDeltaTime = 0.025000;
			float absoluteSafeDeltaTime = 0.000025;
			float keepTime = 0.050000;
			float keepDistance = 0.050000;
			int maxIterations = 5;

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
		};

		hkUint32 isExclusive = 0; // Offset: 0
		hknpCollisionFlags flags = hknpCollisionFlags(0); // Offset: 4
		hkReal gravityFactor = 1.000000; // Offset: 8
		hkReal timeFactor = 1.000000; // Offset: 12
		hkReal maxLinearSpeed = 100.000000; // Offset: 16
		hkReal maxAngularSpeed = 200.000000; // Offset: 20
		hkReal linearDamping = 0.100000; // Offset: 24
		hkReal angularDamping = 0.050000; // Offset: 28
		hkReal solverStabilizationSpeedThreshold = 0.166770; // Offset: 32
		hkReal solverStabilizationSpeedReduction = 0.490500; // Offset: 36
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
	};
}