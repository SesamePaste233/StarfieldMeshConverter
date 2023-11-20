#pragma once
#include "Common.h"
#include "hkPhysicsChunks.h"
#include "hkReflection.h"
#include <map>

namespace hkreflex {
	class hkClassBase;
	class hkIndexedDataBlock;
}

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

		std::map<ChunkType, hkDataChunkBase*> data_chunks;

		std::vector<std::string> type_names;
		std::vector<std::string> field_names;
		std::vector<hkreflex::hkClassBase*> classes;
		std::vector<hkreflex::hkIndexedDataBlock*> indexed_blocks;

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
			field_names.clear();
			classes.clear();
		}

		const uint8_t* GetDataPtr(uint32_t offset = 0);

		std::string classes_to_literal(bool show_members = true, bool use_mapped_ctype = false, bool inverse_order = false);

		std::string dump_instances();

		uint32_t buffer_size = 0;
		uint32_t data_size = 0;

	};
}