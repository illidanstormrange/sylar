#ifndef __SYLAR_STREAM_H__
#define __SYLAR_STREAM_H__

#include <memory>
#include "bytearry.h"

namespace sylar {

class Stream {
public:
	typedef std::shared_ptr<Stream> ptr;
	virtual ~Stream() {}

	virtual int Streamread(void* buffer, size_t length) = 0;
	virtual int Streamread(ByteArray::ptr ba, size_t length) = 0;
	virtual int readFixSize(void* buffer, size_t length);
	virtual int readFixSize(ByteArray::ptr ba, size_t length);
	virtual int Streamwrite(const void* buffer, size_t length) = 0;
	virtual int Streamwrite(ByteArray::ptr ba, size_t length) = 0;
	virtual int writeFixSize(const void* buffer, size_t length);
	virtual int writeFixSize(ByteArray::ptr ba, size_t length);
	virtual void close() = 0;
};

}


#endif
