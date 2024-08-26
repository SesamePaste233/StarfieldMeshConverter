#include "Generated\hkRelArray.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\hknpConvexHull.h"
#include "Generated\hknpConvexHull.h"

template<>
bool hktypes::hkRelArray<hkFloat3>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::FromInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->GetValue(offset);
	class_instance->GetInstanceByFieldName("size")->GetValue(size);
	return true;
}

template<>
bool hktypes::hkRelArray<hkFloat3>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::ToInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->SetValue(offset);
	class_instance->GetInstanceByFieldName("size")->SetValue(size);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRelArray<hkFloat3>::GetTemplateArgs() { return {
	{"tT", "hkFloat3"},
}; };

template<>
bool hktypes::hkRelArray<hkVector4>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::FromInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->GetValue(offset);
	class_instance->GetInstanceByFieldName("size")->GetValue(size);
	return true;
}

template<>
bool hktypes::hkRelArray<hkVector4>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::ToInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->SetValue(offset);
	class_instance->GetInstanceByFieldName("size")->SetValue(size);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRelArray<hkVector4>::GetTemplateArgs() { return {
	{"tT", "hkVector4"},
}; };

template<>
bool hktypes::hkRelArray<hknpConvexHull::Face>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::FromInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->GetValue(offset);
	class_instance->GetInstanceByFieldName("size")->GetValue(size);
	return true;
}

template<>
bool hktypes::hkRelArray<hknpConvexHull::Face>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::ToInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->SetValue(offset);
	class_instance->GetInstanceByFieldName("size")->SetValue(size);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRelArray<hknpConvexHull::Face>::GetTemplateArgs() { return {
	{"tT", "hknpConvexHull::Face"},
}; };

template<>
bool hktypes::hkRelArray<hkUint8>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::FromInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->GetValue(offset);
	class_instance->GetInstanceByFieldName("size")->GetValue(size);
	return true;
}

template<>
bool hktypes::hkRelArray<hkUint8>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::ToInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->SetValue(offset);
	class_instance->GetInstanceByFieldName("size")->SetValue(size);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRelArray<hkUint8>::GetTemplateArgs() { return {
	{"tT", "hkUint8"},
}; };

template<>
bool hktypes::hkRelArray<hknpConvexHull::Edge>::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::FromInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->GetValue(offset);
	class_instance->GetInstanceByFieldName("size")->GetValue(size);
	return true;
}

template<>
bool hktypes::hkRelArray<hknpConvexHull::Edge>::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hkRelArray::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hkRelArray") {
		std::cout << "hkRelArray::ToInstance: Expecting hkRelArray but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("offset")->SetValue(offset);
	class_instance->GetInstanceByFieldName("size")->SetValue(size);
	return true;
}

template<>
inline std::vector<std::pair<std::string, std::string>> hktypes::hkRelArray<hknpConvexHull::Edge>::GetTemplateArgs() { return {
	{"tT", "hknpConvexHull::Edge"},
}; };

