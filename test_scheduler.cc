#include "sylar.h" 

static sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

void test_fiber() {
	static int count = 5;
	SYLAR_LOG_INFO(g_logger) << "test in fiber count=" << count;
	//sleep(1);
	if(--count >= 0) {
		sylar::Scheduler::GetThis()->scheduler(&test_fiber);
	}
}

int main() {
	SYLAR_LOG_INFO(g_logger) << "main";
	sylar::Scheduler sc(3, false , "test");
	sc.start();
	sc.scheduler(&test_fiber);
	sc.stop();
	SYLAR_LOG_INFO(g_logger) << "end";
	return 0;
}
