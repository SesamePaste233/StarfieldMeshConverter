#include "Generated\hclTransformSetUsage.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclTransformSetUsage::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclTransformSetUsage") {
		std::cout << "hclTransformSetUsage::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("perComponentFlags")->GetValue(perComponentFlags);
	class_instance->GetInstanceByFieldName("perComponentTransformTrackers")->GetValue(perComponentTransformTrackers);
	return true;
}

bool hktypes::hclTransformSetUsage::TransformTracker::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclTransformSetUsage::TransformTracker") {
		std::cout << "hclTransformSetUsage::TransformTracker::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("read")->GetValue(read);
	class_instance->GetInstanceByFieldName("readBeforeWrite")->GetValue(readBeforeWrite);
	class_instance->GetInstanceByFieldName("written")->GetValue(written);
	return true;
}

bool hktypes::hclTransformSetUsage::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclTransformSetUsage") {
		std::cout << "hclTransformSetUsage::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("perComponentFlags")->SetValue(perComponentFlags);
	class_instance->GetInstanceByFieldName("perComponentTransformTrackers")->SetValue(perComponentTransformTrackers);
	return true;
}

bool hktypes::hclTransformSetUsage::TransformTracker::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclTransformSetUsage::TransformTracker") {
		std::cout << "hclTransformSetUsage::TransformTracker::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("read")->SetValue(read);
	class_instance->GetInstanceByFieldName("readBeforeWrite")->SetValue(readBeforeWrite);
	class_instance->GetInstanceByFieldName("written")->SetValue(written);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclTransformSetUsage::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclTransformSetUsage::TransformTracker::GetTemplateArgs() { return {
}; };

