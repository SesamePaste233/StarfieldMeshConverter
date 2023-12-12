#pragma once
#include "Common.h"
#include "hkUtils.h"
#include "hkTypeMapper.h"

#include "hkInclude.h"

namespace hkphysics {
	class hkPhysicsReflectionData;
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

		virtual std::string to_C_class_definition(std::vector<hkClassBase*>& ref_types, int indent = 0) = 0;

		virtual std::string to_C_from_instance() = 0;

		virtual std::string to_C_to_instance() = 0;
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

		virtual std::string to_literal(bool use_mapped_ctype = false);

		std::string to_C_identifier() override;

		std::string to_C_class_definition(std::vector<hkClassBase*>& ref_types, int indent = 0) override;

		std::string to_C_from_instance() override;

		std::string to_C_to_instance() override;
	};

	class hkInterfaceBase {
	public:
		hkClassBase* type;
		uint32_t offset;
	};

	class hkClassInstance : public utils::SerializableBase {
	public:
		hkClassBase* type;
		hkphysics::hkPhysicsReflectionData* ref_data;

		hkClassInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : type(type), ref_data(ref_data) {};
		virtual size_t Build(utils::DataAccessor& data) = 0;
		virtual std::string dump(int indent = 0) = 0;
		virtual hkClassInstance* make_copy() = 0;

		template<typename T>
		requires utils::_is_string_t<T> || hktypes::_is_hk_holder_t<T>
		bool GetValue(T & container) const;

		template<typename arithmetic_t>
		requires utils::_is_bool_t<arithmetic_t> || utils::_is_float_t<arithmetic_t> || utils::_is_integer_t<arithmetic_t>
		bool GetValue(arithmetic_t & container) const;

		template<typename elem_t>
		requires utils::_is_string_t<elem_t> || utils::_is_bool_t<elem_t> || utils::_is_float_t<elem_t> || utils::_is_integer_t<elem_t> || hktypes::_is_hk_holder_t<elem_t> || utils::_is_vector_t<elem_t> || hktypes::_is_hk_array_holder_t<elem_t>
		bool GetValue(std::vector<elem_t> & container) const;

		template<typename ptr_t, typename sub_t = std::remove_pointer_t<ptr_t>>
		requires std::is_pointer_v<ptr_t> && (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t> || hktypes::_is_hk_holder_t<sub_t>)
		bool GetValue(ptr_t &container) const;

		template<typename T>
		requires utils::_is_string_t<T> || hktypes::_is_hk_holder_t<T>
		bool SetValue(T & container);

		template<typename arithmetic_t>
		requires utils::_is_bool_t<arithmetic_t> || utils::_is_float_t<arithmetic_t> || utils::_is_integer_t<arithmetic_t>
		bool SetValue(arithmetic_t & container);

		template<typename elem_t>
		requires utils::_is_string_t<elem_t> || utils::_is_bool_t<elem_t> || utils::_is_float_t<elem_t> || utils::_is_integer_t<elem_t> || hktypes::_is_hk_holder_t<elem_t> || utils::_is_vector_t<elem_t> || hktypes::_is_hk_array_holder_t<elem_t>
		bool SetValue(std::vector<elem_t> & container);

		template<typename ptr_t, typename sub_t = std::remove_pointer_t<ptr_t>>
		requires std::is_pointer_v<ptr_t> && (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t> || hktypes::_is_hk_holder_t<sub_t>)
		bool SetValue(ptr_t & container);
	
	};

	class hkIndexedDataBlock : public utils::SerializableBase {
	public:
		enum Type {
			None = 0,
			Pointer = 1,
			Array = 2,
		};

		hkIndexedDataBlock(hkphysics::hkPhysicsReflectionData* ref_data) : ref_data(ref_data) {};

		~hkIndexedDataBlock() {
		}

		hkClassBase* m_data_type = nullptr;
		Type m_block_type = Type::None;
		uint32_t m_offset = 0;
		uint32_t m_num_instances = 0;

		std::vector<hkClassInstance*> m_instances; // Reference

		hkphysics::hkPhysicsReflectionData* ref_data = nullptr;

		bool _built = false;
		bool BuildInstances();

		bool _dumped = false;
		std::string dump_instances(int indent = 0, bool use_mapped_ctype = false, bool suppress_comment = true);

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		static hkIndexedDataBlock* CreateArrayAndAlloc(hkphysics::hkPhysicsReflectionData* ref_data, hkClassBase* type, std::vector<hkClassInstance*> instances);
		
		static hkIndexedDataBlock* CreatePointerAndAlloc(hkphysics::hkPhysicsReflectionData* ref_data, hkClassBase* type, hkClassInstance* instances);
	};

	class hkClassBoolInstance : public hkClassInstance {
	public:
		std::string c_type = "bool";
		bool value = false;

		hkClassBoolInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
		};

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		hkClassInstance* make_copy() override {
			return new hkClassBoolInstance(*this);
		}
	};

	class hkClassStringInstance : public hkClassInstance {
	public:
		std::string c_type = "std::string";
		std::string value;
		hkreflex::hkIndexedDataBlock* data_block = nullptr; // optional

		hkClassStringInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
		};

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

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

		hkClassIntInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data);

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

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

		hkClassFloatInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data);

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		hkClassInstance* make_copy() override {
			return new hkClassFloatInstance(*this);
		}
	};

	class hkClassPointerInstance : public hkClassInstance {
	public:
		hkClassPointerInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
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

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

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
		hkClassRecordInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
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

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

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
		hkClassArrayInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
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

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

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
				float_array[i] = float_instance->value;
			}
#endif
			return;
		}
	};

	class hkClassBase : public CTranscriptableBase {
	public:
		enum TypeKind
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

		std::string type_name;
		std::string ctype_name;
		std::vector<hkTemplateArgumentBase*> template_args;

		hkClassBase* parent_class;
		Optional optionals;
		uint32_t format;
		TypeKind kind;
		hkClassBase* sub_type;
		uint32_t flags;
		uint32_t version;
		uint32_t size;
		uint32_t alignment;
		TypeFlags type_flags;
		std::vector<hkFieldBase*> fields;
		std::vector<hkInterfaceBase*> interfaces;

		std::vector<hkClassBase*> nested_classes;
		bool is_nested_class = false;
		hkClassBase* parent_nested_class = nullptr;
		std::string nested_type_name;
		std::string nested_parent_type_name;

		uint32_t hash;

		hkIndexedDataBlock* data_block; // None static

		bool _declared = false;
		bool _defined = false;

		virtual std::string to_literal(bool show_class_members = false, bool as_plain_class = false, bool use_mapped_ctype = false);

		std::string to_C_simp_identifier();

		std::string to_C_identifier() override;

		std::string to_C_class_definition(std::vector<hkClassBase*>& ref_types, int indent = 0) override;

		std::string to_C_from_instance() override;

		std::string to_C_to_instance() override;

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


	hkClassInstance* AllocateInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* data);

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

	template<typename ptr_t, typename sub_t>
	requires std::is_pointer_v<ptr_t> && (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t> || hktypes::_is_hk_holder_t<sub_t>)
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
	requires utils::_is_string_t<T>  || hktypes::_is_hk_holder_t<T>
	inline bool hkClassInstance::SetValue(T& container)
	{
		if (utils::_is_string_t<T> && type->kind == hkClassBase::TypeKind::String) {
			auto string_type = dynamic_cast<hkClassStringInstance*>(this);
			string_type->value = *reinterpret_cast<std::string*>(&container);
			return true;
		}
		else if (hktypes::_is_hk_holder_t<T> && type->kind == hkClassBase::TypeKind::Record) {
			reinterpret_cast<hktypes::hkHolderBase*>(&container)->ToInstance(this);
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
	requires utils::_is_string_t<elem_t> || utils::_is_bool_t<elem_t> || utils::_is_float_t<elem_t> || utils::_is_integer_t<elem_t> || hktypes::_is_hk_holder_t<elem_t> || utils::_is_vector_t<elem_t> || hktypes::_is_hk_array_holder_t<elem_t>
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

	template<typename ptr_t, typename sub_t>
	requires std::is_pointer_v<ptr_t> && (utils::_is_string_t<sub_t> || utils::_is_bool_t<sub_t> || utils::_is_float_t<sub_t> || utils::_is_integer_t<sub_t> || hktypes::_is_hk_holder_t<sub_t>)
	inline bool hkClassInstance::SetValue(ptr_t & container) {
		if (type->kind == hkClassBase::TypeKind::Pointer) {
			auto ptr_instance = dynamic_cast<hkClassPointerInstance*>(this);
			if (ptr_instance->ptr_instance->SetValue(*container)) {
				return false;
			}
			return true;
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
	}
}