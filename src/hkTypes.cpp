#include "hkTypes.h"
#include "hclSimClothData.h"
#include "hclOperator.h"

bool hktypes::hkPackedVector3::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::FromInstance: type_name is not hkPackedVector3" << std::endl;
		return false;
	}

	std::vector<int16_t> _values;
	class_instance->GetInstanceByFieldName("values")->GetValue(_values);

	this->values[0] = _values[0];
	this->values[1] = _values[1];
	this->values[2] = _values[2];
	this->values[3] = _values[3];

	return true;
}

bool hktypes::hkPackedVector3::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::FromInstance: type_name is not hkPackedVector3" << std::endl;
		return false;
	}

	std::vector<int16_t> _values = { this->values[0], this->values[1], this->values[2], this->values[3] };
	class_instance->GetInstanceByFieldName("values")->SetValue(_values);

	return true;
}

Eigen::Vector3f hktypes::hkPackedVector3::ToVector3f()
{
	auto iexp = (int)values[3] << 16;
	auto fexp = *reinterpret_cast<float*>(&iexp);
	auto x = fexp * float((int)values[0] << 16);
	auto y = fexp * float((int)values[1] << 16);
	auto z = fexp * float((int)values[2] << 16);
	return Eigen::Vector3f(x, y, z);
}

hktypes::hkPackedVector3 hktypes::hkPackedVector3::FromVector3f(const Eigen::Vector3f vec)
{
	hkPackedVector3 result;
	float m = vec.maxCoeff();
	uint8_t b = 0;
	int* const exp_ptr = reinterpret_cast<int*>(&m);
	int x = *exp_ptr;
	const int log_2 = ((x >> 23) & 255) - 128;
	x &= ~(255 << 23);
	x += 127 << 23;
	*exp_ptr = x;
	int log2 = (int(m) + 1 + log_2 + 96);
	if (log2 > b) {
		b = log2;
	}
	result.values[3] = b << 7;
	int iexp = b << 23;
	float fexp = *reinterpret_cast<float*>(&iexp);
	result.values[0] = (int32_t)(vec.x() / fexp) >> 16;
	result.values[1] = (int32_t)(vec.y() / fexp) >> 16;
	result.values[2] = (int32_t)(vec.z() / fexp) >> 16;
	return result;
}

bool hktypes::hkMatrix4Holder::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto array_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);
	if (array_instance->type->type_name != "hkMatrix4Impl" && array_instance->type->type_name != "hkTransformf" && array_instance->type->type_name != "hkMatrix4" && array_instance->type->type_name != "hkMatrix4f" && array_instance->type->type_name != "hkMatrix4d") {
		std::cout << "hkMatrix4Holder::FromInstance: type_name is: " << array_instance->type->type_name << std::endl;
		return false;
	}

	std::vector<float> _values;
	array_instance->GetValue(_values);
	for (int i = 0; i < 16; i++) {
		this->values[i] = _values[i];
	}

	return true;
}

bool hktypes::hkMatrix4Holder::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto array_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);
	if (array_instance->type->type_name != "hkMatrix4Impl" && array_instance->type->type_name != "hkTransformf" && array_instance->type->type_name != "hkMatrix4" && array_instance->type->type_name != "hkMatrix4f" && array_instance->type->type_name != "hkMatrix4d") {
		std::cout << "hkMatrix4Holder::ToInstance: type_name is: " << array_instance->type->type_name << std::endl;
		return false;
	}

	std::vector<float> _values = { this->values[0], this->values[1], this->values[2], this->values[3], this->values[4], this->values[5], this->values[6], this->values[7], this->values[8], this->values[9], this->values[10], this->values[11], this->values[12], this->values[13], this->values[14], this->values[15] };
	array_instance->SetValue(_values);

	return true;
}

Eigen::Matrix4f hktypes::hkMatrix4Holder::ToMatrix4f()
{
	Eigen::Matrix4f mat;
	mat << values[0], values[1], values[2], values[3],
		values[4], values[5], values[6], values[7],
		values[8], values[9], values[10], values[11],
		values[12], values[13], values[14], values[15];
	return mat;
}

hktypes::hkMatrix4Holder hktypes::hkMatrix4Holder::FromMatrix4f(const Eigen::Matrix4f mat)
{
	hkMatrix4Holder result;
	result.values[0] = mat(0, 0);
	result.values[1] = mat(0, 1);
	result.values[2] = mat(0, 2);
	result.values[3] = mat(0, 3);
	result.values[4] = mat(1, 0);
	result.values[5] = mat(1, 1);
	result.values[6] = mat(1, 2);
	result.values[7] = mat(1, 3);
	result.values[8] = mat(2, 0);
	result.values[9] = mat(2, 1);
	result.values[10] = mat(2, 2);
	result.values[11] = mat(2, 3);
	result.values[12] = mat(3, 0);
	result.values[13] = mat(3, 1);
	result.values[14] = mat(3, 2);
	result.values[15] = mat(3, 3);
	return result;
}

bool hktypes::hkVector4Holder::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto array_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);
	if (array_instance->type->type_name != "hkVector4Impl" && array_instance->type->type_name != "hkVector4" && array_instance->type->type_name != "hkVector4f" && array_instance->type->type_name != "hkVector4d") {
		std::cout << "hkVector4Holder::FromInstance: type_name is not hkVector4" << std::endl;
		return false;
	}

	std::vector<float> _values;
	array_instance->GetValue(_values);
	for (int i = 0; i < 4; i++) {
		this->values[i] = _values[i];
	}

	return true;
}

bool hktypes::hkVector4Holder::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto array_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);
	if (array_instance->type->type_name != "hkVector4Impl" && array_instance->type->type_name != "hkVector4" && array_instance->type->type_name != "hkVector4f" && array_instance->type->type_name != "hkVector4d") {
		std::cout << "hkVector4Holder::FromInstance: type_name is not hkVector4" << std::endl;
		return false;
	}

	std::vector<float> _values = { this->values[0], this->values[1], this->values[2], this->values[3] };
	array_instance->SetValue(_values);

	return true;
}

Eigen::Vector4f hktypes::hkVector4Holder::ToVector4f()
{
	return Eigen::Vector4f(values[0], values[1], values[2], values[3]);
}

hktypes::hkVector4Holder hktypes::hkVector4Holder::FromVector4f(const Eigen::Vector4f vec)
{
	hkVector4Holder result;
	result.values[0] = vec.x();
	result.values[1] = vec.y();
	result.values[2] = vec.z();
	result.values[3] = vec.w();
	return result;
}

Eigen::Vector3f hktypes::hkVector4Holder::ToVector3f()
{
	return Eigen::Vector3f(values[0], values[1], values[2]);
}

hktypes::hkVector4Holder hktypes::hkVector4Holder::FromVector3f(const Eigen::Vector3f vec)
{
	hkVector4Holder result;
	result.values[0] = vec.x();
	result.values[1] = vec.y();
	result.values[2] = vec.z();
	result.values[3] = 0;
	return result;
}

bool hktypes::hkBitField::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBitField") {
		std::cout << "hkBitField::FromInstance: type_name is not hkBitField" << std::endl;
		return false;
	}

	hkBitFieldBase<hkBitFieldStorage<std::vector<uint32_t>>>::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hkBitField::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkBitField") {
		std::cout << "hkBitField::FromInstance: type_name is not hkBitField" << std::endl;
		return false;
	}

	hkBitFieldBase<hkBitFieldStorage<std::vector<uint32_t>>>::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

std::vector<bool> hktypes::hkBitField::GetMask()
{
	size_t word_size = sizeof(decltype(this->storage.words)::value_type) * 8;
	std::vector<bool> mask;
	for (auto& word: this->storage.words) {
		for (int i = 0; i < word_size; i++) {
			mask.push_back(word & (1 << i));
		}
	}
	mask.resize(this->storage.numBits);
	return mask;
}

void hktypes::hkBitField::SetMask(std::vector<bool>& mask)
{
	size_t word_size = sizeof(decltype(this->storage.words)::value_type) * 8;
	this->storage.words.clear();
	this->storage.numBits = mask.size();
	this->storage.words.resize((mask.size() + word_size - 1) / word_size);
	for (int i = 0; i < mask.size(); i++) {
		if (mask[i]) {
			this->storage.words[i / word_size] |= 1 << (i % word_size);
		}
	}
}

hktypes::hkBitField& hktypes::hkBitField::operator|(const hkBitField& other)
{
	hkBitField ret;
	auto& storage = ret.storage;
	auto& other_storage = other.storage;
	if (storage.numBits != other_storage.numBits) {
		std::cout << "hkBitField::operator|: numBits is not equal" << std::endl;
		throw std::runtime_error("hkBitField::operator|: numBits is not equal");
		return ret;
	}
	for (int i = 0; i < storage.words.size(); i++) {
		storage.words[i] |= other_storage.words[i];
	}
	return ret;
}

bool hktypes::hkRootLevelContainer::NamedVariant::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkRootLevelContainer::NamedVariant") {
		std::cout << "hkRootLevelContainer::NamedVariant::FromInstance: type_name is not hkRootLevelContainer::NamedVariant" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->GetValue(this->name);
	class_instance->GetInstanceByFieldName("className")->GetValue(this->className);
	this->variant = class_instance->GetPointersByFieldName<hkReferencedObject>("variant");

	return true;
}

bool hktypes::hkRootLevelContainer::NamedVariant::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkRootLevelContainer::NamedVariant") {
		std::cout << "hkRootLevelContainer::NamedVariant::FromInstance: type_name is not hkRootLevelContainer::NamedVariant" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(this->name);
	class_instance->GetInstanceByFieldName("className")->SetValue(this->className);
	class_instance->GetInstanceByFieldName("variant")->SetValue(this->variant);

	return true;
}

bool hktypes::hkRootLevelContainer::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkRootLevelContainer") {
		std::cout << "hkRootLevelContainer::FromInstance: type_name is not hkRootLevelContainer" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("namedVariants")->GetValue(this->namedVariants);

	return true;
}

bool hktypes::hkRootLevelContainer::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hkRootLevelContainer") {
		std::cout << "hkRootLevelContainer::FromInstance: type_name is not hkRootLevelContainer" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("namedVariants")->SetValue(this->namedVariants);

	return true;
}

hktypes::hkReferencedObject* hktypes::hkRootLevelContainer::GetNamedVariantRef(std::string type_name, std::string instance_name)
{
	for (auto& namedVariant : this->namedVariants) {
		if (namedVariant.className == type_name && (instance_name.empty() || instance_name == namedVariant.name)) {
			return namedVariant.variant;
		}
	}
	return nullptr;
}

hktypes::hkRootLevelContainer::NamedVariant& hktypes::hkRootLevelContainer::GetNamedVariant(std::string type_name, std::string instance_name)
{
	for (auto& namedVariant : this->namedVariants) {
		if (namedVariant.className == type_name && (instance_name.empty() || instance_name == namedVariant.name)) {
			return namedVariant;
		}
	}
	throw std::runtime_error("NamedVariant not found");
}

hktypes::hclBufferedMeshObj& hktypes::hclBufferedMeshObj::FromSimClothData(hclSimClothData* simClothData)
{
	if (simClothData == nullptr) {
		return *this;
	}

	auto& ret = *this;

	ret.name = "hclSimClothData_" + simClothData->name;

	auto& sim_poses = simClothData->simClothPoses;
	if (sim_poses.size() == 1) {
		auto& sim_positions = sim_poses[0]->positions;
		for (auto& p : sim_positions) {
			auto pos = p.ToVector4f();
			ret.positions.push_back({ pos.x(), pos.y(), pos.z() });
		}
	}

	for (int i = 0; i < simClothData->triangleIndices.size(); i += 3) {
		ret.triangleIndices.push_back({ simClothData->triangleIndices[i], simClothData->triangleIndices[i + 1], simClothData->triangleIndices[i + 2] });
	}

	if (simClothData->doNormals) {
		// Don't know what to do here
	}

	ret.extraDataList.resize(ret.positions.size());
	for (int i = 0; i < ret.positions.size(); ++i) {
		auto particle_data_extra_data = make_extra_data("particleDatas", simClothData->particleDatas[i]);
		ret.extraDataList[i].push_back(particle_data_extra_data);

		if (std::find(simClothData->fixedParticles.begin(), simClothData->fixedParticles.end(), i) != simClothData->fixedParticles.end()) {
			auto fixed_particles_extra_data = make_extra_data("fixedParticles", true);
			ret.extraDataList[i].push_back(fixed_particles_extra_data);
		}else{
			auto fixed_particles_extra_data = make_extra_data("fixedParticles", false);
			ret.extraDataList[i].push_back(fixed_particles_extra_data);
		}

		auto static_collision_mask_extra_data = make_extra_data("staticCollisionMasks", simClothData->staticCollisionMasks[i]);
		ret.extraDataList[i].push_back(static_collision_mask_extra_data);

		bool perParticlePinchDetectionEnabledFlags = simClothData->perParticlePinchDetectionEnabledFlags[i];
		auto perParticlePinchDetectionEnabledFlags_extra_data = make_extra_data("perParticlePinchDetectionEnabledFlags", perParticlePinchDetectionEnabledFlags);
	}

	size_t num_collidables = simClothData->perInstanceCollidables.size();
	for (int i = 0; i < num_collidables; i++) {
		auto& collider = simClothData->perInstanceCollidables[i];
		auto transform = simClothData->perInstanceCollidables[i]->transform.ToMatrix4f();
		transform.transposeInPlace();
		transform.block<1,3>(3, 0) = Eigen::Vector3f::Zero();
		auto offset = simClothData->collidableTransformMap.offsets[i].ToMatrix4f();
		offset.transposeInPlace();
		auto& shape = collider->shape;
		if (shape->type == 0) {
			auto mesh = shape->ToVisualizeMeshObj();
			mesh.localFrame = transform * offset;
			mesh.name.append(":" + collider->name);
			ret.extraShapes.push_back(mesh);
		}
	}

	return ret;
}

hktypes::hclBufferedMeshObj& hktypes::hclBufferedMeshObj::FromObjectSpaceSkinPNOperator(hclObjectSpaceSkinPNOperator* skinOperator)
{
	if (skinOperator == nullptr) {
		return *this;
	}

	auto& ret = *this;

	ret.name = "hclObjectSpaceSkinPNOperator_" + skinOperator->name;

	auto& transformSubSet = skinOperator->transformSubset;

	int num_verts = skinOperator->objectSpaceDeformer.endVertexIndex + 1;

	ret.positions.resize(num_verts);
	ret.normals.resize(num_verts);
	ret.boneWeights.resize(num_verts);
	ret.extraDataList.resize(num_verts);

	int i = 0;
	for (auto& block : skinOperator->objectSpaceDeformer.eightBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto bone_weight_pairs = block.GetBoneIndicesAndWeights(transformSubSet);
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector3f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
			ret.boneWeights[vert_id_list[j]] = bone_weight_pairs[j];
		}

		i++;
	}

	for (auto& block : skinOperator->objectSpaceDeformer.sevenBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto bone_weight_pairs = block.GetBoneIndicesAndWeights(transformSubSet);
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector3f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
			ret.boneWeights[vert_id_list[j]] = bone_weight_pairs[j];
		}

		i++;
	}

	for (auto& block : skinOperator->objectSpaceDeformer.sixBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto bone_weight_pairs = block.GetBoneIndicesAndWeights(transformSubSet);
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector3f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
			ret.boneWeights[vert_id_list[j]] = bone_weight_pairs[j];
		}

		i++;
	}

	for (auto& block : skinOperator->objectSpaceDeformer.fiveBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto bone_weight_pairs = block.GetBoneIndicesAndWeights(transformSubSet);
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector3f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
			ret.boneWeights[vert_id_list[j]] = bone_weight_pairs[j];
		}

		i++;
	}

	for (auto& block : skinOperator->objectSpaceDeformer.fourBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto bone_weight_pairs = block.GetBoneIndicesAndWeights(transformSubSet);
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector3f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
			ret.boneWeights[vert_id_list[j]] = bone_weight_pairs[j];
		}

		i++;
	}

	for (auto& block : skinOperator->objectSpaceDeformer.threeBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto bone_weight_pairs = block.GetBoneIndicesAndWeights(transformSubSet);
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector3f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
			ret.boneWeights[vert_id_list[j]] = bone_weight_pairs[j];
		}

		i++;
	}

	for (auto& block : skinOperator->objectSpaceDeformer.twoBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto bone_weight_pairs = block.GetBoneIndicesAndWeights(transformSubSet);
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector3f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
			ret.boneWeights[vert_id_list[j]] = bone_weight_pairs[j];
		}

		i++;
	}

	for (auto& block : skinOperator->objectSpaceDeformer.oneBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto bone_weight_pairs = block.GetBoneIndicesAndWeights(transformSubSet);
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector3f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
			ret.boneWeights[vert_id_list[j]] = bone_weight_pairs[j];
		}

		i++;
	}

	return ret;
}

hktypes::hclBufferedMeshObj& hktypes::hclBufferedMeshObj::FromBoneSpaceSkinPNOperator(hclBoneSpaceSkinPNOperator* skinOperator)
{
	if (skinOperator == nullptr) {
		return *this;
	}

	auto& ret = *this;

	ret.name = "hclBoneSpaceSkinPNOperator_" + skinOperator->name;

	auto& transformSubSet = skinOperator->transformSubset;

	int num_verts = skinOperator->boneSpaceDeformer.endVertexIndex + 1;

	ret.positions.resize(num_verts);
	ret.normals.resize(num_verts);

	int i = 0;
	for (auto& block : skinOperator->boneSpaceDeformer.fourBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector4f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
		}

		i++;
	}

	for (auto& block : skinOperator->boneSpaceDeformer.threeBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector4f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
		}

		i++;
	}

	for (auto& block : skinOperator->boneSpaceDeformer.twoBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector4f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
		}

		i++;
	}

	for (auto& block : skinOperator->boneSpaceDeformer.oneBlendEntries) {
		auto& vert_id_list = block.vertexIndices;
		auto localPositions = skinOperator->localPNs[i].localPosition;
		auto localNormals = skinOperator->localPNs[i].localNormal;

		for (int j = 0; j < 16; ++j) {
			auto p = localPositions[j].ToVector4f();
			auto n = localNormals[j].ToVector3f();
			ret.positions[vert_id_list[j]] = { p.x(), p.y(), p.z() };
			ret.normals[vert_id_list[j]] = { n.x(), n.y(), n.z() };
		}

		i++;
	}

	return ret;
}

nlohmann::json hktypes::hclBufferedMeshObj::ToJson()
{
	nlohmann::json ret;

	ret["name"] = this->name;

	ret["type"] = (uint8_t)this->shapeType;

	for (int i = 0; i < 4; ++i) {
		ret["localFrame"].push_back(nlohmann::json::array());
		for (int j = 0; j < 4; ++j) {
			ret["localFrame"][i].push_back(this->localFrame(i, j));
		}
	}

	if (this->shapeType == ShapeType::Capsule) {
		ret["capsuleStart"] = this->capsuleStart;
		ret["capsuleEnd"] = this->capsuleEnd;
		ret["capsuleBigRadius"] = this->capsuleBigRadius;
		ret["capsuleSmallRadius"] = this->capsuleSmallRadius;

		return ret;
	}

	ret["positions"] = this->positions;
	ret["normals"] = this->normals;
	ret["boneWeights"] = this->boneWeights;
	ret["triangleIndices"] = this->triangleIndices;

	for (int i = 0; i < this->extraDataList.size(); ++i) {
		auto& extra_data_list = this->extraDataList[i];
		for (auto& extra_data : extra_data_list) {
			if (extra_data->name == "particleDatas") {
				auto particle_data = static_cast<ExtraData<hclSimClothData::ParticleData>*>(extra_data);
				auto& particle_data_content = particle_data->data;
				auto particle_data_json = nlohmann::json::object();
				particle_data_json["mass"] = particle_data_content.mass;
				particle_data_json["invMass"] = particle_data_content.invMass;
				particle_data_json["radius"] = particle_data_content.radius;
				particle_data_json["friction"] = particle_data_content.friction;
				ret["extraDataList"][i]["particleDatas"] = particle_data_json;
			}
			else if (extra_data->name == "fixedParticles") {
				auto fixed_particles = static_cast<ExtraData<bool>*>(extra_data);
				ret["extraDataList"][i]["fixedParticles"] = fixed_particles->data;
			}
			else if (extra_data->name == "staticCollisionMasks") {
				auto static_collision_masks = static_cast<ExtraData<uint32_t>*>(extra_data);
				ret["extraDataList"][i]["staticCollisionMasks"] = static_collision_masks->data;
			}
			else if (extra_data->name == "perParticlePinchDetectionEnabledFlags") {
				auto per_particle_pinch_detection_enabled_flags = static_cast<ExtraData<bool>*>(extra_data);
				ret["extraDataList"][i]["perParticlePinchDetectionEnabledFlags"] = per_particle_pinch_detection_enabled_flags->data;
			}
		}
	}

	for (auto& extra_shape : this->extraShapes) {
		ret["extraShapes"].push_back(extra_shape.ToJson());
	}

	return ret;
}

hktypes::hclBufferedMeshObj& hktypes::hclBufferedMeshObj::FromJson(nlohmann::json& json)
{
	this->name = json["name"];

	this->shapeType = (ShapeType)json["type"];

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; j++) {
			this->localFrame(i, j) = json["localFrame"][i][j];
		}
	}

	if (this->shapeType == ShapeType::Capsule) {
		this->capsuleStart = json["capsuleStart"];
		this->capsuleEnd = json["capsuleEnd"];
		this->capsuleBigRadius = json["capsuleBigRadius"];
		this->capsuleSmallRadius = json["capsuleSmallRadius"];

		return *this;
	}

	this->positions = json["positions"];
	this->normals = json["normals"];
	this->boneWeights = json["boneWeights"];
	this->triangleIndices = json["triangleIndices"];

	if (json.find("extraDataList") != json.end()) {
		for (int i = 0; i < this->positions.size(); ++i) {
			auto& extra_data_list_json = json["extraDataList"][i];
			for (auto& extra_data_json : extra_data_list_json) {
				if (extra_data_json.find("particleDatas") != extra_data_json.end()) {
					auto particle_data = make_extra_data("particleDatas", hclSimClothData::ParticleData());
					particle_data->data.mass = extra_data_json["particleDatas"]["mass"];
					particle_data->data.invMass = extra_data_json["particleDatas"]["invMass"];
					particle_data->data.radius = extra_data_json["particleDatas"]["radius"];
					particle_data->data.friction = extra_data_json["particleDatas"]["friction"];
					this->extraDataList[i].push_back(particle_data);
				}
				else if (extra_data_json.find("fixedParticles") != extra_data_json.end()) {
					bool fixed_particles_v = extra_data_json["fixedParticles"];
					auto fixed_particles = make_extra_data("fixedParticles", fixed_particles_v);
					this->extraDataList[i].push_back(fixed_particles);
				}
				else if (extra_data_json.find("staticCollisionMasks") != extra_data_json.end()) {
					uint32_t static_collision_masks_v = extra_data_json["staticCollisionMasks"];
					auto static_collision_masks = make_extra_data("staticCollisionMasks", static_collision_masks_v);
					this->extraDataList[i].push_back(static_collision_masks);
				}
				else if (extra_data_json.find("perParticlePinchDetectionEnabledFlags") != extra_data_json.end()) {
					bool per_particle_pinch_detection_enabled_flags_v = extra_data_json["perParticlePinchDetectionEnabledFlags"];
					auto per_particle_pinch_detection_enabled_flags = make_extra_data("perParticlePinchDetectionEnabledFlags", per_particle_pinch_detection_enabled_flags_v);
					this->extraDataList[i].push_back(per_particle_pinch_detection_enabled_flags);
				}
			}
		}
	}

	if (json.find("extraShapes") != json.end()) {
		for (auto& extra_shape_json : json["extraShapes"]) {
			auto extra_shape = hclBufferedMeshObj();
			extra_shape.FromJson(extra_shape_json);
			this->extraShapes.push_back(extra_shape);
		}
	}
}
