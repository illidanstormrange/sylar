#ifndef __SYLAR_SCHEDULER_H__
#define __SYLAR_SCHEDULER_H__

#include "thread.h"
#include "fiber.h"
#include "macro.h"
#include <memory.h>
#include <string>
#include <list>
#include <vector>

namespace sylar {

class Scheduler {
public:
	typedef std::shared_ptr<Scheduler> ptr;
	typedef Mutex MutexType;

	Scheduler(size_t threads = 1, bool use_call = true, const std::string& name = "");
	virtual ~Scheduler();

	const std::string& getName() const { return m_name; }

	static Scheduler* GetThis();
	static Fiber* GetMainFiber();

	void start();
	void stop();

	template<class FiberOrCb>
	void scheduler(FiberOrCb fc, int thread = -1) {
		bool need_tickle = false;
		{
			MutexType::Lock lock(m_mutex);
			need_tickle = schedulerNoLock(fc, thread);
		}

		if(need_tickle) {
			tickle();
		}
	}
	
	template<class InputIterator>
	void scheduler(InputIterator begin, InputIterator end) {
		bool need_tickle = false;
		{
			MutexType::Lock lock(m_mutex);
			while(begin != end) {
				need_tickle = schedulerNoLock(&*begin, -1) || need_tickle;
				++begin;
			}
			if(need_tickle) {
				tickle();
			}
		}
	}

protected:
	virtual void tickle();
	void run();
	virtual bool stopping();
	virtual void idle();

	void setThis();

	bool hasIdleThreads() { return m_idleThreadCount > 0; }
private:
	template<class FiberOrCb>
	bool schedulerNoLock(FiberOrCb fc, int thread) {
		bool need_tickle = m_fibers.empty();
		FiberAndThread ft(fc, thread);
		if(ft.fiber || ft.thread) {
			m_fibers.push_back(ft);
		}

		return need_tickle;
	}

	struct FiberAndThread {
		Fiber::ptr fiber;
		std::function<void()> cb;
		int thread;

		FiberAndThread(Fiber::ptr f, int thr)
			:fiber(f), thread(thr){
		}

		FiberAndThread(Fiber::ptr* f, int thr)
			:thread(thr){
				fiber.swap(*f);
		}

		FiberAndThread(std::function<void()> f, int thr) 
			:cb(f), thread(thr){
		}		
		FiberAndThread(std::function<void()>* f, int thr) 
			:thread(thr){
				cb.swap(*f);
		}

		FiberAndThread() 
			:thread(-1) {
		}

		void reset() {
			fiber = nullptr;
			cb = nullptr;
			thread = -1;
		}
	};
private:
	std::string m_name;
	MutexType m_mutex;
	Fiber::ptr m_rootFiber;
	std::vector<Thread::ptr> m_threads;
	std::list<FiberAndThread> m_fibers;
protected:
	std::vector<int> m_threadIds;
	size_t m_threadCount = 0;
	size_t m_activeThreadCount = 0;
	size_t m_idleThreadCount = 0;
	bool m_stopping = true;
	bool m_autoStop = false;
	int m_rootThread = 0;
};

}

#endif
