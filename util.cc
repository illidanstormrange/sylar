#include "util.h"
#include "log.h"
#include "fiber.h"
#include <execinfo.h>
#include <stdlib.h>
#include <time.h>
#include <dirent.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

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
	for(int i = 0; i < (int)vec.size(); ++i) {
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

std::string Time2Str(time_t ts, const std::string& format) {
	struct tm tm;
	localtime_r(&ts, &tm);
	char buf[64];
	strftime(buf, sizeof(buf), format.c_str(), &tm);
	return buf;
}	
void FSUtil::ListAllFile(std::vector<std::string>& files
							, const std::string& path
							, const std::string& subfix) {
	if(access(path.c_str(), 0) != 0) {
		return;
	}
	DIR* dir = opendir(path.c_str());
	if(dir == nullptr) {
		return;
	}
	struct dirent* dp = nullptr;
	while((dp = readdir(dir)) != nullptr) {
		if(dp->d_type == DT_DIR) {
			if(!strcmp(dp->d_name, ".")
					|| !strcmp(dp->d_name, "..")) {
				continue;
			}
			ListAllFile(files, path + "/" + dp->d_name, subfix);
		} else if(dp->d_type == DT_REG) {
			std::string filename(dp->d_name);
			if(subfix.empty()) {
				files.push_back(path + "/" + filename);
			} else {
				if(filename.size() < subfix.size()) {
					continue;
				}
				if(filename.substr(filename.length() - subfix.size()) == subfix) {
				files.push_back(path + "/" + filename);
				}
			}
		}
	}
	closedir(dir);
}

static int __lstat(const char* file, struct stat* st = nullptr) {
	struct stat lst;
	int ret = lstat(file, &lst);
	if(st) {
		*st = lst;
	}
	return ret;
}

static int __mkdir(const char* dirname) {
	if(access(dirname, F_OK) == 0) {
		return 0;
	}
	return mkdir(dirname, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

bool FSUtil::Mkdir(const std::string& dirname) {
	if(__lstat(dirname.c_str()) == 0) {
		return true;
	}
	char* path = strdup(dirname.c_str());
	char* ptr = strchr(path + 1, '/');
	do {
		for(; ptr; *ptr = '/', ptr = strchr(ptr + 1, '/')) {
			*ptr = '\0';
			if(__mkdir(path) != 0) {
				break;
			}
		}
		if(ptr != nullptr) {
			break;
		} else if(__mkdir(path) != 0) {
			break;
		}
		free(path);
		return true;
	} while(0);
	free(path);
	return false;
}

bool FSUtil::IsRunningPidfile(const std::string& pidfile) {
	if(__lstat(pidfile.c_str()) != 0) {
		return false;
	}
	std::ifstream ifs(pidfile);
	std::string line;
	if(!ifs || !std::getline(ifs, line)) {
		return false;
	}
	if(line.empty()) {
		return false;
	}
	pid_t pid = atoi(line.c_str());
	if(pid <= -1) {
		return false;
	}
	if(kill(pid, 0) != 0) {
		return false;
	}
	return true;
}

int8_t  TypeUtil::ToChar(const std::string& str) {
	if(str.empty()) {
		return 0;
	}
	return *str.begin();
}

int64_t TypeUtil::Atoi(const std::string& str) {
	if(str.empty()) {
		return 0;
	}
	return strtoull(str.c_str(), nullptr, 10);
}
double  TypeUtil::Atof(const std::string& str) {
	if(str.empty()) {
		return 0;
	}
	return atof(str.c_str());
}
int8_t  TypeUtil::ToChar(const char* str) {
	if(str == nullptr) {
		return 0;
	}
	return str[0];
}
int64_t TypeUtil::Atoi(const char* str) {
	if(str == nullptr) {
		return 0;
	}
	return strtoull(str, nullptr, 10);
}
double  TypeUtil::Atof(const char* str) {
	if(str == nullptr) {
		return 0;
	}
	return atof(str);
}
}
