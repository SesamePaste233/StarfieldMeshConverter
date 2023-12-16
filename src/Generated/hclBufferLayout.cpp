#include "Generated\hclBufferLayout.h"

bool hktypes::hclBufferLayout::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout") {
		std::cout << "hclBufferLayout::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("elementsLayout")->GetValue(elementsLayout);
	class_instance->GetInstanceByFieldName("slots")->GetValue(slots);
	class_instance->GetInstanceByFieldName("numSlots")->GetValue(numSlots);
	class_instance->GetInstanceByFieldName("triangleFormat")->GetValue(triangleFormat);
	return true;
}

bool hktypes::hclBufferLayout::BufferElement::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout::BufferElement") {
		std::cout << "hclBufferLayout::BufferElement::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("vectorConversion")->GetValue(vectorConversion);
	class_instance->GetInstanceByFieldName("vectorSize")->GetValue(vectorSize);
	class_instance->GetInstanceByFieldName("slotId")->GetValue(slotId);
	class_instance->GetInstanceByFieldName("slotStart")->GetValue(slotStart);
	return true;
}

bool hktypes::hclBufferLayout::Slot::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout::Slot") {
		std::cout << "hclBufferLayout::Slot::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("flags")->GetValue(flags);
	class_instance->GetInstanceByFieldName("stride")->GetValue(stride);
	return true;
}

bool hktypes::hclBufferLayout::TriangleFormat::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout::TriangleFormat") {
		std::cout << "hclBufferLayout::TriangleFormat::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclBufferLayout::SlotFlags::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout::SlotFlags") {
		std::cout << "hclBufferLayout::SlotFlags::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclBufferLayout::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout") {
		std::cout << "hclBufferLayout::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("elementsLayout")->SetValue(elementsLayout);
	class_instance->GetInstanceByFieldName("slots")->SetValue(slots);
	class_instance->GetInstanceByFieldName("numSlots")->SetValue(numSlots);
	class_instance->GetInstanceByFieldName("triangleFormat")->SetValue(triangleFormat);
	return true;
}

bool hktypes::hclBufferLayout::BufferElement::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout::BufferElement") {
		std::cout << "hclBufferLayout::BufferElement::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("vectorConversion")->SetValue(vectorConversion);
	class_instance->GetInstanceByFieldName("vectorSize")->SetValue(vectorSize);
	class_instance->GetInstanceByFieldName("slotId")->SetValue(slotId);
	class_instance->GetInstanceByFieldName("slotStart")->SetValue(slotStart);
	return true;
}

bool hktypes::hclBufferLayout::Slot::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout::Slot") {
		std::cout << "hclBufferLayout::Slot::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("flags")->SetValue(flags);
	class_instance->GetInstanceByFieldName("stride")->SetValue(stride);
	return true;
}

bool hktypes::hclBufferLayout::TriangleFormat::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout::TriangleFormat") {
		std::cout << "hclBufferLayout::TriangleFormat::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclBufferLayout::SlotFlags::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferLayout::SlotFlags") {
		std::cout << "hclBufferLayout::SlotFlags::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

inline std::vector<std::string> hktypes::hclBufferLayout::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclBufferLayout::BufferElement::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclBufferLayout::Slot::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclBufferLayout::TriangleFormat::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclBufferLayout::SlotFlags::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclBufferLayout::GetFieldTypeAndNames() { return {
	{ "T[N]<hclBufferLayout::BufferElement, 4>", { "elementsLayout", 0, 32 } },
	{ "T[N]<hclBufferLayout::Slot, 4>", { "slots", 16, 32 } },
	{ "hkUint8", { "numSlots", 24, 32 } },
	{ "hkEnum<hclBufferLayout::TriangleFormat, hkUint8>", { "triangleFormat", 25, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclBufferLayout::BufferElement::GetFieldTypeAndNames() { return {
	{ "hkEnum<hclRuntimeConversionInfo::VectorConversion, hkUint8>", { "vectorConversion", 0, 32 } },
	{ "hkUint8", { "vectorSize", 1, 32 } },
	{ "hkUint8", { "slotId", 2, 32 } },
	{ "hkUint8", { "slotStart", 3, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclBufferLayout::Slot::GetFieldTypeAndNames() { return {
	{ "hkEnum<hclBufferLayout::SlotFlags, hkUint8>", { "flags", 0, 32 } },
	{ "hkUint8", { "stride", 1, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclBufferLayout::TriangleFormat::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclBufferLayout::SlotFlags::GetFieldTypeAndNames() { return {
}; };

