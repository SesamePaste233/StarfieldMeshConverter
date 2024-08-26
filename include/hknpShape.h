#pragma once
#include "hkInclude.h"
#include "hkTypes.h"

namespace hktypes {

	enum class hknpShapeType : uint8_t {
		// Unknown
	};

	enum class hknpCollisionDispatchType : uint8_t {
		// Unknown
	};

	class hknpShape : public hkReferencedObject {
	public:
		using BaseType = hkReferencedObject;
		enum class FlagsEnum : uint16_t{
			// Unknown
		};

		hknpShape::FlagsEnum flags; // Offset: 24
		hknpShapeType type; // Offset: 26
		uint8_t numShapeKeyBits; // Offset: 27
		hknpCollisionDispatchType dispatchType; // Offset: 28
		float convexRadius; // Offset: 32
		uint64_t userData; // Offset: 40
		hkRefCountedProperties* properties; // Offset: 48

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpShape"; };
		inline std::string GetTranscriptId() override { return "hknpShape"; };
		inline uint32_t GethkClassHash() override { return 0; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "flags", "hkFlags<hknpShape::FlagsEnum, hkUint16>" },
				{ "type", "hkEnum<hknpShapeType::Enum, hkUint8>" },
				{ "numShapeKeyBits", "hkUint8" },
				{ "dispatchType", "hkEnum<hknpCollisionDispatchType::Enum, hkUint8>" },
				{ "convexRadius", "hkReal" },
				{ "userData", "hkUint64" },
				{ "properties", "hkRefPtr<hkRefCountedProperties>" },
			};
		};
	};

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
		};

		class Edge : public hkHolderBase {
		public:
			using BaseType = void;
			hkUint16 faceIndex; // Offset: 0
			hkUint8 edgeIndex; // Offset: 2
			std::array<hkUint8, 1> padding; // Offset: 3

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
		};

		std::vector<hkFloat3> vertices; // Offset: 0
		std::vector<hkVector4> planes; // Offset: 8
		std::vector<hknpConvexHull::Face> faces; // Offset: 16
		std::vector<hkUint8> indices; // Offset: 24
		std::vector<hknpConvexHull::Edge> faceLinks; // Offset: 32
		std::vector<hknpConvexHull::Edge> vertexEdges; // Offset: 40

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
	};

	class hknpConvexShape : public hknpShape {
	public:
		using BaseType = hknpShape;
		hkHalf16 maxAllowedPenetration; // Offset: 56
		hknpConvexHull hull; // Offset: 60

		// Extra
		bool FromInstance(const hkreflex::hkClassInstance* instance) override;
		bool ToInstance(hkreflex::hkClassInstance* instance) override;
		inline std::string GethkClassName() override { return "hknpConvexShape"; };
		inline std::string GetTranscriptId() override { return "hknpConvexShape"; };
		inline uint32_t GethkClassHash() override { return 3798386044; };
		inline std::vector<std::pair<std::string, std::string>> GethkClassMembers() override {
			return {
				{ "maxAllowedPenetration", "hkHalf16" },
				{ "hull", "hknpConvexHull" },
			};
		};
	};

}