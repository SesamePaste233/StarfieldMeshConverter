#include "hkInclude.h"
#include "hkTypes.h"
#include "hkaSkeleton.h"
#include "hclClothData.h"
#include "hclClothState.h"
#include "hclOperator.h"
#include "hclSimClothData.h"

hktypes::hkHolderBase* hktypes::AllocateHolder(hkreflex::hkClassInstance* instance)
{
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
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

	throw std::runtime_error("AllocateHolder: Unknown type!");
	return nullptr;
};
