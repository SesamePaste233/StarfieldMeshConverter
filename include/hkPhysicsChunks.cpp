#include "hkPhysicsChunks.h"

std::string_view hkphysics::GetChunkTypeName(::hkphysics::ChunkType type) {
	switch (type) {
		case ::hkphysics::ChunkType::TAG0:
			return "TAG0";
		case ::hkphysics::ChunkType::SDKV:
			return "SDKV";
		case ::hkphysics::ChunkType::DATA:
			return "DATA";
		case ::hkphysics::ChunkType::TYPE: // static
			return "TYPE";
		case ::hkphysics::ChunkType::TPTR: // static
			return "TPTR";
		case ::hkphysics::ChunkType::TST1: // static
			return "TST1";
		case ::hkphysics::ChunkType::TNA1: // static
			return "TNA1";
		case ::hkphysics::ChunkType::FST1: // static
			return "FST1";
		case ::hkphysics::ChunkType::TBDY: // static
			return "TBDY";
		case ::hkphysics::ChunkType::THSH: // static
			return "THSH";
		case ::hkphysics::ChunkType::TPAD: // static
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

hkphysics::hkDataChunkBase* hkphysics::AllocateChunk(ChunkType type, hkPhysicsReflectionData* ref_data)
{
	switch (type)
	{	
	case hkphysics::ChunkType::TAG0:
		return new hkphysics::hkDataChunkTAG0(ref_data);
		break;
	case hkphysics::ChunkType::SDKV:
		return new hkphysics::hkDataChunkSDKV(ref_data);
		break;
	case hkphysics::ChunkType::DATA:
		return new hkphysics::hkDataChunkDATA(ref_data);
		break;
	case hkphysics::ChunkType::TYPE:
		return new hkphysics::hkDataChunkTYPE(ref_data);
		break;
	case hkphysics::ChunkType::TPTR:
		return new hkphysics::hkDataChunkTPTR(ref_data);
		break;
	case hkphysics::ChunkType::TST1:
		return new hkphysics::hkDataChunkTST1(ref_data);
		break;
	case hkphysics::ChunkType::TNA1:
		return new hkphysics::hkDataChunkTNA1(ref_data);
		break;
	case hkphysics::ChunkType::FST1:
		return new hkphysics::hkDataChunkFST1(ref_data);
		break;
	case hkphysics::ChunkType::TBDY:
		return new hkphysics::hkDataChunkTBDY(ref_data);
		break;
	case hkphysics::ChunkType::THSH:
		return new hkphysics::hkDataChunkTHSH(ref_data);
		break;
	case hkphysics::ChunkType::TPAD:
		return new hkphysics::hkDataChunkTPAD(ref_data);
		break;
	case hkphysics::ChunkType::INDX:
		return new hkphysics::hkDataChunkINDX(ref_data);
		break;
	case hkphysics::ChunkType::ITEM:
		return new hkphysics::hkDataChunkITEM(ref_data);
		break;
	case hkphysics::ChunkType::PTCH:
		return new hkphysics::hkDataChunkPTCH(ref_data);
		break;
	default:
		return nullptr;
		break;
	}
}

bool hkphysics::hkDataChunkTAG0::DistributeAndDecode(uint32_t indent) {
	if (!_accessor.is_valid())
		return false;
	size_t cur_pos = 8;
	while (cur_pos + 8 <= this->data_size) {
		auto child_pos = cur_pos;
		uint16_t child_decorator = utils::readFromAccessor<uint16_t>(_accessor, child_pos, true); // Decorator
		uint16_t child_data_size = utils::readFromAccessor<uint16_t>(_accessor, child_pos, true); // Data size

		std::string child_type_name = utils::readStringFromAccessor(_accessor, child_pos, 4); // Type name

		utils::DataAccessor child_accessor = _accessor + cur_pos;

		hkDataChunkBase* new_chunk = AllocateChunk(ChunkTypeFromName(child_type_name), ref_data);
		if (!new_chunk) {
			std::cout << "Unknown chunk type: " << child_type_name << std::endl;
			return false;
		}
		hkDataChunkTAG0* chunk = dynamic_cast<hkDataChunkTAG0*>(new_chunk);

		chunk->data_size = child_data_size;
		chunk->chunk_decorator = child_decorator;
		chunk->SetName(child_type_name);
		std::cout << std::string(indent * 2, ' ') << "Chunk Type: " << child_type_name << " Chunk Size: " << child_data_size << std::endl;

		chunk->SetBuffer(child_accessor);

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

bool hkphysics::hkDataChunkSDKV::Decode() {
	size_t cur_pos = 8;
	ref_data->sdk_version = utils::readStringFromAccessor(_accessor, cur_pos, this->GetActualDataSize());
	return true;
}

bool hkphysics::hkDataChunkTST1::Decode()
{
	size_t cur_pos = 8;
	std::string type_name;
	while (cur_pos < GetBufferSize())
	{
		unsigned char cur_char = _accessor[cur_pos];
		if (cur_char == 0x00) {
			ref_data->type_names.push_back(type_name);
			//std::cout << type_name << std::endl;
			type_name.clear();
		}
		else if (cur_char == 0xFF) {
			break;
		}
		else {
			type_name.push_back(cur_char);
		}
		cur_pos++;
	}

	return true;
}

bool hkphysics::hkDataChunkFST1::Decode()
{
	size_t cur_pos = 8;
	std::string member_name;
	while (cur_pos < GetBufferSize())
	{
		unsigned char cur_char = _accessor[cur_pos];
		if (cur_char == 0x00) {
			ref_data->field_names.push_back(member_name);
			member_name.clear();
		}
		else if (cur_char == 0xFF) {
			break;
		}
		else {
			member_name.push_back(cur_char);
		}
		cur_pos++;
	}

	return true;
}

bool hkphysics::hkDataChunkTNA1::Decode()
{
	size_t cur_pos = 8;

	auto num_types = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

	if (num_types > 500) {
		num_types = 500;
	}

	for (size_t i = 0; i < num_types; i++) {
		ref_data->classes.push_back(new hkreflex::hkClassBase);
	}

	for (size_t i = 1; i < num_types; i++) {
		auto& hk_class = ref_data->classes[i];
		hk_class->type_name = ref_data->type_names[utils::readHavokVarUIntFromAccessor(_accessor, cur_pos)];

		auto template_arg_number = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

		if (cur_pos >= GetBufferSize()) {
			std::cout << "Error: cur_pos >= GetBufferSize()" << std::endl;
			return false;
		}

		for (size_t j = 0; j < template_arg_number; j++) {
			auto& param_type = ref_data->type_names[utils::readHavokVarUIntFromAccessor(_accessor, cur_pos)];
			auto param_value = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

			/*if (param_value >= 500) {
				std::cout << "Unknown template type: " << param_type << std::endl;
				hkreflex::hkTemplateArgumentUnk* arg = new hkreflex::hkTemplateArgumentUnk;
				arg->template_arg_name = param_type;
				arg->unk = param_value;
				hk_class->template_args.push_back(arg);
				continue;
			}*/

			if (param_type[0] == 'v') {
				hkreflex::hkTemplateArgumentValue* arg = new hkreflex::hkTemplateArgumentValue;
				arg->template_arg_name = param_type;
				arg->value = param_value;
				hk_class->template_args.push_back(arg);
			}
			else if (param_type[0] == 't') {
				if (param_type == "tT" || param_type == "tTYPE") { // Type
					hkreflex::hkTemplateArgumentType* arg = new hkreflex::hkTemplateArgumentType;
					arg->template_arg_name = param_type;
					arg->type = ref_data->classes[param_value];
					hk_class->template_args.push_back(arg);
				}
				else if (param_type == "tFT") { // Float type
					hkreflex::hkTemplateArgumentType* arg = new hkreflex::hkTemplateArgumentType;
					arg->template_arg_name = param_type;
					arg->type = ref_data->classes[param_value];
					hk_class->template_args.push_back(arg);
				}
				else if (param_type == "tAllocator") { // Allocator
					hkreflex::hkTemplateArgumentType* arg = new hkreflex::hkTemplateArgumentType;
					arg->template_arg_name = param_type;
					arg->type = ref_data->classes[param_value];
					hk_class->template_args.push_back(arg);
				}
				else if (param_type == "tENUM") { // Enum type
					hkreflex::hkTemplateArgumentType* arg = new hkreflex::hkTemplateArgumentType;
					arg->template_arg_name = param_type;
					arg->type = ref_data->classes[param_value];
					hk_class->template_args.push_back(arg);
				}
				else if (param_type == "tBITS") { // Bits type
					hkreflex::hkTemplateArgumentType* arg = new hkreflex::hkTemplateArgumentType;
					arg->template_arg_name = param_type;
					arg->type = ref_data->classes[param_value];
					hk_class->template_args.push_back(arg);
				}
				else if (param_type == "tSTORAGE" || param_type == "tStorage") { // Storage type
					hkreflex::hkTemplateArgumentType* arg = new hkreflex::hkTemplateArgumentType;
					arg->template_arg_name = param_type;
					arg->type = ref_data->classes[param_value];
					hk_class->template_args.push_back(arg);
				}
				else {
					std::cout << "Unknown template type: " << param_type << std::endl;
					hkreflex::hkTemplateArgumentUnk* arg = new hkreflex::hkTemplateArgumentUnk;
					arg->template_arg_name = param_type;
					arg->unk = param_value;
					hk_class->template_args.push_back(arg);
				}
			}
		}

		hk_class->_declared = true;
		//std::cout << hk_class->to_literal(false, true) << std::endl;
	}

	return true;
}

bool hkphysics::hkDataChunkTBDY::Decode()
{
	size_t cur_pos = 8;

#ifdef _DEBUG
	std::vector<bool> deserialized_types;
	for (size_t i = 0; i < ref_data->classes.size(); i++) {
		deserialized_types.push_back(false);
	}
#endif

	uint64_t prev_id = 0;

	while (cur_pos < GetBufferSize()) {
		auto cur_type_id = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

		if (cur_type_id == 0) {
			break;
		}

#ifdef _DEBUG
		if (deserialized_types[cur_type_id] == true) {
			std::cout << "Error: Type already deserialized" << std::endl;
			throw std::exception("Type already deserialized");
		}
		deserialized_types[cur_type_id] = true;
#endif

		auto& hk_class = ref_data->classes[cur_type_id];

		auto parent_type_id = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
		if (parent_type_id > 0) {
			hk_class->parent_class = ref_data->classes[parent_type_id];
		}

		hkreflex::Optional optional = (hkreflex::Optional)utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
		hk_class->optionals = optional;
		if (optional & hkreflex::Optional::Format) { // 0b00000001
			hk_class->format = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
			hk_class->kind = (hkreflex::hkClassBase::TypeKind)(hk_class->format & 0x0000000F);
		}
		if (optional & hkreflex::Optional::SubType) { // 0b00000010
			hk_class->sub_type = ref_data->classes[utils::readHavokVarUIntFromAccessor(_accessor, cur_pos)];
		}
		if (optional & hkreflex::Optional::Version) { // 0b00000100
			hk_class->version = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
		}
		if (optional & hkreflex::Optional::SizeAlign) { // 0b00001000
			hk_class->size = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
			hk_class->alignment = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
		}
		if (optional & hkreflex::Optional::Flags) { // 0b00010000
			hk_class->type_flags = (hkreflex::TypeFlags)utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
		}
		if (optional & hkreflex::Optional::Members) { // 0b00100000
			uint8_t num_members = (uint8_t)utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

			uint8_t num_fields = num_members & 0x0000FFFF;
			uint8_t num_properties = num_members & 0xFFFF0000;

			hk_class->fields.clear();

			for (int i = 0; i < num_fields; i++) {
				hkreflex::hkFieldBase* field = new hkreflex::hkFieldBase;
				field->name = ref_data->field_names[utils::readHavokVarUIntFromAccessor(_accessor, cur_pos)];
				field->flags = (hkreflex::hkFieldBase::FieldFlags)utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
				
				if (field->flags & hkreflex::hkFieldBase::FieldFlags::AdditionalUnkValue) {
					field->unk_value = (uint8_t)utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
				}

				field->offset = (uint32_t)utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);
				field->type = ref_data->classes[utils::readHavokVarUIntFromAccessor(_accessor, cur_pos)];

				hk_class->fields.push_back(field);
			}
		}
		if (optional & hkreflex::Optional::Interfaces) { // 0b01000000
			auto num_interfaces = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

			for (int i = 0; i < num_interfaces; i++) {
				hkreflex::hkInterfaceBase* interface = new hkreflex::hkInterfaceBase;
				interface->type = ref_data->classes[utils::readHavokVarUIntFromAccessor(_accessor, cur_pos)];
				interface->offset = (uint32_t)utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

				hk_class->interfaces.push_back(interface);
			}
		}
		if (optional & hkreflex::Optional::Attributes) { // 0b10000000
			throw std::exception("Not implemented");
		}

		prev_id = cur_type_id;
		hk_class->_defined = true;
	}

	return true;
}

bool hkphysics::hkDataChunkTHSH::Decode()
{
	size_t cur_pos = 8;

	auto num_hashes = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

	for (int i = 0; i < num_hashes; i++) {
		auto type_id = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

		if (type_id >= ref_data->classes.size()) {
			std::cout << "Error: type_id >= data->classes.size()" << std::endl;
			return false;
		}

		auto& hk_class = ref_data->classes[type_id];

		auto hash = utils::readFromAccessor<uint32_t>(_accessor, cur_pos);

		hk_class->hash = hash;
	}

	return true;
}

bool hkphysics::hkDataChunkITEM::Decode()
{
	size_t cur_pos = 8;

	while (cur_pos < this->GetBufferSize()) {
		uint32_t type_id_and_flag = utils::readFromAccessor<uint32_t>(_accessor, cur_pos);

		uint32_t type_id = type_id_and_flag & 0x00FFFFFF;

		hkreflex::hkIndexedDataBlock::Type block_type = (hkreflex::hkIndexedDataBlock::Type)(type_id_and_flag >> 28);

		if (type_id != 0 && block_type > 2) {
			std::cout << "Error: type_id != 0 && block_type > 2" << std::endl;
			return false;
		}

		hkreflex::hkIndexedDataBlock* block = new hkreflex::hkIndexedDataBlock(ref_data);

		block->m_data_type = ref_data->classes[type_id];
		block->m_block_type = block_type;
		block->m_offset = utils::readFromAccessor<uint32_t>(_accessor, cur_pos);
		block->m_num_instances = utils::readFromAccessor<uint32_t>(_accessor, cur_pos);

		ref_data->indexed_blocks.push_back(block);
		this->indexed_blocks.push_back(block); // No ownership
	}

	return false;
}

bool hkphysics::hkDataChunkITEM::Serialize(uint8_t*& out, bool use_cached)
{
	if (hkphysics::hkDataChunkBase::Serialize(out, use_cached))
		return true;

	size_t cur_pos = 8;
	uint64_t cur_block_index = 0;
	for (auto block : this->indexed_blocks) {
		auto block_type = (uint32_t)block->m_block_type;
		auto type_id = (uint32_t)std::distance(ref_data->classes.begin(), std::find(ref_data->classes.begin(), ref_data->classes.end(), block->m_data_type));

		uint32_t type_id_and_flag = (block_type << 28) | (type_id & 0x00FFFFFF);

		utils::writeToBuffer(out, cur_pos, type_id_and_flag);

		utils::SerializePool serializer(cur_block_index);
		auto out_ptr = ref_data->GetSerializeDataPtr();

		block->Serialize(out_ptr, serializer);
	}

	return true;
}

bool hkphysics::hkDataChunkTYPE::Serialize(uint8_t*& out, bool use_cached)
{
	if (hkphysics::hkDataChunkBase::Serialize(out, use_cached))
		return true;

	throw std::exception("Not implemented");
	return true;
}

