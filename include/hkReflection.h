#pragma once
#include "Common.h"
#include "hkUtils.h"

namespace hkreflection {
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
		virtual std::string to_literal() = 0;
	};

	class hkFieldBase {
	public:
		enum FieldFlags :uint8_t {
			None = 0,
			NonSerializable = 1,
			Protected = 1 << 1,
			Private = 1 << 2,
			Hidden = 1 << 3,
			Property = 1 << 4,
			Field = 1 << 5,
			CustomSetter = 1 << 6
		};

		hkClassBase* type;
		std::string name;
		uint32_t offset;
		FieldFlags flags;

		virtual std::string to_literal();
	};

	class hkInterfaceBase {
	public:
		hkClassBase* type;
		uint32_t offset;
	};

	class hkClassBase {
	public:
		std::string type_name;
		std::vector<hkTemplateArgumentBase*> template_args;

		hkClassBase* parent_class;
		Optional optionals;
		uint32_t format;
		hkClassBase* sub_type;
		uint32_t flags;
		uint32_t version;
		uint32_t size;
		uint32_t alignment;
		TypeFlags type_flags;
		std::vector<hkFieldBase*> fields;
		std::vector<hkInterfaceBase*> interfaces;

		virtual std::string to_literal(bool show_class_members = false);
	};

	class hkTemplateArgumentType : public hkTemplateArgumentBase {
	public:
		hkClassBase* type;

		ArgumentType GetArgumentType() override {
			return ArgumentType::TYPE;
		}

		std::string to_literal() override {
			return template_arg_name + " = " + type->to_literal();
		}
	};

	class hkTemplateArgumentValue : public hkTemplateArgumentBase {
	public:
		uint32_t value;

		ArgumentType GetArgumentType() override {
			return ArgumentType::VALUE;
		}

		std::string to_literal() override {
			return template_arg_name + " = " + std::to_string(value);
		}
	};

	class hkTemplateArgumentUnk : public hkTemplateArgumentBase {
	public:
		uint32_t unk;

		ArgumentType GetArgumentType() override {
			return ArgumentType::UNK;
		}

		std::string to_literal() override {
			return template_arg_name + "[UNK] = " + std::to_string(unk);
		}
	};


}