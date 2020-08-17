#ifndef __SYLAR_SOCKET_STREAM_H__
#define __SYLAR_SOCKET_STREAM_H__

#include "stream.h"
#include "socket.h"

namespace sylar {

class SocketStream : public Stream {
public:
	typedef std::shared_ptr<SocketStream> ptr;
	SocketStream(Socket::ptr  sock, bool owner = true);
	~SocketStream();
	virtual int Streamread(void* buffer, size_t length) override;
	virtual int Streamread(ByteArray::ptr ba, size_t length) override;
	virtual int Streamwrite(const void* buffer, size_t length) override;
	virtual int Streamwrite(ByteArray::ptr ba, size_t length) override;
	virtual void close() override;

	Socket::ptr getSocket() const { return m_socket; }
	bool isConnected() const;
protected:
	Socket::ptr m_socket;
	bool m_owner;
};


}


#endif
