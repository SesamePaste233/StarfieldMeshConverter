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

	DLL uint32_t ExportMorph(const char* json_data,
		const char* output_file);

	DLL uint32_t ExportEmptyMorph(uint32_t n_verts, const char* output_file);

	DLL const char * ImportMesh(const char* input_file);

	DLL const char* ImportMorph(const char* input_file);

	DLL uint32_t CreateNif(const char* json_data, const char* output_file, const char* assets_folder);

	DLL const char* ImportNif(const char* input_file, bool export_havok_readable, const char* readable_filepath);

	DLL uint32_t ComposePhysicsData(const char* json_data, uint32_t platform, const char* transcript_path, const char* output_file, bool export_readable);
}