#pragma once
#include "MeshIO.h"
#include "MorphIO.h"
#include "NifIO.h"
#include "Common.h"

//#define _DLLEXPORT

#ifdef _DLLEXPORT
#define DLL __declspec(dllexport)
#else
#define DLL
#endif
extern "C" {
	uint32_t DLL ExportMesh(const char* json_data,
		const char* output_file,
		float max_border,
		bool smooth_edge_normal,
		bool normalize_weights,
		bool do_optimization);

	uint32_t DLL ExportMorph(const char* json_data,
		const char* output_file);

	const char * DLL ImportMesh(const char* input_file, const char* output_name);

	const char* DLL ImportMorph(const char* input_file);

	uint32_t DLL CreateNif(const char* json_data, const char* output_file);

	const char* DLL ImportNif(const char* input_file);
}