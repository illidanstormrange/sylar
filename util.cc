#include "util.h"
#include "log.h"
#include <execinfo.h>
#include <stdlib.h>
#include "fiber.h"

namespace sylar{
sylar::Logger::ptr g_logger = SYLAR_LOG_NAME("system");

pid_t GetThreadId()
{
	return syscall(SYS_gettid);
}

uint32_t GetFiberId()
{
	return sylar::Fiber::GetFiberId();
}

void Backtrace(std::vector<std::string>& bc, int size, int skip) {
	void** array = (void**)malloc(sizeof(void*) * size);
	size_t s = ::backtrace(array, size);
	
	char** strings = backtrace_symbols(array, s);
	if(strings == NULL) {
		SYLAR_LOG_ERROR(g_logger) << "backtrace_symbols error";
		return;
	}

	for(size_t i = skip; i < s; ++i) {
		bc.push_back(strings[i]);
	}
	free(strings);
	free(array);
}
std::string BacktraceTostring(int size, int skip, const std::string& prefix) {
	std::vector<std::string> vec;
	Backtrace(vec, size, skip);
	std::stringstream ss;
	for(int i = 0; i < vec.size(); ++i) {
		ss << prefix << vec[i] << std::endl;
	}
	return ss.str();
}


uint64_t GetCurrentMS() {
	struct timeval val;
	gettimeofday(&val, NULL);
	return val.tv_sec * 1000ul + val.tv_usec / 1000;
}
uint64_t GetCurrentUs() {
	struct timeval val;
	gettimeofday(&val, NULL);
	return val.tv_sec * 1000 * 1000ul + val.tv_usec;
}

}
