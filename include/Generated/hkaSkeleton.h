#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkReferencedObject;
	class hkStringPtr;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;

	class hkaSkeleton : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class LocalFrameOnBone : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hkaSkeleton::LocalFrameOnBone"; };
			inline std::string GetTranscriptId() override { return "hkaSkeleton::LocalFrameOnBone"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class Partition : public hkHolderBase {
		public:
			using BaseType = void;

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hkaSkeleton::Partition"; };
			inline std::string GetTranscriptId() override { return "hkaSkeleton::Partition"; };
			inline uint32_t GethkClassHash() override { return 0; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkStringPtr name; // Offset: 24
		hkArray<hkInt16, hkContainerHeapAllocator> parentIndices; // Offset: 32
		hkArray<hkaBone, hkContainerHeapAllocator> bones; // Offset: 48
		hkArray<hkQsTransform, hkContainerHeapAllocator> referencePose; // Offset: 64
		hkArray<hkReal, hkContainerHeapAllocator> referenceFloats; // Offset: 80
		hkArray<hkStringPtr, hkContainerHeapAllocator> floatSlots; // Offset: 96
		hkArray<hkaSkeleton::LocalFrameOnBone, hkContainerHeapAllocator> localFrames; // Offset: 112
		hkArray<hkaSkeleton::Partition, hkContainerHeapAllocator> partitions; // Offset: 128

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hkaSkeleton"; };
		inline std::string GetTranscriptId() override { return "hkaSkeleton"; };
		inline uint32_t GethkClassHash() override { return 2607764882; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "parentIndices", "hkArray<hkInt16, hkContainerHeapAllocator>" },
				{ "bones", "hkArray<hkaBone, hkContainerHeapAllocator>" },
				{ "referencePose", "hkArray<hkQsTransform, hkContainerHeapAllocator>" },
				{ "referenceFloats", "hkArray<hkReal, hkContainerHeapAllocator>" },
				{ "floatSlots", "hkArray<hkStringPtr, hkContainerHeapAllocator>" },
				{ "localFrames", "hkArray<hkaSkeleton::LocalFrameOnBone, hkContainerHeapAllocator>" },
				{ "partitions", "hkArray<hkaSkeleton::Partition, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
