#pragma once
#include "Common.h"
#include "hkPhysicsChunks.h"
#include "hkReflection.h"
#include <map>
#include "DataAccessor.h"
#include "hkTypes.h"

namespace hkreflex {
	class hkClassBase;
	class hkIndexedDataBlock;
	class hkClassInstance;
	class hkTemplateArgumentBase;
}

namespace hktypes {
	class hkaSkeletonHolder;
}

namespace hkphysics {
	enum class ChunkType;
	class hkDataChunkBase;
	class hkDataChunkPTCH;

	class hkPhysicsReflectionData {
	public:
		hkPhysicsReflectionData() {
			//printf("hkPhysicsData::hkPhysicsData()\n");
		}
		~hkPhysicsReflectionData() {
			for(auto& block:indexed_blocks) {
				delete block;
			}

			for (auto& cls : classes) {
				delete cls;
			}

			for (auto& chunk : data_chunks) {
				delete chunk.second;
			}
		}
		const bool BigEndian = true;

		std::map<ChunkType, hkDataChunkBase*> data_chunks;
		std::vector<std::string> type_names;
		std::vector<std::string> field_names;
		std::vector<hkreflex::hkClassBase*> classes;
		std::vector<hkreflex::hkIndexedDataBlock*> indexed_blocks;

		std::string sdk_version;
		hkreflex::hkClassInstance* root_level_instance = nullptr;

		uint32_t data_size = 0;
		bool _is_type_unchanged = true;
		std::vector<hkreflex::hkIndexedDataBlock*> indexed_blocks_out;
		std::unordered_map<std::string, uint64_t> serialize_string_table;

		hktypes::hkaSkeletonHolder* skeleton = nullptr;

		bool Deserialize(const std::string filename);

		bool Deserialize(std::istream& data_stream);

		bool Deserialize(const uint8_t* data);

		void ExtractClasses();

		bool SerializeWithTypeUnchanged(std::ostream& data_stream);

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

		hkDataChunkPTCH* GetPatchChunk();

		utils::DataAccessor GetDataPtr(uint32_t offset = 0);

		utils::DataAccessor AllocateSerializeData(uint32_t size);

		utils::DataAccessor GetSerializeDataPtr(uint32_t offset = 0);

		std::vector<hkreflex::hkClassBase*> GetClassByName(const std::string& name);

		std::string classes_to_literal(bool show_members = true, bool use_mapped_ctype = false, bool inverse_order = false);

		std::string dump_root_instance();

		std::string dump_indexed_blocks();

		std::vector<hkreflex::hkClassInstance*> GetInstancesByClassName(const std::string& name);

	};
}