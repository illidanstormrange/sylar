#include "socket_stream.h"

namespace sylar {
SocketStream::SocketStream(Socket::ptr sock, bool owner)
	:m_socket(sock)
	,m_owner(owner) {
}
SocketStream::~SocketStream() {
	if(m_owner && m_socket) {
		m_socket->close();
	}
}
int SocketStream::Streamread(void* buffer, size_t length) {
	if(!isConnected()) {
		return -1;
	}
	return m_socket->recv(buffer, length);
}

int SocketStream::Streamread(ByteArray::ptr ba, size_t length) {
	if(!isConnected()) {
		return -1;
	}
	std::vector<iovec> iovs;
	ba->getWriteBuffers(iovs, length);
	int rt = m_socket->recv(&iovs[0], iovs.size());
	if(rt > 0) {
		ba->setPostion(ba->getPosition() + rt);
	}
	return rt;
}

int SocketStream::Streamwrite(const void* buffer, size_t length) {
	if(!isConnected()) {
		return -1;
	}
	return m_socket->send(buffer, length);
}

int SocketStream::Streamwrite(ByteArray::ptr ba, size_t length) {
	if(!isConnected()) {
		return -1;
	}
	std::vector<iovec> iovs;
	ba->getReadBuffers(iovs, length);
	int rt = m_socket->send(&iovs[0], iovs.size());
	if(rt > 0) {
		ba->setPostion(ba->getPosition() + rt);
	}
	return rt;
}

bool SocketStream::isConnected() const {
	return m_socket && m_socket->isConnected();
}

void SocketStream::close() {
	if(m_socket) {
		m_socket->close();
	}
}



}
