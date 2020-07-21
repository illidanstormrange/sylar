#include "log.h"
#include "util.h"
#include <iostream>
int main()
{
	sylar::Logger::ptr logger(new sylar::Logger);
	logger->addAppender(sylar::LogAppender::ptr(new sylar::StdoutLogAppender));
	
	sylar::FileLogAppender::ptr file_appender(new sylar::FileLogAppender("log.txt"));
	sylar::LogFormatter::ptr fmt(new sylar::LogFormatter("%d%T%p%T%m%n"));
	file_appender->setFormatter(fmt);

	logger->addAppender(file_appender);
	sylar::LogEvent::ptr event(new sylar::LogEvent(logger, sylar::LogLevel::DEBUG,
				__FILE__, __LINE__, 0, 1, 2, time(0)));
	event->getSS() << "test xxx";
	std::cout << "hello world!" << std::endl;
	SYLAR_LOG_INFO(logger);
	SYLAR_LOG_FMT_ERROR(logger, "test macor fmt error: %s", "aa");
	auto l = sylar::LogMgr::GetInstence()->getLogger("xx");
	SYLAR_LOG_INFO(l) << "xxx";
	return 0;
}
