#include "config.h"
#include <list>
#include <map>

namespace sylar {
//	Config::ConfigVarMap Config::s_datas;
ConfigVarBase::ptr Config::LookupBase(const std::string& name) {
	RWMutexType::ReadLock lock(GetMutex());
	auto it = GetDatas().find(name);
	return it == GetDatas().end() ? nullptr : it->second;
	
}

static void ListAllMembers(const std::string& prefix,
		const YAML::Node& node,
		std::list<std::pair<std::string, const YAML::Node> >& output) {
	if(prefix.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_.0123456789")
			!= std::string::npos) {
		SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Config invaild name " << prefix << " - " << node;
		return;
	}
	if(node.IsScalar()) {
	}
	output.push_back(std::make_pair(prefix, node));
	if(node.IsMap()) {
		for(auto it = node.begin();
				it != node.end(); ++it) {
			ListAllMembers(prefix.empty() ? it->first.Scalar() : prefix + '.' + it->first.Scalar(),
					it->second, output);
		}
	}
}
void Config::LoadFromYaml(const YAML::Node& root) {
	std::list<std::pair<std::string, const YAML::Node> > all_nodes;
	ListAllMembers("", root, all_nodes);
	for(auto& it : all_nodes) {
		std::string key = it.first;
		if(key.empty())
			continue;
		std::transform(key.begin(), key.end(), key.begin(), ::tolower);
		ConfigVarBase::ptr var = LookupBase(key);
		if(var) {
			if(it.second.IsScalar()){
				var->fromString(it.second.Scalar());
			}
			else {
				std::stringstream ss;
				ss << it.second;
				var->fromString(ss.str());
			}
		}
	}
}
void Config::Visit(std::function<void(ConfigVarBase::ptr)>& cb) {
	RWMutexType::ReadLock lock(GetMutex());
	ConfigVarMap& m = GetDatas();
	for(auto it = m.begin();
			it != m.end(); ++it) {
		cb(it->second);
	}
} 

}
