#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_
#include <ctime>
#include <cstdlib>
#include <memory>
#include <vector>
#include <cstring>
#include "interface.h"

class Skiplist: public Baselist{
	struct Node {
		int data;
		/* pointer array, array[i] indicates the left elements of level i */
		std::vector<std::shared_ptr<Node>> array; 
		Node(int d, int l = 1);
		~Node();
	};
public:
	Skiplist();
	virtual ~Skiplist();
	inline bool find(int k) override {
		return find_pos(k)->data == k;
	}
	bool del(int k) override;
	bool insert(int k) override;
private:
	std::shared_ptr<Node> find_pos(int k);
	void increase_root_level();
	// Return the level of inserted elements. 
	int get_level();
	std::shared_ptr<Node> root, end;
	static const int MAX = 0x7FFFFFFF;
	static const int MAX_LEVEL = 10;
};

#endif
