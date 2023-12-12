#include "Generated\hclVirtualCollisionPointsData.h"

bool hktypes::hclVirtualCollisionPointsData::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData") {
		std::cout << "hclVirtualCollisionPointsData::FromInstance: Wrong type!" << std::endl;
		return false;
	}

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

bool hktypes::hclVirtualCollisionPointsData::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);
	if (class_instance->type->type_name != "hclVirtualCollisionPointsData") {
		std::cout << "hclVirtualCollisionPointsData::ToInstance: Wrong type!" << std::endl;
		return false;
	}

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

