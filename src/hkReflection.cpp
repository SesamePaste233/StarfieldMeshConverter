#include "hkReflection.h"

std::string hkreflection::hkClassBase::to_literal(bool show_class_members)
{
	if (template_args.size() == 0)
		return type_name;

	auto type_literal = type_name + "<" + template_args[0]->to_literal();
	for (int i = 1; i < template_args.size(); ++i) {
		type_literal += ", " + template_args[i]->to_literal();
	}
	type_literal += ">";

	if (show_class_members) {
		type_literal += " {\n";
		for (auto& member : fields) {
			type_literal += "\t" + member->to_literal() + "\n";
		}
		type_literal += "}";
	}

	return type_literal;
}

std::string hkreflection::hkFieldBase::to_literal()
{
	return type->to_literal(false) + " " + name;
}
