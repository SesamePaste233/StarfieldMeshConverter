#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkStringPtr;
	class hkReferencedObject;
	class hkBool;
	class hkVector4;
	class hkTransform;
	class hclShape;

	class hclCollidable : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		hkTransform transform; // Offset: 32
		hkVector4 linearVelocity; // Offset: 96
		hkVector4 angularVelocity; // Offset: 112
		hkUint64 userData; // Offset: 128
		T*<hclShape> shape; // Offset: 136
		hkStringPtr name; // Offset: 144
		hkReal pinchDetectionRadius; // Offset: 152
		hkInt8 pinchDetectionPriority; // Offset: 156
		hkBool pinchDetectionEnabled; // Offset: 157
		hkBool virtualCollisionPointCollisionEnabled; // Offset: 158
		hkBool enabled; // Offset: 159

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
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
