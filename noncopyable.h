#ifndef __SYLAR__NONCOPYABLE_H__
#define __SYLAR__NONCOPYABLE_H__


namespace sylar{

class Noncopyable {
public:
	Noncopyable() = default;
	~Noncopyable() = default;
	Noncopyable(Noncopyable&) = delete;
	Noncopyable operator=(Noncopyable&) = delete; 

};

}

#endif
