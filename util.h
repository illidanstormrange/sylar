#ifndef _SYSLAR_UTIL_H
#define _SYSLAR_UTIL_H

#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <string>

namespace sylar{

pid_t GetThreadId();
uint32_t GetFiberId();

void Backtrace(std::vector<std::string>& bc, int size = 64, int skip = 1);
std::string BacktraceTostring(int size = 64, int skip = 2, const std::string& prefix = "");

uint64_t GetCurrentMS();
uint64_t GetCurrentUs();
}
	

#endif
