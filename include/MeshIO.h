#pragma once
#include "Common.h"
#include <DirectXMesh.h>
#include "WavefrontWriter.h"
#include <WaveFrontReader.h>
#include "json.hpp"

namespace mesh {
	typedef struct {
		uint16_t bone, weight;
	}bone_binding;

	typedef bone_binding* vertex_weight;

	typedef struct {
		uint8_t r, g, b, a;
	}vertex_color;

	class MeshIO
	{
	public:
		enum Options {
			None = 0,
			GenerateTangentIfNA = 1 << 0,
			NormalizeWeight = 1 << 1,
			DoOptimize = 1 << 2,
			SmoothEdgeNormal = 1 << 3,
			FlipTangent = 1 << 4,
		};
		struct BoneBoundingSphere {
			float center[3] = { 0,0,0 };
			float radius = 0.1;
		};

		struct BSCullData {
			float center[3] = { 0,0,0 };
			float expand[3] = { 0,0,0 };
		};

		MeshIO() {
			Clear();
		};

		~MeshIO() = default;

		// Read a mesh from a file
		bool Deserialize(const std::string filename);

		bool Deserialize(std::istream& stream);

		bool Serialize(const std::string filename);

		bool Serialize(std::ostream& stream);

		bool LoadFromString(const std::string json_data, const float scale_factor = 1.f, const uint32_t options = Options::None);

		bool LoadFromNumpy(const std::string json_header,
			const float* ptr_positions,
			const int64_t* ptr_indices,
			const float* ptr_normals,
			const float* ptr_uv1,
			const float* ptr_uv2,
			const float* ptr_color,
			const float* ptr_tangents,
			const int32_t* ptr_bitangent_signs,
			const uint32_t options = Options::None
		);

		bool LoadFromNumpyJson(const nlohmann::json& jsonData,
			const float* ptr_positions,
			const int64_t* ptr_indices,
			const float* ptr_normals,
			const float* ptr_uv1,
			const float* ptr_uv2,
			const float* ptr_color,
			const float* ptr_tangents,
			const int32_t* ptr_bitangent_signs,
			const uint32_t options = Options::None
		);

		bool LoadFromJson(const nlohmann::json& jsonData, const float scale_factor = 1.f, const uint32_t options = Options::None);

		bool LoadToNumpy(
			float* ptr_positions,
			int64_t* ptr_indices,
			float* ptr_normals,
			float* ptr_uv1,
			float* ptr_uv2,
			float* ptr_color,
			float* ptr_tangents,
			int32_t* ptr_bitangent_signs
		);

		bool SerializeToJsonStr(std::string& json_data) const;

		bool SerializeToJson(nlohmann::json& jsonData) const;

		bool PostProcess(const uint32_t options = Options::None);

		bool GeometryFromJson(const nlohmann::json& jsonData, float scale_factor);

		bool GeometryFromOBJ(const std::string filename, float scale_factor);

		// Clear existing mesh data
		void Clear();

		void Optimize(std::vector<uint16_t>& a_indices,
			std::vector<DirectX::XMFLOAT3>& a_positions,
			std::vector<DirectX::XMFLOAT3>& a_normals,
			std::vector<DirectX::XMFLOAT2>& a_uvs,
			std::vector<vertex_weight>& a_weights,
			std::vector<vertex_color>& a_vertColors);

		float max_border;

		void CalculateBoneBounding();

		uint32_t num_weightsPerVertex;

		uint32_t indices_size;
		std::vector<uint16_t> indices;

		uint32_t num_triangles;

		uint32_t num_vertices;

		uint32_t num_positions;
		std::vector<double> positions;

		uint32_t num_uv1;
		std::vector<std::vector<float>> UV_list1;

		// Always empty for some reason
		uint32_t num_uv2;
		std::vector<std::vector<float>> UV_list2;

		uint32_t num_weights;
		std::vector<vertex_weight> weights;
		std::vector<std::vector<uint32_t>> weight_indices;
		std::vector<BoneBoundingSphere> bone_bounding;

		uint32_t num_vert_colors;
		std::vector<vertex_color> vert_colors;

		uint32_t num_normals;
		std::vector<std::vector<float>> normals;

		uint32_t num_tangents;
		std::vector<std::vector<float>> tangents;
		std::vector<int> tangent_signs;

		uint32_t num_lods;
		std::vector<std::vector<uint16_t>> lods;

		uint32_t num_meshlets;
		std::vector<DirectX::Meshlet> meshlets;

		uint32_t num_culldata;
		std::vector<BSCullData> culldata;

		uint32_t num_smooth_group;
		std::vector<uint16_t> smooth_group;

		void UpdateDXAttr();
		void UpdateAttrFromDX();
		std::vector<DirectX::XMFLOAT3> DX_positions;
		std::vector<DirectX::XMFLOAT3> DX_normals;
		std::vector<DirectX::XMFLOAT2> DX_uvs;

		bool GenerateTangents(const uint32_t& options);
		bool GenerateMeshlets();
		size_t NaiveEdgeSmooth();

		// Export controlles
		bool export_geometry = true;
		bool export_uvs = true;
		bool export_normals = true;
		bool export_tangents = true;
		bool export_weights = true;
		bool export_vert_colors = true;
		bool export_meshlets = true;
		bool export_culldata = true;

		static const uint32_t                   kIndexByteCount = 2;

		static bool read_header(const std::string filename, std::string& header_str);
	};
}