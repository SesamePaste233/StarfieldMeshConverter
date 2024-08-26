#include "Generated\hknpConvexHull.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hknpConvexHull::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexHull::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexHull") {
		std::cout << "hknpConvexHull::FromInstance: Expecting hknpConvexHull but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertices")->GetValue(vertices);
	class_instance->GetInstanceByFieldName("planes")->GetValue(planes);
	class_instance->GetInstanceByFieldName("faces")->GetValue(faces);
	class_instance->GetInstanceByFieldName("indices")->GetValue(indices);
	class_instance->GetInstanceByFieldName("faceLinks")->GetValue(faceLinks);
	class_instance->GetInstanceByFieldName("vertexEdges")->GetValue(vertexEdges);
	return true;
}

bool hktypes::hknpConvexHull::Face::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexHull::Face::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexHull::Face") {
		std::cout << "hknpConvexHull::Face::FromInstance: Expecting hknpConvexHull::Face but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("firstIndex")->GetValue(firstIndex);
	class_instance->GetInstanceByFieldName("numIndices")->GetValue(numIndices);
	class_instance->GetInstanceByFieldName("minHalfAngle")->GetValue(minHalfAngle);
	return true;
}

bool hktypes::hknpConvexHull::Edge::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexHull::Edge::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexHull::Edge") {
		std::cout << "hknpConvexHull::Edge::FromInstance: Expecting hknpConvexHull::Edge but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("faceIndex")->GetValue(faceIndex);
	class_instance->GetInstanceByFieldName("edgeIndex")->GetValue(edgeIndex);
	class_instance->GetInstanceByFieldName("padding")->GetValue(padding);
	return true;
}

bool hktypes::hknpConvexHull::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexHull::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexHull") {
		std::cout << "hknpConvexHull::ToInstance: Expecting hknpConvexHull but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("vertices")->SetValue(vertices);
	class_instance->GetInstanceByFieldName("planes")->SetValue(planes);
	class_instance->GetInstanceByFieldName("faces")->SetValue(faces);
	class_instance->GetInstanceByFieldName("indices")->SetValue(indices);
	class_instance->GetInstanceByFieldName("faceLinks")->SetValue(faceLinks);
	class_instance->GetInstanceByFieldName("vertexEdges")->SetValue(vertexEdges);
	return true;
}

bool hktypes::hknpConvexHull::Face::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexHull::Face::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexHull::Face") {
		std::cout << "hknpConvexHull::Face::ToInstance: Expecting hknpConvexHull::Face but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("firstIndex")->SetValue(firstIndex);
	class_instance->GetInstanceByFieldName("numIndices")->SetValue(numIndices);
	class_instance->GetInstanceByFieldName("minHalfAngle")->SetValue(minHalfAngle);
	return true;
}

bool hktypes::hknpConvexHull::Edge::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexHull::Edge::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexHull::Edge") {
		std::cout << "hknpConvexHull::Edge::ToInstance: Expecting hknpConvexHull::Edge but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("faceIndex")->SetValue(faceIndex);
	class_instance->GetInstanceByFieldName("edgeIndex")->SetValue(edgeIndex);
	class_instance->GetInstanceByFieldName("padding")->SetValue(padding);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpConvexHull::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpConvexHull::Face::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hknpConvexHull::Edge::GetTemplateArgs() { return {
}; };

