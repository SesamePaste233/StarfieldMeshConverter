#include "MeshConverter.h"

uint32_t ExportMesh(const char* json_data, const char* output_file, float scale, bool smooth_edge_normal, bool normalize_weights, bool do_optimization)
{
	mesh::MeshIO reader;

	uint32_t opt = mesh::MeshIO::Options::GenerateTangentIfNA /*| MeshIO::Options::FlipTangent*/;
	if (normalize_weights) {
		opt |= mesh::MeshIO::Options::NormalizeWeight;
	}
	if (smooth_edge_normal) {
		opt |= mesh::MeshIO::Options::SmoothEdgeNormal;
	}
	if (do_optimization) {
		opt |= mesh::MeshIO::Options::DoOptimize;
	}

	if (!reader.LoadFromString(json_data, scale, opt)) {
		std::cerr << "Failed to load mesh from blender." << std::endl;
		return 2; // Return an error code
	}

	if (!reader.Serialize(output_file)) {
		std::cerr << "Failed to save mesh to file." << std::endl;
		return 3; // Return an error code
	}
	std::cout << "Mesh loaded from blender and serialized to " << output_file << std::endl;

	return 0;
}

uint32_t ExportMorph(const char* json_data, const char* output_file)
{
	// Equivalent to blenderToMorph
	morph::MorphIO morphReader;

	if (!morphReader.LoadFromString(json_data, morph::MorphIO::Options::None)) {
		std::cerr << "Failed to load morph from blender." << std::endl;
		return 8; // Return an error code
	}
	
	if (!morphReader.Serialize(output_file)) {
		std::cerr << "Failed to save morph to file." << std::endl;
		return 9; // Return an error code
	}

	std::cout << "Morph loaded from blender and serialized to " << output_file << std::endl;

	return 0;
}

uint32_t ImportMesh(const char* input_file, char* json_data)
{
	return 0;
}

uint32_t ImportMorph(const char* input_file, char* json_data)
{
	return 0;
}

uint32_t CreateNif(const char* json_data, const char* output_file)
{
	nif::NifIO nif;

	nif::ni_template::NiSkinInstanceTemplate skin;

	nif.FromTemplate(&skin);

	if (!nif.Serialize(output_file)) {
		std::cerr << "Failed to save nif to file." << std::endl;
		return 10; // Return an error code
	}

	std::cout << "Nif serialized to " << output_file << std::endl;

	return 0;
}
