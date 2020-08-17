#include "../http/http_server.h"
#include "../log.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run() {
	sylar::http::HttpServer::ptr server(new sylar::http::HttpServer);
	sylar::Address::ptr addr = sylar::Address::LookUpAnyIPAddress("0.0.0.0:8020");
	while(!server->bind(addr)) {
		sleep(2);
	}
	server->start();
}


int main()
{
	sylar::IOManager iom(2);
	iom.scheduler(run);
	return 0;
}

