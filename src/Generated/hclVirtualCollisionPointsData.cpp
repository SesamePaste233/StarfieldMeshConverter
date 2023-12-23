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
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData") {
		std::cout << "hclVirtualCollisionPointsData::FromInstance: Wrong type!" << std::endl;
		throw;
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
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::Block") {
		std::cout << "hclVirtualCollisionPointsData::Block::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::BarycentricDictionaryEntry::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::BarycentricDictionaryEntry") {
		std::cout << "hclVirtualCollisionPointsData::BarycentricDictionaryEntry::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::BarycentricPair::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::BarycentricPair") {
		std::cout << "hclVirtualCollisionPointsData::BarycentricPair::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFanSection::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFanSection") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanSection::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFan::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFan") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFan::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFanSection::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFanSection") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanSection::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFan::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFan") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFan::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFanLandscape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFanLandscape") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanLandscape::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFanLandscape::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFanLandscape") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanLandscape::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData") {
		std::cout << "hclVirtualCollisionPointsData::ToInstance: Wrong type!" << std::endl;
		throw;
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
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::Block") {
		std::cout << "hclVirtualCollisionPointsData::Block::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::BarycentricDictionaryEntry::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::BarycentricDictionaryEntry") {
		std::cout << "hclVirtualCollisionPointsData::BarycentricDictionaryEntry::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::BarycentricPair::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::BarycentricPair") {
		std::cout << "hclVirtualCollisionPointsData::BarycentricPair::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFanSection::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFanSection") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanSection::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFan::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFan") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFan::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFanSection::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFanSection") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanSection::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFan::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFan") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFan::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::EdgeFanLandscape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::EdgeFanLandscape") {
		std::cout << "hclVirtualCollisionPointsData::EdgeFanLandscape::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	return true;
}

bool hktypes::hclVirtualCollisionPointsData::TriangleFanLandscape::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hclVirtualCollisionPointsData::TriangleFanLandscape") {
		std::cout << "hclVirtualCollisionPointsData::TriangleFanLandscape::ToInstance: Wrong type!" << std::endl;
		throw;
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

