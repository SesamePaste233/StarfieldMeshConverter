#include "hclOperator.h"

bool hktypes::hclOperator::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclOperator") {
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
	if (class_instance->type->type_name != "hclOperator") {
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

bool hktypes::hclObjectSpaceDeformer::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer") {
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
	if (class_instance->type->type_name != "hclObjectSpaceDeformer") {
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

bool hktypes::hclObjectSpaceSkinOperator::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceSkinOperator") {
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
	if (class_instance->type->type_name != "hclObjectSpaceSkinOperator") {
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

bool hktypes::hclObjectSpaceSkinPNOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceSkinPNOperator") {
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
	if (class_instance->type->type_name != "hclObjectSpaceSkinPNOperator") {
		std::cout << "Mismatching type conversion from hclObjectSpaceSkinPNOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclObjectSpaceSkinOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("localPNs")->SetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->SetValue(localUnpackedPNs);

	return true;
}

bool hktypes::hclMoveParticlesOperator::VertexParticlePair::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
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

bool hktypes::hclMoveParticlesOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclMoveParticlesOperator") {
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
	if (class_instance->type->type_name != "hclMoveParticlesOperator") {
		std::cout << "Mismatching type conversion from hclMoveParticlesOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("vertexParticlePairs")->SetValue(vertexParticlePairs);
	class_instance->GetInstanceByFieldName("simClothIndex")->SetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("refBufferIdx")->SetValue(refBufferIdx);

	return true;
}

bool hktypes::hclSimulateOperator::Config::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
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

bool hktypes::hclSimulateOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimulateOperator") {
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
	if (class_instance->type->type_name != "hclSimulateOperator") {
		std::cout << "Mismatching type conversion from hclSimulateOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("simClothIndex")->SetValue(simClothIndex);
	class_instance->GetInstanceByFieldName("simulateOpConfigs")->SetValue(simulateOpConfigs);

	return true;
}

bool hktypes::hclSimpleMeshBoneDeformOperator::TriangleBonePair::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
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

bool hktypes::hclSimpleMeshBoneDeformOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator") {
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
	if (class_instance->type->type_name != "hclSimpleMeshBoneDeformOperator") {
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

bool hktypes::hclCopyVerticesOperator::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclCopyVerticesOperator") {
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

	if (class_instance->type->type_name != "hclCopyVerticesOperator") {
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

bool hktypes::hclObjectSpaceDeformer::LocalBlockPN::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockPN") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to LocalBlockPN" << std::endl;
		return false;
	}

	std::vector<hkPackedVector3> _localPosition;
	class_instance->GetInstanceByFieldName("localPosition")->GetValue(_localPosition);
	if (_localPosition.size() != 16) {
		throw std::runtime_error("localPosition for LocalBlockPN: size is not 16");
		return false;
	}
	std::memcpy(localPosition, _localPosition.data(), 16 * sizeof(hkPackedVector3));

	std::vector<hkPackedVector3> _localNormal;
	class_instance->GetInstanceByFieldName("localNormal")->GetValue(_localNormal);
	if (_localNormal.size() != 16) {
		throw std::runtime_error("localNormal for LocalBlockPN: size is not 16");
		return false;
	}
	std::memcpy(localNormal, _localNormal.data(), 16 * sizeof(hkPackedVector3));

	return true;
}

bool hktypes::hclObjectSpaceDeformer::LocalBlockPN::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclObjectSpaceDeformer::LocalBlockPN") {
		std::cout << "Mismatching type conversion from LocalBlockPN to " << class_instance->type->type_name << std::endl;
		return false;
	}

	std::vector<hkPackedVector3> _localPosition;
	_localPosition.resize(16);
	for (int i = 0; i < 16; i++) {
		_localPosition[i] = localPosition[i];
	}
	class_instance->GetInstanceByFieldName("localPosition")->SetValue(_localPosition);

	std::vector<hkPackedVector3> _localNormal;
	_localNormal.resize(16);
	for (int i = 0; i < 16; i++) {
		_localNormal[i] = localNormal[i];
	}
	class_instance->GetInstanceByFieldName("localNormal")->SetValue(_localNormal);

	return true;
}

bool hktypes::hclGatherAllVerticesOperator::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclGatherAllVerticesOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclGatherAllVerticesOperator" << std::endl;
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

bool hktypes::hclGatherAllVerticesOperator::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclGatherAllVerticesOperator") {
		std::cout << "Mismatching type conversion from hclGatherAllVerticesOperator to " << class_instance->type->type_name << std::endl;
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

bool hktypes::hclBoneSpaceDeformer::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBoneSpaceDeformer") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclBoneSpaceDeformer" << std::endl;
		return false;
	}

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

bool hktypes::hclBoneSpaceDeformer::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBoneSpaceDeformer") {
		std::cout << "Mismatching type conversion from hclBoneSpaceDeformer to " << class_instance->type->type_name << std::endl;
		return false;
	}

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

bool hktypes::hclBoneSpaceDeformer::LocalBlockPN::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockPN") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to LocalBlockPN" << std::endl;
		return false;
	}

	std::vector<hkVector4Holder> _localPosition;
	class_instance->GetInstanceByFieldName("localPosition")->GetValue(_localPosition);
	if (_localPosition.size() != 16) {
		throw std::runtime_error("localPosition for LocalBlockPN: size is not 16");
		return false;
	}
	std::memcpy(localPosition, _localPosition.data(), 16 * sizeof(hkVector4Holder));

	std::vector<hkPackedVector3> _localNormal;
	class_instance->GetInstanceByFieldName("localNormal")->GetValue(_localNormal);
	if (_localNormal.size() != 16) {
		throw std::runtime_error("localNormal for LocalBlockPN: size is not 16");
		return false;
	}
	std::memcpy(localNormal, _localNormal.data(), 16 * sizeof(hkPackedVector3));

	return true;
}

bool hktypes::hclBoneSpaceDeformer::LocalBlockPN::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBoneSpaceDeformer::LocalBlockPN") {
		std::cout << "Mismatching type conversion from LocalBlockPN to " << class_instance->type->type_name << std::endl;
		return false;
	}

	std::vector<hkVector4Holder> _localPosition;
	_localPosition.resize(16);
	for (int i = 0; i < 16; i++) {
		_localPosition[i] = localPosition[i];
	}
	class_instance->GetInstanceByFieldName("localPosition")->SetValue(_localPosition);

	std::vector<hkPackedVector3> _localNormal;
	_localNormal.resize(16);
	for (int i = 0; i < 16; i++) {
		_localNormal[i] = localNormal[i];
	}
	class_instance->GetInstanceByFieldName("localNormal")->SetValue(_localNormal);

	return true;
}

bool hktypes::hclBoneSpaceSkinOperator::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBoneSpaceSkinOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclBoneSpaceSkinOperator" << std::endl;
		return false;
	}

	hclOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("transformSubset")->GetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->GetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("boneSpaceDeformer")->GetValue(boneSpaceDeformer);

	return true;
}

bool hktypes::hclBoneSpaceSkinOperator::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBoneSpaceSkinOperator") {
		std::cout << "Mismatching type conversion from hclBoneSpaceSkinOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("transformSubset")->SetValue(transformSubset);
	class_instance->GetInstanceByFieldName("outputBufferIndex")->SetValue(outputBufferIndex);
	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("boneSpaceDeformer")->SetValue(boneSpaceDeformer);

	return true;
}

bool hktypes::hclBoneSpaceSkinPNOperator::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBoneSpaceSkinPNOperator") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclBoneSpaceSkinPNOperator" << std::endl;
		return false;
	}

	hclBoneSpaceSkinOperator::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("localPNs")->GetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->GetValue(localUnpackedPNs);

	return true;
}

bool hktypes::hclBoneSpaceSkinPNOperator::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

	if (class_instance->type->type_name != "hclBoneSpaceSkinPNOperator") {
		std::cout << "Mismatching type conversion from hclBoneSpaceSkinPNOperator to " << class_instance->type->type_name << std::endl;
		return false;
	}

	hclBoneSpaceSkinOperator::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));

	class_instance->GetInstanceByFieldName("localPNs")->SetValue(localPNs);
	class_instance->GetInstanceByFieldName("localUnpackedPNs")->SetValue(localUnpackedPNs);

	return true;
}
