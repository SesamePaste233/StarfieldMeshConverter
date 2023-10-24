#include "NifIO.h"
#include "stack"

bool nif::NifIO::Deserialize(const std::string filename)
{
	this->Clear();

	std::string extension = filename.substr(filename.find_last_of(".") + 1);
	if (extension != "nif")
	{
		std::cout << "Invalid file extension" << std::endl;
		return false;
	}

	// Open the file
	std::ifstream file;
	file.open(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return false;
	}

	// Read the header
	if (!ReadHeader(file)) {
		std::cout << "Error reading header" << std::endl;
		return false;
	}

	auto _num_blocks = this->header.num_blocks;

	for (int i = 0; i < _num_blocks; i++) {
		auto type_id = this->header.block_type_indices[i];
		auto type = this->header.block_types[type_id];
		auto bytes = this->header.block_sizes[i];
		auto block = CreateBlock(type, type_id, bytes);
		block->Deserialize(file);

		this->blocks.push_back(block);

		UpdateBlockReference(block);
		UpdateStringReference(block);
	}

    return true;
}

bool nif::NifIO::Serialize(const std::string filename)
{
	std::string extension = filename.substr(filename.find_last_of(".") + 1);
	if (extension != "nif")
	{
		std::cout << "Invalid file extension" << std::endl;
		return false;
	}

	// Open the file
	std::ofstream file;
	file.open(filename, std::ios::binary);
	if (!file.is_open())
	{
		std::cout << "Error opening file" << std::endl;
		return false;
	}

	this->UpdateHeader();

	// Write the header
	if (!WriteHeader(file)) {
		std::cout << "Error writing header" << std::endl;
		return false;
	}

	for (int i = 0; i < this->header.num_blocks; i++) {
		this->blocks[i]->Serialize(file);
	}

	return true;
}

bool nif::NifIO::ReadHeader(std::istream& file)
{
	try {
		auto _header = Util::readString(file, 38);

		if (_header != this->header.header) {
			std::cout << "Invalid header" << std::endl;
			return false;
		}

		this->header.version = Util::readUInt8(file, 5);
		this->header.endian = Util::readUInt8(file)[0];
		this->header.user_version = Util::readUInt32(file)[0];
		this->header.num_blocks = Util::readUInt32(file)[0];
		this->header.BS_version = Util::readUInt32(file)[0];
		auto length = Util::readUInt8(file)[0];
		this->header.author = Util::readString(file, length);
		this->header.unk1 = Util::readUInt32(file)[0];
		length = Util::readUInt8(file)[0];
		this->header.process_script = Util::readString(file, length);
		length = Util::readUInt8(file)[0];
		this->header.unk2 = Util::readString(file, length);
		this->header.num_types = Util::readUInt16(file)[0];

		// Read the block types
		for (int i = 0; i < this->header.num_types; i++) {
			auto _l = Util::readUInt32(file)[0];
			this->header.block_types.push_back(Util::readString(file, _l));
		}

		// Read the block type indices
		for (int i = 0; i < this->header.num_blocks; i++) {
			this->header.block_type_indices.push_back(Util::readUInt16(file)[0]);
		}

		// Read the block sizes
		for (int i = 0; i < this->header.num_blocks; i++) {
			this->header.block_sizes.push_back(Util::readUInt32(file)[0]);
		}

		// Read the strings
		this->header.num_strings = Util::readUInt32(file)[0];
		this->header.max_string_length = Util::readUInt32(file)[0];
		for (int i = 0; i < this->header.num_strings; i++) {
			auto _l = Util::readUInt32(file)[0];
			this->header.strings.push_back(Util::readString(file, _l));
		}

		// Read the groups
		this->header.num_groups = Util::readUInt32(file)[0];
		for (int i = 0; i < this->header.num_groups; i++) {
			throw std::exception("Not implemented");
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}

	return true;
}

bool nif::NifIO::WriteHeader(std::ostream& file)
{
	try {
		Util::writeString(file, this->header.header);

		for (int i = 0; i < this->header.version.size(); i++) {
			Util::writeAsHex(file, this->header.version[i]);
		}

		Util::writeAsHex(file, this->header.endian);
		Util::writeAsHex(file, this->header.user_version);
		Util::writeAsHex(file, this->header.num_blocks);
		Util::writeAsHex(file, this->header.BS_version);

		uint8_t length = this->header.author.length();
		Util::writeAsHex(file, length);
		Util::writeString(file, this->header.author);

		Util::writeAsHex(file, this->header.unk1);

		length = this->header.process_script.length();
		Util::writeAsHex(file, length);
		Util::writeString(file, this->header.process_script);

		length = this->header.unk2.length();
		Util::writeAsHex(file, length);
		Util::writeString(file, this->header.unk2);

		Util::writeAsHex(file, this->header.num_types);

		// Write the block types
		for (int i = 0; i < this->header.num_types; i++) {
			uint32_t _l = this->header.block_types[i].length();
			Util::writeAsHex(file, _l);
			Util::writeString(file, this->header.block_types[i]);
		}

		// Write the block type indices
		for (int i = 0; i < this->header.num_blocks; i++) {
			Util::writeAsHex(file, this->header.block_type_indices[i]);
		}

		// Write the block sizes
		for (int i = 0; i < this->header.num_blocks; i++) {
			Util::writeAsHex(file, this->header.block_sizes[i]);
		}

		// Write the strings
		Util::writeAsHex(file, this->header.num_strings);
		Util::writeAsHex(file, this->header.max_string_length);

		for (int i = 0; i < this->header.num_strings; i++) {
			uint32_t _l = this->header.strings[i].length();
			Util::writeAsHex(file, _l);
			Util::writeString(file, this->header.strings[i]);
		}

		// Write the groups
		Util::writeAsHex(file, this->header.num_groups);
		for (int i = 0; i < this->header.num_groups; i++) {
			throw std::exception("Not implemented");
		}
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	return true;
}

bool nif::NifIO::UpdateHeader()
{
	// Update the header
	this->header.num_blocks = this->blocks.size();
	this->header.num_types = this->header.block_types.size();
	this->header.num_strings = this->header.strings.size();
	this->header.num_groups = this->header.groups.size();

	// Update the block type indices
	this->header.block_type_indices.clear();
	for (int i = 0; i < this->header.num_blocks; i++) {
		this->header.block_type_indices.push_back(this->blocks[i]->type_index);
	}

	// Update the block sizes
	this->header.block_sizes.clear();
	for (int i = 0; i < this->header.num_blocks; i++) {
		this->header.block_sizes.push_back(this->blocks[i]->GetSize());
	}

	// Update the strings
	this->header.num_strings = this->header.strings.size();
	this->header.max_string_length = 0;
	for (int i = 0; i < this->header.num_strings; i++) {
		if (this->header.strings[i].length() > this->header.max_string_length)
			this->header.max_string_length = this->header.strings[i].length();
	}

	// Update the groups
	this->header.num_groups = this->header.groups.size();

	return true;
}

void nif::NifIO::Clear()
{
	header = {};
	blocks.clear();
}

nif::NiNodeBase* nif::NifIO::CreateBlock(const std::string type_name, const uint32_t type_index, const uint32_t block_bytes)
{
	NiNodeBase* block = nullptr;

	if (type_name == "NiNode") {
		block = new NiNode();
	}
	else if (type_name == "BSXFlags") {
		block = new BSXFlags();
	}
	else if (type_name == "NiIntegerExtraData") {
		block = new NiIntegerExtraData();
	}
	else if (type_name == "BSGeometry") {
		block = new BSGeometry();
	}
	else if (type_name == "SkinAttach") {
		block = new SkinAttach();
	}
	else if (type_name == "BSSkin::Instance") {
		block = new BSSkin::Instance();
	}
	else if (type_name == "BSSkin::BoneData") {
		block = new BSSkin::BoneData();
	}
	else if (type_name == "BSLightingShaderProperty") {
		block = new BSLightingShaderProperty();
	}
	else if (type_name == "NiStringExtraData") {
		block = new NiStringExtraData();
	}
	else if (type_name == "NiIntegersExtraData") {
		block = new NiIntegersExtraData();
	}
	else {
		_ASSERT(block_bytes != -1);
		block = new UnkBinaryBlock(block_bytes);
		dynamic_cast<UnkBinaryBlock*>(block)->RTTI = type_name;
	}

	if (block != nullptr)
		block->type_index = type_index;

	return block;
}

nif::NiNodeBase* nif::NifIO::AddBlock(const std::string type_name, const std::string block_name)
{
	auto block = CreateBlock(type_name, -1);
	if (block != nullptr) {
		auto rtn = this->block_manager.RegisterBlock(block);

		if (rtn == -1) {
			delete block;
			return nullptr;
		}

		if (!block_name.empty()) {
			auto name_index = this->string_manager.AddString(block_name, rtn);
			block->name_index = name_index;
		}

		return block;
	}
	return nullptr;
}

nif::NiNodeBase* nif::NifIO::AddBlock(const nif::NiRTTI rtti, const std::string block_name)
{
	return AddBlock(nif::RTTIToString(rtti), block_name);
}

std::vector<nif::NiNodeBase*> nif::NifIO::GetRTTIBlocks(const nif::NiRTTI& RTTI, const bool use_name, const std::string& name) const
{
	std::vector<nif::NiNodeBase*> result;

	for (auto& block : blocks) {
		if (block->GetRTTI() == RTTI) {
			if (use_name && this->string_manager.GetString(block->name_index) != name)
				continue;

			result.push_back(block);
		}
	}

	return result;
}

bool nif::NifIO::FromTemplate(ni_template::NiTemplateBase* template_ptr)
{
	return template_ptr->ToNif(*this);
}

std::vector<nif::NiNodeBase*> nif::NifIO::GetReferencedBlocks(const nif::NiNodeBase* referer, const nif::NiRTTI& RTTI, const bool use_name, const std::string& name) const
{
	std::vector<nif::NiNodeBase*> result;

	auto references = referer->GetBlockReference();

	for (auto& ref : references) {
		auto block = this->block_manager.GetBlock(ref);
		if (RTTI == nif::NiRTTI::None) {
			result.push_back(block);
		}
		else if (block && block->GetRTTI() == RTTI) {
			if (use_name && this->string_manager.GetString(block->name_index) != name)
				continue;

			result.push_back(block);
		}
	}

	return result;
}

mesh::MeshIO* nif::NifIO::GetMesh(const std::string& mesh_factory_path) const
{
	mesh::MeshIO* reader = new mesh::MeshIO;

	if (!reader->Deserialize(this->assets_path + mesh_factory_path + ".mesh")) {
		std::cout << "Failed to load mesh from " << this->assets_path + mesh_factory_path + ".mesh" << std::endl;
		delete reader;
		return nullptr;
	}

	return reader;
}

uint32_t nif::NifIO::NiStringManager::AddString(const std::string& str, const uint32_t& who)
{
	auto id = FindString(str);
	if (FindString(str) != nif::NiNodeBase::NO_REF) {
		return AddReference(id, who);
	}

	header->num_strings++;
	header->strings.push_back(str);

	id = header->num_strings - 1;

	return AddReference(id, who);
}

uint32_t nif::NifIO::NiStringManager::AddReference(const uint32_t& index, const uint32_t& who)
{
	auto& ref = refs[index];
	if (std::find(ref.begin(), ref.end(), who) == ref.end()) {
		refs[index].push_back(who);
		return index;
	}
	return index;
}

std::string nif::NifIO::NiStringManager::GetString(const uint32_t index) const
{
	if (index >= header->num_strings)
		return "";

	return header->strings[index];
}

uint32_t nif::NifIO::NiStringManager::FindString(const std::string& str) const
{
	for (int i = 0; i < header->num_strings; i++) {
		if (header->strings[i] == str)
			return i;
	}
	return nif::NiNodeBase::NO_REF;
}

void nif::NifIO::NiStringManager::MoveString(const std::vector<uint32_t> new_order)
{
	_ASSERT(new_order.size() == header->num_strings);

	std::vector<std::string> new_strings;
	std::unordered_map<uint32_t, std::vector<uint32_t>> new_refs;

	for (int i = 0; i < header->num_strings; i++) {
		auto old_id = new_order[i];
		new_strings.push_back(header->strings[old_id]);
		new_refs[i] = refs[old_id];

		for (auto& referee : refs[old_id]) {
			nif->blocks[referee]->UpdateStrings(old_id, i);
		}
	}

	std::swap(header->strings, new_strings);
	std::swap(refs, new_refs);
}

uint32_t nif::NifIO::NiBlockManager::RegisterBlock(nif::NiNodeBase* block)
{
	if (nif->blocks.size() != header->num_blocks) {
		header->block_type_indices.resize(nif->blocks.size());
	}

	if(!block || block->GetRTTI() == nif::NiRTTI::NiNodeBase)
		return nif::NiNodeBase::NO_REF;

	auto result = std::find(header->block_types.begin(), header->block_types.end(), nif::RTTIToString(block->GetRTTI()));

	if (result == header->block_types.end()) {
		header->block_types.push_back(nif::RTTIToString(block->GetRTTI()).data());
		header->block_type_indices.push_back(header->block_types.size() - 1);
		header->num_types = header->block_types.size();
	}
	else {
		header->block_type_indices.push_back(result - header->block_types.begin());
	}

	header->num_blocks = header->block_type_indices.size();
	block->type_index = header->block_type_indices.back();

	nif->blocks.push_back(block);

	return header->num_blocks - 1;
}

uint32_t nif::NifIO::NiBlockManager::AddReference(const uint32_t& index, const uint32_t& who)
{
	auto& ref = refs[index];
	if (std::find(ref.begin(), ref.end(), who) == ref.end()) {
		refs[index].push_back(who);
		return index;
	}
	return index;
}

nif::NiNodeBase* nif::NifIO::NiBlockManager::GetBlock(const uint32_t index) const
{
	if (index >= header->num_blocks)
		return nullptr;

	return nif->blocks[index];
}

uint32_t nif::NifIO::NiBlockManager::FindBlock(const nif::NiNodeBase* block) const
{
	for (int i = 0; i < header->num_blocks; i++) {
		if (nif->blocks[i] == block)
			return i;
	}
	return nif::NiNodeBase::NO_REF;
}

uint32_t nif::NifIO::NiBlockManager::FindBlockByName(const std::string& name) const
{
	if (name.empty())
		return nif::NiNodeBase::NO_REF;

	for (int i = 0; i < header->num_blocks; i++) {
		if (nif->string_manager.GetString(nif->blocks[i]->name_index) == name)
			return i;
	}

	return nif::NiNodeBase::NO_REF;
}

bool nif::ni_template::NiRootSceneTemplate::ToNif(NifIO& source)
{
	source.Clear();
	auto root_node = dynamic_cast<nif::NiNode*>(source.AddBlock("NiNode", this->root_name));
	return true;
}

nif::ni_template::RTTI nif::ni_template::NiRootSceneTemplate::FromNif(const NifIO& nif)
{
	auto scene_root = nif.GetRTTIBlocks(nif::NiRTTI::NiNode, true, "ExportScene");

	if (scene_root.size() != 1) {
		std::cout << "Warning: Nif format incorrect. Expect a single root node named \"ExportScene\"." << std::endl;
		return RTTI::None;
	}

	auto root_node = dynamic_cast<NiNode*>(scene_root[0]);

	this->root_name = nif.string_manager.GetString(root_node->name_index);

	this->root_flags = root_node->flags;

	std::memcpy(this->root_rotation_matrix, root_node->rotation, 9 * sizeof(float));

	std::memcpy(this->root_translation, root_node->translation, 3 * sizeof(float));

	this->root_scale = root_node->scale;

	return RTTI::NiRootScene;
}

nlohmann::json nif::ni_template::NiRootSceneTemplate::Serialize() const
{
	nlohmann::json result;

	result["root_name"] = this->root_name;
	result["root_flags"] = this->root_flags;
	for (int i = 0; i < 3; i++) {
		result["root_rotation_matrix"][i] = this->root_rotation_matrix[i];
	}
	for (int i = 0; i < 3; i++) {
		result["root_translation"][i] = this->root_translation[i];
	}
	result["root_scale"] = this->root_scale;

	return result;
}

bool nif::ni_template::NiRootSceneTemplate::Deserialize(nlohmann::json data)
{
	if (data.find("root_name") != data.end())
		this->root_name = data["root_name"];

	if (data.find("root_flags") != data.end())
		this->root_flags = data["root_flags"];

	if (data.find("root_rotation_matrix") != data.end()) {
		for (int i = 0; i < 3; i++) {
			this->root_rotation_matrix[i][0] = data["root_rotation_matrix"][i][0];
			this->root_rotation_matrix[i][1] = data["root_rotation_matrix"][i][1];
			this->root_rotation_matrix[i][2] = data["root_rotation_matrix"][i][2];
		}
	}

	if (data.find("root_translation") != data.end()) {
		for (int i = 0; i < 3; i++) {
			this->root_translation[i] = data["root_translation"][i];
		}
	}

	if (data.find("root_scale") != data.end())
		this->root_scale = data["root_scale"];

	return true;
}

bool nif::ni_template::NiSingleGeometryTemplate::ToNif(NifIO& nif)
{
	if(!NiRootSceneTemplate::ToNif(nif))
		return false;

	auto root_node = dynamic_cast<nif::NiNode*>(nif.GetRTTIBlocks(nif::NiRTTI::NiNode)[0]);

	auto bsxflags = dynamic_cast<nif::BSXFlags*>(nif.AddBlock(nif::NiRTTI::BSXFlags, "BSX"));

	root_node->AddExtraData(nif.block_manager.FindBlock(bsxflags));

	auto bsgeometry = dynamic_cast<nif::BSGeometry*>(nif.AddBlock(nif::NiRTTI::BSGeometry, this->geo_name)); // Mesh name

	root_node->AddChild(nif.block_manager.FindBlock(bsgeometry));

	auto niintegerextra = dynamic_cast<nif::NiIntegerExtraData*>(nif.AddBlock(nif::NiRTTI::NiIntegerExtraData, "MaterialID"));

	niintegerextra->data = this->mat_id;// Material ID

	bsgeometry->AddExtraData(nif.block_manager.FindBlock(niintegerextra));

	auto lighting_shader_property = dynamic_cast<nif::BSLightingShaderProperty*>(nif.AddBlock(nif::NiRTTI::BSLightingShaderProperty, this->mat_path));// Material path

	bsgeometry->shader_property = nif.block_manager.FindBlock(lighting_shader_property);

	bsgeometry->flags = this->geo_flags;

	for (MeshInfo& mesh : this->geo_mesh_lod) {
		if (!mesh.has_mesh)
			continue;
		nif::BSGeometry::MeshData mesh_data;

		// Write mesh info here
		mesh_data.num_indices = mesh.num_indices;
		mesh_data.num_vertices = mesh.num_vertices;
		mesh_data.mesh_path = mesh.factory_path;
		mesh_data.path_length = mesh_data.mesh_path.length();

		bsgeometry->AddMesh(mesh_data);
	}

	std::memcpy(bsgeometry->rotation, this->geo_rotation_matrix, 9 * sizeof(float));
	std::memcpy(bsgeometry->translation, this->geo_translation, 3 * sizeof(float));
	bsgeometry->scale = this->geo_scale;


	nif.UpdateBlockReferences();
	nif.UpdateStringReferences();

	return true;
}

nif::ni_template::RTTI nif::ni_template::NiSingleGeometryTemplate::FromNif(const NifIO& nif)
{
	auto rtti = NiRootSceneTemplate::FromNif(nif);
	if (rtti != nif::ni_template::RTTI::NiRootScene)
		return rtti;

	auto scene_root = nif.GetRTTIBlocks(nif::NiRTTI::NiNode, true, "ExportScene");

	auto root_node = dynamic_cast<NiNode*>(scene_root[0]);

	auto bsxflags = nif.GetReferencedBlocks(root_node, nif::NiRTTI::BSXFlags, true, "BSX");

	if (bsxflags.size() != 1) {
		std::cout << "Warning: Nif format incorrect. Expect a single BSXFlags block named \"BSX\"." << std::endl;
		return nif::ni_template::RTTI::NiRootScene;
	}

	auto bsx_node = dynamic_cast<BSXFlags*>(bsxflags[0]);

	auto geometries = nif.GetRTTIBlocks(nif::NiRTTI::BSGeometry);

	if (geometries.size() != 1) {
		std::cout << "Warning: Only support nif with a single geometry." << std::endl;
		return nif::ni_template::RTTI::NiRootScene;
	}

	auto bs_geo = dynamic_cast<BSGeometry*>(geometries[0]);

	if (bs_geo->meshes.size() != 1) {
		std::cout << "Warning: Only support nif with a single mesh." << std::endl;
		return nif::ni_template::RTTI::NiRootScene;
	}

	auto shader_properties = nif.GetReferencedBlocks(bs_geo, nif::NiRTTI::BSLightingShaderProperty);

	auto material_properties = nif.GetReferencedBlocks(bs_geo, nif::NiRTTI::NiIntegerExtraData, true, "MaterialID");

	if (shader_properties.size() != 1) {
		std::cout << "Warning: Only support nif with a single shader property." << std::endl;
		return nif::ni_template::RTTI::NiRootScene;
	}

	if (material_properties.size() != 1) {
		std::cout << "Warning: Only support nif with a single material property." << std::endl;
		return nif::ni_template::RTTI::NiRootScene;
	}

	auto shader_property = dynamic_cast<BSLightingShaderProperty*>(shader_properties[0]);

	auto material_property = dynamic_cast<NiIntegerExtraData*>(material_properties[0]);

	this->geo_name = nif.string_manager.GetString(bs_geo->name_index);

	this->geo_flags = bs_geo->flags;

	std::memcpy(this->geo_rotation_matrix, bs_geo->rotation, 9 * sizeof(float));

	std::memcpy(this->geo_translation, bs_geo->translation, 3 * sizeof(float));

	this->geo_scale = bs_geo->scale;


	this->bsx_flags = bsx_node->flags;

	this->mat_id = material_property->data;

	this->mat_path = nif.string_manager.GetString(shader_property->name_index);

	int i = 0;
	for (auto& mesh : bs_geo->meshes) {
		nif::ni_template::NiSingleGeometryTemplate::MeshInfo mesh_info;

		mesh_info.has_mesh = true;

		mesh_info.factory_path = mesh.mesh_path;

		mesh_info.num_vertices = mesh.num_vertices;

		mesh_info.num_indices = mesh.num_indices;

		this->geo_mesh_lod[i] = mesh_info;

		i++;
	}

	return nif::ni_template::RTTI::NiSingleGeometry;
}

nlohmann::json nif::ni_template::NiSingleGeometryTemplate::Serialize() const
{
	nlohmann::json result = NiRootSceneTemplate::Serialize();

	result["geo_name"] = this->geo_name;
	result["geo_flags"] = this->geo_flags;
	for (int i = 0; i < 3; i++) {
		result["geo_rotation_matrix"][i] = this->geo_rotation_matrix[i];
	}
	for (int i = 0; i < 3; i++) {
		result["geo_translation"][i] = this->geo_translation[i];
	}
	result["geo_scale"] = this->geo_scale;

	result["geo_mesh_lod"] = nlohmann::json::array();

	for (int i = 0; i < 4; ++i) {
		const MeshInfo& mesh = this->geo_mesh_lod[i];
		if (!mesh.has_mesh)
			continue;

		nlohmann::json mesh_info;

		mesh_info["factory_path"] = mesh.factory_path;
		mesh_info["num_indices"] = mesh.num_indices;
		mesh_info["num_vertices"] = mesh.num_vertices;

		result["geo_mesh_lod"].push_back(mesh_info);
	}

	result["mat_id"] = this->mat_id;	
	result["mat_path"] = this->mat_path;

	return result;
}

bool nif::ni_template::NiSingleGeometryTemplate::Deserialize(nlohmann::json data)
{
	if (!NiRootSceneTemplate::Deserialize(data))
		return false;

	if (data.find("geo_name") != data.end())
		this->geo_name = data["geo_name"];

	if (data.find("geo_flags") != data.end())
		this->geo_flags = data["geo_flags"];

	if (data.find("geo_rotation_matrix") != data.end()) {
		for (int i = 0; i < 3; ++i) {
			this->geo_rotation_matrix[i][0] = data["geo_rotation_matrix"][i][0];
			this->geo_rotation_matrix[i][1] = data["geo_rotation_matrix"][i][1];
			this->geo_rotation_matrix[i][2] = data["geo_rotation_matrix"][i][2];
		}
	}

	if (data.find("geo_translation") != data.end()) {
		for (int i = 0; i < 3; ++i) {
			this->geo_translation[i] = data["geo_translation"][i];
		}
	}

	if (data.find("geo_scale") != data.end())
		this->geo_scale = data["geo_scale"];

	if (data.find("geo_mesh_lod") != data.end()) {
		for (int i = 0; i < 4; ++i) {
			const nlohmann::json& mesh_info = data["geo_mesh_lod"][i];
			if (mesh_info.is_null())
				continue;

			this->geo_mesh_lod[i].factory_path = mesh_info["factory_path"];
			this->geo_mesh_lod[i].num_indices = mesh_info["num_indices"];
			this->geo_mesh_lod[i].num_vertices = mesh_info["num_vertices"];
			this->geo_mesh_lod[i].has_mesh = true;
		}
	}

	if (data.find("mat_id") != data.end())
		this->mat_id = data["mat_id"];

	if (data.find("mat_path") != data.end())
		this->mat_path = data["mat_path"];

	return true;
}

bool nif::ni_template::NiSingleSkinInstanceTemplate::ToNif(NifIO& nif)
{
	if(!NiSingleGeometryTemplate::ToNif(nif))
		return false;

	uint32_t num_bones = this->bone_names.size();

	auto root_node = dynamic_cast<nif::NiNode*>(nif.GetRTTIBlocks(nif::NiRTTI::NiNode)[0]);
	auto bsgeometry = dynamic_cast<nif::BSGeometry*>(nif.GetRTTIBlocks(nif::NiRTTI::BSGeometry)[0]);

	auto skin_attach = dynamic_cast<nif::SkinAttach*>(nif.AddBlock(nif::NiRTTI::SkinAttach, "SkinBMP"));

	skin_attach->bone_names = this->bone_names;
	skin_attach->num_bone_names = num_bones;

	bsgeometry->AddExtraData(nif.block_manager.FindBlock(skin_attach));

	auto skin_instance = dynamic_cast<nif::BSSkin::Instance*>(nif.AddBlock(nif::NiRTTI::BSSkinInstance));

	auto skin_bonedata = dynamic_cast<nif::BSSkin::BoneData*>(nif.AddBlock(nif::NiRTTI::BSSkinBoneData));

	skin_bonedata->bone_infos = this->bone_infos;
	skin_bonedata->num_bone_infos = num_bones;

	skin_instance->skeleton_root = nif.block_manager.FindBlock(root_node);
	skin_instance->bone_data = nif.block_manager.FindBlock(skin_bonedata);
	skin_instance->num_bone_attachs = num_bones;

	if (this->bone_refs.size() == num_bones) {
		for (int i = 0; i < num_bones; i++) {
			auto rtn = nif.block_manager.FindBlockByName(this->bone_refs[i]);

			if (rtn == (uint32_t)-1)
				std::cout << "Warning: Invalid bone attach reference name: " << this->bone_refs[i] << std::endl;

			skin_instance->bone_attach_refs.push_back(rtn);
		}
	}
	else {
		for (int i = 0; i < num_bones; i++) {
			skin_instance->bone_attach_refs.push_back(nif::NiNodeBase::NO_REF);
		}
	}

	bsgeometry->skin_instance = nif.block_manager.FindBlock(skin_instance);

	nif.UpdateBlockReferences();
	nif.UpdateStringReferences();

	return true;
}

nif::ni_template::RTTI nif::ni_template::NiSingleSkinInstanceTemplate::FromNif(const NifIO& nif)
{
	auto rtti = NiSingleGeometryTemplate::FromNif(nif);
	if (rtti != nif::ni_template::RTTI::NiSingleGeometry)
		return rtti;

	auto scene_root = nif.GetRTTIBlocks(nif::NiRTTI::NiNode, true, "ExportScene");

	auto root_node = dynamic_cast<NiNode*>(scene_root[0]);

	auto geometries = nif.GetRTTIBlocks(nif::NiRTTI::BSGeometry);

	auto bs_geo = dynamic_cast<BSGeometry*>(geometries[0]);

	auto skin_attachs = nif.GetReferencedBlocks(bs_geo, nif::NiRTTI::SkinAttach, true, "SkinBMP");

	if (skin_attachs.size() != 1) {
		std::cout << "Warning: Only support nif with a single skin attach." << std::endl;
		return nif::ni_template::RTTI::NiSingleGeometry;
	}

	auto skin_attach = dynamic_cast<SkinAttach*>(skin_attachs[0]);

	for (int i = 0; i < skin_attach->num_bone_names; i++) {
		this->bone_names.push_back(skin_attach->bone_names[i]);
	}

	auto skin_instances = nif.GetReferencedBlocks(bs_geo, nif::NiRTTI::BSSkinInstance);

	if (skin_instances.size() != 1) {
		std::cout << "Warning: Only support nif with a single skin instance." << std::endl;
		return nif::ni_template::RTTI::NiSingleGeometry;
	}

	auto skin_instance = dynamic_cast<BSSkin::Instance*>(skin_instances[0]);

	for (auto refs : skin_instance->bone_attach_refs) {
		auto block = nif.block_manager.GetBlock(refs);
		if (block) {
			this->bone_refs.push_back(nif.string_manager.GetString(block->name_index));
		}
		else {
			this->bone_refs.push_back("");
		}
	}

	auto skin_bonedatas = nif.GetReferencedBlocks(skin_instance, nif::NiRTTI::BSSkinBoneData);

	if (skin_bonedatas.size() != 1) {
		std::cout << "Warning: Only support nif with a single skin bone data." << std::endl;
		return nif::ni_template::RTTI::NiSingleGeometry;
	}

	auto skin_bonedata = dynamic_cast<BSSkin::BoneData*>(skin_bonedatas[0]);

	for (int i = 0; i < skin_bonedata->num_bone_infos; i++) {
		this->bone_infos.push_back(skin_bonedata->bone_infos[i]);
	}

	return nif::ni_template::RTTI::NiSingleSkinInstance;
}

nlohmann::json nif::ni_template::NiSingleSkinInstanceTemplate::Serialize() const
{
	nlohmann::json result = NiSingleGeometryTemplate::Serialize();

	result["bone_names"] = nlohmann::json::array();
	for (int i = 0; i < this->bone_names.size(); i++) {
		result["bone_names"].push_back(this->bone_names[i]);
	}

	result["bone_refs"] = nlohmann::json::array();
	for (int i = 0; i < this->bone_refs.size(); i++) {
		result["bone_refs"].push_back(this->bone_refs[i]);
	}

	result["bone_infos"] = nlohmann::json::array();
	for (int i = 0; i < this->bone_infos.size(); i++) {
		nlohmann::json bone_info;
		for (int j = 0; j < 3; ++j) {
			bone_info["center"][j] = this->bone_infos[i].center[j];
		}
		bone_info["radius"] = this->bone_infos[i].radius;

		for (int j = 0; j < 3; ++j) {
			bone_info["rotation"][j][0] = this->bone_infos[i].rotation[j][0];
			bone_info["rotation"][j][1] = this->bone_infos[i].rotation[j][1];
			bone_info["rotation"][j][2] = this->bone_infos[i].rotation[j][2];
		}

		for (int j = 0; j < 3; ++j) {
			bone_info["translation"][j] = this->bone_infos[i].translation[j];
		}

		result["bone_infos"].push_back(bone_info);
	}

	return result;
}

bool nif::ni_template::NiSingleSkinInstanceTemplate::Deserialize(nlohmann::json data)
{
	if (!NiSingleGeometryTemplate::Deserialize(data))
		return false;

	if (data.find("bone_names") != data.end()) {
		for (int i = 0; i < data["bone_names"].size(); i++) {
			this->bone_names.push_back(data["bone_names"][i]);
		}
	}

	if (data.find("bone_refs") != data.end()) {
		for (int i = 0; i < data["bone_refs"].size(); i++) {
			this->bone_refs.push_back(data["bone_refs"][i]);
		}
	}

	if (data.find("bone_infos") != data.end()) {
		for (int i = 0; i < data["bone_infos"].size(); i++) {
			const nlohmann::json& bone_info = data["bone_infos"][i];
			BoneInfo info;
			info.center[0] = bone_info["center"][0];
			info.center[1] = bone_info["center"][1];
			info.center[2] = bone_info["center"][2];
			info.radius = bone_info["radius"];
			for (int i = 0; i < 3; ++i) {
				info.rotation[i][0] = bone_info["rotation"][i][0];
				info.rotation[i][1] = bone_info["rotation"][i][1];
				info.rotation[i][2] = bone_info["rotation"][i][2];
			}
			for (int i = 0; i < 3; ++i) {
				info.translation[i] = bone_info["translation"][i];
			}

			
			this->bone_infos.push_back(info);
		}
	}

	return true;
}

bool nif::Armature::FromNif(const NifIO& nif, const bool skeleton_mode)
{
	auto& manager = nif.block_manager;

	auto _root = manager.GetBlock(manager.FindBlockByName("Root"));

	if (!_root)
		return false;

	auto bone_root = dynamic_cast<NiNode*>(_root);

	this->root = new Bone;
	if (!this->root->FromNiNode(bone_root, nif)) {
		delete this->root;
		this->root = nullptr;
		return false;
	}

	std::stack<std::pair<NiNode*,Bone*>> nodeStack;
	nodeStack.push(std::make_pair(bone_root, this->root));

	while (!nodeStack.empty()) {
		NiNode* current = nodeStack.top().first;
		Bone* current_bone = nodeStack.top().second;

		nodeStack.pop();

		for (int i = current->children.size() - 1; i >= 0; --i) {
			auto _child = manager.GetBlock(current->children[i]);

			auto name = nif.string_manager.GetString(_child->name_index);

			if (skeleton_mode && skeleton_bones.find(name) == skeleton_bones.end())
				continue;

			if (_child != nullptr) {
				auto child = dynamic_cast<NiNode*>(_child);
				Bone* child_bone = new Bone;
				if (!child_bone->FromNiNode(child, nif)) {
					delete child_bone;
					child_bone = nullptr;
					continue;
				}
				child_bone->SetParent(current_bone);
				nodeStack.push(std::make_pair(child, child_bone));
			}
		}
	}
}

using namespace nlohmann;
bool nif::Armature::ToJson(const std::string& file, bool global_heads_tails)
{
	json json_armature;

	json_armature = this->Serialize(this->root, global_heads_tails);

	std::ofstream out(file);
	out << std::setw(4) << json_armature << std::endl;
	out.close();

	return true;
}

nif::ni_template::NiTemplateBase* nif::ni_template::slice_cast(nif::ni_template::NiTemplateBase*& ptr, const nif::ni_template::RTTI& rtti)
{
	switch (rtti) {
	case nif::ni_template::RTTI::NiRootScene:
		return nif::ni_template::slice_cast<nif::ni_template::NiRootSceneTemplate>(ptr);
	case nif::ni_template::RTTI::NiSingleGeometry:
		return nif::ni_template::slice_cast<nif::ni_template::NiSingleGeometryTemplate>(ptr);
	case nif::ni_template::RTTI::NiSingleSkinInstance:
		return nif::ni_template::slice_cast<nif::ni_template::NiSingleSkinInstanceTemplate>(ptr);
	}

	return nullptr;
}
