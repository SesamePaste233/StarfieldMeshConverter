#include "hkPhysics.h"

bool hkphysics::hkPhysicsReflectionData::Deserialize(const std::string filename)
{
	std::ifstream file(filename, std::ios::binary);

	if (!file.is_open())
		return false;

	this->buffer_size = Util::readUInt32(file)[0];

	this->data_size = Util::readUInt32(file)[0];

	hkDataChunkTAG0* chunk = new hkDataChunkTAG0();

	chunk->SetBuffer(Util::readBytes(file, this->data_size), this->data_size);

	chunk->DistributeAndDecode();

	chunk->Traverse([this](hkDataChunkBase* chunk) {
		this->data_chunks.push_back(chunk);
		});

	chunk->ReleaseBuffer();

	return true;
}

bool hkphysics::hkPhysicsReflectionData::Serialize(const std::string filename)
{
	return false;
}
