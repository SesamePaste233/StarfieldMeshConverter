#include "hkTypeTranscriptor.h"

std::string utils::hkTypeTranscriptor::transcript_path = "hkTypeTranscript.json";

utils::hkTypeTranscriptor::TypeTranscriptProperties& utils::hkTypeTranscriptor::RegisterClass(hkreflex::hkClassBase* hk_class, bool recursive, bool update_exist)
{
	MapIdType map_id = hk_class->to_C_identifier();

	if (!is_valid_id(map_id)) {
		throw std::runtime_error("Invalid Map Id");
	}

	auto& properties = this->type_transcripts[map_id]; // Overwrite or create new

	properties.id = map_id;
	properties.hash = hk_class->hash;

	if (hk_class->_defined == false && hk_class->_declared == false) {
		return properties;
	}

	if (update_exist || properties.declared == false) {
		properties.class_name = hk_class->type_name;
		for (auto& temp_arg : hk_class->template_args) {
			std::string arg_identifier = temp_arg->to_arg_identifier();
			MapIdType arg_type = get_invalid_id();
			uint32_t arg_value = 0;
			if (temp_arg->template_arg_name[0] != 'v') {
				auto& arg_hk_class = dynamic_cast<hkreflex::hkTemplateArgumentType*>(temp_arg)->type;
				arg_type = arg_hk_class->to_C_identifier();
				assert(is_valid_id(arg_type));
				if (recursive) {
					this->RegisterClass(arg_hk_class, recursive, update_exist);
				}
			}
			else {
				arg_value = static_cast<hkreflex::hkTemplateArgumentValue*>(temp_arg)->value;
			}
			properties.template_args.push_back({ arg_identifier, arg_type, arg_value });
		}
		properties.declared = true;
	}

	if (hk_class->_defined == false) {
		return properties;
	}

	if (update_exist || properties.defined == false) {
		if (hk_class->parent_class) {
			properties.parent_class_id = hk_class->parent_class->to_C_identifier();
			if (recursive) {
				this->RegisterClass(hk_class->parent_class, recursive, update_exist);
			}
		}

		properties.optionals = to_underlying(hk_class->optionals);
		properties.format = hk_class->format;

		if (hk_class->sub_type) {
			properties.sub_type_id = hk_class->sub_type->to_C_identifier();
			if (recursive) {
				this->RegisterClass(hk_class->sub_type, recursive, update_exist);
			}
		}

		properties.version = hk_class->version;
		properties.size = hk_class->size;
		properties.alignment = hk_class->alignment;
		properties.type_flags = to_underlying(hk_class->type_flags);

		for (auto& member : hk_class->fields) {
			TypeTranscriptProperties::FieldTranscriptProperties field_properties;
			field_properties.name = member->name;
			field_properties.type_id = member->type->to_C_identifier();

			assert(is_valid_id(field_properties.type_id));

			if (recursive) {
				this->RegisterClass(member->type, recursive, update_exist);
			}

			field_properties.offset = member->offset;
			field_properties.flags = to_underlying(member->flags);
			field_properties.unk_value = member->unk_value;
			properties.fields.push_back(field_properties);
		}

		properties.defined = true;
	}

	return properties;
}

hkreflex::hkClassBase* utils::hkTypeTranscriptor::AllocateClassByUniqueId(MapIdType id)
{
	if (!is_valid_id(id)) {
		return nullptr;
	}

	if (all_allocated_classes.find(id) != all_allocated_classes.end()) {
		return all_allocated_classes[id];
	}

	if (this->type_transcripts.find(id) == this->type_transcripts.end()) {
		throw std::runtime_error("Class not found");
	}

	hkreflex::hkClassBase* hk_class = new hkreflex::hkClassBase();
	all_allocated_classes[id] = hk_class;

	auto& properties = this->type_transcripts[id];
	if (properties.declared) {
		hk_class->type_name = properties.class_name;
		hk_class->hash = properties.hash;

		for (auto& temp_arg : properties.template_args) {
			if (!is_valid_id(temp_arg.type_id) && temp_arg.name[0] == 'v') {
				auto temp_arg_value = new hkreflex::hkTemplateArgumentValue();
				temp_arg_value->template_arg_name = temp_arg.name;
				temp_arg_value->value = temp_arg.value;
				hk_class->template_args.push_back(temp_arg_value);
			}
			else if (is_valid_id(temp_arg.type_id) && temp_arg.name[0] != 'v') {
				auto temp_arg_type = new hkreflex::hkTemplateArgumentType();
				temp_arg_type->template_arg_name = temp_arg.name;
				temp_arg_type->type = AllocateClassByUniqueId(temp_arg.type_id);
				hk_class->template_args.push_back(temp_arg_type);
			}
			else {
				throw std::runtime_error("Invalid template arg");
			}
		}

		hk_class->_declared = true;
	}

	if (properties.defined) {
		if (is_valid_id(properties.parent_class_id)) {
			hk_class->parent_class = AllocateClassByUniqueId(properties.parent_class_id);
		}

		hk_class->optionals = static_cast<hkreflex::Optional>(properties.optionals);
		auto& optional = hk_class->optionals;
		if (optional & hkreflex::Optional::Format) { // 0b00000001
			hk_class->format = properties.format;
			hk_class->kind = (hkreflex::hkClassBase::TypeKind)(hk_class->format & 0x0000000F);
		}
		if (optional & hkreflex::Optional::SubType) { // 0b00000010
			if (is_valid_id(properties.sub_type_id)) {
				hk_class->sub_type = AllocateClassByUniqueId(properties.sub_type_id);
			}
			else {
				throw std::runtime_error("Invalid sub type");
			}
		}
		if (optional & hkreflex::Optional::Version) { // 0b00000100
			hk_class->version = properties.version;
		}
		if (optional & hkreflex::Optional::SizeAlign) { // 0b00001000
			hk_class->size = properties.size;
			hk_class->alignment = properties.alignment;
		}
		if (optional & hkreflex::Optional::Flags) { // 0b00010000
			hk_class->type_flags = (hkreflex::TypeFlags)properties.type_flags;
		}
		if (optional & hkreflex::Optional::Members) { // 0b00100000
			hk_class->fields.clear();

			for (auto& field_properties : properties.fields) {
				auto field = new hkreflex::hkFieldBase();
				field->name = field_properties.name;
				field->type = AllocateClassByUniqueId(field_properties.type_id);
				field->offset = field_properties.offset;
				field->flags = (hkreflex::hkFieldBase::FieldFlags)field_properties.flags;
				field->unk_value = field_properties.unk_value;
				hk_class->fields.push_back(field);
			}
		}

		hk_class->_defined = true;
	}

	return hk_class;
}

nlohmann::json utils::hkTypeTranscriptor::SerializeTranscripts()
{
	nlohmann::json json = nlohmann::json::array();

	for (auto& [id, properties] : this->type_transcripts) {
		nlohmann::json json_properties;
		json_properties["declared"] = (uint8_t)properties.declared;
		json_properties["defined"] = (uint8_t)properties.defined;

		if (properties.declared) {
			json_properties["id"] = properties.id;
			json_properties["hash"] = properties.hash;
			json_properties["class_name"] = properties.class_name;
			json_properties["template_args"] = nlohmann::json::array();

			for (auto& arg_prop : properties.template_args) {
				json_properties["template_args"].push_back(arg_prop.Serialize());
			}
		}

		if (properties.defined) {
			json_properties["fields"] = nlohmann::json::array();

			for (auto& field : properties.fields) {
				json_properties["fields"].push_back(field.Serialize());
			}

			json_properties["parent_class_id"] = properties.parent_class_id;
			json_properties["optionals"] = properties.optionals;
			json_properties["format"] = properties.format;
			json_properties["sub_type_id"] = properties.sub_type_id;
			json_properties["version"] = properties.version;
			json_properties["size"] = properties.size;
			json_properties["alignment"] = properties.alignment;
			json_properties["type_flags"] = properties.type_flags;
		}

		json.push_back(json_properties);
	}

	return json;
}

void utils::hkTypeTranscriptor::SerializeTranscripts(std::string path, int json_indent) {
	std::ofstream file(path);
	auto json = SerializeTranscripts();

#ifdef _DEBUG
	json_indent = 2;
#endif // _DEBUG

	file << json.dump(json_indent);
	file.close();
}

void utils::hkTypeTranscriptor::DeserializeTranscripts(nlohmann::json& json)
{
	for (auto& json_properties : json) {
		TypeTranscriptProperties properties;
		properties.declared = (uint8_t)json_properties["declared"];
		properties.defined = (uint8_t)json_properties["defined"];

		if (properties.declared) {
			properties.id = json_properties["id"];
			properties.hash = json_properties["hash"];
			properties.class_name = json_properties["class_name"];

			properties.template_args = std::vector<TypeTranscriptProperties::TemplateArgTranscriptProperties>();

			for (auto& json_arg : json_properties["template_args"]) {
				TypeTranscriptProperties::TemplateArgTranscriptProperties arg_properties;
				arg_properties.Deserialize(json_arg);
				properties.template_args.push_back(arg_properties);
			}
		}

		if (properties.defined) {
			properties.fields = std::vector<TypeTranscriptProperties::FieldTranscriptProperties>();

			for (auto& json_field : json_properties["fields"]) {
				TypeTranscriptProperties::FieldTranscriptProperties field_properties;
				field_properties.Deserialize(json_field);
				properties.fields.push_back(field_properties);
			}

			properties.parent_class_id = json_properties["parent_class_id"];
			properties.optionals = json_properties["optionals"];
			properties.format = json_properties["format"];
			properties.sub_type_id = json_properties["sub_type_id"];
			properties.version = json_properties["version"];
			properties.size = json_properties["size"];
			properties.alignment = json_properties["alignment"];
			properties.type_flags = json_properties["type_flags"];
		}

		this->type_transcripts[properties.id] = properties;
	}
}

void utils::hkTypeTranscriptor::DeserializeTranscripts(std::string path, bool throw_if_not_exist) {
	std::ifstream file(path);

	if (!file.is_open()) {
		if (throw_if_not_exist) {
			throw std::runtime_error("File not found: " + path);
		}
		std::cout << "File not found: " << path << std::endl;
		return;
	}

	nlohmann::json json;
	file >> json;
	file.close();

	DeserializeTranscripts(json);
}
