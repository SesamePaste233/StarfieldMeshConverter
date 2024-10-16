#include "Generated\hclStateDependencyGraph.h"

#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"
#include "Generated\.h"

bool hktypes::hclStateDependencyGraph::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStateDependencyGraph::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStateDependencyGraph") {
		std::cout << "hclStateDependencyGraph::FromInstance: Expecting hclStateDependencyGraph but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::FromInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("branches")->GetValue(branches);
	class_instance->GetInstanceByFieldName("rootBranchIds")->GetValue(rootBranchIds);
	class_instance->GetInstanceByFieldName("children")->GetValue(children);
	class_instance->GetInstanceByFieldName("parents")->GetValue(parents);
	class_instance->GetInstanceByFieldName("multiThreadable")->GetValue(multiThreadable);
	return true;
}

bool hktypes::hclStateDependencyGraph::Branch::FromInstance(const hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<const hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStateDependencyGraph::Branch::FromInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStateDependencyGraph::Branch") {
		std::cout << "hclStateDependencyGraph::Branch::FromInstance: Expecting hclStateDependencyGraph::Branch but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("branchId")->GetValue(branchId);
	class_instance->GetInstanceByFieldName("stateOperatorIndices")->GetValue(stateOperatorIndices);
	class_instance->GetInstanceByFieldName("parentBranches")->GetValue(parentBranches);
	class_instance->GetInstanceByFieldName("childBranches")->GetValue(childBranches);
	return true;
}

bool hktypes::hclStateDependencyGraph::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStateDependencyGraph::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStateDependencyGraph") {
		std::cout << "hclStateDependencyGraph::ToInstance: Expecting hclStateDependencyGraph but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	hkReferencedObject::ToInstance(class_instance->GetInstanceByFieldName("class_parent"));
	class_instance->GetInstanceByFieldName("branches")->SetValue(branches);
	class_instance->GetInstanceByFieldName("rootBranchIds")->SetValue(rootBranchIds);
	class_instance->GetInstanceByFieldName("children")->SetValue(children);
	class_instance->GetInstanceByFieldName("parents")->SetValue(parents);
	class_instance->GetInstanceByFieldName("multiThreadable")->SetValue(multiThreadable);
	return true;
}

bool hktypes::hclStateDependencyGraph::Branch::ToInstance(hkreflex::hkClassInstance* instance) {
	auto class_instance = dynamic_cast<hkreflex::hkClassRecordInstance*>(instance);

#ifndef NO_HK_TYPENAME_CHECK
	if (!class_instance) {
		std::cout << "hclStateDependencyGraph::Branch::ToInstance: hkClassRecordInstance is nullptr!" << std::endl;
		throw;
	}
	if (class_instance->type->type_name != "hclStateDependencyGraph::Branch") {
		std::cout << "hclStateDependencyGraph::Branch::ToInstance: Expecting hclStateDependencyGraph::Branch but got " << class_instance->type->type_name << std::endl;
		return false;
	}
#endif // NO_HK_TYPENAME_CHECK

	class_instance->GetInstanceByFieldName("branchId")->SetValue(branchId);
	class_instance->GetInstanceByFieldName("stateOperatorIndices")->SetValue(stateOperatorIndices);
	class_instance->GetInstanceByFieldName("parentBranches")->SetValue(parentBranches);
	class_instance->GetInstanceByFieldName("childBranches")->SetValue(childBranches);
	return true;
}

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStateDependencyGraph::GetTemplateArgs() { return {
}; };

inline std::vector<std::pair<std::string, std::string>> hktypes::hclStateDependencyGraph::Branch::GetTemplateArgs() { return {
}; };

