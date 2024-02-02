#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tT, typename tAllocator>
	class ;
	class hkcdFourAabb;

	class hkcdSimdTree : public hkHolderBase {
	public:
		using BaseType = void;
		class Node : public hkcdFourAabb {
		public:
			using BaseType = hkcdFourAabb;
			T[N]<hkUint32, 4> data; // Offset: 96
			bool isLeaf; // Offset: 112
			bool isActive; // Offset: 113

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hkcdSimdTree::Node"; };
			inline std::string GetTranscriptId() override { return "hkcdSimdTree::Node"; };
			inline uint32_t GethkClassHash() override { return 3838276382; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "data", "T[N]<hkUint32, 4>" },
					{ "isLeaf", "bool" },
					{ "isActive", "bool" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<hkcdSimdTree::Node, hkContainerHeapAllocator> nodes; // Offset: 0
		bool isCompact; // Offset: 16

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkcdSimdTree"; };
		inline std::string GetTranscriptId() override { return "hkcdSimdTree"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "nodes", "hkArray<hkcdSimdTree::Node, hkContainerHeapAllocator>" },
				{ "isCompact", "bool" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
