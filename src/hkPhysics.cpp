#include "hkPhysics.h"

bool hkphysics::hkPhysicsReflectionData::Deserialize(const std::string filename)
{
	std::ifstream file(filename);
	if (!file.is_open()) {
		return false;
	}
	return this->Deserialize(file);
}

bool hkphysics::hkPhysicsReflectionData::Deserialize(std::istream& data_stream)
{
	this->Clear();

	this->data_size = utils::read<uint32_t>(data_stream)[0];

	const uint8_t* _file_buffer = utils::readBytes(data_stream, this->data_size);

	utils::DataAccessor _accessor(_file_buffer, this->data_size);

	hkDataChunkTAG0* chunk = new hkDataChunkTAG0(this);

	chunk->SetBuffer(_accessor);

	size_t cur_pos = 0;
	chunk->chunk_decorator = utils::readFromAccessor<uint16_t>(_accessor, cur_pos, true); // Decorator
	chunk->data_size = utils::readFromAccessor<uint16_t>(_accessor, cur_pos, true); // Data size

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

	for (auto type = this->indexed_blocks.begin() + 1; type != this->indexed_blocks.end(); type++) {
		if ((*type)->_built)
			continue;

		bool success = (*type)->BuildInstances();

		if (!success) {
			return false;
		}
		else {
			continue;
		}
	}

	delete[] _file_buffer;

	return true;
}

bool hkphysics::hkPhysicsReflectionData::Deserialize(const uint8_t* data)
{
	this->Clear();

	size_t cur_pos = 0;

	this->data_size = utils::readFromBuffer<uint32_t>(data, cur_pos);

	const uint8_t* _file_buffer = data + cur_pos;

	hkDataChunkTAG0* chunk = new hkDataChunkTAG0(this);

	chunk->SetBuffer(utils::DataAccessor(_file_buffer, this->data_size));

	chunk->DistributeAndDecode();

	chunk->Traverse([this](hkDataChunkBase* chunk) {
		this->data_chunks[chunk->GetType()] = chunk;
		});

	for (auto type = this->classes.begin() + 1; type != this->classes.end(); type++) {
		(*type)->ctype_name = hktypes::hkTypeMapper::GetSingleton().GetCType((*type));
	}

	for (auto type = this->indexed_blocks.begin() + 1; type != this->indexed_blocks.end(); type++) {
		if ((*type)->_built)
			continue;

		bool success = (*type)->BuildInstances();

		if (!success) {
			return false;
		}
		else {
			continue;
		}
	}

	return true;
}

bool hkphysics::hkPhysicsReflectionData::SerializeWithTypeUnchanged(std::ostream& data_stream)
{
	if (!this->_is_type_unchanged)
		return false;

	auto type_data = this->data_chunks[ChunkType::TYPE]->GetBuffer();
	auto type_size = this->data_chunks[ChunkType::TYPE]->GetBufferSize();
}

utils::DataAccessor hkphysics::hkPhysicsReflectionData::GetDataPtr(uint32_t offset)
{
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->GetData() + offset;
}

utils::DataAccessor hkphysics::hkPhysicsReflectionData::GetSerializeDataPtr(uint32_t offset)
{
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->GetSerializeData() + offset;
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

std::string hkphysics::hkPhysicsReflectionData::dump_instances()
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
