#include "../tcp_server.h"
#include "../iomanager.h"
#include "../log.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void run()
{
	auto addr = sylar::Address::LookUpAny("0.0.0.0:8011");
	auto addr2 = sylar::UnixAddress::ptr(new sylar::UnixAddress("/tmp/unix_addr"));
	SYLAR_LOG_INFO(g_logger) << *addr << " - " << *addr2;
	std::vector<sylar::Address::ptr> addrs;
	addrs.push_back(addr);
	addrs.push_back(addr2);

	sylar::TcpServer::ptr tcp_server(new sylar::TcpServer);
	std::vector<sylar::Address::ptr> fails;
	while(!tcp_server->bind(addrs, fails)) {
		sleep(2);
	}
	tcp_server->start();
}

int main()
{
	sylar::IOManager iom(2);
	iom.scheduler(run);
	return 0;
}
