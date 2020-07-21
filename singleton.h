#ifndef __SYLAR_SIGNLETON_H__
#define __SYLAR_SIGNLETON_H__


namespace sylar{

template<class T, class X = void, int N = 0>
class Singleton {
public:
	static T* GetInstence()
	{
		static T v;
		return &v;
	}
};

template<class T, class X = void, int N = 0>
class SingletonPtr {
public:
	static std::shared_ptr<T> GetInstence()
	{
		std::shared_ptr<T> v(new T);
		return v;
	}
};

}

#endif
