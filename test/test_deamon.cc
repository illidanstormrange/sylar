#include "../daemon.h"
#include "../iomanager.h"
#include "../log.h"

static sylar::Logger::ptr g_logger = SYLAR_LOG_ROOT();

int server_main(int argc, char** argv) {
	sylar::IOManager iom(1);
	iom.addTimer(1000, [](){
			SYLAR_LOG_INFO(g_logger) << "onTimer";
	}, true);
}


int main(int argc, char** argv) {
	return sylar::start_daemon(argc, argv, server_main, argc != 1);
}
