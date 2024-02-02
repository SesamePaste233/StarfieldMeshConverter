#pragma once
#include "hkInclude.h"


namespace hktypes{
	class hkStringPtr;
	class hkReferencedObject;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	template <typename tT, typename tAllocator>
	class ;
	class hclBufferUsage;
	class hclTransformSetUsage;
	class hclStateDependencyGraph;

	class hclClothState : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		class BufferAccess : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint32 bufferIndex; // Offset: 0
			hclBufferUsage bufferUsage; // Offset: 4
			hkUint32 shadowBufferIndex; // Offset: 12

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclClothState::BufferAccess"; };
			inline std::string GetTranscriptId() override { return "hclClothState::BufferAccess"; };
			inline uint32_t GethkClassHash() override { return 746522671; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "bufferIndex", "hkUint32" },
					{ "bufferUsage", "hclBufferUsage" },
					{ "shadowBufferIndex", "hkUint32" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class TransformSetAccess : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint32 transformSetIndex; // Offset: 0
			hclTransformSetUsage transformSetUsage; // Offset: 8

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hclClothState::TransformSetAccess"; };
			inline std::string GetTranscriptId() override { return "hclClothState::TransformSetAccess"; };
			inline uint32_t GethkClassHash() override { return 3568223325; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "transformSetIndex", "hkUint32" },
					{ "transformSetUsage", "hclTransformSetUsage" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkStringPtr name; // Offset: 24
		hkArray<hkUint32, hkContainerHeapAllocator> operators; // Offset: 32
		hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator> usedBuffers; // Offset: 48
		hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator> usedTransformSets; // Offset: 64
		hkArray<hkUint32, hkContainerHeapAllocator> usedSimCloths; // Offset: 80
		T*<hclStateDependencyGraph> dependencyGraph; // Offset: 96

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hclClothState"; };
		inline std::string GetTranscriptId() override { return "hclClothState"; };
		inline uint32_t GethkClassHash() override { return 1309046206; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "name", "hkStringPtr" },
				{ "operators", "hkArray<hkUint32, hkContainerHeapAllocator>" },
				{ "usedBuffers", "hkArray<hclClothState::BufferAccess, hkContainerHeapAllocator>" },
				{ "usedTransformSets", "hkArray<hclClothState::TransformSetAccess, hkContainerHeapAllocator>" },
				{ "usedSimCloths", "hkArray<hkUint32, hkContainerHeapAllocator>" },
				{ "dependencyGraph", "T*<hclStateDependencyGraph>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
