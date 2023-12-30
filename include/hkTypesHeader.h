#pragma once
#include "hkTypes.h"
#include "hkaSkeleton.h"
#include "hclClothData.h"
#include "hclClothState.h"
#include "hclOperator.h"
#include "hclSimClothData.h"

namespace hktypes {
	hclBufferUsage& operator|(hclBufferUsage& buffer_usage1, hclBufferUsage& buffer_usage2);

	hclTransformSetUsage::TransformTracker& operator|(hclTransformSetUsage::TransformTracker& transform_tracker1, hclTransformSetUsage::TransformTracker& transform_tracker2);

	hclTransformSetUsage& operator|(hclTransformSetUsage& transform_usage1, hclTransformSetUsage& transform_usage2);

	hclClothState::BufferAccess& FromBufferUsage(uint32_t buffer_index, hclBufferUsage buffer_usage, uint32_t shadow_buffer_index = uint32_t(-1));

	hclScratchBufferDefinition& DefaultScratchBufferDefinition();

	hclBufferDefinition& DefaultBufferDefinitionWithTriangles();

	hclStateDependencyGraph& DefaultStateDependencyGraph(int num_operators);
}