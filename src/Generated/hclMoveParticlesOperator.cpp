#include "Generated\hclMoveParticlesOperator.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclMoveParticlesOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclMoveParticlesOperator") {
		std::cout << "hclMoveParticlesOperator::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("vertexParticlePairs")->GetValue(vertexParticlePairs);
	class_instance->GetInstanceByFieldName("simClothIndex")->GetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("refBufferIdx")->GetValue(refBufferIdx);
	return true;
}

bool hktypes::hclMoveParticlesOperator::VertexParticlePair::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclMoveParticlesOperator::VertexParticlePair") {
		std::cout << "hclMoveParticlesOperator::VertexParticlePair::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndex")->GetValue(vertexIndex);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);
	return true;
}

bool hktypes::hclMoveParticlesOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclMoveParticlesOperator") {
		std::cout << "hclMoveParticlesOperator::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("vertexParticlePairs")->SetValue(vertexParticlePairs);
	class_instance->GetInstanceByFieldName("simClothIndex")->SetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("refBufferIdx")->SetValue(refBufferIdx);
	return true;
}

bool hktypes::hclMoveParticlesOperator::VertexParticlePair::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclMoveParticlesOperator::VertexParticlePair") {
		std::cout << "hclMoveParticlesOperator::VertexParticlePair::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertexIndex")->SetValue(vertexIndex);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclMoveParticlesOperator::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclMoveParticlesOperator::VertexParticlePair::GetTemplateArgs() { return {
}; };

