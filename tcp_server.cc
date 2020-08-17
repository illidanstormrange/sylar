#include "tcp_server.h"
#include "config.h"

namespace sylar {

static Logger::ptr g_logger = SYLAR_LOG_NAME("system");

static ConfigVar<uint64_t>::ptr g_tcp_server_read_timeout = 
	sylar::Config::Lookup("tcp_sever.read_timeout", (uint64_t)(60 * 1000 * 2), "tcp server read timeout");

TcpServer::TcpServer(sylar::IOManager* worker
					,sylar::IOManager* accept_worker)
	:m_worker(worker)
	,m_accept_worker(accept_worker)
	,m_recvTimeout(g_tcp_server_read_timeout->getValue())
	,m_name("sylar/1.0.0")
	,m_isStop(true) {
}

bool TcpServer::bind(sylar::Address::ptr addr) {
	std::vector<Address::ptr> addrs;
	std::vector<Address::ptr> fails;
	addrs.push_back(addr);
	return bind(addrs, fails);
}

TcpServer::~TcpServer() {
	for(auto& i : m_socks) {
		i->close();
	}
	m_socks.clear();
}
bool TcpServer::bind(const std::vector<Address::ptr>& addrs
					,std::vector<Address::ptr>& fails) {
	for(auto& addr : addrs) {
		Socket::ptr sock = Socket::CreateTCP(addr);
		if(!sock->bind(addr)) {
			SYLAR_LOG_ERROR(g_logger) << "bind fail error="
				<< errno << "errstr=" << strerror(errno)
				<< " addr=(" << addr->toString() << ")";
			fails.push_back(addr);
			break;
		}
		if(!sock->listen()) {
			SYLAR_LOG_ERROR(g_logger) << "listen fail errno="
				<< errno << " errstr=" << strerror(errno)
				<< " addr=[" << addr->toString() << "]";
			fails.push_back(addr);
			continue;
		}
		m_socks.push_back(sock);
	}

	if(!fails.empty()) {
		m_socks.clear();
		return false;
	}

	for(auto& i : m_socks) {
		SYLAR_LOG_INFO(g_logger) << " name = " << m_name
			<< "server bind success: " << *i;
	}
	return true;

}

bool TcpServer::start() {
	if(!m_isStop) {
		return true;
	}
	m_isStop = false;
	for(auto& sock : m_socks) {
		m_accept_worker->scheduler(std::bind(&TcpServer::startAccept,
					shared_from_this(), sock));
	}
	return true;
}

void TcpServer::stop() {
	m_isStop = true;
	auto self = shared_from_this();
	m_accept_worker->scheduler([this, self]() {
			for(auto& sock : m_socks) {
				sock->cancelAll();
				sock->close();
			}
			m_socks.clear();
	});
}

void TcpServer::handleClient(Socket::ptr client) {
	SYLAR_LOG_INFO(g_logger) << "handleClient: " << *client;
}

void TcpServer::startAccept(Socket::ptr sock) {
	while(!m_isStop) {
		Socket::ptr client = sock->accept();
		if(client) {
			client->setRecvTimeout(m_recvTimeout);
			m_worker->scheduler(std::bind(&TcpServer::handleClient,
						shared_from_this(), client));
		} else {
			SYLAR_LOG_ERROR(g_logger) << "accept errno=" << errno
				<< " errstr=" << strerror(errno);
		}
	}
}
}
