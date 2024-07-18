#pragma once
#include "MeshIO.h"
#include "MorphIO.h"
#include "NifIO.h"
#include "hkPhysics.h"
#include "Common.h"

//#define _DLLEXPORT

#ifdef _DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL
#endif
extern "C" {
	DLL uint32_t ExportMesh(const char* json_data,
		const char* output_file,
		float max_border,
		bool smooth_edge_normal,
		bool normalize_weights,
		bool do_optimization);

	DLL uint32_t ExportMeshNumpy(const char* json_data,
		const char* output_file,
		const float* ptr_positions,
		const int64_t* ptr_indices,
		const float* ptr_normals,
		const float* ptr_uv1,
		const float* ptr_uv2,
		const float* ptr_color,
		const float* ptr_tangents,
		const int32_t* ptr_bitangent_signs
	);

	DLL uint32_t ExportMorph(const char* json_data,
		const char* output_file);

	DLL uint32_t ExportMorphNumpy(const char* json_data,
		const char* output_file,
		const float* delta_positions,
		const float* target_colors,
		const float* delta_normals,
		const float* delta_tangents
	);

	DLL uint32_t ExportEmptyMorph(uint32_t n_verts, const char* output_file);

	DLL const char * ImportMesh(const char* input_file);

	DLL const char* ImportMorph(const char* input_file);

	DLL const char* ImportMorphHeader(const char* input_file);

	DLL uint32_t ImportMorphNumpy(const char* input_file, 
		float* delta_positions, 
		float* target_colors, 
		float* delta_normals, 
		float* delta_tangents
	);

	DLL uint32_t CreateNif(const char* json_data, const char* output_file, const char* assets_folder);

	DLL uint32_t EditNifBSGeometries(const char* base_nif, const char* json_data, const char* output_file, const char* assets_folder, bool edit_mat_path);

	DLL const char* ImportNif(const char* input_file, bool export_havok_readable, const char* readable_filepath);

	DLL uint32_t ComposePhysicsData(const char* json_data, uint32_t platform, const char* transcript_path, const char* output_file, bool export_readable);
}