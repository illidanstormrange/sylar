#ifndef __SYLAR_MACRO_H__
#define __SYLAR_MACRO_H__

#include "util.h"
#include "log.h"
#include <string.h>
#include <assert.h>

#define SYLAR_ASSERT(x) \
	if(!(x)) { \
		SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " #x \
						<< " \nbacktrace\n" \
						<< sylar::BacktraceTostring(10, 2, "    "); \
		assert(x);  \
	}

#define SYLAR_ASSERT2(x, m) \
	if(!(x)) { \
		SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) << "ASSERTION: " #x \
						<< "\n" << m \
						<< " \nbacktrace\n" \
						<< sylar::BacktraceTostring(10, 2, "    "); \
		assert(x);  \
	}
#endif
