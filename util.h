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
#include <boost/lexical_cast.hpp>

namespace sylar{

pid_t GetThreadId();
uint32_t GetFiberId();

void Backtrace(std::vector<std::string>& bc, int size = 64, int skip = 1);
std::string BacktraceTostring(int size = 64, int skip = 2, const std::string& prefix = "");

uint64_t GetCurrentMS();
uint64_t GetCurrentUs();

std::string Time2Str(time_t ts = time(0), const std::string& formart = "%Y-%m-%d %H:%M:%S");
	
class FSUtil {
public:
	static void ListAllFile(std::vector<std::string>& files
							, const std::string& path
							, const std::string& subfix);
	static bool Mkdir(const std::string& dirname);
	static bool IsRunningPidfile(const std::string& pidfile);
};

template<class V, class Map, class K>
V GetParamValue(const Map& m, const K& k, const V& def = V()) {
	auto it = m.find(k);
	if(it == m.end()) {
		return def;
	}
	try {
		return boost::lexical_cast<V>(it->second);
	} catch(...) {
	}
	return def;
}


class TypeUtil {
public:
	static int8_t ToChar(const std::string& str);
	static int64_t Atoi(const std::string& str);
	static double Atof(const std::string& str);
	static int8_t ToChar(const char* str);
	static int64_t Atoi(const char* str);
	static double Atof(const char* str);
};
}

#endif
