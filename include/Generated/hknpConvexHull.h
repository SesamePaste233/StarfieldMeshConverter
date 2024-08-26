#pragma once
#include "hkInclude.h"


namespace hktypes{
	template <typename tT>
	class ;
	template <typename tT>
	class ;
	template <typename tT>
	class ;
	template <typename tT>
	class ;
	template <typename tT>
	class ;

	class hknpConvexHull : public hkHolderBase {
	public:
		using BaseType = void;
		class Face : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint16 firstIndex; // Offset: 0
			hkUint8 numIndices; // Offset: 2
			hkUint8 minHalfAngle; // Offset: 3

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpConvexHull::Face"; };
			inline std::string GetTranscriptId() override { return "hknpConvexHull::Face"; };
			inline uint32_t GethkClassHash() override { return 864046963; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "firstIndex", "hkUint16" },
					{ "numIndices", "hkUint8" },
					{ "minHalfAngle", "hkUint8" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		class Edge : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint16 faceIndex; // Offset: 0
			hkUint8 edgeIndex; // Offset: 2
			T[N]<hkUint8, 1> padding; // Offset: 3

			// Extra
			bool FromInstance(const hkreflex::hkClassInstance* instance) override;
			bool ToInstance(hkreflex::hkClassInstance* instance) override;
			inline std::string GethkClassName() override { return "hknpConvexHull::Edge"; };
			inline std::string GetTranscriptId() override { return "hknpConvexHull::Edge"; };
			inline uint32_t GethkClassHash() override { return 646510277; };
			inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
				return {
					{ "faceIndex", "hkUint16" },
					{ "edgeIndex", "hkUint8" },
					{ "padding", "T[N]<hkUint8, 1>" },
				};
			};
			inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
		};

		hkRelArray<hkFloat3> vertices; // Offset: 0
		hkRelArray<hkVector4> planes; // Offset: 8
		hkRelArray<hknpConvexHull::Face> faces; // Offset: 16
		hkRelArray<hkUint8> indices; // Offset: 24
		hkRelArray<hknpConvexHull::Edge> faceLinks; // Offset: 32
		hkRelArray<hknpConvexHull::Edge> vertexEdges; // Offset: 40

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpConvexHull"; };
		inline std::string GetTranscriptId() override { return "hknpConvexHull"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "vertices", "hkRelArray<hkFloat3>" },
				{ "planes", "hkRelArray<hkVector4>" },
				{ "faces", "hkRelArray<hknpConvexHull::Face>" },
				{ "indices", "hkRelArray<hkUint8>" },
				{ "faceLinks", "hkRelArray<hknpConvexHull::Edge>" },
				{ "vertexEdges", "hkRelArray<hknpConvexHull::Edge>" },
			};
		};
		inline std::vector<std::pair<std::string, std::string>> GetTemplateArgs();
	};

}
