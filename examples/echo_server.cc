#include "../tcp_server.h"
#include "../log.h"
#include "../iomanager.h"
#include "../bytearry.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

class EchoServer : public sylar::TcpServer {
public:
	EchoServer(int type) 
		:m_type(type) {}
	void handleClient(sylar::Socket::ptr client) override;

private:
	int m_type = 0;
};

void EchoServer::handleClient(sylar::Socket::ptr client) {
	SYLAR_LOG_INFO(g_logger) << "handleClient " << *client;
	sylar::ByteArray::ptr ba(new sylar::ByteArray);
	while(true) {
		ba->clear();
		std::vector<iovec> iovs;
		ba->getWriteBuffers(iovs, 1024);

		int rt = client->recv(&iovs[0], iovs.size());
		if(rt == 0) {
			SYLAR_LOG_INFO(g_logger) << "client close :" << *client;
			break;
		} else if(rt < 0) {
			SYLAR_LOG_INFO(g_logger) << "client error rt=" << rt
				<< " errno" << errno << " errstr=" << strerror(errno);
			break;
		}
		ba->setPostion(ba->getPosition() + rt);
		ba->setPostion(0);

		if(m_type == 1) {
			SYLAR_LOG_INFO(g_logger) << ba->toString();
		} else {
			SYLAR_LOG_INFO(g_logger) << ba->toHexString();
		}
	}
}

int type = 1;

void run() {
	EchoServer::ptr es(new EchoServer(type));
	auto addr = sylar::Address::LookUpAny("0.0.0.0:8020");
	while(!es->bind(addr)) {
		sleep(2);
	}
	es->start();
}

int main(int argc, char* argv[])
{
	if(argc < 2) {
		SYLAR_LOG_INFO(g_logger) << "no type";
		return 0;
	}

	if(!strcmp(argv[1], "-b")) {
		type = 2;
	}
	sylar::IOManager iom(2);
	iom.scheduler(run);
	return 0;
}
