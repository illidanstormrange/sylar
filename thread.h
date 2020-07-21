#ifndef __SYLAR_THREAD_H__
#define __SYLAR_THREAD_H__

#include <memory>
#include <pthread.h>
#include <functional>
#include <thread>
#include <semaphore.h>
#include <stdint.h>

namespace sylar
{

class Semaphore {
public:
	Semaphore(uint32_t count = 0);
	~Semaphore();

	void wait();
	void notify();

private:
	Semaphore(const Semaphore&) = delete;
	Semaphore(const Semaphore&&) = delete;
	Semaphore operator=(const Semaphore&) = delete;
private:
	sem_t m_semaphore;
};

template<class T>
struct ScopedLockImpl {
public:
	ScopedLockImpl(T& mutex)
		:m_mutex(mutex){
			m_mutex.lock();
			m_locked = true;
	}
	~ScopedLockImpl() {
		m_mutex.unlock();
		m_locked = false;
	}

	void lock() {
		if(!m_locked) {
			m_mutex.lock();
			m_locked = true;
		}
	}

	void unlock() {
		if(m_locked) {
			m_mutex.unlock();
			m_locked = false;
		}
	}

private:
	T& m_mutex;
	bool m_locked;
};

template<class T>
struct WriteScopedLockImpl {
public:
	WriteScopedLockImpl(T& mutex)
		:m_mutex(mutex){
			m_mutex.wrlock();
			m_locked = true;
	}
	~WriteScopedLockImpl() {
		m_mutex.unlock();
		m_locked = false;
	}

	void lock() {
		if(!m_locked) {
			m_mutex.wrlock();
			m_locked = true;
		}
	}

	void unlock() {
		if(m_locked) {
			m_mutex.unlock();
			m_locked = false;
		}
	}

private:
	T& m_mutex;
	bool m_locked;
};

template<class T>
struct ReadScopedLockImpl {
public:
	ReadScopedLockImpl(T& mutex)
		:m_mutex(mutex){
			m_mutex.rdlock();
			m_locked = true;
	}
	~ReadScopedLockImpl() {
		m_mutex.unlock();
		m_locked = false;
	}

	void lock() {
		if(!m_locked) {
			m_mutex.rdlock();
			m_locked = true;
		}
	}

	void unlock() {
		if(m_locked) {
			m_mutex.unlock();
			m_locked = false;
		}
	}

private:
	T& m_mutex;
	bool m_locked;
};

class NullMutex {
public:
	typedef ScopedLockImpl<NullMutex> Lock;
	NullMutex() {}
	~NullMutex() {}
	void lock() {}
	void unlock() {}
};

class Mutex {
public:
	typedef ScopedLockImpl<Mutex> Lock;
	Mutex() {
		pthread_mutex_init(&m_mutex, nullptr);
	}

	void lock() {
		pthread_mutex_lock(&m_mutex);
	}

	void unlock() {
		pthread_mutex_unlock(&m_mutex);
	}
private:
	pthread_mutex_t m_mutex;
};

class NullRWMutex {
public:
	typedef ReadScopedLockImpl<NullRWMutex> ReadLock;
	typedef WriteScopedLockImpl<NullRWMutex> WriteLock;
	NullRWMutex() {}
	~NullRWMutex() {}
	void rdlock() {}
	void wrlock() {}
	void unlock() {}
};

class RWMutex {
public:
	typedef ReadScopedLockImpl<RWMutex> ReadLock;
	typedef WriteScopedLockImpl<RWMutex> WriteLock;
	RWMutex() {
		pthread_rwlock_init(&m_lock, nullptr);
	}

	void rdlock() {
		pthread_rwlock_rdlock(&m_lock);
	}

	void wrlock() {
		pthread_rwlock_wrlock(&m_lock);
	}

	void unlock() {
		pthread_rwlock_unlock(&m_lock);
	}

private:
	pthread_rwlock_t m_lock;
};

class Thread {
public:
	typedef std::shared_ptr<Thread> ptr;
	Thread(std::function<void()> cb, const std::string name);
	~Thread();

	pid_t getId() const { return m_id; }
	const std::string getName() { return m_name; }

	void join();

	static Thread* GetThis();
	static const std::string& GetName();
	static void SetName(const std::string name);
private:
	Thread(const Thread&) = delete;
	Thread(const Thread&& ) = delete;
	Thread& operator= (const Thread& ) = delete;
	
	static void* run(void* arg);
private:
	pid_t m_id;
	pthread_t m_thread;
	std::function<void()> m_cbs;
	std::string m_name;

	Semaphore m_semaphore;
};


}

#endif