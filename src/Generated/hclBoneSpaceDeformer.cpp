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
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer") {
		std::cout << "hclBoneSpaceDeformer::FromInstance: Expecting hclBoneSpaceDeformer but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::LocalBlockPN::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockPN") {
		std::cout << "hclBoneSpaceDeformer::LocalBlockPN::FromInstance: Expecting hclBoneSpaceDeformer::LocalBlockPN but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("localPosition")->GetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->GetValue(localNormal);
	return true;
}

bool hktypes::hclBoneSpaceDeformer::LocalBlockUnpackedPN::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::LocalBlockUnpackedPN::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclBoneSpaceDeformer::LocalBlockUnpackedPN::FromInstance: Expecting hclBoneSpaceDeformer::LocalBlockUnpackedPN but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::FourBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::FourBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::FourBlendEntryBlock::FromInstance: Expecting hclBoneSpaceDeformer::FourBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	class_instance->GetInstanceByFieldName("padding")->GetValue(padding);
	return true;
}

bool hktypes::hclBoneSpaceDeformer::ThreeBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::ThreeBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::ThreeBlendEntryBlock::FromInstance: Expecting hclBoneSpaceDeformer::ThreeBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::TwoBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::TwoBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::TwoBlendEntryBlock::FromInstance: Expecting hclBoneSpaceDeformer::TwoBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::OneBlendEntryBlock::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::OneBlendEntryBlock::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::OneBlendEntryBlock::FromInstance: Expecting hclBoneSpaceDeformer::OneBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->GetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->GetValue(boneIndices);
	return true;
}

bool hktypes::hclBoneSpaceDeformer::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer") {
		std::cout << "hclBoneSpaceDeformer::ToInstance: Expecting hclBoneSpaceDeformer but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::LocalBlockPN::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockPN") {
		std::cout << "hclBoneSpaceDeformer::LocalBlockPN::ToInstance: Expecting hclBoneSpaceDeformer::LocalBlockPN but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("localPosition")->SetValue(localPosition);
	class_instance->GetInstanceByFieldName("localNormal")->SetValue(localNormal);
	return true;
}

bool hktypes::hclBoneSpaceDeformer::LocalBlockUnpackedPN::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::LocalBlockUnpackedPN::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockUnpackedPN") {
		std::cout << "hclBoneSpaceDeformer::LocalBlockUnpackedPN::ToInstance: Expecting hclBoneSpaceDeformer::LocalBlockUnpackedPN but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::FourBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::FourBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::FourBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::FourBlendEntryBlock::ToInstance: Expecting hclBoneSpaceDeformer::FourBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndices")->SetValue(vertexIndices);
	class_instance->GetInstanceByFieldName("boneIndices")->SetValue(boneIndices);
	class_instance->GetInstanceByFieldName("padding")->SetValue(padding);
	return true;
}

bool hktypes::hclBoneSpaceDeformer::ThreeBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::ThreeBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::ThreeBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::ThreeBlendEntryBlock::ToInstance: Expecting hclBoneSpaceDeformer::ThreeBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::TwoBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::TwoBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::TwoBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::TwoBlendEntryBlock::ToInstance: Expecting hclBoneSpaceDeformer::TwoBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclBoneSpaceDeformer::OneBlendEntryBlock::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclBoneSpaceDeformer::OneBlendEntryBlock::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::OneBlendEntryBlock") {
		std::cout << "hclBoneSpaceDeformer::OneBlendEntryBlock::ToInstance: Expecting hclBoneSpaceDeformer::OneBlendEntryBlock but got " << class_instance->type->type_name << std::endl;
		return false;
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

