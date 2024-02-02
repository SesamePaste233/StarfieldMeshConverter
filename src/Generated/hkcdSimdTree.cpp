#include "Generated\hkcdSimdTree.h"

#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hkcdSimdTree::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdSimdTree") {
		std::cout << "hkcdSimdTree::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("nodes")->GetValue(nodes);
	class_instance->GetInstanceByFieldName("isCompact")->GetValue(isCompact);
	return true;
}

bool hktypes::hkcdSimdTree::Node::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdSimdTree::Node") {
		std::cout << "hkcdSimdTree::Node::FromInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkcdFourAabb::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("data")->GetValue(data);
	class_instance->GetInstanceByFieldName("isLeaf")->GetValue(isLeaf);
	class_instance->GetInstanceByFieldName("isActive")->GetValue(isActive);
	return true;
}

bool hktypes::hkcdSimdTree::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdSimdTree") {
		std::cout << "hkcdSimdTree::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("nodes")->SetValue(nodes);
	class_instance->GetInstanceByFieldName("isCompact")->SetValue(isCompact);
	return true;
}

bool hktypes::hkcdSimdTree::Node::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (class_instance && class_instance->type->type_name != "hkcdSimdTree::Node") {
		std::cout << "hkcdSimdTree::Node::ToInstance: Wrong type!" << std::endl;
		throw;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkcdFourAabb::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("data")->SetValue(data);
	class_instance->GetInstanceByFieldName("isLeaf")->SetValue(isLeaf);
	class_instance->GetInstanceByFieldName("isActive")->SetValue(isActive);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hkcdSimdTree::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hkcdSimdTree::Node::GetTemplateArgs() { return {
}; };

