#include "Generated\hkcdDefaultStaticMeshTree.h"

#include "Generated\hkcdStaticMeshTree.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hkcdDefaultStaticMeshTree::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdDefaultStaticMeshTree") {
		std::cout << "hkcdDefaultStaticMeshTree::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkcdStaticMeshTree::Base::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("packedVertices")->GetValue(packedVertices);
	class_instance->GetInstanceByFieldName("sharedVertices")->GetValue(sharedVertices);
	class_instance->GetInstanceByFieldName("primitiveDataRuns")->GetValue(primitiveDataRuns);
	return true;
}

bool hktypes::hkcdDefaultStaticMeshTree::PrimitiveDataRun::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdDefaultStaticMeshTree::PrimitiveDataRun") {
		std::cout << "hkcdDefaultStaticMeshTree::PrimitiveDataRun::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("value")->GetValue(value);
	class_instance->GetInstanceByFieldName("index")->GetValue(index);
	class_instance->GetInstanceByFieldName("count")->GetValue(count);
	return true;
}

bool hktypes::hkcdDefaultStaticMeshTree::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdDefaultStaticMeshTree") {
		std::cout << "hkcdDefaultStaticMeshTree::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkcdStaticMeshTree::Base::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("packedVertices")->SetValue(packedVertices);
	class_instance->GetInstanceByFieldName("sharedVertices")->SetValue(sharedVertices);
	class_instance->GetInstanceByFieldName("primitiveDataRuns")->SetValue(primitiveDataRuns);
	return true;
}

bool hktypes::hkcdDefaultStaticMeshTree::PrimitiveDataRun::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdDefaultStaticMeshTree::PrimitiveDataRun") {
		std::cout << "hkcdDefaultStaticMeshTree::PrimitiveDataRun::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("value")->SetValue(value);
	class_instance->GetInstanceByFieldName("index")->SetValue(index);
	class_instance->GetInstanceByFieldName("count")->SetValue(count);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkcdDefaultStaticMeshTree::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hkcdDefaultStaticMeshTree::PrimitiveDataRun::GetTemplateArgs() { return {
}; };

