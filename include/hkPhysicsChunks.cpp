#include "hkPhysicsChunks.h"

std::string_view hkphysics::GetChunkTypeName(::hkphysics::ChunkType type) {
	switch (type) {
		case ::hkphysics::ChunkType::TAG0:
			return "TAG0";
		case ::hkphysics::ChunkType::SDKV:
			return "SDKV";
		case ::hkphysics::ChunkType::DATA:
			return "DATA";
		case ::hkphysics::ChunkType::TYPE:
			return "TYPE";
		case ::hkphysics::ChunkType::TPTR:
			return "TPTR";
		case ::hkphysics::ChunkType::TST1:
			return "TST1";
		case ::hkphysics::ChunkType::TNA1:
			return "TNA1";
		case ::hkphysics::ChunkType::FST1:
			return "FST1";
		case ::hkphysics::ChunkType::TBDY:
			return "TBDY";
		case ::hkphysics::ChunkType::THSH:
			return "THSH";
		case ::hkphysics::ChunkType::TPAD:
			return "TPAD";
		case ::hkphysics::ChunkType::INDX:
			return "INDX";
		case ::hkphysics::ChunkType::ITEM:
			return "ITEM";
		case ::hkphysics::ChunkType::PTCH:
			return "PTCH";
		default:
			return "Unknown";
	}
}

hkphysics::ChunkType hkphysics::ChunkTypeFromName(const std::string name)
{
	if (name == "TAG0")
		return hkphysics::ChunkType::TAG0;
	else if (name == "SDKV")
		return hkphysics::ChunkType::SDKV;
	else if (name == "DATA")
		return hkphysics::ChunkType::DATA;
	else if (name == "TYPE")
		return hkphysics::ChunkType::TYPE;
	else if (name == "TPTR")
		return hkphysics::ChunkType::TPTR;
	else if (name == "TST1")
		return hkphysics::ChunkType::TST1;
	else if (name == "TNA1")
		return hkphysics::ChunkType::TNA1;
	else if (name == "FST1")
		return hkphysics::ChunkType::FST1;
	else if (name == "TBDY")
		return hkphysics::ChunkType::TBDY;
	else if (name == "THSH")
		return hkphysics::ChunkType::THSH;
	else if (name == "TPAD")
		return hkphysics::ChunkType::TPAD;
	else if (name == "INDX")
		return hkphysics::ChunkType::INDX;
	else if (name == "ITEM")
		return hkphysics::ChunkType::ITEM;
	else if (name == "PTCH")
		return hkphysics::ChunkType::PTCH;
	else
		return hkphysics::ChunkType::Unknown;
}

hkphysics::hkDataChunkBase* hkphysics::AllocateChunk(ChunkType type)
{
	switch (type)
	{	
	case hkphysics::ChunkType::TAG0:
		return new hkphysics::hkDataChunkTAG0();
		break;
	case hkphysics::ChunkType::SDKV:
		return new hkphysics::hkDataChunkSDKV();
		break;
	case hkphysics::ChunkType::DATA:
		return new hkphysics::hkDataChunkDATA();
		break;
	case hkphysics::ChunkType::TYPE:
		return new hkphysics::hkDataChunkTYPE();
		break;
	case hkphysics::ChunkType::TPTR:
		return new hkphysics::hkDataChunkTPTR();
		break;
	case hkphysics::ChunkType::TST1:
		return new hkphysics::hkDataChunkTST1();
		break;
	case hkphysics::ChunkType::TNA1:
		return new hkphysics::hkDataChunkTNA1();
		break;
	case hkphysics::ChunkType::FST1:
		return new hkphysics::hkDataChunkFST1();
		break;
	case hkphysics::ChunkType::TBDY:
		return new hkphysics::hkDataChunkTBDY();
		break;
	case hkphysics::ChunkType::THSH:
		return new hkphysics::hkDataChunkTHSH();
		break;
	case hkphysics::ChunkType::TPAD:
		return new hkphysics::hkDataChunkTPAD();
		break;
	case hkphysics::ChunkType::INDX:
		return new hkphysics::hkDataChunkINDX();
		break;
	case hkphysics::ChunkType::ITEM:
		return new hkphysics::hkDataChunkITEM();
		break;
	case hkphysics::ChunkType::PTCH:
		return new hkphysics::hkDataChunkPTCH();
		break;
	default:
		return nullptr;
		break;
	}
}

bool hkphysics::hkDataChunkTAG0::DistributeAndDecode(uint32_t indent) {
	if (!_buffer)
		return false;
	size_t cur_pos = 0;
	this->chunk_decorator = Util::readFromBuffer<uint16_t>(_buffer, cur_pos, true); // Decorator
	this->data_size = Util::readFromBuffer<uint16_t>(_buffer, cur_pos, true); // Data size

	std::string type_name = Util::readStringFromBuffer(_buffer, cur_pos, 4); // Type name
	std::memcpy(this->type_name, type_name.c_str(), 4);

	while (cur_pos + 8 <= this->data_size) {
		auto child_pos = cur_pos;
		uint16_t child_decorator = Util::readFromBuffer<uint16_t>(_buffer, child_pos, true); // Decorator
		uint16_t child_data_size = Util::readFromBuffer<uint16_t>(_buffer, child_pos, true); // Data size

		std::string child_type_name = Util::readStringFromBuffer(_buffer, child_pos, 4); // Type name

		const uint8_t* child_buffer = _buffer + cur_pos;

		hkDataChunkBase* new_chunk = AllocateChunk(ChunkTypeFromName(child_type_name));
		if (!new_chunk) {
			std::cout << "Unknown chunk type: " << child_type_name << std::endl;
			return false;
		}
		hkDataChunkTAG0* chunk = dynamic_cast<hkDataChunkTAG0*>(new_chunk);

		chunk->data_size = child_data_size;
		chunk->chunk_decorator = child_decorator;
		std::memcpy(chunk->type_name, child_type_name.c_str(), 4);
		std::cout << std::string(indent * 2, ' ') << "Chunk Type: " << child_type_name << " Chunk Size: " << child_data_size << std::endl;

		chunk->SetBuffer((uint8_t*)child_buffer, child_data_size);

		if (child_decorator & chunk->_leaf_decorator) {
			chunk->Decode();
		}
		else {
			chunk->DistributeAndDecode(indent + 1);
		}

		this->children.push_back(chunk);

		cur_pos += child_data_size;
	}

	return true;
}
