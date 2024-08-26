#include "Generated\hkRefPtr.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

template<>
bool hktypes::hkRefPtr<hknpShape>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::FromInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->GetValue(ptr);
	return true;
}

template<>
bool hktypes::hkRefPtr<hknpShape>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::ToInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->SetValue(ptr);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefPtr<hknpShape>::GetTemplateArgs() { return {
	{"tTYPE", "hknpShape"},
}; };

template<>
bool hktypes::hkRefPtr<hknpRefMassDistribution>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::FromInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->GetValue(ptr);
	return true;
}

template<>
bool hktypes::hkRefPtr<hknpRefMassDistribution>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::ToInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->SetValue(ptr);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefPtr<hknpRefMassDistribution>::GetTemplateArgs() { return {
	{"tTYPE", "hknpRefMassDistribution"},
}; };

template<>
bool hktypes::hkRefPtr<hknpRefDragProperties>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::FromInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->GetValue(ptr);
	return true;
}

template<>
bool hktypes::hkRefPtr<hknpRefDragProperties>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::ToInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->SetValue(ptr);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefPtr<hknpRefDragProperties>::GetTemplateArgs() { return {
	{"tTYPE", "hknpRefDragProperties"},
}; };

template<>
bool hktypes::hkRefPtr<hkLocalFrame>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::FromInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->GetValue(ptr);
	return true;
}

template<>
bool hktypes::hkRefPtr<hkLocalFrame>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::ToInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->SetValue(ptr);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefPtr<hkLocalFrame>::GetTemplateArgs() { return {
	{"tTYPE", "hkLocalFrame"},
}; };

template<>
bool hktypes::hkRefPtr<hkRefCountedProperties>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::FromInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->GetValue(ptr);
	return true;
}

template<>
bool hktypes::hkRefPtr<hkRefCountedProperties>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::ToInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->SetValue(ptr);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefPtr<hkRefCountedProperties>::GetTemplateArgs() { return {
	{"tTYPE", "hkRefCountedProperties"},
}; };

template<>
bool hktypes::hkRefPtr<hkReferencedObject>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::FromInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->GetValue(ptr);
	return true;
}

template<>
bool hktypes::hkRefPtr<hkReferencedObject>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRefPtr::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRefPtr") {
		std::cout << "hkRefPtr::ToInstance: Expecting hkRefPtr but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("ptr")->SetValue(ptr);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRefPtr<hkReferencedObject>::GetTemplateArgs() { return {
	{"tTYPE", "hkReferencedObject"},
}; };

