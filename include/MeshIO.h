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

		MeshIO() {
			Clear();
		};

		~MeshIO() = default;

		// Read a mesh from a file
		bool Deserialize(const std::string filename);

		bool Serialize(const std::string filename);

		bool Load(const std::string filename, const float scale_factor = 1.f, const uint32_t options = Options::None);

		bool LoadFromString(const std::string json_data, const float scale_factor = 1.f, const uint32_t options = Options::None);

		bool SaveOBJ(const std::string filename, const std::string obj_name);

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
		std::vector<DirectX::CullData> culldata;

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
	};
}