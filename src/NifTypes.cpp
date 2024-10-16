#include "NifTypes.h"
#include "NifIO.h"

void nif::NiNode::Deserialize(std::istream& file)
{
	NiObject::Deserialize(file);

	this->num_children = utils::read<uint32_t>(file)[0];
	for (uint32_t j = 0; j < this->num_children; j++)
		this->children.push_back(utils::read<uint32_t>(file)[0]);
}

void nif::NiNode::Serialize(std::ostream& file)
{
	NiObject::Serialize(file);

	utils::writeAsHex(file, this->num_children);
	for (uint32_t j = 0; j < this->num_children; j++)
		utils::writeAsHex(file, this->children[j]);
}

size_t nif::NiNode::GetSize()
{
	return NiObject::GetSize() + 4 + 4 * this->num_children;
}

void nif::BSXFlags::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	this->flags = utils::read<uint32_t>(file)[0];
}

void nif::BSXFlags::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->flags);
}

size_t nif::BSXFlags::GetSize()
{
	return 8;
}

void nif::NiObject::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];

	this->num_extra_data = utils::read<uint32_t>(file)[0];
	for (uint32_t j = 0; j < this->num_extra_data; j++)
		this->extra_data.push_back(utils::read<uint32_t>(file)[0]);

	this->controller_index = utils::read<uint32_t>(file)[0];
	this->flags = utils::read<uint32_t>(file)[0];

	this->translation[0] = utils::read<float>(file)[0];
	this->translation[1] = utils::read<float>(file)[0];
	this->translation[2] = utils::read<float>(file)[0];

	std::memcpy(this->rotation, utils::read<float>(file, 9).data(), 9 * sizeof(float));

	this->scale = utils::read<float>(file)[0];

	this->collision_object = utils::read<uint32_t>(file)[0];
}

void nif::NiObject::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);

	utils::writeAsHex(file, this->num_extra_data);
	for (uint32_t j = 0; j < this->num_extra_data; j++)
		utils::writeAsHex(file, this->extra_data[j]);

	utils::writeAsHex(file, this->controller_index);
	utils::writeAsHex(file, this->flags);

	utils::writeAsHex(file, this->translation[0]);
	utils::writeAsHex(file, this->translation[1]);
	utils::writeAsHex(file, this->translation[2]);

	utils::writeAsHex(file, this->rotation[0][0]);
	utils::writeAsHex(file, this->rotation[0][1]);
	utils::writeAsHex(file, this->rotation[0][2]);
	utils::writeAsHex(file, this->rotation[1][0]);
	utils::writeAsHex(file, this->rotation[1][1]);
	utils::writeAsHex(file, this->rotation[1][2]);
	utils::writeAsHex(file, this->rotation[2][0]);
	utils::writeAsHex(file, this->rotation[2][1]);
	utils::writeAsHex(file, this->rotation[2][2]);

	utils::writeAsHex(file, this->scale);

	utils::writeAsHex(file, this->collision_object);
}

size_t nif::NiObject::GetSize()
{
	return 4 * this->num_extra_data + 72;
}

void nif::BSGeometry::Deserialize(std::istream& file)
{
	NiObject::Deserialize(file);

	std::memcpy(this->center, utils::read<float>(file, 3).data(), 3 * sizeof(float));

	this->radius = utils::read<float>(file)[0];

	std::memcpy(this->bbox_center_expand, utils::read<float>(file, 6).data(), 6 * sizeof(float));

	this->skin_instance = utils::read<uint32_t>(file)[0];
	this->shader_property = utils::read<uint32_t>(file)[0];
	this->alpha_property = utils::read<uint32_t>(file)[0];

	for (int i = 0; i < 4; i++) {
		bool has_mesh = utils::read<uint8_t>(file)[0];
		if (has_mesh) {
			MeshData mesh;
			mesh.num_indices = utils::read<uint32_t>(file)[0];
			mesh.num_vertices = utils::read<uint32_t>(file)[0];
			mesh.flags = utils::read<uint32_t>(file)[0];
			if (this->_use_internal_geom_data()) {
				if (mesh.mesh_data.Deserialize(file)) {
					mesh.path_length = 0;
					mesh.mesh_path = "";
				}
				else {
					std::cout << "Failed to deserialize mesh data." << std::endl;
				}
			}
			else {
				mesh.path_length = utils::read<uint32_t>(file)[0];
				mesh.mesh_path = utils::readString(file, mesh.path_length);
			}
			this->meshes.push_back(mesh);
		}
	}
}

void nif::BSGeometry::Serialize(std::ostream& file)
{
	size_t start_pos = file.tellp();
	NiObject::Serialize(file);

	utils::writeAsHex(file, this->center[0]);
	utils::writeAsHex(file, this->center[1]);
	utils::writeAsHex(file, this->center[2]);

	utils::writeAsHex(file, this->radius);

	utils::writeAsHex(file, this->bbox_center_expand[0]);
	utils::writeAsHex(file, this->bbox_center_expand[1]);
	utils::writeAsHex(file, this->bbox_center_expand[2]);
	utils::writeAsHex(file, this->bbox_center_expand[3]);
	utils::writeAsHex(file, this->bbox_center_expand[4]);
	utils::writeAsHex(file, this->bbox_center_expand[5]);

	utils::writeAsHex(file, this->skin_instance);
	utils::writeAsHex(file, this->shader_property);
	utils::writeAsHex(file, this->alpha_property);

	for (int i = 0; i < 4; i++) {
		if (i < this->meshes.size()) {
			uint8_t has_mesh = 1;
			utils::writeAsHex(file, has_mesh);
			utils::writeAsHex(file, this->meshes[i].num_indices);
			utils::writeAsHex(file, this->meshes[i].num_vertices);
			utils::writeAsHex(file, this->meshes[i].flags);

			if (this->_use_internal_geom_data()){
				this->meshes[i].mesh_data.Serialize(file);
			}
			else {
				this->meshes[i].path_length = (uint32_t)this->meshes[i].mesh_path.length();
				utils::writeAsHex(file, this->meshes[i].path_length);
				utils::writeString(file, this->meshes[i].mesh_path);
			}
		}
		else {
			uint8_t has_mesh = 0;
			utils::writeAsHex(file, has_mesh);
		}
	}

	this->_size = (size_t)file.tellp() - start_pos;
}

size_t nif::BSGeometry::GetSize()
{
	return this->_size;
}

void nif::NiIntegerExtraData::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	this->data = utils::read<uint32_t>(file)[0];
}

void nif::NiIntegerExtraData::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->data);
}

size_t nif::NiIntegerExtraData::GetSize()
{
	return 8;
}

void nif::SkinAttach::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	this->num_bone_names = utils::read<uint32_t>(file)[0];

	for (uint32_t i = 0; i < this->num_bone_names; i++) {
		auto length = utils::read<uint32_t>(file)[0];
		this->bone_names.push_back(utils::readString(file, length));
	}
}

void nif::SkinAttach::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->num_bone_names);

	for (uint32_t i = 0; i < this->num_bone_names; i++) {
		uint32_t length = (uint32_t)this->bone_names[i].length();
		utils::writeAsHex(file, length);
		utils::writeString(file, this->bone_names[i]);
	}
}

size_t nif::SkinAttach::GetSize()
{
	size_t count = 0;
	for (auto& name : this->bone_names) {
		count += 4 + name.length();
	}
	return 8 + count;
}

void nif::BSSkin::Instance::Deserialize(std::istream& file)
{
	this->skeleton_root = utils::read<uint32_t>(file)[0];
	this->bone_data = utils::read<uint32_t>(file)[0];

	this->num_bone_attachs = utils::read<uint32_t>(file)[0];
	for (uint32_t i = 0; i < this->num_bone_attachs; ++i) {
		this->bone_attach_refs.push_back(utils::read<uint32_t>(file)[0]);
	}

	this->num_bone_scales = utils::read<uint32_t>(file)[0];
	for (uint32_t i = 0; i < this->num_bone_scales; ++i) {
		this->bone_scales.push_back(utils::read<float>(file)[0]);
	}

}

void nif::BSSkin::Instance::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->skeleton_root);
	utils::writeAsHex(file, this->bone_data);

	utils::writeAsHex(file, this->num_bone_attachs);
	for (uint32_t i = 0; i < this->num_bone_attachs; ++i) {
		utils::writeAsHex(file, this->bone_attach_refs[i]);
	}

	utils::writeAsHex(file, this->num_bone_scales);
	for (uint32_t i = 0; i < this->num_bone_scales; ++i) {
		utils::writeAsHex(file, this->bone_scales[i]);
	}

}

size_t nif::BSSkin::Instance::GetSize()
{
	return 16 + 4 * (this->num_bone_attachs + this->num_bone_scales);
}

std::vector<std::pair<std::string, std::string>> nif::BSSkin::Instance::GetBoneAttachRefStringPairs(const nif::NifIO& belonged_nif) const
{
	std::vector<std::pair<std::string, std::string>> ret;
	auto parent_candidates = belonged_nif.GetParentBlocks(this, NiRTTI::BSGeometry);
	if (parent_candidates.size() != 1) {
		throw std::runtime_error("Failed to find parent geometry block.");
	}

	auto bsgeo = dynamic_cast<BSGeometry*>(parent_candidates[0]);

	auto skin_attachs = belonged_nif.GetReferencedBlocks(bsgeo, NiRTTI::SkinAttach, true, "SkinBMP");
	if (skin_attachs.size() != 1) {
		throw std::runtime_error("Failed to find skin attach block.");
	}
	auto skin_attach = dynamic_cast<SkinAttach*>(skin_attachs[0]);

	if (skin_attach->num_bone_names != this->num_bone_attachs) {
		throw std::runtime_error("Bone attach count mismatch.");
	}

	uint32_t i = 0;
	for (auto attach_ref : bone_attach_refs) {
		ret.push_back(std::make_pair(skin_attach->bone_names[i], belonged_nif.GetBlockName(attach_ref)));
		++i;
	}

	return ret;
}

void nif::BSSkin::Instance::FromBoneAttachRefStringPairs(const std::vector<std::pair<std::string, std::string>>& pairs, nif::NifIO& belonged_nif, bool not_found_ok) {
	std::vector<std::pair<std::string, std::string>> ret;
	auto parent_candidates = belonged_nif.GetParentBlocks(this, NiRTTI::BSGeometry);
	if (parent_candidates.size() != 1) {
		throw std::runtime_error("Failed to find parent geometry block.");
	}

	auto bsgeo = dynamic_cast<BSGeometry*>(parent_candidates[0]);

	auto skin_attachs = belonged_nif.GetReferencedBlocks(bsgeo, NiRTTI::SkinAttach, true, "SkinBMP");
	if (skin_attachs.size() != 1) {
		throw std::runtime_error("Failed to find skin attach block.");
	}
	auto skin_attach = dynamic_cast<SkinAttach*>(skin_attachs[0]);

	if (skin_attach->num_bone_names != this->num_bone_attachs) {
		throw std::runtime_error("Bone attach count mismatch.");
	}

	this->bone_attach_refs.clear();
	this->bone_attach_refs.resize(skin_attach->num_bone_names, this->NO_REF);
	for (auto& pair : pairs) {
		auto& bone_name = pair.first;
		auto& attach_name = pair.second;
		if (attach_name == "") {
			continue;
		}
		for (size_t i = 0; i < skin_attach->num_bone_names; ++i) {
			if (skin_attach->bone_names[i] != bone_name) {
				continue;
			}
			auto ref_candidates = belonged_nif.GetRTTIBlocks(NiRTTI::NiNode, true, attach_name);
			if (ref_candidates.size() != 1) {
				if (not_found_ok) {
					std::cout << "Failed to find block ref for " << attach_name << ". There are :" << ref_candidates.size() << std::endl;
					continue;
				}
				else {
					throw std::runtime_error("Failed to find block ref for " + attach_name);
				}
			}
			auto ref = belonged_nif.block_manager.FindBlock(ref_candidates[0]);
			if (ref == this->NO_REF) {
				if (not_found_ok) {
					std::cout << "Failed to find block ref for " << attach_name << std::endl;
					continue;
				}
				else {
					throw std::runtime_error("Failed to find block ref for " + attach_name);
				}
			}
			this->bone_attach_refs[i] = ref;
			break;
		}
	}
	this->num_bone_attachs = (uint32_t)this->bone_attach_refs.size();

	belonged_nif.UpdateBlockReference(this);
}

void nif::BSLightingShaderProperty::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	this->num_extra_data = utils::read<uint32_t>(file)[0];
	for (uint32_t i = 0; i < this->num_extra_data; ++i) {
		this->extra_data.push_back(utils::read<uint32_t>(file)[0]);
	}

	this->controller = utils::read<uint32_t>(file)[0];
}

void nif::BSLightingShaderProperty::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->num_extra_data);
	for (uint32_t i = 0; i < this->num_extra_data; ++i) {
		utils::writeAsHex(file, this->extra_data[i]);
	}

	utils::writeAsHex(file, this->controller);
}

size_t nif::BSLightingShaderProperty::GetSize()
{
	return 12 + 4 * this->num_extra_data;
}

void nif::BSSkin::BoneData::Deserialize(std::istream& file)
{
	this->num_bone_infos = utils::read<uint32_t>(file)[0];
	for (uint32_t i = 0; i < this->num_bone_infos; ++i) {
		BoneInfo bone_info;
		std::memcpy(&bone_info, utils::read<float>(file, 17).data(), 17 * sizeof(float));
		this->bone_infos.push_back(bone_info);
	}
}

void nif::BSSkin::BoneData::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->num_bone_infos);
	for (uint32_t i = 0; i < this->num_bone_infos; ++i) {
		utils::writeStream(file, &this->bone_infos[i], 17 * sizeof(float));
	}
}

size_t nif::BSSkin::BoneData::GetSize()
{
	return 4 + sizeof(BoneInfo) * this->num_bone_infos;
}

void nif::BoneTranslations::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	this->num_translations = utils::read<uint32_t>(file)[0];

	for (uint32_t i = 0; i < this->num_translations; ++i) {
		uint32_t name_l = utils::read<uint32_t>(file)[0];
		this->bone_translations[i].bone_name = utils::readString(file, name_l);
		std::memcpy(this->bone_translations[i].translation, utils::read<float>(file, 3).data(), 3 * sizeof(float));
	}
}

void nif::BoneTranslations::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->num_translations);

	for (uint32_t i = 0; i < this->num_translations; ++i) {
		uint32_t name_l = (uint32_t)this->bone_translations[i].bone_name.length();
		utils::writeAsHex(file, name_l);
		utils::writeString(file, this->bone_translations[i].bone_name);
		utils::writeStream(file, this->bone_translations[i].translation, 3 * sizeof(float));
	}
}

size_t nif::BoneTranslations::GetSize()
{
	size_t count = 0;
	for (auto& bone : this->bone_translations) {
		count += 4 + bone.bone_name.length() + 12;
	}
	return 8 + count;
}

void nif::BinaryBlock::Deserialize(std::istream& file)
{
	if (this->binary_bytes > 0) {
		this->binary_data = utils::readBytes(file, this->binary_bytes);
	}
}

void nif::BinaryBlock::Serialize(std::ostream& file)
{
	if (this->binary_bytes > 0 && this->binary_data) {
		utils::writeStream(file, this->binary_data, this->binary_bytes);
	}
}

size_t nif::BinaryBlock::GetSize()
{
	return this->binary_bytes;
}

void nif::NiStringExtraData::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	this->string_index = utils::read<uint32_t>(file)[0];
}

void nif::NiStringExtraData::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->string_index);
}

size_t nif::NiStringExtraData::GetSize()
{
	return 8;
}

void nif::NiIntegersExtraData::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	this->num_integers = utils::read<uint32_t>(file)[0];
	for (uint32_t i = 0; i < this->num_integers; ++i) {
		this->integers.push_back(utils::read<uint32_t>(file)[0]);
	}
}

void nif::NiIntegersExtraData::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->num_integers);
	for (uint32_t i = 0; i < this->num_integers; ++i) {
		utils::writeAsHex(file, this->integers[i]);
	}
}

size_t nif::NiIntegersExtraData::GetSize()
{
	return 8 + 4 * this->num_integers;
}

std::string nif::RTTIToString(const NiRTTI& rtti)
{
	switch (rtti) {
	case NiRTTI::NiNodeBase:
		return "NiNodeBase";
	case NiRTTI::NiObject:
		return "NiObject";
	case NiRTTI::NiNode:
		return "NiNode";
	case NiRTTI::BSGeometry:
		return "BSGeometry";
	case NiRTTI::BSXFlags:
		return "BSXFlags";
	case NiRTTI::NiIntegerExtraData:
		return "NiIntegerExtraData";
	case NiRTTI::SkinAttach:
		return "SkinAttach";
	case NiRTTI::BSSkinInstance:
		return "BSSkin::Instance";
	case NiRTTI::BSLightingShaderProperty:
		return "BSLightingShaderProperty";
	case NiRTTI::BSConnectPointParents:
		return "BSConnectPoint::Parents";
	case NiRTTI::BSSkinBoneData:
		return "BSSkin::BoneData";
	case NiRTTI::BoneTranslations:
		return "BoneTranslations";
	case NiRTTI::NiStringExtraData:
		return "NiStringExtraData";
	case NiRTTI::NiIntegersExtraData:
		return "NiIntegersExtraData";
	case NiRTTI::BSBound:
		return "BSBound";
	case NiRTTI::UnkBinaryBlock:
		return "UnkBinaryBlock";
	case NiRTTI::BSClothExtraData:
		return "BSClothExtraData";
	case NiRTTI::bhkPhysicsSystem:
		return "bhkPhysicsSystem";
	case NiRTTI::bhkNPCollisionObject:
		return "bhkNPCollisionObject";
	}

	throw std::runtime_error("Unknown RTTI");
	return "";
}

nif::NiRTTI nif::StringToRTTI(const std::string& rtti)
{
	if (rtti == "NiNodeBase")
		return NiRTTI::NiNodeBase;
	if (rtti == "NiObject")
		return NiRTTI::NiObject;
	if (rtti == "NiNode")
		return NiRTTI::NiNode;
	if (rtti == "BSGeometry")
		return NiRTTI::BSGeometry;
	if (rtti == "BSXFlags")
		return NiRTTI::BSXFlags;
	if (rtti == "NiIntegerExtraData")
		return NiRTTI::NiIntegerExtraData;
	if (rtti == "SkinAttach")
		return NiRTTI::SkinAttach;
	if (rtti == "BSConnectPoint::Parents")
		return NiRTTI::BSConnectPointParents;
	if (rtti == "BSSkin::Instance")
		return NiRTTI::BSSkinInstance;
	if (rtti == "BSLightingShaderProperty")
		return NiRTTI::BSLightingShaderProperty;
	if (rtti == "BSSkin::BoneData")
		return NiRTTI::BSSkinBoneData;
	if (rtti == "BoneTranslations")
		return NiRTTI::BoneTranslations;
	if (rtti == "NiStringExtraData")
		return NiRTTI::NiStringExtraData;
	if (rtti == "NiIntegersExtraData")
		return NiRTTI::NiIntegersExtraData;
	if (rtti == "BSClothExtraData")
		return NiRTTI::BSClothExtraData;
	if (rtti == "BSBound")
		return NiRTTI::BSBound;
	if (rtti == "bhkPhysicsSystem")
		return NiRTTI::bhkPhysicsSystem;
	if (rtti == "bhkNPCollisionObject")
		return NiRTTI::bhkNPCollisionObject;

	return NiRTTI::UnkBinaryBlock;
}

void nif::BSClothExtraData::Deserialize(std::istream& file)
{
	auto pos = file.tellg();
	BinaryBlock::Deserialize(file);
	if (!this->_decode_binary){
		return;
	}
	file.seekg(pos);

	this->data.Clear();
#ifndef _DEBUG
	try {
		this->data_length = utils::read<uint32_t>(file)[0];
		assert(this->binary_bytes == this->data_length + 4);
		this->data.Deserialize(file, this->data_length);
		root_level_container = this->data.root_level_container;
	}
	catch (std::exception& e) {
		std::cout << "Failed to deserialize BSClothExtraData." << std::endl;
		std::cout << e.what() << std::endl;
	}
#else
	this->data_length = utils::read<uint32_t>(file)[0];
	assert(this->binary_bytes == this->data_length + 4);
	this->data.Deserialize(file, this->data_length);
	root_level_container = this->data.root_level_container;
#endif
}

void nif::BSClothExtraData::Serialize(std::ostream& file)
{
	if (this->_decode_binary && this->root_level_container) {
		std::stringstream ss;
		this->data_serializer.Clear();
		this->data_serializer.root_level_container = this->root_level_container;
		this->data_length = this->data_serializer.Serialize(ss);
		this->binary_bytes = this->data_length + 4;
		utils::writeAsHex<uint32_t>(file, this->data_length);
		utils::writeString(file, ss.str());
		return;
	}

	BinaryBlock::Serialize(file);
}

void nif::bhkPhysicsSystem::Deserialize(std::istream& file)
{
	auto pos = file.tellg();
	BinaryBlock::Deserialize(file);
	if (!this->_decode_binary) {
		return;
	}
	file.seekg(pos);

	this->data.Clear();
	try {
		this->data_length = utils::read<uint32_t>(file)[0];
		assert(this->binary_bytes == this->data_length + 4);
		this->data.Deserialize(file, this->data_length);
		root_level_container = this->data.root_level_container;
	}
	catch (std::exception& e) {
		std::cout << "Failed to deserialize bhkPhysicsSystem." << std::endl;
		std::cout << e.what() << std::endl;
	}
}

void nif::bhkPhysicsSystem::Serialize(std::ostream& file)
{
	if (this->_decode_binary && this->root_level_container) {
		std::stringstream ss;
		this->data_serializer.Clear();
		this->data_serializer.root_level_container = this->root_level_container;
		this->data_length = this->data_serializer.Serialize(ss);
		this->binary_bytes = this->data_length + 4;
		utils::writeAsHex<uint32_t>(file, this->data_length);
		utils::writeString(file, ss.str());
		return;
	}

	BinaryBlock::Serialize(file);
}

void nif::bhkNPCollisionObject::Deserialize(std::istream& file)
{
	this->target_ref = utils::read<uint32_t>(file)[0];
	this->flags = utils::read<uint16_t>(file)[0];
	this->physics_system_ref = utils::read<uint32_t>(file)[0];
	this->body_id = utils::read<uint32_t>(file)[0];
}

void nif::bhkNPCollisionObject::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->target_ref);
	utils::writeAsHex(file, this->flags);
	utils::writeAsHex(file, this->physics_system_ref);
	utils::writeAsHex(file, this->body_id);
}

size_t nif::bhkNPCollisionObject::GetSize()
{
	return 14;
}

void nif::BSBound::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	auto nums = utils::read<float>(file, 6);
	std::memcpy(this->center, nums.data(), 3 * sizeof(float));
	std::memcpy(this->dimensions, nums.data() + 3, 3 * sizeof(float));
}

void nif::BSBound::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->center[0]);
	utils::writeAsHex(file, this->center[1]);
	utils::writeAsHex(file, this->center[2]);
	utils::writeAsHex(file, this->dimensions[0]);
	utils::writeAsHex(file, this->dimensions[1]);
	utils::writeAsHex(file, this->dimensions[2]);
}

size_t nif::BSBound::GetSize()
{
	return size_t(28);
}

void nif::BSConnectPointParents::Deserialize(std::istream& file)
{
	this->name_index = utils::read<uint32_t>(file)[0];
	this->num_parents = utils::read<uint32_t>(file)[0];
	for (uint32_t i = 0; i < this->num_parents; ++i) {
		auto length = utils::read<uint32_t>(file)[0];
		auto parent_name = utils::readString(file, length);
		auto child_length = utils::read<uint32_t>(file)[0];
		auto child_name = utils::readString(file, child_length);
		auto nums = utils::read<float>(file, 8);
		ConnectPoint cp = {
			parent_name,
			child_name,
			{ nums[0], nums[1], nums[2], nums[3] },
			{ nums[4], nums[5], nums[6] },
			nums[7]
		};
		this->connect_points.push_back(cp);
	}
}

void nif::BSConnectPointParents::Serialize(std::ostream& file)
{
	utils::writeAsHex(file, this->name_index);
	utils::writeAsHex(file, this->num_parents);
	for (uint32_t i = 0; i < this->num_parents; ++i) {
		uint32_t length = (uint32_t)this->connect_points[i].parent_name.length();
		utils::writeAsHex(file, length);
		utils::writeString(file, this->connect_points[i].parent_name);
		uint32_t child_length = (uint32_t)this->connect_points[i].child_name.length();
		utils::writeAsHex(file, child_length);
		utils::writeString(file, this->connect_points[i].child_name);
		utils::writeAsHex(file, this->connect_points[i].rot_quat[0]);
		utils::writeAsHex(file, this->connect_points[i].rot_quat[1]);
		utils::writeAsHex(file, this->connect_points[i].rot_quat[2]);
		utils::writeAsHex(file, this->connect_points[i].rot_quat[3]);
		utils::writeAsHex(file, this->connect_points[i].translation[0]);
		utils::writeAsHex(file, this->connect_points[i].translation[1]);
		utils::writeAsHex(file, this->connect_points[i].translation[2]);
		utils::writeAsHex(file, this->connect_points[i].scale);
	}
}

size_t nif::BSConnectPointParents::GetSize()
{
	size_t ret = 8;
	for (auto& cp : this->connect_points) {
		ret += cp.GetSize();
	}
	return ret;
}
