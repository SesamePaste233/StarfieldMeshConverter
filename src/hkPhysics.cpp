#include "hkPhysics.h"

hkphysics::hkPhysicsReflectionData::~hkPhysicsReflectionData() {
	for (auto& block : indexed_blocks) {
		delete block;
	}

	for (auto& cls : classes) {
		delete cls;
	}

	for (auto& chunk : data_chunks) {
		delete chunk.second;
	}
}

bool hkphysics::hkPhysicsReflectionData::Deserialize(const std::string filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		return false;
	}

	uint32_t size = utils::read<uint32_t>(file)[0];

	return this->Deserialize(file);
}

bool hkphysics::hkPhysicsReflectionData::Deserialize(std::istream& data_stream)
{
	this->Clear();

	this->data_size = utils::read<uint32_t>(data_stream)[0];

	const uint8_t* _file_buffer = utils::readBytes(data_stream, this->data_size);

	utils::DataAccessor _accessor = utils::DataAccessor::Create(_file_buffer, this->data_size, true);

	hkDataChunkTAG0* chunk = new hkDataChunkTAG0(this);

	chunk->SetBuffer(_accessor.make_reference());

	size_t cur_pos = 0;
	uint32_t sizeAndFlags = utils::readFromAccessor<uint32_t>(_accessor, cur_pos, true); // Size and flags
	chunk->chunk_decorator = sizeAndFlags >> 24; // Decorator
	chunk->data_size = sizeAndFlags & 0x00FFFFFF; // Data size

	std::string type_name = utils::readStringFromAccessor(_accessor, cur_pos, 4); // Type name
	chunk->SetName(type_name);

	chunk->DistributeAndDecode();

	chunk->Traverse([this](hkDataChunkBase* chunk) {
		this->data_chunks[chunk->GetType()] = chunk;
		if (std::string(chunk->type_name) == "TYPE") {
			chunk->OwnBuffer();
		}
		});

	for (auto type = this->classes.begin() + 1; type != this->classes.end(); type++) {
		(*type)->ctype_name = hktypes::hkTypeMapper::GetSingleton().GetCType((*type));
	}

	// Root level instance
	auto suc = this->indexed_blocks[1]->BuildInstances();
	if (!suc) {
		std::cout << "Warning: root level instance build failed." << std::endl;
		return false;
	}

	for (auto block = this->indexed_blocks.begin() + 1; block != this->indexed_blocks.end(); block++) {
		if((*block)->_built)
			continue;
		std::cout << "Warning: bogus block detected." << std::endl;
		return false;
	}

	if (this->indexed_blocks[1]->m_instances.size() != 1) {
		std::cout << "Warning: root level instance count is not 1." << std::endl;
		return false;
	}

	this->root_level_instance = this->indexed_blocks[1]->m_instances[0];

	ExtractClasses();
	return true;
}

bool hkphysics::hkPhysicsReflectionData::Deserialize(const uint8_t* data)
{
	this->Clear();

	size_t cur_pos = 0;

	this->data_size = utils::readFromBuffer<uint32_t>(data, cur_pos);

	const uint8_t* _file_buffer = data + cur_pos;

	utils::DataAccessor _accessor = utils::DataAccessor::Create(_file_buffer, this->data_size, true);

	hkDataChunkTAG0* chunk = new hkDataChunkTAG0(this);

	chunk->SetBuffer(_accessor);

	cur_pos = 0;
	chunk->chunk_decorator = utils::readFromAccessor<uint16_t>(_accessor, cur_pos, true); // Decorator
	chunk->data_size = utils::readFromAccessor<uint16_t>(_accessor, cur_pos, true); // Data size

	std::string type_name = utils::readStringFromAccessor(_accessor, cur_pos, 4); // Type name
	chunk->SetName(type_name);

	chunk->DistributeAndDecode();

	chunk->Traverse([this](hkDataChunkBase* chunk) {
		this->data_chunks[chunk->GetType()] = chunk;
		});

	for (auto type = this->classes.begin() + 1; type != this->classes.end(); type++) {
		(*type)->ctype_name = hktypes::hkTypeMapper::GetSingleton().GetCType((*type));
	}

	// Root level instance
	auto suc = this->indexed_blocks[1]->BuildInstances();
	if (!suc) {
		std::cout << "Warning: root level instance build failed." << std::endl;
		return false;
	}

	for (auto block = this->indexed_blocks.begin() + 1; block != this->indexed_blocks.end(); block++) {
		if ((*block)->_built)
			continue;
		std::cout << "Warning: bogus block detected." << std::endl;
		return false;
	}

	if (this->indexed_blocks[1]->m_instances.size() != 1) {
		std::cout << "Warning: root level instance count is not 1." << std::endl;
		return false;
	}

	this->root_level_instance = this->indexed_blocks[1]->m_instances[0];

	ExtractClasses();
	return true;
}

bool hkphysics::hkPhysicsReflectionData::SerializeWithTypeUnchanged(std::ostream& data_stream)
{
	if (!this->_is_type_unchanged)
		return false;

	auto patch_chunk = this->GetPatchChunk();
	if (patch_chunk) {
		patch_chunk->patches.clear();
	}
	else {
		throw std::exception("Not implemented");
	}

	uint64_t cur_block_index = 0;

	size_t alloc_size = 0;
	for (auto block : this->indexed_blocks) {
		alloc_size += ((uint64_t)block->m_data_type->size + block->m_data_type->alignment + 2) * block->m_num_instances;
	}

	auto out_accessor = this->AllocateSerializeData(alloc_size);

	size_t true_alloc = 0;

	hkreflex::hkIndexedDataBlock* root_block = hkreflex::hkIndexedDataBlock::CreatePointerAndAlloc(this, this->root_level_instance->type, this->root_level_instance);
	
	utils::SerializePool serializer(1);
	serializer.QueueSerialization(root_block, true);
	cur_block_index = serializer.Resolve(out_accessor.make_reference(), true_alloc);
	
	this->indexed_blocks_out.push_back(new hkreflex::hkIndexedDataBlock(this));
	for (auto block : serializer.serialized_objects) {
		this->indexed_blocks_out.push_back(dynamic_cast<hkreflex::hkIndexedDataBlock*>(block));
	}

#ifdef _DEBUG
	auto map1 = utils::count_element<hkreflex::hkIndexedDataBlock*, std::string>(this->indexed_blocks_out, [](hkreflex::hkIndexedDataBlock* block) {
		return block->m_data_type ? block->m_data_type->type_name : "";
		});

	auto map2 = utils::count_element<hkreflex::hkIndexedDataBlock*, std::string>(this->indexed_blocks, [](hkreflex::hkIndexedDataBlock* block) {
		return block->m_data_type ? block->m_data_type->type_name : "";
		});
	_ASSERT(this->indexed_blocks_out.size() == this->indexed_blocks.size());
#endif

	out_accessor.size = true_alloc;

	auto tag0 = dynamic_cast<hkDataChunkTAG0*>(this->data_chunks[ChunkType::TAG0]);

	utils::DataAccessor result;
	auto size = (uint32_t)tag0->DistributeAndSerialize(result, true);

	utils::writeAsHex(data_stream, size);
	utils::writeAsHex(data_stream, size);
	data_stream.write((const char*)result.data, result.size);

	return true;
}

void hkphysics::hkPhysicsReflectionData::ExtractClasses()
{
	auto root_ctn_insts = this->GetInstancesByClassName("hkRootLevelContainer");
	if (root_ctn_insts.size() == 1) {
		this->root_level_container = new hktypes::hkRootLevelContainer();
		root_ctn_insts[0]->GetValue(*this->root_level_container);

		this->skeleton = dynamic_cast<hktypes::hkaSkeleton*>(this->root_level_container->GetNamedVariantRef("hkaSkeleton"));

		if (this->skeleton == nullptr) {
			auto skele_insts = this->GetInstancesByClassName("hkaSkeleton");
			if (skele_insts.size() == 1) {
				this->skeleton = new hktypes::hkaSkeleton();
				skele_insts[0]->GetValue(*this->skeleton);
			}
		}
	}
}

hkphysics::hkDataChunkPTCH* hkphysics::hkPhysicsReflectionData::GetPatchChunk() {
	return dynamic_cast<hkDataChunkPTCH*>(data_chunks[ChunkType::PTCH]);
}

utils::DataAccessor hkphysics::hkPhysicsReflectionData::GetDataPtr(uint32_t offset){
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->GetData() + offset;
}

utils::DataAccessor hkphysics::hkPhysicsReflectionData::AllocateSerializeData(uint32_t size){
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->AllocateSerializeData(size);
}

utils::DataAccessor hkphysics::hkPhysicsReflectionData::GetSerializeDataPtr(uint32_t offset){
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->GetSerializeData() + offset;
}

std::vector<hkreflex::hkClassBase*> hkphysics::hkPhysicsReflectionData::GetClassByName(const std::string& name)
{
	std::vector<hkreflex::hkClassBase*> ret;
	for (auto it = classes.begin() + 1; it != classes.end(); ++it) {
		if ((*it)->type_name == name) {
			ret.push_back(*it);
		}
	}
	return ret;
}

std::string hkphysics::hkPhysicsReflectionData::classes_to_literal(bool show_members, bool use_mapped_ctype, bool inverse_order)
{
	std::string ret = "";
	ret = "#pragma once\n\n";
	ret += "#include \"hkBaseCTypes.h\"\n";

	if (inverse_order) {
		int i = classes.size();
		for (auto it = classes.rbegin(); it != classes.rend() - 1; ++it) {
			ret += "// Class No." + std::to_string(--i) + "\n";
			ret += (*it)->to_literal(show_members, false, use_mapped_ctype);
			ret += "\n\n";
		}
		return ret;
	}
	else {
		int i = 1;
		for (auto it = classes.begin() + 1; it != classes.end(); ++it) {
			ret += "// Class No." + std::to_string(i++) + "\n";
			ret += (*it)->to_literal(show_members, false, use_mapped_ctype);
			ret += "\n\n";
		}
	}
	return ret;
}

std::string hkphysics::hkPhysicsReflectionData::dump_indexed_blocks()
{
	/*for (auto it = indexed_blocks.begin() + 1; it != indexed_blocks.end(); ++it) {
		(*it)->_dumped = false;
	}*/

	std::string ret = "";
	for (auto it = indexed_blocks.begin() + 1; it != indexed_blocks.end(); ++it) {
		if ((*it)->_dumped == false)
			ret += (*it)->dump_instances(0, false, false) + "\n";
	}
	return ret;
}

std::vector<hkreflex::hkClassInstance*> hkphysics::hkPhysicsReflectionData::GetInstancesByClassName(const std::string& name)
{
	std::vector<hkreflex::hkClassInstance*> ret;
	for (auto it = indexed_blocks.begin() + 1; it != indexed_blocks.end(); ++it) {
		if ((*it)->m_data_type->type_name == name) {
			for (auto instance : (*it)->m_instances) {
				ret.push_back(instance);
			}
		}
	}
	return ret;
}

std::string hkphysics::hkPhysicsReflectionData::dump_root_instance()
{
	if (this->root_level_instance == nullptr)
		return "";

	return this->root_level_instance->dump(0);
}
