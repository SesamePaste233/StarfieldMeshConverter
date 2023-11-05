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

const char* ImportMesh(const char* input_file, const char* output_name)
{
	std::string inputMesh(input_file);
	std::string outputName(output_name);

	size_t const p(inputMesh.find_last_of('.'));
	size_t const lastSlash = inputMesh.find_last_of("/\\");
	std::string const name(inputMesh.substr(lastSlash + 1, p));

	// Create a MeshIO object
	mesh::MeshIO reader;

	// Load the mesh from the input mesh file
	if (!reader.Deserialize(inputMesh)) {
		std::cerr << "Failed to load mesh from " << inputMesh << std::endl;
		return ""; // Return an error code
	}

	// Save the mesh to the output file
	std::string JsonData;
	if (!reader.SerializeToJson(JsonData, outputName, name)) {
		std::cerr << "Failed to serialize mesh to json" << std::endl;
		return ""; // Return an error code
	}

	std::cout << "Mesh loaded from " << inputMesh << std::endl;
	
	return Util::make_copy(JsonData);
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

	return Util::make_copy(JsonData);
}

uint32_t CreateNif(const char* json_data, const char* output_file, const char* assets_folder)
{
	nif::NifIO nif;
	nif.SetAssetsPath(assets_folder);

	nif::ni_template::NiSkinInstanceTemplate* temp = new nif::ni_template::NiSkinInstanceTemplate();

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

	if (!nif.Serialize(output_file)) {
		std::cerr << "Failed to save nif to file." << std::endl;
		return 12; // Return an error code
	}

	std::cout << "Nif serialized to " << output_file << std::endl;

	return 0;
}

const char* ImportNif(const char* input_file)
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

	
	return Util::make_copy(jsondata.dump());
}
