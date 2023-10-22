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

	// Bone list here
	uint32_t num_bones = 3;

	std::vector<std::string> bone_list = { "ABC","BCD","CDF" };

	auto root_node = dynamic_cast<nif::NiNode*>(nif.AddBlock("NiNode", "ExportScene"));
	
	auto bsxflags = dynamic_cast<nif::BSXFlags*>(nif.AddBlock("BSXFlags", "BSX"));

	root_node->AddExtraData(nif.block_manager.FindBlock(bsxflags));

	auto bsgeometry = dynamic_cast<nif::BSGeometry*>(nif.AddBlock("BSGeometry", "SOME_NAME")); // Mesh name

	root_node->AddChild(nif.block_manager.FindBlock(bsgeometry));

	auto niintegerextra = dynamic_cast<nif::NiIntegerExtraData*>(nif.AddBlock("NiIntegerExtraData", "MaterialID"));

	niintegerextra->data = 0;// Material ID

	bsgeometry->AddExtraData(nif.block_manager.FindBlock(niintegerextra));

	auto skin_attach = dynamic_cast<nif::SkinAttach*>(nif.AddBlock("SkinAttach", "SkinBMP"));

	skin_attach->bone_names = bone_list;
	skin_attach->num_bone_names = num_bones;

	bsgeometry->AddExtraData(nif.block_manager.FindBlock(skin_attach));

	auto skin_instance = dynamic_cast<nif::BSSkin::Instance*>(nif.AddBlock("BSSkin::Instance"));

	auto skin_bonedata = dynamic_cast<nif::BSSkin::BoneData*>(nif.AddBlock("BSSkin::BoneData"));

	for (int i = 0; i < num_bones; ++i) {
		nif::BSSkin::BoneData::BoneInfo bone_info;
		// Bone info here
		skin_bonedata->bone_infos.push_back(bone_info);
	}
	skin_bonedata->num_bone_infos = num_bones;

	skin_instance->skeleton_root = nif.block_manager.FindBlock(root_node);
	skin_instance->bone_data = nif.block_manager.FindBlock(skin_bonedata);
	skin_instance->num_bone_attrs = num_bones;
	for (int i = 0; i < num_bones; i++) {
		skin_instance->bone_attrs.push_back(nif::NiNodeBase::NO_REF);
	}

	bsgeometry->skin_instance = nif.block_manager.FindBlock(skin_instance);

	auto lighting_shader_property = dynamic_cast<nif::BSLightingShaderProperty*>(nif.AddBlock("BSLightingShaderProperty", "MAT_PATH"));// Material path

	bsgeometry->shader_property = nif.block_manager.FindBlock(lighting_shader_property);

	bsgeometry->flags = 14;

	nif::BSGeometry::MeshData mesh_data;

	// Write mesh info here
	mesh_data.num_indices = 0;
	mesh_data.num_vertices = 0;
	mesh_data.mesh_path = "MESH_PATH";
	mesh_data.path_length = mesh_data.mesh_path.length();

	bsgeometry->AddMesh(mesh_data);

	nif.UpdateBlockReferences();
	nif.UpdateStringReferences();

	if (!nif.Serialize(output_file)) {
		std::cerr << "Failed to save nif to file." << std::endl;
		return 10; // Return an error code
	}

	std::cout << "Nif serialized to " << output_file << std::endl;

	return 0;
}
