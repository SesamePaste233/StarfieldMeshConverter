#pragma once
#include "Common.h"

namespace nif {
	class NiNodeBase {
	public:
		static constexpr uint32_t NO_REF = 0xffffffff;

		NiNodeBase() = default;
		~NiNodeBase() = default;

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
		virtual std::string GetRTTI() {
			return "NiNodeBase";
		};
		virtual std::vector<uint32_t> GetBlockReference() = 0;
		virtual std::vector<uint32_t> GetStringReference() {
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
		std::string GetRTTI() override {
			return "NiObject";
		};
		std::vector<uint32_t> GetBlockReference() override {
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
		std::vector<uint32_t> GetStringReference() override {
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
		std::string GetRTTI() override {
			return "NiNode";
		};
		std::vector<uint32_t> GetBlockReference() override {
			std::vector<uint32_t> refs = NiObject::GetBlockReference();
			for (const auto& ref : children) {
				refs.push_back(ref);
			}
			return refs;
		};
		std::vector<uint32_t> GetStringReference() override {
			return NiObject::GetStringReference();
		};

		void AddChild(const uint32_t ref) {
			children.push_back(ref);
			num_children = children.size();
		};
	};

	class BSXFlags : public NiNodeBase {
	public:
		BSXFlags() = default;
		~BSXFlags() = default;

		uint32_t flags = 65536;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiNodeBase::UpdateStrings(old_id, new_id);
		};
		std::string GetRTTI() override {
			return "BSXFlags";
		};
		std::vector<uint32_t> GetBlockReference() override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() override {
			return NiNodeBase::GetStringReference();
		};
	};

	class BSGeometry : public NiObject {
	public:
		typedef struct MeshData {
			uint32_t num_indices = 0;
			uint32_t num_vertices = 0;
			uint32_t flags = 64;
			uint32_t path_length = 0;
			std::string mesh_path;
		};

		BSGeometry() = default;
		~BSGeometry() = default;

		float center[3] = { 0,0,0 };
		float radius = 0.f;

		float minmax[6] = { FLT_MAX,
			FLT_MAX,
			FLT_MAX,
			FLT_MAX,
			FLT_MAX,
			FLT_MAX };

		uint32_t skin_instance = NO_REF;
		uint32_t shader_property = NO_REF;
		uint32_t alpha_property = NO_REF;

		std::vector<MeshData> meshes;

		void Deserialize(std::istream& file) override;
		void Serialize(std::ostream& file) override;
		size_t GetSize() override;
		void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
			NiObject::UpdateStrings(old_id, new_id);
		};
		std::string GetRTTI() override {
			return "BSGeometry";
		};
		std::vector<uint32_t> GetBlockReference() override {
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
		std::vector<uint32_t> GetStringReference() override {
			return NiNodeBase::GetStringReference();
		};

		void AddMesh(const MeshData& mesh) {
			meshes.push_back(mesh);
		};
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
		std::string GetRTTI() override {
			return "NiIntegerExtraData";
		};
		std::vector<uint32_t> GetBlockReference() override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() override {
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
		std::string GetRTTI() override {
			return "SkinAttach";
		};
		std::vector<uint32_t> GetBlockReference() override {
			return std::vector<uint32_t>();
		};
		std::vector<uint32_t> GetStringReference() override {
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

			uint32_t num_bone_attrs = 0;
			std::vector<uint32_t> bone_attrs;

			uint32_t num_bone_scales = 0;
			std::vector<float> bone_scales;

			void Deserialize(std::istream& file) override;
			void Serialize(std::ostream& file) override;
			size_t GetSize() override;
			void UpdateStrings(const uint32_t old_id, const uint32_t new_id) override {
				NiNodeBase::UpdateStrings(old_id, new_id);
			};
			std::string GetRTTI() override {
				return "BSSkin::Instance";
			};
			std::vector<uint32_t> GetBlockReference() override {
				std::vector<uint32_t> refs;
				if (skeleton_root != NO_REF) {
					refs.push_back(skeleton_root);
				}
				if (bone_data != NO_REF) {
					refs.push_back(bone_data);
				}
				return refs;
			};
			std::vector<uint32_t> GetStringReference() override {
				return NiNodeBase::GetStringReference();
			};
		};
		class BoneData : public NiNodeBase {
		public:
			typedef struct BoneInfo {
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
			std::string GetRTTI() override {
				return "BSSkin::BoneData";
			};
			std::vector<uint32_t> GetBlockReference() override {
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
		std::string GetRTTI() override {
			return "BSLightingShaderProperty";
		};
		std::vector<uint32_t> GetBlockReference() override {
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

}