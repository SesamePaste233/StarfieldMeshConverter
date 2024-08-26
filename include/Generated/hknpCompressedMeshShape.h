#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tT, typename tAllocator>
	class ;
	class hkBitField;
	class hknpCompositeShape;
	template <typename tTYPE>
	class ;

	class hknpCompressedMeshShape : public hknpCompositeShape {
	public:
		using BaseType = hknpCompositeShape;
		hkRefPtr<hkReferencedObject> data; // Offset: 64
		hkBitField triangleIsInterior; // Offset: 72
		int numTriangles; // Offset: 96
		int numConvexShapes; // Offset: 100
		hkArray<hknpShapeInstance, hkContainerHeapAllocator> externShapes; // Offset: 104

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpCompressedMeshShape"; };
		inline std::string GetTranscriptId() override { return "hknpCompressedMeshShape"; };
		inline uint32_t GethkClassHash() override { return 3605242181; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "data", "hkRefPtr<hkReferencedObject>" },
				{ "triangleIsInterior", "hkBitField" },
				{ "numTriangles", "int" },
				{ "numConvexShapes", "int" },
				{ "externShapes", "hkArray<hknpShapeInstance, hkContainerHeapAllocator>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
