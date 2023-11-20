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

bool hkreflex::hkIndexedDataBlock::BuildInstances(hkphysics::hkPhysicsReflectionData* ref_data)
{
	//return true;
	if (this->m_instances.size() == this->m_num_instances) {
		return true;
	}

	auto data_ptr = ref_data->GetDataPtr() + this->m_offset;
	for (int i = 0; i < this->m_num_instances; ++i) {
		auto instance = AllocateInstance(this->m_data_type, data_ptr);
		if (!instance) {
			return false;
		}

		auto size = instance->Build(ref_data);
		if (size == 0) {
			return false;
		}

		m_instances.push_back(instance);

		data_ptr += size;
	}

	return true;
}

std::string hkreflex::hkIndexedDataBlock::dump_instances(hkphysics::hkPhysicsReflectionData* ref_data, int indent, bool use_mapped_ctype)
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
	for (auto& instance : m_instances) {
		ret += indent_str + instance->dump(ref_data, indent) + ";\n";
	}
	return ret;
}

std::string hkreflex::hkFieldBase::to_literal(bool use_mapped_ctype)
{
	if (use_mapped_ctype) {
		return type->ctype_name + " " + name + ";\t// Offset: " + std::to_string(this->offset) + " Unk: " + std::to_string(this->unk_value);
	}
	return type->to_literal(false, true) + " " + name + ";\t// Offset: " + std::to_string(this->offset) + " Unk: " + std::to_string(this->unk_value);
}

hkreflex::hkClassInstance* hkreflex::AllocateInstance(hkreflex::hkClassBase* type, const uint8_t*& data)
{
	auto kind = type->kind;
	if (kind == hkClassBase::TypeKind::Inherited) {
		_ASSERT(type->parent_class != nullptr);
		type = type->parent_class;
		kind = type->kind;
	}

	switch (kind) {
	case hkClassBase::TypeKind::Array:
		return new hkClassArrayInstance(type, data);
	case hkClassBase::TypeKind::Bool:
		return new hkClassBoolInstance(type, data);
	case hkClassBase::TypeKind::Float:
		return new hkClassFloatInstance(type, data);
	case hkClassBase::TypeKind::Int:
		return new hkClassIntInstance(type, data);
	case hkClassBase::TypeKind::Pointer:
		return new hkClassPointerInstance(type, data);
	case hkClassBase::TypeKind::Record:
		return new hkClassRecordInstance(type, data);
	case hkClassBase::TypeKind::String:
		return new hkClassStringInstance(type, data);
	default:
		std::cout << "Unknown type kind: " << (int)type->kind << std::endl;
		return nullptr;
	}
}

size_t hkreflex::hkClassRecordInstance::Build(hkphysics::hkPhysicsReflectionData* ref_data)
{
	const uint8_t* data_ptr = data;
	for (hkreflex::hkFieldBase*& field : type->fields) {
		const uint8_t* instance_data_ptr = data_ptr + field->offset;

		hkreflex::hkClassInstance* instance = AllocateInstance(field->type, instance_data_ptr);
		if (!instance) {
			return 0;
		}

		auto size = instance->Build(ref_data);
		if (size == 0) {
			return 0;
		}

		record_instances.push_back({ field->name, instance });
	}

	return type->size;
}

size_t hkreflex::hkClassPointerInstance::Build(hkphysics::hkPhysicsReflectionData* ref_data)
{
	in_document_ptr = *reinterpret_cast<const uint64_t*>(data);
	return 4;
}

size_t hkreflex::hkClassArrayInstance::Build(hkphysics::hkPhysicsReflectionData* ref_data)
{
	size_t cur_pos = 0;
	if (type->ctype_name == "Eigen::Vector4f" || type->ctype_name == "Eigen::Quaternionf" || type->ctype_name == "Eigen::Quaterniond") {
		const uint8_t* data_ptr = data;

		for (int i = 0; i < 4; ++i) {
			auto instance = AllocateInstance(type->sub_type, data_ptr);
			if (!instance) {
				return false;
			}

			auto size = instance->Build(ref_data);
			if (size == 0) {
				return false;
			}

			auto float_instance = dynamic_cast<hkClassFloatInstance*>(instance);

			_ASSERT(float_instance);

			float_array[i] = float_instance->value;

			data_ptr += size;
		}

		this->c_type = type->ctype_name;

		return data_ptr - data;
	}
	else if (type->ctype_name == "Eigen::Matrix4f") {
		const uint8_t* data_ptr = data;

		for (int i = 0; i < 16; ++i) {
			auto instance = AllocateInstance(type->sub_type, data_ptr);
			if (!instance) {
				return false;
			}

			auto size = instance->Build(ref_data);
			if (size == 0) {
				return false;
			}

			auto float_instance = dynamic_cast<hkClassFloatInstance*>(instance);

			_ASSERT(float_instance);

			float_array[i] = float_instance->value;

			data_ptr += size;
		}

		this->c_type = type->ctype_name;

		return data_ptr - data;
	}
	else if (type->ctype_name == "Eigen::Matrix3f") {
		const uint8_t* data_ptr = data;

		for (int i = 0; i < 12; ++i) {
			auto instance = AllocateInstance(type->sub_type, data_ptr);
			if (!instance) {
				return false;
			}

			auto size = instance->Build(ref_data);
			if (size == 0) {
				return false;
			}

			auto float_instance = dynamic_cast<hkClassFloatInstance*>(instance);

			_ASSERT(float_instance);

			float_array[i] = float_instance->value;

			data_ptr += size;
		}

		this->c_type = type->ctype_name;

		return data_ptr - data;
	}
	else {
		auto element_type = type->sub_type;
		size_t compile_size = 0;

		if (type->type_name == "T[N]") {
			for (auto& arg : type->template_args) {
				if (arg->template_arg_name == "vN") {
					auto value_arg = dynamic_cast<hkTemplateArgumentValue*>(arg);
					compile_size = value_arg->value;
					break;
				}
			}
		}

		if (type->type_name == "hkArray") {
			in_document_ptr = utils::readFromBuffer<uint64_t>(data, cur_pos);
			uint64_t sizeAndFlag = utils::readFromBuffer<uint64_t>(data, cur_pos);
			_ASSERT(sizeAndFlag == 0x0000000000000000);
			if (in_document_ptr) {
				data_block = ref_data->indexed_blocks[in_document_ptr];
				_ASSERT(data_block->m_data_type == element_type);
				data_block->BuildInstances(ref_data);
				array_instances = data_block->m_instances;
			}
			return cur_pos;
		}
		else if (type->type_name == "hkRelArray") {
			in_document_ptr = utils::readFromBuffer<uint32_t>(data, cur_pos);
			if (in_document_ptr) {
				data_block = ref_data->indexed_blocks[in_document_ptr];
				_ASSERT(data_block->m_data_type == element_type);
				data_block->BuildInstances(ref_data);
				array_instances = data_block->m_instances;
			}
			return cur_pos;
		}
		else if (type->type_name == "T[N]") {
			/*size_t format_size = type->format >> 8;
			if (format_size != compile_size) {
				std::cout << "Warning: Array size mismatch. Compile size: " << compile_size << " Format size: " << format_size << " Format: " << type->format << std::endl;
			}*/

			const uint8_t* data_ptr = data;
			for (int i = 0; i < compile_size; ++i) {
				auto instance = AllocateInstance(element_type, data_ptr);
				if (!instance) {
					return false;
				}

				auto size = instance->Build(ref_data);
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
	}
	return 0;
}

size_t hkreflex::hkClassFloatInstance::Build(hkphysics::hkPhysicsReflectionData* ref_data)
{
	size_t cur_pos = 0;
	auto format = type->format;
	is_big_endian = (format & 0x100);
	byte_length = (format >> 10) / 8;
	c_type = type->ctype_name;
	size_t size = type->size;

	bytes = new uint8_t[size];
	std::memcpy(const_cast<uint8_t*>(bytes), data, size);

	switch (size) {
	case 2:
		value = utils::readHalfAsFullFromBuffer(data, cur_pos, is_big_endian);
		break;
	case 4:
		value = utils::readFromBuffer<float>(data, cur_pos, is_big_endian);
		break;
	case 8:
		value = utils::readFromBuffer<double>(data, cur_pos, is_big_endian);
		break;
	case 16:
		if (byte_length == 23) {
			value = utils::readFromBuffer<float>(data, cur_pos, is_big_endian);
			cur_pos += 12;
		}
		else if (byte_length == 52) {
			value = utils::readFromBuffer<double>(data, cur_pos, is_big_endian);
			cur_pos += 8;
		}
		else {
			throw std::exception("Unknown float size");
		}
	default:
		throw std::exception("Unknown float size");
	}

	return cur_pos;
}

size_t hkreflex::hkClassIntInstance::Build(hkphysics::hkPhysicsReflectionData* ref_data)
{
	size_t cur_pos = 0;
	auto format = type->format;
	
	is_big_endian = (format & 0x100);
	is_signed = (format & 0x200);
	byte_length = (format >> 10) / 8;
	c_type = type->ctype_name;

	size_t size = byte_length;
	if (size != 1 && size != 2 && size != 4 && size != 8) {
		if (format & 0b100) {
			size = type->size;
		}
		else {
			throw std::exception("Unknown int size");
		}
	}

	bytes = new uint8_t[size];
	std::memcpy(const_cast<uint8_t*>(bytes), data, size);

	if (is_signed) {
		switch (size) {
		case 1:
			svalue = utils::readFromBuffer<int8_t>(data, cur_pos, is_big_endian);
			break;
		case 2:
			svalue = utils::readFromBuffer<int16_t>(data, cur_pos, is_big_endian);
			break;
		case 4:
			svalue = utils::readFromBuffer<int32_t>(data, cur_pos, is_big_endian);
			break;
		case 8:
			svalue = utils::readFromBuffer<int64_t>(data, cur_pos, is_big_endian);
			break;
		default:
			throw std::exception("Unknown int size");
		}

	}
	else {
		switch (size) {
		case 1:
			value = utils::readFromBuffer<uint8_t>(data, cur_pos, is_big_endian);
			break;
		case 2:
			value = utils::readFromBuffer<uint16_t>(data, cur_pos, is_big_endian);
			break;
		case 4:
			value = utils::readFromBuffer<uint32_t>(data, cur_pos, is_big_endian);
			break;
		case 8:
			value = utils::readFromBuffer<uint64_t>(data, cur_pos, is_big_endian);
			break;
		default:
			throw std::exception("Unknown int size");
		}
	}

	return size;
}

size_t hkreflex::hkClassStringInstance::Build(hkphysics::hkPhysicsReflectionData* ref_data)
{
	size_t cur_pos = 0;
	if (this->type->format & 0x10) {
		value = utils::readStringFromBuffer(data, cur_pos, this->type->format >> 16);
		return cur_pos;
	}
	else {
		uint64_t ptr = utils::readFromBuffer<uint64_t>(data, cur_pos);
		value = "";
		if (ptr) {
			auto refered = ref_data->indexed_blocks[ptr];
			refered->BuildInstances(ref_data);
			throw std::exception("Not implemented.");
		}
	}
	return cur_pos;
}

std::string hkreflex::hkClassStringInstance::dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent)
{
	return "\"" + value + "\"";
}

size_t hkreflex::hkClassBoolInstance::Build(hkphysics::hkPhysicsReflectionData* ref_data)
{
	size_t cur_pos = 0;

	auto format = type->format;
	bool is_big_endian = (format & 0x100);
	size_t size = type->size;
	size_t bit_length = format >> 10;

	if (size == 1) {
		value = utils::readFromBuffer<uint8_t>(data, cur_pos, is_big_endian);
	}
	else if (size == 4) {
		value = utils::readFromBuffer<uint32_t>(data, cur_pos, is_big_endian);
	}
	else {
		throw std::exception(("Unknown bool size at offset: " + std::to_string(data - ref_data->GetDataPtr())).c_str());
	}

	return cur_pos;
}

std::string hkreflex::hkClassBoolInstance::dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent)
{
	return value ? "true" : "false";
}

std::string hkreflex::hkClassIntInstance::dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent)
{
	if (is_signed) {
		return std::to_string(svalue);
	}
	else {
		return std::to_string(value);
	}
}

std::string hkreflex::hkClassPointerInstance::dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent)
{
	std::string indent_str = "";
	for (int i = 0; i < indent; ++i) {
		indent_str += "\t";
	}

	std::string ret = "<ref> " + std::to_string(in_document_ptr) + " => {\n";
	if (in_document_ptr != 0)
		ret += ref_data->indexed_blocks[in_document_ptr]->dump_instances(ref_data, indent + 1);
	ret += indent_str + "}";
	return ret;
}

std::string hkreflex::hkClassFloatInstance::dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent)
{
	return std::to_string(value);
}

std::string hkreflex::hkClassRecordInstance::dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent)
{
	std::string indent_str = "";
	for (int i = 0; i < indent; ++i) {
		indent_str += "\t";
	}

	std::string ret = type->type_name + ": {\n";
	for (auto& record : record_instances) {
		ret += "\t" + indent_str + record.instance->type->type_name + " " + record.field_name + " = " + record.instance->dump(ref_data, indent + 1) + ", \n";
	}
	ret += indent_str + "}";
	return ret;
}

std::string hkreflex::hkClassArrayInstance::dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent)
{
	std::string indent_str = "";
	for (int i = 0; i < indent; ++i) {
		indent_str += "\t";
	}

	if (c_type == "std::vector" && type->type_name != "T[N]") {
		std::string ret = "<ref> " + std::to_string(in_document_ptr) + " => [\n";
		if (in_document_ptr != 0)
			ret += this->data_block->dump_instances(ref_data, indent + 1);
		ret += indent_str + "]";
		return ret;
	}
	else if (type->type_name == "T[N]") {
		std::string ret = type->sub_type->type_name + "[] => [\n";
		for (auto& instance : array_instances) {
			ret += indent_str + "\t" + instance->dump(ref_data, indent + 1) + ",\n";
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
		std::string ret = "{\n";
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
		std::string ret = "{\n";
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