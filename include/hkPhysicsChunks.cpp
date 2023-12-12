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
		uint32_t sizeAndFlags = utils::readFromAccessor<uint32_t>(_accessor, child_pos, true); // Size and flags
		uint8_t child_decorator = sizeAndFlags >> 24;// Decorator
		uint32_t child_data_size = sizeAndFlags & 0x00FFFFFF;// Data size

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

uint64_t hkphysics::hkDataChunkTAG0::DistributeAndSerialize(utils::DataAccessor& out, bool use_cached)
{
	// SDKV
	utils::DataAccessor sdkv_header = utils::DataAccessor::Alloc(8);
	utils::DataAccessor sdkv_data;
	auto sdkv_chunk = ref_data->data_chunks[ChunkType::SDKV];
	sdkv_chunk->Serialize(sdkv_data, use_cached);
	uint32_t sdkv_size = sdkv_data.size + 8;
	uint32_t sdkv_sizeAndFlags = ((uint32_t)sdkv_chunk->chunk_decorator << 24) | ((uint32_t)(sdkv_size) & 0x00FFFFFF);
	size_t cur_pos = 0;
	utils::writeToAccessor(sdkv_header, cur_pos, sdkv_sizeAndFlags, true);
	utils::writeStringToAccessor(sdkv_header, cur_pos, std::string(sdkv_chunk->type_name));
	auto sdkv = sdkv_header.Weld(sdkv_data);

	// DATA
	utils::DataAccessor data_header = utils::DataAccessor::Alloc(8);
	utils::DataAccessor data_data;
	auto data_chunk = ref_data->data_chunks[ChunkType::DATA];
	data_chunk->Serialize(data_data, use_cached);
	uint32_t data_size = data_data.size + 8;
	uint32_t data_sizeAndFlags = ((uint32_t)data_chunk->chunk_decorator << 24) | ((uint32_t)(data_size) & 0x00FFFFFF);
	cur_pos = 0;
	utils::writeToAccessor(data_header, cur_pos, data_sizeAndFlags, true);
	utils::writeStringToAccessor(data_header, cur_pos, std::string(data_chunk->type_name));
	auto data = data_header.Weld(data_data);

	// TYPE
	utils::DataAccessor type_header = utils::DataAccessor::Alloc(8);
	utils::DataAccessor type_data;
	auto type_chunk = ref_data->data_chunks[ChunkType::TYPE];
	type_chunk->Serialize(type_data, use_cached);
	uint32_t type_size = type_data.size + 8;
	uint32_t type_sizeAndFlags = ((uint32_t)type_chunk->chunk_decorator << 24) | ((uint32_t)(type_size) & 0x00FFFFFF);
	cur_pos = 0;
	utils::writeToAccessor(type_header, cur_pos, type_sizeAndFlags, true);
	utils::writeStringToAccessor(type_header, cur_pos, std::string(type_chunk->type_name));
	auto type = type_header.Weld(type_data);

	// ITEM
	utils::DataAccessor item_header = utils::DataAccessor::Alloc(8);
	utils::DataAccessor item_data;
	auto item_chunk = ref_data->data_chunks[ChunkType::ITEM];
	item_chunk->Serialize(item_data, use_cached);
	uint32_t item_size = item_data.size + 8;
	uint32_t item_sizeAndFlags = ((uint32_t)item_chunk->chunk_decorator << 24) | ((uint32_t)(item_size) & 0x00FFFFFF);
	cur_pos = 0;
	utils::writeToAccessor(item_header, cur_pos, item_sizeAndFlags, true);
	utils::writeStringToAccessor(item_header, cur_pos, std::string(item_chunk->type_name));
	auto item = item_header.Weld(item_data);

	// PTCH
	utils::DataAccessor ptch_header = utils::DataAccessor::Alloc(8);
	utils::DataAccessor ptch_data;
	auto ptch_chunk = ref_data->data_chunks[ChunkType::PTCH];
	ptch_chunk->Serialize(ptch_data, use_cached);
	uint32_t ptch_size = ptch_data.size + 8;
	uint32_t ptch_sizeAndFlags = ((uint32_t)ptch_chunk->chunk_decorator << 24) | ((uint32_t)(ptch_size) & 0x00FFFFFF);
	cur_pos = 0;
	utils::writeToAccessor(ptch_header, cur_pos, ptch_sizeAndFlags, true);
	utils::writeStringToAccessor(ptch_header, cur_pos, std::string(ptch_chunk->type_name));
	auto ptch = ptch_header.Weld(ptch_data);

	// INDX
	utils::DataAccessor indx_header = utils::DataAccessor::Alloc(8);
	auto indx_chunk = ref_data->data_chunks[ChunkType::INDX];
	uint32_t indx_size = item_size + ptch_size + 8;
	uint32_t indx_sizeAndFlags = ((uint32_t)indx_chunk->chunk_decorator << 24) | ((uint32_t)(indx_size) & 0x00FFFFFF);
	cur_pos = 0;
	utils::writeToAccessor(indx_header, cur_pos, indx_sizeAndFlags, true);
	utils::writeStringToAccessor(indx_header, cur_pos, std::string(indx_chunk->type_name));
	auto indx = utils::DataAccessor::WeldAll({ indx_header, item, ptch });

	// TAG0
	utils::DataAccessor tag0_header = utils::DataAccessor::Alloc(8);
	uint32_t tag0_size = sdkv_size + data_size + type_size + indx_size + 8;
	uint32_t tag0_sizeAndFlags = ((uint32_t)this->chunk_decorator << 24) | ((uint32_t)(tag0_size) & 0x00FFFFFF);
	cur_pos = 0;
	utils::writeToAccessor(tag0_header, cur_pos, tag0_sizeAndFlags, true);
	utils::writeStringToAccessor(tag0_header, cur_pos, std::string(this->type_name));
	auto tag0 = utils::DataAccessor::WeldAll({ tag0_header, sdkv, data, type, indx });

	out = tag0;
	return uint64_t(tag0_size);
}

bool hkphysics::hkDataChunkSDKV::Decode() {
	size_t cur_pos = 8;
	ref_data->sdk_version = utils::readStringFromAccessor(_accessor, cur_pos, this->GetActualDataSize());
	return true;
}

uint64_t hkphysics::hkDataChunkSDKV::Serialize(utils::DataAccessor& out, bool use_cached)
{
	utils::DataAccessor out_accessor = utils::DataAccessor::Alloc(ref_data->sdk_version.size());
	size_t cur_pos = 0;
	if (utils::writeStringToAccessor(out_accessor, cur_pos, ref_data->sdk_version)) {
		out = out_accessor;
		return ref_data->sdk_version.size();
	}

	out_accessor.Destroy();
	return false;
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

		auto p = hk_class->type_name.find_last_of("::");
		if (p != std::string::npos) {
			hk_class->nested_type_name = hk_class->type_name.substr(p + 1);
			hk_class->nested_parent_type_name = hk_class->type_name.substr(0, p - 1);
			hk_class->is_nested_class = true;
		}
		else {
			hk_class->nested_type_name = hk_class->type_name;
			hk_class->nested_parent_type_name = "";
			hk_class->is_nested_class = false;
		}

		auto template_arg_number = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

		if (cur_pos >= GetBufferSize()) {
			std::cout << "Error: cur_pos >= GetBufferSize()" << std::endl;
			return false;
		}

		for (size_t j = 0; j < template_arg_number; j++) {
			auto& param_type = ref_data->type_names[utils::readHavokVarUIntFromAccessor(_accessor, cur_pos)];
			auto param_value = utils::readHavokVarUIntFromAccessor(_accessor, cur_pos);

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
				else if (param_type == "tNODE") {
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

	for (auto hk_class = ref_data->classes.begin() + 1; hk_class != ref_data->classes.end(); hk_class++) {
		for (auto hk_class2 = hk_class + 1; hk_class2 != ref_data->classes.end(); hk_class2++) {
			if ((*hk_class2)->type_name == (*hk_class)->nested_parent_type_name) {
				(*hk_class)->parent_nested_class = *hk_class2;
				(*hk_class2)->nested_classes.push_back(*hk_class);
			}
			else if ((*hk_class)->type_name == (*hk_class2)->nested_parent_type_name) {
				(*hk_class2)->parent_nested_class = *hk_class;
				(*hk_class)->nested_classes.push_back(*hk_class2);
			}
		}
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

		// Not always true
		/*_ASSERT((block_type == hkreflex::hkIndexedDataBlock::Type::Pointer && block->m_num_instances == 1) 
			|| (block_type == hkreflex::hkIndexedDataBlock::Type::Array && block->m_num_instances > 1)
			|| (block_type == hkreflex::hkIndexedDataBlock::Type::None && block->m_num_instances == 0)
		);*/

		ref_data->indexed_blocks.push_back(block);
		this->indexed_blocks.push_back(block); // No ownership
	}

	return true;
}

uint64_t hkphysics::hkDataChunkITEM::Serialize(utils::DataAccessor& out, bool use_cached)
{
	this->indexed_blocks = ref_data->indexed_blocks_out;
	auto rtn = hkphysics::hkDataChunkBase::Serialize(out, use_cached);
	if (rtn) {
		return rtn;
	}
	size_t size = 0;
	for (auto block : this->indexed_blocks) {
		size += 12;
	}
	utils::DataAccessor out_accessor = utils::DataAccessor::Alloc(size);

	size_t cur_pos = 0;
	uint64_t cur_block_index = 0;
	for (auto block : this->indexed_blocks) {
		auto block_type = (uint32_t)block->m_block_type;

		if (block_type == 0) {
			uint32_t empty = 0;
			utils::writeToAccessor(out_accessor, cur_pos, empty);
			utils::writeToAccessor(out_accessor, cur_pos, empty);
			utils::writeToAccessor(out_accessor, cur_pos, empty);
			continue;
		}

		auto type_id = (uint32_t)std::distance(ref_data->classes.begin(), std::find(ref_data->classes.begin(), ref_data->classes.end(), block->m_data_type));

		uint32_t type_id_and_flag = (block_type << 28) | (type_id & 0x00FFFFFF);

		utils::writeToAccessor(out_accessor, cur_pos, type_id_and_flag);
		utils::writeToAccessor(out_accessor, cur_pos, block->m_offset);
		utils::writeToAccessor(out_accessor, cur_pos, block->m_num_instances);
	}

	out = out_accessor;
	return cur_pos;
}

uint64_t hkphysics::hkDataChunkTYPE::Serialize(utils::DataAccessor& out, bool use_cached)
{
	auto rtn = hkphysics::hkDataChunkBase::Serialize(out, use_cached);
	if (rtn) {
		return rtn;
	}

	throw std::exception("Not implemented");
}

uint64_t hkphysics::hkDataChunkDATA::Serialize(utils::DataAccessor& out, bool use_cached)
{
	auto rtn = hkphysics::hkDataChunkBase::Serialize(out, use_cached);
	if (rtn) {
		return rtn;
	}

	if (_data_out_accessor.is_valid()) {
		out = _data_out_accessor;
		return _data_out_accessor.size;
	}

	throw std::exception("Not implemented");
}

bool hkphysics::hkDataChunkPTCH::RegisterPatch(hkreflex::hkClassBase* type, uint32_t patch_offset)
{
	for (auto& patch : this->patches) {
		if (patch.type == type) {
			patch.patch_offsets.push_back(patch_offset);
			return true;
		}
	}

	Patch patch;
	patch.type = type;
	patch.patch_offsets.push_back(patch_offset);
	this->patches.push_back(patch);
	return true;
}

bool hkphysics::hkDataChunkPTCH::Decode()
{
	size_t cur_pos = 8;

	while (cur_pos < this->data_size) {
		int32_t type_id = utils::readFromAccessor<int32_t>(_accessor, cur_pos);

		if (type_id < 0 || type_id >= ref_data->classes.size()) {
			std::cout << "Error: type_id < 0 || type_id >= ref_data->classes.size()" << std::endl;
			return false;
		}

		Patch patch;

		patch.type = ref_data->classes[type_id];

		auto num_patches = utils::readFromAccessor<int32_t>(_accessor, cur_pos);

		for (int i = 0; i < num_patches; i++) {
			patch.patch_offsets.push_back(utils::readFromAccessor<uint32_t>(_accessor, cur_pos));
		}

		this->patches.push_back(patch);
	}

	return true;
}

uint64_t hkphysics::hkDataChunkPTCH::Serialize(utils::DataAccessor& out, bool use_cached)
{
	auto rtn = hkphysics::hkDataChunkBase::Serialize(out, use_cached);
	if (rtn) {
		return rtn;
	}

	size_t size = 0;
	for (auto& patch : this->patches) {
		size += 8 + patch.patch_offsets.size() * 4;
	}
	utils::DataAccessor out_accessor = utils::DataAccessor::Alloc(size);

	size_t cur_pos = 0;

	for (auto& patch : this->patches) {
		auto type_id = (int32_t)std::distance(ref_data->classes.begin(), std::find(ref_data->classes.begin(), ref_data->classes.end(), patch.type));

		utils::writeToAccessor(out_accessor, cur_pos, type_id);
		utils::writeToAccessor(out_accessor, cur_pos, (int32_t)patch.patch_offsets.size());

		for (auto& patch_offset : patch.patch_offsets) {
			utils::writeToAccessor(out_accessor, cur_pos, patch_offset);
		}
	}

	out = out_accessor;

	return cur_pos;
}
