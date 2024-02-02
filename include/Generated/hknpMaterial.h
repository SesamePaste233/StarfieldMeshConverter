#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkStringPtr;
	class hknpCollisionFlags;
	template <typename tENUM, typename tSTORAGE>
	class ;
	class hknpSurfaceVelocity;
	template <typename tENUM, typename tSTORAGE>
	class ;
	class hkHalf16;
	class hkUFloat8;
	template <typename tENUM, typename tSTORAGE>
	class ;

	class hknpMaterial : public hkHolderBase {
	public:
		using BaseType = void;
		class TriggerType : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpMaterial::TriggerType"; };
			inline std::string GetTranscriptId() override { return "hknpMaterial::TriggerType"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class CombinePolicy : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpMaterial::CombinePolicy"; };
			inline std::string GetTranscriptId() override { return "hknpMaterial::CombinePolicy"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class MassChangerCategory : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpMaterial::MassChangerCategory"; };
			inline std::string GetTranscriptId() override { return "hknpMaterial::MassChangerCategory"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkStringPtr name; // Offset: 0
		hkUint32 isExclusive; // Offset: 8
		hknpCollisionFlags flags; // Offset: 12
		hkEnum<hknpMaterial::TriggerType, hkUint8> triggerType; // Offset: 16
		hkUFloat8 triggerManifoldTolerance; // Offset: 17
		hkHalf16 dynamicFriction; // Offset: 18
		hkHalf16 staticFriction; // Offset: 20
		hkHalf16 restitution; // Offset: 22
		hkEnum<hknpMaterial::CombinePolicy, hkUint8> frictionCombinePolicy; // Offset: 24
		hkEnum<hknpMaterial::CombinePolicy, hkUint8> restitutionCombinePolicy; // Offset: 25
		hkReal weldingTolerance; // Offset: 28
		hkReal maxContactImpulse; // Offset: 32
		hkReal fractionOfClippedImpulseToApply; // Offset: 36
		hkEnum<hknpMaterial::MassChangerCategory, hkUint8> massChangerCategory; // Offset: 40
		hkHalf16 massChangerHeavyObjectFactor; // Offset: 42
		hkHalf16 softContactForceFactor; // Offset: 44
		hkHalf16 softContactDampFactor; // Offset: 46
		hkUFloat8 softContactSeparationVelocity; // Offset: 48
		T*<hknpSurfaceVelocity> surfaceVelocity; // Offset: 56
		hkHalf16 disablingCollisionsBetweenCvxCvxDynamicObjectsDistance; // Offset: 64
		hkUint64 userData; // Offset: 72

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
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
