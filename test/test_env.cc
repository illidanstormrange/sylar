#include "../env.h"
#include <iostream>

int main(int argc, char** argv) {
	sylar::EnvMgr::GetInstence()->addHelp("s", "start with the termainal");
	sylar::EnvMgr::GetInstence()->addHelp("d", "ryn as daemon");
	sylar::EnvMgr::GetInstence()->addHelp("p", "print help");
	if(!sylar::EnvMgr::GetInstence()->init(argc, argv)) {
		sylar::EnvMgr::GetInstence()->printHelp();
		return 0;
	}

	std::cout << "exe = " << sylar::EnvMgr::GetInstence()->getExe() << std::endl;
	std::cout << "cwd = " << sylar::EnvMgr::GetInstence()->getCwd() << std::endl;

	std::cout << "path = " << sylar::EnvMgr::GetInstence()->getEnv("PATH", "xxx") << std::endl;

	if(sylar::EnvMgr::GetInstence()->has("p")) {
		sylar::EnvMgr::GetInstence()->printHelp();
	}

	return 0;
}
