#ifndef __SYLAR_CONFIG_H__
#define __SYLAR_CONFIG_H__

#include <memory.h>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <string>
#include <list>
#include <map>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <yaml-cpp/yaml.h>
#include "log.h"
#include "thread.h"
#include "util.h"

namespace sylar{

class ConfigVarBase {
public:
	typedef std::shared_ptr<ConfigVarBase> ptr;
	ConfigVarBase(const std::string name, const std::string& description)
		:m_name(name)
		 ,m_description(description) {
		 }
	virtual ~ConfigVarBase() {}
	const std::string& GetName() { return m_name; }
	const std::string& GetDescription() { return m_description; }

	virtual std::string toString() = 0;
	virtual bool fromString(const std::string& val) = 0;
	virtual std::string getTypeid() const = 0;
protected:
	std::string m_name;
	std::string m_description;
};

//F from_type  T to_type
template <class F, class T>
class LexicalCast {
public:
	T operator()(const F& v) {
		return boost::lexical_cast<T>(v);
	}
};

template<class T>
class LexicalCast<std::string, std::vector<T> > {
public:
	std::vector<T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::vector<T> vec;
		std::stringstream ss;
		for(size_t i = 0; i < node.size(); ++i) {
			ss.str("");
			ss << node[i];
			vec.push_back(LexicalCast<std::string, T>()(ss.str()));
		}
		return vec;
	}
};

template<class T>
class LexicalCast<std::vector<T>, std::string> {
public:
	std::string operator()(const std::vector<T>& vec) {
		YAML::Node node;
		for(auto& i : vec) {
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T>
class LexicalCast<std::string, std::list<T> > {
public:
	std::list<T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::list<T> vec;
		std::stringstream ss;
		for(size_t i = 0; i < node.size(); ++i) {
			ss.str("");
			ss << node[i];
			vec.push_back(LexicalCast<std::string, T>()(ss.str()));
		}
		return vec;
	}
};

template<class T>
class LexicalCast<std::list<T>, std::string> {
public:
	std::string operator()(const std::list<T>& vec) {
		YAML::Node node;
		for(auto& i : vec) {
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T>
class LexicalCast<std::string, std::set<T> > {
public:
	std::set<T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::set<T> vec;
		std::stringstream ss;
		for(size_t i = 0; i < node.size(); ++i) {
			ss.str("");
			ss << node[i];
			vec.insert(LexicalCast<std::string, T>()(ss.str()));
		}
		return vec;
	}
};

template<class T>
class LexicalCast<std::set<T>, std::string> {
public:
	std::string operator()(const std::set<T>& vec) {
		YAML::Node node;
		for(auto& i : vec) {
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T>
class LexicalCast<std::string, std::unordered_set<T> > {
public:
	std::unordered_set<T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::unordered_set<T> vec;
		std::stringstream ss;
		for(size_t i = 0; i < node.size(); ++i) {
			ss.str("");
			ss << node[i];
			vec.insert(LexicalCast<std::string, T>()(ss.str()));
		}
		return vec;
	}
};

template<class T>
class LexicalCast<std::unordered_set<T>, std::string> {
public:
	std::string operator()(const std::unordered_set<T>& vec) {
		YAML::Node node;
		for(auto& i : vec) {
			node.push_back(YAML::Load(LexicalCast<T, std::string>()(i)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T>
class LexicalCast<std::string, std::map<std::string, T> > {
public:
	std::map<std::string, T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::map<std::string, T> vec;
		std::stringstream ss;
		for(auto it = node.begin();
				it != node.end(); ++it) {
			ss.str("");
			ss << it->second;
			vec.insert(std::make_pair(it->first.Scalar(), 
					LexicalCast<std::string, T>()(ss.str())));
		}
		return vec;
	}
};

template<class T>
class LexicalCast<std::map<std::string, T>, std::string> {
public:
	std::string operator()(const std::map<std::string, T>& vec) {
		YAML::Node node;
		for(auto& i : vec) {
			node[i.first] = (YAML::Load(LexicalCast<T, std::string>()(i.second)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T>
class LexicalCast<std::string, std::unordered_map<std::string, T> > {
public:
	std::unordered_map<std::string, T> operator()(const std::string& v) {
		YAML::Node node = YAML::Load(v);
		typename std::unordered_map<std::string, T> vec;
		std::stringstream ss;
		for(auto it = node.begin();
				it != node.end(); ++it) {
			ss.str("");
			ss << it->second;
			vec.insert(std::make_pair(it->first.Scalar(), 
					LexicalCast<std::string, T>()(ss.str())));
		}
		return vec;
	}
};

template<class T>
class LexicalCast<std::unordered_map<std::string, T>, std::string> {
public:
	std::string operator()(const std::unordered_map<std::string, T>& vec) {
		YAML::Node node;
		for(auto& i : vec) {
			node[i.first] = (YAML::Load(LexicalCast<T, std::string>()(i.second)));
		}
		std::stringstream ss;
		ss << node;
		return ss.str();
	}
};

template<class T, class FromStr = LexicalCast<std::string, T>, 
		class ToStr = LexicalCast<T, std::string> >
class ConfigVar : public ConfigVarBase {
public:
	typedef RWMutex RWMutexType;
	typedef std::shared_ptr<ConfigVar> ptr;
	typedef std::function<void (const T& old_value, const T& new_value)> on_change_cb;
	ConfigVar(const std::string& name, 
			const T& default_value, const std::string& description = "")
		:ConfigVarBase(name, description)
		,m_val(default_value) {}

	std::string toString() override {
		try {
			//return boost::lexical_cast<std::string>(m_val); 
			RWMutexType::ReadLock lock(m_mutex);
			return ToStr()(m_val);
		}catch(std::exception e) {
			SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception" << e.what()
				<< " conver: " << typeid(m_val).name() << " to string ";
		}
		return "";
	}

	bool fromString(const std::string& val) override {
		try {
			//m_val = boost::lexical_cast<T>(val);
			setValue(FromStr()(val));
		}catch(std::exception e) {
			SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ConfigVar::toString exception" << e.what()
				<< " conver: " << typeid(m_val).name();
		}
		return false;
	}
	std::string getTypeid() const override { return typeid(T).name(); }

	uint64_t addListener(on_change_cb cb) {
		static uint64_t s_fun_id = 0;
		RWMutexType::WriteLock lock(m_mutex);
		++s_fun_id;
		m_cbs[s_fun_id] = cb;
		return s_fun_id;
	}
	
	void delListener(uint64_t type) {
		RWMutexType::WriteLock lock(m_mutex);
		m_cbs.earse(type);
	}

	on_change_cb getListener(uint64_t type) {
		RWMutexType::ReadLock lock(m_mutex);
		auto it = m_cbs.find(type);
		return it == m_cbs.end() ? nullptr : it->second;
	}
	void clearListener() {
		RWMutexType::WriteLock lock(m_mutex);
		m_cbs.clear();
	}

	const T getValue() { 
		RWMutexType::ReadLock lock(m_mutex);
		return m_val;
	}
	void setValue(const T& v) {
		{
			RWMutexType::ReadLock lock(m_mutex);
			if(v == m_val) {
				return;
			}
			for(auto i : m_cbs) {
				i.second(m_val, v);
			}
		}
		RWMutexType::WriteLock lock(m_mutex);
		m_val = v;
	}
private:
	T m_val;
	RWMutexType m_mutex;
	std::map<uint64_t, on_change_cb> m_cbs;

};

class Config 
{
public:
	typedef std::unordered_map<std::string, ConfigVarBase::ptr> ConfigVarMap;
	typedef RWMutex RWMutexType;
	template<class T>
		static typename ConfigVar<T>::ptr Lookup(const std::string& name,
				const T& default_value, const std::string& description = "") {
			RWMutexType::ReadLock lock(GetMutex());
			auto it = GetDatas().find(name);
			if(it != GetDatas().end()) {
				auto tmp = std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
				if(tmp) {
					SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "Lookup name = " << name << " Exists!";
				} else {
					SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name = " << name << " Exists but type not "
						<< typeid(T).name() << " real type = " << it->second->getTypeid();
				}
			}
			if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVXYZ._012345678")
					!= std::string::npos) {
				SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "Lookup name Invalid " << name;
				throw std::invalid_argument(name);
			}
			typename ConfigVar<T>::ptr v(new ConfigVar<T>(name, default_value, description));
			GetDatas()[name] = v;
			//s_datas.insert(std::pair<std::string, ConfigVarBase::ptr>(name, v));
			return v;
		}
	template<class T>
		static typename ConfigVar<T>::ptr Lookup(const std::string& name) {
			RWMutexType::ReadLock lock(GetMutex());
			auto it = GetDatas().find(name);
			if(it == GetDatas().end()) {
				return nullptr;
			}
			return std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
		}

	static void LoadFromYaml(const YAML::Node& root);

	static void LoadFromConfDir(const std::string& path, bool force);

	static ConfigVarBase::ptr LookupBase(const std::string& name);

	static void Visit(std::function<void(ConfigVarBase::ptr)>& cb); 
private:
	static RWMutexType& GetMutex() {
		static RWMutexType m_mutex;
		return m_mutex;
	}
	static ConfigVarMap& GetDatas (){
		static ConfigVarMap s_datas;
		return s_datas;
	}
};
}

#endif


