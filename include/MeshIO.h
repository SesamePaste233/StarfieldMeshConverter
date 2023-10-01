#pragma once
#include "Common.h"
#include <DirectXMesh.h>
#include "WavefrontWriter.h"
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
		MeshIO() {
			Clear();
		};

		~MeshIO() = default;

		// Read a mesh from a file
		bool Deserialize(const std::string filename);

		bool Serialize(const std::string filename);

		bool Load(const std::string filename, const float scale_factor = 1.f, const bool generate_tangents_if_NA = false, const bool normalize_weight = false, const bool do_optimize = false);
		
		bool SaveOBJ(const std::string filename, const std::string obj_name);

		// Clear existing mesh data
		void Clear();

		void Optimize(std::vector<uint16_t>& a_indices,
			std::vector<DirectX::XMFLOAT3>& a_positions,
			std::vector<DirectX::XMFLOAT3>& a_normals,
			std::vector<DirectX::XMFLOAT2>& a_uvs,
			std::vector<vertex_weight>& a_weights,
			std::vector<vertex_color>& a_vertColors);

		float scale;

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

		uint32_t unk_uint32_t;

		uint32_t num_meshlets;
		std::vector<DirectX::Meshlet> meshlets;

		uint32_t num_culldata;
		std::vector<DirectX::CullData> culldata;

		void UpdateDXAttr();
		void UpdateAttrFromDX();
		std::vector<DirectX::XMFLOAT3> DX_positions;
		std::vector<DirectX::XMFLOAT3> DX_normals;
		std::vector<DirectX::XMFLOAT2> DX_uvs;

		bool GenerateTangents();
		bool GenerateMeshlets();

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