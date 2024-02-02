#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hkStringPtr;
	class hknpBodyCinfo;

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
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hknpMaterial, hkContainerHeapAllocator> materials; // Offset: 24
		hkArray<hknpMotionProperties, hkContainerHeapAllocator> motionProperties; // Offset: 40
		hkArray<hknpPhysicsSystemData::bodyCinfoWithAttachment, hkContainerHeapAllocator> bodyCinfos; // Offset: 56
		hkArray<hknpConstraintCinfo, hkContainerHeapAllocator> constraintCinfos; // Offset: 72
		hkStringPtr name; // Offset: 88
		hkUint8 microStepMultiplier; // Offset: 96

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
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
