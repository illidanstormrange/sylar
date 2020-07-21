#ifndef _SYSLAR_UTIL_H
#define _SYSLAR_UTIL_H

#include <pthread.h>
#include <sys/types.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <iostream>

namespace sylar{
pid_t GetThreadId();
uint32_t GetFiberId();
}
	

#endif
