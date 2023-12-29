#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hclConstraintSet;
	class hkVector4;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclVolumeConstraint : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class FrameData : public hkHolderBase {
		public:
			using BaseType = void;
			hkVector4 frameVector; // Offset: 0
			hkUint16 particleIndex; // Offset: 16
			hkReal weight; // Offset: 20

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
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class ApplyData : public hkHolderBase {
		public:
			using BaseType = void;
			hkVector4 frameVector; // Offset: 0
			hkUint16 particleIndex; // Offset: 16
			hkReal stiffness; // Offset: 20

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
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclVolumeConstraint::FrameData, hkContainerHeapAllocator> frameDatas; // Offset: 40
		hkArray<hclVolumeConstraint::ApplyData, hkContainerHeapAllocator> applyDatas; // Offset: 56

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
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
