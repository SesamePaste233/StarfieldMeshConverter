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
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer") {
		std::cout << "hclObjectSpaceDeformer::FromInstance: Expecting hclObjectSpaceDeformer but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::LocalBlockPN::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockPN::FromInstance: Expecting hclObjectSpaceDeformer::LocalBlockPN but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("localPosition")->GetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->GetValue(localNormal);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::LocalBlockUnpackedPN::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockUnpackedPN::FromInstance: Expecting hclObjectSpaceDeformer::LocalBlockUnpackedPN but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::EightBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::EightBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::EightBlendEntryBlock::FromInstance: Expecting hclObjectSpaceDeformer::EightBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::SevenBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::SevenBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SevenBlendEntryBlock::FromInstance: Expecting hclObjectSpaceDeformer::SevenBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::SixBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::SixBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SixBlendEntryBlock::FromInstance: Expecting hclObjectSpaceDeformer::SixBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::FiveBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::FiveBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FiveBlendEntryBlock::FromInstance: Expecting hclObjectSpaceDeformer::FiveBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::FourBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FourBlendEntryBlock::FromInstance: Expecting hclObjectSpaceDeformer::FourBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::ThreeBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::ThreeBlendEntryBlock::FromInstance: Expecting hclObjectSpaceDeformer::ThreeBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->GetValue(boneWeights);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::TwoBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::TwoBlendEntryBlock::FromInstance: Expecting hclObjectSpaceDeformer::TwoBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->GetValue(boneWeights);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::OneBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::OneBlendEntryBlock::FromInstance: Expecting hclObjectSpaceDeformer::OneBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer") {
		std::cout << "hclObjectSpaceDeformer::ToInstance: Expecting hclObjectSpaceDeformer but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::LocalBlockPN::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockPN::ToInstance: Expecting hclObjectSpaceDeformer::LocalBlockPN but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("localPosition")->SetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->SetValue(localNormal);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockUnpackedPN::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::LocalBlockUnpackedPN::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclObjectSpaceDeformer::LocalBlockUnpackedPN::ToInstance: Expecting hclObjectSpaceDeformer::LocalBlockUnpackedPN but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::EightBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::EightBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::EightBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::EightBlendEntryBlock::ToInstance: Expecting hclObjectSpaceDeformer::EightBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SevenBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::SevenBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::SevenBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SevenBlendEntryBlock::ToInstance: Expecting hclObjectSpaceDeformer::SevenBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::SixBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::SixBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::SixBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::SixBlendEntryBlock::ToInstance: Expecting hclObjectSpaceDeformer::SixBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FiveBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::FiveBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::FiveBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FiveBlendEntryBlock::ToInstance: Expecting hclObjectSpaceDeformer::FiveBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FourBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::FourBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::FourBlendEntryBlock::ToInstance: Expecting hclObjectSpaceDeformer::FourBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::ThreeBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::ThreeBlendEntryBlock::ToInstance: Expecting hclObjectSpaceDeformer::ThreeBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->SetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->SetValue(boneWeights);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::TwoBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::TwoBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::TwoBlendEntryBlock::ToInstance: Expecting hclObjectSpaceDeformer::TwoBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->SetValue(boneIndices);
	class_instance->GetInstanceByFieldName("boneWeights")->SetValue(boneWeights);
	return true;
}

bool hktypes::hclObjectSpaceDeformer::OneBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclObjectSpaceDeformer::OneBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclObjectSpaceDeformer::OneBlendEntryBlock::ToInstance: Expecting hclObjectSpaceDeformer::OneBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->SetValue(boneIndices);
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

