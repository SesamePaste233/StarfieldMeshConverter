#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkBitField;
	template <typename tT, typename tAllocator>
	class ;

	class hclTransformSetUsage : public hkHolderBase {
	public:
		using BaseType = void;
		class TransformTracker : public hkHolderBase {
		public:
			using BaseType = void;
			hkBitField read; // Offset: 0
			hkBitField readBeforeWrite; // Offset: 24
			hkBitField written; // Offset: 48

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclTransformSetUsage::TransformTracker"; };
			inline std::string GetTranscriptId() override { return "hclTransformSetUsage::TransformTracker"; };
			inline uint32_t GethkClassHash() override { return 51977619; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "read", "hkBitField" },
					{ "readBeforeWrite", "hkBitField" },
					{ "written", "hkBitField" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		T[N]<hkUint8, 2> perComponentFlags; // Offset: 0
		hkArray<hclTransformSetUsage::TransformTracker, hkContainerHeapAllocator> perComponentTransformTrackers; // Offset: 8

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclTransformSetUsage"; };
		inline std::string GetTranscriptId() override { return "hclTransformSetUsage"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "perComponentFlags", "T[N]<hkUint8, 2>" },
				{ "perComponentTransformTrackers", "hkArray<hclTransformSetUsage::TransformTracker, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
