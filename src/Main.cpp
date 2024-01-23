#include "Common.h"
#include "MeshIO.h"
#include "MorphIO.h"
#include "NifIO.h"
#include "hkPhysics.h"

#include "MeshConverter.h"

#include <iostream>
#include <functional>

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

//int main(int argc, char* argv[]) {
//	// Check the first command-line argument
//	if (argc < 2) {
//		std::cerr << "Usage: " << argv[0] << " -blender|-mesh ..." << std::endl;
//		return 1; // Return an error code
//	}
//
//	// Check if the user wants to convert from Blender to Mesh
//	if (strcmp(argv[1], "-game") == 0 || strcmp(argv[1], "-g") == 0) {
//		std::cout << "Converting from Blender to Mesh" << std::endl;
//		return blenderToMesh(argc, argv);
//	}
//
//	// Check if the user wants to convert from Mesh to Blender
//	if (strcmp(argv[1], "-blender") == 0 || strcmp(argv[1], "-b") == 0) {
//		std::cout << "Converting from Mesh to Blender" << std::endl;
//		return meshToBlender(argc, argv);
//	}
//
//	if (strcmp(argv[1], "-blender_morph") == 0 || strcmp(argv[1], "-bm") == 0) {
//		std::cout << "Converting from Morph to Blender" << std::endl;
//		return morphToBlender(argc, argv);
//	}
//
//	if (strcmp(argv[1], "-game_morph") == 0 || strcmp(argv[1], "-gm") == 0) {
//		std::cout << "Converting from Blender to Morph" << std::endl;
//		return blenderToMorph(argc, argv);
//	}
//
//	return 0; // Return success
//}

void __main() {
	// Recursively get all filepaths with .dat extension from the directory
	std::vector<std::string> filepaths;
	utils::getFilePaths("C:\\test\\meshes\\morphs\\clothes", filepaths, ".dat");

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
				if (reader.per_vert_morph_data[k][j].target_vert_color != padding) {
					padding = reader.per_vert_morph_data[k][j].target_vert_color;
					log_file << "V" + std::to_string(k)+" i" + std::to_string(j) + ": Padding changed to " << std::hex << padding << std::endl;
				}
			}
		}

		database.push_back(std::make_pair(filepaths[i], reader));
	}
}

void amain() {
	// Create a MeshIO object
	nif::NifIO reader;

	reader.Deserialize("C:\\repo\\MeshConverter\\ar99_barrel_long.nif");

	auto armature = dynamic_cast<nif::ni_template::NiArmatureTemplate*>(reader.ToTemplate<nif::ni_template::NiArmatureTemplate>());

	armature->skeleton_mode = true;
	auto json_data = armature->Serialize();

	nif::ni_template::NiArmatureTemplate* armature2 = new nif::ni_template::NiArmatureTemplate();

	armature2->Deserialize(json_data);

	nif::NifIO writer;
	writer.FromTemplate(armature2);

	writer.Serialize("C:\\repo\\MeshConverter\\ar99_barrel_long.nif");

	return;
}

void test_main() {
	hkphysics::hkReflDataDeserializer data;

	data.Deserialize("C:\\repo\\MeshConverter\\UnkBlocks\\bhkPhysicsSystem\\cloth_test.bin");

	auto literals = data.classes_to_literal(true, true, true);

	auto instances = data.dump_indexed_blocks();

	/*std::ofstream file0("C:\\repo\\MeshConverter\\UnkBlocks\\bhkPhysicsSystem\\cloth_test.bin", std::ios::binary);
	data.SerializeWithTypeUnchanged(file0);
	file0.close();*/

	int i = 0;
	utils::ProfilerGlobalOwner::GetInstance().for_each([&i](utils::DataAccessProfiler* profiler) {
		std::ofstream file("C:\\repo\\MeshConverter\\profiler\\" + profiler->GetRTTIName() + "_" + std::to_string(i++) + ".bin", std::ios::binary);
		profiler->dump(file);
		});

	// Save the string into a file
	std::ofstream file("C:\\repo\\MeshConverter\\include\\Generated\\hkGenerated.h");
	file << literals;
	file.close();

	std::ofstream file1("C:\\repo\\MeshConverter\\include\\Generated\\Instances.txt");
	file1 << instances;
	file1.close();
	return;
}
void pmain() {
	hkphysics::hkReflDataDeserializer data;

	data.Deserialize("C:\\repo\\MeshConverter\\UnkBlocks\\bhkPhysicsSystem\\cloth_test.bin");

	/*auto literals = data.classes_to_literal(true, true, true);

	auto instances = data.dump_root_instance();*/
	hkphysics::hkReflDataDeserializer data1;

	data1.Deserialize("C:\\repo\\MeshConverter\\UnkBlocks\\bhkPhysicsSystem\\cloth_test.bin");
	
	data.root_level_instance->assert_equals(data1.root_level_instance);

	int i = 0;
	utils::ProfilerGlobalOwner::GetInstance().for_each([&i](utils::DataAccessProfiler* profiler) {
		std::ofstream file("C:\\repo\\MeshConverter\\profiler\\" + profiler->GetRTTIName() + "_" + std::to_string(i++) + ".bin", std::ios::binary);
		profiler->dump(file);
		});

	// Save the string into a file
	/*std::ofstream file("C:\\repo\\MeshConverter\\include\\Generated\\hkGenerated_cloth.h");
	file << literals;
	file.close();

	std::ofstream file1("C:\\repo\\MeshConverter\\include\\Generated\\Instances_cloth.txt");
	file1 << instances;
	file1.close();*/
	return;
}

int main() {
	std::string json_file = "C:\\repo\\MeshConverter\\physics_data.json";
	std::string output_file = "C:\\repo\\MeshConverter\\physics_data.bin";

	std::ifstream file(json_file);
	std::string json_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	nlohmann::json jsonData = nlohmann::json::parse(json_data);
	hkphysics::hkPhysicsDataBuilder builder;


	if (!builder.ParseJson(jsonData) || !builder.build_target_finished) {
		std::cout << "Physics data build failed." << std::endl;
		return 14; // Return an error code
	}

	hkphysics::hkReflDataSerializer serializer;
	serializer.root_level_container = &builder.GetTarget();

	std::ofstream file1(output_file, std::ios::binary);
	if (!file1.is_open()) {
		std::cout << "Failed to open output file." << std::endl;
		return 15; // Return an error code
	}

	serializer.Serialize(file1);
	file1.close();

	return 0;
}

void asdadsmain() {
	nif::NifIO nif;
	nif.Deserialize("C:\\repo\\MeshConverter\\outfit_dress_sari_lowerbody_f.nif");

	int i = 0;
	utils::ProfilerGlobalOwner::GetInstance().for_each([&i](utils::DataAccessProfiler* profiler) {
		std::ofstream file("C:\\repo\\MeshConverter\\profiler\\" + profiler->GetRTTIName() + "_" + std::to_string(i++) + ".bin");
		profiler->dump(file);
	});

	auto data = dynamic_cast<nif::BSClothExtraData*>(nif.GetRTTIBlocks(nif::NiRTTI::BSClothExtraData)[0])->GetDataDeserializer();

	auto updated_transcript = data->RegisterClassesToTranscriptor();

	if (updated_transcript) {
		data->SaveToCxxCode();

		auto literals = data->classes_to_literal(true, true, true);

		// Save the string into a file
		std::ofstream file_l("C:\\repo\\MeshConverter\\hkGenerated.h");
		file_l << literals;
		file_l.close();

	}

	auto instances = data->root_level_instance->dump();
	std::ofstream file_i("C:\\repo\\MeshConverter\\outfit_dress_sari_lowerbody_f.txt");
	file_i << instances;
	file_i.close();

	hkphysics::hkReflDataSerializer serializer;
	serializer.root_level_container = data->root_level_container;

	std::ofstream file0("C:\\repo\\MeshConverter\\UnkBlocks\\bhkPhysicsSystem\\cloth_test.bin", std::ios::binary);
	serializer.Serialize(file0);
	file0.close();

	data->root_level_instance->assert_equals(serializer.root_level_instance);

	hkphysics::hkReflDataDeserializer data1;

	std::ifstream file1("C:\\repo\\MeshConverter\\UnkBlocks\\bhkPhysicsSystem\\cloth_test.bin", std::ios::binary);
	size_t data_size = utils::read<uint32_t>(file1, 1, true)[0];
	file1.seekg(0, std::ios::beg);
	data1.Deserialize(file1, data_size);
	file1.close();

	data1.root_level_instance->assert_equals(data->root_level_instance);

	//auto json = nlohmann::json::array();
	//auto havok_cloth_data = dynamic_cast<hktypes::hclClothData*>(data->root_level_container->GetNamedVariantRef("hclClothData"));
	//if (havok_cloth_data != nullptr) {
	//	auto havok_meshes = havok_cloth_data->GetBufferedMeshes();
	//	for (auto& mesh : havok_meshes) {
	//		json.push_back(mesh.ToJson());
	//	}
	//}
}

int asdmain() {
	nif::NifIO nif;
	nif.SetAssetsPath("C:\\test");
	nif::ni_template::NiSkinInstanceTemplate* temp = new nif::ni_template::NiSkinInstanceTemplate();

	std::ifstream file("C:\\repo\\MeshConverter\\skeleton.nif.json");
	std::string json_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	std::cout << json_data << std::endl;

	nlohmann::json jsonData = nlohmann::json::parse(json_data);

	auto rtti = temp->Deserialize(jsonData);

	if (rtti == nif::ni_template::RTTI::None) {
		std::cerr << "Failed to deserialize json to template" << std::endl;
		return 10; // Return an error code
	}
	else {
		std::cout << "Template deserialized to template RTTI: " << (uint32_t)rtti << std::endl;
	}

	if (!nif.FromTemplate(nif::ni_template::slice_cast(temp, rtti))) {
		std::cerr << "Failed to convert template to nif" << std::endl;
		return 11; // Return an error code
	}

	nif.Serialize("C:\\repo\\MeshConverter\\ExportScene.nif");

	return 0;
}

void _main() {
	//MeshIO reader;
	//reader.Load("C:\\repo\\MeshConverter\\mesh_data.json", 1.f, MeshIO::Options::NormalizeWeight | MeshIO::Options::GenerateTangentIfNA /*| MeshIO::Options::SmoothEdgeNormal | MeshIO::Options::DoOptimize*/);

	MeshIO reader1;
	reader1.Deserialize("C:\\repo\\MeshConverter\\450aec21f08531a6a273 vanilla.mesh");

	MeshIO reader2;
	reader2.Deserialize("C:\\repo\\MeshConverter\\450aec21f08531a6a273.mesh");

	//for (int i = 0; i < reader1.num_positions; i++) {
	//	if (abs(reader1.positions[i] - reader2.positions[i]) > 0.02) {
	//		std::cout << "Position " << i << " is different" << std::endl;
	//	}
	//}

	std::cout << "complete" << std::endl;
	return;
}