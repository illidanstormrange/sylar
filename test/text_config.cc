#include "../config.h"
#include "../log.h"
#include "../env.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

#if 0
sylar::ConfigVar<int>::ptr g_int_value_config =
	sylar::Config::Lookup<int>("system.port", (int)8080, "system port");

sylar::ConfigVar<float>::ptr g_intx_value_config =
	sylar::Config::Lookup<float>("system.port", (int)8080, "system port");

sylar::ConfigVar<float>::ptr g_float_value_config =
	sylar::Config::Lookup<float>("system.value", (float)20.2f, "system value");

sylar::ConfigVar<std::vector<int> >::ptr g_int_vec_value_config =
	sylar::Config::Lookup<std::vector<int> >("system.int_vec", std::vector<int>{1, 2}, "system int vec");

sylar::ConfigVar<std::list<int> >::ptr g_int_list_value_config =
	sylar::Config::Lookup<std::list<int> >("system.int_list", std::list<int>{1, 2}, "system int list");

sylar::ConfigVar<std::set<int> >::ptr g_int_set_value_config =
	sylar::Config::Lookup<std::set<int> >("system.int_set", std::set<int>{10, 20}, "system int set");

sylar::ConfigVar<std::unordered_set<int> >::ptr g_int_uset_value_config =
	sylar::Config::Lookup<std::unordered_set<int> >("system.int_uset", std::unordered_set<int>{10, 20}, "system int uset");

sylar::ConfigVar<std::map<std::string, int> >::ptr g_str_int_map_value_config =
	sylar::Config::Lookup<std::map<std::string, int> >("system.str_int_map", std::map<std::string, int>{{"k", 1}}, "system string int map");

sylar::ConfigVar<std::unordered_map<std::string, int> >::ptr g_str_int_umap_value_config =
	sylar::Config::Lookup<std::unordered_map<std::string, int> >("system.str_int_umap", std::unordered_map<std::string, int>{{"k", 1}}, "system string int umap");

void print_yaml(const YAML::Node& node, int level) {
	if(node.IsScalar()) {
		SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level + 4, ' ')
			<< node.Scalar() << " - " << node.Type() << " - " << level;
	} else if(node.IsMap()) {
		for(auto it = node.begin();
				it != node.end(); ++it) {
			SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level + 4, ' ')
				<< it->first << " - " << it->second.Type() << " - " << level;
			print_yaml(it->second, level + 1);
		}
	} else if(node.IsSequence()) {
		for(size_t i = 0; i < node.size(); ++i) {
			SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << std::string(level + 4, ' ')
				<< i << " - " << node[i].Type() << " - " << level;
			print_yaml(node[i], level + 1);
		}
	}
	
}

void test_yml() {
	YAML::Node root = YAML::LoadFile("/home/illidan/file/cppfile/firstProject/sylar/bin/conf/log.yml");
	print_yaml(root, 0);
	//SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << root;
}
void test_config() {
	//SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_int_value_config->getValue();
	//SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before: " << g_float_value_config->toString();
	
#define XX(value, name, prefix)	 {\
		auto& v = value->getValue(); \
		for(auto& i : v) {  \
			SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name " : " << i; \
		} \
		SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name " yaml: " << value->toString(); \
	}

#define XX_M(value, name, prefix)	 {\
		auto& v = value->getValue(); \
		for(auto& i : v) {  \
			SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name " : " \
			<< " { " << i.first << " - "<< i.second << "}"; \
		} \
		SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << #prefix " " #name " yaml: " << value->toString(); \
	}

	XX(g_int_vec_value_config, int_vec, before);
	XX(g_int_list_value_config, int_list, before);
	XX(g_int_set_value_config, int_set, before);
	XX(g_int_uset_value_config, int_uset, before);
	XX_M(g_str_int_map_value_config, str_int_map, before);
	XX_M(g_str_int_umap_value_config, str_int_umap, before);

	YAML::Node root = YAML::LoadFile("/home/illidan/file/cppfile/firstProject/sylar/bin/conf/log.yml");
	sylar::Config::LoadFromYaml(root);
	
	//SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_int_value_config->getValue();
	//SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after: " << g_float_value_config->toString();

	XX(g_int_vec_value_config, int_vec, after);
	XX(g_int_list_value_config, int_list, after);
	XX(g_int_set_value_config, int_set, after);
	XX(g_int_uset_value_config, int_uset, after);
	XX_M(g_str_int_map_value_config, str_int_map, after);
	XX_M(g_str_int_umap_value_config, str_int_umap, after);
}
#endif
class Person {
public:
	Person() {}
	std::string m_name = " ";
	int m_age = 0;
	bool m_sex = true;

	std::string toString() const {
		std::stringstream ss;
		ss << "[Person name : " << m_name 
		   << "age : " << m_age 
		   << "sex : " << m_sex
		   << "]";
		return ss.str();
	}

	bool operator==(const Person& oth) const  {
		return oth.m_name == m_name 
			&& oth.m_sex == m_sex
			&& oth.m_age == m_age;
	}
};

namespace sylar {

template<>
class LexicalCast<std::string, Person>  {
public :
	Person operator()(const std::string& str) {
		YAML::Node node = YAML::Load(str);
		Person p;
		p.m_name = node["name"].as<std::string>();
		p.m_sex = node["sex"].as<bool>();
		p.m_age = node["age"].as<int>();
		return p;
	}
};

template<>
class LexicalCast<Person, std::string> {
public:
	std::string operator()(const Person& p) {
		YAML::Node node;
		node["name"] = p.m_name;
		node["age"] = p.m_age;
		node["sex"] = p.m_sex;
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};
}

sylar::ConfigVar<Person>::ptr g_person = 
	sylar::Config::Lookup("class.person", Person(), "class person");

void test_class() {
	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "before " << g_person->getValue().toString() 
		<< " - " << g_person->toString();
	
	g_person->addListener([](const Person& old_value, const Person& new_value){
			SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "old_value = " << old_value.toString() << " - "
			<< "new value = " << new_value.toString();
			});

	YAML::Node root = YAML::LoadFile("/home/illidan/file/cppfile/firstProject/sylar/bin/conf/log.yml");
	sylar::Config::LoadFromYaml(root);

	SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "after " << g_person->getValue().toString() 
		<< " - " << g_person->toString();

}

void test_log() {
	static sylar::Logger::ptr system_log = SYLAR_LOG_NAME("system");
	SYLAR_LOG_INFO(system_log) << "hello system "; 
	std::cout << sylar::LogMgr::GetInstence()->toYamlString() << std::endl;
	YAML::Node root = YAML::LoadFile("/home/illidan/file/cppfile/firstProject/sylar/bin/conf/log.yml");
	sylar::Config::LoadFromYaml(root);
	std::cout << sylar::LogMgr::GetInstence()->toYamlString() << std::endl;

	SYLAR_LOG_INFO(system_log) << "hello system "; 
	system_log->setFormatter("%d - %m%n");
	SYLAR_LOG_INFO(system_log) << "hello system "; 
}

void test_dir() {
	sylar::Config::LoadFromConfDir("../bin/conf", true);
}

int main() 
{	
	//test_yml();
	//test_config();
	//test_class();
	//test_log();
	test_dir();
	std::cout << "-----" << std::endl;
	test_dir();
	return 0;
}
