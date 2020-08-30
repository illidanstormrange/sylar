#include "application.h"
#include "config.h"
#include "env.h"
#include "log.h"
#include "daemon.h"
#include "module.h"
#include "worker.h"
#include "http/ws_server.h"
#include <unistd.h>


namespace sylar {

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

static sylar::ConfigVar<std::string>::ptr g_server_work_path = 
	sylar::Config::Lookup("server.work_path"
			,std::string("~/file/cppfile/firstProject/new/sylar/build")
			,"server work path");

static sylar::ConfigVar<std::string>::ptr g_server_pid_file = 
	sylar::Config::Lookup("server.pid_file"
			,std::string("sylar.pid")
			,"server pid file");

static sylar::ConfigVar<std::vector<TcpServerConf> >::ptr g_servers_conf
	= sylar::Config::Lookup("servers", std::vector<TcpServerConf>(), "http server config");

Application* Application::s_instance = nullptr;

Application::Application() {
	s_instance = this;
}

bool Application::init(int argc, char** argv) {
	m_argc = argc;
	m_argv = argv;
	sylar::EnvMgr::GetInstence()->addHelp("s", "start with the rerminal");
	sylar::EnvMgr::GetInstence()->addHelp("d", "run as daemon");
	sylar::EnvMgr::GetInstence()->addHelp("c", "conf path default: ../bin/conf");
	sylar::EnvMgr::GetInstence()->addHelp("p", "print help");

	if(!sylar::EnvMgr::GetInstence()->init(argc, argv)) {
		sylar::EnvMgr::GetInstence()->printHelp();
		return false;
	}

	if(sylar::EnvMgr::GetInstence()->has("p")) {
		sylar::EnvMgr::GetInstence()->printHelp();
		return false;
	}

	ModuleMgr::GetInstence()->init();
	std::vector<Module::ptr> modules;
	ModuleMgr::GetInstence()->listAll(modules);

	for(auto i: modules) {
		i->onBeforeArgsParse(argc, argv);
	}


	for(auto i: modules) {
		i->onBeforeArgsParse(argc, argv);
	}
	modules.clear();

	int run_type = 0;
	if(sylar::EnvMgr::GetInstence()->has("s")) {
		run_type = 1;
	}
	if(sylar::EnvMgr::GetInstence()->has("d")) {
		run_type = 2;
	}
	
	if(run_type == 0) {
		sylar::EnvMgr::GetInstence()->printHelp();
		return false;
	}

	std::string pidfile = g_server_work_path->getValue()
								+ "/" + g_server_pid_file->getValue();
	if(sylar::FSUtil::IsRunningPidfile(pidfile)) {
		SYLAR_LOG_ERROR(g_logger) << "server is running:" << pidfile;
		return false;
	}

	if(!sylar::FSUtil::Mkdir(g_server_work_path->getValue())) {
		SYLAR_LOG_FATAL(g_logger) << "create work path [" << g_server_work_path->getValue()
			<< " errno=" << errno << " errstr=" << strerror(errno);
		return false;
	}

	return true;
}

bool Application::run() {
	bool is_daemon = sylar::EnvMgr::GetInstence()->has("d");
	return start_daemon(m_argc, m_argv
			,std::bind(&Application::main, this, std::placeholders::_1, std::placeholders::_2), is_daemon);
}

int Application::main(int argc, char** argv) {
	std::string conf_path = sylar::EnvMgr::GetInstence()->getConfigPath();
	sylar::Config::LoadFromConfDir(conf_path, true);
	{
		std::string pidfile = g_server_work_path->getValue()
			+ "/" + g_server_pid_file->getValue();
		std::ofstream ofs(pidfile);
		if(!ofs) {
			SYLAR_LOG_ERROR(g_logger) << "open pidfile " << pidfile << " failed";
			return false;
		}
		ofs << getpid();
	}

	m_mainIOManager.reset(new sylar::IOManager(1, true, "main"));
	m_mainIOManager->scheduler(std::bind(&Application::run_fiber, this));
	m_mainIOManager->addTimer(2000, [](){
			
	}, true);
	m_mainIOManager->stop();
	return 0;
}


int Application::run_fiber() {
	std::vector<Module::ptr> modules;
	ModuleMgr::GetInstence()->listAll(modules);
	bool has_error = false;
	for(auto& i : modules) {
		if(!i->onLoad()) {
			SYLAR_LOG_ERROR(g_logger) << "module name="
				<< i->getName() << " version=" << i->getVersion()
				<< " filename=" << i->getFilename();
			has_error = true;
		}
	}
	if(has_error) {
		_exit(0);
	}

	sylar::WorkerMgr::GetInstence()->init();

	auto http_confs = g_servers_conf->getValue();
	std::vector<TcpServer::ptr> svrs;
	for(auto& i : http_confs) {
		SYLAR_LOG_INFO(g_logger) << LexicalCast<TcpServerConf, std::string>()(i);

		std::vector<Address::ptr> address;
		for(auto& a : i.address) {
			size_t pos = a.find(":");
			if(pos == std::string::npos) {
				//SYLAR_LOG_ERROR(g_logger) << "invalid address: " << a;
				address.push_back(UnixAddress::ptr(new UnixAddress(a)));
				continue;
			}
			int32_t port = atoi(a.substr(pos + 1).c_str());
			auto addr = sylar::IPAddress::Create(a.substr(0, pos).c_str(), port);
			if(addr) {
				address.push_back(addr);
				continue;
			}
			std::vector<std::pair<Address::ptr, uint32_t> > result;
			if(sylar::Address::GetInterfaceAddress(result, a.substr(0, pos)) ) {
				for(auto& x : result) {
					auto ipaddr = std::dynamic_pointer_cast<IPAddress>(x.first);
					if(ipaddr) {
						ipaddr->setPort(atoi(a.substr(pos + 1).c_str()));
					}
					address.push_back(ipaddr);
				}
				continue;
			}
			auto aaddr = sylar::Address::LookUpAny(a);
			if(aaddr) {
				address.push_back(aaddr);
				continue;
			}
			SYLAR_LOG_ERROR(g_logger) << "invalid address: " << a;
			_exit(0);
		}
		IOManager* accept_worker = sylar::IOManager::GetThis();
		IOManager* io_worker = sylar::IOManager::GetThis();
		IOManager* process_worker = sylar::IOManager::GetThis();
		if(!i.accept_worker.empty()) {
			accept_worker = sylar::WorkerMgr::GetInstence()->getAsIOManager(i.accept_worker).get();
			if(!accept_worker) {
				SYLAR_LOG_ERROR(g_logger) << "accept_worker: " << i.accept_worker 
					<< " not exists";
				_exit(0);
			}
		}
		if(!i.io_worker.empty()) {
			io_worker = sylar::WorkerMgr::GetInstence()->getAsIOManager(i.io_worker).get();
			if(!io_worker) {
				SYLAR_LOG_ERROR(g_logger) << "io_worker: " << i.io_worker 
					<< " not exists";
				_exit(0);
			}
		}
		if(!i.process_worker.empty()) {
			process_worker = sylar::WorkerMgr::GetInstence()->getAsIOManager(i.io_worker).get();
			if(!process_worker) {
				SYLAR_LOG_ERROR(g_logger) << "process_worker: " << i.process_worker 
					<< " not exists";
				_exit(0);
			}
		}
		TcpServer::ptr server;
		if(i.type == "http") {
			server.reset(new sylar::http::HttpServer(i.keepalive,
						process_worker, io_worker, accept_worker));
		} else if(i.type == "ws"){
			server.reset(new sylar::http::WSServer(
						process_worker, io_worker, accept_worker));
		} else {
		
			SYLAR_LOG_ERROR(g_logger) << "invalid server type = " << i.type
				<< LexicalCast<TcpServerConf, std::string>()(i);
			_exit(0);
		}
		if(!i.name.empty()) {
			server->setName(i.name);
		}

		std::vector<Address::ptr> fails;
		if(!server->bind(address, fails)) {
			for(auto& x : fails) {
				SYLAR_LOG_ERROR(g_logger) << "bind address fail:" << *x;
			}
			_exit(0);
		}
		server->setName(i.name);
		server->start();
		m_servers[i.type].push_back(server);
		svrs.push_back(server);
	}

	for(auto& i : svrs) {
		i->start();
	}
	return 0;	
}
bool Application::getServer(const std::string& type, std::vector<TcpServer::ptr>& svrs) {
	auto it = m_servers.find(type);
	if(it == m_servers.end()) {
		return false;
	}
	svrs = it->second;
	return true;
	
}
void Application::listAllServer(std::map<std::string, std::vector<TcpServer::ptr> >& servers) {
	servers = m_servers;
}
}
