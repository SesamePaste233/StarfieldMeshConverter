#include "Common.h"
#include "MeshIO.h"

#include <iostream>

using namespace DirectX;
using namespace mesh;

int blenderToMesh(int argc, char* argv[]) {
	// Check if the user provided the correct number of command-line arguments
	if (argc != 5) {
		std::cerr << "Usage: " << argv[0] << " -mesh input_json.json output_mesh.mesh scale" << std::endl;
		return 1; // Return an error code
	}

	// Extract command-line arguments
	std::string inputJson = argv[2];
	std::string outputMesh = argv[3];
	float scale = std::stof(argv[4]);

	// Create a MeshIO object
	MeshIO reader;

	// Load the mesh from the input JSON file
	if (!reader.Load(inputJson, scale, true, false, true)) {
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

int __main(int argc, char* argv[]) {
	// Check the first command-line argument
	if (argc < 2) {
		std::cerr << "Usage: " << argv[0] << " -blender|-mesh ..." << std::endl;
		return 1; // Return an error code
	}

	// Check if the user wants to convert from Blender to Mesh
	if (strcmp(argv[1], "-mesh") == 0 || strcmp(argv[1], "-m") == 0) {
		std::cout << "Converting from Blender to Mesh" << std::endl;
		return blenderToMesh(argc, argv);
	}

	// Check if the user wants to convert from Mesh to Blender
	if (strcmp(argv[1], "-blender") == 0 || strcmp(argv[1], "-b") == 0) {
		std::cout << "Converting from Mesh to Blender" << std::endl;
		return meshToBlender(argc, argv);
	}

	return 0; // Return success
}

void main() {
	// Create a MeshIO object
	MeshIO reader;

	std::string inputMesh = "C:\\repo\\MeshConverter\\test.mesh";
	std::string outputName = "C:\\Users\\26553\\AppData\\Roaming\\Blender Foundation\\Blender\\3.5\\scripts\\addons\\tool_export_mesh\\Temp\\mesh_data_import";

	// Load the mesh from the input mesh file
	if (!reader.Deserialize(inputMesh)) {
		std::cerr << "Failed to load mesh from " << inputMesh << std::endl;
		return; // Return an error code
	}

	// Save the mesh to the output file
	if (!reader.SaveOBJ(outputName, "test")) {
		std::cerr << "Failed to save mesh to " << outputName << std::endl;
		return; // Return an error code
	}

	std::cout << "complete" << std::endl;
	return;
}

void _main() {
	MeshIO reader;

	reader.Load("C:\\repo\\MeshConverter\\mesh_data.json", 1.f, true, false, true);

	reader.Serialize("C:\\repo\\MeshConverter\\mesh_data.mesh");

	std::cout << "complete" << std::endl;
	return;
}