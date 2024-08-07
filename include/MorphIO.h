#pragma once
#include "Common.h"
#include "json.hpp"

#ifdef _DEBUG
#define _EXTENDED_MORPH_DATA
#endif

namespace morph{
	typedef struct {
		uint16_t _offset[3];
		uint16_t target_vert_color;
		uint32_t x, y;
	}morph_data;

	typedef struct {
		float _offset[3]; // Vertex offset/displacement as half-floats.
		float target_vert_color; // Target vertex color.
		float nx, ny, nz; // Delta normal, in DEC3N format.
		float tx, ty, tz; // Delta tangent, in DEC3N format.
	}morph_data_hf; // 16 bytes

	typedef enum {
		None = 0,
		Morph0 = 1 << 0,
		Morph1 = 1 << 1,
		Morph2 = 1 << 2,
		Morph3 = 1 << 3,
		Morph4 = 1 << 4,
		Morph5 = 1 << 5,
		Morph6 = 1 << 6,
		Morph7 = 1 << 7,
		Morph8 = 1 << 8,
		Morph9 = 1 << 9,
		Morph10 = 1 << 10,
		Morph11 = 1 << 11,
		Morph12 = 1 << 12,
		Morph13 = 1 << 13,
		Morph14 = 1 << 14,
		Morph15 = 1 << 15,
		Morph16 = 1 << 16,
		Morph17 = 1 << 17,
		Morph18 = 1 << 18,
		Morph19 = 1 << 19,
		Morph20 = 1 << 20,
		Morph21 = 1 << 21,
		Morph22 = 1 << 22,
		Morph23 = 1 << 23,
		Morph24 = 1 << 24,
		Morph25 = 1 << 25,
		Morph26 = 1 << 26,
		Morph27 = 1 << 27,
		Morph28 = 1 << 28,
		Morph29 = 1 << 29,
		Morph30 = 1 << 30,
		Morph31 = 1 << 31,
	}morph_key_selection;

	typedef struct {
		uint32_t _offset;
		morph_key_selection _marker[4];
	}IOffset;


	class MorphIO
	{
	public:
		enum Options {
			None = 0,
		};

		MorphIO(){
			this->Clear();
		};
		~MorphIO() = default;

		bool Deserialize(const std::string filename);

		bool Serialize(const std::string filename);

		bool Load(const std::string jsonMorphFile, const uint32_t options);

		bool LoadFromString(const std::string json_data, const uint32_t options);

		bool LoadFromNumpy(const std::string json_header_data, const float* delta_positions, const float* target_colors, const float* delta_normals, const float* delta_tangents, const uint32_t options);

		bool Save(const std::string jsonMorphFile);

		bool SerializeToJson(std::string& json_data);

		bool LoadToNumpy(std::string& json_header_data, float* delta_positions, float* target_colors, float* delta_normals, float* delta_tangents);

		bool PostProcess(const uint32_t options);

		void Clear();

		void FakeEmpty(const uint32_t n_verts, const uint8_t n_morphs = 3);

		inline morph_data* GetMorphData(const uint32_t vert_idx, const uint32_t morph_idx_inner) {
			if(morph_idx_inner < per_vert_morph_data[vert_idx].size())
				return &per_vert_morph_data[vert_idx][morph_idx_inner];
			else
				std::cout << "Inner index out of bound: " << morph_idx_inner << std::endl;
			return nullptr;
		}

		inline morph_data* GetMorphData(const uint32_t vert_idx, const std::string morph_name) {
			auto it = std::find(morph_names.begin(), morph_names.end(), morph_name);
			if (it == morph_names.end()) {
				std::cout << "Morph name not found: " << morph_name << std::endl;
				return nullptr;
			}
			else {
				uint32_t morph_idx = std::distance(morph_names.begin(), it);
				uint32_t morph_idx_inner = -1;
				auto it2 = std::find(per_vert_morph_key_indices[vert_idx].begin(), per_vert_morph_key_indices[vert_idx].end(), morph_idx);
				if (it2 == per_vert_morph_key_indices[vert_idx].end()) {
					std::cout << "Morph index not found for current vert: " << morph_idx << std::endl;
					return nullptr;
				}
				else {
					morph_idx_inner = std::distance(per_vert_morph_key_indices[vert_idx].begin(), it2);
					return GetMorphData(vert_idx, morph_idx_inner);
				}
			}
			return nullptr;
		}

		inline morph_data_hf* GetMorphDataHF(const uint32_t vert_idx, const uint32_t morph_idx_inner) {
#ifdef _EXTENDED_MORPH_DATA
			if (morph_idx_inner < per_vert_morph_data_hf[vert_idx].size())
				return &per_vert_morph_data_hf[vert_idx][morph_idx_inner];
			else
				std::cout << "Inner index out of bound: " << morph_idx_inner << std::endl;
#endif
			return nullptr;
		}

		inline morph_data_hf* GetMorphDataHF(const uint32_t vert_idx, const std::string morph_name) {
#ifdef _EXTENDED_MORPH_DATA
			auto it = std::find(morph_names.begin(), morph_names.end(), morph_name);
			if (it == morph_names.end()) {
				std::cout << "Morph name not found: " << morph_name << std::endl;
				return nullptr;
			}
			else {
				uint32_t morph_idx = std::distance(morph_names.begin(), it);
				uint32_t morph_idx_inner = -1;
				auto it2 = std::find(per_vert_morph_key_indices[vert_idx].begin(), per_vert_morph_key_indices[vert_idx].end(), morph_idx);
				if (it2 == per_vert_morph_key_indices[vert_idx].end()) {
					std::cout << "Morph index not found for current vert: " << morph_idx << std::endl;
					return nullptr;
				}
				else {
					morph_idx_inner = std::distance(per_vert_morph_key_indices[vert_idx].begin(), it2);
					return GetMorphDataHF(vert_idx, morph_idx_inner);
				}
			}
#endif
			return nullptr;
		}

		uint32_t num_axis;

		uint32_t num_shape_keys;

		uint32_t num_vertices;

		std::vector<std::string> morph_names;

		uint32_t num_morph_data;

		uint32_t num_offsets;

		std::vector<morph_data> morph_data_raw;

		std::vector<IOffset> offsets_list;

		std::vector<std::vector<morph_data>> per_vert_morph_data;

#ifdef _EXTENDED_MORPH_DATA
		std::vector<morph_data_hf> morph_data_raw_hf;

		std::vector<std::vector<morph_data_hf>> per_vert_morph_data_hf;

#endif

		std::vector<std::vector<uint32_t>> per_vert_morph_key_indices;

		static bool read_header(const std::string filename, std::string& header_str);
	};

}