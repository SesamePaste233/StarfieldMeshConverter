#pragma once
#include "Common.h"
#include "hkReflection.h"
#include "json.hpp"

namespace utils {
	class hkTypeTranscriptor {
	public:
		using MapIdType = std::string;

		static inline bool is_valid_id(MapIdType id) {
			return !id.empty();
		}

		static inline MapIdType get_invalid_id() {
			return std::string();
		}

		class TypeTranscriptProperties {
		public:
			class FieldTranscriptProperties {
			public:
				std::string name;
				MapIdType type_id;
				uint32_t offset;
				uint16_t flags;
				uint8_t unk_value;

				nlohmann::json Serialize() {
					nlohmann::json json;
					json["name"] = name;
					json["type_id"] = type_id;
					json["offset"] = offset;
					json["flags"] = flags;
					json["unk_value"] = unk_value;
					return json;
				}

				void Deserialize(nlohmann::json& json) {
					name = json["name"];
					type_id = json["type_id"];
					offset = json["offset"];
					flags = json["flags"];
					unk_value = json["unk_value"];
				}
			};

			class TemplateArgTranscriptProperties {
			public:
				std::string name;
				MapIdType type_id;
				uint32_t value;

				nlohmann::json Serialize() {
					nlohmann::json json;
					json["name"] = name;
					json["type_id"] = type_id;
					json["value"] = value;
					return json;
				}

				void Deserialize(nlohmann::json& json) {
					name = json["name"];
					type_id = json["type_id"];
					value = json["value"];
				}
			};

			MapIdType id;
			uint32_t hash;
			std::string class_name;
			std::vector<TemplateArgTranscriptProperties> template_args;
			std::vector<FieldTranscriptProperties> fields;
			MapIdType parent_class_id = get_invalid_id();
			uint8_t optionals;
			uint32_t format;
			MapIdType sub_type_id = get_invalid_id();
			uint32_t version;
			uint32_t size;
			uint32_t alignment;
			uint8_t type_flags;

			bool declared = false;
			bool defined = false;
		};

		std::unordered_map<MapIdType, TypeTranscriptProperties> type_transcripts;

		std::unordered_map<MapIdType, hkreflex::hkClassBase*> all_allocated_classes;

		static std::string transcript_path;

		static hkTypeTranscriptor& GetInstance() {
			static hkTypeTranscriptor instance;
			return instance;
		}

		static inline void SetTranscriptPath(std::string path) {
			transcript_path = path;
		}

		TypeTranscriptProperties& RegisterClass(hkreflex::hkClassBase* hk_class, bool recursive = true, bool update_exist = true);

		hkreflex::hkClassBase* AllocateClassByUniqueId(MapIdType id);

		template<typename T>
		requires hktypes::_is_hk_holder_t<T>
		inline hkreflex::hkClassInstance* Instantiate(T* c_instance);

		nlohmann::json SerializeTranscripts();

		void SerializeTranscripts(std::string path, int json_indent = -1);

		void DeserializeTranscripts(nlohmann::json& json);

		void DeserializeTranscripts(std::string path, bool throw_if_not_exist = false);

	private:
		hkTypeTranscriptor() {
			if (transcript_path.empty()) {
				transcript_path = "hkTypeTranscript.json";
			}
			DeserializeTranscripts(transcript_path);
		}
		~hkTypeTranscriptor() {
			SerializeTranscripts(transcript_path);
		}
	};


	template<typename T>
	requires hktypes::_is_hk_holder_t<T>
	inline hkreflex::hkClassInstance* hkTypeTranscriptor::Instantiate(T* c_instance)
	{
		MapIdType id = c_instance->GetTranscriptId();
		auto hk_this_class = AllocateClassByUniqueId(id);
		if (hk_this_class == nullptr) {
			throw std::runtime_error("hkTypeTranscriptor::Instantiate: unable to load class. Id: " + id);
		}

		auto hk_this_instance = hkreflex::AllocateInstance(hk_this_class, nullptr);
		if (hk_this_instance == nullptr) {
			throw std::runtime_error("hkTypeTranscriptor::Instantiate: unable to allocate instance.");
		}

		auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(hk_this_instance);
		if (class_instance == nullptr) {
			throw std::runtime_error("hkTypeTranscriptor::Instantiate: unable to cast to hkClassRecordInstance.");
		}

		if (!std::is_same_v<T::BaseType, void>) {
			auto c_base_instance = dynamic_cast<T::BaseType*>(c_instance);

			auto hk_base_instance = Instantiate(c_base_instance);

			class_instance->record_instances.push_back({ "class_parent", hk_base_instance, nullptr });
		}

		for (int i = 0; i < hk_this_class->fields.size(); ++i) {
			auto& field_name = c_instance->GethkClassMembers()[i].first;
			auto& field_type_id = c_instance->GethkClassMembers()[i].second;
			auto& field = hk_this_class->fields[i];

			assert(field_name == field->name);

			auto hk_field_class = AllocateClassByUniqueId(field_type_id);
			if (hk_field_class == nullptr) {
				throw std::runtime_error("hkTypeTranscriptor::Instantiate: unable to load field class. Id: " + field_type_id);
			}

			auto hk_field_instance = hkreflex::AllocateInstance(hk_field_class, nullptr);
			if (hk_field_instance == nullptr) {
				throw std::runtime_error("hkTypeTranscriptor::Instantiate: unable to allocate field instance.");
			}

			class_instance->record_instances.push_back({ field_name, hk_field_instance, field });
		}
	}

}