#include "Generated\hclObjectSpaceDeformer.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclObjectSpaceDeformer::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer") {
		std::cout << "hclObjectSpaceDeformer::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

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

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockPN::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("localPosition")->GetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->GetValue(localNormal);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockUnpackedPN::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::EightBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::EightBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::SevenBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SevenBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::SixBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SixBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::FiveBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FiveBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FourBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->GetValue(boneWeights);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::ThreeBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::ThreeBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::TwoBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::OneBlendEntryBlock::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer") {
		std::cout << "hclObjectSpaceDeformer::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

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

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockPN::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("localPosition")->SetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->SetValue(localNormal);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockUnpackedPN::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::EightBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::EightBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::SevenBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SevenBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::SixBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SixBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::FiveBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FiveBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FourBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->SetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->SetValue(boneWeights);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::ThreeBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::ThreeBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::TwoBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclObjectSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::OneBlendEntryBlock::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::LocalBlockPN::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::ThreeBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::GetTemplateArgs() { return {
}; };

