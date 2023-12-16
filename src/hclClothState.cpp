#include "hclClothState.h"

bool hktypes::hclTransformSetUsage::TransformTracker::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTransformSetUsage::TransformTracker") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclTransformSetUsage::TransformTracker" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("read")->GetValue(read);
	class_instance->GetInstanceByFieldName("readBeforeWrite")->GetValue(readBeforeWrite);
	class_instance->GetInstanceByFieldName("written")->GetValue(written);

	return true;
}

bool hktypes::hclTransformSetUsage::TransformTracker::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTransformSetUsage::TransformTracker") {
		std::cout << "Mismatching type conversion from hclTransformSetUsage::TransformTracker to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("read")->SetValue(read);
	class_instance->GetInstanceByFieldName("readBeforeWrite")->SetValue(readBeforeWrite);
	class_instance->GetInstanceByFieldName("written")->SetValue(written);

	return true;
}

bool hktypes::hclTransformSetUsage::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTransformSetUsage") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclTransformSetUsage" << std::endl;
		return false;
	}

	std::vector<uint8_t> _perComponentFlags;
	class_instance->GetInstanceByFieldName("perComponentFlags")->GetValue(_perComponentFlags);
	if (_perComponentFlags.size() != 2) {
		std::cout << "Mismatching size of perComponentFlags" << std::endl;
		return false;
	}
	std::memcpy(perComponentFlags, _perComponentFlags.data(), sizeof(uint8_t) * 2);

	class_instance->GetInstanceByFieldName("perComponentTransformTrackers")->GetValue(perComponentTransformTrackers);

	return true;
}

bool hktypes::hclTransformSetUsage::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclTransformSetUsage") {
		std::cout << "Mismatching type conversion from hclTransformSetUsage to " << class_instance->type->type_name << std::endl;
		return false;
	}

	std::vector<uint8_t> _perComponentFlags;
	_perComponentFlags.resize(2);
	std::memcpy(_perComponentFlags.data(), perComponentFlags, sizeof(uint8_t) * 2);
	class_instance->GetInstanceByFieldName("perComponentFlags")->SetValue(_perComponentFlags);

	class_instance->GetInstanceByFieldName("perComponentTransformTrackers")->SetValue(perComponentTransformTrackers);

	return true;
}

bool hktypes::hclBufferUsage::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferUsage") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclBufferUsage" << std::endl;
		return false;
	}

	std::vector<uint8_t> _perComponentFlags;
	class_instance->GetInstanceByFieldName("perComponentFlags")->GetValue(_perComponentFlags);
	if (_perComponentFlags.size() != 4) {
		std::cout << "Mismatching size of perComponentFlags" << std::endl;
		return false;
	}
	std::memcpy(perComponentFlags, _perComponentFlags.data(), sizeof(uint8_t) * 4);

	class_instance->GetInstanceByFieldName("trianglesRead")->GetValue(trianglesRead);
}

bool hktypes::hclBufferUsage::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclBufferUsage") {
		std::cout << "Mismatching type conversion from hclBufferUsage to " << class_instance->type->type_name << std::endl;
		return false;
	}

	std::vector<uint8_t> _perComponentFlags;
	_perComponentFlags.resize(4);
	std::memcpy(_perComponentFlags.data(), perComponentFlags, sizeof(uint8_t) * 4);
	class_instance->GetInstanceByFieldName("perComponentFlags")->SetValue(_perComponentFlags);

	class_instance->GetInstanceByFieldName("trianglesRead")->SetValue(trianglesRead);
}

bool hktypes::hclClothState::BufferAccess::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState::BufferAccess") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclClothState::BufferAccess" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("bufferIndex")->GetValue(bufferIndex);
	class_instance->GetInstanceByFieldName("bufferUsage")->GetValue(bufferUsage);
	class_instance->GetInstanceByFieldName("shadowBufferIndex")->GetValue(shadowBufferIndex);

	return true;
}

bool hktypes::hclClothState::BufferAccess::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState::BufferAccess") {
		std::cout << "Mismatching type conversion from hclClothState::BufferAccess to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("bufferIndex")->SetValue(bufferIndex);
	class_instance->GetInstanceByFieldName("bufferUsage")->SetValue(bufferUsage);
	class_instance->GetInstanceByFieldName("shadowBufferIndex")->SetValue(shadowBufferIndex);

	return true;
}

bool hktypes::hclClothState::TransformSetAccess::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState::TransformSetAccess") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclClothState::TransformSetAccess" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transformSetIndex")->GetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformSetUsage")->GetValue(transformSetUsage);

	return true;
}

bool hktypes::hclClothState::TransformSetAccess::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState::TransformSetAccess") {
		std::cout << "Mismatching type conversion from hclClothState::TransformSetAccess to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("transformSetIndex")->SetValue(transformSetIndex);
	class_instance->GetInstanceByFieldName("transformSetUsage")->SetValue(transformSetUsage);

	return true;
}

bool hktypes::hclClothState::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclClothState" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->GetValue(name);
	class_instance->GetInstanceByFieldName("operators")->GetValue(operators);
	class_instance->GetInstanceByFieldName("usedBuffers")->GetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->GetValue(usedTransformSets);
	class_instance->GetInstanceByFieldName("usedSimCloths")->GetValue(usedSimCloths);
	class_instance->GetInstanceByFieldName("dependencyGraph")->GetValue(dependencyGraph);

	return true;
}

bool hktypes::hclClothState::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclClothState") {
		std::cout << "Mismatching type conversion from hclClothState to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("name")->SetValue(name);
	class_instance->GetInstanceByFieldName("operators")->SetValue(operators);
	class_instance->GetInstanceByFieldName("usedBuffers")->SetValue(usedBuffers);
	class_instance->GetInstanceByFieldName("usedTransformSets")->SetValue(usedTransformSets);
	class_instance->GetInstanceByFieldName("usedSimCloths")->SetValue(usedSimCloths);
	class_instance->GetInstanceByFieldName("dependencyGraph")->SetValue(dependencyGraph);

	return true;
}

bool hktypes::hclStateDependencyGraph::Branch::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStateDependencyGraph::Branch") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclStateDependencyGraph::Branch" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("branchId")->GetValue(branchId);
	class_instance->GetInstanceByFieldName("stateOperatorIndices")->GetValue(stateOperatorIndices);
	class_instance->GetInstanceByFieldName("parentBranches")->GetValue(parentBranches);
	class_instance->GetInstanceByFieldName("childBranches")->GetValue(childBranches);

	return true;
}

bool hktypes::hclStateDependencyGraph::Branch::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStateDependencyGraph::Branch") {
		std::cout << "Mismatching type conversion from hclStateDependencyGraph::Branch to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("branchId")->SetValue(branchId);
	class_instance->GetInstanceByFieldName("stateOperatorIndices")->SetValue(stateOperatorIndices);
	class_instance->GetInstanceByFieldName("parentBranches")->SetValue(parentBranches);
	class_instance->GetInstanceByFieldName("childBranches")->SetValue(childBranches);

	return true;
}

bool hktypes::hclStateDependencyGraph::FromInstance(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStateDependencyGraph") {
		std::cout << "Mismatching type conversion from " << class_instance->type->type_name << " to hclStateDependencyGraph" << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("branches")->GetValue(branches);
	class_instance->GetInstanceByFieldName("rootBranchIds")->GetValue(rootBranchIds);
	class_instance->GetInstanceByFieldName("children")->GetValue(children);
	class_instance->GetInstanceByFieldName("parents")->GetValue(parents);
	class_instance->GetInstanceByFieldName("multiThreadable")->GetValue(multiThreadable);

	return true;
}

bool hktypes::hclStateDependencyGraph::ToInstance(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclStateDependencyGraph") {
		std::cout << "Mismatching type conversion from hclStateDependencyGraph to " << class_instance->type->type_name << std::endl;
		return false;
	}

	class_instance->GetInstanceByFieldName("branches")->SetValue(branches);
	class_instance->GetInstanceByFieldName("rootBranchIds")->SetValue(rootBranchIds);
	class_instance->GetInstanceByFieldName("children")->SetValue(children);
	class_instance->GetInstanceByFieldName("parents")->SetValue(parents);
	class_instance->GetInstanceByFieldName("multiThreadable")->SetValue(multiThreadable);

	return true;
}
