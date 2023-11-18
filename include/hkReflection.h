#pragma once
#include "Common.h"
#include "hkUtils.h"

namespace hkreflection {
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

	class hkClassBase {
	public:
		std::string type_name;
		std::vector<hkTemplateArgumentBase*> template_args;

		virtual std::string to_literal() {
			if(template_args.size() == 0)
				return type_name;

			auto type_literal =  type_name + "<" + template_args[0]->to_literal();
			for (int i = 1; i < template_args.size(); ++i) {
				type_literal += ", " + template_args[i]->to_literal();
			}
			type_literal += ">";
			return type_literal;
		};
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
			return template_arg_name + " = " + std::to_string(unk);
		}
	};


}