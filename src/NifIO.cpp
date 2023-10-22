#include "NifIO.h"

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
		auto block = CreateBlock(type, type_id);
		block->Deserialize(file);

		UpdateBlockReference(block);
		UpdateStringReference(block);

		this->blocks.push_back(block);
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

nif::NiNodeBase* nif::NifIO::CreateBlock(const std::string type_name, const uint32_t type_index)
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
	else {
		throw std::exception("Not implemented");
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

uint32_t nif::NifIO::NiStringManager::AddString(const std::string& str, const uint32_t& who)
{
	auto id = FindString(str);
	if (FindString(str) != -1) {
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

std::string nif::NifIO::NiStringManager::GetString(const uint32_t index)
{
	if (index >= header->num_strings)
		throw std::exception("Invalid string index");

	return header->strings[index];
}

uint32_t nif::NifIO::NiStringManager::FindString(const std::string& str)
{
	for (int i = 0; i < header->num_strings; i++) {
		if (header->strings[i] == str)
			return i;
	}
	return -1;
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

	if(!block || block->GetRTTI() == "NiNodeBase")
		return -1;

	auto result = std::find(header->block_types.begin(), header->block_types.end(), block->GetRTTI());
	if (result == header->block_types.end()) {
		header->block_types.push_back(block->GetRTTI());
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

nif::NiNodeBase* nif::NifIO::NiBlockManager::GetBlock(const uint32_t index)
{
	if (index >= header->num_blocks)
		throw std::exception("Invalid block index");

	return nif->blocks[index];
}

uint32_t nif::NifIO::NiBlockManager::FindBlock(const nif::NiNodeBase* block)
{
	for (int i = 0; i < header->num_blocks; i++) {
		if (nif->blocks[i] == block)
			return i;
	}
	return -1;
}
