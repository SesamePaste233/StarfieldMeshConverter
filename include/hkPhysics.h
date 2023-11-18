#pragma once
#include "Common.h"
#include "hkPhysicsChunks.h"
#include "hkReflection.h"

namespace hkphysics {
	enum class ChunkType;
	class hkDataChunkBase;

	class hkPhysicsReflectionData {
	public:
		hkPhysicsReflectionData() {
			//printf("hkPhysicsData::hkPhysicsData()\n");
		}
		~hkPhysicsReflectionData() {
			// Delete all data chunks
			for (auto& chunk : data_chunks) {
				delete chunk.second;
			}
		}
		std::string sdk_version;

		std::unordered_map<ChunkType, hkDataChunkBase*> data_chunks;

		std::vector<std::string> type_names;
		std::vector<std::string> member_names;
		std::vector<hkreflection::hkClassBase*> classes;

		const bool BigEndian = true;

		bool Deserialize(const std::string filename);

		bool Serialize(const std::string filename);

		void Clear() {
			for (auto& chunk : data_chunks) {
				delete chunk.second;
				chunk.second = nullptr;
			}
			data_chunks.clear();
			type_names.clear();
			member_names.clear();
			classes.clear();
		}

		uint32_t buffer_size = 0;
		uint32_t data_size = 0;

	};
}