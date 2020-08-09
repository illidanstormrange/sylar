#include "../address.h"
#include "../log.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();
void test_address()
{
	std::vector<sylar::Address::ptr> addrs;

	SYLAR_LOG_INFO(g_logger) << "begin";
	bool v = sylar::Address::LookUp(addrs, "www.baidu.com");
	SYLAR_LOG_INFO(g_logger) << "end";
	if(!v) {
		SYLAR_LOG_ERROR(g_logger) << "LookUp fail";
		return;
	}

	for(size_t i = 0; i < addrs.size(); ++i) {
		SYLAR_LOG_INFO(g_logger) << i << " - " << addrs[i]->toString();
	}
}

void test_iface()
{
	std::multimap<std::string, std::pair<sylar::Address::ptr, uint32_t> > results;

	bool v = sylar::Address::GetInterfaceAddress(results);
	if(!v) {
		SYLAR_LOG_ERROR(g_logger) << "GetInterfaceAddress fail";
		return;
	}

	for(auto& i : results) {
		SYLAR_LOG_INFO(g_logger) << i.first << " - " << i.second.first->toString() << " - "
			<< i.second.second;
	}
}

void test_ipv4() {
	auto addr = sylar::IPAddress::Create("www.baidu.com");
	if(addr) {
		SYLAR_LOG_INFO(g_logger) << addr->toString();
	}
}

int main()
{
	test_address();
	//test_iface();
	//test_ipv4();
	return 0;
}
