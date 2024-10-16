#pragma once
#include "Common.h"
#include "hkPhysics.h"
#include "MeshIO.h"

namespace nif {
	class NifIO;

	enum class NiRTTI {
		None = 0,
		NiNodeBase,
		NiObject,
		NiNode,
		BSXFlags,
		BSGeometry,
		NiIntegerExtraData,
		NiStringExtraData,
		NiIntegersExtraData,
		SkinAttach,
		BSSkinInstance,
		BSSkinBoneData,
		BSLightingShaderProperty,
		BoneTranslations,
		BSClothExtraData,
		BSBound,
		BSConnectPointParents,
		bhkPhysicsSystem,
		bhkNPCollisionObject,
		UnkBinaryBlock,
	};

	std::string RTTIToString(const NiRTTI& rtti);

	NiRTTI StringToRTTI(const std::string& rtti);

	class NiNodeBase {
	public:
		static constexpr uint32_t NO_REF = 0xffffffff;

		NiNodeBase() = default;
		virtual ~NiNodeBase() = default;

		uint32_t type_index = NO_REF;
		uint32_t name_index = NO_REF;

		virtual void Deserialize(std::istream& file) = 0;
		virtual void Serialize(std::ostream& file) = 0;
		virtual size_t GetSize() = 0;
		virtual void UpdateStrings(const uint32_t old_id, const uint32_t new_id) {
			if (name_index == old_id) {
				name_index = new_id;
			}
		};
		virtual NiRTTI GetRTTI() const{
			return NiRTTI::NiNodeBase;
		};
		virtual std::vector<uint32_t> GetBlockReference() const = 0;
		virtual std::vector<uint32_t> GetStringReference() const {
			std::vector<uint32_t> refs;
			if (name_index != NO_REF) {
				refs.push_back(name_index);
			}
			return refs;
		};
	};

	class NiObject : public NiNodeBase {
	public:
		NiObject() = default;
		~NiObject() = default;

		enum class Flags : uint32_t {
			SAVE_EXTERNAL_GEOM_DATA = 512,
		};

		float translation[3] = { 0,0,0 };
		float rotation[3][3] = { 1,0,0,0,1,0,0,0,1 };
		float scale = 1.f;

		uint32_t controller_index = NO_REF;
		uint32_t collision_object = NO_REF;

		uint32_t flags = 0;

		uint32_t num_extra_data = 0;
		std::vector<uint32_t> extra_data;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::NiObject;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			std::vector<uint32_t> refs;
			if (controller_index != NO_REF) {
				refs.push_back(controller_index);
			}
			if (collision_object != NO_REF) {
				refs.push_back(collision_object);
			}
			for (const auto& ref : extra_data) {
				refs.push_back(ref);
			}
			return refs;
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiNodeBase::GetStringReference();
		};

		void AddExtraData(const uint32_t ref) {
			extra_data.push_back(ref);
			num_extra_data = extra_data.size();
		};
	};

	class NiNode : public NiObject {
	public:
		NiNode() = default;
		~NiNode() = default;

		uint32_t num_children = 0;
		std::vector<uint32_t> children;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiObject::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::NiNode;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			std::vector<uint32_t> refs = NiObject::GetBlockReference();
			for (const auto& ref : children) {
				refs.push_back(ref);
			}
			return refs;
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiObject::GetStringReference();
		};

		void AddChild(const uint32_t ref) {
			children.push_back(ref);
			num_children = children.size();
		};
	};

	class BSXFlags : public NiNodeBase {
	public:
		enum class BSXFLAG : uint32_t {
			None = 0,
			Animated = 1,
			Havok = 2,
			Ragdoll = 4,
			Complex = 8,
			Addon = 16,
			EditorMarker = 32,
			Dynamic = 64,
			Articulated = 128,
			NeedsTransUpdates = 256,
			RigMesh = 65536,
		};


		BSXFlags() = default;
		~BSXFlags() = default;

		uint32_t flags = 65536;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::BSXFlags;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiNodeBase::GetStringReference();
		};
	};

	class BSGeometry : public NiObject {
	public:
		struct MeshData {
			uint32_t num_indices = 0;
			uint32_t num_vertices = 0;
			uint32_t flags = 64;
			uint32_t path_length = 0;
			std::string mesh_path;
			mesh::MeshIO mesh_data;
		};

		BSGeometry() = default;
		~BSGeometry() = default;

		float center[3] = { 0,0,0 };
		float radius = 0.f;

		float bbox_center_expand[6] = { FLT_MAX,
			FLT_MAX,
			FLT_MAX,
			FLT_MAX,
			FLT_MAX,
			FLT_MAX };

		uint32_t skin_instance = NO_REF;
		uint32_t shader_property = NO_REF;
		uint32_t alpha_property = NO_REF;

		std::vector<MeshData> meshes;

		size_t _size = 0;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiObject::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::BSGeometry;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			std::vector<uint32_t> refs = NiObject::GetBlockReference();
			if (skin_instance != NO_REF) {
				refs.push_back(skin_instance);
			}
			if (shader_property != NO_REF) {
				refs.push_back(shader_property);
			}
			if (alpha_property != NO_REF) {
				refs.push_back(alpha_property);
			}
			return refs;
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiNodeBase::GetStringReference();
		};

		void AddMesh(const MeshData& mesh) {
			meshes.push_back(mesh);
		};

		inline bool _use_internal_geom_data() const {
			return this->flags & 512;
		}

		inline bool _set_use_internal_geom_data(bool use_internal) {
			if (use_internal) {
				this->flags |= 512;
			}
			else {
				this->flags &= ~512;
			}
			return this->_use_internal_geom_data();
		}
	};

	class NiIntegerExtraData : public NiNodeBase {
	public:
		NiIntegerExtraData() = default;
		~NiIntegerExtraData() = default;

		uint32_t data = 0;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::NiIntegerExtraData;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiNodeBase::GetStringReference();
		};
	};

	class NiStringExtraData : public NiNodeBase {
	public:
		NiStringExtraData() = default;
		~NiStringExtraData() = default;

		uint32_t string_index = NO_REF;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
			if (string_index == old_id) {
				string_index = new_id;
			}
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::NiStringExtraData;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() const override {
			auto refs = NiNodeBase::GetStringReference();
			if (string_index != NO_REF) {
				refs.push_back(string_index);
			}
			return refs;
		};
	};

	class NiIntegersExtraData : public NiNodeBase {
	public:
		NiIntegersExtraData() = default;
		~NiIntegersExtraData() = default;

		uint32_t num_integers = 0;
		std::vector<uint32_t> integers;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::NiIntegersExtraData;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiNodeBase::GetStringReference();
		};
	};

	class SkinAttach : public NiNodeBase {
	public:
		SkinAttach() = default;
		~SkinAttach() = default;

		uint32_t num_bone_names = 0;
		std::vector<std::string> bone_names;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::SkinAttach;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiNodeBase::GetStringReference();
		};
	};

	class BSSkin {
	public:
		class Instance : public NiNodeBase {
		public:
			Instance() = default;
			~Instance() = default;

			uint32_t skeleton_root = NO_REF;
			uint32_t bone_data = NO_REF;

			uint32_t num_bone_attachs = 0;
			std::vector<uint32_t> bone_attach_refs;

			uint32_t num_bone_scales = 0;
			std::vector<float> bone_scales;

			void Deserialize(std::istream& file) override;
			void Serialize(std::ostream& file) override;
			size_t GetSize() override;
			void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
				NiNodeBase::UpdateStrings(old_id, new_id);
			};
			NiRTTI GetRTTI() const override {
				return NiRTTI::BSSkinInstance;
			};
			
			std::vector<std::pair<std::string, std::string>> GetBoneAttachRefStringPairs(const nif::NifIO& belonged_nif) const;

			void FromBoneAttachRefStringPairs(const std::vector<std::pair<std::string, std::string>>& pairs, nif::NifIO& belonged_nif, bool not_found_ok = true);

			std::vector<uint32_t> GetBlockReference() const override {
				std::vector<uint32_t> refs;
				if (skeleton_root != NO_REF) {
					refs.push_back(skeleton_root);
				}
				if (bone_data != NO_REF) {
					refs.push_back(bone_data);
				}
				for (auto ref : bone_attach_refs) {
					if (ref != NO_REF) {
						refs.push_back(ref);
					}
				}
				return refs;
			};
			std::vector<uint32_t> GetStringReference() const override {
				return NiNodeBase::GetStringReference();
			};
		};
		class BoneData : public NiNodeBase {
		public:
			struct BoneInfo {
				float center[3] = { 0,0,0 };
				float radius = 0.f;
				float rotation[3][3] = { 1,0,0,0,1,0,0,0,1 };
				float translation[3] = { 0,0,0 };
				float scale = 1.f;
			};

			BoneData() = default;
			~BoneData() = default;

			uint32_t num_bone_infos = 0;
			std::vector<BoneInfo> bone_infos;

			void Deserialize(std::istream& file) override;
			void Serialize(std::ostream& file) override;
			size_t GetSize() override;
			void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
				NiNodeBase::UpdateStrings(old_id, new_id);
			};
			NiRTTI GetRTTI() const override {
				return NiRTTI::BSSkinBoneData;
			};
			std::vector<uint32_t> GetBlockReference() const override {
				return std::vector<uint32_t>();
			};
		};
	};

	class BSLightingShaderProperty : public NiNodeBase {
	public:
		BSLightingShaderProperty() = default;
		~BSLightingShaderProperty() = default;

		uint32_t num_extra_data = 0;
		std::vector<uint32_t> extra_data;

		uint32_t controller = NO_REF;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::BSLightingShaderProperty;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			std::vector<uint32_t> refs;
			if (controller != NO_REF) {
				refs.push_back(controller);
			}
			for (const auto& ref : extra_data) {
				refs.push_back(ref);
			}
			return refs;
		};
	};

	class BoneTranslations : public NiNodeBase {
	public:
		struct BoneTranslation {
			std::string bone_name;
			float translation[3] = { 0,0,0 };
		};

		BoneTranslations() = default;
		~BoneTranslations() = default;

		uint32_t num_translations = 0;
		std::vector<BoneTranslation> bone_translations;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::BoneTranslations;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
	};

	class BinaryBlock : public NiNodeBase {
	public:
		BinaryBlock(uint32_t bytes) :binary_bytes(bytes) {};
		~BinaryBlock() = default;

		std::string RTTI = "Unknown";
		uint32_t binary_bytes = 0;
		uint8_t* binary_data = nullptr;

		bool _decode_binary = true;

		void Dump(std::ostream& file) {
			utils::writeAsHex(file, binary_bytes);
			utils::writeStream(file, binary_data, binary_bytes);
		}

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::UnkBinaryBlock;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
	};

	class BSClothExtraData : public BinaryBlock {
	public:
		BSClothExtraData(uint32_t bytes): BinaryBlock(bytes) {};
		~BSClothExtraData() = default;

		uint64_t data_length = 0;
		hktypes::hkHolderBase* root_level_container = nullptr;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::BSClothExtraData;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};

		hkphysics::hkReflDataDeserializer& GetDataDeserializer() {
			return data;
		};

		hkphysics::hkReflDataSerializer& GetDataSerializer() {
			return data_serializer;
		};

	protected:
		hkphysics::hkReflDataDeserializer data;
		hkphysics::hkReflDataSerializer data_serializer;
	};

	class bhkPhysicsSystem : public BinaryBlock {
	public:
		bhkPhysicsSystem(uint32_t bytes) : BinaryBlock(bytes) {};
		~bhkPhysicsSystem() = default;

		uint64_t data_length = 0;
		hktypes::hkHolderBase* root_level_container = nullptr;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::bhkPhysicsSystem;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};

		hkphysics::hkReflDataDeserializer& GetDataDeserializer() {
			return data;
		};

		hkphysics::hkReflDataSerializer& GetDataSerializer() {
			return data_serializer;
		};

	protected:
		hkphysics::hkReflDataDeserializer data;
		hkphysics::hkReflDataSerializer data_serializer;
	};

	class BSBound : public NiNodeBase {
	public:
		BSBound() = default;
		~BSBound() = default;

		float center[3] = { 0,0,0 };
		float dimensions[3] = { 0,0,0 };

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;

		NiRTTI GetRTTI() const override {
			return NiRTTI::BSBound;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiNodeBase::GetStringReference();
		};
		
		static BSBound _human_bsbound_prefab() {
			BSBound bound;
			float _center[3] = {0, 0, 0.9f};
			float _dimensions[3] = {0.31f, 0.31f, 0.9f};
			memcpy(bound.center, _center, sizeof(float) * 3);
			memcpy(bound.dimensions, _dimensions, sizeof(float) * 3);
			return bound;
		}
	};

	class BSConnectPointParents : public NiNodeBase {
	public:
		class ConnectPoint {
		public:
			std::string parent_name;
			std::string child_name;
			float rot_quat[4] = { 0,0,0,1 };
			float translation[3] = { 0,0,0 };
			float scale = 1.f;

			size_t GetSize() {
				return parent_name.length() + child_name.length() + 40;
			}

			nlohmann::json ToJson() const {
				nlohmann::json j;
				j["parent_name"] = parent_name;
				j["child_name"] = child_name;
				j["rot_quat"] = { rot_quat[0], rot_quat[1], rot_quat[2], rot_quat[3] };
				j["translation"] = { translation[0], translation[1], translation[2] };
				j["scale"] = scale;
				return j;
			}

			void FromJson(nlohmann::json& json) {
				parent_name = json["parent_name"].get<std::string>();
				child_name = json["child_name"].get<std::string>();
				auto rot = json["rot_quat"].get<std::vector<float>>();
				memcpy(rot_quat, rot.data(), sizeof(float) * 4);

				auto trans = json["translation"].get<std::vector<float>>();
				memcpy(translation, trans.data(), sizeof(float) * 3);

				scale = json["scale"].get<float>();
			}
		};

		BSConnectPointParents() = default;
		~BSConnectPointParents() = default;

		uint32_t num_parents = 0;
		std::vector<ConnectPoint> connect_points;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;

		NiRTTI GetRTTI() const override {
			return NiRTTI::BSConnectPointParents;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() const override {
			return NiNodeBase::GetStringReference();
		};

		static BSConnectPointParents _human_head_attachlight_cp_prefab() {
			BSConnectPointParents cp;
			cp.num_parents = 1;
			cp.connect_points.push_back({
				"C_Head",
				"p-AttachLight",
				{3.11183E-08f,0.711903f,0.702277f,-3.06975E-08f},
				{0.149805f,0.126082f,-8.60542E-09f},
				1.f
				});
			return cp;
		}
	};

	class bhkNPCollisionObject : public NiNodeBase {
	public:
		uint32_t target_ref = NO_REF;
		uint16_t flags = 128;
		uint32_t physics_system_ref = NO_REF;
		uint32_t body_id = 0;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		NiRTTI GetRTTI() const override {
			return NiRTTI::bhkNPCollisionObject;
		};
		std::vector<uint32_t> GetBlockReference() const override {
			std::vector<uint32_t> refs;
			if (target_ref != NO_REF) {
				refs.push_back(target_ref);
			}
			if (physics_system_ref != NO_REF) {
				refs.push_back(physics_system_ref);
			}
			return refs;
		};
	};
}