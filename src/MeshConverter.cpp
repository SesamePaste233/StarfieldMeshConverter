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

uint32_t ExportMeshNumpy(const char* json_data, 
	const char* output_file,
	const float* ptr_positions,
	const int64_t* ptr_indices,
	const float* ptr_normals,
	const float* ptr_uv1,
	const float* ptr_uv2,
	const float* ptr_color,
	const float* ptr_tangents,
	const int32_t* ptr_bitangent_signs
){
	mesh::MeshIO reader;

	uint32_t opt = mesh::MeshIO::Options::GenerateTangentIfNA;
	opt |= mesh::MeshIO::Options::NormalizeWeight;

	if (!reader.LoadFromNumpy(json_data, 
		ptr_positions,
		ptr_indices,
		ptr_normals,
		ptr_uv1,
		ptr_uv2,
		ptr_color,
		ptr_tangents,
		ptr_bitangent_signs,
		opt
	)) {
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

	auto start_time = clock();
	if (!morphReader.LoadFromString(json_data, morph::MorphIO::Options::None)) {
		std::cerr << "Failed to load morph from blender." << std::endl;
		return 8; // Return an error code
	}
	auto end_time = clock();
	std::cout << "Morph loaded from blender in " << (end_time - start_time) << "ms" << std::endl;
	
	if (!morphReader.Serialize(output_file)) {
		std::cerr << "Failed to save morph to file." << std::endl;
		return 9; // Return an error code
	}
	auto end_time2 = clock();
	std::cout << "Morph serialized to " << output_file << " in " << (end_time2 - end_time) << "ms" << std::endl;

	return 0;
}

uint32_t ExportMorphNumpy(const char* json_data,
	const char* output_file,
	const float* delta_positions,
	const float* target_colors,
	const float* delta_normals,
	const float* delta_tangents
)
{
	// Equivalent to blenderToMorph
	morph::MorphIO morphReader;

	auto start_time = clock();
	if (!morphReader.LoadFromNumpy(json_data, delta_positions, target_colors, delta_normals, delta_tangents, morph::MorphIO::Options::None)) {
		std::cerr << "Failed to load morph from blender." << std::endl;
		return 8; // Return an error code
	}
	auto end_time = clock();
	std::cout << "Morph loaded from blender in " << (end_time - start_time) << "ms" << std::endl;

	if (!morphReader.Serialize(output_file)) {
		std::cerr << "Failed to save morph to file." << std::endl;
		return 9; // Return an error code
	}
	auto end_time2 = clock();
	std::cout << "Morph serialized to " << output_file << " in " << (end_time2 - end_time) << "ms" << std::endl;

	return 0;
}

uint32_t ExportEmptyMorph(uint32_t n_verts, const char* output_file)
{
	// Equivalent to blenderToMorph
	morph::MorphIO morphReader;

	morphReader.FakeEmpty(n_verts);

	if (!morphReader.Serialize(output_file)) {
		std::cerr << "Failed to save morph to file." << std::endl;
		return 9; // Return an error code
	}

	std::cout << "Faked empty morph and serialized to " << output_file << std::endl;

	return 0;
}


const char* ImportMesh(const char* input_file)
{
	std::string inputMesh(input_file);

	// Create a MeshIO object
	mesh::MeshIO reader;

	// Load the mesh from the input mesh file
	if (!reader.Deserialize(inputMesh)) {
		std::cerr << "Failed to load mesh from " << inputMesh << std::endl;
		return ""; // Return an error code
	}

	// Save the mesh to the output file
	std::string JsonData;
	if (!reader.SerializeToJsonStr(JsonData)) {
		std::cerr << "Failed to serialize mesh to json" << std::endl;
		return ""; // Return an error code
	}

	std::cout << "Mesh loaded from " << inputMesh << std::endl;
	
	return utils::make_copy(JsonData);
}

const char* ImportMeshHeader(const char* input_file) {
	std::string inputMesh(input_file);

	std::string json_header;
	if (!mesh::MeshIO::read_header(inputMesh, json_header)) {
		std::cerr << "Failed to load mesh from " << inputMesh << std::endl;
		return ""; // Return an error code
	}

	return utils::make_copy(json_header);
}

uint32_t ImportMeshNumpy(const char* input_file,
	float* positions,
	int32_t* indices,
	float* normals,
	float* uv1,
	float* uv2,
	float* colors,
	float* tangents,
	int32_t* bitangent_signs,
	float* ptr_weights,
	int32_t* ptr_bone_indices
) {
	std::string inputMesh(input_file);

	mesh::MeshIO meshReader;

	if (!meshReader.Deserialize(inputMesh)) {
		std::cerr << "Failed to load mesh from " << inputMesh << std::endl;
		return 18; // Return an error code
	}

	// Save the morph to the output file
	std::string JsonData;
	if (!meshReader.LoadToNumpy(positions, indices, normals, uv1, uv2, colors, tangents, bitangent_signs, ptr_weights, ptr_bone_indices)) {
		std::cerr << "Failed to serialize morph to json" << std::endl;
		return 99;
	}

	return 0;
}

const char* ImportMorph(const char* input_file)
{
	std::string inputMorph(input_file);

	// Create a MorphIO object
	morph::MorphIO morphReader;

	// Load the morph from the input morph file
	if (!morphReader.Deserialize(inputMorph)) {
		std::cerr << "Failed to load morph from " << inputMorph << std::endl;
		return ""; // Return an error code
	}

	// Save the morph to the output file
	std::string JsonData;
	if (!morphReader.SerializeToJson(JsonData)) {
		std::cerr << "Failed to serialize morph to json" << std::endl;
		return "";
	}

	return utils::make_copy(JsonData);
}

const char* ImportMorphHeader(const char* input_file) {
	std::string inputMorph(input_file);

	std::string json_header;
	if (!morph::MorphIO::read_header(inputMorph, json_header)) {
		std::cerr << "Failed to load morph from " << inputMorph << std::endl;
		return ""; // Return an error code
	}

	return utils::make_copy(json_header);
}

uint32_t ImportMorphNumpy(const char* input_file,
	float* delta_positions,
	float* target_colors,
	float* delta_normals,
	float* delta_tangents
) {
	std::string inputMorph(input_file);

	// Create a MorphIO object
	morph::MorphIO morphReader;

	// Load the morph from the input morph file
	if (!morphReader.Deserialize(inputMorph)) {
		std::cerr << "Failed to load morph from " << inputMorph << std::endl;
		return 17; // Return an error code
	}

	// Save the morph to the output file
	std::string JsonData;
	if (!morphReader.LoadToNumpy(JsonData, delta_positions, target_colors, delta_normals, delta_tangents)) {
		std::cerr << "Failed to serialize morph to json" << std::endl;
		return 99;
	}

	return 0;
}

uint32_t CreateNif(const char* json_data, const char* output_file, const char* assets_folder)
{
	nif::NifIO nif;
	nif.SetAssetsPath(assets_folder);

	nif::ni_template::NiSkinInstanceTemplate* temp = new nif::ni_template::NiSkinInstanceTemplate();

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

	if (!nif.Serialize(output_file)) {
		std::cerr << "Failed to save nif to file." << std::endl;
		return 12; // Return an error code
	}

	std::cout << "Nif serialized to " << output_file << std::endl;

	return 0;
}

uint32_t EditNifBSGeometries(const char* base_nif_path, const char* json_data, const char* output_file, const char* assets_folder, bool edit_mat_path) {
	
	nif::NifIO base_nif;
	base_nif.SetAssetsPath(assets_folder);
		
	base_nif.Deserialize(base_nif_path);

	nif::NifIO nif;
	nif.SetAssetsPath(assets_folder);

	nif::ni_template::NiSkinInstanceTemplate* temp = new nif::ni_template::NiSkinInstanceTemplate();

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

const char* ImportNif(const char* input_file, bool export_havok_readable, const char* readable_filepath)
{
	nif::NifIO nif;

	if (!nif.Deserialize(input_file)) {
		std::cerr << "Failed to load nif from " << input_file << std::endl;
		return "";
	}

	auto t_ptr = nif.ToTemplate<nif::ni_template::NiSkinInstanceTemplate>();

	if (t_ptr == nullptr) {
		std::cerr << "Failed to convert nif to template" << std::endl;
		return "";
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

	if (export_havok_readable) {
		auto bs_cloths = nif.GetRTTIBlocks(nif::NiRTTI::BSClothExtraData);
		for (auto& cloth : bs_cloths) {
			auto cloth_ptr = dynamic_cast<nif::BSClothExtraData*>(cloth);
			if (cloth_ptr != nullptr) {
				auto instances = cloth_ptr->GetDataDeserializer().root_level_instance->dump();
				std::ofstream file_i(readable_filepath);
				file_i << instances;
				file_i.close();
			}
		}
	}
	
	return utils::make_copy(jsondata.dump());
}

uint32_t ComposePhysicsData(const char* json_data, uint32_t platform, const char* transcript_path, const char* output_file, bool export_readable)
{
	nlohmann::json jsonData = nlohmann::json::parse(json_data);

	hkphysics::hkPhysicsDataBuilder builder;

	builder.build_target_platform = (hkphysics::hkPhysicsDataBuilder::Platform)platform;

	if (!hkreflex::hkTypeTranscriptor::SetTranscriptPath(transcript_path)){
		std::cout << "Failed to set transcript path." << std::endl;
		return 13; // Return an error code
	}

	auto& transcript = hkreflex::hkTypeTranscriptor::GetInstance();
	transcript.DeserializeTranscripts(transcript_path);

	if (!builder.ParseJson(jsonData) || !builder.build_target_finished) {
		std::cout << "Physics data build failed." << std::endl;
		return 14; // Return an error code
	}

	hkphysics::hkReflDataSerializer serializer;
	serializer.root_level_container = &builder.GetTarget();

	std::ofstream file(output_file, std::ios::binary);
	if (!file.is_open()) {
		std::cout << "Failed to open output file." << std::endl;
		return 15; // Return an error code
	}

	serializer.Serialize(file);
	file.close();

	if (export_readable) {
		std::cout << "Exporting readable data..." << std::endl;
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

		std::cout << "Ensuring IO equality..." << std::endl;
		deserializer.root_level_instance->assert_equals(serializer.root_level_instance);

		auto instances = deserializer.root_level_instance->dump();
		std::ofstream file_i(std::string(output_file) + "_debug.txt");
		file_i << instances;
		file_i.close();
	}

	return 0;
}
