#include "../sylar.h"
#include <assert.h>


void test() {
	sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();
	SYLAR_LOG_INFO(g_logger) << sylar::BacktraceTostring(10);
	SYLAR_ASSERT(false);
}

int main() {
	test();
	return 0;
}
