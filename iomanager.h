#ifndef __SYLAR_IO_MANAGER_H__
#define __SYLAR_IO_MANAGER_H__

#include "scheduler.h"

namespace sylar {

class IOManager : public Scheduler {
public:
	typedef std::shared_ptr<IOManager> ptr;
	typedef RWMutex RWMutexType;

	enum Event {
		NONE	= 0x0;
		READ	= 0x1;
		WRITE	= 0x2;
	}
private:
	struct FdContext {
		typedef Mutex MutexType;
		struct EventContext {
			Scheduler* scheduler = nullptr;	//事件执行的scheduler
			Fiber::ptr fiber;				//事件协程
			std::function<void()> cb;		//事件的回调函数
		};

		EventContext& getContext(Event event);
		void resetContext(EventContext& ctx);
		void triggerEvent(Event event);

		EventContext read;		//读事件
		EventContext witre;		//写事件
		int fd = 0;				//事件关联的句柄
		Event m_events = NONE;	//已经注册的事件
		MutexType mutex;
	};
public:
	IOManager(size_t threads = 1, bool use_caller = true, const std::string& name = "");
	~IOManager();
	//1 success, 0 retry, -1 error
	int add Event(int fd, Event event, std::function<void()> cb = nullptr);
	void contextResize(size_t size);
	bool delEvent(int fd, Event event);
	bool cancelEvent(int fd, Event event);
	

	bool canceAll(int fd);

	static IOManager* GetThis();
protected:
	void tickle() override;
	void stopping() override;
	void idle() override;
private:
	int m_epfd = 0;
	int m_tickleFds[2];

	std::atomic<size_t> m_pendingEventCount = {0};
	RWMutexType m_mutex;
	std::vector<FdContext*> m_fdContexts;
};


}


#endif
