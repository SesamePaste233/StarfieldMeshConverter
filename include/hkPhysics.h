#pragma once
#include "Common.h"
#include "hkPhysicsChunks.h"

namespace hkphysics {
	class hkPhysicsReflectionData {
	public:
		hkPhysicsReflectionData() {
			//printf("hkPhysicsData::hkPhysicsData()\n");
		}
		~hkPhysicsReflectionData() {
			// Delete all chunks
			for (auto chunk : this->data_chunks) {
				delete chunk;
			}
		}

		std::vector<hkDataChunkBase*> data_chunks;

		const bool BigEndian = true;

		bool Deserialize(const std::string filename);

		bool Serialize(const std::string filename);

		uint32_t buffer_size = 0;
		uint32_t data_size = 0;

	};
}