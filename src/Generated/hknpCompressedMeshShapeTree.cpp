#include "Generated\hknpCompressedMeshShapeTree.h"

#include "Generated\.h"

bool hktypes::hknpCompressedMeshShapeTree::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCompressedMeshShapeTree") {
		std::cout << "hknpCompressedMeshShapeTree::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkcdDefaultStaticMeshTree::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

bool hktypes::hknpCompressedMeshShapeTree::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCompressedMeshShapeTree") {
		std::cout << "hknpCompressedMeshShapeTree::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkcdDefaultStaticMeshTree::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpCompressedMeshShapeTree::GetTemplateArgs() { return {
}; };

