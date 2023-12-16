#include "Generated\hclObjectSpaceDeformer.h"

bool hktypes::hclObjectSpaceDeformer::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer") {
		std::cout << "hclObjectSpaceDeformer::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("eightBlendEntries")->GetValue(eightBlendEntries);
	class_instance->GetInstanceByFieldName("sevenBlendEntries")->GetValue(sevenBlendEntries);
	class_instance->GetInstanceByFieldName("sixBlendEntries")->GetValue(sixBlendEntries);
	class_instance->GetInstanceByFieldName("fiveBlendEntries")->GetValue(fiveBlendEntries);
	class_instance->GetInstanceByFieldName("fourBlendEntries")->GetValue(fourBlendEntries);
	class_instance->GetInstanceByFieldName("threeBlendEntries")->GetValue(threeBlendEntries);
	class_instance->GetInstanceByFieldName("twoBlendEntries")->GetValue(twoBlendEntries);
	class_instance->GetInstanceByFieldName("oneBlendEntries")->GetValue(oneBlendEntries);
	class_instance->GetInstanceByFieldName("controlBytes")->GetValue(controlBytes);
	class_instance->GetInstanceByFieldName("startVertexIndex")->GetValue(startVertexIndex);
	class_instance->GetInstanceByFieldName("endVertexIndex")->GetValue(endVertexIndex);
	class_instance->GetInstanceByFieldName("partialWrite")->GetValue(partialWrite);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockPN::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockPN::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("localPosition")->GetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->GetValue(localNormal);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockUnpackedPN::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::EightBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::EightBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::SevenBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SevenBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::SixBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SixBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::FiveBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FiveBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FourBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->GetValue(boneWeights);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::ThreeBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::ThreeBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::TwoBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::OneBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer") {
		std::cout << "hclObjectSpaceDeformer::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("eightBlendEntries")->SetValue(eightBlendEntries);
	class_instance->GetInstanceByFieldName("sevenBlendEntries")->SetValue(sevenBlendEntries);
	class_instance->GetInstanceByFieldName("sixBlendEntries")->SetValue(sixBlendEntries);
	class_instance->GetInstanceByFieldName("fiveBlendEntries")->SetValue(fiveBlendEntries);
	class_instance->GetInstanceByFieldName("fourBlendEntries")->SetValue(fourBlendEntries);
	class_instance->GetInstanceByFieldName("threeBlendEntries")->SetValue(threeBlendEntries);
	class_instance->GetInstanceByFieldName("twoBlendEntries")->SetValue(twoBlendEntries);
	class_instance->GetInstanceByFieldName("oneBlendEntries")->SetValue(oneBlendEntries);
	class_instance->GetInstanceByFieldName("controlBytes")->SetValue(controlBytes);
	class_instance->GetInstanceByFieldName("startVertexIndex")->SetValue(startVertexIndex);
	class_instance->GetInstanceByFieldName("endVertexIndex")->SetValue(endVertexIndex);
	class_instance->GetInstanceByFieldName("partialWrite")->SetValue(partialWrite);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockPN::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockPN::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("localPosition")->SetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->SetValue(localNormal);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockUnpackedPN::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::EightBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::EightBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::SevenBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SevenBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::SixBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SixBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::FiveBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FiveBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FourBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->SetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->SetValue(boneWeights);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::ThreeBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::ThreeBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::TwoBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

bool hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::OneBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	return true;
}

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::LocalBlockPN::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::ThreeBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::string> hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::GetFieldTypeAndNames() { return {
	{ "hkArray<hclObjectSpaceDeformer::EightBlendEntryBlock, hkContainerHeapAllocator>", { "eightBlendEntries", 0, 32 } },
	{ "hkArray<hclObjectSpaceDeformer::SevenBlendEntryBlock, hkContainerHeapAllocator>", { "sevenBlendEntries", 16, 32 } },
	{ "hkArray<hclObjectSpaceDeformer::SixBlendEntryBlock, hkContainerHeapAllocator>", { "sixBlendEntries", 32, 32 } },
	{ "hkArray<hclObjectSpaceDeformer::FiveBlendEntryBlock, hkContainerHeapAllocator>", { "fiveBlendEntries", 48, 32 } },
	{ "hkArray<hclObjectSpaceDeformer::FourBlendEntryBlock, hkContainerHeapAllocator>", { "fourBlendEntries", 64, 32 } },
	{ "hkArray<hclObjectSpaceDeformer::ThreeBlendEntryBlock, hkContainerHeapAllocator>", { "threeBlendEntries", 80, 32 } },
	{ "hkArray<hclObjectSpaceDeformer::TwoBlendEntryBlock, hkContainerHeapAllocator>", { "twoBlendEntries", 96, 32 } },
	{ "hkArray<hclObjectSpaceDeformer::OneBlendEntryBlock, hkContainerHeapAllocator>", { "oneBlendEntries", 112, 32 } },
	{ "hkArray<hkUint8, hkContainerHeapAllocator>", { "controlBytes", 128, 32 } },
	{ "hkUint16", { "startVertexIndex", 144, 32 } },
	{ "hkUint16", { "endVertexIndex", 146, 32 } },
	{ "hkBool", { "partialWrite", 148, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::LocalBlockPN::GetFieldTypeAndNames() { return {
	{ "T[N]<hkPackedVector3, 16>", { "localPosition", 0, 32 } },
	{ "T[N]<hkPackedVector3, 16>", { "localNormal", 128, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::GetFieldTypeAndNames() { return {
	{ "T[N]<hkUint16, 16>", { "vertexIndices", 0, 32 } },
	{ "T[N]<hkUint16, 64>", { "boneIndices", 32, 32 } },
	{ "T[N]<hkUint8, 64>", { "boneWeights", 160, 32 } },
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::ThreeBlendEntryBlock::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::GetFieldTypeAndNames() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::GetFieldTypeAndNames() { return {
}; };

