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

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->GetValue(boneWeights);
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

	class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->SetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->SetValue(boneWeights);
	return true;
}

