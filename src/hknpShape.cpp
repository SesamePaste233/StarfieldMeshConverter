#include "hknpShape.h"

bool hktypes::hknpShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpShape::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpShape") {
		std::cout << "hknpShape::FromInstance: Expecting hknpShape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("flags")->GetValue(flags);
	class_instance->GetInstanceByFieldName("type")->GetValue(type);
	class_instance->GetInstanceByFieldName("numShapeKeyBits")->GetValue(numShapeKeyBits);
	class_instance->GetInstanceByFieldName("dispatchType")->GetValue(dispatchType);
	class_instance->GetInstanceByFieldName("convexRadius")->GetValue(convexRadius);
	class_instance->GetInstanceByFieldName("userData")->GetValue(userData);
	class_instance->GetInstanceByFieldName("properties")->GetValue(properties);
	return true;
}

bool hktypes::hknpShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpShape::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpShape") {
		std::cout << "hknpShape::ToInstance: Expecting hknpShape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("flags")->SetValue(flags);
	class_instance->GetInstanceByFieldName("type")->SetValue(type);
	class_instance->GetInstanceByFieldName("numShapeKeyBits")->SetValue(numShapeKeyBits);
	class_instance->GetInstanceByFieldName("dispatchType")->SetValue(dispatchType);
	class_instance->GetInstanceByFieldName("convexRadius")->SetValue(convexRadius);
	class_instance->GetInstanceByFieldName("userData")->SetValue(userData);
	class_instance->GetInstanceByFieldName("properties")->SetValue(properties);
	return true;
}

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

bool hktypes::hknpConvexShape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexShape::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexShape") {
		std::cout << "hknpConvexShape::FromInstance: Expecting hknpConvexShape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpShape::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("maxAllowedPenetration")->GetValue(maxAllowedPenetration);
	class_instance->GetInstanceByFieldName("hull")->GetValue(hull);
	return true;
}

bool hktypes::hknpConvexShape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hknpConvexShape::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hknpConvexShape") {
		std::cout << "hknpConvexShape::ToInstance: Expecting hknpConvexShape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hknpShape::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("maxAllowedPenetration")->SetValue(maxAllowedPenetration);
	class_instance->GetInstanceByFieldName("hull")->SetValue(hull);
	return true;
}
