#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkVector4f;
	class hclConstraintSet;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hclVolumeConstraintMx : public hclConstraintSet {
	public:
		using BaseType = hclConstraintSet;
		class FrameBatchData : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkVector4, 4> frameVector; // Offset: 0
			T[N]<hkReal, 4> weight; // Offset: 64
			T[N]<hkUint16, 4> particleIndex; // Offset: 80

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVolumeConstraintMx::FrameBatchData"; };
			inline std::string GetTranscriptId() override { return "hclVolumeConstraintMx::FrameBatchData"; };
			inline uint32_t GethkClassHash() override { return 3774165338; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "frameVector", "T[N]<hkVector4, 4>" },
					{ "weight", "T[N]<hkReal, 4>" },
					{ "particleIndex", "T[N]<hkUint16, 4>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class ApplyBatchData : public hkHolderBase {
		public:
			using BaseType = void;
			T[N]<hkVector4, 4> frameVector; // Offset: 0
			T[N]<hkReal, 4> stiffness; // Offset: 64
			T[N]<hkUint16, 4> particleIndex; // Offset: 80

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclVolumeConstraintMx::ApplyBatchData"; };
			inline std::string GetTranscriptId() override { return "hclVolumeConstraintMx::ApplyBatchData"; };
			inline uint32_t GethkClassHash() override { return 3462998564; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "frameVector", "T[N]<hkVector4, 4>" },
					{ "stiffness", "T[N]<hkReal, 4>" },
					{ "particleIndex", "T[N]<hkUint16, 4>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hclVolumeConstraintMx::FrameBatchData, hkContainerHeapAllocator> frameBatchDatas; // Offset: 40
		hkArray<hclVolumeConstraintMx::ApplyBatchData, hkContainerHeapAllocator> applyBatchDatas; // Offset: 56

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclVolumeConstraintMx"; };
		inline std::string GetTranscriptId() override { return "hclVolumeConstraintMx"; };
		inline uint32_t GethkClassHash() override { return 4022169133; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "frameBatchDatas", "hkArray<hclVolumeConstraintMx::FrameBatchData, hkContainerHeapAllocator>" },
				{ "applyBatchDatas", "hkArray<hclVolumeConstraintMx::ApplyBatchData, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
