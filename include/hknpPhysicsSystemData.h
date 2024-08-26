#pragma once
#include "hkInclude.h"
#include "hkTypes.h"
#include "hknpBodyCinfo.h"
#include "hknpMaterial.h"
#include "hknpMotionProperties.h"

namespace hktypes {
	class hknpBodyCinfo;
	class hknpMaterial;
	class hknpMotionProperties;
	//class hknpConstraintCinfo;

	class hknpPhysicsSystemData : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class bodyCinfoWithAttachment : public hknpBodyCinfo {
		public:
			using BaseType = hknpBodyCinfo;
			int attachedBody; // Offset: 176

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpPhysicsSystemData::bodyCinfoWithAttachment"; };
			inline std::string GetTranscriptId() override { return "hknpPhysicsSystemData::bodyCinfoWithAttachment"; };
			inline uint32_t GethkClassHash() override { return 2149479961; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "attachedBody", "int" },
				};
			};
		};

		std::vector<hknpMaterial> materials; // Offset: 24
		std::vector<hknpMotionProperties> motionProperties; // Offset: 40
		std::vector<hknpPhysicsSystemData::bodyCinfoWithAttachment> bodyCinfos; // Offset: 56
		//std::vector<hknpConstraintCinfo> constraintCinfos; // Offset: 72 Always empty
		std::string name; // Offset: 88
		uint8_t microStepMultiplier = 1; // Offset: 96

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpPhysicsSystemData"; };
		inline std::string GetTranscriptId() override { return "hknpPhysicsSystemData"; };
		inline uint32_t GethkClassHash() override { return 2741073764; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "materials", "hkArray<hknpMaterial, hkContainerHeapAllocator>" },
				{ "motionProperties", "hkArray<hknpMotionProperties, hkContainerHeapAllocator>" },
				{ "bodyCinfos", "hkArray<hknpPhysicsSystemData::bodyCinfoWithAttachment, hkContainerHeapAllocator>" },
				{ "constraintCinfos", "hkArray<hknpConstraintCinfo, hkContainerHeapAllocator>" },
				{ "name", "hkStringPtr" },
				{ "microStepMultiplier", "hkUint8" },
			};
		};
	};
}