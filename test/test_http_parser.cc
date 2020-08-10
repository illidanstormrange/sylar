#include "../http/http_parser.h"
#include "../log.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

const char test_request_data[] = "POST / HTTP/1.1\r\n"
								"Host: www.baidu.com\r\n"
								"Content-Length: 10\r\n\r\n"
								"1234567890";

void test_request() {
	sylar::http::HttpRequestParser parser;
	std::string tmp = test_request_data;
	size_t s = parser.execute(&tmp[0], tmp.size());
	SYLAR_LOG_INFO(g_logger) << "execute rt = " << s
		<< " has error=" << parser.hasError()
		<< " is_finished=" << parser.isFinished()
		<< " total=" << tmp.size()
		<< " content_length=" << parser.getContentLength();

	tmp.resize(tmp.size() - s);
	SYLAR_LOG_INFO(g_logger) << parser.getData()->toString();
}

const char test_response_data[] = "HTTP/1.0 200 OK\r\n"
"Accept-Ranges: bytes\r\n"
"Cache-Control: no-cache\r\n"
"Content-Length: 14615\r\n"
"Content-Type: text/html\r\n"
"Date: Mon, 10 Aug 2020 09:05:42 GMT\r\n"
"P3p: CP=\" OTI DSP COR IVA OUR IND COM \"\r\n"
"P3p: CP=\" OTI DSP COR IVA OUR IND COM \"\r\n"
"Pragma: no-cache\r\n"
"Server: BWS/1.1\r\n"
"Set-Cookie: BAIDUID=5CD58431F69D52E5BE2ADC0438E9548F:FG=1; expires=Thu, 31-Dec-37 23:55:55 GMT; max-age=2147483647; path=/; domain=.baidu.com\r\n"
"Set-Cookie: BIDUPSID=5CD58431F69D52E5BE2ADC0438E9548F; expires=Thu, 31-Dec-37 23:55:55 GMT; max-age=2147483647; path=/; domain=.baidu.com\r\n"
"Set-Cookie: PSTM=1597050342; expires=Thu, 31-Dec-37 23:55:55 GMT; max-age=2147483647; path=/; domain=.baidu.com\r\n"
"Set-Cookie: BAIDUID=5CD58431F69D52E5BA4C59E2F90CA2F7:FG=1; max-age=31536000; expires=Tue, 10-Aug-21 09:05:42 GMT; domain=.baidu.com; path=/; version=1; comment=bd\r\n"
"Traceid: 159705034203051648106797663066468892914\r\n"
"Vary: Accept-Encoding\r\n"
"X-Ua-Compatible: IE=Edge,chrome=1\r\n"
"<!DOCTYPE html><!--STATUS OK-->\r\n"
"<html>\r\n"
"<head>\r\n"
"	<meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\">\r\n"
"	<meta http-equiv=\"X-UA-Compatible\" content=\"IE=Edge\">\r\n"
"	<link rel=\"dns-prefetch\" href=\"//s1.bdstatic.com\"/>\r\n"
"	<link rel=\"dns-prefetch\" href=\"//t1.baidu.com\"/>\r\n"
"	<link rel=\"dns-prefetch\" href=\"//t2.baidu.com\"/>\r\n"
"	<link rel=\"dns-prefetch\" href=\"//t3.baidu.com\"/>\r\n"
"	<link rel=\"dns-prefetch\" href=\"//t10.baidu.com\"/>\r\n"
"	<link rel=\"dns-prefetch\" href=\"//t11.baidu.com\"/>\r\n"
"	<link rel=\"dns-prefetch\" href=\"//t12.baidu.com\"/>\r\n"
"	<link rel=\"dns-prefetch\" href=\"//b1.bdstatic.com\"/>\r\n"
"	<title>百度一下，你就知道</title>\r\n"
"	<link href=\"http://s1.bdstatic.com/r/www/cache/static/home/css/index.css\" rel=\"stylesheet\" type=\"text/css\" />\r\n"
"	<!--[if lte IE 8]><style index=\"index\" >#content{height:480px\9}#m{top:260px\9}</style><![endif]-->\r\n"
"	<!--[if IE 8]><style index=\"index\" >#u1 a.mnav,#u1 a.mnav:visited{font-family:simsun}</style><![endif]-->\r\n"
"	<script>var hashMatch = document.location.href.match(/#+(.*wd=[^&].+)/);if (hashMatch && hashMatch[0] && hashMatch[1]) {document.location.replace(\"http://\"+location.host+\"/s?\"+hashMatch[1]);}var ns_c = function(){};</script>\r\n"
"	<script>function h(obj){obj.style.behavior='url(#default#homepage)';var a = obj.setHomePage('//www.baidu.com/');}</script>\r\n"
"	<noscript><meta http-equiv=\"refresh\" content=\"0; url=/baidu.html?from=noscript\"/></noscript>\r\n"
"	<script>window._ASYNC_START=new Date().getTime();</script>\r\n"
"</head>\r\n"
"</html>\r\n";


void test_response() {
	sylar::http::HttpResponseParser parser;
	std::string tmp = test_response_data;
	size_t s = parser.execute(&tmp[0], tmp.size());
	SYLAR_LOG_ERROR(g_logger) << "execute rt=" << s
		<< " has Error=" << parser.hasError()
		<< " isFinished=" << parser.isFinished()
		<< " total=" << tmp.size()
		<< " content_length=" << parser.getContentLength()
		<< " tem[s]=" << tmp[s];
	tmp.resize(tmp.size() - s);

	SYLAR_LOG_INFO(g_logger) << parser.getData()->toString();
	SYLAR_LOG_INFO(g_logger) << tmp;

}

int main()
{
	test_response();
	return 0;
}
