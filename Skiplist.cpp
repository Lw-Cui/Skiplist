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
		Node(int d, int l = 1)
		:data(d), level(l), array(new Node*[l]) {
			memset(array, NULL, sizeof(l * sizeof(Node *)));
		}
		~Node() {
			delete[] array;
		}
	};
public:
	bool find(int k) {
		return find_pos(k)->data == k;
	}
	bool del(int k) {
		if (!find(k)) return false;
		int level = root->level - 1;
		Node *p = root;
		while (true) {
			if (p->array[level]->data > k) {
				/* If (in level) the data of right element of p larger than k,
				from which we could know that the k is in the interval.
				So we decrease level */
				level--;
			} else if (p->array[level]->data == k) {
				/* If (in level) the data of right element of p equal to k,
				then we should move p down to discard all connect to p->array[level],
				and delete it in the end.
				*/
				Node *tmp = NULL;
				while (level >= 0) {
					if (level == 0) tmp = p->array[level];
					p->array[level] = p->array[level]->array[level];
					level--;
				}
				delete tmp;
				return true;
			} else {
				/* If (in level) the data of right element of p smaller than k,
				which means that the interval is small, 
				then we could move p to its right to include k.
				*/
				p = p->array[level];
			}
		}
	}
	bool insert(int k) {
		if (find(k)) return false;
		Node *new_node = new Node(k, get_level());
		// If cnt is large to root->level then root should increase its level.
		if (new_node->level > root->level)
			increase_root_level();
		int level = new_node->level - 1;
		Node *p = root;
		while (true) {
			if (p->array[level]->data > k) {
				/* If (in level) the data of right element of p larger than k,
				from which we could know that the k is in the interval.
				So we insert k into the interval */
				new_node->array[level] = p->array[level];
				p->array[level] = new_node;
				if (--level < 0) return true;//TODO
			} else {
				/* If (in level) the data of right element of p smaller than k,
				which means that the interval is small, 
				then we could move p to its right to include k.
				*/
				p = p->array[level];
			}
		}
	}
	Skiplist():root(new Node(-MAX)), end(new Node(MAX)) {
		for (int i = 0; i < root->level; i++)
			root->array[i] = end;
	}
	~Skiplist() {
		for (Node *i = root->array[0], *pre = root; 
			pre != end; pre = i, i = i->array[0]) 
			delete pre;
		delete end;
	}
private:
	Node* find_pos(int k) {
		int level = root->level - 1;
		Node *p = root;
		while (true) {
			if (p->data == k) {
				return p;
			} else if (p->array[level]->data > k) {
				/* If (in level) the data of right element of p larger than k,
				from which we could know that the interval is too much large. 
				So we decrease level to reduce it. */
				if (--level < 0) return p;
			} else {
				/* If (in level) the data of right element of p smaller than k,
				which means that the interval is small, then we could move p
				to its right to include k.
				*/
				p = p->array[level];
			}
		}
	}
	void increase_root_level() {
		Node **array = new Node*[root->level + 1];
		// TODO: optimize it
		for (int i = 0; i < root->level; i++)
			array[i] = root->array[i];
		array[root->level] = end;
		delete[] root->array;
		root->array = array;
		root->level++;
	}
	// Return the level of inserted elements. 
	int get_level() {
		int cnt = 1;
		/* The max level of elements shouldn't larger
		 than root->level + 1 before updating it */
		while (rand() % 2 && cnt != root->level + 1) cnt++;
		return cnt;
	}
	Node *root, *end;
};

int main(int argc, char *argv) {
	srand(time(NULL));
	Skiplist p;

	const int LEN = 100000;
	int data[LEN];
	for (int i = 0; i < LEN; i++)
		data[i] = rand();
	std::sort(data, data + LEN);
	int end = std::unique(data, data + LEN) - data;
	for (int i = 0; i < end; i++)
		assert(p.insert(data[i]) && p.find(data[i]));
	for (int i = 0; i < end / 2; i++)
		assert(p.del(data[i]) && !p.find(data[i]));
	for (int i = end / 2; i < end; i++)
		assert(p.find(data[i]));
	return 0;
}