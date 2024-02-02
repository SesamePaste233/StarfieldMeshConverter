#pragma once
#include "Common.h"
#include "hkPhysicsChunks.h"
#include "hkReflection.h"
#include <map>
#include "DataAccessor.h"

#include "hkTypesHeader.h"

namespace hkreflex {
	class hkClassBase;
	class hkIndexedDataBlock;
	class hkClassInstance;
	class hkTemplateArgumentBase;
}

namespace hktypes {
	class hkaSkeleton;
	class hkRootLevelContainer;
}

namespace hkphysics {
	enum class ChunkType;
	class hkDataChunkBase;
	class hkDataChunkPTCH;

	class hkReflDataSerializeContext {
	public:
		struct Patch {
			hkreflex::hkClassBase* type;
			std::vector<uint32_t> patch_offsets;
		};

		hkReflDataSerializeContext() {
		}
		virtual ~hkReflDataSerializeContext() {
			Clear();
		}

		const bool BigEndian = true;
		std::map<ChunkType, hkDataChunkBase*> data_chunks; // Owned by this class
		std::vector<std::string> type_names;
		std::vector<std::string> field_names;
		std::vector<hkreflex::hkClassBase*> classes; // References
		std::vector<hkreflex::hkIndexedDataBlock*> indexed_blocks; // Owned by this class
		std::vector<Patch> patches;
		std::string sdk_version = "20190200";

		hkreflex::hkClassInstance* root_level_instance = nullptr;

		uint32_t data_size = 0;

		inline uint64_t GetClassIndex(hkreflex::hkClassBase* type) {
			auto it = std::find(classes.begin(), classes.end(), type);
			if (it == classes.end()) {
				return -1;
			}
			return it - classes.begin();
		}

		inline uint64_t GetTypeNameIndex(const std::string& name) {
			auto it = std::find(type_names.begin(), type_names.end(), name);
			if (it == type_names.end()) {
				return -1;
			}
			return it - type_names.begin();
		}

		inline uint64_t GetFieldNameIndex(const std::string& name) {
			auto it = std::find(field_names.begin(), field_names.end(), name);
			if (it == field_names.end()) {
				return -1;
			}
			return it - field_names.begin();
		}

		void Clear() {
			for (auto& chunk : data_chunks) {
				delete chunk.second;
				chunk.second = nullptr;
			}
			data_chunks.clear();
			type_names.clear();
			field_names.clear();
			classes.clear();
			for (auto& block : indexed_blocks) {
				delete block;
				block = nullptr;
			}
			indexed_blocks.clear();
			patches.clear();
		}

		std::string classes_to_literal(bool show_members = true, bool use_mapped_ctype = false, bool inverse_order = false);

		std::string dump_indexed_blocks();

		std::vector<hkreflex::hkClassBase*> GetClassByName(const std::string& name);

		std::vector<hkreflex::hkClassInstance*> GetInstancesByClassName(const std::string& name);

		bool RegisterPatch(hkreflex::hkClassBase* type, uint32_t patch_offset);

		bool RegisterClassesToTranscriptor();

		utils::DataAccessor GetDataPtr(uint32_t offset = 0);

		utils::DataAccessor GetSerializeDataPtr(uint32_t offset = 0);

		void _build_data_chunks();

		void SaveToCxxCode();

		bool CompareClasses(hkReflDataSerializeContext& other);

	protected:
		utils::DataAccessor AllocateSerializeData(size_t size);

		void SetTrueAllocSize(size_t size);
	};

	class hkReflDataDeserializer : public hkReflDataSerializeContext {
	public:
		hkReflDataDeserializer() {
		}
		~hkReflDataDeserializer() {
		}

		hktypes::hkHolderBase* root_level_container = nullptr;

		bool Deserialize(const std::string filename, bool no_instantiation = false);

		bool Deserialize(hktypes::hkHolderBase*& root_level_container, std::istream& data_stream, size_t data_size) {
			auto rtn = Deserialize(data_stream, data_size);
			if (rtn) {
				root_level_container = this->root_level_container;
			}
			return rtn;
		}

		bool Deserialize(std::istream& data_stream, size_t data_size, bool no_instantiation = false);

		bool Deserialize(const uint8_t* data, size_t data_size, bool no_instantiation = false);

		void ExtractClasses();
	};

	class hkReflDataSerializer : public hkReflDataSerializeContext {
	public:
		hkReflDataSerializer() {
		}
		~hkReflDataSerializer() {
		}

		std::unordered_map<std::string, uint64_t> serialize_string_table;

		hktypes::hkHolderBase* root_level_container = nullptr;

		size_t Serialize(hktypes::hkHolderBase* root_level_container, std::ostream& data_stream) {
			this->root_level_container = root_level_container;
			return Serialize(data_stream);
		}

		size_t Serialize(std::ostream& data_stream);

	};
}
