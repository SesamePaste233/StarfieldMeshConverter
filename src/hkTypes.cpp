#include "hkTypes.h"

bool hktypes::hkPackedVector3::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto array_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);
	if (array_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::FromInstance: type_name is not hkPackedVector3" << std::endl;
		return false;
	}

	std::vector<int16_t> _values;
	array_instance->GetValue(_values);

	this->values[0] = _values[0];
	this->values[1] = _values[1];
	this->values[2] = _values[2];
	this->values[3] = _values[3];

	return true;
}

bool hktypes::hkPackedVector3::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto array_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);
	if (array_instance->type->type_name != "hkPackedVector3") {
		std::cout << "hkPackedVector3::FromInstance: type_name is not hkPackedVector3" << std::endl;
		return false;
	}

	std::vector<int16_t> _values = { this->values[0], this->values[1], this->values[2], this->values[3] };
	array_instance->SetValue(_values);
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

bool hktypes::hkMatrix4Holder::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto array_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);
	if (array_instance->type->type_name != "hkMatrix4" && array_instance->type->type_name != "hkMatrix4f" && array_instance->type->type_name != "hkMatrix4d") {
		std::cout << "hkMatrix4Holder::FromInstance: type_name is not hkMatrix4" << std::endl;
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
	if (array_instance->type->type_name != "hkMatrix4" && array_instance->type->type_name != "hkMatrix4f" && array_instance->type->type_name != "hkMatrix4d") {
		std::cout << "hkMatrix4Holder::FromInstance: type_name is not hkMatrix4" << std::endl;
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

bool hktypes::hkVector4Holder::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto array_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);
	if (array_instance->type->type_name != "hkVector4" && array_instance->type->type_name != "hkVector4f" && array_instance->type->type_name != "hkVector4d") {
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
	if (array_instance->type->type_name != "hkVector4" && array_instance->type->type_name != "hkVector4f" && array_instance->type->type_name != "hkVector4d") {
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

bool hktypes::hkBitField::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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

bool hktypes::hkRootLevelContainer::NamedVariant::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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
	class_instance->GetInstanceByFieldName("variant")->SetValue(*this->variant);

	return true;
}

bool hktypes::hkRootLevelContainer::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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
