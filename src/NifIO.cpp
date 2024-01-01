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

	uint32_t cur_pos = file.tellg();
	for (int i = 0; i < _num_blocks; i++) {
		auto type_id = this->header.block_type_indices[i];
		auto& type = this->header.block_types[type_id];
		auto bytes = this->header.block_sizes[i];
		auto block = CreateBlock(type, type_id, bytes);

		file.seekg(cur_pos, std::ios::beg);
		block->Deserialize(file);

		cur_pos += bytes;

		if (file.tellg() != cur_pos) {
			std::cout << "Warning: Potential data mismatch in block: " + std::to_string(i) + " in file: " + filename << std::endl;
			std::cout << " Block type: " + type << std::endl;
			std::cout << " Block size: " + std::to_string(bytes) << std::endl;
			std::cout << " Block offset: " + std::to_string(cur_pos - bytes) << std::endl;
			std::cout << " Block name: " + this->string_manager.GetString(block->name_index) << std::endl;
		}

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
		auto _header = utils::readString(file, 38);

		if (_header != this->header.header) {
			std::cout << "Invalid header" << std::endl;
			return false;
		}

		this->header.version = utils::read<uint8_t>(file, 5);
		this->header.endian = utils::read<uint8_t>(file)[0];
		this->header.user_version = utils::read<uint32_t>(file)[0];
		this->header.num_blocks = utils::read<uint32_t>(file)[0];
		this->header.BS_version = utils::read<uint32_t>(file)[0];
		auto length = utils::read<uint8_t>(file)[0];
		this->header.author = utils::readString(file, length);
		this->header.unk1 = utils::read<uint32_t>(file)[0];
		length = utils::read<uint8_t>(file)[0];
		this->header.process_script = utils::readString(file, length);
		length = utils::read<uint8_t>(file)[0];
		this->header.unk2 = utils::readString(file, length);
		this->header.num_types = utils::read<uint16_t>(file)[0];

		// Read the block types
		for (int i = 0; i < this->header.num_types; i++) {
			auto _l = utils::read<uint32_t>(file)[0];
			this->header.block_types.push_back(utils::readString(file, _l));
		}

		// Read the block type indices
		for (int i = 0; i < this->header.num_blocks; i++) {
			this->header.block_type_indices.push_back(utils::read<uint16_t>(file)[0]);
		}

		// Read the block sizes
		for (int i = 0; i < this->header.num_blocks; i++) {
			this->header.block_sizes.push_back(utils::read<uint32_t>(file)[0]);
		}

		// Read the strings
		this->header.num_strings = utils::read<uint32_t>(file)[0];
		this->header.max_string_length = utils::read<uint32_t>(file)[0];
		for (int i = 0; i < this->header.num_strings; i++) {
			auto _l = utils::read<uint32_t>(file)[0];
			this->header.strings.push_back(utils::readString(file, _l));
		}

		// Read the groups
		this->header.num_groups = utils::read<uint32_t>(file)[0];
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
		utils::writeString(file, this->header.header);

		for (int i = 0; i < this->header.version.size(); i++) {
			utils::writeAsHex(file, this->header.version[i]);
		}

		utils::writeAsHex(file, this->header.endian);
		utils::writeAsHex(file, this->header.user_version);
		utils::writeAsHex(file, this->header.num_blocks);
		utils::writeAsHex(file, this->header.BS_version);

		uint8_t length = this->header.author.length();
		utils::writeAsHex(file, length);
		utils::writeString(file, this->header.author);

		utils::writeAsHex(file, this->header.unk1);

		length = this->header.process_script.length();
		utils::writeAsHex(file, length);
		utils::writeString(file, this->header.process_script);

		length = this->header.unk2.length();
		utils::writeAsHex(file, length);
		utils::writeString(file, this->header.unk2);

		utils::writeAsHex(file, this->header.num_types);

		// Write the block types
		for (int i = 0; i < this->header.num_types; i++) {
			uint32_t _l = this->header.block_types[i].length();
			utils::writeAsHex(file, _l);
			utils::writeString(file, this->header.block_types[i]);
		}

		// Write the block type indices
		for (int i = 0; i < this->header.num_blocks; i++) {
			utils::writeAsHex(file, this->header.block_type_indices[i]);
		}

		// Write the block sizes
		for (int i = 0; i < this->header.num_blocks; i++) {
			utils::writeAsHex(file, this->header.block_sizes[i]);
		}

		// Write the strings
		utils::writeAsHex(file, this->header.num_strings);
		utils::writeAsHex(file, this->header.max_string_length);

		for (int i = 0; i < this->header.num_strings; i++) {
			uint32_t _l = this->header.strings[i].length();
			utils::writeAsHex(file, _l);
			utils::writeString(file, this->header.strings[i]);
		}

		// Write the groups
		utils::writeAsHex(file, this->header.num_groups);
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
	else if (type_name == "BSConnectPoint::Parents") {
		block = new BSConnectPointParents();
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
	else if (type_name == "BSClothExtraData") {
		_ASSERT(block_bytes != -1);
		block = new BSClothExtraData(block_bytes);
		dynamic_cast<BSClothExtraData*>(block)->RTTI = type_name;
	}
	else if (type_name == "BSBound") {
		block = new BSBound();
	}
	else if (type_name == "bhkPhysicsSystem") {
		_ASSERT(block_bytes != -1);
		block = new bhkPhysicsSystem(block_bytes);
		dynamic_cast<bhkPhysicsSystem*>(block)->RTTI = type_name;
	}
	else if (type_name == "bhkNPCollisionObject") {
		block = new bhkNPCollisionObject();
	}
	else {
		_ASSERT(block_bytes != -1);
		block = new BinaryBlock(block_bytes);
		dynamic_cast<BinaryBlock*>(block)->RTTI = type_name;
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

nif::NiNode* nif::NifIO::GetRootNode() const
{
	auto root_node = dynamic_cast<nif::NiNode*>(GetRTTIBlocks(nif::NiRTTI::NiNode)[0]);

	return root_node;
}

nif::BSXFlags* nif::NifIO::GetBSXFlag() const
{
	auto root = GetRootNode();

	if (!root)
		return nullptr;

	auto bsx_flags = GetReferencedBlocks(root, nif::NiRTTI::BSXFlags);

	if (bsx_flags.empty())
		return nullptr;

	auto bsx_flag = dynamic_cast<nif::BSXFlags*>(bsx_flags[0]);

	return bsx_flag;
}

bool nif::NifIO::FromTemplate(ni_template::NiTemplateBase* template_ptr)
{
	if (!template_ptr)
		return false;

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

//bool nif::ni_template::NiRootSceneTemplate::ToNif(NifIO& nif)
//{
//	nif.Clear();
//	if (root_node == nullptr)
//		return false;
//
//	auto f = [&nif](nif::NiNode* parent, NodeInfo* cur_node)->nif::NiNode* {
//		auto cur_ni_node = dynamic_cast<nif::NiNode*>(nif.AddBlock("NiNode", cur_node->name));
//
//		cur_ni_node->flags = cur_node->flags;
//
//		std::memcpy(cur_ni_node->rotation, cur_node->rotation, 9 * sizeof(float));
//
//		std::memcpy(cur_ni_node->translation, cur_node->translation, 3 * sizeof(float));
//
//		cur_ni_node->scale = cur_node->scale;
//
//		if (parent)
//			parent->AddChild(nif.block_manager.FindBlock(cur_ni_node));
//
//		return cur_ni_node;
//		};
//
//	Traverse<nif::NiNode*>(nullptr, this->root_node, f);
//
//	return true;
//}
//
//nif::ni_template::RTTI nif::ni_template::NiRootSceneTemplate::FromNif(const NifIO& nif)
//{
//	auto root_node = nif.GetRootNode();
//
//	if (!root_node) {
//		std::cout << "Warning: Nif format incorrect. Expect a single root node named \"ExportScene\"." << std::endl;
//		return RTTI::None;
//	}
//
//	this->root_node->name = nif.string_manager.GetString(root_node->name_index);
//
//	this->root_node->flags = root_node->flags;
//
//	std::memcpy(this->root_node->rotation, root_node->rotation, 9 * sizeof(float));
//
//	std::memcpy(this->root_node->translation, root_node->translation, 3 * sizeof(float));
//
//	this->root_node->scale = root_node->scale;
//
//	return RTTI::NiRootScene;
//}
//
//nlohmann::json nif::ni_template::NiRootSceneTemplate::Serialize() const
//{
//	nlohmann::json result;
//
//	result["root_name"] = this->root_name;
//	result["root_flags"] = this->root_flags;
//	for (int i = 0; i < 3; i++) {
//		result["root_rotation_matrix"][i] = this->root_rotation_matrix[i];
//	}
//	for (int i = 0; i < 3; i++) {
//		result["root_translation"][i] = this->root_translation[i];
//	}
//	result["root_scale"] = this->root_scale;
//
//	return result;
//}
//
//bool nif::ni_template::NiRootSceneTemplate::Deserialize(nlohmann::json data)
//{
//	if (data.find("root_name") != data.end())
//		this->root_name = data["root_name"];
//
//	if (data.find("root_flags") != data.end())
//		this->root_flags = data["root_flags"];
//
//	if (data.find("root_rotation_matrix") != data.end()) {
//		for (int i = 0; i < 3; i++) {
//			this->root_rotation_matrix[i][0] = data["root_rotation_matrix"][i][0];
//			this->root_rotation_matrix[i][1] = data["root_rotation_matrix"][i][1];
//			this->root_rotation_matrix[i][2] = data["root_rotation_matrix"][i][2];
//		}
//	}
//
//	if (data.find("root_translation") != data.end()) {
//		for (int i = 0; i < 3; i++) {
//			this->root_translation[i] = data["root_translation"][i];
//		}
//	}
//
//	if (data.find("root_scale") != data.end())
//		this->root_scale = data["root_scale"];
//
//	return true;
//}

bool nif::ni_template::NiSimpleGeometryTemplate::ToNif(NifIO& nif)
{
	if(!NiArmatureTemplate::ToNif(nif))
		return false;

	for (auto& bone : this->bones) {
		auto ni_node = nif.block_manager.GetBlock(bone.ni_node);
		if(ni_node->GetRTTI() != nif::NiRTTI::BSGeometry)
			continue;
		auto bsgeo = dynamic_cast<nif::BSGeometry*>(ni_node);

		if (bone.geometry_index == -1) {
			std::cout << "Warning: Geometry index not set for bone " << bone.name << std::endl;
			continue;
		}

		auto& geo_info = this->geo_infos[bone.geometry_index];

		auto shader_property = dynamic_cast<nif::BSLightingShaderProperty*>(nif.AddBlock(nif::NiRTTI::BSLightingShaderProperty, geo_info.mat_path));

		bsgeo->shader_property = nif.block_manager.FindBlock(shader_property);

		auto material_property = dynamic_cast<nif::NiIntegerExtraData*>(nif.AddBlock(nif::NiRTTI::NiIntegerExtraData, "MaterialID"));

		bsgeo->AddExtraData(nif.block_manager.FindBlock(material_property));

		material_property->data = geo_info.mat_id;

		std::memcpy(bsgeo->center, geo_info.bounding_sphere, 3 * sizeof(float));

		bsgeo->radius = geo_info.bounding_sphere[3];

		std::memcpy(bsgeo->bbox_center_expand, geo_info.bounding_center, 3 * sizeof(float));

		std::memcpy(bsgeo->bbox_center_expand + 3, geo_info.bounding_expand, 3 * sizeof(float));

		for (int i = 0; i < 4; ++i) {
			MeshInfo& mesh_info = geo_info.geo_mesh_lod[i];

			if (!mesh_info.has_mesh)
				continue;

			nif::BSGeometry::MeshData mesh_data;

			mesh_data.mesh_path = mesh_info.factory_path;

			mesh_data.num_vertices = mesh_info.num_vertices;

			mesh_data.num_indices = mesh_info.num_indices;

			mesh_data.path_length = mesh_info.factory_path.length();

			bsgeo->meshes.push_back(mesh_data);
		}
	}

	nif.UpdateBlockReferences();
	nif.UpdateStringReferences();

	return true;
}

nif::ni_template::RTTI nif::ni_template::NiSimpleGeometryTemplate::FromNif(const NifIO& nif)
{
	auto rtti = NiArmatureTemplate::FromNif(nif);
	if (rtti != nif::ni_template::RTTI::NiArmature) {
		return rtti;
	}

	auto root_node = nif.GetRootNode();

	auto bsxflags = nif.GetReferencedBlocks(root_node, nif::NiRTTI::BSXFlags, true, "BSX");

	if (bsxflags.size() != 1) {
		std::cout << "Warning: Nif format incorrect. Expect a single BSXFlags block named \"BSX\"." << std::endl;
		return rtti;
	}

	auto bsx_node = dynamic_cast<BSXFlags*>(bsxflags[0]);

	this->bsx_flags = bsx_node->flags;

	this->geo_infos.clear();
	int geo_id = 0;
	for (auto& bone : bones) {
		GeoInfo geo_info;

		auto ni_node = nif.block_manager.GetBlock(bone.ni_node);
		if (ni_node->GetRTTI() != nif::NiRTTI::BSGeometry)
			continue;

		auto bs_geo = dynamic_cast<nif::BSGeometry*>(ni_node);

		auto shader_properties = nif.GetReferencedBlocks(bs_geo, nif::NiRTTI::BSLightingShaderProperty);

		auto material_properties = nif.GetReferencedBlocks(bs_geo, nif::NiRTTI::NiIntegerExtraData, true, "MaterialID");

		if (shader_properties.size() != 1) {
			std::cout << "Warning: Only support nif with a single shader property." << std::endl;
			return rtti;
		}

		if (material_properties.size() != 1) {
			std::cout << "Warning: Only support nif with a single material property." << std::endl;
			return rtti;
		}

		std::memcpy(geo_info.bounding_sphere, bs_geo->center, 3 * sizeof(float));

		geo_info.bounding_sphere[3] = bs_geo->radius;

		std::memcpy(geo_info.bounding_center, bs_geo->bbox_center_expand, 3 * sizeof(float));

		std::memcpy(geo_info.bounding_expand, bs_geo->bbox_center_expand + 3, 3 * sizeof(float));

		auto shader_property = dynamic_cast<BSLightingShaderProperty*>(shader_properties[0]);

		auto material_property = dynamic_cast<NiIntegerExtraData*>(material_properties[0]);

		geo_info.mat_id = material_property->data;

		geo_info.mat_path = nif.string_manager.GetString(shader_property->name_index);

		bone.geometry_index = geo_id++;

		int i = 0;
		for (auto& mesh : bs_geo->meshes) {
			nif::ni_template::NiSimpleGeometryTemplate::MeshInfo mesh_info;

			mesh_info.has_mesh = true;

			mesh_info.factory_path = mesh.mesh_path;

			mesh_info.num_vertices = mesh.num_vertices;

			mesh_info.num_indices = mesh.num_indices;

			geo_info.geo_mesh_lod[i] = mesh_info;

			i++;
		}

		this->geo_infos.push_back(geo_info);
	}

	if (geo_id == 0) {
		std::cout << "Warning: No geometry found." << std::endl;
		return rtti;
	}

	return nif::ni_template::RTTI::NiSimpleGeometry;
}

nlohmann::json nif::ni_template::NiSimpleGeometryTemplate::Serialize() const
{
	nlohmann::json _result = NiArmatureTemplate::Serialize();

	_result["geometries"] = nlohmann::json::array();

	for (auto& geo_info : this->geo_infos) {
		nlohmann::json bsgeometry_result;

		bsgeometry_result["geo_mesh_lod"] = nlohmann::json::array();

		for (int i = 0; i < 4; ++i) {
			const MeshInfo& mesh = geo_info.geo_mesh_lod[i];
			if (!mesh.has_mesh)
				continue;

			nlohmann::json mesh_info;

			mesh_info["factory_path"] = mesh.factory_path;
			mesh_info["num_indices"] = mesh.num_indices;
			mesh_info["num_vertices"] = mesh.num_vertices;

			bsgeometry_result["geo_mesh_lod"].push_back(mesh_info);
		}

		bsgeometry_result["geo_bounding_sphere"] = nlohmann::json::array();
		for (int i = 0; i < 4; ++i) {
			bsgeometry_result["geo_bounding_sphere"].push_back(geo_info.bounding_sphere[i] < FLT_MAX ? geo_info.bounding_sphere[i] : 0);
		}

		bsgeometry_result["geo_bounding_center"] = nlohmann::json::array();
		for (int i = 0; i < 3; ++i) {
			bsgeometry_result["geo_bounding_center"].push_back(geo_info.bounding_center[i] < FLT_MAX ? geo_info.bounding_center[i] : 0);
		}

		bsgeometry_result["geo_bounding_expand"] = nlohmann::json::array();
		for (int i = 0; i < 3; ++i) {
			bsgeometry_result["geo_bounding_expand"].push_back(geo_info.bounding_expand[i] < FLT_MAX ? geo_info.bounding_expand[i] : 0);
		}

		bsgeometry_result["mat_id"] = geo_info.mat_id;
		bsgeometry_result["mat_path"] = geo_info.mat_path;

		_result["geometries"].push_back(bsgeometry_result);
	}

	return _result;
}

nif::ni_template::RTTI nif::ni_template::NiSimpleGeometryTemplate::Deserialize(nlohmann::json _data)
{
	auto rtti = NiArmatureTemplate::Deserialize(_data);
	if (rtti != RTTI::NiArmature)
		return rtti;

	if (_data.find("geometries") == _data.end() || _data["geometries"].empty())
		return rtti;


	this->geo_infos.clear();
	for (auto& data : _data["geometries"]) {
		GeoInfo geo_info;

		if (data.find("geo_mesh_lod") != data.end()) {
			for (int i = 0; i < 4; ++i) {
				const nlohmann::json& mesh_info = data["geo_mesh_lod"][i];
				if (mesh_info.is_null())
					continue;

				geo_info.geo_mesh_lod[i].factory_path = mesh_info["factory_path"];
				geo_info.geo_mesh_lod[i].num_indices = mesh_info["num_indices"];
				geo_info.geo_mesh_lod[i].num_vertices = mesh_info["num_vertices"];
				geo_info.geo_mesh_lod[i].has_mesh = true;
			}
		}

		bool no_culling = true;

		if (data.find("geo_bounding_center") != data.end()) {
			for (int j = 0; j < 3; ++j) {
				geo_info.bounding_center[j] = data["geo_bounding_center"][j];
				if (geo_info.bounding_center[j] != 0)
					no_culling = false;
			}
		}

		if (data.find("geo_bounding_expand") != data.end()) {
			for (int j = 0; j < 3; ++j) {
				geo_info.bounding_expand[j] = data["geo_bounding_expand"][j];
				if (geo_info.bounding_expand[j] != 0)
					no_culling = false;
			}
		}

		if (no_culling) {
			std::memset(geo_info.bounding_center, FLT_MAX, sizeof(float) * 3);
			std::memset(geo_info.bounding_expand, FLT_MAX, sizeof(float) * 3);
		}

		if (data.find("geo_bounding_sphere") != data.end()) {
			for (int j = 0; j < 4; ++j) {
				geo_info.bounding_sphere[j] = data["geo_bounding_sphere"][j];
			}
		}
		else if (!no_culling) {
			std::memcpy(geo_info.bounding_sphere, geo_info.bounding_center, 3 * sizeof(float));
			geo_info.bounding_sphere[3] = utils::_vector_norm(geo_info.bounding_expand, 3);
		}
		else {
			std::memset(geo_info.bounding_sphere, 0, sizeof(float) * 4);
		}


		if (data.find("mat_path") != data.end()) {
			std::string path = data["mat_path"];
			std::transform(path.begin(), path.end(), path.begin(),
				[](unsigned char c) -> unsigned char {
					if (c == '/')
						return '\\';
					return c;
				});
			geo_info.mat_path = path;
		}

		if (data.find("mat_id") != data.end()) {
			geo_info.mat_id = data["mat_id"];
		}
		else {
			std::string encoding_string = geo_info.mat_path;

			std::transform(encoding_string.begin(), encoding_string.end(), encoding_string.begin(), ::tolower);

			geo_info.mat_id = utils::encodeCRC32(encoding_string);
		}

		this->geo_infos.push_back(geo_info);
	}

	return nif::ni_template::RTTI::NiSimpleGeometry;
}

bool nif::ni_template::NiSkinInstanceTemplate::ToNif(NifIO& nif)
{
	if(!NiSimpleGeometryTemplate::ToNif(nif))
		return false;

	for (auto& bone: bones) {

		auto ni_node = nif.block_manager.GetBlock(bone.ni_node);
		if (ni_node->GetRTTI() != nif::NiRTTI::BSGeometry)
			continue;

		auto bsgeometry = dynamic_cast<nif::BSGeometry*>(ni_node);
		auto& skin_info = this->skin_infos[bone.geometry_index];

		if (!skin_info.has_skin)
			continue;

		auto skin_attach = dynamic_cast<nif::SkinAttach*>(nif.AddBlock(nif::NiRTTI::SkinAttach, "SkinBMP"));

		uint32_t num_bones = skin_info.bone_names.size();
		skin_attach->bone_names = skin_info.bone_names;
		skin_attach->num_bone_names = num_bones;

		bsgeometry->AddExtraData(nif.block_manager.FindBlock(skin_attach));

		std::memset(bsgeometry->center, 0, sizeof(float) * 3);
		bsgeometry->radius = 0;

		std::memset(bsgeometry->bbox_center_expand, FLT_MAX, sizeof(float) * 6);

		auto skin_instance = dynamic_cast<nif::BSSkin::Instance*>(nif.AddBlock(nif::NiRTTI::BSSkinInstance));

		auto skin_bonedata = dynamic_cast<nif::BSSkin::BoneData*>(nif.AddBlock(nif::NiRTTI::BSSkinBoneData));

		skin_bonedata->num_bone_infos = num_bones;

		if (skin_info.request_recalc_bounding_sphere) {
			auto mesh = nif.GetMesh(bsgeometry);
			if (mesh == nullptr) {
				std::cout << "Warning: Failed to load mesh for geometry. " << std::endl;
				return false;
			}
			mesh->CalculateBoneBounding();
			for (int j = 0; j < num_bones; ++j) {
				auto& bone_info = skin_info.bone_infos[j];

				auto B_inv = utils::xf::createTransformationMatrix(bone_info.rotation, bone_info.translation);
				Eigen::Vector3f center = (B_inv * utils::xf::fromTransform(mesh->bone_bounding[j].center)).hnormalized();

				std::memcpy(bone_info.center, center.data(), sizeof(float) * 3);
				bone_info.radius = mesh->bone_bounding[j].radius;
			}
			delete mesh;
		}

		skin_bonedata->bone_infos = skin_info.bone_infos;

		skin_instance->skeleton_root = root().ni_node;
		skin_instance->bone_data = nif.block_manager.FindBlock(skin_bonedata);
		skin_instance->num_bone_attachs = num_bones;

		if (skin_info.bone_refs.size() == num_bones) {
			for (int i = 0; i < num_bones; i++) {
				auto rtn = nif.block_manager.FindBlockByName(skin_info.bone_refs[i]);

				if (rtn == (uint32_t)-1)
					std::cout << "Warning: Invalid bone attach reference name: " << skin_info.bone_refs[i] << std::endl;

				skin_instance->bone_attach_refs.push_back(rtn);
			}
		}
		else {
			for (int i = 0; i < num_bones; i++) {
				skin_instance->bone_attach_refs.push_back(nif::NiNodeBase::NO_REF);
			}
		}

		bsgeometry->skin_instance = nif.block_manager.FindBlock(skin_instance);
	}

	nif.UpdateBlockReferences();
	nif.UpdateStringReferences();

	auto bsx_flag = nif.GetBSXFlag();

	if (bsx_flag) {
		bsx_flag->flags = 65536;
	}

	return true;
}

nif::ni_template::RTTI nif::ni_template::NiSkinInstanceTemplate::FromNif(const NifIO& nif)
{
	auto rtti = NiSimpleGeometryTemplate::FromNif(nif);

	if (rtti != nif::ni_template::RTTI::NiSimpleGeometry) {
		return rtti;
	}

	this->skin_infos.clear();
	this->skin_infos.assign(this->geo_infos.size(), SkinInfo());

	uint32_t geo_id = 0;
	bool skin_found = false;
	for (auto& bone : bones) {
		auto ni_node = nif.block_manager.GetBlock(bone.ni_node);
		if (ni_node->GetRTTI() != nif::NiRTTI::BSGeometry)
			continue;

		SkinInfo skin_info;

		auto bs_geo = dynamic_cast<BSGeometry*>(ni_node);

		auto skin_attachs = nif.GetReferencedBlocks(bs_geo, nif::NiRTTI::SkinAttach, true, "SkinBMP");

		if (skin_attachs.size() == 0) {
			std::cout << "Warning: No skin attach found for geometry "<<bone.name<<std::endl;
			continue;
		}else if (skin_attachs.size() != 1) {
			std::cout << "Warning: Only support nif with a single skin attach." << std::endl;
			return rtti;
		}

		auto skin_attach = dynamic_cast<SkinAttach*>(skin_attachs[0]);

		for (int i = 0; i < skin_attach->num_bone_names; i++) {
			skin_info.bone_names.push_back(skin_attach->bone_names[i]);
		}

		auto skin_instances = nif.GetReferencedBlocks(bs_geo, nif::NiRTTI::BSSkinInstance);

		if (skin_instances.size() == 0) {
			std::cout << "Warning: No skin instance found for geometry " << bone.name << std::endl;
			continue;
		}else if (skin_instances.size() != 1) {
			std::cout << "Warning: Only support nif with a single skin instance." << std::endl;
			return rtti;
		}

		auto skin_instance = dynamic_cast<BSSkin::Instance*>(skin_instances[0]);

		for (auto refs : skin_instance->bone_attach_refs) {
			auto block = nif.block_manager.GetBlock(refs);
			if (block) {
				skin_info.bone_refs.push_back(nif.string_manager.GetString(block->name_index));
			}
			else {
				skin_info.bone_refs.push_back("");
			}
		}

		auto skin_bonedatas = nif.GetReferencedBlocks(skin_instance, nif::NiRTTI::BSSkinBoneData);

		if (skin_bonedatas.size() == 0) {
			std::cout << "Warning: No skin bone data found for geometry " << bone.name << std::endl;
			continue;
		}else if (skin_bonedatas.size() != 1) {
			std::cout << "Warning: Only support nif with a single skin bone data." << std::endl;
			return rtti;
		}

		auto skin_bonedata = dynamic_cast<BSSkin::BoneData*>(skin_bonedatas[0]);

		for (int i = 0; i < skin_bonedata->num_bone_infos; i++) {
			skin_info.bone_infos.push_back(skin_bonedata->bone_infos[i]);
		}

		skin_info.has_skin = true;
		this->skin_infos[geo_id] = skin_info;

		geo_id++;
		skin_found = true;
	}

	if (!skin_found) {
		std::cout << "Warning: No skin found." << std::endl;
		return rtti;
	}
	return nif::ni_template::RTTI::NiSkinInstance;
}

nlohmann::json nif::ni_template::NiSkinInstanceTemplate::Serialize() const
{
	nlohmann::json _result = NiSimpleGeometryTemplate::Serialize();

	uint32_t current_skin = 0;
	for (auto& result : _result["geometries"]) {
		auto& skin_info = this->skin_infos[current_skin++];

		result["has_skin"] = skin_info.has_skin;
		result["bone_names"] = nlohmann::json::array();
		for (int i = 0; i < skin_info.bone_names.size(); i++) {
			result["bone_names"].push_back(skin_info.bone_names[i]);
		}

		result["bone_refs"] = nlohmann::json::array();
		for (int i = 0; i < skin_info.bone_refs.size(); i++) {
			result["bone_refs"].push_back(skin_info.bone_refs[i]);
		}

		result["bone_infos"] = nlohmann::json::array();
		for (int i = 0; i < skin_info.bone_infos.size(); i++) {
			nlohmann::json bone_info;
			for (int j = 0; j < 3; ++j) {
				bone_info["center"][j] = skin_info.bone_infos[i].center[j];
			}
			bone_info["radius"] = skin_info.bone_infos[i].radius;

			auto matrix = utils::xf::createTransformationMatrix(skin_info.bone_infos[i].rotation, skin_info.bone_infos[i].translation);

			for (int k = 0; k < 4; ++k) {
				bone_info["matrix"].push_back(nlohmann::json::array());
				for (int j = 0; j < 4; ++j) {
					bone_info["matrix"][k].push_back(matrix(k, j));
				}
			}

			result["bone_infos"].push_back(bone_info);
		}
	}
	return _result;
}

nif::ni_template::RTTI nif::ni_template::NiSkinInstanceTemplate::Deserialize(nlohmann::json _data)
{
	auto rtti = NiSimpleGeometryTemplate::Deserialize(_data);
	if (rtti != nif::ni_template::RTTI::NiSimpleGeometry)
		return rtti;

	if (_data.find("geometries") == _data.end())
		return rtti;

	this->skin_infos.clear();
	bool has_skin = false;
	for (auto& data : _data["geometries"]) {
		if (data["has_skin"] == false) {
			this->skin_infos.push_back(SkinInfo());
			continue;
		}

		SkinInfo skin_info;
		skin_info.has_skin = true;
		if (data.find("bone_names") != data.end()) {
			for (int i = 0; i < data["bone_names"].size(); i++) {
				skin_info.bone_names.push_back(data["bone_names"][i]);
			}
			has_skin = true;
		}

		if (data.find("bone_refs") != data.end()) {
			for (int i = 0; i < data["bone_refs"].size(); i++) {
				skin_info.bone_refs.push_back(data["bone_refs"][i]);
			}
			has_skin = true;
		}

		if (data.find("bone_infos") != data.end()) {
			for (int i = 0; i < data["bone_infos"].size(); i++) {
				const nlohmann::json& bone_info = data["bone_infos"][i];
				BoneInfo info;
				if (bone_info.find("center") != bone_info.end() && bone_info.find("radius") != bone_info.end()) {
					info.center[0] = bone_info["center"][0];
					info.center[1] = bone_info["center"][1];
					info.center[2] = bone_info["center"][2];
					info.radius = bone_info["radius"];
				}
				else {
					skin_info.request_recalc_bounding_sphere = true;
				}

				Eigen::Matrix4f matrix = Eigen::Matrix4f::Identity();
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 4; ++j) {
						matrix(i, j) = bone_info["matrix"][i][j];
					}
				}

				Eigen::Matrix3f rotation = matrix.block<3, 3>(0, 0);
				Eigen::Vector3f translation = matrix.block<3, 1>(0, 3);

				for (int j = 0; j < 3; ++j) {
					info.rotation[j][0] = rotation(j, 0);
					info.rotation[j][1] = rotation(j, 1);
					info.rotation[j][2] = rotation(j, 2);
				}

				for (int j = 0; j < 3; ++j) {
					info.translation[j] = translation(j);
				}


				skin_info.bone_infos.push_back(info);
			}
			has_skin = true;
		}

		this->skin_infos.push_back(skin_info);
	}

	if (!has_skin) {
		std::cout << "Warning: Skin info size not match geometry info size." << std::endl;
		return rtti;
	}

	return nif::ni_template::RTTI::NiSkinInstance;
}

bool nif::ni_template::NiArmatureTemplate::ToNif(NifIO& nif)
{
	nif.Clear();

	if (IsRootEmtpy())
		return false;

	auto f = [this, &nif](NodeInfo& cur_node)->void {
		nif::NiObject* cur_ni_node = nullptr;
		if (cur_node.geometry_index != -1) {
			cur_ni_node = dynamic_cast<nif::NiObject*>(nif.AddBlock("BSGeometry", cur_node.name));
		}
		else {
			cur_ni_node = dynamic_cast<nif::NiObject*>(nif.AddBlock("NiNode", cur_node.name));
			if (this->sub_template & (SubTemplate::PureSkeleton|SubTemplate::Weapon) && cur_node.prevent_optimization) {
				auto extra_data = dynamic_cast<nif::NiStringExtraData*>(nif.AddBlock(nif::NiRTTI::NiStringExtraData, "sgoKeep"));
				auto extra_data_id = nif.block_manager.FindBlock(extra_data);
				extra_data->string_index = nif.string_manager.AddString("sgoKeep", extra_data_id);
				cur_ni_node->AddExtraData(extra_data_id);
			}
		}

		cur_ni_node->flags = cur_node.flags;

		std::memcpy(cur_ni_node->rotation, cur_node.rotation, 9 * sizeof(float));

		std::memcpy(cur_ni_node->translation, cur_node.translation, 3 * sizeof(float));

		cur_ni_node->scale = cur_node.scale;

		cur_node.ni_node = nif.block_manager.FindBlock(cur_ni_node);

		if (cur_node.parent != (uint32_t)-1) {
			auto parent = dynamic_cast<nif::NiNode*>(nif.block_manager.GetBlock(this->bones[cur_node.parent].ni_node));
			if (parent)
				parent->AddChild(nif.block_manager.FindBlock(cur_ni_node));
		}
		return;
		};

	Traverse(0, f);

	nif.UpdateBlockReferences();
	nif.UpdateStringReferences();

	auto root_node = nif.GetRootNode();

	if (root_node == nullptr)
		return false;

	auto bsxflags = dynamic_cast<nif::BSXFlags*>(nif.AddBlock(nif::NiRTTI::BSXFlags, "BSX"));
	
	root_node->AddExtraData(nif.block_manager.FindBlock(bsxflags));

	bsxflags->flags = this->bsx_flags;

	if (this->sub_template & SubTemplate::PureSkeleton) {
		auto bsbound = dynamic_cast<nif::BSBound*>(nif.AddBlock(nif::NiRTTI::BSBound, "BBX"));

		auto BBX_prefab = nif::BSBound::_human_bsbound_prefab();

		std::memcpy(bsbound->center, BBX_prefab.center, 3 * sizeof(float));
		std::memcpy(bsbound->dimensions, BBX_prefab.dimensions, 3 * sizeof(float));

		root_node->AddExtraData(nif.block_manager.FindBlock(bsbound));
	}

	if (this->connection_points_parent.size() > 0) {
		auto bsconnectpointparents = dynamic_cast<nif::BSConnectPointParents*>(nif.AddBlock(nif::NiRTTI::BSConnectPointParents, "CPA"));

		bsconnectpointparents->num_parents = this->connection_points_parent.size();
		bsconnectpointparents->connect_points = this->connection_points_parent;

		root_node->AddExtraData(nif.block_manager.FindBlock(bsconnectpointparents));
	}

	nif.UpdateBlockReference(root_node);

	return true;
}

nif::ni_template::RTTI nif::ni_template::NiArmatureTemplate::FromNif(const NifIO& nif)
{
	this->bones.clear();
	this->bones.push_back(NodeInfo());
	auto& manager = nif.block_manager;

	auto bscloth = nif.GetRTTIBlocks(nif::NiRTTI::BSClothExtraData);

	if (bscloth.size() == 1) {
		auto cloth = dynamic_cast<nif::BSClothExtraData*>(bscloth[0]);
		if (cloth->root_level_container) {
			auto root_lvl_container = dynamic_cast<hktypes::hkRootLevelContainer*>(cloth->root_level_container);
			if (root_lvl_container) {
				this->havok_root_lvl_container = root_lvl_container;
				auto hkaskele = root_lvl_container->GetNamedVariantRef("hkaSkeleton");
				if (hkaskele) {
					auto skeleton = dynamic_cast<hktypes::hkaSkeleton*>(hkaskele);
					if (skeleton) {
						this->havok_skeleton = skeleton;
					}
				}
			}
		}
	}

	auto _root = nif.GetRootNode();

	if (!_root)
		return nif::ni_template::RTTI::None;

	auto bone_root = dynamic_cast<NiNode*>(_root);

	auto root_ptr = &root();
	if (!root_ptr->FromNiObject(bone_root, nif)) {
		this->bones.clear();
		return nif::ni_template::RTTI::None;
	}

	std::stack<std::pair<NiObject*,uint32_t>> nodeStack;
	nodeStack.push(std::make_pair(bone_root, 0));

	while (!nodeStack.empty()) {
		NiObject* current_obj = nodeStack.top().first;

		auto current_index = nodeStack.top().second;

		nodeStack.pop();

		NiNode* current = dynamic_cast<NiNode*>(current_obj);

		if (!current)
			continue;

		for (auto extra_data_id : current->extra_data) {
			auto extra_data = nif.block_manager.GetBlock(extra_data_id);
			if (extra_data->GetRTTI() != nif::NiRTTI::NiStringExtraData)
				continue;

			auto name = nif.string_manager.GetString(extra_data->name_index);
			if (name != "sgoKeep")
				continue;
			
			auto extra_string_data = dynamic_cast<nif::NiStringExtraData*>(extra_data);

			auto string_data = nif.string_manager.GetString(extra_string_data->string_index);

			if (string_data == "sgoKeep") {
				bones[current_index].prevent_optimization = true;
			}
		}

		for (int i = 0; i < current->children.size(); ++i) {
			auto _child = manager.GetBlock(current->children[i]);

			auto name = nif.string_manager.GetString(_child->name_index);

			if (skeleton_mode && skeleton_bones.find(name) == skeleton_bones.end())
				continue;

			if (_child != nullptr) {
				auto child = dynamic_cast<NiObject*>(_child);
				NodeInfo child_bone;
				if (!child_bone.FromNiObject(child, nif)) {
					continue;
				}
				bones[current_index].children.push_back(this->bones.size());
				auto child_index = this->bones.size();
				child_bone.parent = current_index;
				this->bones.push_back(child_bone);
				nodeStack.push(std::make_pair(child, child_index));
			}
		}
	}

	auto connect_point_parents = nif.GetReferencedBlocks(_root, nif::NiRTTI::BSConnectPointParents, true, "CPA");

	for (auto& cpp : connect_point_parents) {
		auto bsconnectpointparents = dynamic_cast<nif::BSConnectPointParents*>(cpp);
		this->connection_points_parent.insert(this->connection_points_parent.end(), bsconnectpointparents->connect_points.begin(), bsconnectpointparents->connect_points.end());
	}

	return nif::ni_template::RTTI::NiArmature;
}
