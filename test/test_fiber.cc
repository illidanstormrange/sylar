#include "../sylar.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

void test() {
	SYLAR_LOG_INFO(g_logger) << "test begin";
	sylar::Fiber::YieldToHold();
	SYLAR_LOG_INFO(g_logger) << "test end";
}

void test_fiber() {
	sylar::Fiber::GetThis();
	SYLAR_LOG_INFO(g_logger) << "main begin";
	sylar::Fiber::ptr fiber(new sylar::Fiber(test));
	SYLAR_LOG_INFO(g_logger) << "befor swapIn()";
	fiber->call();
	SYLAR_LOG_INFO(g_logger) << "main after fiber";
	fiber->call();
	SYLAR_LOG_INFO(g_logger) << "uuuuuuuain after end";
}

int main() {
	sylar::Thread::SetName("main");

	std::vector<sylar::Thread::ptr> vec;
	for(int i = 0; i < 3; ++i) {
		vec.push_back(sylar::Thread::ptr(new sylar::Thread(
					&test_fiber, "name_" + std::to_string(i))));
	}
	for(auto& i : vec) {
		i->join();
	}
	SYLAR_LOG_INFO(g_logger) << "main end";
	return 0;
}

