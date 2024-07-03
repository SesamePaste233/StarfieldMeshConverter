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

int main() {
	std::string assets_folder = "C:\\test";
	std::string base_nif_path = "C:\\repo\\MeshConverter\\outfit_first_mech_pilot_01_helmet_m.nif";
	std::string json_file = "C:\\repo\\MeshConverter\\outfit_first_mech_pilot_01_helmet_m.nif.json";
	std::string output_file = "C:\\repo\\MeshConverter\\merge_debug.nif";
	bool edit_mat_path = false;

	nif::NifIO base_nif;
	base_nif.SetAssetsPath(assets_folder);
		
	base_nif.Deserialize(base_nif_path);

	nif::NifIO nif;
	nif.SetAssetsPath(assets_folder);

	nif::ni_template::NiSkinInstanceTemplate* temp = new nif::ni_template::NiSkinInstanceTemplate();

	std::ifstream file(json_file);
	std::string json_data((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	nlohmann::json jsonData = nlohmann::json::parse(json_data);

	auto rtti = temp->Deserialize(jsonData);

	if (rtti == nif::ni_template::RTTI::None) {
		std::cerr << "Failed to deserialize json to template." << std::endl;
		return 10; // Return an error code
	}
	else {
		std::cout << "Template deserialized to template RTTI: " << (uint32_t)rtti << std::endl;
	}

	if (!nif.FromTemplate(nif::ni_template::slice_cast(temp, rtti))) {
		std::cerr << "Failed to convert template to nif." << std::endl;
		return 11; // Return an error code
	}

	if (!base_nif.MergeAllBSGeometryAdditive(nif, edit_mat_path)) {
		std::cerr << "Failed to edit nif geometries." << std::endl;
		return 16; // Return an error code
	}

	if (!base_nif.Serialize(output_file)) {
		std::cerr << "Failed to save nif to file." << std::endl;
		return 12; // Return an error code
	}

	std::cout << "Nif serialized to " << output_file << std::endl;

	return 0;
}

int main1(int argc, char* argv[]){
	// Check if the user provided the correct number of command-line arguments
	if (argc != 4) {
		std::cerr << "Usage: " << argv[0] << " -blender_morph input_morph.dat output_name.json" << std::endl;
		return 1; // Return an error code
	}

	// Extract command-line arguments
	std::string inputMorph = "morph.dat.json";
	std::string outputName = "morph.dat";

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

int __main(int argc, char* argv[]) {
	
	// Extract command-line arguments
	std::string inputMorph = "C:\\repo\\MeshConverter\\morph.dat.json";
	std::string outputName = "morph.dat";

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

void importnif_main() {
	nif::NifIO nif;
	std::string input_file("C:\\repo\\MeshConverter\\new_nif_test.nif");

	if (!nif.Deserialize(input_file)) {
		std::cerr << "Failed to load nif from " << input_file << std::endl;
		return;
	}

	auto t_ptr = nif.ToTemplate<nif::ni_template::NiSkinInstanceTemplate>();

	if (t_ptr == nullptr) {
		std::cerr << "Failed to convert nif to template" << std::endl;
		return;
	}
	else {
		std::cout << "Nif converted to template RTTI: " << (uint32_t)t_ptr->GetRTTI() << std::endl;
	}

	/*if (t_ptr->GetRTTI() == nif::ni_template::RTTI::NiArmature) {
		dynamic_cast<nif::ni_template::NiArmatureTemplate*>(t_ptr)->skeleton_mode = true;
	}*/

	auto jsondata = t_ptr->Serialize();

	jsondata["TEMPLATE_RTTI"] = (uint32_t)t_ptr->GetRTTI();

	std::cout << "Nif serialized to json" << std::endl;


	return;
}

void importmorph_main() {
	MorphIO reader;
	reader.Deserialize("C:\\repo\\MeshConverter\\morph.dat");

	std::vector<morph_data_hf*> morphs;
	std::string key = "HideEar";
	morphs.push_back(reader.GetMorphDataHF(4142, key));
	morphs.push_back(reader.GetMorphDataHF(4143, key));
	morphs.push_back(reader.GetMorphDataHF(4144, key));
	morphs.push_back(reader.GetMorphDataHF(4145, key));

	for (auto& morph : morphs) {
		if (morph != nullptr) {
			std::cout << "Morph: " << morph->nx << morph->ny << morph->nz << std::endl;
		}
		else{
			std::cout << "Morph not found" << std::endl;
		}
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

void ____main() {
	hkphysics::hkReflDataDeserializer data;

	data.Deserialize("C:\\repo\\MeshConverter\\UnkBlocks\\bhkNPCollisionObject\\2.bin", true);
	//data.Deserialize("C:\\repo\\MeshConverter\\UnkBlocks\\bhkPhysicsSystem\\cloth_test.bin", true);

	auto updated_transcript = data.RegisterClassesToTranscriptor();

	if (updated_transcript) {
		data.SaveToCxxCode();

		auto literals = data.classes_to_literal(true, true, true);

		// Save the string into a file
		std::ofstream file_l("C:\\repo\\MeshConverter\\hkGenerated.h");
		file_l << literals;
		file_l.close();

	}

	auto instances = data.root_level_instance->dump();


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

int phexportmain() {
	std::string json_file = "C:\\repo\\MeshConverter\\physics_data_debug.json";
	std::string output_file = "C:\\repo\\MeshConverter\\physics_data_debug.bin";

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

	hkphysics::hkReflDataDeserializer deserializer;

	std::ifstream file2(output_file, std::ios::binary);
	if (!file2.is_open()) {
		std::cout << "Failed to open output file." << std::endl;
		return 16; // Return an error code
	}

	size_t data_size = utils::read<uint32_t>(file2, 1, true)[0];
	file2.seekg(0, std::ios::beg);
	deserializer.Deserialize(file2, data_size);
	file2.close();

	deserializer.root_level_instance->assert_equals(serializer.root_level_instance);

	auto instance_str = deserializer.root_level_instance->dump();

	std::ofstream file3("C:\\repo\\MeshConverter\\physics_data.txt");
	file3 << instance_str;
	file3.close();

	return 0;
}

void phnifmain() {
	nif::NifIO nif;
	nif.Deserialize("C:\\repo\\MeshConverter\\outfit_collector_f_upperbody.nif");
	
	int i = 0;
	utils::ProfilerGlobalOwner::GetInstance().for_each([&i](utils::DataAccessProfiler* profiler) {
		std::ofstream file("C:\\repo\\MeshConverter\\profiler\\" + profiler->GetRTTIName() + "_" + std::to_string(i++) + ".bin");
		profiler->dump(file);
	});

	auto data = &dynamic_cast<nif::BSClothExtraData*>(nif.GetRTTIBlocks(nif::NiRTTI::BSClothExtraData)[0])->GetDataDeserializer();

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
	std::ofstream file_i("C:\\repo\\MeshConverter\\outfit_collector_f_upperbody.txt");
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

int nifmain() {
	nif::NifIO nif;
	nif.SetAssetsPath("C:\\test");
	nif::ni_template::NiSkinInstanceTemplate* temp = new nif::ni_template::NiSkinInstanceTemplate();

	std::ifstream file("C:\\repo\\MeshConverter\\test.nif.json");
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