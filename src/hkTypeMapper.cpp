#include "hkTypeMapper.h"

std::string hktypes::hkTypeMapper::GetCType(hkreflex::hkClassBase* type)
{
	if (type->type_name == "T[N]") {
		std::string ctype_name = "std::array<";
		uint32_t type_value = 0;
		for (auto& arg : type->template_args) {
			if (arg->template_arg_name == "tT") {
				auto type_arg = dynamic_cast<hkreflex::hkTemplateArgumentType*>(arg);

				auto temp_type = type_arg->type;
				ctype_name += GetCType(temp_type);
				break;
			}
		}
		for (auto& arg : type->template_args) {
			if (arg->template_arg_name == "vN") {
				auto type_arg = dynamic_cast<hkreflex::hkTemplateArgumentValue*>(arg);

				ctype_name += ", " + std::to_string(type_arg->value);
				break;
			}
		}
		return ctype_name + ">";
	}
	else if (type->type_name == "hkMatrix4Impl") {
		std::string ret = type->to_literal(false, true);
		return "Eigen::Matrix4f";
	}
	else {
		std::string ret = type->to_literal(false, true);
		return GetCType(ret);
	}
}

std::string hktypes::hkTypeMapper::GetCType(std::string_view type)
{
	auto it = _map.find(type);
	if (it != _map.end()) {
		return it->second.data();
	}
	return type.data();
}

bool hktypes::hkTypeMapper::IsMapped(hkreflex::hkClassBase* type)
{
	if (type->type_name == "T[N]") {
		return true;
	}
	else {
		return _map.find(type->to_literal(false, true)) != _map.end();
	}
}
