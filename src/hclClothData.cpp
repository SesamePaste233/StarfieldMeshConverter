#include "hclClothData.h"

bool hktypes::hclBufferLayout::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBufferLayout") {
		std::cout << "hclBufferLayout::FromInstance: type_name is not hclBufferLayout" << std::endl;
		return false;
	}

	std::vector<BufferElement> _buffer_elements;
	class_instance->GetInstanceByFieldName("elementsLayout")->GetValue(_buffer_elements);
	for (int i = 0; i < 4; ++i) {
		this->elementsLayout[i] = _buffer_elements[i];
	}

	std::vector<Slot> _slots;
	class_instance->GetInstanceByFieldName("slots")->GetValue(_slots);
	for (int i = 0; i < 4; ++i) {
		this->slots[i] = _slots[i];
	}

	this->numSlots = class_instance->GetUIntByFieldName("numSlots");
	this->triangleFormat = (TriangleFormat)class_instance->GetUIntByFieldName("triangleFormat");

	return true;
}

bool hktypes::hclBufferLayout::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBufferLayout") {
		std::cout << "hclBufferLayout::FromInstance: type_name is not hclBufferLayout" << std::endl;
		return false;
	}

	std::vector<BufferElement> _buffer_elements;
	for (int i = 0; i < 4; ++i) {
		_buffer_elements.push_back(this->elementsLayout[i]);
	}
	class_instance->GetInstanceByFieldName("elementsLayout")->SetValue(_buffer_elements);

	std::vector<Slot> _slots;
	for (int i = 0; i < 4; ++i) {
		_slots.push_back(this->slots[i]);
	}
	class_instance->GetInstanceByFieldName("slots")->SetValue(_slots);

	class_instance->GetInstanceByFieldName("numSlots")->SetValue(this->numSlots);

	uint8_t triangle_format = (uint8_t)this->triangleFormat;
	class_instance->GetInstanceByFieldName("triangleFormat")->SetValue(triangle_format);

	return true;
}

bool hktypes::hclBufferLayout::BufferElement::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBufferLayout::BufferElement") {
		std::cout << "hclBufferLayout::BufferElement::FromInstance: type_name is not hclBufferLayout::BufferElement" << std::endl;
		return false;
	}

	this->vectorConversion = (hclRuntimeConversionInfo::VectorConversion)class_instance->GetUIntByFieldName("vectorConversion");
	this->vectorSize = class_instance->GetUIntByFieldName("vectorSize");
	this->slotId = class_instance->GetUIntByFieldName("slotId");
	this->slotStart = class_instance->GetUIntByFieldName("slotStart");

	return true;
}

bool hktypes::hclBufferLayout::BufferElement::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBufferLayout::BufferElement") {
		std::cout << "hclBufferLayout::BufferElement::FromInstance: type_name is not hclBufferLayout::BufferElement" << std::endl;
		return false;
	}

	uint8_t _vector_conversion = (uint8_t)this->vectorConversion;
	class_instance->GetInstanceByFieldName("vectorConversion")->SetValue(_vector_conversion);
	class_instance->GetInstanceByFieldName("vectorSize")->SetValue(this->vectorSize);
	class_instance->GetInstanceByFieldName("slotId")->SetValue(this->slotId);
	class_instance->GetInstanceByFieldName("slotStart")->SetValue(this->slotStart);

	return true;
}

bool hktypes::hclBufferLayout::Slot::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBufferLayout::Slot") {
		std::cout << "hclBufferLayout::Slot::FromInstance: type_name is not hclBufferLayout::Slot" << std::endl;
		return false;
	}

	this->flags = (SlotFlags)class_instance->GetUIntByFieldName("flags");
	this->stride = class_instance->GetUIntByFieldName("stride");

	return true;
}

bool hktypes::hclBufferLayout::Slot::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBufferLayout::Slot") {
		std::cout << "hclBufferLayout::Slot::FromInstance: type_name is not hclBufferLayout::Slot" << std::endl;
		return false;
	}

	uint8_t _flags = (uint8_t)this->flags;
	class_instance->GetInstanceByFieldName("flags")->SetValue(_flags);
	class_instance->GetInstanceByFieldName("stride")->SetValue(this->stride);

	return true;
}

bool hktypes::hclBufferDefinition::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBufferDefinition") {
		std::cout << "hclBufferDefinition::FromInstance: type_name is not hclBufferDefinition" << std::endl;
		return false;
	}

	this->meshName = class_instance->GetStringByFieldName("meshName");
	this->bufferName = class_instance->GetStringByFieldName("bufferName");
	this->type = class_instance->GetIntByFieldName("type");
	this->subType = class_instance->GetIntByFieldName("subType");
	this->numVertices = class_instance->GetUIntByFieldName("numVertices");
	this->numTriangles = class_instance->GetUIntByFieldName("numTriangles");
	class_instance->GetInstanceByFieldName("bufferLayout")->GetValue(this->bufferLayout);

	return true;
}

bool hktypes::hclBufferDefinition::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBufferDefinition") {
		std::cout << "hclBufferDefinition::FromInstance: type_name is not hclBufferDefinition" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("meshName")->SetValue(this->meshName);
	class_instance->GetInstanceByFieldName("bufferName")->SetValue(this->bufferName);
	class_instance->GetInstanceByFieldName("type")->SetValue(this->type);
	class_instance->GetInstanceByFieldName("subType")->SetValue(this->subType);
	class_instance->GetInstanceByFieldName("numVertices")->SetValue(this->numVertices);
	class_instance->GetInstanceByFieldName("numTriangles")->SetValue(this->numTriangles);
	class_instance->GetInstanceByFieldName("bufferLayout")->SetValue(this->bufferLayout);

	return true;
}

bool hktypes::hclScratchBufferDefinition::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclScratchBufferDefinition") {
		std::cout << "hclScratchBufferDefinition::FromInstance: type_name is not hclScratchBufferDefinition" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("class_parent")->GetValue(*(hclBufferDefinition*)this);

	this->triangleIndices = class_instance->GetArrayByFieldName<uint16_t>("triangleIndices");
	this->storeNormals = class_instance->GetBoolByFieldName("storeNormals");
	this->storeTangentsAndBiTangents = class_instance->GetBoolByFieldName("storeTangentsAndBiTangents");

	return true;
}

bool hktypes::hclScratchBufferDefinition::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclScratchBufferDefinition") {
		std::cout << "hclScratchBufferDefinition::FromInstance: type_name is not hclScratchBufferDefinition" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("class_parent")->SetValue(*(hclBufferDefinition*)this);

	class_instance->GetInstanceByFieldName("triangleIndices")->SetValue(this->triangleIndices);
	class_instance->GetInstanceByFieldName("storeNormals")->SetValue(this->storeNormals);
	class_instance->GetInstanceByFieldName("storeTangentsAndBiTangents")->SetValue(this->storeTangentsAndBiTangents);

	return true;
}

bool hktypes::hclTransformSetDefinition::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->ctype_name != "hclTransformSetDefinition") {
		std::cout << "hclTransformSetDefinition::FromInstance: type_name is not hclTransformSetDefinition" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");
	this->type = class_instance->GetIntByFieldName("type");
	this->numTransforms = class_instance->GetUIntByFieldName("numTransforms");

	return true;
}

bool hktypes::hclTransformSetDefinition::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->ctype_name != "hclTransformSetDefinition") {
		std::cout << "hclTransformSetDefinition::FromInstance: type_name is not hclTransformSetDefinition" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(this->name);
	class_instance->GetInstanceByFieldName("type")->SetValue(this->type);
	class_instance->GetInstanceByFieldName("numTransforms")->SetValue(this->numTransforms);

	return true;
}

bool hktypes::hclClothData::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothData") {
		std::cout << "hclClothData::FromInstance: type_name is not hclClothData" << std::endl;
		return false;
	}

	this->name = class_instance->GetStringByFieldName("name");
	this->simClothDatas = class_instance->GetArrayOfPointersByFieldName<hclSimClothData>("simClothDatas");
	this->bufferDefinitions = class_instance->GetArrayOfPointersByFieldName<hclBufferDefinition>("bufferDefinitions");
	this->transformSetDefinitions = class_instance->GetArrayOfPointersByFieldName<hclTransformSetDefinition>("transformSetDefinitions");

	return true;
}

bool hktypes::hclClothData::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclClothData") {
		std::cout << "hclClothData::FromInstance: type_name is not hclClothData" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(this->name);
	std::vector<hclSimClothData> _simClothDatas;
	for (auto& simClothData : this->simClothDatas) {
		_simClothDatas.push_back(*simClothData);
	}
	class_instance->GetInstanceByFieldName("simClothDatas")->SetValue(_simClothDatas);

	std::vector<hclBufferDefinition> _bufferDefinitions;
	for (auto& bufferDefinition : this->bufferDefinitions) {
		_bufferDefinitions.push_back(*bufferDefinition);
	}
	class_instance->GetInstanceByFieldName("bufferDefinitions")->SetValue(_bufferDefinitions);

	std::vector<hclTransformSetDefinition> _transformSetDefinitions;
	for (auto& transformSetDefinition : this->transformSetDefinitions) {
		_transformSetDefinitions.push_back(*transformSetDefinition);
	}
	class_instance->GetInstanceByFieldName("transformSetDefinitions")->SetValue(_transformSetDefinitions);

	return true;
}
