#include "Generated\hclVirtualCollisionPointsData.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclVirtualCollisionPointsData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData") {
		std::cout << "hclVirtualCollisionPointsData::FromInstance: Expecting hclVirtualCollisionPointsData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("blocks")->GetValue(blocks);
	class_instance->GetInstanceByFieldName("numVCPoints")->GetValue(numVCPoints);
	class_instance->GetInstanceByFieldName("landscapeParticlesBlockIndex")->GetValue(landscapeParticlesBlockIndex);
	class_instance->GetInstanceByFieldName("numLandscapeVCPoints")->GetValue(numLandscapeVCPoints);
	class_instance->GetInstanceByFieldName("edgeBarycentricsDictionary")->GetValue(edgeBarycentricsDictionary);
	class_instance->GetInstanceByFieldName("edgeDictionaryEntries")->GetValue(edgeDictionaryEntries);
	class_instance->GetInstanceByFieldName("triangleBarycentricsDictionary")->GetValue(triangleBarycentricsDictionary);
	class_instance->GetInstanceByFieldName("triangleDictionaryEntries")->GetValue(triangleDictionaryEntries);
	class_instance->GetInstanceByFieldName("edges")->GetValue(edges);
	class_instance->GetInstanceByFieldName("edgeFans")->GetValue(edgeFans);
	class_instance->GetInstanceByFieldName("triangles")->GetValue(triangles);
	class_instance->GetInstanceByFieldName("triangleFans")->GetValue(triangleFans);
	class_instance->GetInstanceByFieldName("edgesLandscape")->GetValue(edgesLandscape);
	class_instance->GetInstanceByFieldName("edgeFansLandscape")->GetValue(edgeFansLandscape);
	class_instance->GetInstanceByFieldName("trianglesLandscape")->GetValue(trianglesLandscape);
	class_instance->GetInstanceByFieldName("triangleFansLandscape")->GetValue(triangleFansLandscape);
	class_instance->GetInstanceByFieldName("edgeFanIndices")->GetValue(edgeFanIndices);
	class_instance->GetInstanceByFieldName("triangleFanIndices")->GetValue(triangleFanIndices);
	class_instance->GetInstanceByFieldName("edgeFanIndicesLandscape")->GetValue(edgeFanIndicesLandscape);
	class_instance->GetInstanceByFieldName("triangleFanIndicesLandscape")->GetValue(triangleFanIndicesLandscape);
	return true;
}

bool hktypes::hclVirtualCollisionPointsData::Block::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::Block::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::Block") {
		std::cout << "hclVirtualCollisionPointsData::Block::FromInstance: Expecting hclVirtualCollisionPointsData::Block but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::BarycentricDictionaryEntry::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::BarycentricDictionaryEntry::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::BarycentricDictionaryEntry") {
		std::cout << "hclVirtualCollisionPointsData::BarycentricDictionaryEntry::FromInstance: Expecting hclVirtualCollisionPointsData::BarycentricDictionaryEntry but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::BarycentricPair::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::BarycentricPair::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::BarycentricPair") {
		std::cout << "hclVirtualCollisionPointsData::BarycentricPair::FromInstance: Expecting hclVirtualCollisionPointsData::BarycentricPair but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFanSection::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanSection::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFanSection") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanSection::FromInstance: Expecting hclVirtualCollisionPointsData::EdgeFanSection but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFan::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::EdgeFan::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFan") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFan::FromInstance: Expecting hclVirtualCollisionPointsData::EdgeFan but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFanSection::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanSection::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFanSection") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanSection::FromInstance: Expecting hclVirtualCollisionPointsData::TriangleFanSection but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFan::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::TriangleFan::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFan") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFan::FromInstance: Expecting hclVirtualCollisionPointsData::TriangleFan but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFanLandscape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanLandscape::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFanLandscape") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanLandscape::FromInstance: Expecting hclVirtualCollisionPointsData::EdgeFanLandscape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFanLandscape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanLandscape::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFanLandscape") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanLandscape::FromInstance: Expecting hclVirtualCollisionPointsData::TriangleFanLandscape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData") {
		std::cout << "hclVirtualCollisionPointsData::ToInstance: Expecting hclVirtualCollisionPointsData but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("blocks")->SetValue(blocks);
	class_instance->GetInstanceByFieldName("numVCPoints")->SetValue(numVCPoints);
	class_instance->GetInstanceByFieldName("landscapeParticlesBlockIndex")->SetValue(landscapeParticlesBlockIndex);
	class_instance->GetInstanceByFieldName("numLandscapeVCPoints")->SetValue(numLandscapeVCPoints);
	class_instance->GetInstanceByFieldName("edgeBarycentricsDictionary")->SetValue(edgeBarycentricsDictionary);
	class_instance->GetInstanceByFieldName("edgeDictionaryEntries")->SetValue(edgeDictionaryEntries);
	class_instance->GetInstanceByFieldName("triangleBarycentricsDictionary")->SetValue(triangleBarycentricsDictionary);
	class_instance->GetInstanceByFieldName("triangleDictionaryEntries")->SetValue(triangleDictionaryEntries);
	class_instance->GetInstanceByFieldName("edges")->SetValue(edges);
	class_instance->GetInstanceByFieldName("edgeFans")->SetValue(edgeFans);
	class_instance->GetInstanceByFieldName("triangles")->SetValue(triangles);
	class_instance->GetInstanceByFieldName("triangleFans")->SetValue(triangleFans);
	class_instance->GetInstanceByFieldName("edgesLandscape")->SetValue(edgesLandscape);
	class_instance->GetInstanceByFieldName("edgeFansLandscape")->SetValue(edgeFansLandscape);
	class_instance->GetInstanceByFieldName("trianglesLandscape")->SetValue(trianglesLandscape);
	class_instance->GetInstanceByFieldName("triangleFansLandscape")->SetValue(triangleFansLandscape);
	class_instance->GetInstanceByFieldName("edgeFanIndices")->SetValue(edgeFanIndices);
	class_instance->GetInstanceByFieldName("triangleFanIndices")->SetValue(triangleFanIndices);
	class_instance->GetInstanceByFieldName("edgeFanIndicesLandscape")->SetValue(edgeFanIndicesLandscape);
	class_instance->GetInstanceByFieldName("triangleFanIndicesLandscape")->SetValue(triangleFanIndicesLandscape);
	return true;
}

bool hktypes::hclVirtualCollisionPointsData::Block::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::Block::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::Block") {
		std::cout << "hclVirtualCollisionPointsData::Block::ToInstance: Expecting hclVirtualCollisionPointsData::Block but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::BarycentricDictionaryEntry::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::BarycentricDictionaryEntry::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::BarycentricDictionaryEntry") {
		std::cout << "hclVirtualCollisionPointsData::BarycentricDictionaryEntry::ToInstance: Expecting hclVirtualCollisionPointsData::BarycentricDictionaryEntry but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::BarycentricPair::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::BarycentricPair::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::BarycentricPair") {
		std::cout << "hclVirtualCollisionPointsData::BarycentricPair::ToInstance: Expecting hclVirtualCollisionPointsData::BarycentricPair but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFanSection::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanSection::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFanSection") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanSection::ToInstance: Expecting hclVirtualCollisionPointsData::EdgeFanSection but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFan::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::EdgeFan::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFan") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFan::ToInstance: Expecting hclVirtualCollisionPointsData::EdgeFan but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFanSection::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanSection::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFanSection") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanSection::ToInstance: Expecting hclVirtualCollisionPointsData::TriangleFanSection but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFan::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::TriangleFan::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFan") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFan::ToInstance: Expecting hclVirtualCollisionPointsData::TriangleFan but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFanLandscape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanLandscape::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFanLandscape") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanLandscape::ToInstance: Expecting hclVirtualCollisionPointsData::EdgeFanLandscape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFanLandscape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanLandscape::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFanLandscape") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanLandscape::ToInstance: Expecting hclVirtualCollisionPointsData::TriangleFanLandscape but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::Block::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::BarycentricDictionaryEntry::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::BarycentricPair::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::EdgeFanSection::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::EdgeFan::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::TriangleFanSection::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::TriangleFan::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::EdgeFanLandscape::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclVirtualCollisionPointsData::TriangleFanLandscape::GetTemplateArgs() { return {
}; };

