#include "sylar.h"

sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

int count = 0;
sylar::RWMutex g_mutex;

void func1() {

	g_logger->setFormatter("%d%T%t%T%F%T%m%T%n");
	SYLAR_LOG_INFO(g_logger) << "thread name : " << sylar::Thread::GetName()
							 << " this.name : " << sylar::Thread::GetThis()->getName()
							 << " thread id : " << sylar::GetThreadId()
							 << " this.id : " << sylar::Thread::GetThis()->getId();
	//sleep(20);
}

void func2() {

}

int main() {
	SYLAR_LOG_INFO(g_logger) << "thread test begin";
	std::vector<sylar::Thread::ptr> thrs;
	for(int i = 0; i < 5; ++i) {
		sylar::Thread::ptr thr(new sylar::Thread(&func1, "name_" + std::to_string(i)));
		thrs.push_back(thr);
	}
	for(int i = 0; i < 5; ++i) {
		thrs[i]->join();
	}
	SYLAR_LOG_INFO(g_logger) << "thread test end";
	SYLAR_LOG_INFO(g_logger) << count;
	return 0;
}
