#include "hkInclude.h"
#include "hkTypes.h"
#include "hkaSkeleton.h"
#include "hclClothData.h"
#include "hclClothState.h"
#include "hclOperator.h"
#include "hclSimClothData.h"

hktypes::hkHolderBase* hktypes::AllocateHolder(const hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name == "hclSimClothData") {
		return new hclSimClothData();
	}
	else if (class_instance->type->type_name == "hclClothData") {
		return new hclClothData();
	}
	else if (class_instance->type->type_name == "hkaSkeleton") {
		return new hkaSkeleton();
	}
	else if (class_instance->type->type_name == "hclClothState") {
		return new hclClothState();
	}
	else if (class_instance->type->type_name == "hclTransformSetDefinition") {
		return new hclTransformSetDefinition();
	}
	else if (class_instance->type->type_name == "hclSimClothPose") {
		return new hclSimClothPose();
	}
	else if (class_instance->type->type_name == "hclConstraintSet") {
		return new hclConstraintSet();
	}
	else if (class_instance->type->type_name == "hclCollidable") {
		return new hclCollidable();
	}
	else if (class_instance->type->type_name == "hclLocalRangeConstraintSet") {
		return new hclLocalRangeConstraintSet();
	}
	else if (class_instance->type->type_name == "hclStandardLinkConstraintSetMx") {
		return new hclStandardLinkConstraintSetMx();
	}
	else if (class_instance->type->type_name == "hclStretchLinkConstraintSetMx") {
		return new hclStretchLinkConstraintSetMx();
	}
	else if (class_instance->type->type_name == "hclOperator") {
		return new hclOperator();
	}
	else if (class_instance->type->type_name == "hclObjectSpaceSkinOperator") {
		return new hclObjectSpaceSkinOperator();
	}
	else if (class_instance->type->type_name == "hclObjectSpaceSkinPNOperator") {
		return new hclObjectSpaceSkinPNOperator();
	}
	else if (class_instance->type->type_name == "hclBufferDefinition") {
		return new hclBufferDefinition();
	}
	else if (class_instance->type->type_name == "hclScratchBufferDefinition") {
		return new hclScratchBufferDefinition();
	}
	else if (class_instance->type->type_name == "hclMoveParticlesOperator") {
		return new hclMoveParticlesOperator();
	}
	else if (class_instance->type->type_name == "hclSimulateOperator") {
		return new hclSimulateOperator();
	}
	else if (class_instance->type->type_name == "hclSimpleMeshBoneDeformOperator") {
		return new hclSimpleMeshBoneDeformOperator();
	}
	else if (class_instance->type->type_name == "hclCopyVerticesOperator") {
		return new hclCopyVerticesOperator();
	}
	else if (class_instance->type->type_name == "hclGatherAllVerticesOperator") {
		return new hclGatherAllVerticesOperator();
	}
	else if (class_instance->type->type_name == "hclStateDependencyGraph") {
		return new hclStateDependencyGraph();
	}
	else if (class_instance->type->type_name == "hclBonePlanesConstraintSet") {
		return new hclBonePlanesConstraintSet();
	}
	else if (class_instance->type->type_name == "hclBoneSpaceSkinOperator") {
		return new hclBoneSpaceSkinOperator();
	}
	else if (class_instance->type->type_name == "hclBoneSpaceSkinPNOperator") {
		return new hclBoneSpaceSkinPNOperator();
	}
	else if (class_instance->type->type_name == "hclVolumeConstraint") {
		return new hclVolumeConstraint();
	}
	else if (class_instance->type->type_name == "hclVolumeConstraintMx") {
		return new hclVolumeConstraintMx();
	}
	else if (class_instance->type->type_name == "hclCompressibleLinkConstraintSetMx") {
		return new hclCompressibleLinkConstraintSetMx();
	}
	else if (class_instance->type->type_name == "hclBendStiffnessConstraintSetMx") {
		return new hclBendStiffnessConstraintSetMx();
	}
	else if (class_instance->type->type_name == "hclBendStiffnessConstraintSet") {
		return new hclBendStiffnessConstraintSet();
	}
	else if (class_instance->type->type_name == "hclCapsuleShape") {
		return new hclCapsuleShape();
	}
	else if (class_instance->type->type_name == "hclTaperedCapsuleShape") {
		return new hclTaperedCapsuleShape();
	}

	throw std::runtime_error("AllocateHolder: Unknown type: " + class_instance->type->type_name);
	return nullptr;
};
