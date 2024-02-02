#include "Generated\hknpCompressedMeshShapeData.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\hkcdStaticMeshTree.h"
#include "Generated\.h"

bool hktypes::hknpCompressedMeshShapeData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCompressedMeshShapeData") {
		std::cout << "hknpCompressedMeshShapeData::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("meshTree")->GetValue(meshTree);
	class_instance->GetInstanceByFieldName("simdTree")->GetValue(simdTree);
	class_instance->GetInstanceByFieldName("connectivity")->GetValue(connectivity);
	class_instance->GetInstanceByFieldName("hasSimdTree")->GetValue(hasSimdTree);
	return true;
}

bool hktypes::hknpCompressedMeshShapeData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCompressedMeshShapeData") {
		std::cout << "hknpCompressedMeshShapeData::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("meshTree")->SetValue(meshTree);
	class_instance->GetInstanceByFieldName("simdTree")->SetValue(simdTree);
	class_instance->GetInstanceByFieldName("connectivity")->SetValue(connectivity);
	class_instance->GetInstanceByFieldName("hasSimdTree")->SetValue(hasSimdTree);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpCompressedMeshShapeData::GetTemplateArgs() { return {
}; };

