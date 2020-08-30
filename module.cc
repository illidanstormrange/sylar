#include "module.h"
#include "env.h"
#include "config.h"
#include "log.h"
#include "util.h"
#include "library.h"
#include <iostream>
#include <sstream>

namespace sylar {

static sylar::ConfigVar<std::string>::ptr g_module_path
	= Config::Lookup("module.path", std::string("module"), "module path");

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");


Module::Module(const std::string& name
		,const std::string& version
		,const std::string& filename) 
	:m_name(name)
	,m_version(version)
	,m_filename(filename)
	,m_id(name + "/" + version) {
}

Module::~Module() {

}

void Module::onBeforeArgsParse(int argc, char** argv) {

}

void Module::onAfterArgsParse(int argc, char** argv) {

}

bool Module::onLoad() {
	return true;
}
bool Module::onUnLoad() {
	return true;

}

bool Module::onConnect(sylar::Stream::ptr stream) {
	return true;

}
bool Module::onDisconnect(sylar::Stream::ptr stream) {
	return true;

}

bool Module::onServerReady() {
	return true;

}

bool Module::onServerUp() {
	return true;

}

std::string Module::statusString() {
	std::stringstream ss;
	ss << "Module name=" << getName()
	   << " version=" << getVersion()
	   << " filename=" << getFilename()
	   << std::endl;
	return ss.str();
}


ModuleManager::ModuleManager() {
}

void ModuleManager::add(Module::ptr m) {
	del(m->getId());
	RWMutexType::WriteLock lock(m_mutex);
	m_modules[m->getId()] = m;
	m_type2Modules[m->getType()][m->getId()] = m;
}

void ModuleManager::del(const std::string& name) {
	Module::ptr module;
	RWMutexType::WriteLock lock(m_mutex);
	auto it = m_modules.find(name);
	if(it == m_modules.end()) {
		return;
	}
	module = it->second;
	m_modules.erase(it);
	m_type2Modules[module->getType()].erase(module->getId());
	if(m_type2Modules[module->getType()].empty()) {
		m_type2Modules.erase(module->getType());
	}
	lock.unlock();
	module->onLoad();
}
void ModuleManager::delAll() {
	RWMutexType::WriteLock lock(m_mutex);
	auto tmp = m_modules;
	lock.unlock();

	for(auto& i : tmp) {
		del(i.first);
	}
}

void ModuleManager::init() {
	auto path = EnvMgr::GetInstence()->getAbsolutePath(g_module_path->getValue());
	std::vector<std::string> files;
	sylar::FSUtil::ListAllFile(files, path, ".so");
	for(auto& i : files) {
		initModule(i);
	}
}

Module::ptr ModuleManager::get(const std::string& name) {
	RWMutexType::ReadLock lock(m_mutex);
	auto it = m_modules.find(name);
	return it == m_modules.end() ? nullptr : it->second;
}

void ModuleManager::onConnect(Stream::ptr stream) {
	std::vector<Module::ptr> ms;
	listAll(ms);

	for(auto& m : ms) {
		m->onConnect(stream);
	}
}

void ModuleManager::onDisconnect(Stream::ptr stream) {
	std::vector<Module::ptr> ms;
	listAll(ms);

	for(auto& m : ms) {
		m->onDisconnect(stream);
	}
}

void ModuleManager::listAll(std::vector<Module::ptr>& ms) {
	RWMutexType::ReadLock lock(m_mutex);
	for(auto& i : m_modules) {
		ms.push_back(i.second);
	}
}
void ModuleManager::listByType(uint32_t type, std::vector<Module::ptr>& ms) {
	RWMutexType::ReadLock lock(m_mutex);
	auto it = m_type2Modules.find(type);
	if(it == m_type2Modules.end()) {
		return;
	}
	for(auto& i : it->second) {
		ms.push_back(i.second);
	}

}
void ModuleManager::foreach(uint32_t type, std::function<void(Module::ptr)> cb) {
	std::vector<Module::ptr> ms;
	listByType(type, ms);
	for(auto& i : ms) {
		cb(i);
	}
}

void ModuleManager::initModule(const std::string& path) {
	Module::ptr m = Library::GetModule(path);
	if(m) {
		add(m);
	}
}


}
