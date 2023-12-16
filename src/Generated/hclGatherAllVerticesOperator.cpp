#include "Generated\hclGatherAllVerticesOperator.h"

bool hktypes::hclGatherAllVerticesOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclGatherAllVerticesOperator") {
		std::cout << "hclGatherAllVerticesOperator::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("vertexInputFromVertexOutput")->GetValue(vertexInputFromVertexOutput);
	class_instance->GetInstanceByFieldName("inputBufferIdx")->GetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputBufferIdx")->GetValue(outputBufferIdx);
	class_instance->GetInstanceByFieldName("gatherNormals")->GetValue(gatherNormals);
	class_instance->GetInstanceByFieldName("partialGather")->GetValue(partialGather);
	return true;
}

bool hktypes::hclGatherAllVerticesOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclGatherAllVerticesOperator") {
		std::cout << "hclGatherAllVerticesOperator::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("vertexInputFromVertexOutput")->SetValue(vertexInputFromVertexOutput);
	class_instance->GetInstanceByFieldName("inputBufferIdx")->SetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputBufferIdx")->SetValue(outputBufferIdx);
	class_instance->GetInstanceByFieldName("gatherNormals")->SetValue(gatherNormals);
	class_instance->GetInstanceByFieldName("partialGather")->SetValue(partialGather);
	return true;
}

inline std::vector<std::string> hktypes::hclGatherAllVerticesOperator::GetTemplateArgs() { return {
}; };

inline std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> hktypes::hclGatherAllVerticesOperator::GetFieldTypeAndNames() { return {
	{ "hkArray<hkInt16, hkContainerHeapAllocator>", { "vertexInputFromVertexOutput", 72, 32 } },
	{ "hkUint32", { "inputBufferIdx", 88, 32 } },
	{ "hkUint32", { "outputBufferIdx", 92, 32 } },
	{ "hkBool", { "gatherNormals", 96, 32 } },
	{ "hkBool", { "partialGather", 97, 32 } },
}; };

