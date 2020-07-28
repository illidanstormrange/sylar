#include "sylar.h" 

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

void test_fiber() {
	SYLAR_LOG_INFO(g_logger) << "test in fiber";
}

int main() {
	SYLAR_LOG_INFO(g_logger) << "main";
	sylar::Scheduler sc;
	sc.scheduler(&test_fiber);
	sc.start();
	sc.stop();
	SYLAR_LOG_INFO(g_logger) << "end";
	return 0;
}
