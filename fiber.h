#ifndef __SYLAR_FIBER_H__
#define __SYLAR_FIBER_H__

#include <memory.h>
#include <functional>
#include <ucontext.h>
#include "thread.h"

namespace sylar {

class Fiber : public std::enable_shared_from_this<Fiber> {
public:
	typedef std::shared_ptr<Fiber> ptr;

	enum State {
		INIT, 
		HOLD,
		EXEC,
		TERM,
		READY,
		EXCEPT
	};
private:
	Fiber();
public:
	Fiber(std::function<void()> cb, size_t stacksize = 0);
	~Fiber();
	
	//重置协程函数，并重设状态
	//INIT, TERM
	void reset(std::function<void()> cb);
	//切换到当前协程
	void swapIn();
	//切换到后台执行
	void swapOut();
	uint64_t getId() const { return m_id; };
public:
	static uint64_t GetFiberId();
	//设置当前协程
	static void SetThis(Fiber* f);
	//返回当前线程
	static Fiber::ptr GetThis();
	//协程切换到后台，并转化为Ready状态
	static void YieldToReady();
	//协程切换到后台，并转化为Hold状态
	static void YieldToHold();
	//总协程数
	static uint64_t TotalFibers();

	static void MainFunc();
private:
	uint64_t m_id = 0;
	uint32_t m_stacksize = 0;
	State m_state = INIT;
	
	ucontext_t m_ctx;
	void* m_stack = nullptr;
	std::function<void()> m_cb;
};
}
#endif
