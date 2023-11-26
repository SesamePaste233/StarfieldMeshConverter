#pragma once
#include "Common.h"
#include "hkUtils.h"
#include "hkTypeMapper.h"
#include "hkPhysics.h"

namespace hkphysics {
	class hkPhysicsReflectionData;
}

namespace hktypes {
	class hkHolderBase;

	template<typename T>
	concept _is_hk_holder_t = std::is_base_of<hkHolderBase, T>::value;
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
	};

	class hkFieldBase {
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

		template<typename T>
		requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
		bool GetValue(T & container);

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
			for (auto instance : m_instances) {
				delete instance;
			}
		}

		hkClassBase* m_data_type = nullptr;
		Type m_block_type = Type::None;
		uint32_t m_offset = 0;
		uint32_t m_num_instances = 0;

		std::vector<hkClassInstance*> m_instances;

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
	};

	class hkClassPointerInstance : public hkClassInstance {
	public:
		std::string c_type = "ptr";
		uint64_t in_document_ptr = NULL;
		hkIndexedDataBlock* data_block = nullptr;

		hkClassInstance* ptr_instance = nullptr;

		hkClassPointerInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
		};

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;
	};

	class hkClassRecordInstance : public hkClassInstance {
	public:
		struct Record {
			std::string field_name = "";
			hkClassInstance* instance = nullptr;
			hkFieldBase* field = nullptr;
		};

		std::string c_type = "class";

		std::vector<Record> record_instances;

		hkClassRecordInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
		};

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;

		hkClassInstance* GetParentInstance();

		hkClassInstance* GetInstanceByFieldName(const std::string& field_name);

		std::string GetStringByFieldName(const std::string& field_name);

		int64_t GetIntByFieldName(const std::string& field_name);

		uint64_t GetUIntByFieldName(const std::string& field_name);

		double GetFloatByFieldName(const std::string& field_name);

		bool GetBoolByFieldName(const std::string& field_name);

		template<typename T>
		requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
		std::vector<T> GetArrayByFieldName(const std::string& field_name);
	};

	class hkClassArrayInstance : public hkClassInstance {
	public:
		std::string c_type = "std::vector";
		std::vector<hkClassInstance*> array_instances;
		hkIndexedDataBlock* data_block = nullptr;
		uint64_t in_document_ptr = NULL;
		uint64_t size_and_flags = 0;

		float float_array[16] = { 0 };

		hkClassArrayInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* ref_data) : hkClassInstance(type, ref_data) {
		};

		size_t Build(utils::DataAccessor& data) override;

		std::string dump(int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;
	};

	class hkClassBase {
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

		uint32_t hash;

		hkIndexedDataBlock* data_block; // None static

		bool _declared = false;
		bool _defined = false;

		virtual std::string to_literal(bool show_class_members = false, bool as_plain_class = false, bool use_mapped_ctype = false);

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
	};


	hkClassInstance* AllocateInstance(hkClassBase* type, hkphysics::hkPhysicsReflectionData* data);

	template<typename T>
	requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
	inline bool hkClassInstance::GetValue(T& container)
	{
		if (utils::_is_string_t<T> && type->kind == hkClassBase::TypeKind::String) {
			auto string_type = dynamic_cast<hkClassStringInstance*>(this);
			container = *reinterpret_cast<T*>(&string_type->value);
			return true;
		}
		else if (utils::_is_bool_t<T> && type->kind == hkClassBase::TypeKind::Bool) {
			auto bool_type = dynamic_cast<hkClassBoolInstance*>(this);
			container = *reinterpret_cast<T*>(&bool_type->value);
			return true;
		}
		else if (utils::_is_float_t<T> && type->kind == hkClassBase::TypeKind::Float) {
			auto float_type = dynamic_cast<hkClassFloatInstance*>(this);
			if (std::is_same_v<T, float>) {
				float v = float(float_type->value);
				container = *reinterpret_cast<T*>(&v);
				return true;
			}else {
				container = *reinterpret_cast<T*>(&float_type->value);
				return true;
			}
		}
		else if (utils::_is_integer_t<T> && type->kind == hkClassBase::TypeKind::Int) {
			auto int_type = dynamic_cast<hkClassIntInstance*>(this);
			if (utils::_signed_integer_t<T> && int_type->is_signed) {
				container = *reinterpret_cast<T*>(&int_type->svalue);
				return true;
			}
			else if (utils::_unsigned_integer_t<T> && !int_type->is_signed) {
				container = *reinterpret_cast<T*>(&int_type->value);
				return true;
			}
		}
		else if (hktypes::_is_hk_holder_t<T> && type->kind == hkClassBase::TypeKind::Record) {
			reinterpret_cast<hktypes::hkHolderBase*>(&container)->FromInstance(this);
			return true;
		}
		return false;
	}

	template<typename T>
	requires utils::_is_string_t<T> || utils::_is_bool_t<T> || utils::_is_float_t<T> || utils::_is_integer_t<T> || hktypes::_is_hk_holder_t<T>
	inline std::vector<T> hkClassRecordInstance::GetArrayByFieldName(const std::string& field_name)
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
			}
		}
		return ret;
	}

}