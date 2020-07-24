#include "scheduler.h"
#include "log.h"

namespace sylar {
Logger::ptr g_logger = SYLAR_LOG_NAME("system");

static thread_local Scheduler* t_scheduler = nullptr;
static thread_local Fiber* t_fiber = nullptr;

Scheduler::Scheduler(size_t threads, bool use_caller, const std::string name)
	:m_name(name) {
	SYLAR_ASSERT(threads > 0);

	if(use_caller) {
		Fiber::GetThis();
		--threads;

		SYLAR_ASSERT(GetThis() == nullptr);
		t_scheduler = this;

		m_rootFiber.reset(new Fiber(std::bind(&Scheduler::run, this)));
		Thread::SetName(m_name);

		t_fiber = m_rootFiber.get();
		m_rootFiber = GetThreadId();
		m_threadIds.push_back(m_rootThread);
	} else {
		m_rootThread = -1;
	}
	m_threadCount = threads;
}

virtual Scheduler::~Scheduler() {
	SYLAR_ASSERT(m_stopping);
	if(GetThis() == this) {
		t_scheduler = nullptr;
	}
}

static Scheduler* Scheduler::GetThis() {
	return t_scheduler;
}

static Fiber* Scheduler::GetMainFiber() {
	return t_fiber;
}

void Scheduler::start() {
	MutexType::Lock lock(m_mutex);
	if(!m_stopping) {
		return;
	}
	m_stopping = false;
	SYLAR_ASSERT(m_threads.empty());

	m_threads.resize(m_threadCount);
	for(size_t i = 0; i < m_threadCount; ++i) {
		m_threads[i].reset(new Thread(std::bind(&Scheduler::run, this)
					, m_name + "_" + std::to_string(i)));
		m_threadIds.push_back(m_threads[i]->getId());
	}
}
void Scheduler::stop() {
	m_autoStop = true;
	if(m_rootFiber
			&& m_threadCount == 0
			&& (m_rootFiber->getState() == Fiber::TERM
				|| m_rootFiber->getState() == Fiber::INIT)) {
		SYLAR_LOG_INFO(g_logger) << this << " stopped";
		m_stopping = true;

		if(stopping()) {
			return;
		}
	}

	bool exit_on_this_fiber = false;
	if(m_rootThread != -1) {
		SYLAR_ASSERT(GetThis() == this);
	} else {
		SYLAR_ASSERT(GetThis() != this);
	}

	m_stopping = true;
	for(size_t i = 0; i < m_threadCount; ++i) {
		tickle();
	}

	if(m_rootFiber) {
		tickle();
	}
}

void Scheduler::run() {

}

}
