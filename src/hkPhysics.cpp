#include "hkPhysics.h"

bool hkphysics::hkPhysicsReflectionData::Deserialize(const std::string filename)
{
	this->Clear();

	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open())
		return false;

	this->buffer_size = utils::read<uint32_t>(file)[0];

	this->data_size = utils::read<uint32_t>(file)[0];

	hkDataChunkTAG0* chunk = new hkDataChunkTAG0();

	chunk->SetBuffer(utils::readBytes(file, this->data_size), this->data_size);

	chunk->DistributeAndDecode(this);

	chunk->Traverse([this](hkDataChunkBase* chunk) {
		this->data_chunks[chunk->GetType()] = chunk;
		});

	chunk->ReleaseBuffer();

	for (auto type = this->classes.begin() + 1; type != this->classes.end(); type++) {
		(*type)->ctype_name = hktypes::hkTypeMapper::GetSingleton().GetCType((*type));
	}

	for (auto type = this->indexed_blocks.begin() + 1; type != this->indexed_blocks.end(); type++) {
		if(!(*type)->BuildInstances(this))
			return false;
	}

	return true;
}

bool hkphysics::hkPhysicsReflectionData::Serialize(const std::string filename)
{
	return false;
}

const uint8_t* hkphysics::hkPhysicsReflectionData::GetDataPtr(uint32_t offset)
{
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->GetData() + offset;
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
	for (auto it = indexed_blocks.begin() + 1; it != indexed_blocks.end(); ++it) {
		(*it)->_dumped = false;
	}

	std::string ret = "";
	for (auto it = indexed_blocks.begin() + 1; it != indexed_blocks.end(); ++it) {
		if ((*it)->_dumped == false)
			ret += (*it)->dump_instances(this) + "\n";
	}
	return ret;
}
