#include "Generated\hclBoneSpaceDeformer.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclBoneSpaceDeformer::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer") {
		std::cout << "hclBoneSpaceDeformer::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

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

bool hktypes::hclBoneSpaceDeformer::LocalBlockPN::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockPN") {
		std::cout << "hclBoneSpaceDeformer::LocalBlockPN::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("localPosition")->GetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->GetValue(localNormal);
	return true;
}

bool hktypes::hclBoneSpaceDeformer::LocalBlockUnpackedPN::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclBoneSpaceDeformer::LocalBlockUnpackedPN::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::FourBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::FourBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::ThreeBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::ThreeBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::TwoBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::TwoBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::OneBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::OneBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	return true;
}

bool hktypes::hclBoneSpaceDeformer::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer") {
		std::cout << "hclBoneSpaceDeformer::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

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

bool hktypes::hclBoneSpaceDeformer::LocalBlockPN::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockPN") {
		std::cout << "hclBoneSpaceDeformer::LocalBlockPN::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("localPosition")->SetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->SetValue(localNormal);
	return true;
}

bool hktypes::hclBoneSpaceDeformer::LocalBlockUnpackedPN::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclBoneSpaceDeformer::LocalBlockUnpackedPN::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::FourBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::FourBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::ThreeBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::ThreeBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::TwoBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::TwoBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::OneBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBoneSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::OneBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->SetValue(boneIndices);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceDeformer::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceDeformer::LocalBlockPN::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceDeformer::LocalBlockUnpackedPN::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceDeformer::FourBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceDeformer::ThreeBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceDeformer::TwoBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBoneSpaceDeformer::OneBlendEntryBlock::GetTemplateArgs() { return {
}; };

