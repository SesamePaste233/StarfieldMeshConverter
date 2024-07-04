#pragma once
#include "Common.h"
#include "NifTypes.h"
#include "MeshIO.h"

namespace nif {
	class NifIO;
	namespace ni_template {
		class NiTemplateBase;
		class NiArmatureTemplate;
		class NiSimpleGeometryTemplate;
		class NiSkinInstanceTemplate;

		enum class RTTI {
			None = 0,
			NiArmature,
			NiSimpleGeometry,
			NiSkinInstance,
		};

		enum SubTemplate {
			None = 1 << 0,
			PureSkeleton = 1 << 1,
			Weapon = 1 << 2,
			GeneralScene = 1 << 3,
		};

		template<class _to_type, class _from_type>
		NiTemplateBase* slice_cast(_from_type*& ptr) {
			_to_type* _ptr = new _to_type;
			auto n_ptr = dynamic_cast<_to_type*>(ptr);
			if (n_ptr == nullptr) {
				return nullptr;
			}
			*_ptr = *n_ptr;
			delete ptr;
			ptr = nullptr;
			return _ptr;
		};

		template<class _from_type>
		NiTemplateBase* slice_cast(_from_type*& ptr, const RTTI& rtti) {
			if (dynamic_cast<NiTemplateBase*>(ptr) == nullptr) {
				return nullptr;
			}

			switch (rtti) {
			case nif::ni_template::RTTI::NiArmature:
				return nif::ni_template::slice_cast<nif::ni_template::NiArmatureTemplate>(ptr);
			case nif::ni_template::RTTI::NiSimpleGeometry:
				return nif::ni_template::slice_cast<nif::ni_template::NiSimpleGeometryTemplate>(ptr);
			case nif::ni_template::RTTI::NiSkinInstance:
				return nif::ni_template::slice_cast<nif::ni_template::NiSkinInstanceTemplate>(ptr);
			}

			return nullptr;
		};
	};

	class NifIO
	{
	public:
		struct Header {
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

			void PurgeStrings();

			void RemoveStrings(const std::vector<uint32_t> indices);

			void RemoveReferee(const uint32_t index);

			uint32_t ReplaceString(const uint32_t index, const std::string& str);
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

			void RemoveReferee(const uint32_t index);
		};

		bool Deserialize(const std::string filename);

		bool Serialize(const std::string filename);

		bool ReadHeader(std::istream& file);

		bool WriteHeader(std::ostream& file);

		bool UpdateHeader();

		void Clear();

		static NiNodeBase* CreateBlock(const std::string type_name, const uint32_t type_index = -1, const uint32_t block_bytes = -1);
		
		NiNodeBase* AddBlock(const std::string type_name, const std::string block_name = "");

		NiNodeBase* AddBlock(const nif::NiRTTI rtti, const std::string block_name = "");

		std::string GetBlockName(const uint32_t index) const {
			if (index >= header.num_blocks) {
				return "";
			}
			if (blocks[index]->name_index >= header.strings.size()) {
				return "";
			}
			return header.strings[blocks[index]->name_index];
		}
		std::string GetBlockName(const NiNodeBase* block) const {
			return GetBlockName(block_manager.FindBlock(block));
		}

		void UpdateBlockReference(NiNodeBase* block) {
			auto block_index = block_manager.FindBlock(block);
			block_manager.RemoveReferee(block_index);
			for (const auto& ref : block->GetBlockReference()) {
				block_manager.AddReference(ref, block_manager.FindBlock(block));
			}
		};

		void UpdateStringReference(NiNodeBase* block) {
			auto block_index = block_manager.FindBlock(block);
			string_manager.RemoveReferee(block_index);
			for (const auto& ref : block->GetStringReference()) {
				string_manager.AddReference(ref, block_index);
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

		std::string assets_path = "";

		std::vector<NiNodeBase*> blocks;

		NiStringManager string_manager = NiStringManager(&header, this);

		NiBlockManager block_manager = NiBlockManager(&header, this);

		std::vector<NiNodeBase*> GetRTTIBlocks(const NiRTTI& RTTI, const bool use_name = false, const std::string& name = "") const;

		NiNode* GetRootNode() const;

		BSXFlags* GetBSXFlag() const;

		bool FromTemplate(ni_template::NiTemplateBase* template_ptr);

		template<class _template_type>
		ni_template::NiTemplateBase* ToTemplate() const {
			nif::ni_template::NiTemplateBase* t_ptr = new _template_type;
			auto rtti = t_ptr->FromNif(*this);
			if (rtti != t_ptr->GetRTTI()) {
				return ni_template::slice_cast(t_ptr, rtti);
			}
			return (ni_template::NiTemplateBase*)t_ptr;
		};

		std::vector<NiNodeBase*> GetReferencedBlocks(const NiNodeBase* referer, const NiRTTI& RTTI = NiRTTI::None, const bool use_name = false, const std::string& name = "") const;

		std::vector<NiNodeBase*> GetParentBlocks(const NiNodeBase* child, const NiRTTI& RTTI = NiRTTI::None, const bool use_name = false, const std::string& name = "") const;

		void SetAssetsPath(const std::string& path) {
			// Append "geometries" to the path if it doesn't end with it
			if (path.length() >= 11 && path.substr(path.length() - 11) != "/geometries/") {
				assets_path = path + "/geometries/";
			}
			else
				assets_path = path;
		};

		mesh::MeshIO* GetMesh(const std::string& mesh_factory_path) const;

		mesh::MeshIO* GetMesh(const nif::BSGeometry* geometry_node, int lod_index = 0) const {
			if (geometry_node->meshes.empty()) {
				return nullptr;
			}
			if (geometry_node->_use_internal_geom_data()) {
				return new mesh::MeshIO(geometry_node->meshes[lod_index].mesh_data);
			}
			return GetMesh(geometry_node->meshes[lod_index].mesh_path);
		};

		bool MergeBSGeometryAdditive(const nif::NifIO& src_nif, const nif::BSGeometry* geometry_node, std::string target_geometry_name, bool edit_mat_path);
		
		bool MergeAllBSGeometryAdditive(const nif::NifIO& src_nif, bool edit_mat_path, bool skip_if_fail = true);

		void DumpUnkBinary(const std::string& folder_path) const {
			auto unknown_blocks = this->GetRTTIBlocks(NiRTTI::UnkBinaryBlock);
			for (auto& block : unknown_blocks) {
				auto unk_block = dynamic_cast<BinaryBlock*>(block);
				if (unk_block == nullptr) continue;

				auto name = std::to_string(block_manager.FindBlock(block)) + string_manager.GetString(block->name_index);

				std::filesystem::create_directories(folder_path + "/" + unk_block->RTTI);

				std::ofstream file(folder_path + "/" + unk_block->RTTI + "/" + name + ".bin", std::ios::binary);

				if (!file.is_open()) {
					std::cerr << "Failed to open file " << folder_path + "/" + unk_block->RTTI + "/" + name + ".bin" << std::endl;
					continue;
				}

				unk_block->Dump(file);

				file.close();
			}
		}
	};


	namespace ni_template {

		class NiTemplateBase {
		public:
			virtual RTTI GetRTTI() const { return RTTI::None; };
			virtual bool ToNif(NifIO& source) { return false; };
			virtual RTTI FromNif(const NifIO& source) {
				return RTTI::None;
			}
			virtual nlohmann::json Serialize() const {
				return nlohmann::json();
			};
			virtual RTTI Deserialize(nlohmann::json data) {
				return RTTI::None;
			};
		};

		class NiArmatureTemplate : public NiTemplateBase {
		public:
			struct NodeInfo {
				NodeInfo() = default;
				~NodeInfo() = default;

				// copy constructor
				NodeInfo(const NodeInfo& other) {
					name = other.name;
					std::memcpy(rotation, other.rotation, sizeof(float) * 9);
					std::memcpy(translation, other.translation, sizeof(float) * 3);
					scale = other.scale;
					flags = other.flags;
					ni_node = other.ni_node;
					geometry_index = other.geometry_index;
					parent = other.parent;
					children = other.children;
					prevent_optimization = other.prevent_optimization;
				};

				std::string name = "";
				float rotation[3][3] = { 1,0,0,0,1,0,0,0,1 };
				float translation[3] = { 0,0,0 };
				float scale = 1.f;
				uint32_t flags = 14;

				uint32_t ni_node = -1;
				uint32_t geometry_index = -1;
				uint32_t parent = -1;
				std::vector<uint32_t> children;

				bool prevent_optimization = false;

				bool FromNiObject(const NiObject* node, const nif::NifIO& nif) {
					if (node == nullptr) return false;

					name = nif.string_manager.GetString(node->name_index);
					if (name == "") return false;

					std::memcpy(rotation, node->rotation, sizeof(float) * 9);
					std::memcpy(translation, node->translation, sizeof(float) * 3);
					scale = node->scale;
					ni_node = nif.block_manager.FindBlock(node);
					return true;
				};
			};

			NiArmatureTemplate() { bones.push_back(NodeInfo()); };
			~NiArmatureTemplate() = default;

			// copy constructor
			NiArmatureTemplate(const NiArmatureTemplate& other) {
				bones = other.bones;
				skeleton_mode = other.skeleton_mode;
				bsx_flags = other.bsx_flags;
				sub_template = other.sub_template;
				havok_skeleton = other.havok_skeleton;
				havok_root_lvl_container = other.havok_root_lvl_container;
				connection_points_parent = other.connection_points_parent;
				physics_data = other.physics_data;
				transcript_path = other.transcript_path;
			};

			NiArmatureTemplate& operator=(const NiArmatureTemplate& other) {
				bones = other.bones;
				skeleton_mode = other.skeleton_mode;
				bsx_flags = other.bsx_flags;
				sub_template = other.sub_template;
				havok_skeleton = other.havok_skeleton;
				havok_root_lvl_container = other.havok_root_lvl_container;
				connection_points_parent = other.connection_points_parent;
				physics_data = other.physics_data;
				transcript_path = other.transcript_path;
				return *this;
			};

			const NodeInfo& root_read_only() const {
				return bones[0];
			};

			NodeInfo& root() {
				return bones[0];
			};

			std::vector<NodeInfo> bones;

			std::vector<BSConnectPointParents::ConnectPoint> connection_points_parent;

			hktypes::hkaSkeleton* havok_skeleton = nullptr;

			hktypes::hkRootLevelContainer* havok_root_lvl_container = nullptr;

			bool skeleton_mode = false;

			SubTemplate sub_template = SubTemplate::None;

			uint32_t bsx_flags = 65536;

			nlohmann::json physics_data;
			std::string transcript_path = "";

			RTTI GetRTTI() const override {
				return RTTI::NiArmature;
			};

			bool ToNif(NifIO& source) override;

			RTTI FromNif(const NifIO& source) override;

			nlohmann::json Serialize() const override {
				if (IsRootEmtpy()) {
					return nlohmann::json();
				}

				Eigen::Matrix4f root_axis = Eigen::Matrix4f::Identity();
				auto json_data = SerializeGlobalImpl(0, root_axis);

				json_data["skeleton_mode"] = skeleton_mode;

				if (!connection_points_parent.empty()) {
					json_data["connection_points_p"] = nlohmann::json::array();
					for (auto& cp : connection_points_parent) {
						std::cout << "CPA: " << cp.parent_name << " -> " << cp.child_name << std::endl;
						json_data["connection_points_p"].push_back(cp.ToJson());
					}
				}

				if (havok_skeleton != nullptr) {
					nlohmann::json havok_skeleton_json = havok_skeleton->ToJson();

					json_data["havok_skeleton"] = havok_skeleton_json;

					if (havok_root_lvl_container) {
						auto havok_cloth_datas = havok_root_lvl_container->GetNamedVariantRefs("hclClothData");
						for (auto data : havok_cloth_datas) {
							auto havok_cloth_data = dynamic_cast<hktypes::hclClothData*>(data);
							if (havok_cloth_data != nullptr) {
								auto havok_meshes = havok_cloth_data->GetBufferedMeshes();
								for (auto& mesh : havok_meshes) {
									auto mesh_json = mesh.ToJson();
									json_data["havok_meshes"].push_back(mesh_json);
								}
							}
						}
					}
				}

				return json_data;
			};

			RTTI Deserialize(nlohmann::json data) override {
				this->bones.clear();
				this->bones.push_back(NodeInfo());
				if (data.is_null()) {
					return RTTI::None;
				}

				if (data.contains("connection_points_p")) {
					for (auto& cp : data["connection_points_p"]) {
						BSConnectPointParents::ConnectPoint new_cp;
						new_cp.FromJson(cp);
						connection_points_parent.push_back(new_cp);
					}
				}

				if (data.contains("physics_data")) {
					physics_data = data["physics_data"];
				}

				if (data.contains("transcript_path")) {
					transcript_path = data["transcript_path"];
				}

				if (data.find("skeleton_mode") != data.end())
					skeleton_mode = data["skeleton_mode"];

				if (data.find("auto_detect") != data.end() && int(data["auto_detect"])) {
					std::string root_name = data["name"];
					if (root_name == "WEAPON") {
						sub_template = SubTemplate::Weapon;
					}
					else if (root_name == "ExportScene") {
						sub_template = SubTemplate::GeneralScene;
					}
					else if (!root_name.empty()) {
						for (auto& child : data["children"]) {
							if (child["name"] == "Root") {
								sub_template = SubTemplate::PureSkeleton;
								break;
							}
						}
					}
				}

				if (data.find("sub_template") != data.end()) {
					sub_template = SubTemplate(uint32_t(data["sub_template"]));
				}

				if (data.find("BSX") != data.end()) {
					this->bsx_flags = data["BSX"];
				}
				else if (sub_template & (SubTemplate::Weapon|SubTemplate::PureSkeleton)) {
					this->bsx_flags = 74;
				}
				else if (sub_template & SubTemplate::GeneralScene) {
					this->bsx_flags = 10;
				}

				Eigen::Matrix4f root_axis = Eigen::Matrix4f::Identity();

				bool success = DeserializeGlobalImpl(0, data, root_axis);
				if (!success) {
					return RTTI::None;
				}
				return RTTI::NiArmature;
			};

			nlohmann::json SerializeGlobalImpl(const uint32_t current_index, Eigen::Matrix4f& cur_axis) const {
				if (current_index == -1) {
					return nullptr;
				}

				auto current = &bones[current_index];

				nlohmann::json serialized;

				Eigen::Matrix4f T = utils::xf::createTransformationMatrix(current->rotation, current->translation);

				Eigen::Matrix4f new_axis = cur_axis * T;
				auto rtn = utils::xf::toAxis(new_axis, 0.07);

				serialized["name"] = current->name;
				serialized["head"].push_back(rtn.first.x());
				serialized["head"].push_back(rtn.first.y());
				serialized["head"].push_back(rtn.first.z());
				serialized["tail"].push_back(rtn.second.x());
				serialized["tail"].push_back(rtn.second.y());
				serialized["tail"].push_back(rtn.second.z());
				for (int i = 0; i < 4; ++i) {
					serialized["matrix"].push_back(nlohmann::json::array());
					for (int j = 0; j < 4; ++j) {
						serialized["matrix"][i].push_back(new_axis(i, j));
					}
				}
				serialized["scale"] = current->scale;

				serialized["geometry_index"] = current->geometry_index;

				serialized["sgo_keep"] = int(current->prevent_optimization);

				serialized["children"] = nlohmann::json::array();
				for (uint32_t child : bones[current_index].children) {
					if (skeleton_mode && skeleton_bones.find(bones[child].name) == skeleton_bones.end()) {
						continue;
					}
					serialized["children"].push_back(SerializeGlobalImpl(child, new_axis));
				}

				return serialized;
			}

			bool DeserializeGlobalImpl(uint32_t current_index, nlohmann::json& data, Eigen::Matrix4f& cur_axis) {
				if (current_index == -1) {
					return false;
				}

				auto current = &bones[current_index];

				current->name = data["name"];
				current->scale = data["scale"];

				current->geometry_index = data["geometry_index"];

				current->prevent_optimization = int(data["sgo_keep"]);

				Eigen::Matrix4f new_axis = Eigen::Matrix4f::Identity();
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 4; ++j) {
						new_axis(i, j) = data["matrix"][i][j];
					}
				}
				Eigen::Matrix4f T = utils::xf::quickInverse(cur_axis) * new_axis;
				Eigen::Matrix4f R, t;
				utils::xf::decomposeTransformation(T, R, t);

				current->rotation[0][0] = R(0, 0);
				current->rotation[0][1] = R(0, 1);
				current->rotation[0][2] = R(0, 2);
				current->rotation[1][0] = R(1, 0);
				current->rotation[1][1] = R(1, 1);
				current->rotation[1][2] = R(1, 2);
				current->rotation[2][0] = R(2, 0);
				current->rotation[2][1] = R(2, 1);
				current->rotation[2][2] = R(2, 2);

				current->translation[0] = t(0, 3);
				current->translation[1] = t(1, 3);
				current->translation[2] = t(2, 3);


				for (auto& child : data["children"]) {
					NodeInfo new_child;
					new_child.parent = current_index;
					bones[current_index].children.push_back(this->bones.size());
					uint32_t new_index = this->bones.size();
					this->bones.push_back(new_child);
					DeserializeGlobalImpl(new_index, child, new_axis);
				}

				return true;
			};

			const std::unordered_set<std::string> skeleton_bones = {
				"Root",
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

			void Traverse(uint32_t cur_node_index, std::function<void(NodeInfo&)> func) {
				func(bones[cur_node_index]);
				for (auto child : bones[cur_node_index].children) {
					Traverse(child, func);
				}
			};

			bool IsRootEmtpy() const {
				return bones.size() == 0 || root_read_only().name == "";
			};
		};

		class NiSimpleGeometryTemplate :public NiArmatureTemplate {
		public:
			struct MeshInfo {
				bool has_mesh = false;
				uint32_t num_indices = 0;
				uint32_t num_vertices = 0;
				std::string factory_path = "";
				mesh::MeshIO mesh_data;
			};

			NiSimpleGeometryTemplate() = default;
			~NiSimpleGeometryTemplate() = default;

			// copy constructor
			NiSimpleGeometryTemplate(const NiSimpleGeometryTemplate& other) {
				bsx_flags = other.bsx_flags;
				geo_infos = other.geo_infos;
			};

			NiSimpleGeometryTemplate& operator=(const NiSimpleGeometryTemplate& other) {
				this->NiArmatureTemplate::operator=(other);
				bsx_flags = other.bsx_flags;
				geo_infos = other.geo_infos;
				return *this;
			};

			struct GeoInfo {
				bool use_internal_geom_data = false;

				MeshInfo geo_mesh_lod[4];

				float bounding_sphere[4] = { 0,0,0,0 };
				float bounding_center[3] = { FLT_MAX,FLT_MAX,FLT_MAX };
				float bounding_expand[3] = { FLT_MAX,FLT_MAX,FLT_MAX };

				uint32_t mat_id = 0;
				std::string mat_path = "";
			};

			std::vector<GeoInfo> geo_infos;

			RTTI GetRTTI() const override {
				return RTTI::NiSimpleGeometry;
			};
			bool ToNif(NifIO& source) override;
			RTTI FromNif(const NifIO& source) override;
			nlohmann::json Serialize() const override;
			RTTI Deserialize(nlohmann::json data) override;
		};

		class NiSkinInstanceTemplate :public NiSimpleGeometryTemplate {
		public:
			typedef nif::BSSkin::BoneData::BoneInfo BoneInfo;

			struct SkinInfo {
				bool has_skin = false;
				bool request_recalc_bounding_sphere = false;
				std::vector<std::string> bone_names;
				std::vector<std::string> bone_refs;
				std::vector<BoneInfo> bone_infos;
			};

			NiSkinInstanceTemplate() = default;
			~NiSkinInstanceTemplate() = default;

			// copy constructor
			NiSkinInstanceTemplate(const NiSkinInstanceTemplate& other) {
				skin_infos = other.skin_infos;
			};

			NiSkinInstanceTemplate& operator=(const NiSkinInstanceTemplate& other) {
				this->NiSimpleGeometryTemplate::operator=(other);
				skin_infos = other.skin_infos;
				return *this;
			};

			std::vector<SkinInfo> skin_infos;

			RTTI GetRTTI() const override {
				return RTTI::NiSkinInstance;
			};
			bool ToNif(NifIO& source) override;
			RTTI FromNif(const NifIO& source) override;
			nlohmann::json Serialize() const override;
			RTTI Deserialize(nlohmann::json data) override;

		};

	};	
}