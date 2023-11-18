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

	return true;
}

bool hkphysics::hkPhysicsReflectionData::Serialize(const std::string filename)
{
	return false;
}
