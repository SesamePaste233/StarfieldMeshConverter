#pragma once
#include "Common.h"
#include "hkUtils.h"
#include "hkTypeMapper.h"

#include "json.hpp"
#include "hkInclude.h"

namespace hkphysics {
	class hkReflDataSerializeContext;
}

namespace hkreflex {
	enum class Optional : uint8_t
	{
		None = 0,
		Format = 1 << 0,
		SubType = 1 << 1,
		Version = 1 << 2,
		SizeAlign = 1 << 3,
		Flags = 1 << 4,
		Members = 1 << 5,
		Interfaces = 1 << 6,
		Attributes = 1 << 7
	};

	enum class TypeFlags : uint8_t
	{
		None = 0,
		NonSerializable = 1 << 0,
		Abstract = 1 << 1,
		Property = 1 << 3,
		Interface = 1 << 4
	};

	class hkClassBase;

	class CTranscriptableBase {
	public:
		virtual std::string to_C_identifier() = 0;

		virtual std::string to_C_class_definition(std::set<hkClassBase*>& ref_types, int indent = 0) = 0;

		virtual std::string to_C_FromInstance() = 0;

		virtual std::string to_C_ToInstance() = 0;
	};

	class hkTemplateArgumentBase {
	public:
		enum class ArgumentType {
			NONE,
			TYPE,
			VALUE,
			UNK,
		};

		std::string template_arg_name;

		virtual ArgumentType GetArgumentType() = 0;
		virtual std::string to_literal(bool argument_only = true) = 0;
		virtual std::string to_arg_specifier() { return template_arg_name; };
		virtual std::string to_arg_identifier() = 0;
	};

	class hkFieldBase : public CTranscriptableBase {
	public:
		enum FieldFlags :uint16_t {
			None = 0,
			NonSerializable = 1,
			Protected = 1 << 1,
			Private = 1 << 2,
			Hidden = 1 << 3,
			Property = 1 << 4,
			Field = 1 << 5,
			CustomSetter = 1 << 6,
			AdditionalUnkValue = 1 << 7,
		};

		hkClassBase* type;
		std::string name;
		uint32_t offset;
		FieldFlags flags;
		uint8_t unk_value;

		bool equals(hkFieldBase* other);

		void assert_equals(hkFieldBase* other);

		virtual std::string to_literal(bool use_mapped_ctype = false);

		std::string to_C_identifier() override;

		std::string to_C_class_definition(std::set<hkClassBase*>& ref_types, int indent = 0) override;

		std::string to_C_FromInstance() override;

		std::string to_C_ToInstance() override;
	};

	class hkInterfaceBase {
	public:
		hkClassBase* type;
		uint32_t offset;
	};

	class hkClassInstance : public utils::SerializableBase {
	public:
		hkClassBase* type;
		hkphysics::hkReflDataSerializeContext* ref_context;

		hkClassInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* ref_data) : type(type), ref_context(ref_data) {};
		virtual ~hkClassInstance() {};

		virtual bool equals(hkClassInstance* other) = 0;
		virtual void assert_equals(hkClassInstance* other) = 0;
		virtual size_t Build(utils::DataAccessor& data) = 0;
		virtual std::string dump(int indent = 0) = 0;
		virtual void CollectSerializeClasses(std::vector<hkClassBase*>& classes);
		virtual hkClassInstance* make_copy() = 0;
		virtual uint64_t GetSerializeSize() = 0;

		template<typename T>
		requires utils::_is_string_t<T> || hktypes::_is_hk_holder_t<T>
		bool GetValue(T & container) const;

		template<typename arithmetic_t>
		requires utils::_is_bool_t<arithmetic_t> || utils::_is_float_t<arithmetic_t> || utils::_is_integer_t<arithmetic_t>
		bool GetValue(arithmetic_t & container) const;

		template<typename elem_t>
		requires utils::_is_string_t<elem_t> || utils::_is_bool_t<elem_t> || utils::_is_float_t<elem_t> || utils::_is_integer_t<elem_t> || hktypes::_is_hk_holder_t<elem_t> || utils::_is_vector_t<elem_t> || hktypes::_is_hk_array_holder_t<elem_t>
		bool GetValue(std::vector<elem_t> & container) const;

		template<typename elem_t, typename sub_t = std::remove_pointer_t<elem_t>>
		requires std::is_pointer_v<elem_t> && (hktypes::_is_hk_holder_t<sub_t>)
		bool GetValue(std::vector<elem_t> &container) const;

		template<typename ptr_t, typename sub_t = std::remove_pointer_t<ptr_t>>
		requires std::is_pointer_v<ptr_t> /*&& (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t> || hktypes::_is_hk_holder_t<sub_t>)*/
		bool GetValue(ptr_t &container) const;

		template<typename T>
		requires utils::_is_string_t<T>
		bool SetValue(T & container);

		template<typename T>
		requires hktypes::_is_hk_holder_t<T>
		bool SetValue(T & container);

		template<typename arithmetic_t>
		requires utils::_is_bool_t<arithmetic_t> || utils::_is_float_t<arithmetic_t> || utils::_is_integer_t<arithmetic_t>
		bool SetValue(arithmetic_t & container);

		template<typename elem_t>
		requires utils::_is_string_t<elem_t> || utils::_is_bool_t<elem_t> || utils::_is_float_t<elem_t> || utils::_is_integer_t<elem_t> || utils::_is_vector_t<elem_t> || hktypes::_is_hk_array_holder_t<elem_t>
		bool SetValue(std::vector<elem_t> & container);

		template<typename elem_t>
		requires hktypes::_is_hk_holder_t<elem_t>
		bool SetValue(std::vector<elem_t> &container);

		template<typename elem_t, typename sub_t = std::remove_pointer_t<elem_t>>
		requires std::is_pointer_v<elem_t> && (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t> || hktypes::_is_hk_holder_t<sub_t>)
		bool SetValue(std::vector<elem_t> &container);

		template<typename ptr_t, typename sub_t = std::remove_pointer_t<ptr_t>>
		requires std::is_pointer_v<ptr_t> && (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t>)
		bool SetValue(ptr_t & container);

		template<typename ptr_t, typename sub_t = std::remove_pointer_t<ptr_t>>
		requires std::is_pointer_v<ptr_t> && (hktypes::_is_hk_holder_t<sub_t>)
		bool SetValue(ptr_t& container);
	};

	class hkIndexedDataBlock : public utils::SerializableBase {
	public:
		enum Type {
			None = 0,
			Pointer = 1,
			Array = 2,
		};

		hkIndexedDataBlock(hkphysics::hkReflDataSerializeContext* ref_data) : ref_data(ref_data) {};

		~hkIndexedDataBlock() {
		}

		hkClassBase* m_data_type = nullptr;
		Type m_block_type = Type::None;
		uint32_t m_offset = 0;
		uint32_t m_num_instances = 0;

		std::vector<hkClassInstance*> m_instances; // Reference

		hkphysics::hkReflDataSerializeContext* ref_data = nullptr;

		bool _built = false;
		bool BuildInstances();

		bool _dumped = false;
		std::string dump_instances(int indent = 0, bool use_mapped_ctype = false, bool suppress_comment = true);

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		static hkIndexedDataBlock* CreateArrayAndAlloc(hkphysics::hkReflDataSerializeContext* ref_data, hkClassBase* type, std::vector<hkClassInstance*> instances);
		
		static hkIndexedDataBlock* CreatePointerAndAlloc(hkphysics::hkReflDataSerializeContext* ref_data, hkClassBase* type, hkClassInstance* instances);
	};

	class hkClassBoolInstance : public hkClassInstance {
	public:
		std::string c_type = "bool";
		bool value = false;

		hkClassBoolInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* ref_data) : hkClassInstance(type, ref_data) {
		};

		bool equals(hkClassInstance* other) override;

		void assert_equals(hkClassInstance* other) override;

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		uint64_t GetSerializeSize() override;

		hkClassInstance* make_copy() override {
			return new hkClassBoolInstance(*this);
		}
	};

	class hkClassStringInstance : public hkClassInstance {
	public:
		std::string c_type = "std::string";
		std::string value;
		hkClassBase* char_type = nullptr; // optional
		hkreflex::hkIndexedDataBlock* data_block = nullptr; // optional

		hkClassStringInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* ref_data) : hkClassInstance(type, ref_data) {
		};

		bool equals(hkClassInstance* other) override;

		void assert_equals(hkClassInstance* other) override;

		void CollectSerializeClasses(std::vector<hkClassBase*>& classes);

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		uint64_t GetSerializeSize() override;

		hkClassInstance* make_copy() override {
			return new hkClassStringInstance(*this);
		}
	};

	class hkClassIntInstance : public hkClassInstance {
	public:
		std::string c_type = "";
		bool is_big_endian = false;
		bool is_signed = false;
		size_t byte_length = 0;

		uint64_t value = 0;
		int64_t svalue = 0;

		hkClassIntInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* ref_data);

		bool equals(hkClassInstance* other) override;

		void assert_equals(hkClassInstance* other) override;

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		uint64_t GetSerializeSize() override;

		hkClassInstance* make_copy() override {
			return new hkClassIntInstance(*this);
		}
	};

	class hkClassFloatInstance : public hkClassInstance {
	public:
		std::string c_type = "";
		bool is_big_endian = false;
		size_t bit_length = 0;
		size_t byte_length = 0;
		double value = 0;

		hkClassFloatInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* ref_data);

		bool equals(hkClassInstance* other) override;

		void assert_equals(hkClassInstance* other) override;

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		uint64_t GetSerializeSize() override;

		hkClassInstance* make_copy() override {
			return new hkClassFloatInstance(*this);
		}
	};

	class hkClassPointerInstance : public hkClassInstance {
	public:
		hkClassPointerInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* ref_data) : hkClassInstance(type, ref_data) {
		};
		// Delete instance in destructor
		~hkClassPointerInstance() {
			if (ptr_instance) {
				delete ptr_instance;
				ptr_instance = nullptr;
			}
		}

		hkClassPointerInstance(const hkClassPointerInstance& other): hkClassInstance(other) {
			c_type = other.c_type;
			in_document_ptr = other.in_document_ptr;
			data_block = other.data_block;
			ptr_instance = other.ptr_instance->make_copy();
		}

		hkClassPointerInstance& operator=(const hkClassPointerInstance& other) {
			if (this == &other)
				return *this;
			hkClassInstance::operator=(other);
			c_type = other.c_type;
			in_document_ptr = other.in_document_ptr;
			data_block = other.data_block;
			ptr_instance = other.ptr_instance->make_copy();
			return *this;
		};

		std::string c_type = "ptr";
		uint64_t in_document_ptr = NULL;
		hkIndexedDataBlock* data_block = nullptr; // Reference

		hkClassInstance* ptr_instance = nullptr; // With ownership

		bool equals(hkClassInstance* other) override;

		void assert_equals(hkClassInstance* other) override;

		void CollectSerializeClasses(std::vector<hkClassBase*>& classes);

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		uint64_t GetSerializeSize() override;

		hkClassInstance* make_copy() override {
			return new hkClassPointerInstance(*this);
		}
	};

	class hkClassRecordInstance : public hkClassInstance {
	public:
		struct Record {
			std::string field_name = "";
			hkClassInstance* instance = nullptr;
			hkFieldBase* field = nullptr;
		};
		hkClassRecordInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* ref_data) : hkClassInstance(type, ref_data) {
		};

		~hkClassRecordInstance() {
			for (auto& record : record_instances)
				delete record.instance;
		}

		hkClassRecordInstance(const hkClassRecordInstance& other) : hkClassInstance(other) {
			c_type = other.c_type;
			for(auto& record : other.record_instances) {
				record_instances.push_back({ record.field_name, record.instance->make_copy(), record.field });
			}
		}

		hkClassRecordInstance& operator=(const hkClassRecordInstance& other) {
			if (this == &other)
				return *this;
			hkClassInstance::operator=(other);
			c_type = other.c_type;
			for (auto& record : record_instances)
				delete record.instance;
			record_instances.clear();
			for (auto& record : other.record_instances) {
				record_instances.push_back({ record.field_name, record.instance->make_copy(), record.field });
			}
			return *this;
		};

		std::string c_type = "class";

		std::vector<Record> record_instances; // With ownership

		bool equals(hkClassInstance* other) override;

		void assert_equals(hkClassInstance* other) override;

		void CollectSerializeClasses(std::vector<hkClassBase*>& classes);

		size_t Build(utils::DataAccessor& data) override;

		void SetupFieldInstances();

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		uint64_t GetSerializeSize() override;

		hkClassInstance* make_copy() override {
			return new hkClassRecordInstance(*this);
		}

		hkClassInstance* GetParentInstance();

		hkClassInstance* GetInstanceByFieldName(const std::string& field_name) const;

		std::string GetStringByFieldName(const std::string& field_name) const;

		int64_t GetIntByFieldName(const std::string& field_name) const;

		uint64_t GetUIntByFieldName(const std::string& field_name) const;

		double GetFloatByFieldName(const std::string& field_name) const;

		bool GetBoolByFieldName(const std::string& field_name) const;

		template<typename T>
		requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
		std::vector<T> GetArrayByFieldName(const std::string& field_name) const;

		template<typename T>
		requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
		std::vector<T*> GetArrayOfPointersByFieldName(const std::string & field_name) const;

		template<typename T>
		requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
		T* GetPointersByFieldName(const std::string & field_name) const;
	};

	class hkClassArrayInstance : public hkClassInstance {
	public:
		hkClassArrayInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* ref_data) : hkClassInstance(type, ref_data) {
		};

		~hkClassArrayInstance() {
			for (auto instance : array_instances)
				delete instance;
		}

		hkClassArrayInstance(const hkClassArrayInstance& other) : hkClassInstance(other) {
			c_type = other.c_type;
			for (auto instance : other.array_instances) {
				array_instances.push_back(instance->make_copy());
			}
			data_block = other.data_block;
			in_document_ptr = other.in_document_ptr;
			size_and_flags = other.size_and_flags;
			std::memcpy(float_array, other.float_array, sizeof(float_array));
		}

		hkClassArrayInstance& operator=(const hkClassArrayInstance& other) {
			if (this == &other)
				return *this;
			hkClassInstance::operator=(other);
			c_type = other.c_type;
			for (auto instance : array_instances)
				delete instance;
			array_instances.clear();
			for (auto instance : other.array_instances) {
				array_instances.push_back(instance->make_copy());
			}
			data_block = other.data_block;
			in_document_ptr = other.in_document_ptr;
			size_and_flags = other.size_and_flags;
			std::memcpy(float_array, other.float_array, sizeof(float_array));
			return *this;
		};

		std::string c_type = "std::vector";
		std::vector<hkClassInstance*> array_instances; // With ownership
		hkIndexedDataBlock* data_block = nullptr;
		uint64_t in_document_ptr = NULL;
		uint64_t size_and_flags = 0;

		float float_array[16] = { 0 };

		void assert_equals(hkClassInstance* other) override;

		void CollectSerializeClasses(std::vector<hkClassBase*>& classes);

		bool equals(hkClassInstance* other) override;

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		uint64_t GetSerializeSize() override;

		hkClassInstance* make_copy() override {
			return new hkClassArrayInstance(*this);
		}

		void resize(size_t num);

		inline void update_view() {
#ifdef _DEBUG
			for (int i = 0; i < this->array_instances.size(); i++) {
				auto float_instance = dynamic_cast<hkClassFloatInstance*>(array_instances[i]);
				if (float_instance == nullptr)
					return;
				float_array[i] = (float)float_instance->value;
			}
#endif
			return;
		}
	};

	class hkClassBase : public CTranscriptableBase {
	public:
		enum TypeKind : uint8_t
		{
			Inherited = 0,
			Opaque,
			Bool,
			String,
			Int,
			Float,
			Pointer,
			Record,
			Array
		};

		~hkClassBase()
		{
			for (auto template_arg : template_args)
				delete template_arg;
			for (auto field : fields)
				delete field;
			for (auto _interface : interfaces)
				delete _interface;
		}

		uint32_t hash = 0;
		std::string type_name;
		std::string ctype_name; // Generate at runtime via type mapper
		std::vector<hkTemplateArgumentBase*> template_args; // Has references to other types

		hkClassBase* parent_class; // reference to other type or nullptr
		Optional optionals;
		uint32_t format;
		TypeKind kind; // Generated at runtime
		hkClassBase* sub_type; // reference to other type or nullptr
		uint32_t version;
		uint32_t size;
		uint32_t alignment;
		TypeFlags type_flags;
		std::vector<hkFieldBase*> fields; // Has references to other types
		std::vector<hkInterfaceBase*> interfaces; // Ignored

		// Generated at runtime
		std::vector<hkClassBase*> nested_classes;
		bool is_nested_class = false;
		hkClassBase* parent_nested_class = nullptr;
		std::string nested_type_name;
		std::string nested_parent_type_name;

		hkIndexedDataBlock* data_block; // None static, generated at runtime

		bool _declared = false;

		bool _defined = false;

		bool _instantiated = false;

		bool equals(hkClassBase* other);

		void assert_equals(hkClassBase* other);

		void CollectSerializeClasses(std::vector<hkClassBase*>& classes, bool include_definition = true);

		virtual std::string to_literal(bool show_class_members = false, bool as_plain_class = false, bool use_mapped_ctype = false);

		std::string to_C_simp_identifier();

		std::string to_C_identifier() override;

		std::string to_C_class_definition(std::set<hkClassBase*>& ref_types, int indent = 0) override;

		std::string to_C_FromInstance() override;

		std::string to_C_ToInstance() override;

		std::string to_C_GetTemplateArgs();

		std::string to_C_GetFieldTypeAndNames();

		std::string to_C_GetPropertyBag();

		uint8_t is_parent_of(hkClassBase* cls) {
			uint8_t i = 1;
			while (cls != nullptr) {
				if (cls == this)
					return i;
				cls = cls->parent_class;
				i++;
			}
			return 0;
		}
	};

	class hkTemplateArgumentType : public hkTemplateArgumentBase {
	public:
		hkClassBase* type;

		ArgumentType GetArgumentType() override {
			return ArgumentType::TYPE;
		}

		std::string to_literal(bool argument_only = true) override {
			if(argument_only)
				return type->type_name;
			else
				return "class " + template_arg_name + "=" + type->to_literal(false, true);
		}

		std::string to_arg_identifier() override {
			return type->to_C_identifier();
		}
	};

	class hkTemplateArgumentValue : public hkTemplateArgumentBase {
	public:
		uint32_t value;

		ArgumentType GetArgumentType() override {
			return ArgumentType::VALUE;
		}

		std::string to_literal(bool argument_only = true) override {
			if (argument_only)
				return std::to_string(value);
			else
				return "class " + template_arg_name + "=" + std::to_string(value);
		}

		std::string to_arg_identifier() override {
			return std::to_string(value);
		}
	};

	class hkTemplateArgumentUnk : public hkTemplateArgumentBase {
	public:
		uint32_t unk;

		ArgumentType GetArgumentType() override {
			return ArgumentType::UNK;
		}

		std::string to_literal(bool argument_only = true) override {
			if (argument_only)
				return std::to_string(unk);
			else
				return template_arg_name + "[UNK]=" + std::to_string(unk);
		}

		std::string to_arg_identifier() override {
			return std::to_string(unk);
		}
	};

	hkClassInstance* AllocateInstance(hkClassBase* type, hkphysics::hkReflDataSerializeContext* data);

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

				nlohmann::json Serialize() const {
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

				nlohmann::json Serialize() const {
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

		std::unordered_map<MapIdType, bool> entry_updated;

		std::unordered_map<MapIdType, hkreflex::hkClassBase*> all_allocated_classes; // References

		std::vector<hkreflex::hkClassBase*> all_allocated_classes_list; // References

		static std::string transcript_path;

		void Clear() {
			type_transcripts.clear();
			entry_updated.clear();
			all_allocated_classes.clear();
			all_allocated_classes_list.clear();
		}

		static hkTypeTranscriptor& GetInstance() {
			static hkTypeTranscriptor instance;
			return instance;
		}

		static inline bool SetTranscriptPath(std::string path, bool throw_if_not_exist = false) {
			std::ifstream file(path);

			std::filesystem::path currentPath = std::filesystem::current_path();

			std::filesystem::path absolutePath = currentPath / path;

			std::cout << "Loading transcript at: " << absolutePath.string() << std::endl;

			if (!file.is_open()) {

				if (throw_if_not_exist) {
					throw std::runtime_error("File not found.");
				}
				std::cout << "Warning: File not found." << std::endl;
				return false;
			}

			transcript_path = path;

			return true;
		}

		bool RegisterClass(hkreflex::hkClassBase* hk_class, bool recursive = true, bool update_exist = true);

		hkreflex::hkClassBase* AllocateClassByUniqueId(MapIdType id, bool include_definition = true);

		template<typename T>
		requires hktypes::_is_hk_holder_t<T>
		inline hkreflex::hkClassInstance* Instantiate(T& c_instance, hkphysics::hkReflDataSerializeContext* ref_data);

		nlohmann::json SerializeTranscripts() const;

		void SerializeTranscripts(std::string path, int json_indent = -1) const;

		void DeserializeTranscripts(nlohmann::json& json);

		bool DeserializeTranscripts(std::string path, bool throw_if_not_exist = false);

		inline bool TranscriptEntryUpdated(MapIdType id) const {
			if (entry_updated.find(id) == entry_updated.end())
				throw std::runtime_error("hkTypeTranscriptor::TranscriptUpdated: id not found. Id: " + id);
			return entry_updated.at(id);
		}

		inline bool TranscriptUpdated() const {
			bool updated = false;
			for (auto& entry : entry_updated) {
				if (entry.second) {
					updated = true;
					break;
				}
			}
			return updated;
		}

	private:
		hkTypeTranscriptor() {
			if (transcript_path.empty()) {
				transcript_path = "hkTypeTranscript.json";
			}
			DeserializeTranscripts(transcript_path);
		}
		~hkTypeTranscriptor() {
			if (TranscriptUpdated()) {
				std::cout << "hkTypeTranscriptor: transcript updated. Saving to " << transcript_path << std::endl;
				SerializeTranscripts(transcript_path);
			}
			else {
				std::cout << "hkTypeTranscriptor: transcript not updated. Skipping save." << std::endl;
			}
		}
	};

	template<typename T>
	requires hktypes::_is_hk_holder_t<T>
	inline hkreflex::hkClassInstance* hkTypeTranscriptor::Instantiate(T& c_instance_obj, hkphysics::hkReflDataSerializeContext* ref_data)
	{
		T* c_instance = &c_instance_obj;
		MapIdType id = c_instance->GetTranscriptId();
		auto hk_this_class = AllocateClassByUniqueId(id);
		if (hk_this_class == nullptr) {
			throw std::runtime_error("hkTypeTranscriptor::Instantiate: unable to load class. Id: " + id);
		}

		auto hk_this_instance = hkreflex::AllocateInstance(hk_this_class, ref_data);
		if (hk_this_instance == nullptr) {
			throw std::runtime_error("hkTypeTranscriptor::Instantiate: unable to allocate instance.");
		}

		auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(hk_this_instance);
		if (class_instance == nullptr) {
			throw std::runtime_error("hkTypeTranscriptor::Instantiate: unable to cast to hkClassRecordInstance.");
		}

		class_instance->SetupFieldInstances();

		return hk_this_instance;
	}

	template<typename T>
	requires utils::_is_string_t<T> || hktypes::_is_hk_holder_t<T>
	inline bool hkClassInstance::GetValue(T& container) const
	{
		if (utils::_is_string_t<T> && type->kind == hkClassBase::TypeKind::String) {
			auto string_type = dynamic_cast<const hkClassStringInstance*>(this);
			container = *reinterpret_cast<const T*>(&string_type->value);
			return true;
		}
		else if (hktypes::_is_hk_holder_t<T>) {
			if (type->kind == hkClassBase::TypeKind::Record) { // Ordinary havok classes
				reinterpret_cast<hktypes::hkHolderBase*>(&container)->FromInstance(this);
				return true;
			}
			else if (type->kind == hkClassBase::TypeKind::Array) { // Matrices, Vectors, Quaternions
				reinterpret_cast<hktypes::hkHolderBase*>(&container)->FromInstance(this);
				return true;
			}
		}
		
		return false;
	}

	template<typename arithmetic_t>
	requires utils::_is_bool_t<arithmetic_t> || utils::_is_float_t<arithmetic_t> || utils::_is_integer_t<arithmetic_t>
	inline bool hkClassInstance::GetValue(arithmetic_t& container) const
	{
		if (utils::_is_bool_t<arithmetic_t> && type->kind == hkClassBase::TypeKind::Bool) {
			auto bool_type = dynamic_cast<const hkClassBoolInstance*>(this);
			container = static_cast<arithmetic_t>(bool_type->value);
			return true;
		}
		else if (utils::_is_float_t<arithmetic_t> && type->kind == hkClassBase::TypeKind::Float) {
			auto float_type = dynamic_cast<const hkClassFloatInstance*>(this);
			container = static_cast<arithmetic_t>(float_type->value);
			return true;
		}
		else if (utils::_is_integer_t<arithmetic_t> && type->kind == hkClassBase::TypeKind::Int) {
			auto int_type = dynamic_cast<const hkClassIntInstance*>(this);
			if (int_type->is_signed) {
				if (!utils::_signed_integer_t<arithmetic_t>) {
					std::cout << "Warning: Attempting to retrieve an unsigned value from a signed value." << std::endl;
				}
				container = static_cast<arithmetic_t>(int_type->svalue);
				return true;
			}
			else if (!int_type->is_signed) {
				if (!utils::_unsigned_integer_t<arithmetic_t>) {
					std::cout << "Warning: Attempting to retrieve a signed value from an unsigned value." << std::endl;
				}
				container = static_cast<arithmetic_t>(int_type->value);
				return true;
			}
		}

		return false;
	}

	template<typename elem_t>
	requires utils::_is_string_t<elem_t> || utils::_is_bool_t<elem_t> || utils::_is_float_t<elem_t> || utils::_is_integer_t<elem_t> || hktypes::_is_hk_holder_t<elem_t> || utils::_is_vector_t<elem_t> || hktypes::_is_hk_array_holder_t<elem_t>
	inline bool hkClassInstance::GetValue(std::vector<elem_t> & container) const
	{
		if (type->kind == hkClassBase::TypeKind::Array) {
			auto array_instance = dynamic_cast<const hkClassArrayInstance*>(this);
			container.clear();
			for (auto& instance : array_instance->array_instances) {
				elem_t elem_container;
				if (instance->GetValue(elem_container)) {
					container.push_back(elem_container);
				}
			}
			return true;
		}
		return false;
	}

	template<typename elem_t, typename sub_t>
	requires std::is_pointer_v<elem_t> && (hktypes::_is_hk_holder_t<sub_t>)
	bool hkClassInstance::GetValue(std::vector<elem_t>& container) const {
		if (type->kind == hkClassBase::TypeKind::Array) {
			auto array_instance = dynamic_cast<const hkClassArrayInstance*>(this);
			container.clear();
			for (auto& instance : array_instance->array_instances) {
				hkClassPointerInstance* ptr_instance = dynamic_cast<hkClassPointerInstance*>(instance);

				if (ptr_instance == nullptr) {
					std::cout << "Instance is not array of pointers" << std::endl;
					return false;
				}

				sub_t* elem_container = static_cast<sub_t*>(hktypes::AllocateHolder(ptr_instance->ptr_instance));
				if (ptr_instance->ptr_instance->GetValue(*elem_container)) {
					container.push_back(elem_container);
				}
			}
			return true;
		}
		return false;
	}

	template<typename ptr_t, typename sub_t>
	requires std::is_pointer_v<ptr_t> /*&& (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t> || hktypes::_is_hk_holder_t<sub_t>)*/
	inline bool hkClassInstance::GetValue(ptr_t& container) const
	{
		if (type->kind == hkClassBase::TypeKind::Pointer) {
			auto ptr_instance = dynamic_cast<const hkClassPointerInstance*>(this);
			container = dynamic_cast<sub_t*>(hktypes::AllocateHolder(ptr_instance->ptr_instance));
			if (ptr_instance->ptr_instance->GetValue(*container)) {
				return false;
			}
			return true;
		}
		return false;
	}

	template<typename T>
	requires utils::_is_string_t<T>
	inline bool hkClassInstance::SetValue(T & container)
	{
		if (type->kind == hkClassBase::TypeKind::String) {
			auto string_type = dynamic_cast<hkClassStringInstance*>(this);
			string_type->value = *reinterpret_cast<std::string*>(&container);
			return true;
		}
		
		return false;
	}

	template<typename T>
	requires hktypes::_is_hk_holder_t<T>
	inline bool hkClassInstance::SetValue(T & container)
	{
		if (type->kind == hkClassBase::TypeKind::Record) {
			auto hk_holder = dynamic_cast<hktypes::hkHolderBase*>(&container);
			hk_holder->ToInstance(this);
			return true;
		}
		if (type->kind == hkClassBase::TypeKind::Array) { // hkVector4f, which is weird why they use array for this
			auto hk_holder = dynamic_cast<hktypes::hkHolderBase*>(&container);
			hk_holder->ToInstance(this);
			return true;
		}
		
		return false;
	}

	template<typename arithmetic_t>
	requires utils::_is_bool_t<arithmetic_t> || utils::_is_float_t<arithmetic_t> || utils::_is_integer_t<arithmetic_t>
	inline bool hkClassInstance::SetValue(arithmetic_t& container)
	{
		if (utils::_is_bool_t<arithmetic_t> && type->kind == hkClassBase::TypeKind::Bool) {
			auto bool_type = dynamic_cast<hkClassBoolInstance*>(this);
			bool_type->value = static_cast<bool>(container);
			return true;
		}
		else if (utils::_is_float_t<arithmetic_t> && type->kind == hkClassBase::TypeKind::Float) {
			auto float_type = dynamic_cast<hkClassFloatInstance*>(this);
			float_type->value = static_cast<double>(container);
			return true;
		}
		else if (utils::_is_integer_t<arithmetic_t> && type->kind == hkClassBase::TypeKind::Int) {
			auto int_type = dynamic_cast<hkClassIntInstance*>(this);
			if (int_type->byte_length < sizeof(arithmetic_t)) {
				std::cout << "Warning: Attempting to set the value of an instance with a value of larger size. Expected size: " << int_type->byte_length << std::endl;
			}

			if (int_type->is_signed) {
				if (!utils::_signed_integer_t<arithmetic_t>) {
					std::cout << "Warning: Attempting to set a signed value from an unsigned value." << std::endl;
				}
				int_type->svalue = static_cast<int64_t>(container);
				return true;
			}
			else if (utils::_unsigned_integer_t<arithmetic_t> && !int_type->is_signed) {
				if (!utils::_unsigned_integer_t<arithmetic_t>) {
					std::cout << "Warning: Attempting to set an unsigned value from a signed value." << std::endl;
				}
				int_type->value = static_cast<uint64_t>(container);
				return true;
			}
		}
		return false;
	}

	template<typename elem_t>
	requires utils::_is_string_t<elem_t> || utils::_is_bool_t<elem_t> || utils::_is_float_t<elem_t> || utils::_is_integer_t<elem_t> || utils::_is_vector_t<elem_t> || hktypes::_is_hk_array_holder_t<elem_t>
	inline bool hkClassInstance::SetValue(std::vector<elem_t>& container)
	{
		if (type->kind == hkClassBase::TypeKind::Array) {
			auto array_instance = dynamic_cast<hkClassArrayInstance*>(this);

			auto array_instance_copied = *array_instance;
			array_instance_copied.resize(container.size());

			for (size_t i = 0; i < container.size(); i++) {
				elem_t elem_container = container[i];
				auto& instance = array_instance_copied.array_instances[i];
				if (!instance->SetValue(elem_container)) {
					std::cout << "hkClassInstance::SetValue: Failed to set value of array instance." << std::endl;
					return false;
				}
			}

			array_instance_copied.update_view();

			*array_instance = array_instance_copied;

			return true;
		}
		return false;
	}

	template<typename elem_t>
	requires hktypes::_is_hk_holder_t<elem_t>
	inline bool hkClassInstance::SetValue(std::vector<elem_t>& container) {
		if (type->kind == hkClassBase::TypeKind::Array) {
			auto& transcriptor = hkreflex::hkTypeTranscriptor::GetInstance();
			auto array_instance = dynamic_cast<hkClassArrayInstance*>(this);

			auto array_instance_copied = *array_instance;
			array_instance_copied.resize(0);

			for (size_t i = 0; i < container.size(); i++) {
				elem_t elem_container = container[i];

				auto hk_this_instance = hkreflex::AllocateInstance(this->type->sub_type, ref_context);
				if (hk_this_instance == nullptr) {
					throw std::runtime_error("hkClassInstance::SetValue: unable to allocate instance.");
				}
				
				if (hk_this_instance->type->kind == hkClassBase::TypeKind::Record) {
					auto instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(hk_this_instance);
					if (instance == nullptr) {
						throw std::runtime_error("hkClassInstance::SetValue: unable to cast to hkClassRecordInstance.");
					}

					instance->SetupFieldInstances();
				}else if (hk_this_instance->type->kind == hkClassBase::TypeKind::Array) {
					auto instance = dynamic_cast<hkreflex::hkClassArrayInstance*>(hk_this_instance);
					if (instance == nullptr) {
						throw std::runtime_error("hkClassInstance::SetValue: unable to cast to hkClassArrayInstance.");
					}
				}
				else {
					throw std::runtime_error("hkClassInstance::SetValue: unsupported type.");
				}

				if (!hk_this_instance->SetValue(elem_container)) {
					std::cout << "hkClassInstance::SetValue: Failed to set value of array instance." << std::endl;
					return false;
				}
				array_instance_copied.array_instances.push_back(hk_this_instance);
			}

			array_instance_copied.update_view();

			*array_instance = array_instance_copied;

			return true;
		}
		return false;
	}

	template<typename elem_t, typename sub_t>
	requires std::is_pointer_v<elem_t> && (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t> || hktypes::_is_hk_holder_t<sub_t>)
	bool hkClassInstance::SetValue(std::vector<elem_t>& container) {
		if (type->kind == hkClassBase::TypeKind::Array) {
			auto& transcriptor = hkreflex::hkTypeTranscriptor::GetInstance();
			auto array_instance = dynamic_cast<hkClassArrayInstance*>(this);

			auto array_instance_copied = *array_instance;
			array_instance_copied.resize(0);

			for (size_t i = 0; i < container.size(); i++) {
				elem_t elem_container = container[i];

				auto hk_this_instance = hkreflex::AllocateInstance(this->type->sub_type, ref_context);
				if (hk_this_instance == nullptr) {
					throw std::runtime_error("hkClassInstance::SetValue: unable to allocate instance.");
				}

				auto instance = dynamic_cast<hkreflex::hkClassPointerInstance*>(hk_this_instance);
				if (instance == nullptr) {
					throw std::runtime_error("hkClassInstance::SetValue: unable to cast to hkClassPointerInstance.");
				}

				if (!instance->SetValue(elem_container)) {
					std::cout << "hkClassInstance::SetValue: Failed to set value of array instance." << std::endl;
					return false;
				}
				array_instance_copied.array_instances.push_back(instance);
			}

			array_instance_copied.update_view();

			*array_instance = array_instance_copied;

			return true;
		}
		return false;
	}

	template<typename ptr_t, typename sub_t>
	requires std::is_pointer_v<ptr_t> && (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t>)
	inline bool hkClassInstance::SetValue(ptr_t & container) {
		if (type->kind == hkClassBase::TypeKind::Pointer) {
			auto& ptr_instance = dynamic_cast<hkClassPointerInstance*>(this)->ptr_instance;

			if (ptr_instance == nullptr) {
				ptr_instance = AllocateInstance(type->sub_type, this->ref_context);
			}

			if (ptr_instance->SetValue(*container)) {
				return true;
			}
			return false;
		}
		return false;
	}

	template<typename ptr_t, typename sub_t>
	requires std::is_pointer_v<ptr_t> && (hktypes::_is_hk_holder_t<sub_t>)
	inline bool hkClassInstance::SetValue(ptr_t& container) {
		if (type->kind == hkClassBase::TypeKind::Pointer) {
			auto& ptr_instance = dynamic_cast<hkClassPointerInstance*>(this)->ptr_instance;
			auto& transcriptor = hkreflex::hkTypeTranscriptor::GetInstance();

			if (ptr_instance == nullptr) {
				ptr_instance = transcriptor.Instantiate(*container, ref_context);

				if (ptr_instance->SetValue(*container)) {
					return true;
				}
				return false;
			}
			else if (ptr_instance->type->to_C_identifier() != container->GetTranscriptId()){
				delete ptr_instance;
				ptr_instance = nullptr;

				ptr_instance = transcriptor.Instantiate(*container, ref_context);

				if (ptr_instance->SetValue(*container)) {
					return true;
				}
				return false;
			}
			else {
				if (ptr_instance->SetValue(*container)) {
					return true;
				}
				return false;
			}
		}
		return false;
	}

	template<typename T>
	requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
	inline std::vector<T> hkClassRecordInstance::GetArrayByFieldName(const std::string& field_name) const
	{
		std::vector<T> ret;
		for (auto& record : record_instances) {
			if (record.field_name == field_name) {
				auto array_instance = dynamic_cast<hkClassArrayInstance*>(record.instance);
				if (array_instance == nullptr) {
					std::cout << "hkClassRecordInstance::GetArrayByFieldName: field_name is not array" << std::endl;
					return ret;
				}
				for (auto& instance : array_instance->array_instances) {
					T container;
					if (instance->GetValue(container)) {
						ret.push_back(container);
					}
				}
				return ret;
			}
		}
		return ret;
	}

	template<typename T>
	requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
	inline std::vector<T*> hkClassRecordInstance::GetArrayOfPointersByFieldName(const std::string& field_name) const
	{
		std::vector<T*> ret;
		for (auto& record : record_instances) {
			if (record.field_name == field_name) {
				auto array_instance = dynamic_cast<hkClassArrayInstance*>(record.instance);
				if (array_instance == nullptr) {
					std::cout << "hkClassRecordInstance::GetArrayOfPointersByFieldName: field_name is not array" << std::endl;
					return ret;
				}
				for (auto& instance : array_instance->array_instances) {
					hkClassPointerInstance* ptr_instance = dynamic_cast<hkClassPointerInstance*>(instance);

					if (ptr_instance == nullptr) {
						std::cout << "hkClassRecordInstance::GetArrayOfPointersByFieldName: field_name is not array of pointers" << std::endl;
						return ret;
					}

					T* container = static_cast<T*>(hktypes::AllocateHolder(ptr_instance->ptr_instance));
					if (ptr_instance->ptr_instance->GetValue(*container)) {
						ret.push_back(container);
					}
					else {
						throw std::exception("Failed to get value of pointer instance");
						delete container;
					}
				}
				return ret;
			}
		}
		return ret;
	}

	template<typename T>
	requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
	inline T* hkClassRecordInstance::GetPointersByFieldName(const std::string& field_name) const
	{
		T* ret = nullptr;
		for (auto& record : record_instances) {
			if (record.field_name == field_name) {
				auto ptr_instance = dynamic_cast<hkClassPointerInstance*>(record.instance);
				if (ptr_instance == nullptr) {
					std::cout << "hkClassRecordInstance::GetPointerByFieldName: field_name is not pointer" << std::endl;
					return ret;
				}
				
				ret = static_cast<T*>(hktypes::AllocateHolder(ptr_instance->ptr_instance));
				if (!ptr_instance->ptr_instance->GetValue(*ret)) {
					std::cout << "hkClassRecordInstance::GetPointerByFieldName: Failed to get value of pointer instance" << std::endl;
					delete ret;
					ret = nullptr;
				}

				return ret;
			}
		}
		return ret;
	}

	//class ClassSerializeContext {
	//public:
	//	std::map<std::string, hkreflex::hkClassBase*> class_map;

	//	ClassSerializeContext() {};

	//	// Delete copy constructor
	//	ClassSerializeContext(const ClassSerializeContext&) = delete;

	//	// Delete copy assignment
	//	ClassSerializeContext& operator=(const ClassSerializeContext&) = delete;

	//	template<class T>
	//	requires hktypes::_is_hk_holder_t<T>
	//	hkreflex::hkClassBase* AddClassDefinition(T& c_instance) {
	//		utils::ClassProperty parent_class_entry = utils::ClassProperty::parse<T::BaseType>();
	//		utils::ClassProperty class_entry = utils::ClassProperty::parse<T>();
	//		std::map<std::string, utils::ClassProperty> template_args = {};
	//		std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag> field_properties = T::GetFieldTypeAndNames();

	//		auto hk_class = AddClassDeclarationImpl(class_entry, template_args);

	//		hk_class = AddClassDefinitionImpl(class_entry, parent_class_entry, T::GetPropertyBag(), field_properties);

	//		return hk_class;
	//	}

	//	hkreflex::hkClassBase* AddClassDeclarationImpl(std::string class_registry, std::map<std::string, utils::ClassProperty>& template_args) {
	//		if (class_map.find(class_registry) != class_map.end()) {
	//			return class_map[class_registry];
	//		}
	//		
	//		auto class_def = new hkreflex::hkClassBase;

	//		for (auto& arg_pair : template_args) {
	//			auto& arg_name = arg_pair.first;
	//			auto& arg_value = arg_pair.second;
	//			if (arg_name[0] == 'v') {
	//				hkreflex::hkTemplateArgumentValue* arg = new hkreflex::hkTemplateArgumentValue;
	//				arg->template_arg_name = arg_name;
	//				arg->value = stoi(arg_value.getCxxIdentifier());
	//			}
	//			else {
	//				hkreflex::hkTemplateArgumentType* arg = new hkreflex::hkTemplateArgumentType;
	//				arg->template_arg_name = arg_name;
	//				arg->type = class_map[arg_value];
	//			}
	//		}

	//		class_map[class_registry] = class_def;

	//		class_def->_declared = true;

	//		return class_def;
	//	}

	//	hkreflex::hkClassBase* AddClassDefinitionImpl(utils::ClassProperty& class_entry, utils::ClassProperty& parent_class_entry, hkreflex::hkClassBase::DefinitionPropertyBag& class_properties, std::map<std::string, hkreflex::hkFieldBase::DefinitionPropertyBag>& field_properties) {
	//		if (class_map.find(class_entry) == class_map.end()) {
	//			std::cout << "Error: Class Registry \"" << class_entry.getCxxIdentifier() << "\": Attempting to define before declare." << std::endl;
	//			throw;
	//		}
	//		
	//		auto class_def = class_map[class_entry];
	//		
	//		if (parent_class_entry.is_valid() || parent_class_entry == class_entry) {
	//			class_def->parent_class = nullptr;
	//		}
	//		else {
	//			std::map<std::string, utils::ClassProperty> template_args = {};
	//			AddClassDeclarationImpl(parent_class_entry, template_args);
	//			class_def->parent_class = class_map[parent_class_entry];
	//		}

	//		class_def->FromPropertyBag(class_properties);

	//		for (auto& field : field_properties) {
	//			auto& field_type_entry = field.first;
	//			auto& field_type_properties = field.second;
	//			//auto field_hk_class = AddClassDeclarationImpl(field_type_entry, field_type_properties.template_args);
	//		}

	//		return class_def;
	//	}
	//};
}