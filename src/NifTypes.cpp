#include "NifTypes.h"

void nif::NiNode::Deserialize(std::istream& file)
{
	NiObject::Deserialize(file);

	this->num_children = Util::readUInt32(file)[0];
	for (int j = 0; j < this->num_children; j++)
		this->children.push_back(Util::readUInt32(file)[0]);
}

void nif::NiNode::Serialize(std::ostream& file)
{
	NiObject::Serialize(file);

	Util::writeAsHex(file, this->num_children);
	for (int j = 0; j < this->num_children; j++)
		Util::writeAsHex(file, this->children[j]);
}

size_t nif::NiNode::GetSize()
{
	return NiObject::GetSize() + 4 + 4 * this->num_children;
}

void nif::BSXFlags::Deserialize(std::istream& file)
{
	this->name_index = Util::readUInt32(file)[0];
	this->flags = Util::readUInt32(file)[0];
}

void nif::BSXFlags::Serialize(std::ostream& file)
{
	Util::writeAsHex(file, this->name_index);
	Util::writeAsHex(file, this->flags);
}

size_t nif::BSXFlags::GetSize()
{
	return 8;
}

void nif::NiObject::Deserialize(std::istream& file)
{
	this->name_index = Util::readUInt32(file)[0];

	this->num_extra_data = Util::readUInt32(file)[0];
	for (int j = 0; j < this->num_extra_data; j++)
		this->extra_data.push_back(Util::readUInt32(file)[0]);

	this->controller_index = Util::readUInt32(file)[0];
	this->flags = Util::readUInt32(file)[0];

	this->translation[0] = Util::readFloat(file)[0];
	this->translation[1] = Util::readFloat(file)[0];
	this->translation[2] = Util::readFloat(file)[0];

	std::memcpy(this->rotation, Util::readFloat(file, 9).data(), 9 * sizeof(float));

	this->scale = Util::readFloat(file)[0];

	this->collision_object = Util::readUInt32(file)[0];
}

void nif::NiObject::Serialize(std::ostream& file)
{
	Util::writeAsHex(file, this->name_index);

	Util::writeAsHex(file, this->num_extra_data);
	for (int j = 0; j < this->num_extra_data; j++)
		Util::writeAsHex(file, this->extra_data[j]);

	Util::writeAsHex(file, this->controller_index);
	Util::writeAsHex(file, this->flags);

	Util::writeAsHex(file, this->translation[0]);
	Util::writeAsHex(file, this->translation[1]);
	Util::writeAsHex(file, this->translation[2]);

	Util::writeAsHex(file, this->rotation[0][0]);
	Util::writeAsHex(file, this->rotation[0][1]);
	Util::writeAsHex(file, this->rotation[0][2]);
	Util::writeAsHex(file, this->rotation[1][0]);
	Util::writeAsHex(file, this->rotation[1][1]);
	Util::writeAsHex(file, this->rotation[1][2]);
	Util::writeAsHex(file, this->rotation[2][0]);
	Util::writeAsHex(file, this->rotation[2][1]);
	Util::writeAsHex(file, this->rotation[2][2]);

	Util::writeAsHex(file, this->scale);

	Util::writeAsHex(file, this->collision_object);
}

size_t nif::NiObject::GetSize()
{
	return 4 * this->num_extra_data + 72;
}

void nif::BSGeometry::Deserialize(std::istream& file)
{
	NiObject::Deserialize(file);

	std::memcpy(this->center, Util::readFloat(file, 3).data(), 3 * sizeof(float));

	this->radius = Util::readFloat(file)[0];

	std::memcpy(this->minmax, Util::readFloat(file, 6).data(), 6 * sizeof(float));

	this->skin_instance = Util::readUInt32(file)[0];
	this->shader_property = Util::readUInt32(file)[0];
	this->alpha_property = Util::readUInt32(file)[0];

	for (int i = 0; i < 4; i++) {
		bool has_mesh = Util::readUInt8(file)[0];
		if (has_mesh) {
			MeshData mesh;
			mesh.num_indices = Util::readUInt32(file)[0];
			mesh.num_vertices = Util::readUInt32(file)[0];
			mesh.flags = Util::readUInt32(file)[0];
			mesh.path_length = Util::readUInt32(file)[0];
			mesh.mesh_path = Util::readString(file, mesh.path_length);
			this->meshes.push_back(mesh);
		}
	}
}

void nif::BSGeometry::Serialize(std::ostream& file)
{
	NiObject::Serialize(file);

	Util::writeAsHex(file, this->center[0]);
	Util::writeAsHex(file, this->center[1]);
	Util::writeAsHex(file, this->center[2]);

	Util::writeAsHex(file, this->radius);

	Util::writeAsHex(file, this->minmax[0]);
	Util::writeAsHex(file, this->minmax[1]);
	Util::writeAsHex(file, this->minmax[2]);
	Util::writeAsHex(file, this->minmax[3]);
	Util::writeAsHex(file, this->minmax[4]);
	Util::writeAsHex(file, this->minmax[5]);

	Util::writeAsHex(file, this->skin_instance);
	Util::writeAsHex(file, this->shader_property);
	Util::writeAsHex(file, this->alpha_property);

	for (int i = 0; i < 4; i++) {
		if (i < this->meshes.size()) {
			uint8_t has_mesh = 1;
			Util::writeAsHex(file, has_mesh);
			Util::writeAsHex(file, this->meshes[i].num_indices);
			Util::writeAsHex(file, this->meshes[i].num_vertices);
			Util::writeAsHex(file, this->meshes[i].flags);
			Util::writeAsHex(file, this->meshes[i].path_length);
			Util::writeString(file, this->meshes[i].mesh_path);
		}
		else {
			uint8_t has_mesh = 0;
			Util::writeAsHex(file, has_mesh);
		}
	}
}

size_t nif::BSGeometry::GetSize()
{
	size_t count = 0;
	for (auto& mesh : this->meshes) {
		count += 16 + mesh.path_length;
	}
	return NiObject::GetSize() + 56 + count;
}

void nif::NiIntegerExtraData::Deserialize(std::istream& file)
{
	this->name_index = Util::readUInt32(file)[0];
	this->data = Util::readUInt32(file)[0];
}

void nif::NiIntegerExtraData::Serialize(std::ostream& file)
{
	Util::writeAsHex(file, this->name_index);
	Util::writeAsHex(file, this->data);
}

size_t nif::NiIntegerExtraData::GetSize()
{
	return 8;
}

void nif::SkinAttach::Deserialize(std::istream& file)
{
	this->name_index = Util::readUInt32(file)[0];
	this->num_bone_names = Util::readUInt32(file)[0];

	for (int i = 0; i < this->num_bone_names; i++) {
		auto length = Util::readUInt32(file)[0];
		this->bone_names.push_back(Util::readString(file, length));
	}
}

void nif::SkinAttach::Serialize(std::ostream& file)
{
	Util::writeAsHex(file, this->name_index);
	Util::writeAsHex(file, this->num_bone_names);

	for (int i = 0; i < this->num_bone_names; i++) {
		uint32_t length = this->bone_names[i].length();
		Util::writeAsHex(file, length);
		Util::writeString(file, this->bone_names[i]);
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
	this->skeleton_root = Util::readUInt32(file)[0];
	this->bone_data = Util::readUInt32(file)[0];

	this->num_bone_attrs = Util::readUInt32(file)[0];
	for (int i = 0; i < this->num_bone_attrs; ++i) {
		this->bone_attrs.push_back(Util::readUInt32(file)[0]);
	}

	this->num_bone_scales = Util::readUInt32(file)[0];
	for (int i = 0; i < this->num_bone_scales; ++i) {
		this->bone_scales.push_back(Util::readFloat(file)[0]);
	}

}

void nif::BSSkin::Instance::Serialize(std::ostream& file)
{
	Util::writeAsHex(file, this->skeleton_root);
	Util::writeAsHex(file, this->bone_data);

	Util::writeAsHex(file, this->num_bone_attrs);
	for (int i = 0; i < this->num_bone_attrs; ++i) {
		Util::writeAsHex(file, this->bone_attrs[i]);
	}

	Util::writeAsHex(file, this->num_bone_scales);
	for (int i = 0; i < this->num_bone_scales; ++i) {
		Util::writeAsHex(file, this->bone_scales[i]);
	}

}

size_t nif::BSSkin::Instance::GetSize()
{
	return 16 + 4 * (this->num_bone_attrs + this->num_bone_scales);
}

void nif::BSLightingShaderProperty::Deserialize(std::istream& file)
{
	this->name_index = Util::readUInt32(file)[0];
	this->num_extra_data = Util::readUInt32(file)[0];
	for (int i = 0; i < this->num_extra_data; ++i) {
		this->extra_data.push_back(Util::readUInt32(file)[0]);
	}

	this->controller = Util::readUInt32(file)[0];
}

void nif::BSLightingShaderProperty::Serialize(std::ostream& file)
{
	Util::writeAsHex(file, this->name_index);
	Util::writeAsHex(file, this->num_extra_data);
	for (int i = 0; i < this->num_extra_data; ++i) {
		Util::writeAsHex(file, this->extra_data[i]);
	}

	Util::writeAsHex(file, this->controller);
}

size_t nif::BSLightingShaderProperty::GetSize()
{
	return 12 + 4 * this->num_extra_data;
}

void nif::BSSkin::BoneData::Deserialize(std::istream& file)
{
	this->num_bone_infos = Util::readUInt32(file)[0];
	for (int i = 0; i < this->num_bone_infos; ++i) {
		BoneInfo bone_info;
		std::memcpy(&bone_info, Util::readFloat(file, 17).data(), 17 * sizeof(float));
		this->bone_infos.push_back(bone_info);
	}
}

void nif::BSSkin::BoneData::Serialize(std::ostream& file)
{
	Util::writeAsHex(file, this->num_bone_infos);
	for (int i = 0; i < this->num_bone_infos; ++i) {
		Util::writeStream(file, &this->bone_infos[i], 17 * sizeof(float));
	}
}

size_t nif::BSSkin::BoneData::GetSize()
{
	return 4 + sizeof(BoneInfo) * this->num_bone_infos;
}