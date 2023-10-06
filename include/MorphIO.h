#pragma once
#include "Common.h"


typedef struct {
	int16_t v[8];
}morph_data;

typedef struct {
	float v[8];
}morph_data_hf;

typedef struct {
	float v[8];
}morph_data_sn;

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
	MorphIO() = default;
	~MorphIO() = default;

	bool Deserialize(const std::string filename);

	uint32_t num_axis;

	uint32_t num_shape_keys;

	uint32_t num_vertices;

	std::vector<std::string> morph_names;

	uint32_t num_morph_data;

	uint32_t num_offsets;

	std::vector<morph_data> morph_data_raw;

	std::vector<morph_data_hf> morph_data_raw_hf;

	std::vector<morph_data_sn> morph_data_raw_sn;

	std::vector<IOffset> offsets_list;

	std::vector<std::vector<morph_data>> per_vert_morph_data;

	std::vector<std::vector<morph_data_hf>> per_vert_morph_data_hf;

	std::vector<std::vector<morph_data_sn>> per_vert_morph_data_sn;

	std::vector<std::vector<uint32_t>> per_vert_morph_key_indices;

};

