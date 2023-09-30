#include "Common.h"
#include "MeshIO.h"

#include <iostream>

using namespace DirectX;
using namespace mesh;

int main(int argc, char* argv[]) {
    // Check if the user provided the correct number of command-line arguments
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " input_json.json output_mesh.mesh scale" << std::endl;
        return 1; // Return an error code
    }

    // Extract command-line arguments
    std::string inputJson = argv[1];
    std::string outputMesh = argv[2];
    float scale = std::stof(argv[3]);

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

void test() {
    MeshIO reader;

    reader.Load("mesh_data.json", 0.1f, true, false, true);
    //reader.Deserialize("d8836db87a4ae206af1b.mesh");

    reader.Serialize("d8836db87a4ae206af1b_cvrt.mesh");

    std::cout << "Mesh loaded from " << "mesh_data.json" << " and serialized to " << "d8836db87a4ae206af1b_cvrt.mesh" << std::endl;
    return;
}