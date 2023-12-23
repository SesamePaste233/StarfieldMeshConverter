#include "Generated\hclBufferUsage.h"

#include "Generated\.h"

bool hktypes::hclBufferUsage::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBufferUsage") {
		std::cout << "hclBufferUsage::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("perComponentFlags")->GetValue(perComponentFlags);
	class_instance->GetInstanceByFieldName("trianglesRead")->GetValue(trianglesRead);
	return true;
}

bool hktypes::hclBufferUsage::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBufferUsage") {
		std::cout << "hclBufferUsage::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("perComponentFlags")->SetValue(perComponentFlags);
	class_instance->GetInstanceByFieldName("trianglesRead")->SetValue(trianglesRead);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBufferUsage::GetTemplateArgs() { return {
}; };

