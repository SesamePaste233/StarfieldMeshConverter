#pragma once
#include "hkTypes.h"
#include "hkaSkeleton.h"
#include "hclClothData.h"
#include "hclClothState.h"
#include "hclOperator.h"
#include "hclSimClothData.h"

namespace hktypes {
	hclBufferUsage& operator|(const hclBufferUsage& buffer_usage1, const hclBufferUsage& buffer_usage2);

	hclTransformSetUsage::TransformTracker& operator|(const hclTransformSetUsage::TransformTracker& transform_tracker1, const hclTransformSetUsage::TransformTracker& transform_tracker2);

	hclTransformSetUsage& operator|(const hclTransformSetUsage& transform_usage1, const hclTransformSetUsage& transform_usage2);

	hclClothState::BufferAccess& operator|(const hclClothState::BufferAccess& buffer_access1, const hclClothState::BufferAccess& buffer_access2);

	hclClothState::BufferAccess CombineBufferAccess(const std::vector<hclClothState::BufferAccess>& buffer_accesses);

	bool AccessSameBuffer(const hclClothState::BufferAccess& buffer_access1, const hclClothState::BufferAccess& buffer_access2);

	hclClothState::TransformSetAccess& operator|(const hclClothState::TransformSetAccess& transform_set_access1, const hclClothState::TransformSetAccess& transform_set_access2);

	hclClothState::TransformSetAccess CombineTransformSetAccess(const std::vector<hclClothState::TransformSetAccess>& transform_set_accesses);

	bool AccessSameTransformSet(const hclClothState::TransformSetAccess& transform_set_access1, const hclClothState::TransformSetAccess& transform_set_access2);

	hclClothState::BufferAccess& FromBufferUsage(uint32_t buffer_index, hclBufferUsage buffer_usage, uint32_t shadow_buffer_index = uint32_t(-1));

	hclClothState::BufferAccess& BufferAccessFromParameters(uint32_t buffer_index, uint8_t position_usage, uint8_t normal_usage, uint8_t tangent_usage, uint8_t bitangent_usage, bool triangles_read = false, uint32_t shadow_buffer_index = uint32_t(-1));

	hclClothState::TransformSetAccess& FromTransformSetUsage(uint32_t transform_set_index, hclTransformSetUsage transform_set_usage);

	hclScratchBufferDefinition& DefaultScratchBufferDefinition();

	hclBufferDefinition& DefaultBufferDefinitionWithTriangles();

	hclStateDependencyGraph& DefaultStateDependencyGraph(int num_operators);

	hclShape* AllocateShapeFromMesh(hclBufferedMeshObj& mesh_obj);

	hclCollidable* AllocateCollidableFromMesh(hclBufferedMeshObj& mesh_obj);

	hclConstraintSet* AllocateConstraint(std::string type, std::string name);

	hclTransformSetUsage CollectTransformSetUsage(hclSimClothData* sim_cloth_data, int num_bones);

	hclSimpleMeshBoneDeformOperator* AllocateSimpleMeshBoneDeformOperator(std::vector<std::pair<uint16_t, uint16_t>> bone_triangle_id_pair, std::vector<Eigen::Matrix4f> local_bone_transforms);

	hclSimulateOperator* AllocateSimulateOperator(hclSimClothData* sim_cloth_data, hclTransformSetDefinition* transform_set_definition, uint8_t subSteps = 1, uint8_t numberOfSolveIterations = 1);

	hclCopyVerticesOperator* AllocateCopyVerticesOperator(uint32_t num_vertices);

	hclMoveParticlesOperator* AllocateMoveParticlesOperator(std::vector<uint16_t> fixed_particles);

	hclObjectSpaceSkinPNOperator* AllocateObjectSpaceSkinPNOperator(
		hkaSkeleton* skeleton, 
		const std::vector<uint16_t>& used_bone_ids,
		const std::vector<std::vector<float>>& positions,
		const std::vector<std::vector<float>>& normals,
		const std::vector<std::vector<std::pair<uint16_t, uint8_t>>>& weights
	);

	hclObjectSpaceDeformer& DeformerFromWeights(
		const std::vector<std::vector<std::pair<uint16_t, uint8_t>>>& weights
	);

	std::vector<hclObjectSpaceDeformer::LocalBlockPN> localPNsFromDeformer(
		const hclObjectSpaceDeformer& deformer,
		const std::vector<std::vector<float>>& positions,
		const std::vector<std::vector<float>>& normals
	);

	void SetClothStateOperators(hclClothState* state, std::vector<hclOperator*> operators);

	namespace impl {
		hclCapsuleShape* AllocateCapsuleShapeFromMesh(hclBufferedMeshObj& mesh_obj);

		hclTaperedCapsuleShape* AllocateTaperedCapsuleShapeFromMesh(hclBufferedMeshObj& mesh_obj);

		hclStandardLinkConstraintSetMx* AllocateStandardLinkConstraintSetMx(std::string name);
	}
}