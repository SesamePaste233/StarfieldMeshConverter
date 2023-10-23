#pragma once
#include "Common.h"
#include "NifTypes.h"
#include "MeshIO.h"

namespace nif {
	class NifIO;
	namespace ni_template {
		class NiTemplateBase;
		class NiRootSceneTemplate;
		class NiSimpleGeometryTemplate;
		class NiSkinInstanceTemplate;
	};

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

			std::string GetString(const uint32_t index) const;

			uint32_t FindString(const std::string& str) const;

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

			NiNodeBase* GetBlock(const uint32_t index) const;

			uint32_t FindBlock(const NiNodeBase* block) const;

			uint32_t FindBlockByName(const std::string& name) const;
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

	class Armature {
	public:
		typedef struct Bone {
			~Bone() {
				for (Bone* child : children) {
					delete child;
				}
			};

			std::string name = "";
			float rotation[3][3] = { 1,0,0,0,1,0,0,0,1 };
			float translation[3] = { 0,0,0 };
			float scale = 1.f;
			Bone* parent = nullptr;
			std::vector<Bone*> children;

			void SetParent(Bone* parent) {
				this->parent = parent;
				parent->children.push_back(this);
			};

			bool FromNiNode(const NiNode* node, const nif::NifIO& nif) {
				if (node == nullptr) return false;

				name = nif.string_manager.GetString(node->name_index);
				if (name == "") return false;

				std::memcpy(rotation, node->rotation, sizeof(float) * 9);
				std::memcpy(translation, node->translation, sizeof(float) * 3);
				scale = node->scale;
				return true;
			};
		};

		Armature() = default;
		~Armature() = default;

		Bone* root = nullptr;

		bool FromNif(const NifIO& source, const bool skeleton_mode = true);

		bool ToJson(const std::string& file);

		nlohmann::json Serialize(Bone* current) {
			if (!current) {
				return nullptr;
			}

			nlohmann::json serialized;
			serialized["name"] = current->name;
			serialized["rotation"] = nlohmann::json::array();
			for (int i = 0; i < 3; i++) {
				serialized["rotation"].push_back(nlohmann::json::array());
				for (int j = 0; j < 3; j++) {
					serialized["rotation"][i].push_back(current->rotation[i][j]);
				}
			}
			serialized["translation"] = nlohmann::json::array();
			for (int i = 0; i < 3; i++) {
				serialized["translation"].push_back(current->translation[i]);
			}
			serialized["scale"] = current->scale;
			for (Bone* child : current->children) {
				serialized["children"].push_back(Serialize(child));
			}

			return serialized;
		}

		const std::unordered_set<std::string> skeleton_bones = {
			"COM",
			"C_Spine",
			"C_Hips",
			"R_Butt",
			"L_Butt",
			"L_Thigh",
			"R_Thigh",
			"R_Thigh_Twist1",
			"R_Thigh_Twist",
			"R_Knee",
			"R_Calf",
			"R_CalfMass",
			"R_Foot",
			"R_Toe",
			"L_Thigh_Twist1",
			"L_Thigh_Twist",
			"L_Knee",
			"L_Calf",
			"L_CalfMass",
			"L_Foot",
			"L_Toe",
			"C_Spine1",
			"C_Spine2",
			"C_Chest",
			"DirectAt",
			"WeaponLeft",
			"WEAPON",
			"R_Clavicle",
			"C_BackPack",
			"L_Clavicle",
			"C_Neck",
			"C_Neck_Twist",
			"C_Neck1",
			"C_Head",
			"Eye_Target",
			"R_Eye",
			"L_Eye",
			"L_Biceps",
			"L_Biceps_Twist1",
			"L_Biceps_Twist",
			"L_Elbow",
			"L_Forearm",
			"L_Wrist_Twist2",
			"L_Wrist_Twist1",
			"L_Wrist_Twist",
			"L_Arm",
			"L_Wrist",
			"L_AnimObject3",
			"L_AnimObject2",
			"L_AnimObject1",
			"L_Index",
			"L_Middle",
			"L_Ring",
			"L_Cup",
			"L_Thumb",
			"L_Thumb1",
			"L_Thumb2",
			"L_Pinky",
			"L_Pinky1",
			"L_Pinky2",
			"L_Ring1",
			"L_Ring2",
			"L_Middle1",
			"L_Middle2",
			"L_Index1",
			"L_Index2",
			"L_Deltoid",
			"L_ArmMass",
			"C_BackPackHose",
			"R_Biceps",
			"R_Biceps_Twist1",
			"R_Biceps_Twist",
			"R_Elbow",
			"R_Forearm",
			"R_Wrist_Twist2",
			"R_Wrist_Twist1",
			"R_Wrist_Twist",
			"R_Arm",
			"R_Wrist",
			"R_AnimObject3",
			"R_AnimObject2",
			"R_AnimObject1",
			"R_Index",
			"R_Middle",
			"R_Ring",
			"R_Cup",
			"R_Thumb",
			"R_Thumb1",
			"R_Thumb2",
			"R_Pinky",
			"R_Pinky1",
			"R_Pinky2",
			"R_Ring1",
			"R_Ring2",
			"R_Middle1",
			"R_Middle2",
			"R_Index1",
			"R_Index2",
			"R_Deltoid",
			"R_ArmMass",
			"L_HandIk",
			"R_HandIk",
		};

		const std::unordered_set<std::string> skeleton_bones_exclude = {
			
		};
	};
}