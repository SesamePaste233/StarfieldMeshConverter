#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkcdStaticMeshTree::Base;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hkcdDefaultStaticMeshTree : public hkcdStaticMeshTree::Base {
	public:
		using BaseType = hkcdStaticMeshTree::Base;
		class PrimitiveDataRun : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint16 value; // Offset: 0
			hkUint8 index; // Offset: 2
			hkUint8 count; // Offset: 3

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hkcdDefaultStaticMeshTree::PrimitiveDataRun"; };
			inline std::string GetTranscriptId() override { return "hkcdDefaultStaticMeshTree::PrimitiveDataRun"; };
			inline uint32_t GethkClassHash() override { return 3223277798; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "value", "hkUint16" },
					{ "index", "hkUint8" },
					{ "count", "hkUint8" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkArray<unsigned int, hkContainerHeapAllocator> packedVertices; // Offset: 112
		hkArray<unsigned long long, hkContainerHeapAllocator> sharedVertices; // Offset: 128
		hkArray<hkcdDefaultStaticMeshTree::PrimitiveDataRun, hkContainerHeapAllocator> primitiveDataRuns; // Offset: 144

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkcdDefaultStaticMeshTree"; };
		inline std::string GetTranscriptId() override { return "hkcdDefaultStaticMeshTree"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "packedVertices", "hkArray<unsigned int, hkContainerHeapAllocator>" },
				{ "sharedVertices", "hkArray<unsigned long long, hkContainerHeapAllocator>" },
				{ "primitiveDataRuns", "hkArray<hkcdDefaultStaticMeshTree::PrimitiveDataRun, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
