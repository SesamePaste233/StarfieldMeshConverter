#pragma once
#include "Common.h"
#include "hkUtils.h"
#include "hkTypeMapper.h"
#include "hkPhysics.h"

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
		utils::DataAccessor data;

		hkClassInstance(hkClassBase* type, utils::DataAccessor& data) : type(type), data(data) {};
		virtual size_t Build(hkphysics::hkPhysicsReflectionData* ref_data) = 0;
		virtual std::string dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent = 0) = 0;
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
		uint64_t m_offset = 0;
		uint32_t m_num_instances = 0;

		std::vector<hkClassInstance*> m_instances;

		hkphysics::hkPhysicsReflectionData* ref_data = nullptr;

		bool _built = false;
		bool BuildInstances();

		bool _dumped = false;
		std::string dump_instances(int indent = 0, bool use_mapped_ctype = false, bool suppress_comment = true);

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;
	};

	class hkClassBoolInstance : public hkClassInstance {
	public:
		std::string c_type = "bool";
		bool value = false;

		hkClassBoolInstance(hkClassBase* type, utils::DataAccessor& data) : hkClassInstance(type, data) {
		};

		size_t Build(hkphysics::hkPhysicsReflectionData* ref_data) override;

		std::string dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;
	};

	class hkClassStringInstance : public hkClassInstance {
	public:
		std::string c_type = "std::string";
		std::string value;
		hkreflex::hkIndexedDataBlock* data_block = nullptr; // optional

		hkClassStringInstance(hkClassBase* type, utils::DataAccessor& data) : hkClassInstance(type, data) {
		};

		size_t Build(hkphysics::hkPhysicsReflectionData* ref_data) override;

		std::string dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent = 0) override;

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

		hkClassIntInstance(hkClassBase* type, utils::DataAccessor& data) : hkClassInstance(type, data) {
		};

		size_t Build(hkphysics::hkPhysicsReflectionData* ref_data) override;

		std::string dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;
	};

	class hkClassFloatInstance : public hkClassInstance {
	public:
		std::string c_type = "";
		bool is_big_endian = false;
		size_t byte_length = 0;
		double value = 0;

		hkClassFloatInstance(hkClassBase* type, utils::DataAccessor& data) : hkClassInstance(type, data) {
		};

		size_t Build(hkphysics::hkPhysicsReflectionData* ref_data) override;

		std::string dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;
	};

	class hkClassPointerInstance : public hkClassInstance {
	public:
		std::string c_type = "ptr";
		uint64_t in_document_ptr = NULL;
		hkIndexedDataBlock* data_block = nullptr;

		hkClassPointerInstance(hkClassBase* type, utils::DataAccessor& data) : hkClassInstance(type, data) {
		};

		size_t Build(hkphysics::hkPhysicsReflectionData* ref_data) override;

		std::string dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent = 0) override;

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

		hkClassRecordInstance(hkClassBase* type, utils::DataAccessor& data) : hkClassInstance(type, data) {
		};

		size_t Build(hkphysics::hkPhysicsReflectionData* ref_data) override;

		std::string dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent = 0) override;

		uint64_t Serialize(utils::DataAccessor data, utils::SerializePool& serializer) override;
	};

	class hkClassArrayInstance : public hkClassInstance {
	public:
		std::string c_type = "std::vector";
		std::vector<hkClassInstance*> array_instances;
		hkIndexedDataBlock* data_block = nullptr;
		uint64_t in_document_ptr = NULL;
		uint64_t size_and_flags = 0;

		float float_array[16] = { 0 };

		hkClassArrayInstance(hkClassBase* type, utils::DataAccessor& data) : hkClassInstance(type, data) {
		};

		size_t Build(hkphysics::hkPhysicsReflectionData* ref_data) override;

		std::string dump(hkphysics::hkPhysicsReflectionData* ref_data, int indent = 0) override;

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
				return template_arg_name + "=" + type->to_literal(false, true);
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
				return template_arg_name + "=" + std::to_string(value);
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


	hkClassInstance* AllocateInstance(hkClassBase* type, utils::DataAccessor& data);

}