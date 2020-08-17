#include "http_session.h"
#include <iostream>

namespace sylar {
namespace http {

HttpSession::HttpSession(Socket::ptr sock, bool owner)
	:SocketStream(sock, owner){
}

HttpRequest::ptr HttpSession::recvRequsest() {
	HttpRequestParser::ptr parser(new HttpRequestParser);
	uint64_t buff_size = HttpRequestParser::GetHttpRequestBufferSize();
	//uint64_t buff_size = 100;
	std::shared_ptr<char> buffer (
			new char[buff_size], [](char* ptr){
				delete[] ptr;
			});
	char* data = buffer.get();
	int offset = 0;
	do{
		int len = Streamread(data + offset, buff_size - offset);
		if(len <= 0) {
			close();
			std::cout << "len <= 0" << std::endl;
			return nullptr;
		}
		len += offset;
		size_t nparse = parser->execute(data, len + offset);
		if(parser->hasError()) {
			return nullptr;
		}
		offset = len - nparse;
		if(parser->isFinished()) {
			break;
		}
	} while(true);
	int64_t length = parser->getContentLength();
	if(length > 0) {
		std::string body;
		body.resize(length);

		int len = 0;
		if(length >= offset) {
			memcpy(&body[0], data, offset);
			len = offset;
		} else {
			memcpy(&body[0], data, length);
			len = offset;
		}
		length -= offset;

		if(length > 0) {
			if(readFixSize(&body[len], length) <= 0) {
				return nullptr;
			}
		}
		parser->getData()->setBody(body);
	}
	return parser->getData();
}

int HttpSession::sendRespons(HttpResponse::ptr rsp) {
	std::stringstream ss;
	ss << *rsp;
	std::string data = ss.str();
	return writeFixSize(data.c_str(), data.length());
}

}
}
