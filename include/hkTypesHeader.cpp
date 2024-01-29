#include "hkTypesHeader.h"

hktypes::hclBufferUsage hktypes::operator|(const hclBufferUsage& buffer1, const hclBufferUsage& buffer2)
{
    hclBufferUsage out;
    for (uint8_t i = 0; i < 4; i++) {
        out.perComponentFlags[i] = buffer1.perComponentFlags[i] | buffer2.perComponentFlags[i];
    }
    out.trianglesRead = buffer1.trianglesRead || buffer2.trianglesRead;
    return out;
}

hktypes::hclTransformSetUsage::TransformTracker hktypes::operator|(const hclTransformSetUsage::TransformTracker& transform_tracker1, const hclTransformSetUsage::TransformTracker& transform_tracker2)
{
    hclTransformSetUsage::TransformTracker out;
	out.read = transform_tracker1.read | transform_tracker2.read;
	out.readBeforeWrite = transform_tracker1.readBeforeWrite | transform_tracker2.readBeforeWrite;
	out.written = transform_tracker1.written | transform_tracker2.written;
	return out;
}

hktypes::hclTransformSetUsage hktypes::operator|(const hclTransformSetUsage& transform_usage1, const hclTransformSetUsage& transform_usage2)
{
    hclTransformSetUsage out;
    for (uint8_t i = 0; i < 2; i++) {
		out.perComponentFlags[i] = transform_usage1.perComponentFlags[i] | transform_usage2.perComponentFlags[i];
	}
    for (uint32_t i = 0; i < 2; i++) {
		out.perComponentTransformTrackers[i] = transform_usage1.perComponentTransformTrackers[i] | transform_usage2.perComponentTransformTrackers[i];
	}
	return out;
}

hktypes::hclClothState::BufferAccess hktypes::operator|(const hclClothState::BufferAccess& buffer_access1, const hclClothState::BufferAccess& buffer_access2)
{
	if (!AccessSameBuffer(buffer_access1, buffer_access2)) {
		throw std::runtime_error("Buffer indices do not match");
	}
	hclClothState::BufferAccess out;
	out.bufferIndex = buffer_access1.bufferIndex;
	out.shadowBufferIndex = buffer_access1.shadowBufferIndex;
	out.bufferUsage = buffer_access1.bufferUsage | buffer_access2.bufferUsage;
	return out;
}

hktypes::hclClothState::BufferAccess hktypes::CombineBufferAccess(const std::vector<hclClothState::BufferAccess>& buffer_accesses)
{
	if (buffer_accesses.empty()) {
		throw std::runtime_error("Buffer accesses is empty");
	}
	hclClothState::BufferAccess out = buffer_accesses[0];
	for (int i = 1; i < buffer_accesses.size(); i++) {
		out = out | buffer_accesses[i];
	}
	return out;
}

bool hktypes::AccessSameBuffer(const hclClothState::BufferAccess& buffer_access1, const hclClothState::BufferAccess& buffer_access2)
{
	return buffer_access1.bufferIndex == buffer_access2.bufferIndex && buffer_access1.shadowBufferIndex == buffer_access2.shadowBufferIndex;
}

hktypes::hclClothState::TransformSetAccess hktypes::operator|(const hclClothState::TransformSetAccess& transform_set_access1, const hclClothState::TransformSetAccess& transform_set_access2)
{
	if (!AccessSameTransformSet(transform_set_access1, transform_set_access2)) {
		throw std::runtime_error("Transform set indices do not match");
	}
	hclClothState::TransformSetAccess out;
	out.transformSetIndex = transform_set_access1.transformSetIndex;
	out.transformSetUsage = transform_set_access1.transformSetUsage | transform_set_access2.transformSetUsage;
	return out;
}

hktypes::hclClothState::TransformSetAccess hktypes::CombineTransformSetAccess(const std::vector<hclClothState::TransformSetAccess>& transform_set_accesses)
{
	if (transform_set_accesses.empty()) {
		throw std::runtime_error("Transform set accesses is empty");
	}
	hclClothState::TransformSetAccess out = transform_set_accesses[0];
	for (int i = 1; i < transform_set_accesses.size(); i++) {
		out = out | transform_set_accesses[i];
	}
	return out;
}

bool hktypes::AccessSameTransformSet(const hclClothState::TransformSetAccess& transform_set_access1, const hclClothState::TransformSetAccess& transform_set_access2)
{
	return transform_set_access1.transformSetIndex == transform_set_access2.transformSetIndex;
}

hktypes::hclClothState::BufferAccess hktypes::FromBufferUsage(uint32_t buffer_index, hclBufferUsage buffer_usage, uint32_t shadow_buffer_index)
{
	hclClothState::BufferAccess out;
	out.bufferIndex = buffer_index;
	if (shadow_buffer_index == uint32_t(-1)) {
		out.shadowBufferIndex = buffer_index;
	}
	else {
		out.shadowBufferIndex = shadow_buffer_index;
	}
	out.bufferUsage = buffer_usage;
	return out;
}

hktypes::hclClothState::BufferAccess hktypes::BufferAccessFromParameters(uint32_t buffer_index, uint8_t position_usage, uint8_t normal_usage, uint8_t tangent_usage, uint8_t bitangent_usage, bool triangles_read, uint32_t shadow_buffer_index)
{
	hclClothState::BufferAccess out;
	out.bufferIndex = buffer_index;
	if (shadow_buffer_index == uint32_t(-1)) {
		out.shadowBufferIndex = buffer_index;
	}
	else {
		out.shadowBufferIndex = shadow_buffer_index;
	}
	out.bufferUsage.perComponentFlags[0] = position_usage;
	out.bufferUsage.perComponentFlags[1] = normal_usage;
	out.bufferUsage.perComponentFlags[2] = tangent_usage;
	out.bufferUsage.perComponentFlags[3] = bitangent_usage;
	out.bufferUsage.trianglesRead = triangles_read;
	return out;
}

hktypes::hclClothState::TransformSetAccess hktypes::FromTransformSetUsage(uint32_t transform_set_index, hclTransformSetUsage transform_set_usage)
{
	hclClothState::TransformSetAccess out;
	out.transformSetIndex = transform_set_index;
	out.transformSetUsage = transform_set_usage;
	return out;
}

hktypes::hclScratchBufferDefinition hktypes::DefaultScratchBufferDefinition()
{
    hclScratchBufferDefinition out;
	out.meshName = "SS_cloth_SIM_MESH";
	out.bufferName = "Sim Scratch";
	out.type = 6;
	out.subType = 0;
	out.storeNormals = true;
	out.storeTangentsAndBiTangents = false;

	out.bufferLayout.elementsLayout[0].vectorConversion = hclRuntimeConversionInfo::VC_FLOAT4;
	out.bufferLayout.elementsLayout[0].vectorSize = 16;
	out.bufferLayout.elementsLayout[0].slotId = 0;
	out.bufferLayout.elementsLayout[0].slotStart = 0;

	out.bufferLayout.elementsLayout[1].vectorConversion = hclRuntimeConversionInfo::VC_FLOAT4;
	out.bufferLayout.elementsLayout[1].vectorSize = 16;
	out.bufferLayout.elementsLayout[1].slotId = 1;
	out.bufferLayout.elementsLayout[1].slotStart = 0;

	out.bufferLayout.elementsLayout[2].vectorConversion = hclRuntimeConversionInfo::VC_NONE;
	out.bufferLayout.elementsLayout[2].vectorSize = 0;
	out.bufferLayout.elementsLayout[2].slotId = 0;
	out.bufferLayout.elementsLayout[2].slotStart = 0;

	out.bufferLayout.elementsLayout[3].vectorConversion = hclRuntimeConversionInfo::VC_NONE;
	out.bufferLayout.elementsLayout[3].vectorSize = 0;
	out.bufferLayout.elementsLayout[3].slotId = 0;
	out.bufferLayout.elementsLayout[3].slotStart = 0;

	out.bufferLayout.slots[0].flags = hclBufferLayout::SlotFlags::SF_16BYTE_ALIGNED_START;
	out.bufferLayout.slots[0].stride = 16;

	out.bufferLayout.slots[1].flags = hclBufferLayout::SlotFlags::SF_16BYTE_ALIGNED_START;
	out.bufferLayout.slots[1].stride = 16;

	out.bufferLayout.slots[2].flags = hclBufferLayout::SlotFlags::F_NO_ALIGNED_START;
	out.bufferLayout.slots[2].stride = 0;

	out.bufferLayout.slots[3].flags = hclBufferLayout::SlotFlags::F_NO_ALIGNED_START;
	out.bufferLayout.slots[3].stride = 0;

	out.bufferLayout.numSlots = 2;
	out.bufferLayout.triangleFormat = hclBufferLayout::TriangleFormat::TF_OTHER;

	return out;
}

hktypes::hclBufferDefinition hktypes::DefaultBufferDefinitionWithTriangles()
{
	hclBufferDefinition out;
	out.meshName = "SS_cloth_SIM_MESH";
	out.bufferName = "SimBuf";
	out.type = 1;
	out.subType = 0;

	out.bufferLayout.elementsLayout[0].vectorConversion = hclRuntimeConversionInfo::VC_FLOAT4;
	out.bufferLayout.elementsLayout[0].vectorSize = 16;
	out.bufferLayout.elementsLayout[0].slotId = 0;
	out.bufferLayout.elementsLayout[0].slotStart = 0;

	out.bufferLayout.elementsLayout[1].vectorConversion = hclRuntimeConversionInfo::VC_FLOAT4;
	out.bufferLayout.elementsLayout[1].vectorSize = 16;
	out.bufferLayout.elementsLayout[1].slotId = 1;
	out.bufferLayout.elementsLayout[1].slotStart = 0;

	out.bufferLayout.elementsLayout[2].vectorConversion = hclRuntimeConversionInfo::VC_NONE;
	out.bufferLayout.elementsLayout[2].vectorSize = 0;
	out.bufferLayout.elementsLayout[2].slotId = 0;
	out.bufferLayout.elementsLayout[2].slotStart = 0;

	out.bufferLayout.elementsLayout[3].vectorConversion = hclRuntimeConversionInfo::VC_NONE;
	out.bufferLayout.elementsLayout[3].vectorSize = 0;
	out.bufferLayout.elementsLayout[3].slotId = 0;
	out.bufferLayout.elementsLayout[3].slotStart = 0;

	out.bufferLayout.slots[0].flags = hclBufferLayout::SlotFlags::SF_16BYTE_ALIGNED_START;
	out.bufferLayout.slots[0].stride = 16;

	out.bufferLayout.slots[1].flags = hclBufferLayout::SlotFlags::SF_16BYTE_ALIGNED_START;
	out.bufferLayout.slots[1].stride = 16;

	out.bufferLayout.slots[2].flags = hclBufferLayout::SlotFlags::F_NO_ALIGNED_START;
	out.bufferLayout.slots[2].stride = 0;

	out.bufferLayout.slots[3].flags = hclBufferLayout::SlotFlags::F_NO_ALIGNED_START;
	out.bufferLayout.slots[3].stride = 0;

	out.bufferLayout.numSlots = 2;
	out.bufferLayout.triangleFormat = hclBufferLayout::TriangleFormat::TF_THREE_INT16S;

	return out;
}

hktypes::hclStateDependencyGraph hktypes::DefaultStateDependencyGraph(int num_operators)
{
	hktypes::hclStateDependencyGraph out;
	hclStateDependencyGraph::Branch branch;
	branch.branchId = 0;
	for (int i = 0; i < num_operators; i++) {
		branch.stateOperatorIndices.push_back(i);
	}
	out.branches.push_back(branch);
	out.rootBranchIds.push_back(0);
	out.parents.push_back({});
	for (int i = 1; i < num_operators; i++) {
		out.children.push_back({ i });
		out.parents.push_back({ i - 1 });
	}
	out.children.push_back({});
	out.multiThreadable = false;
	return out;
}

hktypes::hclShape* hktypes::AllocateShapeFromMesh(hclBufferedMeshObj& mesh_obj)
{
	if (mesh_obj.shapeType != hclBufferedMeshObj::ShapeType::Capsule) {
		return nullptr;
	}
	else {
		if (abs(mesh_obj.capsuleSmallRadius - mesh_obj.capsuleBigRadius) < 1E-4) {
			return impl::AllocateCapsuleShapeFromMesh(mesh_obj);
		}
		else {
			return impl::AllocateTaperedCapsuleShapeFromMesh(mesh_obj);
		}
	}
}

hktypes::hclCollidable* hktypes::AllocateCollidableFromMesh(hclBufferedMeshObj& mesh_obj)
{
	auto shape = AllocateShapeFromMesh(mesh_obj);
	if (shape == nullptr) {
		return nullptr;
	}

	hclCollidable* out = new hclCollidable();
	out->name = mesh_obj.name;
	out->transform = hkMatrix4Holder::FromMatrix4f(mesh_obj.localFrame);
	out->shape = shape;
	return out;
}

hktypes::hclConstraintSet* hktypes::AllocateConstraint(std::string type, std::string name)
{
	if (type == "StandardLink") {
		return impl::AllocateStandardLinkConstraintSetMx(name);
	}
	else if (type == "StretchLink") {
		return impl::AllocateStretchLinkConstraintSetMx(name);
	}
	else if (type == "BonePlanes") {
		return impl::AllocateBonePlanesConstraintSet(name);
	}
	else if (type == "LocalRange") {
		hclLocalRangeConstraintSet* out = new hclLocalRangeConstraintSet();
		out->name = name;
		return out;
	}
	return nullptr;
}

hktypes::hclTransformSetUsage hktypes::CollectTransformSetUsage(hclSimClothData* sim_cloth_data, int num_bones)
{
	hclTransformSetUsage out;
	out.SetNumBitsForAll(num_bones);
	std::vector<uint32_t> static_bone_ids = sim_cloth_data->collidableTransformMap.transformIndices;
	if (sim_cloth_data->transferMotionEnabled) {
		static_bone_ids.push_back(sim_cloth_data->transferMotionData.transformIndex);
	}
	out.AddUsage(0, hclTransformSetUsage::UF_Read | hclTransformSetUsage::UF_ReadBeforeWrite, static_bone_ids);
	
	std::vector<uint32_t> constraint_bone_ids;
	for (auto& constraint : sim_cloth_data->staticConstraintSets) {
		constraint->CollectBoneUsage(constraint_bone_ids);
	}
	out.AddUsage(1, hclTransformSetUsage::UF_Read | hclTransformSetUsage::UF_ReadBeforeWrite, constraint_bone_ids);

	return out;
}

hktypes::hclSimpleMeshBoneDeformOperator* hktypes::AllocateSimpleMeshBoneDeformOperator(uint32_t num_bones, std::vector<std::pair<uint16_t, uint16_t>> bone_triangle_id_pair, std::vector<Eigen::Matrix4f> local_bone_transforms)
{
	hclSimpleMeshBoneDeformOperator* out = new hclSimpleMeshBoneDeformOperator();
	out->name = "Deform";
	uint8_t input_buffer_index = 1;
	uint32_t output_transform_set_index = 0;
	out->inputBufferIdx = input_buffer_index;
	out->outputTransformSetIdx = output_transform_set_index;
	out->usedBuffers.push_back(BufferAccessFromParameters(input_buffer_index, 1, 0, 0, 0, true));

	std::vector<uint32_t> used_bone_ids;
	for (auto& pair: bone_triangle_id_pair) {
		hclSimpleMeshBoneDeformOperator::TriangleBonePair bone_triangle_pair;
		bone_triangle_pair.boneOffset = pair.first * 64;
		bone_triangle_pair.triangleOffset = pair.second * 6;
		out->triangleBonePairs.push_back(bone_triangle_pair);
		used_bone_ids.push_back(pair.first);
	}

	for (auto& transform : local_bone_transforms) {
		out->localBoneTransforms.push_back(hkMatrix4Holder::FromMatrix4f(transform));
	}

	hclTransformSetUsage transform_set_usage;
	transform_set_usage.SetNumBitsForAll(num_bones);
	transform_set_usage.AddUsage(0, hclTransformSetUsage::UF_Write, used_bone_ids);

	out->usedTransformSets.push_back(FromTransformSetUsage(output_transform_set_index, transform_set_usage));

	return out;
}

hktypes::hclSimulateOperator* hktypes::AllocateSimulateOperator(hclSimClothData* sim_cloth_data, hclTransformSetDefinition* transform_set_definition, uint8_t subSteps, uint8_t numberOfSolveIterations)
{
	hclSimulateOperator* out = new hclSimulateOperator();
	out->name = "Sim";
	out->simClothIndex = 0;
	hclBufferUsage buffer_usage;
	buffer_usage.perComponentFlags[0] = 15;
	buffer_usage.perComponentFlags[1] = 6;
	buffer_usage.trianglesRead = false;
	out->usedBuffers.push_back(FromBufferUsage(1, buffer_usage));

	hclTransformSetUsage transform_set_usage = CollectTransformSetUsage(sim_cloth_data, transform_set_definition->numTransforms);
	out->usedTransformSets.push_back(FromTransformSetUsage(0, transform_set_usage));

	std::vector<std::pair<uint32_t, int>> constraint_id_priority_pairs;
	for (auto constraint: sim_cloth_data->staticConstraintSets) {
		constraint_id_priority_pairs.push_back({ constraint->constraintId.value, constraint->ConstraintPriority()});
	}

	std::sort(constraint_id_priority_pairs.begin(), constraint_id_priority_pairs.end(), [](std::pair<uint32_t, int> a, std::pair<uint32_t, int> b) {
		return a.second > b.second;
	});

	std::vector<int32_t> execution_order;
	for (auto& pair : constraint_id_priority_pairs) {
		execution_order.push_back(pair.first);
	}
	execution_order.push_back(-1);

	out->simulateOpConfigs.resize(1);
	out->simulateOpConfigs[0].constraintExecution = execution_order;
	out->simulateOpConfigs[0].subSteps = subSteps;
	out->simulateOpConfigs[0].numberOfSolveIterations = numberOfSolveIterations;

	return out;
}

hktypes::hclCopyVerticesOperator* hktypes::AllocateCopyVerticesOperator(uint32_t num_vertices)
{
	hclCopyVerticesOperator* out = new hclCopyVerticesOperator();
	out->name = "VertGather Op";

	hclBufferUsage buffer_usage1;
	buffer_usage1.perComponentFlags[0] = 1;
	buffer_usage1.perComponentFlags[1] = 1;
	auto buffer_access1 = FromBufferUsage(0, buffer_usage1);

	hclBufferUsage buffer_usage2;
	buffer_usage2.perComponentFlags[0] = 6;
	buffer_usage2.perComponentFlags[1] = 6;
	auto buffer_access2 = FromBufferUsage(1, buffer_usage2);

	out->usedBuffers.push_back(buffer_access1);
	out->usedBuffers.push_back(buffer_access2);

	out->inputBufferIdx = 0;
	out->outputBufferIdx = 1;
	out->numberOfVertices = num_vertices;
	out->startVertexIn = 0;
	out->startVertexOut = 0;
	out->copyNormals = true;

	return out;
}

hktypes::hclMoveParticlesOperator* hktypes::AllocateMoveParticlesOperator(std::vector<uint16_t> fixed_particles)
{
	hclMoveParticlesOperator* out = new hclMoveParticlesOperator();
	out->name = "Move Particles";

	hclBufferUsage buffer_usage1;
	buffer_usage1.perComponentFlags[0] = 1;
	auto buffer_access1 = FromBufferUsage(0, buffer_usage1);

	hclBufferUsage buffer_usage2;
	buffer_usage2.perComponentFlags[0] = 2;
	auto buffer_access2 = FromBufferUsage(1, buffer_usage2);

	out->usedBuffers.push_back(buffer_access1);
	out->usedBuffers.push_back(buffer_access2);

	for (auto& id : fixed_particles) {
		hclMoveParticlesOperator::VertexParticlePair pair;
		pair.vertexIndex = id;
		pair.particleIndex = id;
		out->vertexParticlePairs.push_back(pair);
	}

	out->simClothIndex = 0;
	out->refBufferIdx = 0;

	return out;
}

hktypes::hclObjectSpaceSkinPNOperator* hktypes::AllocateObjectSpaceSkinPNOperator(hkaSkeleton* skeleton, const std::vector<uint16_t>& used_bone_ids, const std::vector<std::vector<float>>& positions, const std::vector<std::vector<float>>& normals, const std::vector<std::vector<std::pair<uint16_t, uint8_t>>>& weights)
{
	hclObjectSpaceSkinPNOperator* out = new hclObjectSpaceSkinPNOperator();

	out->name = "Skin Simulation";

	for (auto& bone_id : used_bone_ids) {
		auto& bone = skeleton->bones[bone_id];
		auto global_transform = bone->GetWorldTransform().getMatrix();

		auto R = global_transform.block<3, 3>(0, 0);
		auto T = global_transform.block<3, 1>(0, 3);

		auto inv_T = -R.transpose() * T;

		// boneFromSkinMeshTransform = [R, 0; inv_T, 1]

		Eigen::Matrix4f bone_from_skin_mesh_transform = Eigen::Matrix4f::Identity();
		bone_from_skin_mesh_transform.block<3, 3>(0, 0) = R;
		bone_from_skin_mesh_transform.block<1, 3>(3, 0) = inv_T.transpose();

		out->transformSubset.push_back(bone_id);
		out->boneFromSkinMeshTransforms.push_back(bone_from_skin_mesh_transform);
	}

	hclTransformSetUsage transform_set_usage;
	transform_set_usage.SetNumBitsForAll(skeleton->bones.size());
	transform_set_usage.AddUsage(0, hclTransformSetUsage::UF_Read | hclTransformSetUsage::UF_ReadBeforeWrite, used_bone_ids);

	out->usedTransformSets.push_back(FromTransformSetUsage(0, transform_set_usage));

	out->usedBuffers.push_back(BufferAccessFromParameters(0, 6, 6, 0, 0, false));

	out->outputBufferIndex = 0;
	out->transformSetIndex = 0;

	out->objectSpaceDeformer = DeformerFromWeights(weights);
	out->localPNs = localPNsFromDeformer(out->objectSpaceDeformer, positions, normals);

	return out;
}

hktypes::hclObjectSpaceDeformer hktypes::DeformerFromWeights(const std::vector<std::vector<std::pair<uint16_t, uint8_t>>>& weights)
{
	hclObjectSpaceDeformer deformer;

	deformer.startVertexIndex = 0;
	deformer.endVertexIndex = weights.size() - 1;
	deformer.controlBytes.clear();

	std::vector<std::vector<uint16_t>> entry_vert_ids;
	entry_vert_ids.resize(8);
	for (uint16_t i = 0; i < weights.size(); ++i) {
		auto& weight_list = weights[i];
		uint8_t num_entries = weight_list.size();
		entry_vert_ids[num_entries - 1].push_back(i);
	}

	for (uint8_t i = 0; i < entry_vert_ids.size(); ++i) {
		auto& entry = entry_vert_ids[7 - i];
		if (entry.empty()) {
			continue;
		}
		int j = 0;
		while (entry.size() < 16 && i + j + 1 < 8) {
			auto& next_entry = entry_vert_ids[7 - (i + j + 1)];
			int additional = 16 - entry.size();
			utils::stack_elems(next_entry, entry, additional);
			j++;
		}
	}

	auto& eight_entry = entry_vert_ids[7];
	if (!eight_entry.empty()) {
		auto entries = utils::split_vector(eight_entry, 16);
		deformer.eightBlendEntries.resize(entries.size());
		int i = 0;
		for (auto& entry : entries) {
			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> entry_weights;
			entry_weights.resize(entry.size());
			int j = 0;
			for (auto& id : entry) {
				entry_weights[j] = weights[id];
				j++;
			}
			deformer.eightBlendEntries[i].SetWeights(entry_weights, entry);
			i++;
		}
	}

	auto& seven_entry = entry_vert_ids[6];
	if (!seven_entry.empty()) {
		auto entries = utils::split_vector(seven_entry, 16);
		deformer.sevenBlendEntries.resize(entries.size());
		int i = 0;
		for (auto& entry : entries) {
			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> entry_weights;
			entry_weights.resize(entry.size());
			int j = 0;
			for (auto& id : entry) {
				entry_weights[j] = weights[id];
				j++;
			}
			deformer.sevenBlendEntries[i].SetWeights(entry_weights, entry);
			i++;
		}
	}

	auto& six_entry = entry_vert_ids[5];
	if (!six_entry.empty()) {
		auto entries = utils::split_vector(six_entry, 16);
		deformer.sixBlendEntries.resize(entries.size());
		int i = 0;
		for (auto& entry : entries) {
			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> entry_weights;
			entry_weights.resize(entry.size());
			int j = 0;
			for (auto& id : entry) {
				entry_weights[j] = weights[id];
				j++;
			}
			deformer.sixBlendEntries[i].SetWeights(entry_weights, entry);
			i++;
		}
	}

	auto& five_entry = entry_vert_ids[4];
	if (!five_entry.empty()) {
		auto entries = utils::split_vector(five_entry, 16);
		deformer.fiveBlendEntries.resize(entries.size());
		int i = 0;
		for (auto& entry : entries) {
			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> entry_weights;
			entry_weights.resize(entry.size());
			int j = 0;
			for (auto& id : entry) {
				entry_weights[j] = weights[id];
				j++;
			}
			deformer.fiveBlendEntries[i].SetWeights(entry_weights, entry);
			i++;
		}
	}

	auto& four_entry = entry_vert_ids[3];
	if (!four_entry.empty()) {
		auto entries = utils::split_vector(four_entry, 16);
		deformer.fourBlendEntries.resize(entries.size());
		int i = 0;
		for (auto& entry : entries) {
			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> entry_weights;
			entry_weights.resize(entry.size());
			int j = 0;
			for (auto& id : entry) {
				entry_weights[j] = weights[id];
				j++;
			}
			deformer.fourBlendEntries[i].SetWeights(entry_weights, entry);
			i++;
		}
	}

	auto& three_entry = entry_vert_ids[2];
	if (!three_entry.empty()) {
		auto entries = utils::split_vector(three_entry, 16);
		deformer.threeBlendEntries.resize(entries.size());
		int i = 0;
		for (auto& entry : entries) {
			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> entry_weights;
			entry_weights.resize(entry.size());
			int j = 0;
			for (auto& id : entry) {
				entry_weights[j] = weights[id];
				j++;
			}
			deformer.threeBlendEntries[i].SetWeights(entry_weights, entry);
			i++;
		}
	}

	auto& two_entry = entry_vert_ids[1];
	if (!two_entry.empty()) {
		auto entries = utils::split_vector(two_entry, 16);
		deformer.twoBlendEntries.resize(entries.size());
		int i = 0;
		for (auto& entry : entries) {
			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> entry_weights;
			entry_weights.resize(entry.size());
			int j = 0;
			for (auto& id : entry) {
				entry_weights[j] = weights[id];
				j++;
			}
			deformer.twoBlendEntries[i].SetWeights(entry_weights, entry);
			i++;
		}
	}

	auto& one_entry = entry_vert_ids[0];
	if (!one_entry.empty()) {
		auto entries = utils::split_vector(one_entry, 16);
		deformer.oneBlendEntries.resize(entries.size());
		int i = 0;
		for (auto& entry : entries) {
			std::vector<std::vector<std::pair<uint16_t, uint8_t>>> entry_weights;
			entry_weights.resize(entry.size());
			int j = 0;
			for (auto& id : entry) {
				entry_weights[j] = weights[id];
				j++;
			}
			deformer.oneBlendEntries[i].SetWeights(entry_weights, entry);
			i++;
		}
	}

	// TODO: there could be another indexing scheme for control bytes
	// four: 4 (index 0)
	// three: 2 (index 1)
	// two: 0 (index 2)
	// one: 1 (index 3)
	// control_bytes: 0,0,0,0,1,1,3
	for (uint8_t i = 7, j = -4; i < 8 && i >= 0; --i) {
		int num_entries = entry_vert_ids[i].size() % 16 > 0 ? entry_vert_ids[i].size() / 16 + 1 : entry_vert_ids[i].size() / 16;
		for (int k = 0; k < num_entries; ++k) {
			deformer.controlBytes.push_back(j);
		}
		j++;
	}

	return deformer;
}

std::vector<hktypes::hclObjectSpaceDeformer::LocalBlockPN> hktypes::localPNsFromDeformer(const hclObjectSpaceDeformer& deformer, const std::vector<std::vector<float>>& positions, const std::vector<std::vector<float>>& normals)
{
	std::vector<hktypes::hclObjectSpaceDeformer::LocalBlockPN> PNs;

	using _block_t = hclObjectSpaceDeformer::EntryBlockBase;
	std::vector<std::vector<_block_t*>> blocks;
	blocks.push_back(utils::make_references<_block_t*>(deformer.eightBlendEntries));
	blocks.push_back(utils::make_references<_block_t*>(deformer.sevenBlendEntries));
	blocks.push_back(utils::make_references<_block_t*>(deformer.sixBlendEntries));
	blocks.push_back(utils::make_references<_block_t*>(deformer.fiveBlendEntries));
	blocks.push_back(utils::make_references<_block_t*>(deformer.fourBlendEntries));
	blocks.push_back(utils::make_references<_block_t*>(deformer.threeBlendEntries));
	blocks.push_back(utils::make_references<_block_t*>(deformer.twoBlendEntries));
	blocks.push_back(utils::make_references<_block_t*>(deformer.oneBlendEntries));

	//blocks.erase(std::remove_if(blocks.begin(), blocks.end(), [](auto& block) {return block.empty(); }), blocks.end());

	std::vector<uint8_t> control_bytes = deformer.controlBytes;

	std::vector<std::queue<std::array<uint16_t, 16>>> vert_ids;

	for (auto& block_list : blocks) {
		std::queue<std::array<uint16_t, 16>> _vert_id_list;
		for (auto& block : block_list) {
			auto& vert_id_list = block->vertexIndices;
			_vert_id_list.push(utils::make_array(vert_id_list));
		}
		vert_ids.push_back(_vert_id_list);
	}

	PNs.resize(control_bytes.size());
	for (int i = 0; i < PNs.size(); ++i) {
		auto& localPositions = PNs[i].localPosition;
		auto& localNormals = PNs[i].localNormal;

		auto& vert_id_block = vert_ids[control_bytes[i] + 4];
		auto& vert_id_list = vert_id_block.front();
		vert_id_block.pop();

		for (int j = 0; j < 16; ++j) {
			auto& p = localPositions[j];
			auto& n = localNormals[j];
			auto n_vec = Eigen::Vector3f(normals[vert_id_list[j]][0], normals[vert_id_list[j]][1], normals[vert_id_list[j]][2]);
			// Normalize it
			n_vec = n_vec / n_vec.norm();
			p = p.FromVector3f(Eigen::Vector3f(positions[vert_id_list[j]][0], positions[vert_id_list[j]][1], positions[vert_id_list[j]][2]));
			n = n.FromVector3f(n_vec);
		}
	}

	return PNs;
}

void hktypes::SetClothStateOperators(hclClothState* state, std::vector<hclOperator*> operators)
{
	using BA = hclClothState::BufferAccess;
	using TSA = hclClothState::TransformSetAccess;
	std::vector<BA> buffer_accesses;
	std::vector<TSA> transform_set_accesses;
	state->operators.clear();
	for (auto& op : operators) {
		state->operators.push_back(op->operatorID);
		for(auto& buffer_access : op->usedBuffers) {
			buffer_accesses.push_back(buffer_access);
		}
		for (auto& transform_set_access : op->usedTransformSets) {
			transform_set_accesses.push_back(transform_set_access);
		}
	}

	state->usedBuffers = utils::group_and_calc<BA, BA>(buffer_accesses, AccessSameBuffer, CombineBufferAccess);
	assert(state->usedBuffers.size() == 2);
	state->usedTransformSets = utils::group_and_calc<TSA, TSA>(transform_set_accesses, AccessSameTransformSet, CombineTransformSetAccess);
	assert(state->usedTransformSets.size() == 1);

	if (state->dependencyGraph) {
		delete state->dependencyGraph;
		state->dependencyGraph = nullptr;
	}
	state->dependencyGraph = new hclStateDependencyGraph();
	*state->dependencyGraph = DefaultStateDependencyGraph(operators.size());

	state->usedSimCloths.clear();
	state->usedSimCloths.push_back(0);

	return;
}

hktypes::hclCapsuleShape* hktypes::impl::AllocateCapsuleShapeFromMesh(hclBufferedMeshObj& mesh_obj)
{
	using namespace hktypes;
	hclCapsuleShape* out = new hclCapsuleShape();
	out->FromParameters(mesh_obj.capsuleStart, mesh_obj.capsuleEnd, mesh_obj.capsuleBigRadius);
	return out;
}

hktypes::hclTaperedCapsuleShape* hktypes::impl::AllocateTaperedCapsuleShapeFromMesh(hclBufferedMeshObj& mesh_obj)
{
	using namespace hktypes;
	hclTaperedCapsuleShape* out = new hclTaperedCapsuleShape();
	out->FromParameters(mesh_obj.capsuleStart, mesh_obj.capsuleEnd, mesh_obj.capsuleBigRadius, mesh_obj.capsuleSmallRadius);
	return out;
}

hktypes::hclStandardLinkConstraintSetMx* hktypes::impl::AllocateStandardLinkConstraintSetMx(std::string name)
{
	hclStandardLinkConstraintSetMx* out = new hclStandardLinkConstraintSetMx();
	out->name = name;
	return out;
}

hktypes::hclStretchLinkConstraintSetMx* hktypes::impl::AllocateStretchLinkConstraintSetMx(std::string name)
{
	hclStretchLinkConstraintSetMx* out = new hclStretchLinkConstraintSetMx();
	out->name = name;
	return out;
}

hktypes::hclBonePlanesConstraintSet* hktypes::impl::AllocateBonePlanesConstraintSet(std::string name)
{
	hclBonePlanesConstraintSet* out = new hclBonePlanesConstraintSet();
	out->name = name;
	return out;
}
