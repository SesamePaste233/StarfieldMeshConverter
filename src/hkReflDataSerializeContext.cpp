#include "hkReflDataSerializeContext.h"

bool hkphysics::hkReflDataDeserializer::Deserialize(const std::string filename)
{
	std::ifstream file(filename, std::ios::binary);
	if (!file.is_open()) {
		return false;
	}

	uint32_t size = utils::read<uint32_t>(file)[0];

	return this->Deserialize(file, size);
}

bool hkphysics::hkReflDataDeserializer::Deserialize(std::istream& data_stream, size_t data_size)
{
	const uint8_t* _file_buffer = utils::readBytes(data_stream, data_size);

	return Deserialize(_file_buffer, data_size);
}

bool hkphysics::hkReflDataDeserializer::Deserialize(const uint8_t* data, size_t data_size)
{
	this->Clear();

	this->data_size = (uint32_t)data_size;

	utils::DataAccessor _accessor = utils::DataAccessor::Create(data, this->data_size, true);

	hkDataChunkTAG0* chunk = new hkDataChunkTAG0(this);

	chunk->SetBuffer(_accessor.make_reference());

	size_t cur_pos = 0;
	uint32_t sizeAndFlags = utils::readFromAccessor<uint32_t>(_accessor, cur_pos, true); // Size and flags
	chunk->chunk_decorator = sizeAndFlags >> 24; // Decorator
	chunk->data_size = sizeAndFlags & 0x00FFFFFF; // Data size

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

	// Root level instance
	auto suc = this->indexed_blocks[1]->BuildInstances();
	if (!suc) {
		std::cout << "Warning: root level instance build failed." << std::endl;
		return false;
	}

	for (auto block = this->indexed_blocks.begin() + 1; block != this->indexed_blocks.end(); block++) {
		if((*block)->_built)
			continue;
		std::cout << "Warning: bogus block detected." << std::endl;
		return false;
	}

	if (this->indexed_blocks[1]->m_instances.size() != 1) {
		std::cout << "Warning: root level instance count is not 1." << std::endl;
		return false;
	}

	this->root_level_instance = this->indexed_blocks[1]->m_instances[0];

	auto root_ctn_insts = this->GetInstancesByClassName("hkRootLevelContainer");
	if (root_ctn_insts.size() == 1) {
		this->root_level_container = new hktypes::hkRootLevelContainer();
		root_ctn_insts[0]->GetValue(*this->root_level_container);
	}

	return true;
}

void hkphysics::hkReflDataDeserializer::ExtractClasses()
{
	auto root_ctn_insts = this->GetInstancesByClassName("hkRootLevelContainer");
	if (root_ctn_insts.size() == 1) {
		this->root_level_container = new hktypes::hkRootLevelContainer();
		root_ctn_insts[0]->GetValue(*this->root_level_container);
	}
}

bool hkphysics::hkReflDataSerializeContext::RegisterPatch(hkreflex::hkClassBase* type, uint32_t patch_offset)
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

utils::DataAccessor hkphysics::hkReflDataSerializeContext::GetDataPtr(uint32_t offset){
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->GetData() + offset;
}

utils::DataAccessor hkphysics::hkReflDataSerializeContext::AllocateSerializeData(size_t size){
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->AllocateSerializeData(size);
}

void hkphysics::hkReflDataSerializeContext::SetTrueAllocSize(size_t size)
{
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->SetTrueAllocatedSize(size);
}

utils::DataAccessor hkphysics::hkReflDataSerializeContext::GetSerializeDataPtr(uint32_t offset){
	return dynamic_cast<hkDataChunkDATA*>(this->data_chunks[ChunkType::DATA])->GetSerializeData() + offset;
}

void hkphysics::hkReflDataSerializeContext::_build_data_chunks()
{
	for (auto& chunk : data_chunks) {
		delete chunk.second;
		chunk.second = nullptr;
	}
	data_chunks.clear();
	this->data_chunks.emplace(ChunkType::TAG0, new hkDataChunkTAG0(this));
	this->data_chunks.emplace(ChunkType::SDKV, new hkDataChunkSDKV(this));
	this->data_chunks.emplace(ChunkType::DATA, new hkDataChunkDATA(this));
	this->data_chunks.emplace(ChunkType::TYPE, new hkDataChunkTYPE(this));
	this->data_chunks.emplace(ChunkType::TPTR, new hkDataChunkTPTR(this));
	this->data_chunks.emplace(ChunkType::TST1, new hkDataChunkTST1(this));
	this->data_chunks.emplace(ChunkType::TNA1, new hkDataChunkTNA1(this));
	this->data_chunks.emplace(ChunkType::FST1, new hkDataChunkFST1(this));
	this->data_chunks.emplace(ChunkType::TBDY, new hkDataChunkTBDY(this));
	this->data_chunks.emplace(ChunkType::THSH, new hkDataChunkTHSH(this));
	this->data_chunks.emplace(ChunkType::TPAD, new hkDataChunkTPAD(this));
	this->data_chunks.emplace(ChunkType::INDX, new hkDataChunkINDX(this));
	this->data_chunks.emplace(ChunkType::ITEM, new hkDataChunkITEM(this));
	this->data_chunks.emplace(ChunkType::PTCH, new hkDataChunkPTCH(this));
	this->data_chunks[ChunkType::TAG0]->children = {
		this->data_chunks[ChunkType::SDKV],
		this->data_chunks[ChunkType::DATA],
		this->data_chunks[ChunkType::TYPE],
		this->data_chunks[ChunkType::INDX],
	};
	this->data_chunks[ChunkType::TYPE]->children = {
		this->data_chunks[ChunkType::TPTR],
		this->data_chunks[ChunkType::TST1],
		this->data_chunks[ChunkType::TNA1],
		this->data_chunks[ChunkType::FST1],
		this->data_chunks[ChunkType::TBDY],
		this->data_chunks[ChunkType::THSH],
		this->data_chunks[ChunkType::TPAD],
	};
	this->data_chunks[ChunkType::INDX]->children = {
		this->data_chunks[ChunkType::ITEM],
		this->data_chunks[ChunkType::PTCH],
	};
}

void hkphysics::hkReflDataSerializeContext::SaveToCxxCode()
{
	std::map<std::string, std::string> header_strings;
	std::map<std::string, std::vector<std::string>> header_template_args;
	std::map<std::string, std::string> source_strings;
	std::map<std::string, std::set<hkreflex::hkClassBase*>> extra_includes;

	for (auto& hk_class : this->classes) {
		if (hk_class->_defined == false) {
			// No undeclared classes
			continue;
		}
		if (hk_class->is_nested_class) {
			// No nested classes
			continue;
		}
		//if (hk_class->template_args.size() != 0) {
		//	// No template classes
		//	continue;
		//}
		if (hk_class->kind != hkreflex::hkClassBase::TypeKind::Record
			&& hktypes::hkTypeMapper::IsMapped(hk_class)
			) {
			// Record classes only
			continue;
		}
		if (hktypes::hkTypeMapper::IsBasicTypes(hk_class)) {
			// No basic types
			continue;
		}
		std::string hk_class_definition = "";
		std::set<hkreflex::hkClassBase*> ref_types;

		auto def_str = hk_class->to_C_class_definition(ref_types, 1);
		header_strings[hk_class->type_name] += def_str + "\n";
		auto& lst = extra_includes[hk_class->type_name];
		lst.insert(ref_types.begin(), ref_types.end());

		std::vector<std::string> h_template_args;
		for (auto& template_arg : hk_class->template_args) {
			h_template_args.push_back(template_arg->template_arg_name);
		}

		header_template_args[hk_class->type_name] = h_template_args;

		std::string hk_class_definition_cpp = "";
		hk_class_definition_cpp += hk_class->to_C_FromInstance();
		hk_class_definition_cpp += hk_class->to_C_ToInstance();
		hk_class_definition_cpp += hk_class->to_C_GetTemplateArgs();
		//hk_class_definition_cpp += hk_class->to_C_GetFieldTypeAndNames();
		//hk_class_definition_cpp += hk_class->to_C_GetPropertyBag();

		source_strings[hk_class->type_name] += hk_class_definition_cpp;
	}

	auto header_strings_iter = header_strings.begin();
	auto source_strings_iter = source_strings.begin();
	for (int i = 0; i < header_strings.size(); ++i) {
		auto& header = *(header_strings_iter++);
		auto& source = *(source_strings_iter++);
		auto& ref_types = extra_includes[header.first];
		auto& header_t_args = header_template_args[header.first];

		std::string hk_class_definition = "";
		hk_class_definition += "#pragma once\n";
		hk_class_definition += "#include \"hkInclude.h\"\n\n";
		hk_class_definition += "\nnamespace hktypes{\n";
		for (auto& ref_type : ref_types) {
			if (ref_type->template_args.size() == 0) {
				hk_class_definition += "\tclass " + ref_type->to_C_identifier() + ";\n";
			}
			else {
				hk_class_definition += "\ttemplate <";
				for (int i = 0; i < ref_type->template_args.size(); i++) {
					hk_class_definition += "typename " + ref_type->template_args[i]->template_arg_name;
					if (i != ref_type->template_args.size() - 1) {
						hk_class_definition += ", ";
					}
				}
				hk_class_definition += ">\n";
				hk_class_definition += "\tclass " + ref_type->nested_parent_type_name + ";\n";
			}
		}
		hk_class_definition += "\n";

		if (!header_t_args.empty()) {
			hk_class_definition += "\ttemplate <";
			for (int i = 0; i < header_t_args.size(); i++) {
				hk_class_definition += "typename " + header_t_args[i];
				if (i != header_t_args.size() - 1) {
					hk_class_definition += ", ";
				}
			}
			hk_class_definition += ">\n";
			hk_class_definition += "\tclass " + header.first + ";\n";
		}

		hk_class_definition += header.second;
		hk_class_definition += "}\n";
		std::ofstream file("C:\\repo\\MeshConverter\\include\\Generated\\" + header.first + ".h");
		file << hk_class_definition;
		file.close();

		std::string hk_class_definition_cpp = "";
		hk_class_definition_cpp += "#include \"Generated\\" + source.first + ".h\"\n\n";
		for (auto& ref_type : ref_types) {
			hk_class_definition_cpp += "#include \"Generated\\" + ref_type->nested_parent_type_name + ".h\"\n";
		}
		hk_class_definition_cpp += "\n" + source.second;
		std::ofstream file1("C:\\repo\\MeshConverter\\src\\Generated\\" + source.first + ".cpp");
		file1 << hk_class_definition_cpp;
		file1.close();
	}
}

bool hkphysics::hkReflDataSerializeContext::CompareClasses(hkReflDataSerializeContext& other)
{
	std::vector<std::string> data_classes_identifiers;
	for (auto& hk_class : this->classes) {
		auto id = hk_class->to_C_identifier();
		if (id != "") {
			data_classes_identifiers.push_back(id);
		}
	}
	std::vector<std::string> serialize_classes_identifiers;
	for (auto& hk_class : other.classes) {
		auto id = hk_class->to_C_identifier();
		if (id != "") {
			serialize_classes_identifiers.push_back(id);
		}
	}
	/*int size = data_classes_identifiers.size() < serialize_classes_identifiers.size() ? data_classes_identifiers.size() : serialize_classes_identifiers.size();
	for (int i = 0; i < size; i++) {
		std::cout << data_classes_identifiers[i] << " <-> " << serialize_classes_identifiers[i] << std::endl;
	}*/
	bool missing_classes = false;
	for (auto& data_id : data_classes_identifiers) {
		if (std::find(serialize_classes_identifiers.begin(), serialize_classes_identifiers.end(), data_id) == serialize_classes_identifiers.end()) {
			std::cout << data_id << " is not in serialize classes" << std::endl;
			missing_classes = true;
		}
	}
	return missing_classes;
}

std::vector<hkreflex::hkClassBase*> hkphysics::hkReflDataSerializeContext::GetClassByName(const std::string& name)
{
	std::vector<hkreflex::hkClassBase*> ret;
	for (auto it = classes.begin() + 1; it != classes.end(); ++it) {
		if ((*it)->type_name == name) {
			ret.push_back(*it);
		}
	}
	return ret;
}

std::string hkphysics::hkReflDataSerializeContext::classes_to_literal(bool show_members, bool use_mapped_ctype, bool inverse_order)
{
	std::string ret = "";
	ret = "#pragma once\n\n";
	ret += "#include \"hkBaseCTypes.h\"\n";

	if (inverse_order) {
		size_t i = classes.size();
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

std::string hkphysics::hkReflDataSerializeContext::dump_indexed_blocks()
{
	std::string ret = "";
	for (auto it = indexed_blocks.begin() + 1; it != indexed_blocks.end(); ++it) {
		if ((*it)->_dumped == false)
			ret += (*it)->dump_instances(0, false, false) + "\n";
	}
	return ret;
}

std::vector<hkreflex::hkClassInstance*> hkphysics::hkReflDataSerializeContext::GetInstancesByClassName(const std::string& name)
{
	std::vector<hkreflex::hkClassInstance*> ret;
	for (auto it = indexed_blocks.begin() + 1; it != indexed_blocks.end(); ++it) {
		if ((*it)->m_data_type->type_name == name) {
			for (auto instance : (*it)->m_instances) {
				ret.push_back(instance);
			}
		}
	}
	return ret;
}

bool hkphysics::hkReflDataSerializeContext::RegisterClassesToTranscriptor() {
	bool updated = false;
	for (int i = 1; i < this->classes.size(); i++) {
		if (hkreflex::hkTypeTranscriptor::GetInstance().RegisterClass(this->classes[i], true, false)) {
			std::cout << "Registered or updated " << this->classes[i]->to_C_identifier() << std::endl;
			updated = true;
		}
		else {
		}
	}
	return updated;
}

size_t hkphysics::hkReflDataSerializer::Serialize(std::ostream& data_stream)
{
	this->Clear();
	this->serialize_string_table.clear();

	this->_build_data_chunks();

	auto& transcriptor = hkreflex::hkTypeTranscriptor::GetInstance();

	this->root_level_instance = transcriptor.Instantiate(*this->root_level_container, this);

	if (!this->root_level_instance) {
		std::cout << "Warning: root level container instantiation failed." << std::endl;
		return false;
	}

	if (!this->root_level_container->ToInstance(this->root_level_instance)) {
		std::cout << "Warning: root level instance build failed." << std::endl;
		return false;
	}

	this->classes.push_back(new hkreflex::hkClassBase());
	this->root_level_instance->CollectSerializeClasses(this->classes);

	for (auto type = this->classes.begin() + 1; type != this->classes.end(); type++) {
		auto& t_name = (*type)->type_name;
		if (std::find(this->type_names.begin(), this->type_names.end(), t_name) == this->type_names.end()) {
			this->type_names.push_back(t_name);
		}

		for (auto template_type = (*type)->template_args.begin(); template_type != (*type)->template_args.end(); template_type++) {
			auto& tt_name = (*template_type)->template_arg_name;
			if (std::find(this->type_names.begin(), this->type_names.end(), tt_name) == this->type_names.end()) {
				this->type_names.push_back(tt_name);
			}
		}

		for (auto field = (*type)->fields.begin(); field != (*type)->fields.end(); field++) {
			auto& f_name = (*field)->name;
			if (std::find(this->field_names.begin(), this->field_names.end(), f_name) == this->field_names.end()) {
				this->field_names.push_back(f_name);
			}
		}
	}
	
	uint64_t cur_block_index = 0;
	
	size_t alloc_size = this->root_level_instance->GetSerializeSize() * 4;
	
	auto out_accessor = this->AllocateSerializeData(alloc_size);
	
	size_t true_alloc = 0;
	
	hkreflex::hkIndexedDataBlock* root_block = hkreflex::hkIndexedDataBlock::CreatePointerAndAlloc(this, this->root_level_instance->type, this->root_level_instance);
		
	utils::SerializePool serializer(1);
	serializer.QueueSerialization(root_block, true);
	cur_block_index = serializer.Resolve(out_accessor.make_reference(), true_alloc);
		
	this->indexed_blocks.push_back(new hkreflex::hkIndexedDataBlock(this));
	for (auto block : serializer.serialized_objects) {
		this->indexed_blocks.push_back(dynamic_cast<hkreflex::hkIndexedDataBlock*>(block));
	}

	this->SetTrueAllocSize(true_alloc);

	auto tag0 = dynamic_cast<hkDataChunkTAG0*>(this->data_chunks[ChunkType::TAG0]);

	utils::DataAccessor result;
	auto size = (uint32_t)tag0->DistributeAndSerialize(result, true);

	data_stream.write((const char*)result.data, result.size);

	return size;
}
