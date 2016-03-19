#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include "memory"

struct Baselist {
	virtual ~Baselist(){};
	virtual bool find(int k) = 0;
	virtual bool del(int k) = 0;
	virtual bool insert(int k) = 0;
	static std::shared_ptr<Baselist> make_Skiplist();
};
#endif
