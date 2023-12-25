#include "Generated\hclCopyVerticesOperator.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclCopyVerticesOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclCopyVerticesOperator") {
		std::cout << "hclCopyVerticesOperator::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("inputBufferIdx")->GetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputBufferIdx")->GetValue(outputBufferIdx);
	class_instance->GetInstanceByFieldName("numberOfVertices")->GetValue(numberOfVertices);
	class_instance->GetInstanceByFieldName("startVertexIn")->GetValue(startVertexIn);
	class_instance->GetInstanceByFieldName("startVertexOut")->GetValue(startVertexOut);
	class_instance->GetInstanceByFieldName("copyNormals")->GetValue(copyNormals);
	return true;
}

bool hktypes::hclCopyVerticesOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclCopyVerticesOperator") {
		std::cout << "hclCopyVerticesOperator::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("inputBufferIdx")->SetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputBufferIdx")->SetValue(outputBufferIdx);
	class_instance->GetInstanceByFieldName("numberOfVertices")->SetValue(numberOfVertices);
	class_instance->GetInstanceByFieldName("startVertexIn")->SetValue(startVertexIn);
	class_instance->GetInstanceByFieldName("startVertexOut")->SetValue(startVertexOut);
	class_instance->GetInstanceByFieldName("copyNormals")->SetValue(copyNormals);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclCopyVerticesOperator::GetTemplateArgs() { return {
}; };

