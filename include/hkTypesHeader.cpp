#include "hkTypesHeader.h"

hktypes::hclBufferUsage& hktypes::operator|(hclBufferUsage& buffer1, hclBufferUsage& buffer2)
{
    hclBufferUsage out;
    for (uint8_t i = 0; i < 4; i++) {
        out.perComponentFlags[i] = buffer1.perComponentFlags[i] | buffer2.perComponentFlags[i];
    }
    out.trianglesRead = buffer1.trianglesRead || buffer2.trianglesRead;
    return out;
}

hktypes::hclTransformSetUsage::TransformTracker& hktypes::operator|(hclTransformSetUsage::TransformTracker& transform_tracker1, hclTransformSetUsage::TransformTracker& transform_tracker2)
{
    hclTransformSetUsage::TransformTracker out;
	out.read = transform_tracker1.read | transform_tracker2.read;
	out.readBeforeWrite = transform_tracker1.readBeforeWrite | transform_tracker2.readBeforeWrite;
	out.written = transform_tracker1.written | transform_tracker2.written;
	return out;
}

hktypes::hclTransformSetUsage& hktypes::operator|(hclTransformSetUsage& transform_usage1, hclTransformSetUsage& transform_usage2)
{
    hclTransformSetUsage out;
    for (uint8_t i = 0; i < 2; i++) {
		out.perComponentFlags[i] = transform_usage1.perComponentFlags[i] | transform_usage2.perComponentFlags[i];
	}
    for (uint32_t i = 0; i < transform_usage1.perComponentTransformTrackers.size(); i++) {
		out.perComponentTransformTrackers.push_back(transform_usage1.perComponentTransformTrackers[i] | transform_usage2.perComponentTransformTrackers[i]);
	}
	return out;
}

hktypes::hclClothState::BufferAccess& hktypes::FromBufferUsage(uint32_t buffer_index, hclBufferUsage buffer_usage, uint32_t shadow_buffer_index)
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

hktypes::hclScratchBufferDefinition& hktypes::DefaultScratchBufferDefinition()
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

hktypes::hclBufferDefinition& hktypes::DefaultBufferDefinitionWithTriangles()
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

hktypes::hclStateDependencyGraph& hktypes::DefaultStateDependencyGraph(int num_operators)
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
