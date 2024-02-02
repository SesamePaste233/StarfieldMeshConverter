#include "Generated\hkArray.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\hknpPhysicsSystemData.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\hkcdStaticMeshTree::Connectivity.h"
#include "Generated\.h"
#include "Generated\hkRefCountedProperties.h"
#include "Generated\hkcdSimdTree.h"
#include "Generated\hkcdStaticMeshTree.h"
#include "Generated\hkcdStaticMeshTree.h"
#include "Generated\hkcdCompressedAabbCodecs.h"
#include "Generated\hkcdDefaultStaticMeshTree.h"
#include "Generated\hkcdCompressedAabbCodecs.h"
#include "Generated\.h"

template<>
bool hktypes::hkArray<hknpMaterial, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hknpMaterial, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hknpMaterial, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hknpMaterial"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hknpMotionProperties, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hknpMotionProperties, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hknpMotionProperties, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hknpMotionProperties"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hknpPhysicsSystemData::bodyCinfoWithAttachment, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hknpPhysicsSystemData::bodyCinfoWithAttachment, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hknpPhysicsSystemData::bodyCinfoWithAttachment, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hknpPhysicsSystemData::bodyCinfoWithAttachment"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hknpConstraintCinfo, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hknpConstraintCinfo, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hknpConstraintCinfo, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hknpConstraintCinfo"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hknpShapeInstance, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hknpShapeInstance, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hknpShapeInstance, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hknpShapeInstance"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkUint32, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkUint32, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkUint32, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkUint32"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkRefCountedProperties::Entry"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkcdSimdTree::Node, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkcdSimdTree::Node, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkcdSimdTree::Node, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkcdSimdTree::Node"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkcdStaticMeshTree::Connectivity::SectionHeader, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkcdStaticMeshTree::Connectivity::SectionHeader, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkcdStaticMeshTree::Connectivity::SectionHeader, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkcdStaticMeshTree::Connectivity::SectionHeader"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkUint8, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkUint8, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkUint8, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkUint8"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkHandle<hkUint32, 4294967295>, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkHandle<hkUint32, 4294967295>, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkHandle<hkUint32, 4294967295>, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkHandle<hkUint32, 4294967295>"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<unsigned int, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<unsigned int, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<unsigned int, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "unsigned int"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<unsigned long long, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<unsigned long long, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<unsigned long long, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "unsigned long long"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkcdDefaultStaticMeshTree::PrimitiveDataRun, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkcdDefaultStaticMeshTree::PrimitiveDataRun, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkcdDefaultStaticMeshTree::PrimitiveDataRun, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkcdDefaultStaticMeshTree::PrimitiveDataRun"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkcdStaticMeshTree::Section, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkcdStaticMeshTree::Section, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkcdStaticMeshTree::Section, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkcdStaticMeshTree::Section"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkcdStaticMeshTree::Primitive, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkcdStaticMeshTree::Primitive, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkcdStaticMeshTree::Primitive, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkcdStaticMeshTree::Primitive"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkUint16, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkUint16, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkUint16, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkUint16"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkcdCompressedAabbCodecs::Aabb5BytesCodec, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkcdCompressedAabbCodecs::Aabb5BytesCodec, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkcdCompressedAabbCodecs::Aabb5BytesCodec, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkcdCompressedAabbCodecs::Aabb5BytesCodec"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hkcdCompressedAabbCodecs::Aabb4BytesCodec, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hkcdCompressedAabbCodecs::Aabb4BytesCodec, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hkcdCompressedAabbCodecs::Aabb4BytesCodec, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hkcdCompressedAabbCodecs::Aabb4BytesCodec"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

template<>
bool hktypes::hkArray<hknpBSMaterial, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->GetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->GetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->GetValue(m_capacityAndFlags);
	return true;
}

template<>
bool hktypes::hkArray<hknpBSMaterial, hkContainerHeapAllocator>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("m_data")->SetValue(m_data);
	class_instance->GetInstanceByFieldName("m_size")->SetValue(m_size);
	class_instance->GetInstanceByFieldName("m_capacityAndFlags")->SetValue(m_capacityAndFlags);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkArray<hknpBSMaterial, hkContainerHeapAllocator>::GetTemplateArgs() { return {
	{"tT", "hknpBSMaterial"},
	{"tAllocator", "hkContainerHeapAllocator"},
}; };

