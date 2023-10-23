#pragma once
#include "Common.h"
#include "NifTypes.h"
#include "MeshIO.h"

namespace nif {
	class NifIO;
	class ni_template::NiTemplateBase;

	class NifIO
	{
	public:
		typedef struct Header {
			std::string header = "Gamebryo File Format, Version 20.2.0.7";
			std::vector<uint8_t> version = {10,7,0,2,20};
			uint8_t endian = 1;
			uint32_t user_version = 12;
			uint32_t num_blocks;
			uint32_t BS_version = 172;
			std::string author = "";
			uint32_t unk1 = 3;
			std::string process_script = "Blender Mesh Plugin";
			std::string unk2 = "\x13\x30\xf6\xe6\x5b\x02\x00";
			uint16_t num_types;
			std::vector<std::string> block_types;
			std::vector<uint16_t> block_type_indices;
			std::vector<uint32_t> block_sizes;
			uint32_t num_strings;
			uint32_t max_string_length;
			std::vector<std::string> strings;
			uint32_t num_groups = 0;
			std::vector<std::string> groups;
		};

		class NiStringManager {
		public:
			NiStringManager(Header* header_ptr, NifIO* nif_ptr) : header(header_ptr), nif(nif_ptr) {};
			~NiStringManager() = default;

			Header* header = nullptr;
			NifIO* nif = nullptr;

			std::unordered_map<uint32_t, std::vector<uint32_t>> refs;

			uint32_t AddString(const std::string& str, const uint32_t& who);

			uint32_t AddReference(const uint32_t& index, const uint32_t& who);

			std::string GetString(const uint32_t index);

			uint32_t FindString(const std::string& str);

			void MoveString(const std::vector<uint32_t> new_order);
		};

		class NiBlockManager {
		public:
			NiBlockManager(Header* header_ptr, NifIO* nif_ptr) : header(header_ptr), nif(nif_ptr) {};
			~NiBlockManager() = default;

			Header* header = nullptr;
			NifIO* nif = nullptr;

			std::unordered_map<uint32_t, std::vector<uint32_t>> refs;

			uint32_t RegisterBlock(NiNodeBase* block);

			uint32_t AddReference(const uint32_t& index, const uint32_t& who);

			NiNodeBase* GetBlock(const uint32_t index);

			uint32_t FindBlock(const NiNodeBase* block);

			uint32_t FindBlockByName(const std::string& name);
		};

		bool Deserialize(const std::string filename);

		bool Serialize(const std::string filename);

		bool ReadHeader(std::istream& file);

		bool WriteHeader(std::ostream& file);

		bool UpdateHeader();

		void Clear();

		static NiNodeBase* CreateBlock(const std::string type_name, const uint32_t type_index = -1, const uint32_t block_bytes = -1);
		
		NiNodeBase* AddBlock(const std::string type_name, const std::string block_name = "");

		void UpdateBlockReference(NiNodeBase* block) {
			for (const auto& ref : block->GetBlockReference()) {
				block_manager.AddReference(ref, block_manager.FindBlock(block));
			}
		};

		void UpdateStringReference(NiNodeBase* block) {
			for (const auto& ref : block->GetStringReference()) {
				string_manager.AddReference(ref, block_manager.FindBlock(block));
			}
		};

		void UpdateReferences(NiNodeBase* block) {
			UpdateBlockReference(block);
			UpdateStringReference(block);
		};

		void UpdateBlockReferences() {
			for (const auto& block : blocks) {
				UpdateBlockReference(block);
			}
		};

		void UpdateStringReferences() {
			for (const auto& block : blocks) {
				UpdateStringReference(block);
			}
		};

		Header header;

		std::vector<NiNodeBase*> blocks;

		NiStringManager string_manager = NiStringManager(&header, this);

		NiBlockManager block_manager = NiBlockManager(&header, this);

		std::vector<NiNodeBase*> GetRTTIBlocks(const std::string& RTTI);

		bool FromTemplate(ni_template::NiTemplateBase* template_ptr);
	};


	namespace ni_template {
		class NiTemplateBase {
		public:
			virtual bool ToNif(NifIO& source) = 0;
		};

		class NiRootSceneTemplate :public NiTemplateBase {
		public:
			NiRootSceneTemplate() = default;
			~NiRootSceneTemplate() = default;

			float root_rotation_matrix[3][3] = { 1,0,0,0,1,0,0,0,1 };
			float root_translation[3] = { 0,0,0 };
			float root_scale = 1;
			uint32_t root_flags = 0x2000000E;
			std::string root_name = "ExportScene";

			bool ToNif(NifIO& source) override;
		};
		
		class NiSimpleGeometryTemplate :public NiRootSceneTemplate {
		public:
			typedef struct MeshInfo {
				mesh::MeshIO* entry = nullptr;
				std::string factory_path = "";
			};

			NiSimpleGeometryTemplate() = default;
			~NiSimpleGeometryTemplate() = default;

			uint32_t bsx_flags = 65536;

			float geo_rotation_matrix[3][3] = { 1,0,0,0,1,0,0,0,1 };
			float geo_translation[3] = { 0,0,0 };
			float geo_scale = 1;
			uint32_t geo_flags = 0x0000000E;
			std::string geo_name = "";

			MeshInfo geo_mesh_lod[4];

			uint32_t mat_id = 0;
			std::string mat_path = "";

			bool ToNif(NifIO& source) override;
		};

		class NiSkinInstanceTemplate :public NiSimpleGeometryTemplate {
		public:
			typedef nif::BSSkin::BoneData::BoneInfo BoneInfo;

			NiSkinInstanceTemplate() = default;
			~NiSkinInstanceTemplate() = default;

			std::vector<std::string> bone_names;
			std::vector<std::string> bone_refs;
			std::vector<BoneInfo> bone_infos;

			bool ToNif(NifIO& source) override;
		};
	};

}