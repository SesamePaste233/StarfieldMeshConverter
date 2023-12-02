#include "hkReflection.h"

std::string hkreflex::hkClassBase::to_literal(bool show_class_members, bool as_plain_class, bool use_mapped_ctype)
{
	if (!_declared) {
		return "// [Undeclared]";
	}

	std::string type_literal = "";

	if (use_mapped_ctype && hktypes::hkTypeMapper::GetSingleton().IsMapped(this)) {
		return "// Original: " + this->to_literal(false, true) + " Mapped to c type : " + this->ctype_name + "\n";
	}

	if (as_plain_class) {
		type_literal = type_name;
		if (template_args.size() != 0) {
			type_literal += "<" + template_args[0]->to_literal(true);
			for (int i = 1; i < template_args.size(); ++i) {
				type_literal += ", " + template_args[i]->to_literal(true);
			}
			type_literal += ">";
		}
		return type_literal;
	}

	type_literal += "// Mapped to c type: " + this->ctype_name + "\n";

	if (template_args.size() != 0) {
		type_literal += "template<";
		type_literal += template_args[0]->to_literal(false);
		for (int i = 1; i < template_args.size(); ++i) {
			type_literal += ", " + template_args[i]->to_literal(false);
		}
		type_literal += ">\n";
	}

	type_literal += "class " + type_name;

	if (parent_class) {
		type_literal += " : public " + parent_class->to_literal(false, true);
	}

	if (show_class_members) {
		if (!_defined) {
			type_literal += ";\t// [Undefined]";
		}
		else {
			type_literal += " {\n";
			for (auto& member : fields) {
				type_literal += "\t" + member->to_literal(use_mapped_ctype) + "\n";
			}
			type_literal += "};";
		}
	}

	return type_literal;
}

bool hkreflex::hkIndexedDataBlock::BuildInstances()
{
	//return true;
	if (_built) {
		return true;
	}

	auto data_ptr = ref_data->GetDataPtr() + this->m_offset;

#ifdef _DEBUG
	data_ptr.mark_read(0);
#endif

	for (int i = 0; i < this->m_num_instances; ++i) {
		auto instance = AllocateInstance(this->m_data_type, ref_data);
		if (!instance) {
			return false;
		}

		auto size = instance->Build(data_ptr);
		if (size == 0) {
			return false;
		}

		m_instances.push_back(instance);

		data_ptr += size;
		//_ASSERT(size == this->m_data_type->size);
		//_ASSERT(instance->type == this->m_data_type);
	}
	_built = true;
	return true;
}

std::string hkreflex::hkIndexedDataBlock::dump_instances(int indent, bool use_mapped_ctype, bool suppress_comment)
{
	if (_dumped) 
		return "";
	else 
		_dumped = true;
	
	std::string indent_str = "";
	for (int i = 0; i < indent; ++i) {
		indent_str += "\t";
	}

	std::string ret = "";

	if (!suppress_comment)
		ret += "// " + this->m_data_type->type_name + "[" + std::to_string(this->m_num_instances) + "]\n";

	for (auto& instance : m_instances) {
		ret += indent_str + instance->dump(indent) + ";\n";
	}
	return ret;
}

uint64_t hkreflex::hkIndexedDataBlock::Serialize(utils::DataAccessor data, utils::SerializePool& serializer)
{
	auto offset = data - ref_data->GetSerializeDataPtr();
	auto alignment = this->m_data_type->alignment;

	if (this->m_data_type->ctype_name == "std::string") {
		alignment = 2;
	}

	if (alignment == 0) {
		alignment = 2;
	}
	
	size_t cur_pos = 0;

	if (offset % alignment != 0) {
		uint8_t pad = 0;
		auto padding = alignment - offset % alignment;
		for (int i = 0; i < padding; ++i) {
			utils::writeToAccessor(data, cur_pos, pad);
		}
		offset += padding;
	}

	this->m_offset = offset;
	this->m_num_instances = m_instances.size();

	for (auto& instance : m_instances) {
		cur_pos += instance->Serialize(data + cur_pos, serializer);
	}
	return cur_pos;
}

hkreflex::hkIndexedDataBlock* hkreflex::hkIndexedDataBlock::CreateArrayAndAlloc(hkphysics::hkPhysicsReflectionData* ref_data, hkClassBase* type, std::vector<hkClassInstance*> instances)
{
	hkIndexedDataBlock* block = new hkIndexedDataBlock(ref_data);
	block->m_block_type = hkIndexedDataBlock::Type::Array;
	block->m_data_type = type;
	block->m_num_instances = instances.size();
	block->m_instances = instances;
	return block;
}

hkreflex::hkIndexedDataBlock* hkreflex::hkIndexedDataBlock::CreatePointerAndAlloc(hkphysics::hkPhysicsReflectionData* ref_data, hkClassBase* type, hkClassInstance* instances)
{
	hkIndexedDataBlock* block = new hkIndexedDataBlock(ref_data);
	block->m_block_type = hkIndexedDataBlock::Type::Pointer;
	block->m_data_type = type;
	block->m_num_instances = 1;
	block->m_instances.push_back(instances);
	return block;
}

std::string hkreflex::hkFieldBase::to_literal(bool use_mapped_ctype)
{
	if (use_mapped_ctype) {
		return type->ctype_name + " " + name + ";\t// Offset: " + std::to_string(this->offset) + " Unk: " + std::to_string(this->unk_value);
	}
	return type->to_literal(false, true) + " " + name + ";\t// Offset: " + std::to_string(this->offset) + " Unk: " + std::to_string(this->unk_value);
}

hkreflex::hkClassInstance* hkreflex::AllocateInstance(hkreflex::hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data)
{
	auto kind = type->kind;
	if (kind == hkClassBase::TypeKind::Inherited) {
		_ASSERT(type->parent_class != nullptr);
		type = type->parent_class;
		kind = type->kind;
		if (kind == hkClassBase::TypeKind::Inherited) {
			_ASSERT(type->parent_class != nullptr);
			type = type->parent_class;
			kind = type->kind;
		}
	}

	switch (kind) {
	case hkClassBase::TypeKind::Array:
		return new hkClassArrayInstance(type, ref_data);
	case hkClassBase::TypeKind::Bool:
		return new hkClassBoolInstance(type, ref_data);
	case hkClassBase::TypeKind::Float:
		return new hkClassFloatInstance(type, ref_data);
	case hkClassBase::TypeKind::Int:
		return new hkClassIntInstance(type, ref_data);
	case hkClassBase::TypeKind::Pointer:
		return new hkClassPointerInstance(type, ref_data);
	case hkClassBase::TypeKind::Record:
		return new hkClassRecordInstance(type, ref_data);
	case hkClassBase::TypeKind::String:
		return new hkClassStringInstance(type, ref_data);
	default:
		std::cout << "Unknown type kind: " << (int)type->kind << std::endl;
		return nullptr;
	}
}

size_t hkreflex::hkClassStringInstance::Build(utils::DataAccessor& data)
{
	size_t cur_pos = 0;
	if (this->type->format & 0x10) {
		value = utils::readStringFromAccessor(data, cur_pos, this->type->format >> 16);

		std::cout << std::hex << data - ref_data->GetDataPtr() << std::endl;
		return cur_pos;
	}
	else {
		uint64_t ptr = utils::readFromAccessor<uint64_t>(data, cur_pos);
		value = "";
		if (ptr) {
			this->data_block = ref_data->indexed_blocks[ptr];
			this->data_block->BuildInstances();
			for (auto instance : this->data_block->m_instances) {
				auto int_instance = dynamic_cast<hkClassIntInstance*>(instance);
				_ASSERT(int_instance && int_instance->type->size == 1);
				value += (char)int_instance->value;
			}
			this->data_block->_dumped = true;
			value.pop_back();
		}
	}
	return cur_pos;
}

std::string hkreflex::hkClassStringInstance::dump(int indent)
{
	return "\"" + value + "\"";
}

uint64_t hkreflex::hkClassStringInstance::Serialize(utils::DataAccessor data, utils::SerializePool& serializer)
{
	size_t cur_pos = 0;
	if (this->type->format & 0x10) {
		_ASSERT(value.size() == (this->type->format >> 16));
		utils::writeStringToAccessor(data, cur_pos, value);
	}
	else {
		if (!value.empty()) {
			auto rtn = ref_data->serialize_string_table.find(value);
			if (rtn != ref_data->serialize_string_table.end()) {
				ref_data->GetPatchChunk()->RegisterPatch(this->type, data - ref_data->GetSerializeDataPtr() + cur_pos);
				utils::writeToAccessor(data, cur_pos, (*rtn).second);
			}
			else {
				ref_data->GetPatchChunk()->RegisterPatch(this->type, data - ref_data->GetSerializeDataPtr() + cur_pos);

				auto char_classes = ref_data->GetClassByName("char");

				_ASSERT(char_classes.size() == 1);
				_ASSERT(this->data_block->m_num_instances == value.size() + 1);

				auto char_class = char_classes[0];

				hkIndexedDataBlock* block = new hkIndexedDataBlock(ref_data);
				block->m_block_type = hkIndexedDataBlock::Type::Array;
				block->m_data_type = char_class;
				block->m_num_instances = value.size() + 1;

				for (auto c : value) {
					hkClassIntInstance* instance = new hkClassIntInstance(char_class, ref_data);
					instance->value = c;
					block->m_instances.push_back(instance);
				}
				hkClassIntInstance* end = new hkClassIntInstance(char_class, ref_data);
				end->value = 0x00;
				block->m_instances.push_back(end);

				auto ptr = serializer.QueueSerialization(block, true);
				utils::writeToAccessor(data, cur_pos, ptr);
				ref_data->serialize_string_table[value] = ptr;
			}
			/*ref_data->GetPatchChunk()->RegisterPatch(this->type, data - ref_data->GetSerializeDataPtr() + cur_pos);

			auto char_classes = ref_data->GetClassByName("char");

			_ASSERT(char_classes.size() == 1);
			_ASSERT(this->data_block->m_num_instances == value.size() + 1);

			auto char_class = char_classes[0];

			hkIndexedDataBlock* block = new hkIndexedDataBlock(ref_data);
			block->m_block_type = hkIndexedDataBlock::Type::Array;
			block->m_data_type = char_class;
			block->m_num_instances = value.size() + 1;

			for (auto c : value) {
				hkClassIntInstance* instance = new hkClassIntInstance(char_class, ref_data);
				instance->value = c;
				block->m_instances.push_back(instance);
			}
			hkClassIntInstance* end = new hkClassIntInstance(char_class, ref_data);
			end->value = 0x00;
			block->m_instances.push_back(end);


			utils::writeToAccessor(data, cur_pos, serializer.QueueSerialization(block, true));*/
		}
		else {
			utils::writeToAccessor(data, cur_pos, uint64_t(0));
		}
	}
	return cur_pos;
}

size_t hkreflex::hkClassBoolInstance::Build(utils::DataAccessor& data)
{
	size_t cur_pos = 0;

	auto format = type->format;
	bool is_big_endian = (format & 0x100);
	size_t size = type->size;
	size_t bit_length = format >> 10;

	if (size == 1) {
		value = utils::readFromAccessor<uint8_t>(data, cur_pos, is_big_endian);
	}
	else if (size == 4) {
		value = utils::readFromAccessor<uint32_t>(data, cur_pos, is_big_endian);
	}
	else {
		throw std::exception(("Unknown bool size at offset: " + std::to_string(data - ref_data->GetDataPtr())).c_str());
	}

	return cur_pos;
}

std::string hkreflex::hkClassBoolInstance::dump(int indent)
{
	return value ? "true" : "false";
}

uint64_t hkreflex::hkClassBoolInstance::Serialize(utils::DataAccessor data, utils::SerializePool& serializer)
{
	size_t cur_pos = 0;

	auto format = type->format;
	bool is_big_endian = (format & 0x100);
	size_t size = type->size;

	if (size == 1) {
		utils::writeToAccessor(data, cur_pos, uint8_t(value), is_big_endian);
	}
	else if (size == 4) {
		utils::writeToAccessor(data, cur_pos, uint32_t(value), is_big_endian);
	}
	else {
		throw std::exception(("Unknown bool size: " + std::to_string(size)).c_str());
	}
	return size;
}

hkreflex::hkClassIntInstance::hkClassIntInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
	auto format = type->format;
	is_big_endian = (format & 0x100);
	is_signed = (format & 0x200);
	byte_length = (format >> 10) / 8;
	c_type = type->ctype_name;
	_ASSERT(byte_length == type->size);
}

size_t hkreflex::hkClassIntInstance::Build(utils::DataAccessor& data)
{
	size_t cur_pos = 0;

	size_t size = byte_length;
	if (size != 1 && size != 2 && size != 4 && size != 8) {
		throw std::exception("Unknown int size");
	}

	if (is_signed) {
		switch (size) {
		case 1:
			svalue = utils::readFromAccessor<int8_t>(data, cur_pos, is_big_endian);
			break;
		case 2:
			svalue = utils::readFromAccessor<int16_t>(data, cur_pos, is_big_endian);
			break;
		case 4:
			svalue = utils::readFromAccessor<int32_t>(data, cur_pos, is_big_endian);
			break;
		case 8:
			svalue = utils::readFromAccessor<int64_t>(data, cur_pos, is_big_endian);
			break;
		default:
			throw std::exception("Unknown int size");
		}

	}
	else {
		switch (size) {
		case 1:
			value = utils::readFromAccessor<uint8_t>(data, cur_pos, is_big_endian);
			break;
		case 2:
			value = utils::readFromAccessor<uint16_t>(data, cur_pos, is_big_endian);
			break;
		case 4:
			value = utils::readFromAccessor<uint32_t>(data, cur_pos, is_big_endian);
			break;
		case 8:
			value = utils::readFromAccessor<uint64_t>(data, cur_pos, is_big_endian);
			break;
		default:
			throw std::exception("Unknown int size");
		}
	}

	return size;
}

std::string hkreflex::hkClassIntInstance::dump(int indent)
{
	std::string comment = "";

	if (type->type_name == "short") {
		auto value = utils::snorm_to_double(svalue, 1);
		if (value < 0) {
			value =  - 1 - value;
		}
		else {
			value = 1 - value;
		}
		comment = " // Comment: " + std::to_string(value);
	}
	else if (type->type_name == "char"){
		std::string str = "";
		str += (char)value;
		comment = " // Comment: " + str;
	}

	if (is_signed) {
		return std::to_string(svalue) + comment;
	}
	else {
		return std::to_string(value) + comment;
	}
}

uint64_t hkreflex::hkClassIntInstance::Serialize(utils::DataAccessor data, utils::SerializePool& serializer)
{
	size_t cur_pos = 0;
	size_t size = byte_length;
	if (size != 1 && size != 2 && size != 4 && size != 8) {
		throw std::exception("Unknown int size");
	}

	if (is_signed) {
		switch (size) {
		case 1:
			utils::writeToAccessor(data, cur_pos, int8_t(svalue), is_big_endian);
			break;
		case 2:
			utils::writeToAccessor(data, cur_pos, int16_t(svalue), is_big_endian);
			break;
		case 4:
			utils::writeToAccessor(data, cur_pos, int32_t(svalue), is_big_endian);
			break;
		case 8:
			utils::writeToAccessor(data, cur_pos, int64_t(svalue), is_big_endian);
			break;
		default:
			throw std::exception("Unknown int size");
		}

	}
	else {
		switch (size) {
		case 1:
			utils::writeToAccessor(data, cur_pos, uint8_t(value), is_big_endian);
			break;
		case 2:
			utils::writeToAccessor(data, cur_pos, uint16_t(value), is_big_endian);
			break;
		case 4:
			utils::writeToAccessor(data, cur_pos, uint32_t(value), is_big_endian);
			break;
		case 8:
			utils::writeToAccessor(data, cur_pos, uint64_t(value), is_big_endian);
			break;
		default:
			throw std::exception("Unknown int size");
		}
	}

	return size;
}

size_t hkreflex::hkClassPointerInstance::Build(utils::DataAccessor& data)
{
	size_t cur_pos = 0;
	in_document_ptr = utils::readFromAccessor<uint64_t>(data, cur_pos, false);

	if (in_document_ptr != 0) {
		if (in_document_ptr > ref_data->indexed_blocks.size()) {
			std::cout << "Warning: Out of bounds" << std::endl;
		}
		else {
			this->data_block = ref_data->indexed_blocks[in_document_ptr];
			_ASSERT(this->data_block->m_block_type == hkIndexedDataBlock::Type::Pointer);
			_ASSERT(this->data_block->m_num_instances == 1);
			//_ASSERT(this->type->is_parent_of(this->data_block->m_data_type));
			this->data_block->BuildInstances();
			this->ptr_instance = this->data_block->m_instances[0];
			_ASSERT(this->ptr_instance->type == this->data_block->m_data_type);
		}
	}
	return 8;
}

std::string hkreflex::hkClassPointerInstance::dump(int indent)
{
	std::string indent_str = "";
	for (int i = 0; i < indent; ++i) {
		indent_str += "\t";
	}

	std::string ret = "<ref> " + std::to_string(in_document_ptr) + " => " + type->sub_type->type_name + ": {\n";
	if (in_document_ptr != 0) {
		if (in_document_ptr > ref_data->indexed_blocks.size()) {
			ret += indent_str + "\t// Error: Out of bounds\n";
		}
		else if(this->ptr_instance) {
			ret += indent_str + "\t" + this->ptr_instance->dump(indent + 1);
		}
		else {
			ret += indent_str + "\t// Error: Null pointer\n";
		}
	}
	ret += indent_str + "}";
	return ret;
}

uint64_t hkreflex::hkClassPointerInstance::Serialize(utils::DataAccessor data, utils::SerializePool& serializer)
{
	size_t cur_pos = 0;
	if (this->ptr_instance) {
		ref_data->GetPatchChunk()->RegisterPatch(this->type, data - ref_data->GetSerializeDataPtr() + cur_pos);

		auto block = hkreflex::hkIndexedDataBlock::CreatePointerAndAlloc(ref_data, this->ptr_instance->type, this->ptr_instance);

		utils::writeToAccessor(data, cur_pos, serializer.QueueSerialization(block, true));
	}
	else {
		utils::writeToAccessor(data, cur_pos, (uint64_t)0);
	}
	return cur_pos;
}

hkreflex::hkClassFloatInstance::hkClassFloatInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
	auto format = type->format;
	is_big_endian = (format & 0x100);
	bit_length = (format >> 16);
	c_type = type->ctype_name;
	byte_length = type->size;
}

size_t hkreflex::hkClassFloatInstance::Build(utils::DataAccessor& data)
{
	size_t cur_pos = 0;
	size_t size = byte_length;

	switch (size) {
	case 2:
		value = utils::readHalfAsFullFromAccessor(data, cur_pos, is_big_endian);
		break;
	case 4:
		value = utils::readFromAccessor<float>(data, cur_pos, is_big_endian);
		break;
	case 8:
		value = utils::readFromAccessor<double>(data, cur_pos, is_big_endian);
		break;
	case 16:
		if (bit_length == 23) {
			value = utils::readFromAccessor<float>(data, cur_pos, is_big_endian);
			cur_pos += 12;
		}
		else if (bit_length == 52) {
			value = utils::readFromAccessor<double>(data, cur_pos, is_big_endian);
			cur_pos += 8;
		}
		else {
			throw std::exception("Unknown float size");
		}
		break;
	default:
		throw std::exception("Unknown float size");
	}

	return cur_pos;
}

std::string hkreflex::hkClassFloatInstance::dump(int indent)
{
	return std::to_string(value);
}

uint64_t hkreflex::hkClassFloatInstance::Serialize(utils::DataAccessor data, utils::SerializePool& serializer)
{
	size_t cur_pos = 0;
	size_t size = this->byte_length;

	switch (size) {
	case 2:
		utils::writeToAccessor(data, cur_pos, utils::floatToHalf(value), is_big_endian);
		break;
	case 4:
		utils::writeToAccessor(data, cur_pos, float(value), is_big_endian);
		break;
	case 8:
		utils::writeToAccessor(data, cur_pos, double(value), is_big_endian);
		break;
	case 16:
		if (bit_length == 23) {
			utils::writeToAccessor(data, cur_pos, float(value), is_big_endian);
			cur_pos += 12;
		}
		else if (bit_length == 52) {
			utils::writeToAccessor(data, cur_pos, double(value), is_big_endian);
			cur_pos += 8;
		}
		else {
			throw std::exception("Unknown float size");
		}
		break;
	default:
		throw std::exception("Unknown float size");
	}

	return cur_pos;
}

size_t hkreflex::hkClassRecordInstance::Build(utils::DataAccessor& data)
{
	utils::DataAccessor data_ptr = data;
	// The first field is always parent class
	if (type->parent_class) {
		hkreflex::hkClassInstance* instance = AllocateInstance(type->parent_class, ref_data);
		if (!instance) {
			return 0;
		}

		auto size = instance->Build(data_ptr);
		if (size == 0) {
			return 0;
		}

		record_instances.push_back({ "class_parent", instance, nullptr });
	}

	for (hkreflex::hkFieldBase*& field : type->fields) {
		utils::DataAccessor instance_data_ptr = data_ptr + field->offset;

		hkreflex::hkClassInstance* instance = AllocateInstance(field->type, ref_data);
		if (!instance) {
			return 0;
		}

		auto size = instance->Build(instance_data_ptr);
		if (size == 0) {
			return 0;
		}

		record_instances.push_back({ field->name, instance, field });
	}

	if (type->type_flags & TypeFlags::Interface){
		if (type->size == 8) {
			size_t cur_pos = 0;
			auto virtual_func = utils::readFromAccessor<uint64_t>(data_ptr, cur_pos);
			_ASSERT(virtual_func == 0);
		}
	}

	if (type->size == 0) {
		std::cout << "Warning: Record size is 0" << std::endl;
	}

	return type->size == 0 ? 1 : type->size;
}

std::string hkreflex::hkClassRecordInstance::dump(int indent)
{
	std::string indent_str = "";
	for (int i = 0; i < indent; ++i) {
		indent_str += "\t";
	}

	std::string ret = type->type_name + ": {\n";
	for (auto& record : record_instances) {
		ret += "\t" + indent_str + record.instance->type->type_name + " " + record.field_name + " = " + record.instance->dump(indent + 1) + ", \n";
	}
	ret += indent_str + "}";
	return ret;
}

uint64_t hkreflex::hkClassRecordInstance::Serialize(utils::DataAccessor data, utils::SerializePool& serializer)
{
	size_t cur_pos = 0;
	if (type->type_flags & TypeFlags::Interface) {
		if (type->size == 8) {
			uint64_t virtual_func = 0;
			utils::writeToAccessor(data, cur_pos, virtual_func);
		}
	}
	for (auto& record : record_instances) {
		utils::DataAccessor field_data = data;
		if (record.field_name != "class_parent") {
			field_data += record.field->offset;
		}
		cur_pos += record.instance->Serialize(field_data, serializer);
	}
	return type->size;
}

hkreflex::hkClassInstance* hkreflex::hkClassRecordInstance::GetParentInstance()
{
	for (auto& record : record_instances) {
		if (record.field_name == "class_parent") {
			return record.instance;
		}
	}
	return nullptr;
}

hkreflex::hkClassInstance* hkreflex::hkClassRecordInstance::GetInstanceByFieldName(const std::string& field_name)
{
	for (auto& record : record_instances) {
		if (record.field_name == field_name) {
			return record.instance;
		}
	}
	return nullptr;
}

std::string hkreflex::hkClassRecordInstance::GetStringByFieldName(const std::string& field_name)
{
	auto instance = GetInstanceByFieldName(field_name);
	if (!instance) {
		throw std::exception(("Field not found: " + field_name).c_str());
		return "";
	}

	if (instance->type->ctype_name == "std::string") {
		return dynamic_cast<hkreflex::hkClassStringInstance*>(instance)->value;
	}
	else {
		throw std::exception(("Field is not string: " + field_name).c_str());
		return "";
	}
}

int64_t hkreflex::hkClassRecordInstance::GetIntByFieldName(const std::string& field_name)
{
	auto instance = GetInstanceByFieldName(field_name);
	if (!instance) {
		throw std::exception(("Field not found: " + field_name).c_str());
		return 0;
	}

	auto int_instance = dynamic_cast<hkreflex::hkClassIntInstance*>(instance);
	if (int_instance && int_instance->is_signed) {
		return int_instance->svalue;
	}
	else {
		throw std::exception(("Field is not signed int: " + field_name).c_str());
		return 0;
	}
}

uint64_t hkreflex::hkClassRecordInstance::GetUIntByFieldName(const std::string& field_name)
{
	auto instance = GetInstanceByFieldName(field_name);
	if (!instance) {
		throw std::exception(("Field not found: " + field_name).c_str());
		return 0;
	}

	auto int_instance = dynamic_cast<hkreflex::hkClassIntInstance*>(instance);
	if (int_instance && !int_instance->is_signed) {
		return int_instance->value;
	}
	else {
		throw std::exception(("Field is not unsigned int: " + field_name).c_str());
		return 0;
	}
}

double hkreflex::hkClassRecordInstance::GetFloatByFieldName(const std::string& field_name)
{
	auto instance = GetInstanceByFieldName(field_name);
	if (!instance) {
		throw std::exception(("Field not found: " + field_name).c_str());
		return 0;
	}

	auto float_instance = dynamic_cast<hkreflex::hkClassFloatInstance*>(instance);
	if (float_instance) {
		return float_instance->value;
	}
	else {
		throw std::exception(("Field is not float: " + field_name).c_str());
		return 0;
	}
}

bool hkreflex::hkClassRecordInstance::GetBoolByFieldName(const std::string& field_name)
{
	auto instance = GetInstanceByFieldName(field_name);
	if (!instance) {
		throw std::exception(("Field not found: " + field_name).c_str());
		return false;
	}

	auto bool_instance = dynamic_cast<hkreflex::hkClassBoolInstance*>(instance);
	if (bool_instance) {
		return bool_instance->value;
	}
	else {
		throw std::exception(("Field is not bool: " + field_name).c_str());
		return false;
	}
}

size_t hkreflex::hkClassArrayInstance::Build(utils::DataAccessor& data)
{
	size_t cur_pos = 0;
	auto element_type = type->sub_type;
	if (type->ctype_name == "Eigen::Vector4f" || type->ctype_name == "Eigen::Quaternionf" || type->ctype_name == "Eigen::Quaterniond") { // Allocation
		utils::DataAccessor data_ptr = data;

		for (int i = 0; i < 4; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return false;
			}

			auto size = instance->Build(data_ptr);
			if (size == 0) {
				return false;
			}

			auto float_instance = dynamic_cast<hkClassFloatInstance*>(instance);

			_ASSERT(float_instance);

			float_array[i] = float_instance->value;

			array_instances.push_back(instance);

			data_ptr += size;
		}

		this->c_type = type->ctype_name;

		return data_ptr - data;
	}
	else if (type->ctype_name == "Eigen::Matrix4f") { // Allocation
		utils::DataAccessor data_ptr = data;

		for (int i = 0; i < 16; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return false;
			}

			auto size = instance->Build(data_ptr);
			if (size == 0) {
				return false;
			}

			auto float_instance = dynamic_cast<hkClassFloatInstance*>(instance);

			_ASSERT(float_instance);

			float_array[i] = float_instance->value;

			array_instances.push_back(instance);

			data_ptr += size;
		}

		this->c_type = type->ctype_name;

		return data_ptr - data;
	}
	else if (type->ctype_name == "Eigen::Matrix3f") { // Allocation
		utils::DataAccessor data_ptr = data;

		for (int i = 0; i < 12; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return false;
			}

			auto size = instance->Build(data_ptr);
			if (size == 0) {
				return false;
			}

			auto float_instance = dynamic_cast<hkClassFloatInstance*>(instance);

			_ASSERT(float_instance);

			float_array[i] = float_instance->value;

			array_instances.push_back(instance);

			data_ptr += size;
		}

		this->c_type = type->ctype_name;

		return data_ptr - data;
	}
	else if (type->type_name == "hkArray") { // Copy
		this->in_document_ptr = utils::readFromAccessor<uint64_t>(data, cur_pos);
		this->size_and_flags = utils::readFromAccessor<uint64_t>(data, cur_pos);
		//_ASSERT(this->size_and_flags == 0x0000000000000000);
		if (this->size_and_flags != 0x0000000000000000) {
			std::cout << "Warning: Unknown sizeAndFlag. SizeAndFlag: " << std::hex << size_and_flags << std::endl;
			return cur_pos;
		}

		if (in_document_ptr) {
			if (in_document_ptr >= ref_data->indexed_blocks.size()) {
				std::cout << "Warning: Out of bounds. In document ptr: " << in_document_ptr << " Indexed blocks size: " << ref_data->indexed_blocks.size() << std::endl;
				return cur_pos;
			}
			data_block = ref_data->indexed_blocks[in_document_ptr];
			if (data_block->m_data_type != element_type) {
				std::cout << "Warning: Array type mismatch. Data type: " << data_block->m_data_type->type_name << " Expected type: " << element_type->type_name << std::endl;
				return cur_pos;
			}
			data_block->BuildInstances();
				
			array_instances = data_block->m_instances;
		}
		else {
			//std::cout << "Warning: In document ptr is null" << std::endl;
		}
		return cur_pos;
	}
	else if (type->type_name == "hkRelArray") { // Reference
		in_document_ptr = utils::readFromAccessor<uint32_t>(data, cur_pos);
		if (in_document_ptr) {
			data_block = ref_data->indexed_blocks[in_document_ptr];
			_ASSERT(data_block->m_data_type == element_type);
			data_block->BuildInstances();
			array_instances = data_block->m_instances;
		}
		return cur_pos;
	}
	else if (type->type_name == "T[N]") { // Allocation
		size_t compile_size = 0;

		for (auto& arg : type->template_args) {
			if (arg->template_arg_name == "vN") {
				auto value_arg = dynamic_cast<hkTemplateArgumentValue*>(arg);
				compile_size = value_arg->value;
				break;
			}
		}
		utils::DataAccessor data_ptr = data;
		for (int i = 0; i < compile_size; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return false;
			}

			auto size = instance->Build(data_ptr);
			if (size == 0) {
				return false;
			}

			this->array_instances.push_back(instance);
			data_ptr += size;
		}
		return data_ptr - data;
	}
	else {
		throw std::exception("Unknown array type");
	}
	return 0;
}

std::string hkreflex::hkClassArrayInstance::dump(int indent)
{
	std::string indent_str = "";
	for (int i = 0; i < indent; ++i) {
		indent_str += "\t";
	}

	if (c_type == "std::vector" && type->type_name != "T[N]") {
		std::string ret = "<ref> " + std::to_string(in_document_ptr) + " => " + type->sub_type->type_name + "[" + std::to_string(array_instances.size()) + "]: [\n";
		if (!this->array_instances.empty()) {
			for(auto instance : array_instances) {
				ret += indent_str + "\t" + instance->dump(indent + 1) + ",\n";
			}
		}
		else if (in_document_ptr == 0) {
			ret += indent_str + "\t// Empty\n";
		}
		else if (in_document_ptr > 0 && in_document_ptr < ref_data->indexed_blocks.size() && this->data_block == 0) {
			ret += indent_str + "\t// Element type mismatch\n";
		}
		else {
			ret += indent_str + "\t// Referencing an outer object\n";
		}

		ret += indent_str + "]";
		return ret;
	}
	else if (type->type_name == "T[N]") {
		std::string ret = type->sub_type->type_name + "[" + std::to_string(array_instances.size()) + "]: [\n";
		for (auto& instance : array_instances) {
			ret += indent_str + "\t" + instance->dump(indent + 1) + ",\n";
		}
		ret += indent_str + "]";
		return ret;
	}
	else if (c_type == "Eigen::Vector4f" || c_type == "Eigen::Quaternionf" || c_type == "Eigen::Quaterniond") {
		std::string ret = "[";
		for (int i = 0; i < 3; i++) {
			ret += std::to_string(float_array[i]) + ", ";
		}
		ret += std::to_string(float_array[3]) + "]";
		return ret;
	}
	else if (c_type == "Eigen::Matrix4f") {
		std::string ret = c_type + "{\n";
		for (int j = 0; j < 4; j++) {
			ret += indent_str + "\t";
			for (int i = 0; i < 3; i++) {
				ret += std::to_string(float_array[j * 4 + i]) + ", ";
			}
			ret += std::to_string(float_array[j * 4 + 3]) + "\n";
		}
		return ret + indent_str + "}";
	}
	else if (c_type == "Eigen::Matrix3f") {
		std::string ret = c_type + "{\n";
		for (int j = 0; j < 3; j++) {
			ret += indent_str + "\t";
			for (int i = 0; i < 3; i++) {
				ret += std::to_string(float_array[j * 4 + i]) + ", ";
			}
			ret += std::to_string(float_array[j * 4 + 3]) + "\n";
		}
		return ret + indent_str + "}";
	}
	else {
		throw std::runtime_error("Unknown array type: " + c_type);
	}
}

uint64_t hkreflex::hkClassArrayInstance::Serialize(utils::DataAccessor data, utils::SerializePool& serializer)
{
	size_t cur_pos = 0;
	if (type->ctype_name == "Eigen::Vector4f" || type->ctype_name == "Eigen::Quaternionf" || type->ctype_name == "Eigen::Quaterniond") {
		for (int i = 0; i < 4; i++) {
			auto instance = dynamic_cast<hkClassFloatInstance*>(array_instances[i]);
			instance->Serialize(data + cur_pos, serializer);
			cur_pos += instance->type->size;
		}
	}
	else if (type->ctype_name == "Eigen::Matrix4f") {
		for (int i = 0; i < 16; i++) {
			auto instance = dynamic_cast<hkClassFloatInstance*>(array_instances[i]);
			instance->Serialize(data + cur_pos, serializer);
			cur_pos += instance->type->size;
		}
	}
	else if (type->ctype_name == "Eigen::Matrix3f") {
		for (int i = 0; i < 12; i++) {
			auto instance = dynamic_cast<hkClassFloatInstance*>(array_instances[i]);
			instance->Serialize(data + cur_pos, serializer);
			cur_pos += instance->type->size;
		}
	}
	else {
		auto element_type = type->sub_type;

		if (type->type_name == "hkArray") {
			uint64_t ptr = 0;
			if (!this->array_instances.empty()) {
				ref_data->GetPatchChunk()->RegisterPatch(this->type, data - ref_data->GetSerializeDataPtr() + cur_pos);

				auto block = hkIndexedDataBlock::CreateArrayAndAlloc(ref_data, element_type, array_instances);

				ptr = serializer.QueueSerialization(block, true);
			}
			else{
				ptr = 0;
			}

			utils::writeToAccessor(data, cur_pos, ptr);
			utils::writeToAccessor(data, cur_pos, this->size_and_flags);
		}
		else if (type->type_name == "hkRelArray") {
			uint32_t ptr = 0;
			if (!this->array_instances.empty()) {
				ref_data->GetPatchChunk()->RegisterPatch(this->type, data - ref_data->GetSerializeDataPtr() + cur_pos);

				auto block = hkIndexedDataBlock::CreateArrayAndAlloc(ref_data, element_type, array_instances);

				ptr = serializer.QueueSerialization(block, true);
			}
			else {
				ptr = 0;
			}

			utils::writeToAccessor(data, cur_pos, ptr);
		}
		else if (type->type_name == "T[N]") {
			size_t compile_size = 0;
			for (auto& arg : type->template_args) {
				if (arg->template_arg_name == "vN") {
					auto value_arg = dynamic_cast<hkTemplateArgumentValue*>(arg);
					compile_size = value_arg->value;
					break;
				}
			}
			for (auto& instance : array_instances) {
				cur_pos += instance->Serialize(data + cur_pos, serializer);
			}
		}
		else {
			throw std::exception("Unknown array type");
		}
	}
	return cur_pos;
}

void hkreflex::hkClassArrayInstance::resize(size_t num)
{
	auto element_type = type->sub_type;
	if (type->ctype_name == "Eigen::Vector4f" || type->ctype_name == "Eigen::Quaternionf" || type->ctype_name == "Eigen::Quaterniond") { // Allocation
		for (int i = this->array_instances.size(); i < 4; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return;
			}

			this->array_instances.push_back(instance);
		}
	}
	else if (type->ctype_name == "Eigen::Matrix4f") { // Allocation
		
		for (int i = this->array_instances.size(); i < 16; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return;
			}

			this->array_instances.push_back(instance);
		}
	}
	else if (type->ctype_name == "Eigen::Matrix3f") { // Allocation
		for (int i = this->array_instances.size(); i < 12; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return;
			}

			this->array_instances.push_back(instance);
		}
	}
	else if (type->type_name == "hkArray") {
		if (this->array_instances.empty()) {
			this->in_document_ptr = 0;
			this->size_and_flags = 0;
		}

		for (int i = this->array_instances.size(); i > num; --i) {
			delete this->array_instances.back();
			this->array_instances.pop_back();
		}

		for (int i = this->array_instances.size(); i < num; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return;
			}

			this->array_instances.push_back(instance);
		}
	}
	else if (type->type_name == "hkRelArray") {
		if (this->array_instances.empty()) {
			this->in_document_ptr = 0;
		}

		for (int i = this->array_instances.size(); i > num; --i) {
			delete this->array_instances.back();
			this->array_instances.pop_back();
		}

		for (int i = this->array_instances.size(); i < num; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return;
			}

			this->array_instances.push_back(instance);
		}
	}
	else if (type->type_name == "T[N]") { // Fill array with fixed number of elements defined by template argument
		size_t compile_size = 0;
		for (auto& arg : type->template_args) {
			if (arg->template_arg_name == "vN") {
				auto value_arg = dynamic_cast<hkTemplateArgumentValue*>(arg);
				compile_size = value_arg->value;
				break;
			}
		}

		for (int i = this->array_instances.size(); i > compile_size; --i) {
			delete this->array_instances.back();
			this->array_instances.pop_back();
		}

		for (int i = this->array_instances.size(); i < compile_size; ++i) {
			auto instance = AllocateInstance(element_type, ref_data);
			if (!instance) {
				return;
			}

			this->array_instances.push_back(instance);
		}	
	}
	else {
		throw std::exception("Unknown array type");
	}
	return;
}
