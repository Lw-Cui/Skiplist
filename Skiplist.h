#ifndef _SKIPLIST_H_
#define _SKIPLIST_H_
#include <stdio.h>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
const int MAX = 0x7FFFFFFF;
const int MAX_LEVEL = 10;

class Skiplist {
	struct Node {
		int data;
		/* number of elements in array */
		int level;
		/* pointer array, array[i] indicates the left elements of level i */
		Node **array; 
		Node(int d, int l = 1);
		~Node();
	};
public:
	Skiplist();
	~Skiplist();
	inline bool find(int k) {
		return find_pos(k)->data == k;
	}
	bool del(int k);
	bool insert(int k);
private:
	Node* find_pos(int k);
	void increase_root_level();
	// Return the level of inserted elements. 
	int get_level();
	Node *root, *end;
};

#endif