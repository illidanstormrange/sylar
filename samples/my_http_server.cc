#include "../http/http_server.h"
#include "../log.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run() {
	g_logger->setLevel(sylar::LogLevel::Level::INFO);
	sylar::Address::ptr addr = sylar::Address::LookUpAnyIPAddress("0.0.0.0:8020");
	if(!addr) {
		SYLAR_LOG_ERROR(g_logger) << "get address error";
		return;
	}

	sylar::http::HttpServer::ptr http_server(new sylar::http::HttpServer);
	while(!http_server->bind(addr)) {
		SYLAR_LOG_ERROR(g_logger) << "bind" << *addr << " fail";
		sleep(1);
	}


	http_server->start();
}

int main()
{
	sylar::IOManager iom(1);
	iom.scheduler(run);
	return 0;
}
