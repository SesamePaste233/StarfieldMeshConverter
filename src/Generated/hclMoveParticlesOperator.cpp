#include "Generated\hclMoveParticlesOperator.h"

bool hktypes::hclMoveParticlesOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclMoveParticlesOperator") {
		std::cout << "hclMoveParticlesOperator::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("vertexParticlePairs")->GetValue(vertexParticlePairs);
	class_instance->GetInstanceByFieldName("simClothIndex")->GetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("refBufferIdx")->GetValue(refBufferIdx);
	return true;
}

bool hktypes::hclMoveParticlesOperator::VertexParticlePair::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclMoveParticlesOperator::VertexParticlePair") {
		std::cout << "hclMoveParticlesOperator::VertexParticlePair::FromInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("vertexIndex")->GetValue(vertexIndex);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	return true;
}

bool hktypes::hclMoveParticlesOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclMoveParticlesOperator") {
		std::cout << "hclMoveParticlesOperator::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("vertexParticlePairs")->SetValue(vertexParticlePairs);
	class_instance->GetInstanceByFieldName("simClothIndex")->SetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("refBufferIdx")->SetValue(refBufferIdx);
	return true;
}

bool hktypes::hclMoveParticlesOperator::VertexParticlePair::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclMoveParticlesOperator::VertexParticlePair") {
		std::cout << "hclMoveParticlesOperator::VertexParticlePair::ToInstance: Wrong type!" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("vertexIndex")->SetValue(vertexIndex);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	return true;
}

