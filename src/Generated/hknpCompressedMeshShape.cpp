#include "Generated\hknpCompressedMeshShape.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpCompressedMeshShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCompressedMeshShape") {
		std::cout << "hknpCompressedMeshShape::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpCompositeShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("data")->GetValue(data);
	class_instance->GetInstanceByFieldName("triangleIsInterior")->GetValue(triangleIsInterior);
	class_instance->GetInstanceByFieldName("numTriangles")->GetValue(numTriangles);
	class_instance->GetInstanceByFieldName("numConvexShapes")->GetValue(numConvexShapes);
	class_instance->GetInstanceByFieldName("externShapes")->GetValue(externShapes);
	return true;
}

bool hktypes::hknpCompressedMeshShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hknpCompressedMeshShape") {
		std::cout << "hknpCompressedMeshShape::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpCompositeShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("data")->SetValue(data);
	class_instance->GetInstanceByFieldName("triangleIsInterior")->SetValue(triangleIsInterior);
	class_instance->GetInstanceByFieldName("numTriangles")->SetValue(numTriangles);
	class_instance->GetInstanceByFieldName("numConvexShapes")->SetValue(numConvexShapes);
	class_instance->GetInstanceByFieldName("externShapes")->SetValue(externShapes);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpCompressedMeshShape::GetTemplateArgs() { return {
}; };

