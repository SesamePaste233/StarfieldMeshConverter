#include "Generated\hclCopyVerticesOperator.h"

bool hktypes::hclCopyVerticesOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCopyVerticesOperator") {
		std::cout << "hclCopyVerticesOperator::FromInstance: Wrong type!" << std::endl;
		return false;
	}

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
	if (class_instance->type->type_name != "hclCopyVerticesOperator") {
		std::cout << "hclCopyVerticesOperator::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("inputBufferIdx")->SetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputBufferIdx")->SetValue(outputBufferIdx);
	class_instance->GetInstanceByFieldName("numberOfVertices")->SetValue(numberOfVertices);
	class_instance->GetInstanceByFieldName("startVertexIn")->SetValue(startVertexIn);
	class_instance->GetInstanceByFieldName("startVertexOut")->SetValue(startVertexOut);
	class_instance->GetInstanceByFieldName("copyNormals")->SetValue(copyNormals);
	return true;
}

