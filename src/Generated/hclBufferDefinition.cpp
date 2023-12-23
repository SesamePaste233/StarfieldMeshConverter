#include "Generated\hclBufferDefinition.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclBufferDefinition::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBufferDefinition") {
		std::cout << "hclBufferDefinition::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("meshName")->GetValue(meshName);
	class_instance->GetInstanceByFieldName("bufferName")->GetValue(bufferName);
	class_instance->GetInstanceByFieldName("type")->GetValue(type);
	class_instance->GetInstanceByFieldName("subType")->GetValue(subType);
	class_instance->GetInstanceByFieldName("numVertices")->GetValue(numVertices);
	class_instance->GetInstanceByFieldName("numTriangles")->GetValue(numTriangles);
	class_instance->GetInstanceByFieldName("bufferLayout")->GetValue(bufferLayout);
	return true;
}

bool hktypes::hclBufferDefinition::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclBufferDefinition") {
		std::cout << "hclBufferDefinition::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("meshName")->SetValue(meshName);
	class_instance->GetInstanceByFieldName("bufferName")->SetValue(bufferName);
	class_instance->GetInstanceByFieldName("type")->SetValue(type);
	class_instance->GetInstanceByFieldName("subType")->SetValue(subType);
	class_instance->GetInstanceByFieldName("numVertices")->SetValue(numVertices);
	class_instance->GetInstanceByFieldName("numTriangles")->SetValue(numTriangles);
	class_instance->GetInstanceByFieldName("bufferLayout")->SetValue(bufferLayout);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclBufferDefinition::GetTemplateArgs() { return {
}; };

