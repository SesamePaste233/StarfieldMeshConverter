#include "hkReflection.h"

std::string hkreflection::hkClassBase::to_literal(bool show_class_members, bool as_plain_class)
{
	if (!_declared) {
		return "[Undeclared]";
	}

	std::string type_literal = "";

	if (as_plain_class) {
		type_literal = type_name;
		if (template_args.size() != 0) {
			type_literal += "<" + template_args[0]->to_literal();
			for (int i = 1; i < template_args.size(); ++i) {
				type_literal += ", " + template_args[i]->to_literal();
			}
			type_literal += ">";
		}
		return type_literal;
	}

	if (template_args.size() != 0) {
		type_literal += "template<";
		type_literal += template_args[0]->to_literal();
		for (int i = 1; i < template_args.size(); ++i) {
			type_literal += ", " + template_args[i]->to_literal();
		}
		type_literal += ">\n";
	}

	type_literal += "class " + type_name;

	if (parent_class) {
		type_literal += " : " + parent_class->to_literal(false, true);
	}

	if (show_class_members) {
		if (!_defined) {
			type_literal += " {\n";
			type_literal += " [Undefined]\n";
			type_literal += "}";
		}
		else {
			type_literal += " {\n";
			for (auto& member : fields) {
				type_literal += "\t" + member->to_literal() + "\n";
			}
			type_literal += "}";
		}
	}

	return type_literal;
}

std::string hkreflection::hkFieldBase::to_literal()
{
	return type->to_literal(false, true) + " " + name + "\t// Offset: " + std::to_string(this->offset) + " Unk: " + std::to_string(this->unk_value);
}
