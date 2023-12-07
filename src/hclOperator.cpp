#include "hclOperator.h"

bool hktypes::hclOperator::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclOperator" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("operatorID")->GetValue(operatorID);
	class_instance->GetInstanceByFieldName("type")->GetValue(type);
	class_instance->GetInstanceByFieldName("usedBuffers")->GetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->GetValue(usedTransformSets);

	return true;
}

bool hktypes::hclOperator::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclOperator") {
		std::cout << "Mismatching type conversion from hclOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("operatorID")->SetValue(operatorID);
	class_instance->GetInstanceByFieldName("type")->SetValue(type);
	class_instance->GetInstanceByFieldName("usedBuffers")->SetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->SetValue(usedTransformSets);

	return true;
}

bool hktypes::hclObjectSpaceDeformer::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclObjectSpaceDeformer") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclObjectSpaceDeformer" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("eightBlendEntries")->GetValue(eightBlendEntries);
	class_instance->GetInstanceByFieldName("sevenBlendEntries")->GetValue(sevenBlendEntries);
	class_instance->GetInstanceByFieldName("sixBlendEntries")->GetValue(sixBlendEntries);
	class_instance->GetInstanceByFieldName("fiveBlendEntries")->GetValue(fiveBlendEntries);

	class_instance->GetInstanceByFieldName("fourBlendEntries")->GetValue(fourBlendEntries);
	class_instance->GetInstanceByFieldName("threeBlendEntries")->GetValue(threeBlendEntries);
	class_instance->GetInstanceByFieldName("twoBlendEntries")->GetValue(twoBlendEntries);
	class_instance->GetInstanceByFieldName("oneBlendEntries")->GetValue(oneBlendEntries);

	class_instance->GetInstanceByFieldName("controlBytes")->GetValue(controlBytes);
	class_instance->GetInstanceByFieldName("startVertexIndex")->GetValue(startVertexIndex);
	class_instance->GetInstanceByFieldName("endVertexIndex")->GetValue(endVertexIndex);
	class_instance->GetInstanceByFieldName("partialWrite")->GetValue(partialWrite);

	return true;
}

bool hktypes::hclObjectSpaceDeformer::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclObjectSpaceDeformer") {
		std::cout << "Mismatching type conversion from hclObjectSpaceDeformer to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("eightBlendEntries")->SetValue(eightBlendEntries);
	class_instance->GetInstanceByFieldName("sevenBlendEntries")->SetValue(sevenBlendEntries);
	class_instance->GetInstanceByFieldName("sixBlendEntries")->SetValue(sixBlendEntries);
	class_instance->GetInstanceByFieldName("fiveBlendEntries")->SetValue(fiveBlendEntries);

	class_instance->GetInstanceByFieldName("fourBlendEntries")->SetValue(fourBlendEntries);
	class_instance->GetInstanceByFieldName("threeBlendEntries")->SetValue(threeBlendEntries);
	class_instance->GetInstanceByFieldName("twoBlendEntries")->SetValue(twoBlendEntries);
	class_instance->GetInstanceByFieldName("oneBlendEntries")->SetValue(oneBlendEntries);

	class_instance->GetInstanceByFieldName("controlBytes")->SetValue(controlBytes);
	class_instance->GetInstanceByFieldName("startVertexIndex")->SetValue(startVertexIndex);
	class_instance->GetInstanceByFieldName("endVertexIndex")->SetValue(endVertexIndex);
	class_instance->GetInstanceByFieldName("partialWrite")->SetValue(partialWrite);

	return true;
}

bool hktypes::hclObjectSpaceSkinOperator::FromInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclObjectSpaceSkinOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclObjectSpaceSkinOperator" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	std::vector<hkMatrix4Holder> _boneFromSkinMeshTransforms;
	class_instance->GetInstanceByFieldName("boneFromSkinMeshTransforms")->GetValue(_boneFromSkinMeshTransforms);
	boneFromSkinMeshTransforms.resize(_boneFromSkinMeshTransforms.size());
	for (int i = 0; i < _boneFromSkinMeshTransforms.size(); i++) {
		boneFromSkinMeshTransforms[i] = _boneFromSkinMeshTransforms[i].ToMatrix4f();
	}

	class_instance->GetInstanceByFieldName("transformSubset")->GetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->GetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("objectSpaceDeformer")->GetValue(objectSpaceDeformer);

	return true;
}

bool hktypes::hclObjectSpaceSkinOperator::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclObjectSpaceSkinOperator") {
		std::cout << "Mismatching type conversion from hclObjectSpaceSkinOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	std::vector<hkMatrix4Holder> _boneFromSkinMeshTransforms;
	_boneFromSkinMeshTransforms.resize(boneFromSkinMeshTransforms.size());
	for (int i = 0; i < boneFromSkinMeshTransforms.size(); i++) {
		_boneFromSkinMeshTransforms[i].FromMatrix4f(boneFromSkinMeshTransforms[i]);
	}
	class_instance->GetInstanceByFieldName("boneFromSkinMeshTransforms")->SetValue(_boneFromSkinMeshTransforms);

	class_instance->GetInstanceByFieldName("transformSubset")->SetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->SetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("objectSpaceDeformer")->SetValue(objectSpaceDeformer);

	return true;
}

bool hktypes::hclObjectSpaceSkinPNOperator::FromInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclObjectSpaceSkinPNOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclObjectSpaceSkinPNOperator" << std::endl;
		return false;
	}

	hclObjectSpaceSkinOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("localPNs")->GetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->GetValue(localUnpackedPNs);

	return true;
}

bool hktypes::hclObjectSpaceSkinPNOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclObjectSpaceSkinPNOperator") {
		std::cout << "Mismatching type conversion from hclObjectSpaceSkinPNOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclObjectSpaceSkinOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("localPNs")->SetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->SetValue(localUnpackedPNs);

	return true;
}

bool hktypes::hclMoveParticlesOperator::VertexParticlePair::FromInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclMoveParticlesOperator::VertexParticlePair") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclMoveParticlesOperator::VertexParticlePair" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("vertexIndex")->GetValue(vertexIndex);
	class_instance->GetInstanceByFieldName("particleIndex")->GetValue(particleIndex);

	return true;
}

bool hktypes::hclMoveParticlesOperator::VertexParticlePair::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclMoveParticlesOperator::VertexParticlePair") {
		std::cout << "Mismatching type conversion from hclMoveParticlesOperator::VertexParticlePair to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("vertexIndex")->SetValue(vertexIndex);
	class_instance->GetInstanceByFieldName("particleIndex")->SetValue(particleIndex);

	return true;
}

bool hktypes::hclMoveParticlesOperator::FromInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclMoveParticlesOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclMoveParticlesOperator" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("vertexParticlePairs")->GetValue(vertexParticlePairs);
	class_instance->GetInstanceByFieldName("simClothIndex")->GetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("refBufferIdx")->GetValue(refBufferIdx);

	return true;
}

bool hktypes::hclMoveParticlesOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclMoveParticlesOperator") {
		std::cout << "Mismatching type conversion from hclMoveParticlesOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("vertexParticlePairs")->SetValue(vertexParticlePairs);
	class_instance->GetInstanceByFieldName("simClothIndex")->SetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("refBufferIdx")->SetValue(refBufferIdx);

	return true;
}

bool hktypes::hclSimulateOperator::Config::FromInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimulateOperator::Config") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclSimulateOperator::Config" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("constraintExecution")->GetValue(constraintExecution);
	class_instance->GetInstanceByFieldName("instanceCollidablesUsed")->GetValue(instanceCollidablesUsed);
	class_instance->GetInstanceByFieldName("subSteps")->GetValue(subSteps);
	class_instance->GetInstanceByFieldName("numberOfSolveIterations")->GetValue(numberOfSolveIterations);
	class_instance->GetInstanceByFieldName("useAllInstanceCollidables")->GetValue(useAllInstanceCollidables);
	class_instance->GetInstanceByFieldName("adaptConstraintStiffness")->GetValue(adaptConstraintStiffness);

	return true;
}

bool hktypes::hclSimulateOperator::Config::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimulateOperator::Config") {
		std::cout << "Mismatching type conversion from hclSimulateOperator::Config to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("constraintExecution")->SetValue(constraintExecution);
	class_instance->GetInstanceByFieldName("instanceCollidablesUsed")->SetValue(instanceCollidablesUsed);
	class_instance->GetInstanceByFieldName("subSteps")->SetValue(subSteps);
	class_instance->GetInstanceByFieldName("numberOfSolveIterations")->SetValue(numberOfSolveIterations);
	class_instance->GetInstanceByFieldName("useAllInstanceCollidables")->SetValue(useAllInstanceCollidables);
	class_instance->GetInstanceByFieldName("adaptConstraintStiffness")->SetValue(adaptConstraintStiffness);

	return true;
}

bool hktypes::hclSimulateOperator::FromInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclSimulateOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclSimulateOperator" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("simClothIndex")->GetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("simulateOpConfigs")->GetValue(simulateOpConfigs);

	return true;
}

bool hktypes::hclSimulateOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclSimulateOperator") {
		std::cout << "Mismatching type conversion from hclSimulateOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("simClothIndex")->SetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("simulateOpConfigs")->SetValue(simulateOpConfigs);

	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::FromInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator::TriangleBonePair") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclSimpleMeshBoneDeformOperator::TriangleBonePair" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("boneOffset")->GetValue(boneOffset);
	class_instance->GetInstanceByFieldName("triangleOffset")->GetValue(triangleOffset);

	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator::TriangleBonePair") {
		std::cout << "Mismatching type conversion from hclSimpleMeshBoneDeformOperator::TriangleBonePair to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("boneOffset")->SetValue(boneOffset);
	class_instance->GetInstanceByFieldName("triangleOffset")->SetValue(triangleOffset);

	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::FromInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclSimpleMeshBoneDeformOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclSimpleMeshBoneDeformOperator" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("inputBufferIdx")->GetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputTransformSetIdx")->GetValue(outputTransformSetIdx);
	class_instance->GetInstanceByFieldName("triangleBonePairs")->GetValue(triangleBonePairs);
	class_instance->GetInstanceByFieldName("localBoneTransforms")->GetValue(localBoneTransforms);

	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclSimpleMeshBoneDeformOperator") {
		std::cout << "Mismatching type conversion from hclSimpleMeshBoneDeformOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("inputBufferIdx")->SetValue(inputBufferIdx);
	class_instance->GetInstanceByFieldName("outputTransformSetIdx")->SetValue(outputTransformSetIdx);
	class_instance->GetInstanceByFieldName("triangleBonePairs")->SetValue(triangleBonePairs);
	class_instance->GetInstanceByFieldName("localBoneTransforms")->SetValue(localBoneTransforms);

	return true;
}

bool hktypes::hclCopyVerticesOperator::FromInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclCopyVerticesOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclCopyVerticesOperator" << std::endl;
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

	if (class_instance->type->type_name == "hclCopyVerticesOperator") {
		std::cout << "Mismatching type conversion from hclCopyVerticesOperator to " << class_instance->type->type_name << std::endl;
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

bool hktypes::hclObjectSpaceDeformer::LocalBlockPN::FromInstance(hkreflex::hkClassInstance* instance)
{
	return false;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockPN::ToInstance(hkreflex::hkClassInstance* instance)
{
	return false;
}
