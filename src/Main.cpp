#include "Common.h"
#include "MeshIO.h"
#include "MorphIO.h"

#include <iostream>

using namespace DirectX;
using namespace mesh;
using namespace morph;

int blenderToMesh(int argc, char* argv[]) {
	// Check if the user provided the correct number of command-line arguments
	if (argc != 8) {
		std::cerr << "Usage: " << argv[0] << " -mesh input_json.json output_mesh.mesh scale bool_smooth_edge_normal bool_normalize_weights bool_do_optimization" << std::endl;
		return 1; // Return an error code
	}

	// Extract command-line arguments
	std::string inputJson = argv[2];
	std::string outputMesh = argv[3];
	float scale = std::stof(argv[4]);
	bool smooth_edge_normal = std::stoi(argv[5]);
	bool normalize_weights = std::stoi(argv[6]);
	bool do_optimization = std::stoi(argv[7]);

	// Create a MeshIO object
	MeshIO reader;

	uint32_t opt = MeshIO::Options::GenerateTangentIfNA /*| MeshIO::Options::FlipTangent*/;
	if (normalize_weights) {
		opt |= MeshIO::Options::NormalizeWeight;
	}
	if (smooth_edge_normal) {
		opt |= MeshIO::Options::SmoothEdgeNormal;
	}
	if (do_optimization) {
		opt |= MeshIO::Options::DoOptimize;
	}

	// Print options
	std::cout << "# Options: " << std::endl;
	std::cout << "# Scale: " << std::to_string(scale) << std::endl;
	std::cout << "# Smooth edge normal: " << std::to_string(smooth_edge_normal) << std::endl;
	std::cout << "# Normalize weights: " << std::to_string(normalize_weights) << std::endl;
	std::cout << "# Do optimization: " << std::to_string(do_optimization) << std::endl;

	// Load the mesh from the input JSON file
	if (!reader.Load(inputJson, scale, opt)) {
		std::cerr << "Failed to load mesh from " << inputJson << std::endl;
		return 2; // Return an error code
	}

	// Serialize the mesh to the output file
	if (!reader.Serialize(outputMesh)) {
		std::cerr << "Failed to serialize mesh to " << outputMesh << std::endl;
		return 3; // Return an error code
	}

	std::cout << "Mesh loaded from " << inputJson << " and serialized to " << outputMesh << std::endl;

	return 0; // Return success
}

int meshToBlender(int argc, char* argv[]) {
	// Check if the user provided the correct number of command-line arguments
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " -blender input_mesh.mesh output_name" << std::endl;
		return 1; // Return an error code
	}

	// Extract command-line arguments
	std::string inputMesh = argv[2];
	std::string outputName = argv[3];

	// Get the name of the input mesh file without the extension
	size_t const p(inputMesh.find_last_of('.'));
	size_t const lastSlash = inputMesh.find_last_of("/\\");
	std::string const name(inputMesh.substr(lastSlash + 1, p));

	// Create a MeshIO object
	MeshIO reader;

	// Load the mesh from the input mesh file
	if (!reader.Deserialize(inputMesh)) {
		std::cerr << "Failed to load mesh from " << inputMesh << std::endl;
		return 4; // Return an error code
	}

	// Save the mesh to the output file
	if (!reader.SaveOBJ(outputName, name)) {
		std::cerr << "Failed to save mesh to " << outputName << std::endl;
		return 5; // Return an error code
	}

	std::cout << "Mesh loaded from " << inputMesh << " and saved to " << outputName << std::endl;

	return 0; // Return success
}

int morphToBlender(int argc, char* argv[]){
	// Check if the user provided the correct number of command-line arguments
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " -blender_morph input_morph.dat output_name.json" << std::endl;
		return 1; // Return an error code
	}

	// Extract command-line arguments
	std::string inputMorph = argv[2];
	std::string outputName = argv[3];

	// Create a MorphIO object
	MorphIO reader;

	// Load the morph from the input morph file
	if (!reader.Deserialize(inputMorph)) {
		std::cerr << "Failed to load morph from " << inputMorph << std::endl;
		return 6; // Return an error code
	}

	// Save the morph to the output file
	if (!reader.Save(outputName)) {
		std::cerr << "Failed to save json to " << outputName << std::endl;
		return 7; // Return an error code
	}

	std::cout << "Morph loaded from " << inputMorph << " and saved to " << outputName << std::endl;

	return 0; // Return success
}

int blenderToMorph(int argc, char* argv[]) {
	// Check if the user provided the correct number of command-line arguments
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " -game_morph input_morph.json output_name.dat" << std::endl;
		return 1; // Return an error code
	}

	// Extract command-line arguments
	std::string inputMorph = argv[2];
	std::string outputName = argv[3];

	// Create a MorphIO object
	MorphIO reader;

	// Load the morph from the input morph file
	if (!reader.Load(inputMorph, 0)) {
		std::cerr << "Failed to load json from " << inputMorph << std::endl;
		return 8; // Return an error code
	}

	// Save the morph to the output file
	if (!reader.Serialize(outputName)) {
		std::cerr << "Failed to serialize morph to " << outputName << std::endl;
		return 9; // Return an error code
	}

	std::cout << "Json loaded from " << inputMorph << " and serialized to " << outputName << std::endl;
	return 0;
}

#ifndef _DEBUG
int main(int argc, char* argv[]) {
	// Check the first command-line argument
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " -blender|-mesh ..." << std::endl;
		return 1; // Return an error code
	}

	// Check if the user wants to convert from Blender to Mesh
	if (strcmp(argv[1], "-game") == 0 || strcmp(argv[1], "-g") == 0) {
		std::cout << "Converting from Blender to Mesh" << std::endl;
		return blenderToMesh(argc, argv);
	}

	// Check if the user wants to convert from Mesh to Blender
	if (strcmp(argv[1], "-blender") == 0 || strcmp(argv[1], "-b") == 0) {
		std::cout << "Converting from Mesh to Blender" << std::endl;
		return meshToBlender(argc, argv);
	}

	if (strcmp(argv[1], "-blender_morph") == 0 || strcmp(argv[1], "-bm") == 0) {
		std::cout << "Converting from Morph to Blender" << std::endl;
		return morphToBlender(argc, argv);
	}

	if (strcmp(argv[1], "-game_morph") == 0 || strcmp(argv[1], "-gm") == 0) {
		std::cout << "Converting from Blender to Morph" << std::endl;
		return blenderToMorph(argc, argv);
	}

	return 0; // Return success
}

void __main() {
	// Recursively get all filepaths with .dat extension from the directory
	std::vector<std::string> filepaths;
	Util::getFilePaths("C:\\test\\meshes\\morphs\\clothes", filepaths, ".dat");

	// Test read in MorphIO
	std::vector<std::pair<std::string, MorphIO>> database;
	database.reserve(filepaths.size());

	// Create a log file
	std::ofstream log_file;
	log_file.open("log.txt");

	for (int i = 0; i < filepaths.size(); i++) {
		log_file << filepaths[i] << std::endl;

		MorphIO reader;
		reader.Deserialize(filepaths[i]);

		for (int k = 0; k < reader.num_vertices; k++) {
			int16_t padding = 0;
			for (int j = 0; j < reader.per_vert_morph_key_indices[k].size(); j++) {
				if (reader.per_vert_morph_data[k][j]._padding != padding) {
					padding = reader.per_vert_morph_data[k][j]._padding;
					log_file << "V" + std::to_string(k)+" i" + std::to_string(j) + ": Padding changed to " << std::hex << padding << std::endl;
				}
			}
		}

		database.push_back(std::make_pair(filepaths[i], reader));
	}
}

#endif

#ifdef _DEBUG
void main() {
	// Create a MeshIO object
	MorphIO reader;
	
	reader.Load("C:\\repo\\MeshConverter\\morph_data_export.json",0);

	std::cout << "complete" << std::endl;
	return;
}

void __main() {
	//MeshIO reader;
	//reader.Load("C:\\repo\\MeshConverter\\mesh_data.json", 1.f, MeshIO::Options::NormalizeWeight | MeshIO::Options::GenerateTangentIfNA /*| MeshIO::Options::SmoothEdgeNormal | MeshIO::Options::DoOptimize*/);

	MeshIO reader1;
	reader1.Deserialize("C:\\repo\\MeshConverter\\b9a4813c2649254b121f (1).mesh.mesh");

	MeshIO reader2;
	reader2.Deserialize("C:\\repo\\MeshConverter\\b9a4813c2649254b121f (1).mesh");

	//for (int i = 0; i < reader1.num_positions; i++) {
	//	if (abs(reader1.positions[i] - reader2.positions[i]) > 0.02) {
	//		std::cout << "Position " << i << " is different" << std::endl;
	//	}
	//}

	std::cout << "complete" << std::endl;
	return;
}

void _main() {
	// Recursively get all filepaths with .dat extension from the directory
	//std::vector<std::string> filepaths;
	//Util::getFilePaths("C:\\test\\meshes\\morphs\\clothes", filepaths, ".dat");

	//// Test read in MorphIO
	//std::vector<std::pair<std::string, MorphIO>> database;
	//database.reserve(filepaths.size());

	//// Create a log file
	//std::ofstream log_file;
	//log_file.open("log.txt");

	//for (int i = 0; i < filepaths.size(); i++) {
	//	log_file << filepaths[i] << std::endl;

	//	MorphIO reader;
	//	reader.Deserialize(filepaths[i]);

	//	for (int k = 0; k < reader.num_vertices; k++) {
	//		int16_t padding = 0;
	//		for (int j = 0; j < reader.per_vert_morph_key_indices[k].size(); j++) {
	//			if (reader.per_vert_morph_data[k][j]._padding != padding) {
	//				padding = reader.per_vert_morph_data[k][j]._padding;
	//				log_file << "V" + std::to_string(k)+" i" + std::to_string(j) + ": Padding changed to " << std::hex << padding << std::endl;
	//			}
	//		}
	//	}

	//	database.push_back(std::make_pair(filepaths[i], reader));
	//}

	//MorphIO reader;
	//reader.Deserialize("C:\\repo\\MeshConverter\\morph_3_2077.dat");

	//std::ofstream file;
	//file.open("C:\\repo\\MeshConverter\\morph_data.csv");

	//// Write the per_vert_morph_data_hf to a file
	//file<<"X,Y,Z,Padding,Unk1,Unk2" << std::endl;
	//for (int i = 0; i < reader.num_vertices; i++) {
	//	auto data = reader.per_vert_morph_data_hf[i];
	//	for ( auto& d : data) {
	//		file << std::setprecision(6) << d._offset[0] << "," << d._offset[1] << "," << d._offset[2] << "," << std::to_string(d._padding) << "," << std::to_string(d.x) << "," << std::to_string(d.y) << std::endl;
	//	}
	//}
	//file.close();

	//reader.Serialize("C:\\repo\\MeshConverter\\morph_changed.dat");
	MorphIO reader;
	/*reader.Load("C:\\repo\\MeshConverter\\morph_data_export.json", 0);

	reader.Serialize("C:\\repo\\MeshConverter\\mesh_data.dat");*/

	reader.Deserialize("C:\\repo\\MeshConverter\\morph_3_2077_f.dat");

	reader.Save("C:\\repo\\MeshConverter\\morph_3_2077_f.json");

	std::cout << "complete" << std::endl;

	return;
}
#endif