#include "Generated\hkArray.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\hknpPhysicsSystemData.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\hkRefCountedProperties.h"

template<>
bool hktypes::hkArray<hknpMaterial, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hkArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hkArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hkArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hkArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hkArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hkArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hkArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
bool hktypes::hkArray<hkRefCountedProperties::Entry, hkContainerHeapAllocator>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::FromInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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
	if (!class_instance) {
		std::cout << "hkArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkArray") {
		std::cout << "hkArray::ToInstance: Expecting hkArray but got " << class_instance->type->type_name << std::endl;
		return false;
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

